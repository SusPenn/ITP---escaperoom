#include "Button.hpp"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& text, const int characterSize) {
	font.loadFromFile("assets/intro/arial.ttf");

    buttonShape.setSize(size);
    buttonShape.setPosition(position);
    buttonShape.setFillColor(color);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(characterSize);
    buttonText.setFillColor(sf::Color::White);
    centerText();
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(buttonShape);
    window.draw(buttonText);
}

bool Button::isClicked(sf::Vector2f clickPosition) {
    return buttonShape.getGlobalBounds().contains(clickPosition);
}

void Button::centerText() {
    sf::FloatRect textRect = buttonText.getLocalBounds();
    sf::Vector2f buttonPosition = buttonShape.getPosition();
    sf::Vector2f buttonSize = buttonShape.getSize();
    buttonText.setPosition(
        buttonShape.getPosition().x + (buttonShape.getSize().x - textRect.width) / 2.f - textRect.left,
        buttonShape.getPosition().y + (buttonShape.getSize().y - textRect.height) / 2.f - textRect.top
    );
}

void Button::setVisibility(bool isVisible) {
	this->isVisible = isVisible;
}

bool Button::getIsButtonVisible() const {
	return isVisible;
}