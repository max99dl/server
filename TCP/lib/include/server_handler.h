#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <string>

//////////////////////////////////////////////// STRUCT DECLARATIONS START

enum class Status { //!< status of a log message
    DEBUG, INFO, WARN, ERROR, CRITICAL
};

/////////////////////////////////////////////////////////////////////////////////////// LOGGER START
/**
 * Log server's information for debug
 */
struct Logger
{
    Logger();
    void log_information(const Status       status,
                         const std::string& message);
};
//////////////////////////////////////////////////////////////////////////////////////// LOGGER END


//////////////////////////////////////////////// FUNCTIONS DECLARATIONS START

//////////////////////////////////////////////// FUNCTIONS DECLARATIONS END

#endif // SERVER_HANDLER_H