// Intro.hpp
#ifndef INTRO_HPP
#define INTRO_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include "Button.hpp"
#include "Game.hpp"

using namespace std;

class Game;

class Intro {
public:
    Intro(Game* gameInstance);
    void enter();
    void exit();
    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    Game* game;
    string filename;
    sf::Font font;
    Button skipButton;
    Button losButton;
    string entireText;
    sf::Text introText;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    bool losButtonActive;

    string displayedText;
    size_t currentIndex;
    float displayTextLineByLineTime;
    int lineCount;
    bool lineDelayActive;
    float lineDelayTime;
    const float lineDelayDuration;

    void loadAssets();
    void displayText(float dt);
};

#endif // INTRO_HPP