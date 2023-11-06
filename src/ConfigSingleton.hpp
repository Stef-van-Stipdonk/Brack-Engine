//
// Created by jesse on 06/11/2023.
//

#ifndef BRACKOCALYPSE_CONFIGSINGLETON_HPP
#define BRACKOCALYPSE_CONFIGSINGLETON_HPP


class ConfigSingleton {
public:
    static ConfigSingleton& GetInstance();
    ConfigSingleton(ConfigSingleton &other) = delete;
    void operator=(const ConfigSingleton &) = delete;
    ConfigSingleton(ConfigSingleton &&other) = delete;
    void operator=(ConfigSingleton &&) = delete;

    void SetIsRunning(bool isRunning);
    bool IsRunning() const;
    void ToggleIsRunning();
private:
    static ConfigSingleton instance;
    ConfigSingleton() = default;
    bool isRunning = true;
};


#endif //BRACKOCALYPSE_CONFIGSINGLETON_HPP
