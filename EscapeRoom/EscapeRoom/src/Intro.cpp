#include "Intro.hpp"
#include "AudioManager.hpp"

Intro::Intro(Game* gameInstance) :
    game(gameInstance), 
    filename("assets/intro/intro.txt"),
    skipButton(sf::Vector2f(100.f, 50.f), sf::Vector2f(1160.f, 650.f), sf::Color::Blue, "Skip", 20),
    losButton(sf::Vector2f(200.f, 100.f), sf::Vector2f(520.f, 460.f), sf::Color::Green, "LOS!", 40),
    currentIndex(0),
    displayTextLineByLineTime(0.0f), 
    lineCount(0), 
    lineDelayActive(false), 
    lineDelayTime(0.0f), 
    lineDelayDuration(3.0f),
    losButtonActive(false){
}

void Intro::loadAssets() {
    if (!font.loadFromFile("assets/intro/arial.ttf")) {
        cerr << "Failed to load font from " << filename << endl;
    }
    if (!backgroundTexture.loadFromFile("assets/intro/introBackground.png")) {
        cerr << "Failed to load background image!" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Failed to open file: " << filename << endl;
    }
    else {
        string line;
        while (getline(inFile, line)) {
            entireText += line + "\n";
        }
    }
    introText.setFont(font);
    introText.setCharacterSize(24);
    introText.setFillColor(sf::Color::Green);
    introText.setPosition(50.f, 50.f);
}

void Intro::enter() {
    loadAssets();
    currentIndex = 0;
    displayedText.clear();
    displayTextLineByLineTime = 0.0f;
    lineCount = 0;
    lineDelayActive = false;
    lineDelayTime = 0.0f;
    AudioManager::getInstance().playMusic("keyboardTyping.ogg", true);
}

void Intro::exit() {
    cout << "Exiting intro" << endl;
    AudioManager::getInstance().stopMusic();
    game->enterRoom("DocRoom");
}

void Intro::handleInput(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Closed) {
        window.close();
        exit();
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);

        if (skipButton.isClicked(clickPosition)) {
            AudioManager::getInstance().playSoundEffect("Click.ogg");
            exit();
        }

        if (losButtonActive && losButton.isClicked(clickPosition)) {
            AudioManager::getInstance().playSoundEffect("Teleport.ogg");
            exit();
        }
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        AudioManager::getInstance().stopMusic();
        exit(); // Call the exit function when the Escape key is pressed
    }
}

void Intro::update(float dt) {
    if (lineDelayActive) {
        AudioManager::getInstance().stopMusic();
        lineDelayTime += dt;
        if (lineDelayTime >= lineDelayDuration) {
            lineDelayActive = false;
            lineDelayTime = 0.0f;
            displayedText.clear();
            introText.setString(displayedText);
            lineCount = 0;
            AudioManager::getInstance().setMusicVolume(100);
            AudioManager::getInstance().playMusic("keyboardTyping.ogg", true);
        }
        return;
    }

    displayText(dt);
}

void Intro::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(introText);
    skipButton.draw(window);

    if(losButtonActive) {
		losButton.draw(window);
	}

    window.display();
}

void Intro::displayText(float dt) {
    displayTextLineByLineTime += dt;
    if (displayTextLineByLineTime >= 0.05f && currentIndex < entireText.length()) {
        displayTextLineByLineTime = 0.0f;
        char c = entireText[currentIndex++];
        displayedText += c;

        if (c == '\n') {
            lineCount++;
            if (lineCount == 13) {
                lineDelayActive = true;
                lineDelayTime = 0.0f;
            }
        }

        introText.setString(displayedText);

        if (currentIndex >= entireText.length() && !lineDelayActive) {
            AudioManager::getInstance().stopMusic();
            losButtonActive = true;
        }
    }
}