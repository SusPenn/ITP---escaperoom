#ifndef ROOM_HPP
#define ROOM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Riddle.hpp"
#include "Timer.hpp"
#include "Scene.hpp"

class Room : public Scene {
public:
    void enter() override;
    void exit() override;
    void handleInput(sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;

private:
    sf::Texture backgroundTexture;
    std::vector<Riddle> riddles;
    Timer roomTimer;
};

#endif // ROOM_HPP
