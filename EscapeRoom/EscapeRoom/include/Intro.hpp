#ifndef INTRO_HPP
#define INTRO_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "AudioManager.hpp"
#include "Button.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

class Game;

using namespace std;

class Intro {
public:
    Intro(const string& filename, sf::RenderWindow& window);
    void play(Game& game);
    static void sleepMilliseconds(int milliseconds);

private:
    string filename;
    sf::RenderWindow& window;
    sf::Font font;
    void printSlowly(const string& text, int delay, sf::Text& introText, sf::Sprite& backgroundSprite, sf::RenderWindow& window);
    void processEvents(sf::RenderWindow& window, bool& skipRequested);
    bool skipRequested = false;
    Game* game;

    Button skipButton;
};

#endif // INTRO_HPP
