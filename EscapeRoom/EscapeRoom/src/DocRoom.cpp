//
// Created by Lukas Kalab on 22.05.24.
//

#include "DocRoom.h"

void DocRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/Pictures/Datenmanagement/Datenmanagement+Docsek.png", "Doc");
    loadTexture(textfieldTexture, "assets/textures/Pictures/Datenmanagement/textfelddm.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/Pictures/Datenmanagement/Datenmanagement+Docsek.png", "Mad Doc");
    loadTexture(roomCompletedTexture, "assets/textures/Pictures/Datenmanagement/Datenmanagement+Docsek.png", "DocRoomCompleted");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/Pictures/Datenmanagement/Fortuna.png", "Player");
    }
    else {
        loadTexture(playerTexture, "assets/textures/Pictures/Datenmanagement/Hilarius.png", "Player");
    }

    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/Pictures/Datenmanagement/cRiddle.txt");
    madLecturerText = readFile("assets/textures/Pictures/Datenmanagement/madRichterReply.txt");
}

void DocRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("InspirationalLoop.ogg", true);
}

void DocRoom::setupQuestionText(const std::string& text) {
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(357, 462);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool DocRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 350 && pos.x <= 470 && pos.y >= 494 && pos.y <= 520);
}

bool DocRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 350 && pos.x <= 494 && pos.y >= 520 && pos.y <= 600);
}

void DocRoom::handleCorrectAnswer() {
    std::cout << "Correct answer!" << std::endl;
    background = roomCompletedSprite;  // Change the background
    draw(game->getWindow());
    AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
    AudioManager::getInstance().stopMusic();
    waitingForAnswer = false;
    game->getGlobalTimer().pause();
    game->setRoom1Finished();
    game->setCurrentState(GameState::Outro);
}