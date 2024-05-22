#include "MathRoom.hpp"

void MathRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/Pictures/Mathematik für Computer Science 1/Mathematik_für_Computer_Science_1+Porchet.png", "Porchet");
    loadTexture(textfieldTexture, "assets/textures/Pictures/Mathematik für Computer Science 1/textfeldmathe.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/Pictures/Mathematik für Computer Science 1/Mathematik_für_Computer_Science_1+Porchet+unfreundlich.png", "Mad Porchet");
    loadTexture(roomCompletedTexture, "assets/textures/Pictures/Mathematik für Computer Science 1/Mathematik_für_Computer_Science_1+Porchet.png", "MathRoomCompleted");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/Pictures/Mathematik für Computer Science 1/Fortuna.png", "Player");
    }
    else {
        loadTexture(playerTexture, "assets/textures/Pictures/Mathematik für Computer Science 1/Hilarius.png", "Player");
    }

    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/Pictures/Mathematik für Computer Science 1/MACRiddle.txt");
    madLecturerText = readFile("assets/textures/Pictures/Mathematik für Computer Science 1/MadMACRiddle.txt");
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
    questionText.setPosition(357, 462);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool MathRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 350 && pos.x <= 470 && pos.y >= 494 && pos.y <= 520);
}

bool MathRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 350 && pos.x <= 494 && pos.y >= 520 && pos.y <= 600);
}

void MathRoom::handleCorrectAnswer() {
    std::cout << "Correct answer!" << std::endl;
    background = roomCompletedSprite;  // Change the background
    draw(game->getWindow());
    AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
    AudioManager::getInstance().stopMusic();
    waitingForAnswer = false;
    game->getGlobalTimer().pause();
    game->enterRoom("ProzdRoom");
}