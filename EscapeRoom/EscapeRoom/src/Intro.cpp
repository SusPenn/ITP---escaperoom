#include "Intro.hpp"
#include "game.hpp"

Intro::Intro(const std::string& filename, sf::RenderWindow& window) :
    filename(filename), window(window), skipButton(window, font) {
    if (!font.loadFromFile("assets/intro/arial.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
        // Optionally handle error properly, e.g., by setting a flag or throwing an exception
    }
}

void Intro::play(Game& game) {
    AudioManager::getInstance().playMusic("keyboardTyping.ogg", true);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/intro/introBackground.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        AudioManager::getInstance().stopMusic();
        return;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        AudioManager::getInstance().stopMusic();
        return;
    }

    std::string entireText;
    std::string line;
    while (std::getline(inFile, line)) {
        entireText += line + "\n";
    }

    sf::Text introText;
    introText.setFont(font);
    introText.setCharacterSize(24);
    introText.setFillColor(sf::Color::Green);
    introText.setPosition(50.f, 50.f);

    skipButton.setPosition(window);

    printSlowly(entireText, 50, introText, backgroundSprite, window);
    AudioManager::getInstance().stopMusic();
    game.setIntroFinished();
}

void Intro::printSlowly(const std::string& text, int delay, sf::Text& introText, sf::Sprite& backgroundSprite, sf::RenderWindow& window) {
    std::string displayedText;
    int lineCount = 0;
    sf::Event event;
    bool skipRequested = false;

    for (size_t i = 0; i < text.length(); ++i) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return; // Exit the function if the window is closed
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (isSkipButtonClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        AudioManager::getInstance().playSoundEffect("Click.ogg");
                        AudioManager::getInstance().stopMusic();
                        skipRequested = true;
                        break; // Exit the event loop and set skipRequested
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                AudioManager::getInstance().stopMusic();
                skipRequested = true;
                break; // Exit the event loop and set skipRequested
            }
        }

        if (skipRequested) {
            break; // Exit the text processing loop if skipRequested is true
        }

        char c = text[i];
        displayedText += c;

        if (c == '\n') {
            lineCount++;
            if (lineCount == 13) {
                sleepMilliseconds(delay * 15);
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
        skipButton.draw();
        window.display();

        sleepMilliseconds(delay);
    }
}

bool Intro::isSkipClicked(sf::Event& event) {
    return (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);
}

bool Intro::isSkipButtonClicked(sf::Vector2f clickPosition) {
    return skipButton.isClicked(clickPosition);
}

void Intro::sleepMilliseconds(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

Intro::SkipButton::SkipButton(sf::RenderWindow& window, sf::Font& font) :
    window(window), buttonShape(sf::Vector2f(100.f, 50.f)), buttonText() {
    buttonShape.setFillColor(sf::Color::Blue);
    buttonText.setFont(font);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setString("Skip");
}

void Intro::SkipButton::draw() {
    window.draw(buttonShape);
    window.draw(buttonText);
}

void Intro::SkipButton::setPosition(sf::RenderWindow& window) {
    buttonShape.setPosition(window.getSize().x - buttonShape.getSize().x - 20.f, window.getSize().y - buttonShape.getSize().y - 20.f);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setPosition(
        buttonShape.getPosition().x + (buttonShape.getSize().x - textRect.width) / 2.f - textRect.left,
        buttonShape.getPosition().y + (buttonShape.getSize().y - textRect.height) / 2.f - textRect.top
    );
}

bool Intro::SkipButton::isClicked(sf::Vector2f clickPosition) {
    return buttonShape.getGlobalBounds().contains(clickPosition);
}