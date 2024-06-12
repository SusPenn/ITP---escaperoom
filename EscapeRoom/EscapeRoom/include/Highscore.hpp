#ifndef HIGHSCORE_HPP
#define HIGHSCORE_HPP

#include <SFML/Graphics.hpp>
#include "AudioManager.hpp"
#include "Button.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// Forward declaration
class Game;

class Highscore {
public:
    Highscore();
    void handleInput(sf::Event& event, sf::RenderWindow& window, Game& game);
    void loadHighscores();
    void showHighscore();
    void resetHighscores();
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Button returnToMenuButton;
    vector<sf::Text> highscoreTexts;
    sf::Font font;
    vector<pair<string, int>> highscoreList;
};

#endif // HIGHSCORE_HPP
