#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H
/**
 * @file
 * 
 * This file conatains some usful classes and functions 
 * to maintain the server during work.
 * 
 * This functions are not available in the public API
 */

//////////// INCLUDES ////////////////
#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
/////////////////////////////////////


namespace TCP {

///////////// LIST OF CLASSES ///////////////////
class      Session;
enum class  Status;
/////////////////////////////////////////////////

///////////////////// FUNCTIONS DECLARATION ///////////////////
void log_information(const Status       status,
                     const std::string& message);
////////////////////////////////////////////////////////////////


enum class Status { ///< status of a log message
    DEBUG, INFO, WARNING, ERROR, FATAL
};


/**
 * @brief A TCP client session 
 * 
 * This was created as shared ptr and we need later 'this' 
 * therefore we need to inherit from enable_shared_from_this
 */
class Session : public std::enable_shared_from_this<Session>
{
    boost::asio::ip::tcp::socket socket_; ///< our tcp socket
    boost::asio::streambuf       buffer_; ///< buffer for client's messages
public:
    Session(boost::asio::ip::tcp::socket sock);
    void run();

private:
    void wait_for_request();
};


} // TCP

#endif // SERVER_HANDLER_H