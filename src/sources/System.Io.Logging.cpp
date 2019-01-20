#include "System.Io.Logging.hpp"
#include "System.Os.hpp" 
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace System {
namespace Io {
    
void ConsoleLogObserver::Update(int event, std::string& observable) {
    std::cout << observable;
}

FlatFileLogObserver::FlatFileLogObserver(std::string& file) : file(file) {}

void FlatFileLogObserver::Update(int event, std::string& observable) {
    std::ofstream file;
    file.open(this->file, std::ios::out | std::ios::app);
    if(!file.fail()){
        file << observable;
    }
}

Logger::Logger() : System::Object(), observers(), enabled(), data() {
    enabled[LogLevel::TRACE]    = false;
    enabled[LogLevel::DEBUG]    = false;
    enabled[LogLevel::INFO]     = true;
    enabled[LogLevel::WARNING]  = true;
    enabled[LogLevel::ERROR]    = true;
    enabled[LogLevel::FATAL]    = true;
}

Logger::Logger(const Logger& other) : System::Object(), observers(other.observers), enabled(other.enabled), data(other.data) {}

Logger::~Logger() {}

void Logger::Attach(System::Event::IObserver<std::string>* observer) {
    this->Attach((int)LogLevel::TRACE, observer);
    this->Attach((int)LogLevel::DEBUG, observer);
    this->Attach((int)LogLevel::INFO, observer);
    this->Attach((int)LogLevel::WARNING, observer);
    this->Attach((int)LogLevel::ERROR, observer);
    this->Attach((int)LogLevel::FATAL, observer);
}

void Logger::Attach(int event, System::Event::IObserver<std::string>* observer) {
    observers[static_cast<LogLevel>(event)].push_back(observer);
}

void Logger::Detach(int event, System::Event::IObserver<std::string>* observer) {
    std::vector<System::Event::IObserver<std::string>*>& ptr = observers[static_cast<LogLevel>(event)];
    ptr.erase(std::remove(ptr.begin(), ptr.end(), observer), ptr.end());
}

void Logger::Notify(int event) {
    if(enabled[static_cast<LogLevel>(event)]) {
        for(auto observer : observers[static_cast<LogLevel>(event)]) {
            observer->Update(event, this->data);
        }
    }
}

void Logger::Enable(LogLevel event, bool isEnabled) {
    enabled[event] = isEnabled;
}

void Logger::Log(LogLevel event, const std::string& data) {
    std::stringstream buf;
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    buf 
        << "[" 
        << std::put_time(std::localtime(&now), "%F %T")
        << "] ";
    switch(event) {
        case LogLevel::TRACE:
            buf << "[TRACE] ";
            break;
        case LogLevel::DEBUG:
            buf << "[DEBUG] ";
            break;
        case LogLevel::INFO:
            buf << "[INFO] ";
            break;
        case LogLevel::WARNING:
            buf << "[WARNING] ";
            break;
        case LogLevel::ERROR:
            buf << "[ERROR] ";
            break;
        case LogLevel::FATAL:
            buf << "[FATAL] ";
            break;
    }
    buf 
        << data 
        << System::Os::EOL;
    this->data = buf.str();
    this->Notify(static_cast<int>(event));
}

void Logger::Trace(const std::string& data) {
    Log(LogLevel::TRACE, data);
}

void Logger::Debug(const std::string& data) {
    Log(LogLevel::DEBUG, data);
}

void Logger::Info(const std::string& data) {
    Log(LogLevel::INFO, data);
}

void Logger::Warn(const std::string& data) {
    Log(LogLevel::WARNING, data);
}

void Logger::Error(const std::string& data) {
    Log(LogLevel::ERROR, data);
}

void Logger::Fatal(const std::string& data) {
    Log(LogLevel::FATAL, data);
}


}
}