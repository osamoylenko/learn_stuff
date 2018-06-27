cmake_minimum_required(VERSION 3.8)
project(groupchat)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_libraries(zmqpp zmq)

add_executable(server server.cpp)
add_executable(client client.cpp)
add_executable(client_mt client_multithreaded.cpp)