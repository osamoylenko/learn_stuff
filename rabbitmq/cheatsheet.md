## Admin Web UI
https://www.rabbitmq.com/management.html
```
rabbitmq-plugins enable rabbitmq_management
kubectl port-forward staging-rabbitmq-0 15672
```

## Dumping all messages
https://www.rabbitmq.com/firehose.html
```
rabbitmqctl eval 'application:set_env(rabbitmq_tracing, username, datalore).'
rabbitmqctl eval 'application:set_env(rabbitmq_tracing, password, [pass]).'

rabbitmqctl trace_on -p datalore
rabbitmq-plugins enable rabbitmq_tracing
```

Then create Tracing in Admin section of Web UI. And look at `/var/tmp/rabbitmq-tracing`

When you're done, don't forget to turn tracing off:
```
rabbitmqctl trace_off -p datalore
rabbitmq-plugins disable rabbitmq_tracing
```

## Just commands
```
rabbitmqadmin -u datalore -p [pass] list queues
rabbitmqadmin -u datalore -p [pass] list exchanges
service rabbitmq-server restart
```

## Another way of getting messages
`get queue`  
https://stackoverflow.com/questions/10709533/is-it-possible-to-view-rabbitmq-message-contents-directly-from-the-command-line
