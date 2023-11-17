#ifndef BRACKOCALYPSE_USER_LOGGER_HPP
#define BRACKOCALYPSE_USER_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

// User log levels
#define USER_LOG_LEVEL_NONE 0
#define USER_LOG_LEVEL_ERROR 1
#define USER_LOG_LEVEL_WARNING 2
#define USER_LOG_LEVEL_INFO 3
#define USER_LOG_LEVEL_DEBUG 4

// Default log level
#ifndef USER_CURRENT_LOG_LEVEL
#define USER_CURRENT_LOG_LEVEL USER_LOG_LEVEL_DEBUG
#endif

class UserLogger {
public:
    static void Error(const std::string &message);
    static void Warning(const std::string &message);
    static void Info(const std::string &message);
    static void Debug(const std::string &message);

    void Initialize();
    void Shutdown();
    void SetLogLevel(int level);

    UserLogger(const UserLogger&) = delete;
    UserLogger& operator=(const UserLogger&) = delete;
    static UserLogger& GetInstance();

private:
    UserLogger();
    ~UserLogger();

    void LogError(const std::string &message);
    void LogWarning(const std::string &message);
    void LogInfo(const std::string &message);
    void LogDebug(const std::string &message);
    void Log(const std::string &level, const std::string &message);
    void ProcessLogQueue();

#ifdef USER_LOG_TO_FILE
    std::ofstream logFile;
    std::mutex fileMutex;
    void OpenLogFile(const std::string& filename);
#endif

    std::vector<std::string> log_queue_;
    std::mutex queue_mutex_;
    std::condition_variable condition_;
    std::thread logging_thread_;
    bool shutdown_ = false;

    void CreateDirectories(const std::string &dir);

    void CheckAndCleanOldLogs();
};

#endif // BRACKOCALYPSE_USER_LOGGER_HPP
