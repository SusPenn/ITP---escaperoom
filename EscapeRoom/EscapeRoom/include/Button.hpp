#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& text, const int characterSize);
    void draw(sf::RenderWindow& window) const;
    bool isClicked(sf::Vector2f clickPosition);

private:
	sf::Font font;
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    void centerText();
};

#endif // BUTTON_HPP
