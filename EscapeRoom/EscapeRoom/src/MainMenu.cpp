#include "MainMenu.hpp"
#include "Game.hpp"

MainMenu::MainMenu() {
    if (!menuTexture.loadFromFile("assets/textures/MainMenu/MainMenu.png")) {
        std::cerr << "Failed to load main menu texture." << std::endl;
    }
    if (!newGameTexture.loadFromFile("assets/textures/MainMenu/New_Game.png")) {
        std::cerr << "Failed to load new game texture." << std::endl;
    }
    if (!exitTexture.loadFromFile("assets/textures/MainMenu/Quit.png")) {
        std::cerr << "Failed to load exit texture." << std::endl;
    }
    if (!highScoreTexture.loadFromFile("assets/textures/MainMenu/Highscore.png")) {
        std::cerr << "Failed to load high score texture." << std::endl;
    }

    menuSprite.setTexture(menuTexture);
    newGameSprite.setTexture(newGameTexture);
    exitSprite.setTexture(exitTexture);
    highScoreSprite.setTexture(highScoreTexture);

    AudioManager::getInstance().playMusic("synthwave1.ogg", true);
}

void MainMenu::handleInput(sf::Event& event, sf::RenderWindow& window, Game& game) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            sf::Vector2f translated_pos = window.mapPixelToCoords(mouse_pos);

            if (translated_pos.x >= 36 && translated_pos.x <= 360 && translated_pos.y >= 466 && translated_pos.y <= 518) {
                std::cout << "Neues Spiel" << std::endl;
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                game.startNewGame();
            }
            if (translated_pos.x >= 39 && translated_pos.x <= 361 && translated_pos.y >= 525 && translated_pos.y <= 575) {
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                std::cout << "Highscore" << std::endl;
                game.showHighscore();
            }
            if (translated_pos.x >= 54 && translated_pos.x <= 362 && translated_pos.y >= 583 && translated_pos.y <= 633) {
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                std::cout << "Beenden" << std::endl;
                window.close();
            }
        }
    }
}

void MainMenu::draw(sf::RenderWindow& window) const {
    window.draw(menuSprite);
    window.draw(newGameSprite);
    window.draw(exitSprite);
    window.draw(highScoreSprite);
    window.display();
}