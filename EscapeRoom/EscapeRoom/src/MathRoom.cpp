#include "MathRoom.hpp"

void MathRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/MACS_1/MACS_1_Porsche.png", "Porchet");
    loadTexture(textfieldTexture, "assets/textures/MACS_1/MACS_1_Textfield.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/MACS_1/MACS_1_Porsche_Mad.png", "Mad Porchet");
    loadTexture(progressTexture, "assets/textures/ProgressGlass/glass_1.png", "ProgressBefore");
    loadTexture(progressTextureAfter, "assets/textures/ProgressGlass/glass_2.png", "ProgressAfter");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/MACS_1/Fortuna.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_fortuna.png", "FortunaCompleted");
    }
    else {
        loadTexture(playerTexture, "assets/textures/MACS_1/Hilarius.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_hilarius.png", "FortunaCompleted");
    }

    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/MACS_1/MACRiddle.txt");
    madLecturerText = readFile("assets/textures/MACS_1/MadMACRiddle.txt");
}

void MathRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("Primzahlen.ogg", true);
}

void MathRoom::setupQuestionText(const std::string& text) {
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(235, 135);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool MathRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 235 && pos.x <= 325 && pos.y >= 218 && pos.y <= 249);
}

bool MathRoom::isWrongAnswer(const sf::Vector2f& pos) {
    if ((pos.x >= 235 && pos.x <= 325 && pos.y >= 165 && pos.y <= 218) || (pos.x >= 235 && pos.x <= 325 && pos.y >= 249 && pos.y <= 277)) {
        return true;
    } else {
        return false;
    }
}

void MathRoom::handleCorrectAnswer() {
    game->enterRoom("WebRoom");
}