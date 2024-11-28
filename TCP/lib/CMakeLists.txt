cmake_minimum_required(VERSION 3.15)

project(TCP_server_library)

add_library(
    tcp_server
    STATIC
    src/asynchronous_server.cpp
    src/server_handler.cpp
)
set_target_properties(
    tcp_server PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_compile_options(
    tcp_server PRIVATE
    -Wall -Wextra -Werror
)
target_include_directories(
    tcp_server
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    #${CMAKE_CURRENT_SOURCE_DIR}/boost
)
install(
    TARGETS tcp_server EXPORT tcp_serverTargets
    LIBRARY  DESTINATION lib
    ARCHIVE  DESTINATION lib
    INCLUDES DESTINATION include
)
install(FILES include/asynchronous_server.h DESTINATION include)

install(
    EXPORT tcp_serverTargets
    FILE tcp_serverConfig.cmake
    DESTINATION lib/cmake
)