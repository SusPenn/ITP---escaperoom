#ifndef INTRO_HPP
#define INTRO_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "AudioManager.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

class Intro {
public:
    Intro(const std::string& filename, sf::RenderWindow& window);
    void play();
    static void sleepMilliseconds(int milliseconds);

private:
    std::string filename;
    sf::RenderWindow& window;
    sf::Font font;
    bool printSlowly(const std::string& text, int delay, sf::Text& introText, sf::Sprite& backgroundSprite, sf::RenderWindow& window);
    bool isSkipClicked(sf::Event& event);
    bool isSkipButtonClicked(sf::Vector2f clickPosition);
    bool skipRequested = false;

    class SkipButton {
    public:
        SkipButton(sf::RenderWindow& window, sf::Font& font);
        void draw();
        void setPosition(sf::RenderWindow& window);
        bool isClicked(sf::Vector2f clickPosition);

    private:
        sf::RenderWindow& window;
        sf::RectangleShape buttonShape;
        sf::Text buttonText;
    };

    SkipButton skipButton;
};

#endif // INTRO_HPP
