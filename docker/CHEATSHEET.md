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


Запустить контейнер:
    docker run -v /hostDir:/contDir -i -t --rm -p 8080:8080 --name Name Image /bin/bash
    -v /hostDir:/contDir подключенине папки
    -i -t интерактивное управление
    --rm удалить контейнер после остановки
    -p hostPort:containerPort пробросить порт
    --name Name имя контейнера
    Image имя образа
    /bin/bash запускаемая команда при запуске контейнера
    --link db:db прилинковать имяконтейнера:внутренее имя

Собрать образ из текущей папки:
    docker build -t Name .


  432  docker commit -m "test container commit" -a "OS" 20d11e4d45fe testcont:sam
  458  docker commit 934cec1ae801 someimg

restart & reattach exited container
docker start -a -i `docker ps -q -l`

docker run --network=host --rm -it ubuntu
