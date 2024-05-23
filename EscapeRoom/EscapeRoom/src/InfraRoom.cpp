#include "InfraRoom.hpp"

void InfraRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/Pictures/Infrastruktur Grundlagen/Infrastruktur_Grundlagen+Ballner.png", "Ballner");
    loadTexture(textfieldTexture, "assets/textures/Pictures/Infrastruktur Grundlagen/textfeldinfra.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/Pictures/Infrastruktur Grundlagen/Infrastruktur_Grundlagen+Ballner+unfreundlich.png", "Mad Ballner");
    loadTexture(roomCompletedTexture, "assets/textures/Pictures/Infrastruktur Grundlagen/Infrastruktur_Grundlagen+Ballner.png", "InfraRoomCompleted");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/Pictures/Infrastruktur Grundlagen/Fortuna.png", "Player");
    }
    else {
        loadTexture(playerTexture, "assets/textures/Pictures/Infrastruktur Grundlagen/Hilarius.png", "Player");
    }
  
    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/Pictures/Infrastruktur Grundlagen/InfraRiddle.txt");
    madLecturerText = readFile("assets/textures/Pictures/Infrastruktur Grundlagen/MadInfraRiddle.txt");
}

void InfraRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("InspiringDaysLoop.ogg", true);
}

void InfraRoom::setupQuestionText(const std::string& text) {
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(523, 80);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool InfraRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 525 && pos.x <= 1153 && pos.y >= 144 && pos.y <= 178); // area **b**
}

bool InfraRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 525 && pos.x <= 1153 &&
        ((pos.y >= 118 && pos.y < 144) ||  (pos.y > 178 && pos.y < 208)));  
}

void InfraRoom::handleCorrectAnswer() {
    std::cout << "Correct answer!" << std::endl;
    background = roomCompletedSprite;  // Change the background
    draw(game->getWindow());
    AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
    AudioManager::getInstance().stopMusic();
    waitingForAnswer = false;
    game->getGlobalTimer().pause();
    game->enterRoom("ProzdRoom");
}
