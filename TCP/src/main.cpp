#include "asynchronous_server.h"
#include <iostream>


int main()
{
    boost::asio::io_context context;
    TCP::Configuration config = TCP::parse_config_file("filename");
    TCP::Server server(context, {});
    // run until our server is alive
    context.run();

    return 0;
}