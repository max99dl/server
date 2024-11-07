
//////////// INCLUDES ////////////////
#include "../include/asynchronous_server.h"
#include <thread>
#include <iostream>
#include <memory>
////////////////////////////////////////

//////////// DEFINES /////////////
///////////////////////////////
using namespace TCP;
using namespace boost::asio;
using namespace boost::asio::ip;

////////////////////////////////////////////////////////////////////// FUNCTIONS DECLARATION
///////////////////////////////////////////

//////////////////////////////////////////////////////////////////////// START SERVER'S PART
Server::Server(io_context &io_contx)
    : acceptor_(io_contx, tcp::endpoint(tcp::v4(), PORT))
{
    // now we ready to waiting for clients
    do_accept();
}


void Server::do_accept()
{
    /**
     * This is an async accept which means the lambda function is executed, 
     * when a client connects.
     * We can pass to the async_accept a callable object, instead of socket.
    */
    acceptor_.async_accept([this](boost::system::error_code ec,
                           tcp::socket socket)
    {
        if(ec) { //!< check for success accepting
            std::cout << "error: " << ec.message() << std::endl;
        } else {   
            // print some information about the connection
            std::cout << "creating session on: "
                      << socket.remote_endpoint().address().to_string()
                      << ":" << socket.remote_endpoint().port()
                      << '\n';
            /**
             * Create a session where we immediately call the run function. 
             * Note: the socket is passed to the lambda here
             */
            std::make_shared<Session>(std::move(socket))->run();
        }

        /**
         * since we want multiple clients to connect,
         * wait for the next one by calling do_accept()
         */
        do_accept();
    });
}
//////////////////////////////////////////////////////////////////////////// END SERVER'S PART


//////////////////////////////////////////////////////////////////////////// START SESSIONS'S PART
Session::Session(tcp::socket sock)
    : socket_(std::move(sock))
{}

/**
 * @brief Call the private method wait_for_requests()
 * 
 * We add this public method to make our API more flexible
 */
void Session::run()
{
    //!< `run` was already called in our server, where we just wait for requests
    wait_for_request();
}

void Session::wait_for_request()
{
    //!< shared_from_this() return a shared_ptr to `this` pointer
    auto self(shared_from_this());
    /**
     * And now call the lambda once data arrives. 
     * We read a string until the null termination character
     */
    async_read_until(socket_, buffer_, "\0",
        [this, self](boost::system::error_code ec, size_t length) {
            /**
             * If there was no error, everything went well and for this demo 
             * we print the data to stdout and wait for the next request
             */
            if(!ec) {
                std::string data{
                    std::istreambuf_iterator<char>(&buffer_),
                    std::istreambuf_iterator<char>()
                };
                /**
                 * we just print the data, you can here call other api's
                 * or whatever the server needs to do with the received data
                 */
                std::cout << data << std::endl;
                wait_for_request();
            } else {
                std::cout << "error: " << ec << std::endl;
            }
    });
}
/////////////////////////////////////////////////////////////////////////////// END SESSIONS'S PART