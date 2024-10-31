#ifndef SYNCHRONOYS_SERVER_H
#define SYNCHRONOYS_SERVER_H

//////////// INCLUDES ////////////////
#include <vector>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace tcp{

// list of classes
class Server;
class Connection;

/**
 * @brief Handles the TCP connections //!<
 * 
 * Class stores a vector of tcp client connections.
 */
class Server
{
    std::vector<Connection>  connections_;
    static int               client_count; //!< count of active connections
public:
    Server();
    void init(); // starts our tcp server


    Server(const Server& ser)            = delete; // to woun't be able
    Server& operator=(const Server& ser) = delete; // copy a Server object

private:
    int count_of_clients() const;
};

} // tcp 


namespace ip = boost::asio::ip;
class Connection
{
    ip::tcp::socket     socket_;
    ip::tcp::endpoint endPoint_;
    const std::string        id; //!< unique ID of the client
    const std::string        ip; //!< ip of the client


public:
    Connection();
    std::string get_client_id() const;
    std::string get_client_ip() const;
}

#endif // SYNCHRONOYS_SERVER_H