#include "KokoRoom.hpp"

void KokoRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/KOKO/KOKO_Hippie_Joint.png", "Hippie");
    loadTexture(textfieldTexture, "assets/textures/KOKO/KOKO_Textfield.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/KOKO/KOKO_Hippie_Mad.png", "Mad Hippie");
    loadTexture(roomCompletedTexture, "assets/textures/KOKO/KOKO_Hippie_Joint.png", "WebRoomCompleted");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/WEB_1/Fortuna.png", "Player");
    }
    else {
        loadTexture(playerTexture, "assets/textures/WEB_1/Hilarius.png", "Player");
    }

    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/KOKO/KOKORiddle.txt");
    madLecturerText = readFile("assets/textures/KOKO/MadKOKORiddle.txt");
}

void KokoRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("Wonderful.ogg", true);
}

void KokoRoom::setupQuestionText(const std::string& text) {
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(50, 119);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool KokoRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 80 && pos.x <= 420 && pos.y >= 160 && pos.y <= 245);
}

 bool KokoRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 170 && pos.x <= 210 && pos.y >= 590 && pos.y <= 595);
}

void KokoRoom::handleCorrectAnswer() {
    std::cout << "Correct answer!" << std::endl;
    background = roomCompletedSprite;  // Change the background
    draw(game->getWindow());
    AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
    AudioManager::getInstance().stopMusic();
    waitingForAnswer = false;
    game->getGlobalTimer().pause();
    game->enterRoom("InfraRoom");
}