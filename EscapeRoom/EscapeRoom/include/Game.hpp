#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <chrono>
#include "Intro.hpp"
#include "Outro.hpp"
#include "FinalRoom.hpp"    
#include "MainMenu.hpp"
#include "Highscore.hpp"
#include "CharacterSelection.hpp"
#include "Timer.hpp"
#include "GameOver.hpp"

class Outro; 
class FinalRoom;

enum class GameState {
    MainMenu,
    Highscore,
    Intro,
    InGame,
    Outro,
    GameOver
};

class Game {
public:
    Game();
    void run();
    void startNewGame();
    void chooseCharacter();
    void startIntro();
    void startOutro();
    void showHighscore();
    void enterRoom(const std::string& roomName);
    void returnToMainMenu();
    sf::RenderWindow& getWindow();
    std::string getChosenCharacter() const;
    Timer& getGlobalTimer();
    void setScore(int score);
    void setCurrentState(GameState state);

    // Bool flag setter für die Spielabschnitte
    void setCharacterChosen();
    void setIntroFinished();
    void setRoom1Finished();
    void setRoom2Finished();
    void setRoom3Finished();
    void setFinalRoomFinished();
    void setOutroFinished();

private:
    void handleInput(sf::Event& event);
    void update(float dt);
    void draw();

    sf::RenderWindow window;
    std::map<std::string, std::unique_ptr<FinalRoom>> rooms;
    FinalRoom* currentRoom;
    MainMenu mainMenu;
    Highscore highscore;
    Intro* intro;
    Outro* outro;
    GameOver* gameOver;
    CharacterSelection* characterSelection;
    GameState currentState;
    std::string chosenCharacter;
    int score;
    Timer globalTimer;

    // Boolean Flags für die verschiedenen Spielabschnitte
    bool isCharacterChosen;
    bool isIntroFinished;
    bool isRoom1Finished;
    bool isRoom2Finished;
    bool isRoom3Finished;
    bool isFinalRoomFinished;
    bool isOutroFinished;

    void resetGame();
};

#endif // GAME_HPP
