#include "LoggerManager.h"

#include <iostream>

#include "Utils.h"

namespace Satellite
{
    void LoggerManager::Log(const std::string& message)
    {
        const std::string date = Utils::CurrentDateTimeToString();
        std::cout << "LOG - " << date << " - " << message << std::endl;
    }

    void LoggerManager::Warning(const std::string& message)
    {
        const std::string date = Utils::CurrentDateTimeToString();
        std::cout << "WARNING - " << date << " - " << message << std::endl;
    }

    void LoggerManager::Error(const std::string& message)
    {
        const std::string date = Utils::CurrentDateTimeToString();
        std::cout << "ERROR - " << date << " - " << message << std::endl;
    }

    void LoggerManager::Error(const std::string& message, const char* error)
    {
        const std::string date = Utils::CurrentDateTimeToString();
        std::cout << "ERROR - " << date << " - " << message << ": " << error << std::endl;
    }
}