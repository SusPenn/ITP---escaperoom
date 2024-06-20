#include "AudioManager.hpp"
#include <SFML/Audio.hpp>

AudioManager::AudioManager(const string& soundEffectPath, const string& musicPath)
    : soundEffectPath(soundEffectPath), musicPath(musicPath) {}

AudioManager::~AudioManager() {
    // Stop any playing music to clean up resources
    music.stop();
}

void AudioManager::playSoundEffect(const string& filename) {
    string fullPath = soundEffectPath + filename;
    if (soundBuffers.find(fullPath) == soundBuffers.end()) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(fullPath)) {
            cerr << "Failed to load sound effect: " << fullPath << endl;
            return;
        }
        soundBuffers[fullPath] = buffer;
    }
    sound.setBuffer(soundBuffers[fullPath]);
    sound.play();
}

void AudioManager::playMusic(const string& filename, bool loop) {
    // Stop any currently playing music first
    if (music.getStatus() != sf::Music::Stopped) {
        music.stop();
    }

    string fullPath = musicPath + filename;
    if (!music.openFromFile(fullPath)) {
        cerr << "Failed to load music: " << fullPath << endl;
        return;
    }

    currentMusicFilename = filename;
    music.setLoop(loop);
    music.play();
}

void AudioManager::stopMusic() {
    fadeOutMusic(1); // Fade out over 1 second
}

void AudioManager::pauseMusic() {
    if (music.getStatus() == sf::Music::Playing) {
        fadeOutMusic(2); // Optionally fade out over 2 seconds before pausing
        music.pause();
    }
}

void AudioManager::resumeMusic() {
    if (music.getStatus() == sf::Music::Paused) {
        if (!currentMusicFilename.empty() && music.openFromFile(musicPath + currentMusicFilename)) {
            fadeInMusic(currentMusicFilename, music.getLoop(), 1); // Fade in over 1 second
        }
        else {
            cerr << "Failed to resume music: No music track is loaded or file is missing." << endl;
        }
    }
}

void AudioManager::setMusicVolume(float volume) {
    // Clamp the volume between 0 and 100
    volume = max(0.0f, min(100.0f, volume));
    music.setVolume(volume);
}

void AudioManager::setSoundEffectVolume(float volume) {
    // Clamp the volume between 0 and 100
    volume = max(0.0f, min(100.0f, volume));
    sound.setVolume(volume);
}

void AudioManager::fadeOutMusic(float duration) {
    float startVolume = music.getVolume();
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < duration) {
        float elapsed = clock.getElapsedTime().asSeconds();
        float newVolume = max(0.0f, startVolume * (1 - elapsed / duration));
        music.setVolume(newVolume);
        sf::sleep(sf::milliseconds(10));
    }
    music.setVolume(0);
    music.stop();
}

void AudioManager::fadeInMusic(const string& filename, bool loop, float duration) {
    if (!music.openFromFile(musicPath + filename)) {
        cerr << "Failed to load music: " << (musicPath + filename) << endl;
        return;
    }

    music.setVolume(0);
    music.setLoop(loop);
    music.play();

    float targetVolume = 100;
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < duration) {
        float elapsed = clock.getElapsedTime().asSeconds();
        float newVolume = targetVolume * (elapsed / duration);
        music.setVolume(newVolume);
        sf::sleep(sf::milliseconds(10));
    }
    music.setVolume(targetVolume);
}