#ifndef SYNCHRONOYS_SERVER_H
#define SYNCHRONOYS_SERVER_H

//////////// INCLUDES ////////////////
#include <vector>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/read_until.hpp>
/////////////////////////////////////

///////////////////////////////// DEFINES
#define PORT 2001
/////////////////////////////////

namespace TCP{

// list of classes
class Server;
class Session;


/**
 * @brief Handles the TCP clients //!<
 * 
 * Class stores a vector of tcp client connections.
 */
class Server
{
    boost::asio::ip::tcp::acceptor acceptor_;
public:
    Server(boost::asio::io_context &context);
    ~Server();

    Server(const Server& ser)            = delete; // to woun't be able
    Server& operator=(const Server& ser) = delete; // copy a Server object
private:
    void do_accept(); //!< waits for the clients
};
 


/**
 * @brief A TCP client session //!<
 * 
 * This was created as shared ptr and we need later 'this' 
 * therefore we need to inherit from enable_shared_from_this
 */
class Session : public std::enable_shared_from_this<Session>
{
    boost::asio::ip::tcp::socket socket_; //!< our tcp socket
    boost::asio::streambuf       buffer_; //!< buffer for client's messages
public:
    Session(boost::asio::ip::tcp::socket sock);
    void run();

private:
    void wait_for_request();
};






} // TCP
#endif // SYNCHRONOYS_SERVER_H