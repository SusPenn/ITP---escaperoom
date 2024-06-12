#include "Highscore.hpp"
#include "Game.hpp"

Highscore::Highscore() :
    returnToMenuButton(sf::Vector2f(200.f, 50.f), sf::Vector2f(1040.f, 650.f),
                       sf::Color(0, 100, 156), "Hauptmenue", 20)
   {
    if (!backgroundTexture.loadFromFile("assets/textures/Highscore/Highscore.png")) {
        std::cerr << "Failed to load game over background texture." << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
    }


    AudioManager::getInstance().playMusic("synthwave1.ogg", true);
    std::cout << "Playing GameOver music." << std::endl;
}


void Highscore::handleInput(sf::Event& event, sf::RenderWindow& window, Game& game) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f translated_pos = window.mapPixelToCoords(mouse_pos);
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            cout << "Mouse x: " << translated_pos.x << " Mouse y: " << translated_pos.y << endl;
            sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);

            if (returnToMenuButton.isClicked(clickPosition)) {
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                game.returnToMainMenu();

            }
        }
    }
}

void Highscore::loadHighscores() {
    std::ifstream highscoreFile("assets/highscore/highscore.txt");
    if(!highscoreFile) {
        std::cerr << "Failed to open highscore file." << std::endl;
        return;
    }

    std::string line;
    std::getline(highscoreFile, line);
    std::istringstream iss(line);
    std::string entry;

    while (std::getline(iss, entry, '|')) {
        std::istringstream entryStream(entry);
        std::string name;
        std::string score;

        std::getline(entryStream, name, ',');
        std::getline(entryStream, score);

        // Remove any leading/trailing whitespace
        name.erase(name.find_last_not_of(" \n\r\t") + 1);
        score.erase(score.find_last_not_of(" \n\r\t") + 1);

        int points = std::stoi(score);
        highscoreList.push_back(std::make_pair(name, points));
    }
    highscoreFile.close();

    // Sort the highscores in descending order
    std::sort(highscoreList.begin(), highscoreList.end(), []
            (const auto& a, const auto& b) {
        return a.second > b.second;
    });
    showHighscore();
}

void Highscore::showHighscore() {
    highscoreTexts.clear();
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    float y = 80.0f; // Starting position
    int rank = 1;
    for (const auto& highscore : highscoreList) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(40);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Black);
        text.setPosition(314.f, y);
        text.setString(std::to_string(rank) + ". " + highscore.first + " : " + std::to_string(highscore.second));
        highscoreTexts.push_back(text);

        rank++;
        y += 40.f;
    }
}

void Highscore::resetHighscores() {
    highscoreList.clear();
}


void Highscore::update(float dt) {
    // Update logic if needed
}


void Highscore::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);
    returnToMenuButton.draw(window);
    for (const auto& text : highscoreTexts) {
        window.draw(text);
    }
    window.display();
}
