#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "AudioManager.hpp"

class Game;  // Forward declaration of Game

class MainMenu {
public:
    MainMenu();
    void handleInput(sf::Event& event, sf::RenderWindow& window, Game& game);
    void draw(sf::RenderWindow& window) const;

private:
    void startNewGame(Game& game);

    sf::Texture menuTexture;
    sf::Texture newGameTexture;
    sf::Texture exitTexture;
    sf::Texture highScoreTexture;

    sf::Sprite menuSprite;
    sf::Sprite newGameSprite;
    sf::Sprite exitSprite;
    sf::Sprite highScoreSprite;
};

#endif // MAINMENU_HPP
