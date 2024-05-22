#include "Game.hpp"
#include "FinalRoom.hpp"
#include "DocRoom.h"

Game::Game()
    : window(sf::VideoMode(1280, 720), "Game Title"),
    currentRoom(nullptr),
    intro(nullptr),
    outro(nullptr),
    chosenCharacter(""),
    score(0),
    globalTimer(600.0f),  // 10 Minuten
    isCharacterChosen(false),
    isIntroFinished(false),
    isRoom1Finished(false),
    isRoom2Finished(false),
    isRoom3Finished(false),
    isFinalRoomFinished(false),
    isOutroFinished(false),
    currentState(GameState::MainMenu) {
    // Die anderen R�ume hier initialisieren
    rooms["DocRoom"] = std::make_unique<FinalRoom>(this);  // Game instanz an FinalRoom �bergeben
    rooms["FinalRoom"] = std::make_unique<FinalRoom>(this);  // Game instanz an FinalRoom �bergeben
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
    if (isCharacterChosen) {
        startIntro();
    }
    // andere R�ume hier einf�gen
    if (isIntroFinished) {
        std::cout << "Hier rein gekommen" << std::endl;
        globalTimer.start();
        enterRoom("DocRoom");
    }
    //Room one finished
    if (isRoom1Finished) {
        enterRoom("FinalRoom");
    }
    // Nach dem Outro wieder zur�ck ins mainMenu?
}

void Game::chooseCharacter() {
    // Charakterauswal in den chosenCharacter String speichern
    chosenCharacter = "Fortuna";
    setCharacterChosen();
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
    isIntroFinished = true;
    currentState = GameState::InGame;
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
	isCharacterChosen = false;
	isIntroFinished = false;
	isRoom1Finished = false;
	isRoom2Finished = false;
	isRoom3Finished = false;
	isFinalRoomFinished = false;
    isOutroFinished = false;
    score = 0;
    globalTimer.resetTimer(600.0f);
}

void Game::setScore(int score) {
	this->score = score;
}

void Game::setCurrentState(GameState state) {
	currentState = state;
}

void Game::setCharacterChosen() {
	isCharacterChosen = true;
}

void Game::setIntroFinished() {
	isIntroFinished = true;
}

void Game::setRoom1Finished() {
	isRoom1Finished = true;
}

void Game::setRoom2Finished() {
	isRoom2Finished = true;
}

void Game::setRoom3Finished() {
	isRoom3Finished = true;
}

void Game::setFinalRoomFinished() {
	isFinalRoomFinished = true;
}

void Game::setOutroFinished() {
	isOutroFinished = true;
}