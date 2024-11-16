cmake_minimum_required(VERSION 3.15)

project(TCP_SERVER)

add_executable(
    main
    src/main.cpp
    lib/src/asynchronous_server.cpp
    lib/src/server_handler.cpp
)

target_include_directories(
    main
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/spdlog/include
)