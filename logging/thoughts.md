To collect docker containers' output (stdout & stderr)
```
docker run -d --name logagent -e LOGS_TOKEN=[your token] -v /var/run/docker.sock:/var/run/docker.sock sematext/logagent
```

To run logagent as a syslog server
```
docker run -d --name logagent -e LOGS_TOKEN=[your token] LOGAGENT_ARGS="-u 514" -p 514:514/udp sematext/logagent
```

Sending a log message to a remote syslog server
```
<14>sourcehost message text' | nc -v -u -w 0 [host] 514
```

