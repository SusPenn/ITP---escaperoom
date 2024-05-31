#ifndef OUTRO_HPP
#define OUTRO_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "AudioManager.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

class Game;

class Outro {
public:
    Outro(Game* gameInstance);
    void enter();
    void exit();
    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void play(Game& game);

private:
    Game* game;
    Button skipButton;
    Button returnToMainMenuButton;
    Button doorButton;
    sf::Font font;
    sf::Text outroText;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture spritzerStandTexture;
    sf::Sprite spritzerStandSprite;
    sf::RectangleShape overlay;

    string entireText;
    string displayedText;
    size_t currentIndex;
    bool outroTextFinished;
    float lineDelayTime;
    int lineCount;
    const float lineDelayDuration;
    float displayTextLineByLineTime;
    bool lineDelayActive;

    void loadAssets();
    void loadTexture(sf::Texture& texture, const string& filename, const string& name);
    void setupSprites();
    void loadFont(const string& fontPath);
    string readFile(const string& filename);
    void setupOutroText();
    void displayText(float dt);
    void displayTextFinished();

    void printSlowly(const string& text, int delay, sf::Text& outroText, sf::Sprite& backgroundSprite, sf::RenderWindow& window);

    bool skipRequested = false;
    bool displayOverlay;
    bool isLinkClicked(sf::Vector2f clickPosition);
    void toTheSpritzer();
};

#endif // OUTRO_HPP
