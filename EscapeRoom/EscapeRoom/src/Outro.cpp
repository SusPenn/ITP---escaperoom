#include "Outro.hpp"

Outro::Outro(Game* gameInstance) :
    game(gameInstance),
    window(window), 
    skipButton(sf::Vector2f(100.f, 50.f), sf::Vector2f(1160.f, 650.f), sf::Color::Blue, "Skip", 20),
    returnToMainMenuButton(sf::Vector2f(100.f, 50.f), sf::Vector2f(1160.f, 650.f), sf::Color::Blue, "Skip", 20),
    doorButton(sf::Vector2f(220.f, 240.f), sf::Vector2f(215.f, 210.f), sf::Color::Transparent, "", 20)
    {
    returnToMainMenuButton.setVisibility(false);
    doorButton.setVisibility(false);

    loadAssets();
}

void Outro::loadAssets() {
    loadTexture(backgroundTexture, "assets/outro/outroBackground.png", "Background");
    loadTexture(spritzerStandTexture, "assets/outro/spritzerstand.png", "Spritzerstand");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/PROZD/Fortuna.png", "Player");
    }
    else {
        loadTexture(playerTexture, "assets/textures/PROZD/Hilarius.png", "Player");
    }

    setupSprites();
    loadFont("assets/outro/arial.ttf");
    setupOutroText();
}

void Outro::loadTexture(sf::Texture& texture, const string& filename, const string& name) {
    if (!texture.loadFromFile(filename)) {
        cerr << "Failed to load " << name << " texture from " << filename << endl;
    }
}

void Outro::loadFont(const string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        cerr << "Failed to load font from " << fontPath << endl;
    }
}

void Outro::setupSprites() {
	playerSprite.setTexture(playerTexture);
    backgroundSprite.setTexture(backgroundTexture);
    spritzerStandSprite.setTexture(spritzerStandTexture);
}

string Outro::readFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Failed to open file: " << filename << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    return content;
}

void Outro::setupOutroText() {
    outroText.setFont(font);
    outroText.setCharacterSize(24);
    outroText.setFillColor(sf::Color::White);
    outroText.setPosition(50.f, 50.f);
    outroText.setString(readFile("assets/outro/outro.txt"));
}

void Outro::play(Game& game) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(playerSprite);
    window.display();

    AudioManager::getInstance().playSoundEffect("SuccessSounds/SuccessFanfare.ogg");
    sf::sleep(sf::seconds(6));

    displayOverlay = true;

    // Den Text anzeigen lassen
    printSlowly(outroText, 50, outroText, backgroundSprite, window);

    // Nachdem die Textanzeige fertig ist, oder geskipped wurde, wird die Tür clickable gemacht
    doorButton.setVisibility(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (doorButton.getIsButtonVisible() && doorButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        loadNewImage();
                        AudioManager::getInstance().stopMusic();
                        return; // Nach dem Laden des neuen Bildes k�nnen wir zur�ckkehren, um eine weitere Verarbeitung zu vermeiden
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(playerSprite);
        if (doorButton.getIsButtonVisible()) {
            doorButton.draw(window); // Zeichne den Link-Bereich nur, wenn er sichtbar sein soll
        }
        window.draw(outroText);
        skipButton.draw(window);
        window.display();
    }
}

void Outro::printSlowly(const std::string& text, int delay, sf::Text& outroText, sf::Sprite& backgroundSprite, sf::RenderWindow& window) {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.setMusicVolume(100);
    audioManager.playMusic("keyboardTyping.ogg", true);

    string displayedText;
    int lineCount = 0;
    sf::Event event;
    bool skipRequested = false;

    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 220));

    for (size_t i = 0; i < text.length(); ++i) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (skipButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        skipRequested = true;
                        displayOverlay = false;
                        outroText.setString("");
                        skipButton.setVisibility(false); // Skip-Button unsichtbar machen
                        AudioManager::getInstance().playSoundEffect("Click.ogg"); // Skip-Sound abspielen
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                skipRequested = true;
                displayOverlay = false;
                outroText.setString("");
                skipButton.setVisibility(false); // Skip-Button unsichtbar machen
                AudioManager::getInstance().playSoundEffect("Click.ogg"); // Skip-Sound abspielen
            }
        }

        if (skipRequested) {
            break; // Beende die Schleife fr�hzeitig, wenn ein Skip geklickt wird
        }
        else {
            char c = text[i];
            displayedText += c;

            if (c == '\n' || i == text.length() - 1) {
                lineCount++;
                if (lineCount >= 13 || i == text.length() - 1) {
                    sf::sleep(sf::seconds(delay * 15));

                    window.clear();
                    window.draw(backgroundSprite);
                    window.draw(playerSprite);
                    outroText.setString(displayedText);
                    window.draw(outroText);
                    if (displayOverlay) {
                        window.draw(overlay);
                    }
                    window.display();

                    displayedText.clear();
                    lineCount = 0;
                }
            }
        }

        outroText.setString(displayedText);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(playerSprite);
        if (displayOverlay) {
            window.draw(overlay);
        }
        window.draw(outroText);
        skipButton.draw(window);
        window.display();

        sf::sleep(sf::seconds(delay));
    }

    audioManager.stopMusic();
    audioManager.setMusicVolume(10);
    audioManager.playMusic("Synthwave-002.ogg", true);
    // Sichergehen, dass linkVisible basierend darauf gesetzt wird, ob wir nat�rlich oder aufgrund eines Skips beendet haben
    doorButton.setVisibility(!skipRequested);
}

void Outro::loadNewImage() {
    AudioManager& audioManager = AudioManager::getInstance();
    audioManager.playSoundEffect("DoorOpen.ogg");
    sf::sleep(sf::milliseconds(1500));
    audioManager.setMusicVolume(100);

    window.clear();
    window.draw(spritzerStandSprite);
    returnToMainMenuButton.setVisibility(true);
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (returnToMainMenuButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        returnToMainMenuButton.setVisibility(false);
                        AudioManager::getInstance().playSoundEffect("Click.ogg");
                        return;
                    }
                }
            }
        }

        window.clear();
        window.draw(spritzerStandSprite);
        skipButton.draw(window);
        window.display();
    }
}