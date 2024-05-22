#include "ProzdRoom.hpp"

void ProzdRoom::loadAssets() {
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

void ProzdRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("Kahoot.ogg", true);
}

void ProzdRoom::setupQuestionText(const std::string& text) {
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
    std::cout << "Correct answer!" << std::endl;
    background = roomCompletedSprite;  // Change the background
    draw(game->getWindow());
    AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
    AudioManager::getInstance().stopMusic();
    waitingForAnswer = false;
    game->getGlobalTimer().pause();
    game->setCurrentState(GameState::Outro);
}