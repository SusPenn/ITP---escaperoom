#include "Intro.hpp"

Intro::Intro(const std::string& filename, sf::RenderWindow& window) :
    filename(filename), window(window), skipButton(window, font) {
    if (!font.loadFromFile("assets/intro/arial.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
        // Optionally handle error properly, e.g., by setting a flag or throwing an exception
    }
}

void Intro::play() {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Fehler beim Öffnen der Datei: " << filename << std::endl;
        return;
    }

    sf::Text introText("", font, 24);
    introText.setFillColor(sf::Color::Green);
    introText.setPosition(50.f, 50.f);

    skipButton.setPosition(window);

    sf::Event event;
    while (window.isOpen() && !skipRequested) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (isSkipClicked(event) || isSkipButtonClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                skipRequested = true;
            }
        }

        std::string line;
        if (std::getline(inFile, line)) {
            printSlowly(line + "\n", 50, introText); // Now passing introText
            window.display();
        }
        else {
            break;
        }
    }

    inFile.close();
}

void Intro::printSlowly(const std::string& text, int delay, sf::Text& introText) {
    std::string displayedText;
    for (char c : text) {
        displayedText += c;
        introText.setString(displayedText);
        window.clear();
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
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonShape.setPosition(window.getSize().x - buttonShape.getSize().x - 20.f, window.getSize().y - buttonShape.getSize().y - 20.f);
    buttonText.setPosition(buttonShape.getPosition().x + (buttonShape.getSize().x - textRect.width) / 2.f, buttonShape.getPosition().y + (buttonShape.getSize().y - textRect.height) / 2.f);
}

bool Intro::SkipButton::isClicked(sf::Vector2f clickPosition) {
    return buttonShape.getGlobalBounds().contains(clickPosition);
}
