// Logger.hpp

#ifndef BRACKOCALYPSE_LOGGER_HPP
#define BRACKOCALYPSE_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <condition_variable>
#include <thread>
#include <chrono>

// Log levels definitions
#define LOG_LEVEL_NONE 0
#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_INFO 3
#define LOG_LEVEL_DEBUG 4

// If CURRENT_LOG_LEVEL is not defined elsewhere, set it to the most verbose level
#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

class Logger {
public:
    // Public interface for logging
    static void Error(const std::string &message);
    static void Warning(const std::string &message);
    static void Info(const std::string &message);
    static void Debug(const std::string &message);

    void Initialize();

    void Shutdown();

    // Deleted copy constructor and assignment operator for singleton
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

// Static method to get the singleton instance
static Logger& GetInstance();

private:
    // Private constructor and destructor
    Logger();
    ~Logger();

    // Instance methods to perform the actual logging
    void LogError(const std::string &message);
    void LogWarning(const std::string &message);
    void LogInfo(const std::string &message);
    void LogDebug(const std::string &message);
    void Log(const std::string &level, const std::string &message);

    void ProcessLogQueue();

#ifdef LOG_TO_FILE
    std::ofstream logFile;
    std::mutex fileMutex;
    void OpenLogFile(const std::string& filename);
#endif

    std::vector<std::string> log_queue_;
    std::mutex queue_mutex_;
    std::condition_variable condition_;
    std::thread logging_thread_;
    bool shutdown_ = false;
};
#endif // BRACKOCALYPSE_LOGGER_HPP
