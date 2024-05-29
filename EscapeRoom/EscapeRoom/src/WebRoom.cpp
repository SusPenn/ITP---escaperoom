#include "WebRoom.hpp"

void WebRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/WEB_1/WEB_1_Browser.png", "Browser");
    loadTexture(textfieldTexture, "assets/textures/WEB_1/WEB_1_Textfield.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/WEB_1/WEB_1_Browser_Mad.png", "Mad Browser");
    loadTexture(roomCompletedTexture, "assets/textures/WEB_1/WEB_1_Browser.png", "WebRoomCompleted");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/WEB_1/Fortuna.png", "Player");
    }
    else {
        loadTexture(playerTexture, "assets/textures/WEB_1/Hilarius.png", "Player");
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
    questionText.setPosition(300, 149);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool WebRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 300 && pos.x <= 774 && pos.y >= 262 && pos.y <= 319);
}

bool WebRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 300 && pos.x <= 996 && pos.y >= 185 && pos.y <= 262);
}

void WebRoom::handleCorrectAnswer() {
    std::cout << "Correct answer!" << std::endl;
    background = roomCompletedSprite;  // Change the background
    draw(game->getWindow());
    AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
    AudioManager::getInstance().stopMusic();
    waitingForAnswer = false;
    game->getGlobalTimer().pause();
    game->enterRoom("InfraRoom");
}