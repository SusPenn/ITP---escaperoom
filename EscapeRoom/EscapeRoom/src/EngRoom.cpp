#include "EngRoom.hpp"

void EngRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/ENG_1/ENG_1_Liberty.png", "Liberty");
    loadTexture(textfieldTexture, "assets/textures/ENG_1/ENG_1_Textfield.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/ENG_1/ENG_1_Liberty.png", "Liberty");
    loadTexture(roomCompletedTexture, "assets/textures/ENG_1/ENG_1_Liberty.png", "EngRoomCompleted");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/ENG_1/Fortuna.png", "Player");
    }
    else {
        loadTexture(playerTexture, "assets/textures/ENG_1/Hilarius.png", "Player");
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

void EngRoom::setupQuestionText(const std::string& text) {
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
    return (pos.x >= 288 && pos.x <= 628 && pos.y >= 212 && pos.y <= 220);
}

bool EngRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 287 && pos.x <= 775 && pos.y >= 178 && pos.y <= 190);
}

void EngRoom::handleCorrectAnswer() {
    std::cout << "Correct answer!" << std::endl;
    background = roomCompletedSprite;  // Change the background
    draw(game->getWindow());
    AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
    AudioManager::getInstance().stopMusic();
    waitingForAnswer = false;
    game->getGlobalTimer().pause();
    game->enterRoom("InfraRoom");
}