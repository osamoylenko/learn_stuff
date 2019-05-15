## List keys:
```
gpg --list-keys --with-subkey-fingerprints
gpg --list-keys --with-keygrip (keygrip is equal to a private key file name as it's stored in ~/.gnupg/private*)
gpg --list-secret-keys
```
Some detailed info about a key you might retrieve with `gpg --edit-key [key]`.

## Export
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
4. Add `enable-ssh-support` to `~/.gnupg/gpg-agent.conf`  
TODO: check necessity of this step
5. Check `ssh-add -L`. You'll see key from gpg
6. If you want to specify which key stored in agent to use:
  * `gpg --export-ssh-key <auth-subkey-id>! > ~/.ssh/mykey.pub`
  * `chmod 0600 ~/.ssh/mykey.pub`
  * Specify it in `~/.ssh/config` as `IdentityFile`

Yes it's a fucking undocumented possibility to specify a public key in the `IdentityFile` option.
Together with `IdentitiesOnly` option turned on it allows to specify which key to use in ssh-agent.

7. Restart gpg-agent in order to reload configuration, reset cached passphrase, etc.  
`gpg-connect-agent <<< reloadagent`
