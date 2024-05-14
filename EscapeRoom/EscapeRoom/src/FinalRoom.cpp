//
// Created by Lukas Kalab on 11.05.24.
//

#include "FinalRoom.hpp"
FinalRoom::FinalRoom() {
    if (!finalRoomNiceRichterTexture.loadFromFile("assets/textures/Pictures/Prozedurale Sprachen Labor/Prozedurale Sprachen Labor+Richter+freundlich.png")) {
        std::cerr << "Failed to load Richter texture." << std::endl;
    }
    if (!finalRoomTextfieldTexture.loadFromFile("assets/textures/Pictures/Prozedurale Sprachen Labor/textfeld1.png")) {
        std::cerr << "Failed to load Textfield texture." << std::endl;
    }
    if (!playerTexture.loadFromFile("assets/textures/Pictures/Prozedurale Sprachen Labor/Fortuna.png")) {
        std::cerr << "Failed to load Player texture." << std::endl;
    }
    if (!finalRoomMadRichterTexture.loadFromFile("assets/textures/Pictures/Prozedurale Sprachen Labor/Prozedurale Sprachen Labor+Richter+unfreundlich.png")) {
        std::cerr << "Failed to load Player texture." << std::endl;
    }
    if (!font.loadFromFile("assets/intro/arial.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
        // Optionally handle error properly, e.g., by setting a flag or throwing an exception
    }

    // Musik abspielen
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("Kahoot.ogg", true);

    finalRoomTextfieldSprite.setTexture(finalRoomTextfieldTexture);
    finalRoomMadRichterSprite.setTexture(finalRoomMadRichterTexture);
    playerSprite.setTexture(playerTexture);
    finalRoomNiceRichterSprite.setTexture(finalRoomNiceRichterTexture);
    finalRoomTextfieldSprite.setScale(0.5, 0.5);
    finalRoomTextfieldSprite.setPosition(323, 450);
}

void FinalRoom::enter() {

}

void FinalRoom::exit() {

}

void FinalRoom::handleInput(sf::Event &event, sf::RenderWindow &window) {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        window.clear();
        window.draw(finalRoomNiceRichterSprite);
        window.draw(playerSprite);
        window.draw(finalRoomTextfieldSprite);
        window.draw(playerText);
        window.display();


    }
    displayQuestion("assets/textures/Pictures/Prozedurale Sprachen Labor/cRiddle.txt", window, playerFailedBool, finalRoomNiceRichterSprite);
}

void FinalRoom::update(float dt) {

}

void FinalRoom::draw(sf::RenderWindow &window) {
    window.draw(finalRoomNiceRichterSprite);
    window.draw(playerSprite);
    window.draw(finalRoomTextfieldSprite);
}

void FinalRoom::displayQuestion(std::string filename, sf::RenderWindow &window, bool playerFailed, sf::Sprite background) {
    std::string entireText;
    std::string line;
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Fehler beim oeffnen der Datei: " << filename << std::endl;
        return;
    }
    while (std::getline(inFile, line)) {
        entireText += line + "\n";
    }
    inFile.close();
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::Black);
    questionText.setPosition(357, 462);

    int lineCount = 0;
    int delay = 50;
    std::string displayedText;
    sf::Event event;

    for (size_t i = 0; i < entireText.length(); ++i) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        char c = entireText[i];
        displayedText += c;
        if (c == '\n') {
            lineCount++;
            if (lineCount == 5 || lineCount == 10) {
                // When 10 lines are reached, wait for a moment before clearing
                sleepMilliseconds(delay * 15);  // Longer pause at the end of the 10 lines

                window.clear();
                window.draw(background);
                window.draw(playerSprite);
                window.draw(finalRoomTextfieldSprite);
                window.display();  // Show the empty background briefly

                displayedText.clear();  // Clear the current text
                continue;
            }
            if (playerFailed) {
                if (lineCount == 15) {
                    // When 10 lines are reached, wait for a moment before clearing
                    sleepMilliseconds(delay * 15);  // Longer pause at the end of the 10 lines

                    window.clear();
                    window.draw(background);
                    window.draw(playerSprite);
                    window.draw(finalRoomTextfieldSprite);
                    window.display();  // Show the empty background briefly

                    displayedText.clear();  // Clear the current text
                    playerFailedBool = false;
                    continue;
                }
            }
        }
        questionText.setString(displayedText);

        window.clear();  // Clear previous frame
        window.draw(background);
        window.draw(playerSprite);
        window.draw(finalRoomTextfieldSprite);
        window.draw(questionText);  // Draw the updated text
        window.display();  // Display the current frame

        sleepMilliseconds(delay);
    }
    //hält window open
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    sf::Vector2f translated_pos = window.mapPixelToCoords(mouse_pos);
                    //std::cout << "Mouse x: " << translated_pos.x << " Mouse y: " << translated_pos.y << std::endl;
                    if (translated_pos.x >= 359 && translated_pos.x <= 416 && translated_pos.y >= 500 && translated_pos.y <= 514) {
                        //right answer
                        AudioManager::getInstance().playSoundEffect("SuccessSounds/LvlUp.ogg");
                        AudioManager::getInstance().stopMusic();
                        std::cout << "Richtige Antwort" << std::endl;
                        return;
                    }
                    if (translated_pos.x >= 359 && translated_pos.x <= 416 && translated_pos.y >= 528 && translated_pos.y <= 600) {
                        //wrong answer
                        AudioManager::getInstance().playSoundEffect("FailSounds/ComputerFail.ogg");
                        //display mad richter and mad text!
                        playerFailedBool = true;
                        displayQuestion("assets/textures/Pictures/Prozedurale Sprachen Labor/madRichterReply.txt", window, playerFailedBool, finalRoomMadRichterSprite);
                    }
                }
            }
        }
            window.clear();  // Clear previous frame
            window.draw(background);
            window.draw(playerSprite);
            window.draw(finalRoomTextfieldSprite);
            window.draw(questionText);  // Draw the updated text
            window.display();  // Display the current frame

    }
}

void FinalRoom::sleepMilliseconds(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
