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

using namespace std;

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
    void loadAssets();

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture highscoreTexture;
    sf::Sprite highscoreSprite;
    sf::Texture highscoreButtonTexture;
    sf::Sprite highscoreButtonSprite;
    sf::Texture newGameButtonTexture;
    sf::Sprite newGameButtonSprite;
    sf::Texture exitButtonTexture;
    sf::Sprite exitButtonSprite;

    vector<sf::Text> highscoreTexts;
    sf::Font font;
    vector<pair<string, int>> highscoreList;
};

#endif // HIGHSCORE_HPP
