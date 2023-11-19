//
// Created by Stef van Stipdonk on 13/11/2023.
//

#include "Helpers/UserLogger.hpp"

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <sys/stat.h>
#include <filesystem>
#include <algorithm>
// Logger.cpp

// Current log level
#ifndef USER_CURRENT_LOG_LEVEL
#define USER_CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

UserLogger::UserLogger() {
#ifdef USER_LOG_TO_FILE
    // Get the current time
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert the current time to tm struct
    std::tm bt{};
#if defined(_WIN32)
    localtime_s(&bt, &in_time_t);
#else
    localtime_r(&in_time_t, &bt); // POSIX
#endif
    std::ostringstream timeStream;
    timeStream << std::put_time(&bt, "%Y%m%d_%H%M");

    // Create filename with timestamp prefix
    std::string fileName = "logging/game/" + timeStream.str() + "_game.log";

    // Create directories if they don't exist
    CreateDirectories("logging/game");

    OpenLogFile(fileName);
    Initialize();
#endif
}

void UserLogger::CheckAndCleanOldLogs() {
    const std::string logDir = "logging/game/";
    const size_t maxLogFiles = 10;

    std::vector<std::filesystem::directory_entry> logFiles;

    // Gather list of log files
    for (const auto& entry : std::filesystem::directory_iterator(logDir)) {
        if (entry.is_regular_file()) {
            logFiles.push_back(entry);
        }
    }

    // Sort files by last write time in descending order (newest first)
    std::sort(logFiles.begin(), logFiles.end(),
              [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
                  return std::filesystem::last_write_time(a) > std::filesystem::last_write_time(b);
              });

    // Delete all files except the newest 10
    if (logFiles.size() > maxLogFiles) {
        for (auto it = logFiles.begin() + maxLogFiles; it != logFiles.end(); ++it) {
            std::cout << "Deleting log file: " << it->path() << std::endl;
            std::filesystem::remove(it->path());
        }
    }
}


void UserLogger::CreateDirectories(const std::string& dir) {
#if defined(_WIN32)
    std::string command = "mkdir " + dir;
    system(command.c_str());
#else
    std::istringstream iss(dir);
    std::string token;
    std::string currentDir;

    while (std::getline(iss, token, '/')) {
        if (token.empty()) continue;  // Skip leading '/' in absolute paths
        currentDir += token + "/";
        if (mkdir(currentDir.c_str(), 0777) != 0 && errno != EEXIST) {
            throw std::runtime_error("Failed to create directory: " + currentDir);
        }
    }
#endif
}

UserLogger::~UserLogger() {
#ifdef USER_LOG_TO_FILE
    if (logFile.is_open()) {
        logFile.close();
    }

    Shutdown();
#endif
}

UserLogger &UserLogger::GetInstance() {
    static UserLogger instance;
    return instance;
}

#ifdef USER_LOG_TO_FILE

void UserLogger::OpenLogFile(const std::string &filename) {
    std::lock_guard<std::mutex> lock(fileMutex);
    if (!logFile.is_open()) {
        CheckAndCleanOldLogs();
        logFile.open(filename, std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Unable to open log file: " + filename);
        }
    }
}

#endif

// Static methods to check log level and log if appropriate
void UserLogger::Error(const std::string &message) {
#if USER_CURRENT_LOG_LEVEL >=  USER_LOG_LEVEL_ERROR
    GetInstance().LogError(message);
    throw std::runtime_error(message);
#endif
}

void UserLogger::Warning(const std::string &message) {
#if USER_CURRENT_LOG_LEVEL >= USER_LOG_LEVEL_WARNING
    GetInstance().LogWarning(message);
#endif
}

void UserLogger::Info(const std::string &message) {
#if USER_CURRENT_LOG_LEVEL >= USER_LOG_LEVEL_INFO
    GetInstance().LogInfo(message);
#endif
}

void UserLogger::Debug(const std::string &message) {
#if USER_CURRENT_LOG_LEVEL >= USER_LOG_LEVEL_DEBUG
    GetInstance().LogDebug(message);
#endif
}

void UserLogger::LogError(const std::string &message) {
    Log("ERROR", message);
}

void UserLogger::LogWarning(const std::string &message) {
    Log("WARNING", message);
}

void UserLogger::LogInfo(const std::string &message) {
    Log("INFO", message);
}

void UserLogger::LogDebug(const std::string &message) {
    Log("DEBUG", message);
}

void UserLogger::Log(const std::string &level, const std::string &message) {
    auto log_entry = level + ": " + message;
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        log_queue_.push_back(log_entry);
    }
    condition_.notify_one();
}

void UserLogger::ProcessLogQueue() {
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

        for (const auto &entry: queue_to_write) {
#ifdef USER_LOG_TO_FILE
            if (logFile.is_open()) {
                logFile << entry << std::endl;
            }
#endif
            std::cout << entry << std::endl;
        }

        queue_to_write.clear();

#ifdef USER_LOG_TO_FILE
        if (logFile.is_open()) {
            logFile.flush();
        }
#endif
    }
}

void UserLogger::Initialize() {
    // Start the background thread
    logging_thread_ = std::thread(&UserLogger::ProcessLogQueue, this);
}

void UserLogger::Shutdown() {
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        shutdown_ = true;
    }
    condition_.notify_one();
    if (logging_thread_.joinable()) {
        logging_thread_.join();
    }
}
