#ifndef OUTRO_HPP
#define OUTRO_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "AudioManager.hpp"
#include "Button.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

class Outro {
public:
    Outro(const std::string& filename, sf::RenderWindow& window); // Konstruktor
    void play();
    void playSuccessMusic();
    static void sleepMilliseconds(int milliseconds);
    void loadNewImage();

private:
    std::string filename;
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture girlTexture;
    sf::Sprite girlSprite;
    sf::Texture boyTexture;
    sf::Sprite boySprite;
    sf::Texture spritzerStandTexture;
    sf::Sprite spritzerStandSprite;
    sf::RectangleShape linkArea;
    void printSlowly(const std::string& text, int delay, sf::Text& outroText, sf::Sprite& backgroundSprite, sf::RenderWindow& window);
    bool isSkipClicked(sf::Event& event);
    bool isSkipButtonClicked(sf::Vector2f clickPosition);
    bool skipRequested = false;
    bool displayOverlay;
    bool linkVisible = false;
    bool isLinkClicked(sf::Vector2f clickPosition);

    class SkipButton {
    public:
        SkipButton(sf::RenderWindow& window, sf::Font& font);
        void draw();
        void setPosition(sf::RenderWindow& window);
        bool isClicked(sf::Vector2f clickPosition);
        void setVisible(bool isVisible);

    private:
        sf::RenderWindow& window;
        sf::RectangleShape buttonShape;
        sf::Text buttonText;
        bool visible = true; // Standardm‰ﬂig sichtbar
    };

    SkipButton skipButton;
};

#endif // OUTRO_HPP
