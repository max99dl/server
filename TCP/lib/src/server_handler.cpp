#include "server_handler.h"
#include "spdlog/spdlog.h"


//////////////////////////////////////////// LOGGER START

Logger::Logger()
{
    spdlog::default_logger()->set_level(spdlog::level::trace);
}

void Logger::log_information(const Status       status,
                             const std::string& message)
{

    switch (status)
    {
    case Status::DEBUG:
        spdlog::debug(message); break;
    case Status::INFO:
        spdlog::info(message);  break;
    case Status::WARN:
        spdlog::warn(message);  break;
    case Status::ERROR:
        spdlog::error(message); break;
    case Status::CRITICAL:
        spdlog::critical(message);break;
    }
}
//////////////////////////////////////////// LOGGER END

//////////////////////////////////////////// CONFIGURATION START

//////////////////////////////////////////// CONFIGURATION END