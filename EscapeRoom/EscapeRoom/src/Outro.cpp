#include "Outro.hpp"

Outro::Outro(Game* gameInstance) :
    game(gameInstance),
    skipButton(sf::Vector2f(100.f, 50.f), sf::Vector2f(1160.f, 650.f), sf::Color::Blue, "Skip", 20),
    returnToMainMenuButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(1060.f, 650.f), sf::Color::Blue, "Back to Main Menu", 20),
    doorButton(sf::Vector2f(220.f, 240.f), sf::Vector2f(215.f, 210.f), sf::Color::Transparent, "", 20),
    overlay(sf::Vector2f(1280, 720)),
    currentIndex(0),
    lineCount(0),
    displayTextLineByLineTime(0.0f),
    outroTextFinished(false),
    lineDelayTime(0.0f),
    lineDelayActive(false),
    lineDelayDuration(3.0f),
    displayOverlay(false),
    showScore(false),
    showCredits(false),
    creditsPositionY(720.f)
{
    skipButton.setVisibility(false);
    returnToMainMenuButton.setVisibility(false);
    doorButton.setVisibility(false);
    overlay.setFillColor(sf::Color(0, 0, 0, 220));
}

void Outro::enter() {
    loadAssets();

    game->getWindow().clear();
    game->getWindow().draw(backgroundSprite);
    game->getWindow().display();

    AudioManager::getInstance().playSoundEffect("SuccessSounds/SuccessFanfare.ogg");
    sf::sleep(sf::seconds(6));
    displayOverlay = true;
    skipButton.setVisibility(true);
    AudioManager::getInstance().setMusicVolume(100);
    AudioManager::getInstance().playMusic("keyboardTyping.ogg", true);
}

void Outro::exit() {
    returnToMainMenuButton.setVisibility(false);
    doorButton.setVisibility(false);
    displayOverlay = false;
    skipButton.setVisibility(false);
    outroText.setString("");
    skipButton.setVisibility(false);
    doorButton.setVisibility(false);
    returnToMainMenuButton.setVisibility(false);
    game->returnToMainMenu();
}

void Outro::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);

    if (displayOverlay) {
        window.draw(overlay);
    }
    if (!outroTextFinished) {
        window.draw(outroText);
    }

    if (skipButton.getIsButtonVisible()) {
        skipButton.draw(window);
    }

    if (doorButton.getIsButtonVisible()) {
        doorButton.draw(window);
    }

    if(showScore) {
		window.draw(scoreTextfieldSprite);
		window.draw(scoreText);
	}

    if(showCredits) {
        window.draw(outroCreditsSprite);
    }

    if (returnToMainMenuButton.getIsButtonVisible()) {
        returnToMainMenuButton.draw(window);
    }

    window.display();
}

void Outro::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        window.close();
        exit();
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (skipButton.getIsButtonVisible() && skipButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                displayTextFinished();
            }
            else if (doorButton.getIsButtonVisible() && doorButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                doorButton.setVisibility(false);
                AudioManager::getInstance().playSoundEffect("DoorOpen.ogg");
                toTheSpritzer();
            }
            else if (returnToMainMenuButton.getIsButtonVisible() && returnToMainMenuButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                returnToMainMenuButton.setVisibility(false);
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                exit();
            }
        }
    }
}

void Outro::update(float dt) {
    if (!outroTextFinished) {
        if (lineDelayActive) {
            lineDelayTime += dt;
            if (lineDelayTime >= lineDelayDuration) {
                lineDelayActive = false;
                lineDelayTime = 0.0f;
                displayedText.clear();
                outroText.setString(displayedText);
                lineCount = 0;
                AudioManager::getInstance().setMusicVolume(100);
                AudioManager::getInstance().playMusic("keyboardTyping.ogg", true);
            }
            return;
        }
        displayText(dt);
    }

    if (showCredits) {
        if(creditsPositionY > 0.f) {
			creditsPositionY -= 0.2;
			outroCreditsSprite.setPosition(0.f, creditsPositionY);
		}
    }
}

void Outro::displayText(float dt) {
    displayTextLineByLineTime += dt;
    if (displayTextLineByLineTime >= 0.05f && currentIndex < entireText.length()) {
        displayTextLineByLineTime = 0.0f;
        char c = entireText[currentIndex++];
        displayedText += c;

        if (c == '\n') {
            lineCount++;
            if (lineCount == 13) {  // Delay nach 13 Zeilen
                lineDelayActive = true;
                lineDelayTime = 0.0f;
                return;
            }
        }

        outroText.setString(displayedText);
    }
    else if (currentIndex >= entireText.length() && !lineDelayActive) {
        sf::sleep(sf::seconds(3));
        displayTextFinished(); // Wenn der Text fertig ist, wird die Funktion aufgerufen
    }
}

void Outro::loadAssets() {
    loadTexture(backgroundTexture, "assets/outro/outroBackground.png", "Background");
    loadTexture(spritzerStandTexture, "assets/outro/spritzerstand.png", "Spritzerstand");
    loadTexture(outroCreditsTexture, "assets/outro/outroCredits.png", "Credits");
    loadTexture(scoreTextfieldTexture, "assets/outro/scoreTextfield.png", "ScoreTextfield");

    if (game->getChosenCharacter() == "Fortuna") {
        loadTexture(playerTexture, "assets/textures/PROZD/Fortuna.png", "Player");
    }
    else {
        loadTexture(playerTexture, "assets/textures/PROZD/Hilarius.png", "Player");
    }

    setupSprites();
    loadFont("assets/outro/arial.ttf");
    setupOutroText();
    setupScoreText();
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
    outroCreditsSprite.setTexture(outroCreditsTexture);
    scoreTextfieldSprite.setTexture(scoreTextfieldTexture);
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
    entireText = readFile("assets/outro/outro.txt");
    displayedText.clear(); // Ensure displayedText is clear before starting
    outroText.setString(displayedText); // Initially set to empty string
}

void Outro::setupScoreText() {
    scoreText.setFont(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(550.f, 70.f);
    scoreText.setString("Score: " + to_string(game->getScore()));
}

void Outro::displayTextFinished() {
    displayedText.clear();
    outroText.setString(displayedText);
    outroTextFinished = true;
    skipButton.setVisibility(false);
    displayOverlay = false;
    doorButton.setVisibility(true);
    AudioManager::getInstance().stopMusic();
    AudioManager::getInstance().setMusicVolume(10);
    AudioManager::getInstance().playMusic("Synthwave-002.ogg", true);
}

void Outro::toTheSpritzer() {
    backgroundSprite = spritzerStandSprite;
    doorButton.setVisibility(false);
    showScore = true;
    showCredits = true;
    outroCreditsSprite.setPosition(0.f, creditsPositionY);
    AudioManager::getInstance().playSoundEffect("DoorOpen.ogg");
    sf::sleep(sf::milliseconds(1500));
    AudioManager::getInstance().setMusicVolume(100);
    returnToMainMenuButton.setVisibility(true);
}