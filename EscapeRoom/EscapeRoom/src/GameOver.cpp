#include "GameOver.hpp"
#include "Game.hpp"
#include "AudioManager.hpp"

GameOver::GameOver(Game* gameInstance) :
    game(gameInstance),
    returnToMenuButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(1040.f, 650.f), sf::Color(0, 100, 156), "Hauptmenue", 20),
    restartGameButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(1040.f, 580.f), sf::Color(139, 179, 29), "Neues Spiel", 20) {
}

void GameOver::enter() {
    static bool isEntered = false;
    if (isEntered) return;
    isEntered = true;

    if (!backgroundTexture.loadFromFile("assets/textures/GameOver/GameOver.png")) {
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
    }

    AudioManager::getInstance().playMusic("GameOverMusic.ogg", true);
    cout << "Playing GameOver music." << endl;
}

void GameOver::exit() {
    static bool isEntered = false; // Reset the flag
}

void GameOver::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);

            if (returnToMenuButton.isClicked(clickPosition)) {
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                game->returnToMainMenu();
                exit();

            }

            if (restartGameButton.isClicked(clickPosition)) { 
                AudioManager::getInstance().playSoundEffect("Click.ogg"); 
                game->resetGame();
                AudioManager::getInstance().stopMusic();
                AudioManager::getInstance().setMusicVolume(100);
                game->startNewGame();
                exit(); 
            }
        }
    }
}

void GameOver::update(float dt) {

}

void GameOver::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    returnToMenuButton.draw(window);
    restartGameButton.draw(window); 
    window.display();
}
