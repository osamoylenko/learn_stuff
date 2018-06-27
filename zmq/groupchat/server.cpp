#include <iostream>
#include <string>
#include <zmqpp/zmqpp.hpp>

#include "groupchat.h"

// TODO: add signal handling

int main() {
    zmqpp::context ctx;

    zmqpp::socket pull_socket{ctx, zmqpp::socket_type::pull};
    pull_socket.bind(SERVER_SOCKET_NAME);

    zmqpp::socket pub_socket{ctx, zmqpp::socket_type::publish};
    pub_socket.bind(CLIENT_SOCKET_NAME);

    while (true) {
        zmqpp::message msg;
        pull_socket.receive(msg);
        std::string user_name, user_msg;
        msg >> user_name >> user_msg;
        std::cout << "[" << user_name << "] " << user_msg << std::endl;

        pub_socket.send(msg);
    }

    return 0;
}
