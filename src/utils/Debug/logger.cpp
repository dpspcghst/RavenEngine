// logger.cpp

// #include section
// #################
// Standard library includes

// Third-party library includes

// Raven includes
#include "Logger.h"

std::ofstream Logger::outputStream;

void Logger::Init(const std::string& logFile) {
    outputStream.open(logFile, std::ios::out | std::ios::app);
}

void Logger::Log(const std::string& message, LogLevel level) {
    switch (level) {
        case LogLevel::Info:
            outputStream << "[INFO]: ";
            break;
        case LogLevel::Warning:
            outputStream << "[WARNING]: ";
            break;
        case LogLevel::Error:
            outputStream << "[ERROR]: ";
            break;
        case LogLevel::Debug:
            outputStream << "[DEBUG]: ";
            break;
    }
    outputStream << message << std::endl;
}
