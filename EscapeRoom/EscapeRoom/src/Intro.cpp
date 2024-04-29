#include "Intro.hpp"

Intro::Intro(const std::string& filename, sf::RenderWindow& window) :
    filename(filename), window(window), skipButton(window, font) {
    if (!font.loadFromFile("assets/intro/arial.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
        // Optionally handle error properly, e.g., by setting a flag or throwing an exception
    }
}

void Intro::play() {
    AudioManager::getInstance().playMusic("synthwave1.ogg", true);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/intro/introBackground.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Fehler beim Öffnen der Datei: " << filename << std::endl;
        return;
    }

    std::string entireText;
    std::string line;
    while (std::getline(inFile, line)) {
        entireText += line + "\n";
    }
    inFile.close();

    sf::Text introText;
    introText.setFont(font);
    introText.setCharacterSize(24);
    introText.setFillColor(sf::Color::Green);
    introText.setPosition(50.f, 50.f);

    skipButton.setPosition(window);

    // Now call printSlowly instead of manually looping through the text here
    printSlowly(entireText, 50, introText, backgroundSprite, window);
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
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (isSkipButtonClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        skipRequested = true;
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                skipRequested = true;
            }
        }

        if (skipRequested) {
            break; // Exit the loop if skip is requested
        }

        char c = text[i];
        displayedText += c;

        if (c == '\n') {
            lineCount++;
            if (lineCount == 13) {
                // When 10 lines are reached, wait for a moment before clearing
                sleepMilliseconds(delay * 10);  // Longer pause at the end of the 10 lines

                window.clear();
                window.draw(backgroundSprite);
                window.display();  // Show the empty background briefly

                displayedText.clear();  // Clear the current text
                lineCount = 0;  // Reset line count
                continue;
            }
        }

        introText.setString(displayedText);

        window.clear();  // Clear previous frame
        window.draw(backgroundSprite);  // Draw the background
        window.draw(introText);  // Draw the updated text
        skipButton.draw();  // Draw the skip button
        window.display();  // Display the current frame

        sleepMilliseconds(delay);  // Pause for effect between characters
    }
    AudioManager::getInstance().stopMusic();
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
