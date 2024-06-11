// Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <string>
#include "Intro.hpp"
#include "Outro.hpp"
#include "Room.hpp" 
#include "MainMenu.hpp"
#include "Highscore.hpp"
#include "CharacterSelection.hpp"
#include "Timer.hpp"
#include "GameOver.hpp"
#include "SetHighscore.hpp"

using namespace std;

class Outro;
class Room;
class Intro;
class GameOver;

enum class GameState {
    MainMenu,
    Highscore,
    SetHighscore,
    Intro,
    InGame,
    Outro,
    GameOver,
    CharacterSelection
};

class Game {
public:
    Game();
    void run();
    void startNewGame();
    void setChosenCharacter(const string& character);
    void showHighscore();
    void enterRoom(const string& roomName);
    void returnToMainMenu();
    sf::RenderWindow& getWindow();
    string getChosenCharacter() const;
    Timer& getGlobalTimer();
    void resetGame();
    void setScore();
    int getScore() const;
    void setCurrentState(GameState state);
    void gameWon();
    void setNewHighscore();

private:
    void handleInput(sf::Event& event);
    void update(float dt);
    void draw();
    void initializeRooms();
    sf::RenderWindow window;
    Room* currentRoom;
    map<string, unique_ptr<Room>> rooms;
    unique_ptr<CharacterSelection> characterSelection;
    unique_ptr<Intro> intro; // Add intro as a unique_ptr
    unique_ptr<Outro> outro;
    unique_ptr<GameOver> gameOver;
    string chosenCharacter;
    int score;
    Timer globalTimer;
    GameState currentState;
    MainMenu mainMenu;
    Highscore highscore;
    SetHighscore setHighscore;
};

#endif // GAME_HPP
