// Logger.cpp

#include "Logger.hpp"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <chrono>

// Current log level
#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

Logger::Logger() {
#ifdef LOG_TO_FILE
    // Get the current time
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert the current time to tm struct
    std::tm bt{};
#if defined(_MSC_VER)
    localtime_s(&bt, &in_time_t);
#else
    localtime_r(&in_time_t, &bt); // POSIX
#endif

    // Format the current time to YYYYMMDD_HHMMSS (for example, 20231107_153045)
    std::ostringstream timeStream;
    timeStream << std::put_time(&bt, "%Y%m%d_%H%M");

    // Create filename with timestamp prefix
    std::string fileName = timeStream.str() + "_brack_engine.log";
    OpenLogFile(fileName);
    Initialize();
#endif
}

Logger::~Logger() {
#ifdef LOG_TO_FILE
    if (logFile.is_open()) {
        logFile.close();
    }

    Shutdown();
#endif
}

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

#ifdef LOG_TO_FILE
void Logger::OpenLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(fileMutex);
    if (!logFile.is_open()) {
        logFile.open(filename, std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Unable to open log file: " + filename);
        }
    }
}
#endif

// Static methods to check log level and log if appropriate
void Logger::Error(const std::string &message) {
#if CURRENT_LOG_LEVEL >= LOG_LEVEL_ERROR
    GetInstance().LogError(message);
    throw std::runtime_error(message);
#endif
}

void Logger::Warning(const std::string &message) {
#if CURRENT_LOG_LEVEL >= LOG_LEVEL_WARNING
    GetInstance().LogWarning(message);
#endif
}

void Logger::Info(const std::string &message) {
#if CURRENT_LOG_LEVEL >= LOG_LEVEL_INFO
    GetInstance().LogInfo(message);
#endif
}

void Logger::Debug(const std::string &message) {
#if CURRENT_LOG_LEVEL >= LOG_LEVEL_DEBUG
    GetInstance().LogDebug(message);
#endif
}

void Logger::LogError(const std::string &message) {
    Log("ERROR", message);
}

void Logger::LogWarning(const std::string &message) {
    Log("WARNING", message);
}

void Logger::LogInfo(const std::string &message) {
    Log("INFO", message);
}

void Logger::LogDebug(const std::string &message) {
    Log("DEBUG", message);
}

void Logger::Log(const std::string &level, const std::string &message) {
    auto log_entry = level + ": " + message;
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        log_queue_.push_back(log_entry);
    }
    condition_.notify_one();
}

void Logger::ProcessLogQueue() {
    std::vector<std::string> queue_to_write;
    while (true) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            condition_.wait(lock, [this] {
                return !log_queue_.empty() || shutdown_;
            });

            if (shutdown_ && log_queue_.empty()) {
                break;
            }

            queue_to_write.swap(log_queue_);
        }

        for (const auto &entry : queue_to_write) {
#ifdef LOG_TO_FILE
            if (logFile.is_open()) {
                logFile << entry << std::endl;
            }
#endif
            std::cout << entry << std::endl;
        }

        queue_to_write.clear();

#ifdef LOG_TO_FILE
        if (logFile.is_open()) {
            logFile.flush();
        }
#endif
    }
}

void Logger::Initialize() {
    // Start the background thread
    logging_thread_ = std::thread(&Logger::ProcessLogQueue, this);
}

void Logger::Shutdown() {
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        shutdown_ = true;
    }
    condition_.notify_one();
    if (logging_thread_.joinable()) {
        logging_thread_.join();
    }
}
