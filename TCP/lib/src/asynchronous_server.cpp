
//////////// INCLUDES ///////////////
#include "asynchronous_server.h"
#include "server_handler.h"
#include <boost/asio/read_until.hpp>           // to read client's messages
#include "boost/property_tree/json_parser.hpp" // to parse json
#include "boost/property_tree/ptree.hpp"       // to parse json
#include <memory>                              // for shared_ptr
////////////////////////////////////////

//////////// DEFINES /////////////
///////////////////////////////
using namespace TCP;
using namespace boost::asio;
using namespace boost::asio::ip;

////////////////////////////////// GLOBAL VARIABLES //////////////////
////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////// START SERVER'S PART
/**
 * @brief Private properties of the class Server.
 * 
 */
class Server::Pimpl
{
public:
    boost::asio::ip::tcp::acceptor acceptor_;
    const Configuration              config_;

    Pimpl(io_context &io_contx, const Configuration &conf)
        : acceptor_(io_contx, tcp::endpoint(tcp::v4(), PORT)),
          config_(conf)
    {}
    void do_accept(); // waits for clients
};

Server::Server(io_context &io_contx, const Configuration &conf)
    : properties_( new Server::Pimpl(io_contx, conf) ) // @todo may be need to replace with `make_shared` 
{
    log_information(Status::DEBUG, "Start server...");
    // now we ready to waiting for clients
    properties_->do_accept();
}

Server::~Server()
{
    log_information(Status::DEBUG, "Close server...");
    properties_->acceptor_.close();
}

void Server::Pimpl::do_accept()
{
    /*
     * This is an async accept which means the lambda function is executed, 
     * when a client connects.
     * We can pass to the async_accept a callable object, instead of socket.
    */
    acceptor_.async_accept([this](boost::system::error_code ec,
                           tcp::socket socket)
    {
        if(ec) { // check for success accepting
            log_information(Status::ERROR, ec.message());
        } else {   
            // log some information about the connection
            const std::string message =
                 "creating session on: "
                 + socket.remote_endpoint().address().to_string()
                 + ":"
                 + std::to_string(socket.remote_endpoint().port());

            log_information(Status::INFO, message);
            /*
             * Create a session where we immediately call the run function. 
             * Note: the socket is passed to the lambda here
             */
            std::make_shared<Session>(std::move(socket))->run();
        }

        /*
         * since we want multiple clients to connect,
         * wait for the next one by calling do_accept()
         */
        do_accept();
    });
}
//////////////////////////////////////////////////////////////////////////// END SERVER'S PART



//////////////////////////////////////////////////////////////////////////// FUNCTIONS DEFENITION START
/**
 * parse a .json file with TCP server parameters, and check for valid values. 
 * In case of invalid configuration there are exit() is called. 
 * 
 * @param  filename - path to the config file
 * @return TCP client configuration
 */
Configuration TCP::parse_config_file(const std::string& filename)
{
    boost::property_tree::ptree rootHive;
    boost::property_tree::read_json(filename, rootHive);

    auto client_count = rootHive.get<size_t>("Server.max_client_count", 0);

    // check for valid server configuration
    if(client_count < 1) // at least must be 1 client
    {
        log_information(Status::FATAL, "Some problems in json configuration");
        exit(1);
    }
    return {client_count};
}
//////////////////////////////////////////////////////////////////////////// FUNCTIONS DEFENITION END