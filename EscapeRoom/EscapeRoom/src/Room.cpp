#include "Room.hpp"

Room::Room(Game* gameInstance) {
    game = gameInstance;
    questionIndex = 0;
    displayTextLineByLineActive = false;
    waitingForAnswer = false;
    lineDelayActive = false;
    lineDelayTime = 0;
    lineDelayDuration = 2.0f;
}

void Room::loadTexture(sf::Texture& texture, const std::string& filename, const std::string& name) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load " << name << " texture from " << filename << std::endl;
    }
}

void Room::setupSprites() {
    textfieldSprite.setTexture(textfieldTexture);
    madLecturerSprite.setTexture(madLecturerTexture);
    playerSprite.setTexture(playerTexture);
    niceLecturerSprite.setTexture(niceLecturerTexture);
    roomCompletedSprite.setTexture(roomCompletedTexture);
    background = niceLecturerSprite;
}

void Room::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from " << fontPath << std::endl;
    }
}

void Room::enter() {
    loadAssets();
    playBackgroundMusic();
    setupQuestionText(riddleText);
    displayTextLineByLineActive = true;
    displayTextLineByLineTime = 0;
}

void Room::exit() {
    _sleep(2000);
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

    if (displayTextLineByLineActive) {
        displayTextLineByLineTime += dt;
        if (displayTextLineByLineTime >= 0.05f) {
            displayTextLineByLineTime = 0;
            if (questionIndex < riddleText.size()) {
                char c = riddleText[questionIndex++];
                currentText += c;
                if (c == '\n') {
                    lineCount++;
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

std::string Room::readFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();
    return content;
}