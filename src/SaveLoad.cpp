#include "../outfacingInterfaces/SaveLoad.hpp"
#include "Logger.hpp"
#include "Systems/ReplaySystem.hpp"

SaveLoad SaveLoad::instance;

void SaveLoad::save(const std::string &filePath, const std::string &content) const {
    std::ofstream file(filePath, std::ios::binary);

    // Check if the file can be opened for writing
    if (!file.is_open()) {
        std::cerr << "Unable to open file for writing: " << filePath << std::endl;
        return;
    }

    // Write the size of the string first
    size_t size = content.size();
    if (!file.write(reinterpret_cast<const char *>(&size), sizeof(size_t))) {
        std::cerr << "Error writing size to file: " << filePath << std::endl;
        file.close(); // Close the file before returning
        return;
    }

    // Write the content of the string
    if (!file.write(content.c_str(), size)) {
        std::cerr << "Error writing content to file: " << filePath << std::endl;
    }

    file.close();
}

std::string SaveLoad::load(const std::string &filePath) const {
    std::ifstream file(filePath, std::ios::binary);

    // Check if the file can be opened for reading
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading: " << filePath << std::endl;
        return "";
    }

    // Read the size of the string first
    size_t size;
    if (!file.read(reinterpret_cast<char *>(&size), sizeof(size_t))) {
        std::cerr << "Error reading size from file: " << filePath << std::endl;
        return "";
    }

    // Read the content of the string
    std::string content(size, '\0');
    if (!file.read(&content[0], size)) {
        std::cerr << "Error reading content from file: " << filePath << std::endl;
    }

    file.close();
    return content;
}