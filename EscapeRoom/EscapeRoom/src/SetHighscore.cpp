//
// Created by Lukas Kalab on 10.06.24.
//
#include "SetHighscore.hpp"
#include "Game.hpp"

int SetHighscore::score = 0;

SetHighscore::SetHighscore() {
    if (!backgroundTexture.loadFromFile("assets/textures/MainMenu/MainMenu.png")) {
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
    }
    if (!highscoreTexture.loadFromFile("assets/textures/Highscore/Highscore.png")) {
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        highscoreSprite.setTexture(highscoreTexture);
    }
    if (!highscoreTextfieldTexture.loadFromFile("assets/textures/Highscore/SetHighscore.png")) {
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        highscoreTextfieldSprite.setTexture(highscoreTextfieldTexture);
    }
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        cerr << "Failed to load font." << endl;
    }

    playerText.setPosition(475, 280);
    playerText.setFont(font);
    playerText.setCharacterSize(30);
    playerText.setFillColor(sf::Color::Black);

    yourScore.setFont(font);
    yourScore.setCharacterSize(30);
    yourScore.setPosition(610, 180);


    AudioManager::getInstance().playMusic("synthwave1.ogg", true);
    cout << "Playing GameOver music." << endl;
}

void SetHighscore::handleInput(sf::Event& event, sf::RenderWindow& window, Game& game) {
    yourScore.setString(to_string(getScore()));
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f translated_pos = window.mapPixelToCoords(mouse_pos);
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            cout << "Mouse x: " << translated_pos.x << " Mouse y: " << translated_pos.y << endl;

            if (translated_pos.x >= 562 && translated_pos.x <= 700
            && translated_pos.y >= 340 && translated_pos.y <= 388
            && playerInput.getSize() > 0) {
                addHighscore();
                playerInput.clear();
                playerText.setString(playerInput);
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                game.showHighscore();
            }
        }
    }
    else if (event.type == sf::Event::TextEntered) {
        // Only allow ASCII characters and limit the input to 15 characters
        if (event.text.unicode < 128 && event.text.unicode >= 32 && playerInput.getSize() < 15) {
            playerInput += static_cast<char>(event.text.unicode);
            playerText.setString(playerInput);
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace && playerInput.getSize() > 0) {
            //delete last character
            playerInput.erase(playerInput.getSize() - 1, 1);
            playerText.setString(playerInput);
        }
    }
}



void SetHighscore::addHighscore() {
    ofstream highscoreFile("assets/highscore/highscore.txt", ios_base::app);
    if (!highscoreFile) {
        cerr << "Failed to open highscore file for writing." << endl;
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
    window.draw(highscoreSprite);
    window.draw(highscoreTextfieldSprite);
    window.draw(yourScore);
    window.draw(playerText);
    window.display();
}
