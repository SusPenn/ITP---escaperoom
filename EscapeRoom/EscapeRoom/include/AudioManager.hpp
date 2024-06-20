#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class AudioManager {
public:
    static AudioManager& getInstance() {
        static AudioManager instance("assets/sounds/", "assets/music/");
        return instance;
    }

    AudioManager(AudioManager const&) = delete;
    void operator=(AudioManager const&) = delete;

    void playSoundEffect(const string& filename);
    void playMusic(const string& filename, bool loop);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void setMusicVolume(float volume);
    void setSoundEffectVolume(float volume);
    void fadeOutMusic(float duration);
    void fadeInMusic(const string& filename, bool loop, float duration);

private:
    AudioManager(const string& soundEffectPath, const string& musicPath);
    ~AudioManager();

    unordered_map<string, sf::SoundBuffer> soundBuffers;
    sf::Sound sound;
    sf::Music music;
    string soundEffectPath;
    string musicPath;
    string currentMusicFilename;
};

#endif // AUDIOMANAGER_HPP