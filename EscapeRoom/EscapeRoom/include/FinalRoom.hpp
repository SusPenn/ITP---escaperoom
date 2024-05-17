#ifndef FINALROOM_HPP
#define FINALROOM_HPP

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

class FinalRoom {
public:
    FinalRoom(Game* gameInstance);
    void loadAssets();
    void enter();
    void exit();
    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
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

    void loadTexture(sf::Texture& texture, const std::string& filename, const std::string& name);
    void setupSprites();
    void loadFont(const std::string& fontPath);
    void playBackgroundMusic();
    void setupQuestionText(const std::string& text);
    std::string readFile(const std::string& filename);
    void displayTextLineByLine(const std::string& entireText);
    void waitForAnswer(sf::RenderWindow& window);
    void handleMouseClick(sf::RenderWindow& window);
    bool isCorrectAnswer(const sf::Vector2f& pos);
    bool isWrongAnswer(const sf::Vector2f& pos);
    void handleCorrectAnswer();
    void handleWrongAnswer();
};

#endif // FINALROOM_HPP
