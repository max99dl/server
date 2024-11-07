cmake_minimum_required(VERSION 3.15)

project(TCP_SERVER)

add_executable(main src/main.cpp lib/src/synchronous_server.cpp)

