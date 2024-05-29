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

	// Die Mitte des Buttons berechnen und den Text zentrieren
	float centerX = buttonPosition.x + buttonSize.x / 2.0f - textRect.width / 2.0f;
    float centerY = buttonPosition.y + buttonSize.y / 2.0f - textRect.height / 2.0f;
    buttonText.setPosition(centerX, centerY);
}