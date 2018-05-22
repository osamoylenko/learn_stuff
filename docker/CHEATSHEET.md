Add user into `docker` usergroup to avoid writing `sudo` every time

`sudo usermod -aG docker $(whoami)`

Check that Docker works

`docker run hello-world`

Finding and pull image from repository
```
docker search ubuntu
docker pull ubuntu
docker run ubuntu
docker images
```

`run` can automatically pull the image

Run interactively (with console access)

`docker run -it ubuntu`

To look inside the image
```
docker save hello-world > hw.tar
tar -xvf hw.tar
```

To commit the container and create new image
`docker commit 934cec1ae801 someimg


One liner to stop / remove all of Docker containers:
```
docker stop $(docker ps -a -q)
docker rm $(docker ps -a -q)
```

You can get some clues what an image consists of:
    docker history --no-trunc someimg

Map ports & run in background
    docker run -p 9090:9090 -d prom/prometheus
