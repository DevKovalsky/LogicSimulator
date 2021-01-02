#include "Logger.h"

std::shared_ptr<Logger> Logger::mCoreLogger;

std::map<LogLevel, std::string> logLevelsToNames
{
    {LogLevel::INFO, "[INFO]"},
    {LogLevel::DEBUG, "[DEBUG]"},
    {LogLevel::WARNING, "[WARNING]"},
    {LogLevel::ERROR, "[ERROR]"},
};

Logger::Logger()
{
    std::cout << "Logger konstruktor" << std::endl;
}

Logger::~Logger()
{
}

void Logger::init()
{
    //set pattern
    mCoreLogger = std::make_shared<Logger>();
}

void Logger::log(const char* msg, LogLevel level)
{
    for(auto& stream : mStreams)
    {
        if(level < stream.level)
        {
            continue;
        }

        auto ptrStream = stream.stream;
        *(ptrStream) << logLevelsToNames[level].c_str();
        *(ptrStream) << " ";
        *(ptrStream) << msg;
        *(ptrStream) << "\n";
    }
}

void Logger::addStream(std::wostream& s, LogLevel level)
{
    StreamInfo sInfo(s, level);
    mStreams.emplace_back(sInfo);
}

void Logger::info(const char* msg)
{
    log(msg, LogLevel::INFO);
}

void Logger::debug(const char* msg)
{
    log(msg, LogLevel::DEBUG);
}

void Logger::warn(const char* msg)
{
    log(msg, LogLevel::WARNING);
}

void Logger::error(const char* msg)
{
    log(msg, LogLevel::ERROR);
}
