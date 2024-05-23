#include "Game.hpp"
#include "ProzdRoom.hpp"
#include "DocRoom.hpp"
#include "MathRoom.hpp"
//#include "InfraRoom.hpp"
#include "CharacterSelection.hpp"

Game::Game()
    : window(sf::VideoMode(1280, 720), "Game Title"),
    currentRoom(nullptr),
    intro(nullptr),
    outro(nullptr),
    characterSelection(nullptr), //NEW
   
    chosenCharacter(""),
    score(0),
    globalTimer(600.0f),  // 10 Minuten
    currentState(GameState::MainMenu) {
    // Die anderen Raeume hier initialisieren
    rooms["DocRoom"] = std::make_unique<DocRoom>(this);  
    rooms["MathRoom"] = std::make_unique<MathRoom>(this); 
   // rooms["InfraRoom"] = std::make_unique<InfraRoom>(this);
    rooms["ProzdRoom"] = std::make_unique<ProzdRoom>(this);  
}

void Game::run() {
    sf::Clock clock;  // Initialize the clock here
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handleInput(event);
        }

        float dt = clock.restart().asSeconds(); 
        update(dt);
        draw();
    }
}

void Game::startNewGame() {
    chooseCharacter();
}

void Game::chooseCharacter() {
    // Charakterauswal in den chosenCharacter String speichern
    if (currentRoom) {
        currentRoom->exit(); 
    }
    currentRoom = nullptr; 
    characterSelection = std::make_unique<CharacterSelection>(this);
    currentState = GameState::CharacterSelection;
}
void Game::setChosenCharacter(const std::string& character) { 
    chosenCharacter = character;
    startIntro();
} 


void Game::startIntro() {
    if (currentRoom) {
        currentRoom->exit();
    }
    currentRoom = nullptr;
    currentState = GameState::Intro;
    intro = new Intro("assets/intro/intro.txt", window);
    intro->play(*this);
    delete intro;
    intro = nullptr;
    currentState = GameState::InGame;
    enterRoom("DocRoom");
}

void Game::startOutro() {
    if (currentRoom) {
        currentRoom->exit();
    }
    currentRoom = nullptr;
    currentState = GameState::Outro;
    outro = new Outro("assets/outro/outro.txt", window);
    outro->play(*this);
    delete outro;
    outro = nullptr;
    returnToMainMenu();
}

void Game::showHighscore() {
    if (currentRoom) {
        currentRoom->exit();
    }
    currentRoom = nullptr;
    currentState = GameState::Highscore;
    AudioManager::getInstance().playMusic("synthwave1.ogg", true);
}

void Game::enterRoom(const std::string& roomName) {
    auto it = rooms.find(roomName);
    if (it != rooms.end()) {
        if (currentRoom) {
            currentRoom->exit();
        }
        currentRoom = it->second.get();
        currentRoom->enter();
        currentState = GameState::InGame;
    }
    else {
        std::cerr << "Room " << roomName << " not found!" << std::endl;
    }
}

void Game::returnToMainMenu() {
    if (currentRoom) {
        currentRoom->exit();
    }
    resetGame();

    currentRoom = nullptr;
    currentState = GameState::MainMenu;
    AudioManager::getInstance().stopMusic();
    AudioManager::getInstance().setMusicVolume(100);
    AudioManager::getInstance().playMusic("synthwave1.ogg", true);
}

sf::RenderWindow& Game::getWindow() {
    return window;
}

void Game::handleInput(sf::Event& event) {
    if (currentState == GameState::MainMenu) {
        mainMenu.handleInput(event, window, *this);
    }
    else if (currentState == GameState::Highscore) {
        highscore.handleInput(event, window, *this);
    } 
    else if (currentState == GameState::CharacterSelection) {
        characterSelection->handleInput(event, window);
    }
    else if (currentState == GameState::InGame && currentRoom) {
        currentRoom->handleInput(event, window);
    }
}

void Game::update(float dt) {
    if (globalTimer.getIsTimeUp()) {
        currentState = GameState::GameOver;
    }
    
    if (currentState == GameState::InGame && currentRoom) {
        currentRoom->update(dt);
    }
    if (currentState == GameState::Outro && currentRoom) {
        setScore();
        startOutro();
	}

    if (currentState == GameState::GameOver) {
        // gameOver->update(dt);
    }
}

void Game::draw() {
    window.clear();
    if (currentState == GameState::MainMenu) {
        mainMenu.draw(window);
    }
    else if (currentState == GameState::Highscore) {
        highscore.draw(window);
    } 
    else if (currentState == GameState::CharacterSelection) {
        characterSelection->draw(window);
    }
    else if (currentState == GameState::InGame && currentRoom) {
        currentRoom->draw(window);
    }
    else if (currentState == GameState::GameOver) {
		// gameOver->draw(window);
	}
}

std::string Game::getChosenCharacter() const {
	return chosenCharacter;
}

Timer& Game::getGlobalTimer() {
	return globalTimer;
}

void Game::resetGame() {
    score = 0;
    globalTimer.resetTimer(600.0f);
}

void Game::setScore() {
    this->score = globalTimer.getScore();
}

void Game::setCurrentState(GameState state) {
	currentState = state;
}