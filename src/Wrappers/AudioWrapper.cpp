//
// Created by jesse on 31/10/2023.
//


#include <algorithm>
#include "AudioWrapper.hpp"



AudioWrapper::AudioWrapper() : system(nullptr) {
    FMOD_RESULT result = FMOD::System_Create(&system);
    if (result != FMOD_OK) {
        Logger::Error("FMOD system creation failed: " + std::string(FMOD_ErrorString(result)));
    } else {
        result = system->init(32, FMOD_INIT_NORMAL, nullptr); // Use system->init
        if (result != FMOD_OK) {
            Logger::Error("FMOD system initialization failed: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

AudioWrapper::~AudioWrapper() {
    if (system) {
        FMOD_RESULT result = system->release();
        if (result != FMOD_OK) {
            Logger::Error("Failed to release FMOD system: " + std::string(FMOD_ErrorString(result)));
        }
    }
}

void AudioWrapper::CleanUp() {
    if (system) {
        FMOD_RESULT result = system->release();
        if (result != FMOD_OK) {
            Logger::Error("Failed to release FMOD system: " + std::string(FMOD_ErrorString(result)));
        }
        system = nullptr;
    }
}

int AudioWrapper::FindAvailableSFXChannel() {
    ClearUnusedChannels();

    int availableSFXChannels = ConfigSingleton::GetInstance().getAmountOfSFXChannels();

    if (availableSFXChannels <= 0) {
        Logger::Error("Invalid SFX channel count.");
        return -1;
    }

    for (int i = 0; i < availableSFXChannels; ++i) {
        if (soundEffectsChannelMap.find(i) == soundEffectsChannelMap.end()) {
            return i;
        }
    }
    return -1; // No available channel found
}

void AudioWrapper::ClearUnusedChannels() {
    std::vector<int> channelsToRelease;

    for (auto it = soundEffectsChannelMap.begin(); it != soundEffectsChannelMap.end();) {
        FMOD::Channel* channel = it->second;
        bool isPlaying; // Declaration without initialization

        // Checking if the channel is playing
        if (channel) {
            FMOD_RESULT result = channel->isPlaying(&isPlaying);
            if (result != FMOD_OK) {
                Logger::Error("Error checking if channel is playing: " + std::string(FMOD_ErrorString(result)));
                ++it;
                continue;
            }

            Logger::Debug("Channel ID: " + std::to_string(it->first) + ", Is playing: " + (isPlaying ? "true" : "false"));

            if (!isPlaying) {
                channelsToRelease.push_back(it->first); // Marking channel for release
                it = soundEffectsChannelMap.erase(it); // Erasing channel from map
            } else {
                ++it; // Move to the next channel
            }
        } else {
            Logger::Debug("Invalid channel found and removed.");
            it = soundEffectsChannelMap.erase(it); // Erase invalid channel from the map
        }
    }
}

void AudioWrapper::PlaySound(AudioArchetype &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    if (!IsValidAudioPath(audioComponent)) {
        Logger::Error("Invalid audio file path.");
        return;
    }

    int availableSFXChannels = ConfigSingleton::GetInstance().getAmountOfSFXChannels();

    if (availableSFXChannels <= 0) {
        Logger::Error("No available SFX channels.");
        return;
    }

    if (audioComponent.getIsSoundTrack()) {
        soundTrackChannelPair.first = soundTrackChannel; // Set the channel ID
        soundTrackChannelPair.second->setVolume(audioComponent.volume); // Set volume

        FMOD::Sound* sound = nullptr;
        FMOD_MODE mode = audioComponent.getIsSoundTrack() ? FMOD_LOOP_NORMAL : FMOD_DEFAULT; // Set looping for SoundTrack

        FMOD_RESULT result = system->createSound(audioComponent.getAudioPath().c_str(), mode, 0, &sound);

        if (result != FMOD_OK) {
            Logger::Error("Failed to create sound: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        result = system->playSound(sound, nullptr, false, &soundTrackChannelPair.second);

        if (result != FMOD_OK) {
            Logger::Error("Failed to play sound on SoundTrack channel: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        Logger::Debug("Uploaded sound to Soundtrack Channel: " + std::to_string(soundTrackChannelPair.first) + ", Path: " + audioComponent.getAudioPath());
    } else { // SoundEffect
        // Find an available SFX channel to play the sound
        int channelID = FindAvailableSFXChannel();

        if (channelID == -1) {
            Logger::Debug("All SFX channels are currently in use.");
            return;
        }

        FMOD::Sound* sound = nullptr;
        FMOD_RESULT result = system->createSound(audioComponent.getAudioPath().c_str(), FMOD_DEFAULT, 0, &sound);

        if (result != FMOD_OK) {
            Logger::Error("Failed to create sound: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        // Play the sound on the available SFX channel
        FMOD::Channel* channel = nullptr;
        result = system->playSound(sound, nullptr, false, &channel);

        if (result != FMOD_OK) {
            Logger::Error("Failed to play sound on SFX channel: " + std::string(FMOD_ErrorString(result)));
            return;
        }

        // Set the channel's ID and volume
        channel->setUserData(reinterpret_cast<void*>(channelID));
        channel->setVolume(audioComponent.volume);

        // Add the channel to the map
        soundEffectsChannelMap[channelID] = channel;

        Logger::Debug("Uploaded sound to Channel: " + std::to_string(channelID) + ", Path: " + audioComponent.getAudioPath());
    }
}

void AudioWrapper::PauseSound(AudioArchetype &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    if(!audioComponent.getIsSoundTrack()){
        for (auto it = soundEffectsChannelMap.begin(); it != soundEffectsChannelMap.end(); ++it) {
            FMOD::Channel* channel = it->second;
            if (channel) {
                FMOD::Sound* sound = nullptr;
                FMOD_RESULT result = channel->getCurrentSound(&sound);
                if (result != FMOD_OK) {
                    Logger::Error("Error getting current sound: " + std::string(FMOD_ErrorString(result)));
                    continue;
                }
                char audioPath[256];
                result = sound->getName(audioPath, sizeof(audioPath));
                if (result != FMOD_OK) {
                    Logger::Error("Error getting sound name: " + std::string(FMOD_ErrorString(result)));
                    continue;
                }

                if (std::string(audioPath) == getFileName(audioComponent.getAudioPath())) {
                    result = channel->setPaused(true);
                    if (result != FMOD_OK) {
                        Logger::Error("Error pausing channel: " + std::string(FMOD_ErrorString(result)));
                    }
                }
            }
        }
    }
    else {
        FMOD::Channel* channel = soundTrackChannelPair.second;
        if (channel) {
            FMOD::Sound* sound = nullptr;
            FMOD_RESULT result = channel->getCurrentSound(&sound);
            if (result != FMOD_OK) {
                Logger::Error("Error getting current sound: " + std::string(FMOD_ErrorString(result)));
                return;
            }

            char audioPath[256];
            result = sound->getName(audioPath, sizeof(audioPath));
            if (result != FMOD_OK) {
                Logger::Error("Error getting sound name: " + std::string(FMOD_ErrorString(result)));
                return;
            }

            if (std::string(audioPath) == getFileName(audioComponent.getAudioPath())) {
                result = channel->setPaused(true);
                if (result != FMOD_OK) {
                    Logger::Error("Error pausing channel: " + std::string(FMOD_ErrorString(result)));
                }
            }
        }
    }
}

void AudioWrapper::ResumeSound(AudioArchetype &audioComponent) {
    if (!system) {
        Logger::Error("FMOD audio system is not initialized.");
        return;
    }

    bool anySoundsPaused = false;
    for (auto it = soundEffectsChannelMap.begin(); it != soundEffectsChannelMap.end(); ++it) {
        FMOD::Channel* channel = it->second;
        if (channel) {
            bool isPlaying;
            FMOD_RESULT result = channel->isPlaying(&isPlaying);
            if (result != FMOD_OK) {
                Logger::Error("Error checking if channel is playing: " + std::string(FMOD_ErrorString(result)));
                continue;
            }
            if (!isPlaying) {
                anySoundsPaused = true;
                Logger::Debug("Paused Sound Found");
                break; // Exit the loop as soon as a paused sound is found
            }
        }
    }

    if (!anySoundsPaused) {
        return;
    }

    if (!audioComponent.getIsSoundTrack()) {
        for (auto it = soundEffectsChannelMap.begin(); it != soundEffectsChannelMap.end(); ++it) {
            FMOD::Channel* channel = it->second;
            if (channel) {
                FMOD::Sound* sound = nullptr;
                FMOD_RESULT result = channel->getCurrentSound(&sound);
                if (result != FMOD_OK) {
                    Logger::Error("Error getting current sound: " + std::string(FMOD_ErrorString(result)));
                    continue;
                }

                char audioPath[256];
                result = sound->getName(audioPath, sizeof(audioPath));
                if (result != FMOD_OK) {
                    Logger::Error("Error getting sound name: " + std::string(FMOD_ErrorString(result)));
                    continue;
                }

                if (std::string(audioPath) == getFileName(audioComponent.getAudioPath())) {
                    bool isPaused;
                    result = channel->getPaused(&isPaused);
                    if (result != FMOD_OK) {
                        Logger::Error("Error checking if channel is paused: " + std::string(FMOD_ErrorString(result)));
                        continue;
                    }

                    if (isPaused) {
                        result = channel->setPaused(false); // Resume the channel
                        if (result != FMOD_OK) {
                            Logger::Error("Error resuming channel: " + std::string(FMOD_ErrorString(result)));
                        }
                    }
                }
            }
        }
    } else {
        FMOD::Channel* channel = soundTrackChannelPair.second;
        if (channel) {
            FMOD::Sound* sound = nullptr;
            FMOD_RESULT result = channel->getCurrentSound(&sound);
            if (result != FMOD_OK) {
                Logger::Error("Error getting current sound: " + std::string(FMOD_ErrorString(result)));
                return;
            }

            char audioPath[256];
            result = sound->getName(audioPath, sizeof(audioPath));
            if (result != FMOD_OK) {
                Logger::Error("Error getting sound name: " + std::string(FMOD_ErrorString(result)));
                return;
            }

            if (std::string(audioPath) == getFileName(audioComponent.getAudioPath())) {
                bool isPaused;
                result = channel->getPaused(&isPaused);
                if (result != FMOD_OK) {
                    Logger::Error("Error checking if channel is paused: " + std::string(FMOD_ErrorString(result)));
                    return;
                }

                if (isPaused) {
                    result = channel->setPaused(false); // Resume the channel
                    if (result != FMOD_OK) {
                        Logger::Error("Error resuming channel: " + std::string(FMOD_ErrorString(result)));
                    }
                }
            }
        }
    }
}

bool AudioWrapper::IsValidAudioPath(const AudioArchetype& audioComponent){
    std::ifstream file(audioComponent.getAudioPath());

    if (!file.good()) {
        Logger::Error("Audio file not found at path: " + audioComponent.getAudioPath());
        return false;
    }

    // Extract the file extension
    size_t dotIndex = audioComponent.getAudioPath().find_last_of('.');
    if (dotIndex == std::string::npos) {
        Logger::Error("Invalid audio file path (no file extension): " + audioComponent.getAudioPath());
        return false;
    }

    std::string extension = audioComponent.getAudioPath().substr(dotIndex + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // List of common audio file extensions
    const std::vector<std::string> audioExtensions = {"mp3", "wav", "ogg", "flac", "aac", "m4a"};

    // Check if the extension is in the list of common audio file extensions
    if (std::find(audioExtensions.begin(), audioExtensions.end(), extension) == audioExtensions.end()) {
        Logger::Error("Invalid audio file extension at path: " + audioComponent.getAudioPath());
        return false;
    }

    return true;
}

std::string AudioWrapper::getFileName(const std::string& audioPath) {
    size_t lastSlash = audioPath.find_last_of("/\\");
    std::string fileName = audioPath.substr(lastSlash + 1);

    return fileName;
}