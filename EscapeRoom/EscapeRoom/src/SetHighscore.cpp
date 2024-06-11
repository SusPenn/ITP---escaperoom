//
// Created by Lukas Kalab on 10.06.24.
//
#include "SetHighscore.hpp"
#include "Game.hpp"

int SetHighscore::score = 0;

SetHighscore::SetHighscore() :
        returnToHighscoreButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(1040.f, 650.f),
                           sf::Color(0, 100, 156), "Add your Highscore", 20) {
    if (!backgroundTexture.loadFromFile("assets/textures/Highscore/Highscore.png")) {
        std::cerr << "Failed to load game over background texture." << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
    }
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    headlineText.setString("Enter your name:");
    headlineText.setFont(font);
    headlineText.setCharacterSize(50);
    headlineText.setPosition(500, 400);
    headlineText.setStyle(sf::Text::Bold);
    headlineText.setFillColor(sf::Color::Black);

    playerText.setPosition(500, 500);
    playerText.setFont(font);
    playerText.setCharacterSize(30);
    playerText.setFillColor(sf::Color::Green);

    yourScore.setFont(font);
    yourScore.setCharacterSize(60);
    yourScore.setPosition(500, 300);


    AudioManager::getInstance().playMusic("synthwave1.ogg", true);
    std::cout << "Playing GameOver music." << std::endl;
}

void SetHighscore::handleInput(sf::Event& event, sf::RenderWindow& window, Game& game) {
    yourScore.setString("Your Score" + to_string(getScore()));
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f translated_pos = window.mapPixelToCoords(mouse_pos);
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            cout << "Mouse x: " << translated_pos.x << " Mouse y: " << translated_pos.y << endl;
            sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);

            if (returnToHighscoreButton.isClicked(clickPosition) && !playerInput.isEmpty()) {
                cout << "Your Score: " << getScore() << endl;
                addHighscore();
                playerInput.clear();
                playerText.setString(playerInput);
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                game.showHighscore();
            }
        }
    }
    else if (event.type == sf::Event::TextEntered) {
        playerInput +=event.text.unicode;
        playerText.setString(playerInput);
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace && playerInput.end() != playerInput.begin()) {
            playerInput.erase(playerInput.getSize() - 1, 1);
            //playerInput = playerInput.substring(0, playerInput.getSize()-1);
            playerText.setString(playerInput);
        }
    }
}


void SetHighscore::addHighscore() {
    std::ofstream highscoreFile("assets/highscore/highscore.txt", std::ios_base::app);
    if (!highscoreFile) {
        std::cerr << "Failed to open highscore file for writing." << std::endl;
        return;
    }

    // Add the new highscore to the file
    highscoreFile << playerInput.toAnsiString() << "," << score << "|";
    highscoreFile.close();
}

void SetHighscore::update(float dt) {
    // Update logic if needed
}

void SetHighscore::setScore(int newScore) {
    score = newScore;
}

int SetHighscore::getScore() {
    return score;
}

void SetHighscore::draw(sf::RenderWindow& window) {

    window.clear();
    window.draw(backgroundSprite);
    returnToHighscoreButton.draw(window);
    window.draw(headlineText);
    window.draw(yourScore);
    window.draw(playerText);
    window.display();
}
