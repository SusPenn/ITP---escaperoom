#include "DocRoom.hpp"

void DocRoom::loadAssets() {
    loadTexture(niceLecturerTexture, "assets/textures/DMNMT/DMNMT_Doc.png", "Doc");
    loadTexture(textfieldTexture, "assets/textures/DMNMT/DMNMT_Textfield.png", "Textfield");
    loadTexture(madLecturerTexture, "assets/textures/DMNMT/DMNMT_Doc_Mad.png", "Mad Doc");
    loadTexture(progressTexture, "assets/textures/ProgressGlass/glass_empty.png", "ProgressBefore");
    loadTexture(progressTextureAfter, "assets/textures/ProgressGlass/glass_1.png", "ProgressAfter");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/DMNMT/Fortuna.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_fortuna.png", "FortunaCompleted");
    }
    else {
        loadTexture(playerTexture, "assets/textures/DMNMT/Hilarius.png", "Player");
        loadTexture(roomCompletedTexture, "assets/textures/Characters/Hurra_hilarius.png", "FortunaCompleted");
    }

    setupSprites();
    loadFont("assets/intro/arial.ttf");

    // load the text files
    riddleText = readFile("assets/textures/DMNMT/DocRiddle.txt");
    madLecturerText = readFile("assets/textures/DMNMT/DocMadRiddle.txt");
}

void DocRoom::playBackgroundMusic() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("InspirationalLoop.ogg", true);
}

void DocRoom::setupQuestionText(const string& text) {
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(300, 149);
    currentText.clear();
    questionIndex = 0;
    lineCount = 0;
    questionText.setString(currentText);
}

bool DocRoom::isCorrectAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 300 && pos.x <= 774 && pos.y >= 262 && pos.y <= 319);
}

bool DocRoom::isWrongAnswer(const sf::Vector2f& pos) {
    return (pos.x >= 300 && pos.x <= 996 && pos.y >= 185 && pos.y <= 262);
}

void DocRoom::handleCorrectAnswer() {
    game->enterRoom("MathRoom");
}

void DocRoom::update(float dt) {
    // If the line delay is active, wait for the line delay to finish
    if (lineDelayActive) {
        lineDelayTime += dt;
        if (lineDelayTime >= lineDelayDuration) {
            lineDelayActive = false;
            lineDelayTime = 0;
            currentText.clear();
            questionText.setString(currentText);
            displayTextLineByLineActive = true;
        }
        return;
    }
    // If the line delay is not active, display the text line by line
    if (displayTextLineByLineActive) {
        displayTextLineByLineTime += dt;
        if (displayTextLineByLineTime >= 0.05f) {
            displayTextLineByLineTime = 0;
            if (questionIndex < riddleText.size()) {
                char c = riddleText[questionIndex++];
                currentText += c;
                if (c == '\n') {
                    lineCount++;
                    // If the line count is 6, 12, or 18, stop displaying the text line by line
                    if (lineCount == 6 || lineCount == 12 || lineCount == 18) {
                        displayTextLineByLineActive = false;
                        lineDelayActive = true;
                        lineDelayTime = 0;
                    }
                }
                questionText.setString(currentText);
            }
            else {
                displayTextLineByLineActive = false;
                waitingForAnswer = true;
            }
        }
    }
}