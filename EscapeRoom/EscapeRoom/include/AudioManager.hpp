#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <unordered_map>
#include <string>


class AudioManager {
    public:
        AudioManager(const std::string& soundEffectPath, const std::string& musicPath);
        ~AudioManager();
        void playSoundEffect(const std::string& filename); // Sound-Effekt abspielen
        void playMusic(const std::string& filename, bool loop); // Musik abspielen
        void stopMusic();  // Musik stoppen
        void pauseMusic(); // Musik pausieren
        void resumeMusic(); // Pausierte Musik fortsetzen
        void setMusicVolume(float volume); // Lautstärke der Musik einstellen
        void setSoundEffectVolume(float volume); // Lautstärke der Sound-Effekte einstellen
        void fadeOutMusic(float duration); // Musik fade-out
        void fadeInMusic(const std::string& filename, bool loop, float duration); // Musik fade-in

    private:
        std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
        sf::Sound sound;
        sf::Music music;
        std::string soundEffectPath;  
        std::string musicPath;
        std::string currentMusicFilename;
};

#endif // AUDIOMANAGER_HPP