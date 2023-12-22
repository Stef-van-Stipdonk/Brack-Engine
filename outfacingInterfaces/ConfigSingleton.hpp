//
// Created by jesse on 06/11/2023.
//

#ifndef BRACKOCALYPSE_CONFIGSINGLETON_HPP
#define BRACKOCALYPSE_CONFIGSINGLETON_HPP


#include <string>
#include <Helpers/Vector2.hpp>
#include <Config.hpp>

class ConfigSingleton {
public:
    static ConfigSingleton &getInstance();

    ConfigSingleton(ConfigSingleton &other) = delete;

    void operator=(const ConfigSingleton &) = delete;

    ConfigSingleton(ConfigSingleton &&other) = delete;

    void operator=(ConfigSingleton &&) = delete;

    void setConfig(Config config);

    void setIsRunning(bool isRunning);

    bool isRunning() const;

    bool showFps() const;

    void toggleShowFps();

    std::string getWindowTitle() const;

    Vector2 getWindowSize() const;

    Vector2 getInitialWindowSize() const;

    Vector2 getWindowChangeFactor() const;

    float getAspectRatio() const;

    void setWindowSize(Vector2 size);

    bool isFullscreen() const;

    int getParticleLimit() const;

    std::string getBaseAssetPath() const;

    int getAmountOfSoundEffectsChannels() const;

    uint32_t getFPSLimit() const;

    void setFPSLimit(uint32_t fpsLimit);

    void toggleIsRunning();

    void toggleFullScreen();

    void setDeltaTimeMultiplier(float deltaTimeMultiplier);

    float deltaTimeMultiplier = 1;

    std::string getAppLogoPath() const;

private:
    static ConfigSingleton instance;

    ConfigSingleton() = default;

    bool isRunning_ = true;
    std::string windowTitle = "Brack-Engine";
    Vector2 windowSize = Vector2(0, 0);
    Vector2 initialWindowSize = Vector2(1280, 720);
    bool fullscreen = false;
    std::string BaseAssetPath = "./Assets/";
    std::string appLogoPath = "Resources/BrackEngineLogo.png";
    bool showFPS_ = true;
    int amountOfSoundEffectsChannels = 7;
    uint32_t fpsLimit = 60;
    int particleLimit = 100;
};


#endif //BRACKOCALYPSE_CONFIGSINGLETON_HPP
