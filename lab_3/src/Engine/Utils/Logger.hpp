#pragma once

#include <string>

#define LOGGER_LOG(msg) Logger::info(__FILE__, __func__, __LINE__, msg)
#define LOGGER_WARN(msg) Logger::warn(__FILE__, __func__, __LINE__, msg)
#define LOGGER_ERROR(msg) Logger::error(__FILE__, __func__, __LINE__, msg)
#define __LOGGER_STR(a) #a

#define LOG_FUNC Logger::info(__FILE__, __func__, __LINE__, __func__)

class Logger
{
public:

    static void setLogFile(const char* filename);

    static void info(const char* where, const char *func, int line, const char* message);
    static void warn(const char* where, const char* func, int line, const char* message);
    static void error(const char* where, const char* func, int line, const char* message);

    enum class MessageLevel
    {
        Info,
        Warn,
        Error
    };

private:
    FILE* logFile = NULL;

    static Logger instance;
    Logger();
    ~Logger();

    void writeMessage(MessageLevel level, const char* message);
};
