#ifndef ESCAPEROOM_SETHIGHSCORE_HPP
#define ESCAPEROOM_SETHIGHSCORE_HPP

#include <SFML/Graphics.hpp>
#include "AudioManager.hpp"
#include "Button.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


class Game;

using namespace std;

class SetHighscore {
public:
    SetHighscore();
    void handleInput(sf::Event& event, sf::RenderWindow& window, Game& game);
    void addHighscore();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    static void setScore(int newScore);
    int getScore();

private:
    static int score;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Button returnToHighscoreButton;
    sf::Font font;
    sf::String playerInput;
    sf::Text playerText;
    sf::Text headlineText;
    sf::Text yourScore;
};

#endif //ESCAPEROOM_SETHIGHSCORE_HPP
