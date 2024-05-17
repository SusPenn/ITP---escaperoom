#include "Highscore.hpp"
#include "Game.hpp"

Highscore::Highscore() {
    if (!highscoreTexture.loadFromFile("assets/textures/highscore.png")) {
        std::cerr << "Failed to load high score texture." << std::endl;
    }

    highscoreSprite.setTexture(highscoreTexture);
    AudioManager::getInstance().playMusic("synthwave1.ogg", true);
}

void Highscore::handleInput(sf::Event& event, sf::RenderWindow& window, Game& game) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        game.returnToMainMenu();
    }
}

void Highscore::update(float dt) {
    // Update logic if needed
}

void Highscore::draw(sf::RenderWindow& window) {
    window.draw(highscoreSprite);
}
