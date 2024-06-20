#include "EngRoom.hpp"

void EngRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/ENG_1/ENG_1_Liberty.png", "Liberty");
    loadTexture(textfieldTexture, "assets/textures/ENG_1/ENG_1_Textfield.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/ENG_1/ENG_1_Liberty.png", "Liberty");
    loadTexture(roomCompletedTexture, "assets/textures/ENG_1/ENG_1_Liberty.png", "EngRoomCompleted");
    loadTexture(progressTexture, "assets/textures/ProgressGlass/glass_4.png", "ProgressBefore");
    loadTexture(progressTextureAfter, "assets/textures/ProgressGlass/glass_5.png", "ProgressAfter");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/ENG_1/Fortuna.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_fortuna.png", "FortunaCompleted");
    }
    else {
        loadTexture(playerTexture, "assets/textures/ENG_1/Hilarius.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_hilarius.png", "FortunaCompleted");
    }

    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/ENG_1/EngRiddle.txt");
    madLecturerText = readFile("assets/textures/ENG_1/MadEngRiddle.txt");
}

void EngRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("National.ogg", true);
}

void EngRoom::setupQuestionText(const string& text) {
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(285, 85);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool EngRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 287 && pos.x <= 715 && pos.y >= 147 && pos.y <= 164);
}

bool EngRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 287 && pos.x <= 581 && pos.y >= 176 && pos.y <= 252);
}

void EngRoom::handleCorrectAnswer() {
    game->enterRoom("InfraRoom");
}