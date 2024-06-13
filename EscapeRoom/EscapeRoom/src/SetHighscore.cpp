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
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
    }
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        cerr << "Failed to load font." << endl;
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
    cout << "Playing GameOver music." << endl;
}

void SetHighscore::handleInput(sf::Event& event, sf::RenderWindow& window, Game& game) {
    yourScore.setString("Your Score: " + to_string(getScore()));
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
        if (event.text.unicode < 128 && event.text.unicode >= 32) { // Nur ASCII-Zeichen erlauben
            playerInput += static_cast<char>(event.text.unicode);
            playerText.setString(playerInput);
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace && playerInput.getSize() > 0) {
            playerInput.erase(playerInput.getSize() - 1, 1);
            cout << "PlayerInput: " << playerInput.toAnsiString() << endl;
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
    returnToHighscoreButton.draw(window);
    window.draw(headlineText);
    window.draw(yourScore);
    window.draw(playerText);
    window.display();
}
