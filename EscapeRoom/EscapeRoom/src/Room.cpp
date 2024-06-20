#include "Room.hpp"

Room::Room(Game* gameInstance) {
    game = gameInstance;
    questionIndex = 0;
    displayTextLineByLineActive = false;
    waitingForAnswer = false;
    lineCount = 0;
    displayTextLineByLineActive = false;
    lineDelayActive = false;
    lineDelayTime = 0;
    lineDelayDuration = 2.0f;
}

void Room::loadTexture(sf::Texture& texture, const string& filename, const string& name) {
    if (!texture.loadFromFile(filename)) {
        cerr << "Failed to load " << name << " texture from " << filename << endl;
    }
}

void Room::setupSprites() {
    textfieldSprite.setTexture(textfieldTexture);
    madLecturerSprite.setTexture(madLecturerTexture);
    playerSprite.setTexture(playerTexture);
    niceLecturerSprite.setTexture(niceLecturerTexture);
    roomCompletedSprite.setTexture(roomCompletedTexture);
    background.setTexture(niceLecturerTexture);
    progressSprite.setTexture(progressTexture);
    progressSpriteAfter.setTexture(progressTextureAfter);
}

void Room::loadFont(const string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        cerr << "Failed to load font from " << fontPath << endl;
    }
}

void Room::enter() {
    game->getGlobalTimer().start();
    loadAssets();
    playBackgroundMusic();
    setupQuestionText(riddleText);
    displayTextLineByLineActive = true;
    displayTextLineByLineTime = 0;
}

void Room::exit() {
    game->getGlobalTimer().pause();
    progressSprite = progressSpriteAfter;
    game->getWindow().clear();
    game->getWindow().draw(niceLecturerSprite);
    game->getWindow().draw(roomCompletedSprite);
    game->getWindow().draw(progressSprite);
    game->getGlobalTimer().draw(game->getWindow());
    game->getWindow().display();
    AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
    AudioManager::getInstance().stopMusic();
    waitingForAnswer = false;
    sf::sleep(sf::seconds(2));
    AudioManager::getInstance().playSoundEffect("Teleport.ogg");
    sf::sleep(sf::seconds(1));
}

void Room::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    if (waitingForAnswer && event.type == sf::Event::MouseButtonPressed) {
        handleMouseClick(window);
    }
}

void Room::update(float dt) {
    // If the line delay is active, wait for the line delay to finish
    if (lineDelayActive) {
        lineDelayTime += dt;
        if (lineDelayTime >= lineDelayDuration) {
            lineDelayActive = false;
            lineDelayTime = 0;
            currentText.clear();
            questionText.setString(currentText);
            displayTextLineByLineActive = true;
        }
        return;
    }
    // If the line delay is not active, display the text line by line
    if (displayTextLineByLineActive) {
        displayTextLineByLineTime += dt;
        if (displayTextLineByLineTime >= 0.05f) {
            displayTextLineByLineTime = 0;
            if (questionIndex < riddleText.size()) {
                char c = riddleText[questionIndex++];
                currentText += c;
                if (c == '\n') {
                    lineCount++;
                    // If the line count is 5, 10, or 15, stop displaying the text line by line
                    if (lineCount == 5 || lineCount == 10 || lineCount == 15) {
                        displayTextLineByLineActive = false;
                        lineDelayActive = true;
                        lineDelayTime = 0;
                    }
                }
                questionText.setString(currentText);
            }
            else {
                displayTextLineByLineActive = false;
                waitingForAnswer = true;
            }
        }
    }
}

void Room::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(background);
    window.draw(playerSprite);
    window.draw(textfieldSprite);
    window.draw(questionText);
    window.draw(progressSprite);
    game->getGlobalTimer().draw(window);
    window.display();
    game->getGlobalTimer().update();
}

void Room::handleWrongAnswer() {
    AudioManager::getInstance().playSoundEffect("FailSounds/ComputerFail.ogg");
    background = madLecturerSprite;
    setupQuestionText(madLecturerText);
    displayTextLineByLineActive = true;
    questionIndex = 0;
    currentText.clear();
    riddleText = madLecturerText;
    waitingForAnswer = false;
}

void Room::handleMouseClick(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f translatedPos = window.mapPixelToCoords(mousePos);

    if (isCorrectAnswer(translatedPos)) {
        handleCorrectAnswer();
    }
    else if (isWrongAnswer(translatedPos)) {
        handleWrongAnswer();
    }
}

string Room::readFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Failed to open file: " << filename << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    return content;
}