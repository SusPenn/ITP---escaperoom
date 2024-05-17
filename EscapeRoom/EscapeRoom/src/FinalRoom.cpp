#include "FinalRoom.hpp"
#include "Game.hpp"

FinalRoom::FinalRoom(Game* gameInstance) {
    game = gameInstance;
    questionIndex = 0;
    displayTextLineByLineActive = false;
    waitingForAnswer = false;
    lineDelayActive = false;
    lineDelayTime = 0;
    lineDelayDuration = 2.0f;
}

void FinalRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/Pictures/Prozedurale Sprachen Labor/Prozedurale Sprachen Labor+Richter+freundlich.png", "Richter");
    loadTexture(textfieldTexture, "assets/textures/Pictures/Prozedurale Sprachen Labor/textfeldprozd.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/Pictures/Prozedurale Sprachen Labor/Prozedurale Sprachen Labor+Richter+unfreundlich.png", "Mad Richter");
    loadTexture(roomCompletedTexture, "assets/textures/Pictures/Prozedurale Sprachen Labor/Prozedurale Sprachen Labor+Richter+freundlich.png", "FinalRoomCompleted");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/Pictures/Prozedurale Sprachen Labor/Fortuna.png", "Player");
    }
    else {
        loadTexture(playerTexture, "assets/textures/Pictures/Prozedurale Sprachen Labor/Hilarius.png", "Player");
    }

    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/Pictures/Prozedurale Sprachen Labor/cRiddle.txt");
    madLecturerText = readFile("assets/textures/Pictures/Prozedurale Sprachen Labor/madRichterReply.txt");
}

void FinalRoom::loadTexture(sf::Texture& texture, const std::string& filename, const std::string& name) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load " << name << " texture from " << filename << std::endl;
    }
}

void FinalRoom::setupSprites() {
    textfieldSprite.setTexture(textfieldTexture);
    madLecturerSprite.setTexture(madLecturerTexture);
    playerSprite.setTexture(playerTexture);
    niceLecturerSprite.setTexture(niceLecturerTexture);
    roomCompletedSprite.setTexture(roomCompletedTexture);
    background = niceLecturerSprite;
}

void FinalRoom::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from " << fontPath << std::endl;
    }
}

void FinalRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("Kahoot.ogg", true);
}

void FinalRoom::enter() {
    loadAssets();
    playBackgroundMusic();
    setupQuestionText(riddleText);
    displayTextLineByLineActive = true;
    displayTextLineByLineTime = 0;
}

void FinalRoom::exit() {
    _sleep(2000);
}

void FinalRoom::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    if (waitingForAnswer && event.type == sf::Event::MouseButtonPressed) {
        handleMouseClick(window);
    }
}

void FinalRoom::update(float dt) {
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

void FinalRoom::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(background);
    window.draw(playerSprite);
    window.draw(textfieldSprite);
    window.draw(questionText);
    game->getGlobalTimer().draw(window);
    window.display();
    game->getGlobalTimer().update();
}

void FinalRoom::setupQuestionText(const std::string& text) {
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(357, 462);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

std::string FinalRoom::readFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();
    return content;
}

void FinalRoom::handleMouseClick(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f translatedPos = window.mapPixelToCoords(mousePos);

    if (isCorrectAnswer(translatedPos)) {
        handleCorrectAnswer();
    }
    else if (isWrongAnswer(translatedPos)) {
        handleWrongAnswer();
    }
}

bool FinalRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 350 && pos.x <= 470 && pos.y >= 494 && pos.y <= 520);
}

bool FinalRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 350 && pos.x <= 494 && pos.y >= 520 && pos.y <= 600);
}

void FinalRoom::handleCorrectAnswer() {
    std::cout << "Correct answer!" << std::endl;
    background = roomCompletedSprite;  // Change the background
    draw(game->getWindow());
    AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
    AudioManager::getInstance().stopMusic();
    waitingForAnswer = false;
    game->getGlobalTimer().pause();
    game->setFinalRoomFinished();
    game->setCurrentState(GameState::Outro);
}

void FinalRoom::handleWrongAnswer() {
    AudioManager::getInstance().playSoundEffect("FailSounds/ComputerFail.ogg");
    background = madLecturerSprite;
    setupQuestionText(madLecturerText);
    displayTextLineByLineActive = true;
    questionIndex = 0;
    currentText.clear();
    riddleText = madLecturerText;
    waitingForAnswer = false;
}
