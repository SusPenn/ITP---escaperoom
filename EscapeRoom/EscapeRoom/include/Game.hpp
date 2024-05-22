#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <chrono>
#include "Intro.hpp"
#include "Outro.hpp"
#include "Room.hpp" 
#include "MainMenu.hpp"
#include "Highscore.hpp"
#include "CharacterSelection.hpp"
#include "Timer.hpp"
#include "GameOver.hpp"

class Outro;
class Room;

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
    void setScore();
    void setCurrentState(GameState state);

private:
    void handleInput(sf::Event& event);
    void update(float dt);
    void draw();
    void resetGame();

    sf::RenderWindow window;
    std::map<std::string, std::unique_ptr<Room>> rooms;
    Room* currentRoom;
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
};

#endif // GAME_HPP
