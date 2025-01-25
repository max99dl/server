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
 * 
 * We add getPimpl() and getConstPimpl() to be able use properties_ in const methods. 
 * That way, the compiler will enforce that you use the const version in a const method. 
 * If the const function also returns a const properties_ pointer, then you also get 
 * compiler const checking for you properties_ methods.
 * 
 * @todo add const method to return count of actual tcp users
 */
class Server
{
    class                         Pimpl; // forward declaration
    std::shared_ptr<Pimpl>  properties_; ///< points to private members and methods
public:
    Server(boost::asio::io_context &context, const Configuration &conf);
    ~Server();

    Server(const Server& ser)            = delete; // to woun't be able
    Server& operator=(const Server& ser) = delete; // copy a Server object
private:
    std::shared_ptr<const Pimpl> getConstPimpl() const;
    std::shared_ptr<Pimpl>       getPimpl();
};
 

} // TCP
#endif // SYNCHRONOYS_SERVER_H