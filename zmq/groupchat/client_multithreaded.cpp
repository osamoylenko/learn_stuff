#include <iostream>
#include <string>
#include <thread>

#include <zmqpp/zmqpp.hpp>

#include "groupchat.h"

// TODO: add signal handling

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <nickname>" << std::endl;
        return EXIT_FAILURE;
    }
    std::string nickname = argv[1];

    zmqpp::context ctx;

    zmqpp::socket sub_socket{ctx, zmqpp::socket_type::subscribe};
    sub_socket.connect(CLIENT_SOCKET_NAME);
    sub_socket.set(zmqpp::socket_option::subscribe, ""); // empty string in prefix - so we receive all messages

    std::thread{
        [&ctx, nickname]() {
            zmqpp::socket push_socket{ctx, zmqpp::socket_type::push};
            push_socket.connect(SERVER_SOCKET_NAME);

            while(true) {
                std::string text;
                std::getline(std::cin, text);

                zmqpp::message msg;
                msg << nickname << text;
                push_socket.send(msg);
            }
        }
    }.detach();


    while (true) {
        zmqpp::message msg;
        sub_socket.receive(msg);
        std::string nn, tt;
        msg >> nn >> tt;
        if (nn != nickname) { // skip own messages
            std::cout << "[" << nn << "] " << tt << std::endl;
        }
    }

    return 0;
}
