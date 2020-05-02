## Strategy
* Store the master key in really secure manner (don't store it on devices!)
* For devices use subkeys signed by the master key. And cipher it with a different passphrase!
* You can store whole .gnupg directory on an external encrypted USB device. See `GNUPGHOME` envvar and `--homedir` option

## List keys:
```
gpg --list-keys --with-subkey-fingerprints
gpg --list-keys --with-keygrip (keygrip is equal to a private key file name as it's stored in ~/.gnupg/private*)
gpg --list-secret-keys
```
Some detailed info about a key you might retrieve with `gpg --edit-key [key]`.

## Export
### Public keys
You need to export public keys in order to use a smartcard. Because you can't extract public keys from a smartcard itself.
```
gpg --export (all subkeys will be included)
```

### Private keys
```
gpg --export-secret-keys
gpg --export-secret-subkeys (without master key)
gpg --export-secret-subkeys [key]! (only specific subkey)
```
For backup purposes you might also consider using `paperkey`.

## Import preview
`gpg --show-keys [file]` allows to see keys from the file before actually importing them  
(On older versions: `gpg --import-option show-only --import [file]`)

## Trust level
After importing, in order to keep the original trust level (ultimate):
```
gpg --edit-key [key]
```
Then type `trust` and select desired level.

## Decent FLOSS password managers
* Bitwarden
* KeepassXC

## Software
pinentry-mac - GUI app to enter a passphrase

## Add subkey
Use expert mode `gpg --edit-key --expert [user-id]` to get more options of subkey crypto algorithms.

## Using gpg-agent as ssh-agent
Read `man gpg-agent` ('cause on Internet there is a lot of stale information)
1. Add subkey with auth capability (`--edit-key` dialogue)
2. Put this to `.bashrc` (or another autoloading file):
```
# GPG stuff
export GPG_TTY=$(tty)

unset SSH_AGENT_PID
if [ "${gnupg_SSH_AUTH_SOCK_by:-0}" -ne $$ ]; then
  export SSH_AUTH_SOCK="$(gpgconf --list-dirs agent-ssh-socket)"
fi
```
3. Add keygrip of auth key to `~/.gnupg/sshcontrol`
5. Check `ssh-add -L`. You'll see key from gpg
6. If you want to specify which key stored in agent to use:
  * `gpg --export-ssh-key <auth-subkey-id>! > ~/.ssh/mykey.pub`
  * `chmod 0600 ~/.ssh/mykey.pub`
  * Specify it in `~/.ssh/config` as `IdentityFile`

Yes it's a fucking undocumented possibility to specify a public key in the `IdentityFile` option.
Together with `IdentitiesOnly` option turned on it allows to specify which key to use in ssh-agent.

7. Restart gpg-agent in order to reload configuration, reset cached passphrase, etc.  
`gpg-connect-agent <<< reloadagent`

## To connect smart card on Ubuntu
```
sudo apt install scdaemon
gpg --card-status
gpg --edit-card
gpgconf --kill gpg-agent
```

## Working with smart card
* Inserting a smart card automatically adds the auth key to gpg-agent. Even without specifying in ~/.gnupg/sshcontrol
* Inserting a smart card automatically adds keyfiles (stubs) to ~/.gnupg/private*

## Some other interesting features
### Strengthening hash preferences
You can set your key to prefer stronger hashes. Use the `gpg --edit-key` command. At the `gpg>` prompt, enter the command `setpref SHA512 SHA384 SHA256 SHA224 AES256 AES192 AES CAST5 ZLIB BZIP2 ZIP Uncompressed`, then save.

### RAMFS
You can create a RAM-based ramfs temporary folder to prevent your keys from being written to permanent storage. Use ramfs instead of tmpfs/ or /dev/shm/ because ramfs doesn’t write to swap.
```
mkdir /tmp/gpg
sudo mount -t ramfs -o size=1M ramfs /tmp/gpg
```
