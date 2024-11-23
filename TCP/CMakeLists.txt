cmake_minimum_required(VERSION 3.15)

project(Main)

add_subdirectory(lib)

#find_package(tcp_server CONFIG REQUIRED)

add_executable(main src/main.cpp)
set_target_properties(
    main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_compile_options(
    main PRIVATE
    -Wall -Wextra
)
target_include_directories(
    main
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
)

 target_link_libraries(main tcp_server)