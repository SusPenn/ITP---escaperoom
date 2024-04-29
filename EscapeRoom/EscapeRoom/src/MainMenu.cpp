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

void MainMenu::handleInput(sf::Vector2f translated_pos, sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (translated_pos.x >= 36 && translated_pos.x <= 360 && translated_pos.y >= 466 && translated_pos.y <= 518) {
            std::cout << "Neues Spiel" << std::endl;
            window.clear();  
            window.display();  

            Intro intro = Intro("assets/intro/intro.txt", window);
            intro.play();  
        }
        if (translated_pos.x >= 39 && translated_pos.x <= 361 && translated_pos.y >= 525 && translated_pos.y <= 575) {
            std::cout << "Highscore" << std::endl;
        }
        if (translated_pos.x >= 54 && translated_pos.x <= 362 && translated_pos.y >= 583 && translated_pos.y <= 633) {
            std::cout << "Beenden" << std::endl;
            window.close();
        }
    }
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


