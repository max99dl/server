#include "server_handler.h"
#include "boost/log/trivial.hpp"     // for logging
#include <boost/asio/read_until.hpp> // to read client's messages
#include <iostream>

using namespace TCP;
using namespace boost::asio::ip;


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
    // `run` was already called in our server, where we just wait for requests
    wait_for_request();
}

void Session::wait_for_request()
{
    ///< shared_from_this() return a shared_ptr to `this` pointer
    auto self(shared_from_this());
    /*
     * And now call the lambda once data arrives. 
     * We read a string until the null termination character
     */
    async_read_until(socket_, buffer_, "\0",
        [this, self](boost::system::error_code ec, size_t length) {
            /*
             * If there was no error, everything went well and for this demo 
             * we print the data to stdout and wait for the next request
             */
            if(!ec) {
                std::string data{
                    std::istreambuf_iterator<char>(&buffer_),
                    std::istreambuf_iterator<char>()
                };
                /*
                 * we just print the data, you can here call other api's
                 * or whatever the server needs to do with the received data
                 */
                std::cout << data << length << std::endl;
                wait_for_request();
            } else {
                log_information(Status::ERROR, ec.message());
            }
    });
}
/////////////////////////////////////////////////////////////////////////////// END SESSIONS'S PART


//////////////////////////////////////////////////////////////////////////// FUNCTIONS DEFENITION START
/**
 * @brief Log information during work.
 * @param status  status of the log message
 * @param message the log message
 */
void TCP::log_information(const Status       status,
                     const std::string& message)
{

    switch (status)
    {
    case Status::DEBUG:
        BOOST_LOG_TRIVIAL(debug) << message;
        break;
    case Status::INFO:
        BOOST_LOG_TRIVIAL(info) << message;
        break;
    case Status::WARNING:
        BOOST_LOG_TRIVIAL(warning) << message;
        break;
    case Status::ERROR:
        BOOST_LOG_TRIVIAL(error) << message;
        break;
    case Status::FATAL:
        BOOST_LOG_TRIVIAL(fatal) << message;
        break;
    }
}
//////////////////////////////////////////////////////////////////////////// FUNCTIONS DEFENITION END