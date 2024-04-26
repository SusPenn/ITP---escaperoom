#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Item {
public:
    void pickUp();
    void use();

private:
    std::string name;
    sf::Sprite iconTexture;
};

#endif // ITEM_HPP
