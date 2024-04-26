#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>
#include "Inventory.hpp"

class Player {
public:
    void move(const sf::Vector2f& direction);
    void interact();

private:
    sf::Vector2f position;
    Inventory inventory;
};

#endif // PLAYER_HPP
