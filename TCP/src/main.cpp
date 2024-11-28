#include "asynchronous_server.h"
#include <iostream>


int main(int argc, char* argv[])
{
    boost::asio::io_context context;
    TCP::Configuration config = TCP::parse_config_file(argv[1]);
    TCP::Server server(context, config);
    // run until our server is alive
    context.run();

    return 0;
}