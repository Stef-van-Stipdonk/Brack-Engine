#ifndef BRACKOCALYPSE_SAVELOAD_HPP
#define BRACKOCALYPSE_SAVELOAD_HPP

#include <string>

class SaveLoad {
public:
    ~SaveLoad() = default;
    SaveLoad(const SaveLoad &) = delete;
    SaveLoad &operator=(const SaveLoad &) = delete;
    SaveLoad(SaveLoad &&) = delete;
    SaveLoad &operator=(SaveLoad &&) = delete;

    static SaveLoad &getInstance() {
        return instance;
    }

    void save(const std::string &filePath, const std::string &content) const;
    std::string load(const std::string &filePath) const;
private:
    SaveLoad() = default;
    static SaveLoad instance;
    static const std::string defaultPath;
};

#endif //BRACKOCALYPSE_SAVELOAD_HPP
