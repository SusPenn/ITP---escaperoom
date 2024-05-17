#ifndef ROOM_HPP
#define ROOM_HPP

#include <SFML/Graphics.hpp>
#include "Timer.hpp"

class Game;  // Forward declaration

class Room {
public:
    virtual ~Room() = default;
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void handleInput(sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

protected:
    sf::Texture niceLecturerTexture;
    sf::Texture madLecturerTexture;
    sf::Texture playerTexture;
    sf::Texture textfieldTexture;
    sf::Texture roomCompletedTexture;

    sf::Sprite niceLecturerSprite;
    sf::Sprite madLecturerSprite;
    sf::Sprite playerSprite;
    sf::Sprite textfieldSprite;
    sf::Sprite roomCompletedSprite;
    sf::Sprite background;

    sf::Font font;
    sf::Text questionText;
    sf::Text playerText;
    bool playerFailedBool = false;
    bool roomCompleted = false;

    Game* game;  // Assuming Game class is declared in Game.hpp

    bool isRoomCompleted() const;

    void pollEvent(sf::RenderWindow& window, sf::Event& event);
};

#endif // ROOM_HPP
