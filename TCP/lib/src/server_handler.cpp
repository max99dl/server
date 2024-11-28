#include "server_handler.h"
#include "boost/log/trivial.hpp" // for logging


/**
 * @brief Log information during work.
 * @param status  status of the log message
 * @param message the log message
 */
void log_information(const Status       status,
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

//////////////////////////////////////////// LOGGER END

//////////////////////////////////////////// CONFIGURATION START

//////////////////////////////////////////// CONFIGURATION END