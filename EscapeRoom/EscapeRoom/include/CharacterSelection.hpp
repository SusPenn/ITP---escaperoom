#ifndef CHARACTER_SELECTION_HPP
#define CHARACTER_SELECTION_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Game;

class CharacterSelection {
public:
    CharacterSelection(Game* game);
    void handleInput(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    Game* game;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::FloatRect fortunaRect;
    sf::FloatRect hilariusRect;
};

#endif // CHARACTER_SELECTION_HPP
