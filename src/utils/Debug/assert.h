// assert.h
#pragma once
// #include section
// #################
// Standard library includes
#include <cassert>
// Third-party library includes

// Raven includes
#include "Logger.h"

#define ASSERT(condition, message) \
    if (!(condition)) { \
        Logger::Log(message, LogLevel::Error); \
        assert(condition); \
    }
