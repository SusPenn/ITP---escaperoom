#include "MainMenu.hpp"

MainMenu::MainMenu() {
    menuTexture.loadFromFile("assets/textures/mainMenu.png");
    newGameTexture.loadFromFile("assets/textures/newGame.png");
    exitTexture.loadFromFile("assets/textures/exit.png");
    highScoreTexture.loadFromFile("assets/textures/highscore.png");
    menuSprite.setTexture(menuTexture);
    newGameSprite.setTexture(newGameTexture);
    exitSprite.setTexture(exitTexture);
    highScoreSprite.setTexture(highScoreTexture);
}

void MainMenu::handleInput() {

}

void MainMenu::update(float dt) {

}

void MainMenu::draw(sf::RenderWindow &window) {
    window.draw(menuSprite);
    window.draw(newGameSprite);
    window.draw(exitSprite);
    window.draw(highScoreSprite);

    newGameSprite.setPosition(35.0f, 460.0f);
    highScoreSprite.setPosition(36.0f, 517.5f);
    exitSprite.setPosition(50.5f, 575.5f);
}



void MainMenu::activateButton() {

}

void MainMenu::enter() {

}

void MainMenu::exit() {

}

sf::Sprite MainMenu::getNewGameSprite() const {
    return newGameSprite;
}

sf::Sprite MainMenu::getExitSprite() const {
    return exitSprite;
}

sf::Sprite MainMenu::getHighScoreSprite() const {
    return highScoreSprite;
}


