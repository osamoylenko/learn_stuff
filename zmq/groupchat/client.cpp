#include <iostream>
#include <string>
#include <zmqpp/zmqpp.hpp>
#include <zmq.h>
#include <unistd.h>

#include "groupchat.h"

// TODO: add signal handling

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <nickname>" << std::endl;
        return EXIT_FAILURE;
    }
    std::string nickname = argv[1];

    zmqpp::context ctx;

    zmqpp::socket push_socket{ctx, zmqpp::socket_type::push};
    push_socket.connect(SERVER_SOCKET_NAME);

    zmqpp::socket sub_socket{ctx, zmqpp::socket_type::subscribe};
    sub_socket.connect(CLIENT_SOCKET_NAME);
    sub_socket.set(zmqpp::socket_option::subscribe, ""); // empty string in prefix - so we receive all messages

    zmqpp::poller poller;
    poller.add(sub_socket);
    poller.add(STDIN_FILENO);

    while (true) {
        poller.poll();

        if (poller.has_input(sub_socket)) {
            zmqpp::message msg;
            sub_socket.receive(msg);
            std::string nn, tt;
            msg >> nn >> tt;
            if (nn != nickname) { // skip own messages
                std::cout << "[" << nn << "] " << tt << std::endl;
            }
        }

        if (poller.has_input(STDIN_FILENO)) {
            std::string text;
            std::getline(std::cin, text);

            zmqpp::message msg;
            msg << nickname << text;
            push_socket.send(msg);
        }
    }

    return 0;
}
