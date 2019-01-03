#ifndef _SYSTEM_IO_LOGGING_HPP
#define _SYSTEM_IO_LOGGING_HPP

#include "System.hpp"
#include "System.Event.hpp"

#include <iostream>
#include <vector>
#include <map>

namespace System {
namespace Io {

/**
 * All supported logging levels 
 */
enum struct LogLevel {
    /**
     * Most verbose logging level. Used for code tracing. 
     */
    TRACE,
    /**
     * Second most verbose logging level. Used for debug messages. 
     */
    DEBUG,
    /**
     * Basic logging level. Used for generic messages.
     */
    INFO,
    /**
     * Logging level used for warning messages.
     */
    WARNING,
    /**
     * Logging level used for errors that could effect the program's execution.
     */
    ERROR,
    /**
     * Logging level used for fatal errors that cause the program to fail.
     */
    FATAL
};

/**
 * A loging observer for outputing values to the terminal 
 */
class ConsoleLogObserver : public System::Event::IObserver<std::string>, public System::Object {
    public:
        /**
         * Print the observed quantity to standard out
         */
        void Update(int event, std::string& observable);
};

/**
 * A loging observer for outputing values to a file 
 */
class FlatFileLogObserver : public System::Event::IObserver<std::string>, public System::Object {
    private: 
        /**
         * The name of the file to output to 
         */
        std::string file;
    public:
        /**
         * Create a new observer that outputs values to a file
         */
        FlatFileLogObserver(std::string& file);
        /**
         * Append the observable quantity to the end of the file;
         */
        void Update(int event, std::string& observable);
};

/**
 * Class allowing for configurable logging of software messages 
 */
class Logger : public System::Event::IObservable<std::string>, System::Object {
    private:
        /**
         * List of all observers for each logging level 
         */
        std::map<LogLevel, std::vector<System::Event::IObserver<std::string>*>> observers;
        /**
         * List of booleans to check if a log level is enabled 
         */
        std::map<LogLevel, bool> enabled;
        /**
         * Internal storage of the data to be logged 
         */
        std::string data;
    public:
        /**
         * Create an empty logger. By default all levels except TRACE and DEBUG are enabled.
         */
        Logger();
        /**
         * Copy an existing logger 
         */
        Logger(const Logger& other);
        /**
         * Destroy the logger 
         */
        ~Logger();
        /**
         * Add an observer to this observable for all events
         */
        void Attach(System::Event::IObserver<std::string>* observer);
        /**
         * Add an observer to this observable for the given event 
         */
        void Attach(int event, System::Event::IObserver<std::string>* observer);
        /**
         * Remove an observer from this observable for the given event 
         */
        void Detach(int event, System::Event::IObserver<std::string>* observer);
        /**
         * Notify observers of this event that the observable may have changed 
         */
        void Notify(int event);

        /**
         * Enable or disable log levels 
         */
        void Enable(LogLevel event, bool isEnabled);
        /**
         * Log a message for the given event 
         */
        void Log(LogLevel event, const std::string& data);

        /**
         * Log a message with the TRACE level
         */
        void Trace(const std::string& data);
        /**
         * Log a message with the DEBUG level
         */
        void Debug(const std::string& data);
        /**
         * Log a message with the INFO level
         */
        void Info(const std::string& data);
        /**
         * Log a message with the WARNING level
         */
        void Warn(const std::string& data);
        /**
         * Log a message with the ERROR level
         */
        void Error(const std::string& data);
        /**
         * Log a message with the FATAL level
         */
        void Fatal(const std::string& data);
};

}
}

#endif