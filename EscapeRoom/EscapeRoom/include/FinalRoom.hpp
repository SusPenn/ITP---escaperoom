//
// Created by Lukas Kalab on 11.05.24.
//

#ifndef ESCAPEROOM_FINALROOM_HPP
#define ESCAPEROOM_FINALROOM_HPP

#include <SFML/Graphics.hpp>
#include <AudioManager.hpp>
#include <vector>
#include <fstream>
#include "Riddle.hpp"
#include "Timer.hpp"
#include "Scene.hpp"
#include <chrono>
#include <thread>


class FinalRoom : public Scene {
public:
    FinalRoom();
    void enter() override;
    void exit() override;
    void handleInput(sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    void displayQuestion(std::string filename, sf::RenderWindow &window, bool playerFailed, sf::Sprite background);
    static void sleepMilliseconds(int milliseconds);

private:
    sf::Texture finalRoomNiceRichterTexture;
    sf::Sprite finalRoomNiceRichterSprite;
    sf::Texture finalRoomMadRichterTexture;
    sf::Sprite finalRoomMadRichterSprite;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Texture finalRoomTextfieldTexture;
    sf::Sprite finalRoomTextfieldSprite;
    std::vector<Riddle> riddles;
    sf::String playerInput;
    sf::Text playerText;
    sf::Text questionText;
    sf::Font font;
    std::string textFileToOpen;
    bool playerFailedBool = false;
    //Timer finalRoomTimer;
};


#endif //ESCAPEROOM_FINALROOM_HPP
