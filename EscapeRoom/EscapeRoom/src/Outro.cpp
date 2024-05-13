#include "Outro.hpp"


Outro::Outro(const std::string& filename, sf::RenderWindow& window) :
    filename(filename), window(window), skipButton(window, font) {

    if (!font.loadFromFile("assets/outro/arial.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
    }

    linkArea.setSize(sf::Vector2f(220, 240)); 
    linkArea.setPosition(215, 210); 
    linkArea.setFillColor(sf::Color::Transparent);

}

void Outro::playSuccessMusic() {
    AudioManager::getInstance().playSoundEffect("SuccessSounds/SuccessFanfare.ogg");
}

void Outro::play() {
    
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/outro/outroBackground.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return;
    }

    sf::Sprite backgroundSprite(backgroundTexture);

    /* ToDo player auswahl if male or female */

    if (!girlTexture.loadFromFile("assets/outro/girl.png")) {
        std::cerr << "Failed to load girl image!" << std::endl;
        return;

    }
    girlSprite.setTexture(girlTexture);

    window.clear();
    window.draw(backgroundSprite);
    window.draw(girlSprite);
    window.draw(linkArea);
    window.display();

    playSuccessMusic();

    sleepMilliseconds(2000); 
   
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to load file: " << filename << std::endl;
        return;
    }

    std::string entireText;
    std::string line;
    while (std::getline(inFile, line)) {
        entireText += line + "\n";
    }
    inFile.close();

    sf::Text outroText;
    outroText.setFont(font);
    outroText.setCharacterSize(24);
    outroText.setFillColor(sf::Color::White);
    outroText.setPosition(50.f, 50.f);

    skipButton.setPosition(window);

    displayOverlay = true;

    printSlowly(entireText, 50, outroText, backgroundSprite, window);  

}

void Outro::printSlowly(const std::string& text, int delay, sf::Text& outroText, sf::Sprite& backgroundSprite, sf::RenderWindow& window) {
    AudioManager::getInstance().setMusicVolume(100);
    AudioManager::getInstance().playMusic("keyboardTyping.ogg", true);

    std::string displayedText;
    int lineCount = 0;
    sf::Event event;
    bool skipRequested = false;
    bool endOfTextReached = false;

    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));  
    overlay.setFillColor(sf::Color(0, 0, 0, 220));

    for (size_t i = 0; i < text.length(); ++i) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    if (isSkipButtonClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        skipRequested = true;
                        displayOverlay = false; 
                        linkVisible = true; //door area

                    }
                    if (linkVisible && isLinkClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        loadNewImage(); 
                    }    
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                skipRequested = true;
                displayOverlay = false;
            }
        }

        if (skipRequested) {

            displayedText.clear();
            window.clear(); 
            window.draw(backgroundSprite);
            window.draw(girlSprite); 
            if (linkVisible) {
                window.draw(linkArea);
            }
            window.display();
        }
        else {
            char c = text[i];
            displayedText += c;

            if (c == '\n' || i == text.length() - 1)  {
                lineCount++;
                if (lineCount >= 13 || i == text.length() - 1) {
                    
                    sleepMilliseconds(delay * 15);  

                    window.clear();
                    window.draw(backgroundSprite);
                    window.draw(girlSprite);
                    outroText.setString(displayedText); 
                    window.draw(outroText);
                    if (displayOverlay) {
                        window.draw(overlay);
                    }
                    if (linkVisible) {
                        window.draw(linkArea); 
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
        /* TODO */
        window.draw(girlSprite); 
        if (displayOverlay) {  
            window.draw(overlay);  
        }
        if (linkVisible) {
            window.draw(linkArea); 
        }
        window.draw(outroText);  
        skipButton.draw();  
        window.display();  

        sleepMilliseconds(delay);  // Pause for effect between characters
    }
    if (!skipRequested) { 
        linkVisible = true;
        displayOverlay = false;
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (linkVisible && isLinkClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        loadNewImage(); 
                    }
                }
            }
            window.clear();
            window.draw(backgroundSprite);
            window.draw(girlSprite);
            window.draw(linkArea);
            window.display();
        }
    }

    AudioManager::getInstance().stopMusic();
}

// Outro BUTTON

bool Outro::isSkipClicked(sf::Event& event) {
    return (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape);
}

bool Outro::isSkipButtonClicked(sf::Vector2f clickPosition) {
    return skipButton.isClicked(clickPosition);
}

bool Outro::isLinkClicked(sf::Vector2f clickPosition) { // NEW: Funktion zur Überprüfung des Link-Klicks
    return linkVisible && linkArea.getGlobalBounds().contains(clickPosition);
}

void Outro::sleepMilliseconds(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

Outro::SkipButton::SkipButton(sf::RenderWindow& window, sf::Font& font) :
    window(window), buttonShape(sf::Vector2f(100.f, 50.f)), buttonText() {
    buttonShape.setFillColor(sf::Color::Blue);
    buttonText.setFont(font);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setString("Skip");
}

void Outro::SkipButton::draw() {
    window.draw(buttonShape);
    window.draw(buttonText);
}

void Outro::SkipButton::setPosition(sf::RenderWindow& window) {
    buttonShape.setPosition(window.getSize().x - buttonShape.getSize().x - 20.f, window.getSize().y - buttonShape.getSize().y - 20.f);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setPosition(
        buttonShape.getPosition().x + (buttonShape.getSize().x - textRect.width) / 2.f - textRect.left,
        buttonShape.getPosition().y + (buttonShape.getSize().y - textRect.height) / 2.f - textRect.top
    );
}

bool Outro::SkipButton::isClicked(sf::Vector2f clickPosition) {
    return buttonShape.getGlobalBounds().contains(clickPosition);
}


void Outro::loadNewImage() {
    displayOverlay = false; // Stoppe die Anzeige des Textes
    if (!spritzerStandTexture.loadFromFile("assets/outro/spritzerstand.png")) {
        std::cerr << "Failed to load new image!" << std::endl;
        return;
    }
    spritzerStandSprite.setTexture(spritzerStandTexture);
    window.clear();
    window.draw(spritzerStandSprite);
    window.display();

    bool windowOpen = true;
    while (windowOpen) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                windowOpen = false; 
            }
        }
    }
}