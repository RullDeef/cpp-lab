#include "Logger.hpp"
#include <stdexcept>
#include <ctime>
#include <iostream>

void Logger::setLogFile(const char* filename)
{
    std::time_t t = std::time(NULL);   // get time now
    std::tm* now = std::localtime(&t);

    char timedFilename[256];
    std::snprintf(timedFilename, 256, "%s_%02d%02d%02d.log", filename, now->tm_year % 100, now->tm_mon % 12 + 1, now->tm_mday);

    if (instance.logFile)
        fclose(instance.logFile);
    instance.logFile = fopen(timedFilename, "at");
    if (!instance.logFile)
        throw std::runtime_error("invalid log file");
}

void Logger::info(const char* where, const char* func, int line, const char* message)
{
    std::string str = std::string(where) + ":" + func + ":" + std::to_string(line) + ": " + message;
    instance.writeMessage(MessageLevel::Info, str.c_str());
}

void Logger::warn(const char* where, const char* func, int line, const char* message)
{
    std::string str = std::string(where) + ":" + func + ":" + std::to_string(line) + ": " + message;
    instance.writeMessage(MessageLevel::Warn, str.c_str());
}

void Logger::error(const char* where, const char* func, int line, const char* message)
{
    std::string str = std::string(where) + ":" + func + ":" + std::to_string(line) + ": " + message;
    instance.writeMessage(MessageLevel::Error, str.c_str());
}

Logger::Logger()
{
}

Logger::~Logger()
{
    if (logFile)
        fclose(logFile);
}

Logger Logger::instance;

void Logger::writeMessage(MessageLevel level, const char* message)
{
    if (!logFile)
        return;

    std::time_t t = std::time(NULL);   // get time now
    std::tm* now = std::localtime(&t);

    char timedMessage[256];
    std::snprintf(timedMessage, 256, "[%02d:%02d:%02d]: %s", now->tm_hour, now->tm_min, now->tm_sec, message);

    fprintf(logFile, "%s\n", timedMessage);
}
