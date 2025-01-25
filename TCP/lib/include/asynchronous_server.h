#ifndef SYNCHRONOYS_SERVER_H
#define SYNCHRONOYS_SERVER_H

//////////// INCLUDES ////////////////
#include <memory> // need for shared_ptr
#include <boost/asio/io_context.hpp>
/////////////////////////////////////

///////////// DEFINES ///////////////////
#define PORT 2001
/////////////////////////////////////////

namespace TCP{

///////////// LIST OF CLASSES ///////////////////
class  Server;
struct Configuration;
/////////////////////////////////////////////////

///////////////////// FUNCTIONS DECLARATION ///////////////////
Configuration parse_config_file(const std::string& filename);
///////////////////////////////////////////////////////////////


/**
 * @brief a TCP server configuration
 * 
 * Now it is contains only one field max_client_count
 */
struct Configuration
{
    size_t max_client_count;
};


/**
 * @brief Handles the TCP clients
 * 
 * The class uses the PIMPL idiom, and contains pointer 
 * to the private members and methods realization.
 * 
 * It also cannot be copied.
 */
class Server
{
    class                         Pimpl; // forward declaration
    std::shared_ptr<Pimpl>  properties_; ///< points to members and methods
public:
    Server(boost::asio::io_context &context, const Configuration &conf);
    ~Server();

    Server(const Server& ser)            = delete; // to woun't be able
    Server& operator=(const Server& ser) = delete; // copy a Server object
};
 

} // TCP
#endif // SYNCHRONOYS_SERVER_H