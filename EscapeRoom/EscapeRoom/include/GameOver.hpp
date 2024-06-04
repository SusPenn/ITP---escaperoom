#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.hpp"

class Game;

class GameOver {
public:
    GameOver(Game* gameInstance);
    void enter();
    void exit();
    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void update(float dt);
    void draw(sf::RenderWindow& window);
private:
    Game* game;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Button returnToMenuButton;
    Button restartGameButton;
};

#endif // GAMEOVER_HPP
