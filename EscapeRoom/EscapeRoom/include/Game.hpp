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

using namespace std;

class Outro;
class Room;
class Intro;

enum class GameState {
    MainMenu,
    Highscore,
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
    void handleInput(sf::Event& event);
    void update(float dt);
    void draw();
    string getChosenCharacter() const;
    Timer& getGlobalTimer();
    void resetGame();
    void setScore();
    void setCurrentState(GameState state);
    void gameWon();

private:
    sf::RenderWindow window;
    Room* currentRoom;
    map<string, unique_ptr<Room>> rooms;
    unique_ptr<CharacterSelection> characterSelection;
    unique_ptr<Intro> intro; // Add intro as a unique_ptr
    unique_ptr<Outro> outro;
    string chosenCharacter;
    int score;
    Timer globalTimer;
    GameState currentState;
    MainMenu mainMenu;
    Highscore highscore;
};

#endif // GAME_HPP
