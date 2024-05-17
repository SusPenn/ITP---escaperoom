#ifndef HIGHSCORE_HPP
#define HIGHSCORE_HPP

#include <SFML/Graphics.hpp>
#include "AudioManager.hpp"
#include <iostream>

// Forward declaration
class Game;

class Highscore {
public:
    Highscore();
    void handleInput(sf::Event& event, sf::RenderWindow& window, Game& game);
    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite highscoreSprite;
    sf::Texture highscoreTexture;
};

#endif // HIGHSCORE_HPP
