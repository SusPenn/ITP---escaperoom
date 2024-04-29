#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <unordered_map>
#include <string>


class AudioManager {
public:
    static AudioManager& getInstance() {
        static AudioManager instance("assets/sounds/", "assets/music/");
        return instance;
    }

    AudioManager(AudioManager const&) = delete;
    void operator=(AudioManager const&) = delete;

    void playSoundEffect(const std::string& filename);
    void playMusic(const std::string& filename, bool loop);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void setMusicVolume(float volume);
    void setSoundEffectVolume(float volume);
    void fadeOutMusic(float duration);
    void fadeInMusic(const std::string& filename, bool loop, float duration);

private:
    AudioManager(const std::string& soundEffectPath, const std::string& musicPath);
    ~AudioManager();

    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    sf::Sound sound;
    sf::Music music;
    std::string soundEffectPath;
    std::string musicPath;
    std::string currentMusicFilename;
};

#endif // AUDIOMANAGER_HPP