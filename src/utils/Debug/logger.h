// logger.h
#pragma once
// #include section
// #################
// Standard library includes
#include <string>
#include <iostream>
#include <fstream>
// Third-party library includes

// Raven includes

enum class LogLevel {
    Info,
    Warning,
    Error,
    Debug
};

class Logger {
public:
    static void Init(const std::string& logFile);
    static void Log(const std::string& message, LogLevel level);

private:
    static std::ofstream outputStream;
};