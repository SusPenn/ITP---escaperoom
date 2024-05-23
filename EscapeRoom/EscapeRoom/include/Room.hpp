#ifndef ROOM_HPP
#define ROOM_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <memory>
#include "AudioManager.hpp"
#include "Game.hpp"
#include "Timer.hpp"

class Game;  // Forward declaration to avoid circular dependency

class Room {
public:
    Room(Game* gameInstance);
    virtual ~Room() = default;
    void enter();
    void exit();
    void handleInput(sf::Event& event, sf::RenderWindow& window);
    virtual void update(float dt);
    void draw(sf::RenderWindow& window);

protected:
    Game* game;

    sf::Texture niceLecturerTexture;
    sf::Texture textfieldTexture;
    sf::Texture madLecturerTexture;
    sf::Texture roomCompletedTexture;
    sf::Texture playerTexture;

    sf::Sprite textfieldSprite;
    sf::Sprite madLecturerSprite;
    sf::Sprite playerSprite;
    sf::Sprite niceLecturerSprite;
    sf::Sprite roomCompletedSprite;
    sf::Sprite background;

    sf::Font font;
    sf::Text questionText;

    std::string riddleText;
    std::string madLecturerText;

    int questionIndex;
    bool displayTextLineByLineActive;
    float displayTextLineByLineTime;
    bool waitingForAnswer;
    std::string currentText;
    int lineCount;
    bool lineDelayActive;
    float lineDelayTime;
    float lineDelayDuration;

    virtual void loadAssets() = 0;
    virtual bool isCorrectAnswer(const sf::Vector2f& pos) = 0;
    virtual bool isWrongAnswer(const sf::Vector2f& pos) = 0;
    virtual void handleCorrectAnswer() = 0;
    virtual void playBackgroundMusic() = 0;
    virtual void setupQuestionText(const std::string& text) = 0;
    void loadTexture(sf::Texture& texture, const std::string& filename, const std::string& name);
    void setupSprites();
    void loadFont(const std::string& fontPath);
    std::string readFile(const std::string& filename);
    void handleMouseClick(sf::RenderWindow& window);
    void handleWrongAnswer();
};

#endif // ROOM_HPP
