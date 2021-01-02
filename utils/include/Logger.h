#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <map>

#define LOGINFO(msg) ::Logger::getCoreLogger()->info(msg);
#define LOGDEBUG(msg) ::Logger::getCoreLogger()->debug(msg);
#define LOGWARNING(msg) ::Logger::getCoreLogger()->warn(msg);
#define LOGERROR(msg)::Logger::getCoreLogger()->error(msg);

enum class LogLevel
{
    INFO,
    DEBUG,
    WARNING,
    ERROR
};

struct StreamInfo
{
    std::wostream* stream;
    LogLevel level;

    StreamInfo(std::wostream& s, LogLevel lvl)
    {
        stream = &s;
        level = lvl;
    }
};

class Logger
{
public:
    Logger();
    ~Logger();

    static void init();

    void addStream(std::wostream& s, LogLevel level);

    inline static std::shared_ptr<Logger>& getCoreLogger() {return mCoreLogger; }

    void info(const char* msg);
    void debug(const char* msg);
    void warn(const char* msg);
    void error(const char* msg);

private:
    void log(const char* msg, LogLevel level);
    std::string getLabel(LogLevel level);

    std::vector<StreamInfo> mStreams;
    static std::shared_ptr<Logger> mCoreLogger;
};
