From https://github.com/JetBrains/datalore-workshop-0mq

# Preliminaries

    Install libzmq and libzmqpp libraries. On MacOS:

        brew install zmq zmqpp

    Install zmq wrapper for you favourite language.

# RAII in C++

    RAII -- Resource acquisition is initialization

    raii/raii-examples.cpp

# Ping-pong using REQ-REP sockets

    ping-pong/client.cpp
    ping-pong/server.cpp

                           Client   Client   Client
                            REQ      REQ      REQ
                            | ^      | ^      | ^
                            | |      | |      | |
                            v |      v |      v |  
                            +-------------------+
                            |       REP         |
                            |      Server       |
                            +-------------------+

    Showcases:
        * start server first, then client
        * start many clients and one server
          `for i in {1..5}; do (./client $i &) ; done`
        * start client first, then server
        * server recovering does not work

    Exercises
        *   read http://zguide.zeromq.org/page:all#Ask-and-Ye-Shall-Receive
        *   Implement the example in your favourite language.

# PUB-SUB sockets

    pub-sub/server.cpp
    pub-sub/client.cpp

                                  Publisher
                                     PUB
                                     bind
                                      |
                                      |
                         +------------+------------+
                         |            |            |     
                         |            |            |
                         v            v            v
                                            
                        SUB          SUB          SUB   
                       connect      connect      connect
                     Subscriber   Subscriber   Subscriber

    *   Subscription takes some time. While client's subscription is not
        finished, the client will not receive the messages, they can be lost.

    Showcase

    *   you can stop and restart the server as often as you like, and the client
        will keep working

    Exercises
        *   Read http://zguide.zeromq.org/page:all#Getting-the-Message-Out
        *   Implement the example in your favourite language.
        
# PULL-PUSH sockets

    pull-push/ventilator.cpp
    pull-push/worker.cpp
    pull-push/sink.cpp

                                  Ventilator
                                     PUSH
                                      |
                                      v
                             +--------+--------+
                             |        |        |
                             v        v        v
                             |        |        |
                            PULL     PULL     PULL
                           Worker   Worker   Worker
                            PUSH     PUSH     PUSH 
                             |        |        |
                             v        v        v
                             |        |        |
                             +--------+--------+
                                      |
                                      v
                                     PULL
                                     Sink

    Showcases

        *   Remove the synchronization in the beginning of `ventilator`.

    Quotes from 0mq guide:

        *   The workers connect upstream to the ventilator, and downstream to
            the sink.  This means you can add workers arbitrarily. If the
            workers bound to their endpoints, you would need (a) more
            endpoints and (b) to modify the ventilator and/or the sink each
            time you added a worker. We say that the ventilator and sink are
            stable parts of our architecture and the workers are dynamic parts
            of it.

        *   We have to synchronize the start of the batch with all workers
            being up and running. This is a fairly common gotcha in ZeroMQ and
            there is no easy solution. The zmq_connect method takes a certain
            time. So when a set of workers connect to the ventilator, the
            first one to successfully connect will get a whole load of
            messages in that short time while the others are also connecting.
            If you don't synchronize the start of the batch somehow, the
            system won't run in parallel at all. Try removing the wait in the
            ventilator, and see what happens.

        *   The ventilator's PUSH socket distributes tasks to workers
            (assuming they are all connected before the batch starts going
            out) evenly. This is called load balancing and it's something
            we'll look at again in more detail.

        *   The sink's PULL socket collects results from workers evenly. This
            is called fair-queuing.

    Exercises
        *   Read http://zguide.zeromq.org/page:all#Divide-and-Conquer
        *   Implement the example in your favourite language.

# Simple broker, polling, DEALER and ROUTER sockets

    broker/client.cpp
    broker/broker.cpp
    broker/worker.cpp

                           Client  Client  Client
                             REQ     REQ     REQ
                              |       |       |
                              |       |       |   
                              +-------+-------+
                                      |
                                      |
                                    ROUTER
                                   frontend
                                    ------
                                    Broker
                                    ------
                                   backend
                                    DEALER
                                      |
                                      |
                              +-------+-------+
                              |       |       |   
                             REP     REP     REP
                            Worker  Worker  Worker

    Showcases:
        *   Run one worker, client and broker
        *   Uncomment logging of number of frames in worker and broker.
            Discuss how REP and REQ sockets work. 
        *   Run several workers, clients and a broker. Check that all clients
            and workers are in the logs.
        *   Show that without self-pipe trick Foo's desctructor is not called
            if broker is interrupted.

    Notes
        Balancing in this example is round-robin (fair-queue). It will work
        poorly if tasks have very different time complexity. For more
        elaborate balancing see
        http://zguide.zeromq.org/page:all#Chapter-Advanced-Request-Reply-Patterns.

    Exercises:
        *   read http://zguide.zeromq.org/page:all#Shared-Queue-DEALER-and-ROUTER-sockets
        *   Implement the example in your favourite language.
        *   Implement the example using `zmq_proxy` function.

# Multithreading with 0mq

    > To make utterly perfect MT programs (and I mean that literally), we don't need
    > mutexes, locks, or any other form of inter-thread communication except
    > messages sent across ZeroMQ sockets.

    > just don't share state

                                                                  0mq tutorial 
    There is PAIR socket for thread synchronization. See
    http://zguide.zeromq.org/page:all#Signaling-Between-Threads-PAIR-Sockets
    for details. PAIR sockets are only for two peers, do not reconnect
    automatically, connecting should be after binding.

    Multi-threading models:

        *   tightly-bound: use inproc transport and PAIR sockets, one context
            for several threads. Lowest latency, not scalable to processes.

        *   loosely-bound: every thread has its own context, do not use PAIR
            sockets. Scalable model: you can easily change inproc transport to
            ipc or tcp and scale your application from threads to processes or
            even processes on a distributed cluster of computers.

    Sockets are not thread-safe. Do not use a socket in several threads.

    Datalor's evaluator was rewritten using 0mq. It had just several threads
    and processes, but was incomprehensible because of synchronization
    complexity. It was not clear where you should synchronize, some
    synchronization points were added only after failures in production. Now
    there is no threads, only processes, and all synchronization and message
    passing is done using 0mq.

    Exercise
        *   read http://zguide.zeromq.org/page:all#Multithreading-with-ZeroMQ
        *   Play with PAIR socket

# Exercise

    Implement load-balancing message broker,
    http://zguide.zeromq.org/page:all#A-Load-Balancing-Message-Broker.

# General notes

    Transports:

        *   in-process
        *   inter-process
        *   TCP
        *   multicast

        See also man pages: zmq_inproc, zmq_ipc, zmq_tcp, zmq_pgm        

    Patterns

        *   REQ-REP
        *   PUB-SUB
        *   PULL-PUSH
        *   ROUTER
        *   DEALER

        See also man pages: `man zmq_socket`

# Why 0mq?

    * asynchronous: IO operations are performed in a separate thread,
      implementation is based on lock-free data structures;
    * connection order does not matter. If you use TCP, you should start a
      server at first and only then clients can connect.
    * easy switch between transports, application is simple to scale
    * manages connections
    * routing sockets
    * support basic load-balancing
    * messages operations are atomically: one can not read or write a message
      partly
    * can combine 0mq sockets and system files in one poll.
    * does not impose any format on messages

# Why not a message broker?

    * require additional management, can increase complexity
    * another SPOF (single point of failure) and a bottleneck
    * increase latency

# Notable examples of usage

    * Datalore (evaluator)
    * Jupyter
    * bitcoin core

Reference

 [1] 0mq guide: http://zguide.zeromq.org/page:all
 [2] Examples from 0mq guide:
     git clone --depth=1 https://github.com/imatix/zguide.git
 [3] `man zmq`
