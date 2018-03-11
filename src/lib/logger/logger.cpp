#include <syslog.h>
#include <unistd.h>
#include <sys/types.h>

#include "logger.hpp"

Logger Logger::_instance=Logger();

Logger::Logger()
{
    setlogmask (LOG_UPTO (LOG_DEBUG));
    openlog ("dominus", LOG_CONS | LOG_PID | LOG_NDELAY | LOG_PERROR, LOG_LOCAL0);
}

Logger::~Logger()
{
    closelog();
}

Logger& Logger::instance()
{
    return _instance;
}

void Logger::log( const std::string &message, int priority )
{
    syslog( priority, message.c_str() );
}

void Logger::debug( const std::string &message )
{
    Logger::log( message, LOG_DEBUG );
}

void Logger::warning( const std::string &message )
{
    Logger::log( message, LOG_WARNING );
}

void Logger::error( const std::string &message )
{
    Logger::log( message, LOG_ERR );
}
