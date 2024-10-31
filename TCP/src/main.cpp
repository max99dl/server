#include "synchronous_server.h"
//#include <iostream>

int main() {
    tcp::Server server;
    server.init();
    // we don't use the method server.close()
    // because we don't mean to close it
    size_t ad;
}