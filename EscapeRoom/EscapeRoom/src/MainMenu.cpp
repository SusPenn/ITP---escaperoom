#include "MainMenu.hpp"

MainMenu::MainMenu() {
    sf::Texture menuTexture;
    sf::Texture newGameTexture;
    sf::Texture quidTexture;
    sf::Texture highScoreTexture;
    menuTexture.loadFromFile("assets/textures/mainMenu.png");
    newGameTexture.loadFromFile("assets/textures/newGame.png");
    quidTexture.loadFromFile("assets/textures/exit.png");
    highScoreTexture.loadFromFile("assets/textures/highscore.png");
    menuSprite.setTexture(menuTexture);
    newGameSprite.setTexture(newGameTexture);
    quidSprite.setTexture(quidTexture);
    highScoreSprite.setTexture(highScoreTexture);

    newGameSprite.setPosition(35.0f, 460.0f);
    highScoreSprite.setPosition(36.0f, 517.5f);
    quidSprite.setPosition(50.5f, 575.5f);


}

void MainMenu::handleInput() {

}

void MainMenu::update(float dt) {

}

void MainMenu::draw(sf::RenderWindow &window) {
    window.draw(menuSprite);
    window.draw(newGameSprite);
    window.draw(quidSprite);
    window.draw(highScoreSprite);
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

sf::Sprite MainMenu::getQuidSprite() const {
    return quidSprite;
}

sf::Sprite MainMenu::getHighScoreSprite() const {
    return highScoreSprite;
}


