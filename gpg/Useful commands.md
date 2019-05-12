gpg --list-keys --with-subkey-fingerprints


add subkey with auth capability

gpg --export-ssh-key <subkey-id>!
(exclamation mark to prevent using of the primary key instead of the specified one)


might also consider using paperkey

gpg --list-keys --with-keygrip (keygrip is equal to private key file names as they are stored in .gnupg)


put
enable-ssh-support
to ~/.gnupg/gpg-agent.conf
check necessity


put keygrip of ssh key to ~/.gnupg/sshcontrol


put it to .bashrc (or another autoloading file)

# GPG stuff
export GPG_TTY=$(tty)

unset SSH_AGENT_PID
if [ "${gnupg_SSH_AUTH_SOCK_by:-0}" -ne $$ ]; then
  export SSH_AUTH_SOCK="$(gpgconf --list-dirs agent-ssh-socket)"
fi


read man gpg-agent (cause on Internet there is a lot of stale information)

check ssh-add -L
you'll see key from gpg

then to specify it in ~/.ssh/config
ssh-add -L > ~/.ssh/mykey.pub
chmod 0600 ~/.ssh/mykey.pub

put to config:
Host vultr
  Hostname 199.247.20.206
  User oleg
  IdentityFile ~/.ssh/vultr.pub
  IdentitiesOnly yes


Yes it's fucking undocumented possibility to specify public key in IdentityFile option.
Together with IdentitiesOnly option turned on it allows to specify which key to use in ssh-agent.

Restart gpg-agent in order to reload configuration, reset cached passphrase, etc.
`gpg-connect-agent <<< reloadagent`

## Exporting
```
gpg --export-secret-keys
gpg --export-secret-subkeys (without master key)
```

`gpg --show-keys [file]` allows to see keys from the file before actually importing them

## Decent FLOSS password managers
Bitwarden
KeepassXC

## Software
pinentry-mac - GUI app to enter a passphrase

