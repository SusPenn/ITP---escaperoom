#include "Highscore.hpp"
#include "Game.hpp"

Highscore::Highscore() {
    loadAssets();
}

void Highscore::loadAssets() {
    if (!backgroundTexture.loadFromFile("assets/textures/MainMenu/MainMenu.png")) {
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
    }

    if (!highscoreTexture.loadFromFile("assets/textures/Highscore/Highscore.png")) {
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        highscoreSprite.setTexture(highscoreTexture);
    }

    if (!highscoreButtonTexture.loadFromFile("assets/textures/MainMenu/Highscore.png")) {
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        highscoreButtonSprite.setTexture(highscoreButtonTexture);
    }

    if (!exitButtonTexture.loadFromFile("assets/textures/MainMenu/Quit.png")) {
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        exitButtonSprite.setTexture(exitButtonTexture);
    }

    if (!newGameButtonTexture.loadFromFile("assets/textures/MainMenu/New_Game.png")) {
        cerr << "Failed to load game over background texture." << endl;
    }
    else {
        newGameButtonSprite.setTexture(newGameButtonTexture);
    }
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

            if (translated_pos.x >= 39 && translated_pos.x <= 361 && translated_pos.y >= 525 && translated_pos.y <= 575) {
                AudioManager::getInstance().playSoundEffect("Click.ogg");
                game.setCurrentState(GameState::MainMenu);
            }
        }
    }
}

void Highscore::loadHighscores() {
    ifstream highscoreFile("assets/highscore/highscore.txt");
    if(!highscoreFile) {
        cerr << "Failed to open highscore file." << endl;
        return;
    }

    string line;
    getline(highscoreFile, line);
    istringstream iss(line);
    string entry;

    while (getline(iss, entry, '|')) {
        istringstream entryStream(entry);
        string name;
        string score;

        getline(entryStream, name, ',');
        getline(entryStream, score);

        // Remove any leading/trailing whitespace
        name.erase(name.find_last_not_of(" \n\r\t") + 1);
        score.erase(score.find_last_not_of(" \n\r\t") + 1);

        int points = stoi(score);
        highscoreList.push_back(make_pair(name, points));
    }
    highscoreFile.close();

    // Sort the highscores in descending order
    sort(highscoreList.begin(), highscoreList.end(), []
            (const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Only keep the top 10 highscores
    if (highscoreList.size() > 10) {
        highscoreList.resize(10);
    }

    showHighscore();
}

void Highscore::showHighscore() {
    highscoreTexts.clear();
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        cerr << "Failed to load font." << endl;
    }

    float y = 105.0f; // Starting position
    int rank = 1;
    for (const auto& highscore : highscoreList) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(40);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setPosition(455.f, y);
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
    window.draw(newGameButtonSprite);
    window.draw(exitButtonSprite);
    window.draw(highscoreSprite);
    window.draw(highscoreButtonSprite);
    for (const auto& text : highscoreTexts) {
        window.draw(text);
    }
    window.display();
}
