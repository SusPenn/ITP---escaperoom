#include "Intro.hpp"
#include "Game.hpp"

Intro::Intro(const string& filename, sf::RenderWindow& window) :
    filename(filename), window(window), skipButton(sf::Vector2f(100.f, 50.f), sf::Vector2f(window.getSize().x - 120.f, window.getSize().y - 70.f), sf::Color::Blue, "Skip", 20) {
    if (!font.loadFromFile("assets/intro/arial.ttf")) {
        cerr << "Fehler beim Laden der Schriftart!" << endl;

    }
}

void Intro::play(Game& game) {
    AudioManager::getInstance().playMusic("keyboardTyping.ogg", true);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/intro/introBackground.png")) {
        cerr << "Failed to load background image!" << endl;
        AudioManager::getInstance().stopMusic();
        return;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Failed to open file: " << filename << endl;
        AudioManager::getInstance().stopMusic();
        return;
    }

    string entireText;
    string line;
    while (getline(inFile, line)) {
        entireText += line + "\n";
    }

    sf::Text introText;
    introText.setFont(font);
    introText.setCharacterSize(24);
    introText.setFillColor(sf::Color::Green);
    introText.setPosition(50.f, 50.f);

    printSlowly(entireText, 50, introText, backgroundSprite, window);
    AudioManager::getInstance().stopMusic();
}

void Intro::printSlowly(const string& text, int delay, sf::Text& introText, sf::Sprite& backgroundSprite, sf::RenderWindow& window) {
    string displayedText;
    int lineCount = 0;
    bool skipRequested = false;

    for (size_t i = 0; i < text.length(); ++i) {
        processEvents(window, skipRequested);

        if (skipRequested) {
            break; // Exit the text processing loop if skipRequested is true
        }

        char c = text[i];
        displayedText += c;

        if (c == '\n') {
            lineCount++;
            if (lineCount == 13) {
                sleepMilliseconds(delay * 40);
                window.clear();
                window.draw(backgroundSprite);
                window.display();

                displayedText.clear();
                lineCount = 0;
                continue;
            }
        }

        introText.setString(displayedText);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(introText);
        skipButton.draw(window);
        window.display();

        sleepMilliseconds(delay);
    }
}

void Intro::processEvents(sf::RenderWindow& window, bool& skipRequested) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            skipRequested = true;
            return;
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (skipButton.isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                AudioManager::getInstance().stopMusic();
                skipRequested = true;
                return;
            }
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            AudioManager::getInstance().stopMusic();
            skipRequested = true;
            return;
        }
    }
}

void Intro::sleepMilliseconds(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}