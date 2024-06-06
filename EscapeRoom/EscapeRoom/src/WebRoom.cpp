#include "WebRoom.hpp"

void WebRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/WEB_1/WEB_1_Browser.png", "Browser");
    loadTexture(textfieldTexture, "assets/textures/WEB_1/WEB_1_Textfield.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/WEB_1/WEB_1_Browser_Mad.png", "Mad Browser");
    loadTexture(roomCompletedTexture, "assets/textures/WEB_1/WEB_1_Browser.png", "WebRoomCompleted");
    loadTexture(progressTexture, "assets/textures/ProgressGlass/glass_2.png", "ProgressBefore");
    loadTexture(progressTextureAfter, "assets/textures/ProgressGlass/glass_3.png", "ProgressAfter");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/WEB_1/Fortuna.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_fortuna.png", "FortunaCompleted");
    }
    else {
        loadTexture(playerTexture, "assets/textures/WEB_1/Hilarius.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_hilarius.png", "FortunaCompleted");
    }

    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/WEB_1/WEBRiddle.txt");
    madLecturerText = readFile("assets/textures/WEB_1/MadWEBRiddle.txt");
}

void WebRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("Bowser.ogg", true);
}

void WebRoom::setupQuestionText(const std::string& text) {
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(300, 119);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool WebRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 300 && pos.x <= 824 && pos.y >= 232 && pos.y <= 289);
}

bool WebRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 300 && pos.x <= 996 && pos.y >= 135 && pos.y <= 232);
}

void WebRoom::handleCorrectAnswer() {
    game->enterRoom("KokoRoom");
}