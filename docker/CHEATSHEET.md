Add user into `docker` usergroup to avoid writing `sudo` every time

`sudo usermod -aG docker $(whoami)`

Check that Docker works

```docker run hello-world```
