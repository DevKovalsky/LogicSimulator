#include "Logger.h"

Logger::Logger(bool coutStream)
{
    std::cout << "Logger konstruktor" << std::endl;
    if(coutStream)
        addStream(std::wcout, LogLevel::INFO);
}

Logger::~Logger()
{
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
        *(ptrStream) << msg;
        *(ptrStream) << "\n";
    }
}

void Logger::addStream(std::wostream& s, LogLevel level)
{
    StreamInfo sInfo(s, level);
    mStreams.emplace_back(sInfo);
}
