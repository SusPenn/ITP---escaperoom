#include "CharacterSelection.hpp"
#include "Game.hpp"

CharacterSelection::CharacterSelection(Game* game)
    : game(game) {
    if (!backgroundTexture.loadFromFile("./assets/textures/Characters/Character_Choose.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return;
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);

    // define click area
    float halfWidth = game->getWindow().getSize().x / 2.0f;
    float height = game->getWindow().getSize().y;

    // left side -> fortuna
    fortunaRect = sf::FloatRect(0, 0, halfWidth, height);
    // right side -> Hilarius
    hilariusRect = sf::FloatRect(halfWidth, 0, halfWidth, height);
}

void CharacterSelection::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (fortunaRect.contains(mousePos)) {
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                game->setChosenCharacter("Fortuna");
                game->setCurrentState(GameState::InGame);
            }
            else if (hilariusRect.contains(mousePos)) {
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                game->setChosenCharacter("Hilarius");
                game->setCurrentState(GameState::InGame);
            }
        }
    }
}

void CharacterSelection::draw(sf::RenderWindow& window) {
    window.clear(); //Clear the window before drawing
    window.draw(backgroundSprite);
    window.display();
}