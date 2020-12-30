#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

#define LOGINFO(logObj, msg) logObj.log(msg, LogLevel::INFO);
#define LOGDEBUG(logObj, msg) logObj.log(msg, LogLevel::DEBUG);
#define LOGWARNING(logObj, msg) logObj.log(msg, LogLevel::WARNING);
#define LOGERROR(logObj, msg) logObj.log(msg, LogLevel::ERROR);

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
    Logger(LogLevel lvl);
    ~Logger();

    void log(const char* msg, LogLevel level);

    void addStream(std::wostream& s, LogLevel level);


private:
    LogLevel mLevel;
    std::vector<StreamInfo> mStreams;
};
