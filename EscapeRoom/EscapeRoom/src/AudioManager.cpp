#include "AudioManager.hpp"

AudioManager::AudioManager(const std::string& soundEffectPath, const std::string& musicPath)
    : soundEffectPath(soundEffectPath), musicPath(musicPath) {}

AudioManager::~AudioManager() {
}

void AudioManager::playSoundEffect(const std::string& filename) {
    std::string fullPath = soundEffectPath + filename;
    if (soundBuffers.find(fullPath) == soundBuffers.end()) { 
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(fullPath)) {
            throw std::runtime_error("Failed to load sound effect: " + fullPath);
        }
        soundBuffers[fullPath] = buffer;
    }
    sound.setBuffer(soundBuffers[fullPath]);
    sound.play();
}

void AudioManager::playMusic(const std::string& filename, bool loop) {
    std::string fullPath = musicPath + filename;
    if (!music.openFromFile(fullPath)) {
        throw std::runtime_error("Failed to load music: " + fullPath);
    }
    currentMusicFilename = filename; 
    music.setLoop(loop);
    music.play();
}

void AudioManager::stopMusic() {
    fadeOutMusic(1); // Fade out über 2 seconds
}

void AudioManager::pauseMusic() {
    if (music.getStatus() == sf::Music::Playing) {
        fadeOutMusic(2); // Fade out über 2 seconds
        music.pause();
    }
}

void AudioManager::resumeMusic() {
    if (music.getStatus() == sf::Music::Paused) {
        if (!currentMusicFilename.empty() && music.openFromFile(musicPath + currentMusicFilename)) {
            fadeInMusic(currentMusicFilename, music.getLoop(), 1);
        }
        else {
            throw std::runtime_error("Failed to resume music: No music track is loaded or file is missing.");
        }
    }
}

void AudioManager::setMusicVolume(float volume) {
    music.setVolume(volume);
}

void AudioManager::setSoundEffectVolume(float volume) {
    sound.setVolume(volume);
}

void AudioManager::fadeOutMusic(float duration) {
    sf::Clock clock;
    float startVolume = music.getVolume();
    while (clock.getElapsedTime().asSeconds() < duration) {
        float elapsed = clock.getElapsedTime().asSeconds();
        float newVolume = startVolume * (1 - elapsed / duration);
        music.setVolume(newVolume);
    }
    music.setVolume(0);
    music.stop();
}

void AudioManager::fadeInMusic(const std::string& filename, bool loop, float duration) {
    if (!music.openFromFile(musicPath + filename)) {
        throw std::runtime_error("Failed to load music: " + (musicPath + filename));
    }
    music.setVolume(0);
    music.setLoop(loop);
    music.play();

    sf::Clock clock;
    float targetVolume = 100;
    while (clock.getElapsedTime().asSeconds() < duration) {
        float elapsed = clock.getElapsedTime().asSeconds();
        float newVolume = targetVolume * (elapsed / duration);
        music.setVolume(newVolume);
    }
    music.setVolume(targetVolume);
}