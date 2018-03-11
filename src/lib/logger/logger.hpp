#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger
{
    public:
        static Logger& instance();

        static void log( const std::string &message, int priority );

        static void debug( const std::string &message );
        static void warning( const std::string &message );
        static void error( const std::string &message );

    private:
        static Logger _instance;
        Logger();
        ~Logger();
};

#endif
