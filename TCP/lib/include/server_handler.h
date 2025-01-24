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


#include <string>

//////////////////////////////////////////////// STRUCT DECLARATIONS START

enum class Status { //!< status of a log message
    DEBUG, INFO, WARNING, ERROR, FATAL
};


//////////////////////////////////////////////// FUNCTIONS DECLARATIONS START

void log_information(const Status       status,
                     const std::string& message);

//////////////////////////////////////////////// FUNCTIONS DECLARATIONS END

#endif // SERVER_HANDLER_H