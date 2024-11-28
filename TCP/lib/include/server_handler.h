#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

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