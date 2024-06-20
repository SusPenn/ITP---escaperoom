#include "ProzdRoom.hpp"

void ProzdRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/PROZD/PROZD_Judge.png", "Richter");
    loadTexture(textfieldTexture, "assets/textures/PROZD/PROZD_Textfield.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/PROZD/PROZD_Judge_Mad.png", "Mad Richter");
    loadTexture(roomCompletedTexture, "assets/textures/PROZD/PROZD_Judge.png", "FinalRoomCompleted");
    loadTexture(progressTexture, "assets/textures/ProgressGlass/glass_6.png", "ProgressBefore");
    loadTexture(progressTextureAfter, "assets/textures/ProgressGlass/glass_7.png", "ProgressAfter");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/PROZD/Fortuna.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_fortuna.png", "FortunaCompleted");
    }
    else {
        loadTexture(playerTexture, "assets/textures/PROZD/Hilarius.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_hilarius.png", "FortunaCompleted");
    }

    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/PROZD/cRiddle.txt");
    madLecturerText = readFile("assets/textures/PROZD/madRichterReply.txt");
}

void ProzdRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("Kahoot.ogg", true);
}

void ProzdRoom::setupQuestionText(const string& text) {
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(357, 462);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool ProzdRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 350 && pos.x <= 470 && pos.y >= 494 && pos.y <= 520);
}

bool ProzdRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 350 && pos.x <= 494 && pos.y >= 520 && pos.y <= 600);
}

void ProzdRoom::handleCorrectAnswer() {
    game->getGlobalTimer().pause();
    game->setScore();
    exit();
    game->gameWon();
}