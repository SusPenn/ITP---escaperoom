#include "Game.hpp"
#include "ProzdRoom.hpp"
#include "InfraRoom.hpp"
#include "DocRoom.hpp"
#include "MathRoom.hpp"
#include "WebRoom.hpp"
#include "CharacterSelection.hpp"

Game::Game()
    : window(sf::VideoMode(1280, 720), "Game Title"),
    currentRoom(nullptr),
    chosenCharacter(""),
    score(0),
    globalTimer(600.0f),
   // globalTimer(10.0f),  // TEST TIME
    currentState(GameState::MainMenu) {
    initializeRooms();
    gameOver = std::make_unique<GameOver>(this); // NEW
}

void Game::initializeRooms() {
    characterSelection = make_unique<CharacterSelection>(this);
    intro = make_unique<Intro>(this);
    outro = make_unique<Outro>(this);
    // Die anderen Raeume hier initialisieren
    rooms["DocRoom"] = make_unique<DocRoom>(this);
    rooms["MathRoom"] = make_unique<MathRoom>(this);
    rooms["InfraRoom"] = make_unique<InfraRoom>(this);
    rooms["WebRoom"] = make_unique<WebRoom>(this);
    rooms["ProzdRoom"] = make_unique<ProzdRoom>(this);
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

    currentState = GameState::CharacterSelection;

}

void Game::setChosenCharacter(const string& character) { 
    chosenCharacter = character;
    intro->enter();
} 

void Game::showHighscore() {
    if (currentRoom) {
        currentRoom->exit();
    }
    currentRoom = nullptr;
    currentState = GameState::Highscore;
    AudioManager::getInstance().playMusic("synthwave1.ogg", true);
}

void Game::enterRoom(const string& roomName) {
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
    else if (currentState == GameState::Intro) {
		intro->handleInput(event, window);
	}
    else if (currentState == GameState::InGame && currentRoom) {
        currentRoom->handleInput(event, window);
    }
	else if (currentState == GameState::Outro) {
        outro->handleInput(event, window);
        }
    else if (currentState == GameState::GameOver) {
		 gameOver->handleInput(event, window);
	}
}

void Game::update(float dt) {

    globalTimer.update(); // NEW: Timer-Update
    if (globalTimer.getIsTimeUp()) {
        currentState = GameState::GameOver;
        gameOver->enter(); 
    }


    if (currentState == GameState::Intro) {
        intro->update(dt);
    }
    if (currentState == GameState::InGame && currentRoom) {
        currentRoom->update(dt);
    }
    if (currentState == GameState::Outro) {
        outro->update(dt);
	}
    if (currentState == GameState::GameOver) { 
        gameOver->update(dt);
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
    else if(currentState == GameState::Intro) {
		intro->draw(window);
	}
    else if (currentState == GameState::InGame && currentRoom) {
        currentRoom->draw(window);
    }
    else if (currentState == GameState::Outro) {
		outro->draw(window);
	}
    else if (currentState == GameState::GameOver) {
		 gameOver->draw(window); 
	}
}

string Game::getChosenCharacter() const {
	return chosenCharacter;
}

void Game::gameWon() {
    currentState = GameState::Outro;
    outro->enter();
}

Timer& Game::getGlobalTimer() {
	return globalTimer;
}

void Game::resetGame() {
    score = 0;
    globalTimer.resetTimer(600.0f);
    chosenCharacter = "";

    rooms.clear();
    currentRoom = nullptr;

    initializeRooms();
}

void Game::setScore() {
    this->score = globalTimer.getScore();
}

int Game::getScore() const {
	return score;
}

void Game::setCurrentState(GameState state) {
	currentState = state;
}