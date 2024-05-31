#ifndef WEBROOM_HPP
#define WEBROOM_HPP

#include "Room.hpp"

class WebRoom : public Room {
public:
    WebRoom(Game* gameInstance) : Room(gameInstance) {}
    void playBackgroundMusic() override;
    void setupQuestionText(const std::string& text) override;
    bool isCorrectAnswer(const sf::Vector2f& pos) override;
    bool isWrongAnswer(const sf::Vector2f& pos) override;
    void handleCorrectAnswer() override;
    void loadAssets() override;
};

#endif // WEBROOM_HPP