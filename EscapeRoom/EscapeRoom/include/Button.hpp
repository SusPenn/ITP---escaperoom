#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class Button {
public:
    Button(const std::string& label, const sf::Vector2f& position, std::function<void()> onClick);
    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2i& mousePosition) const;

private:
    std::string label;
    sf::RectangleShape shape;
    std::function<void()> action;
};

#endif // BUTTON_HPP
