#ifndef INFRAROOM_HPP
#define INFRAROOM_HPP

#include "Room.hpp"

class InfraRoom : public Room {
public:
    InfraRoom(Game* gameInstance) : Room(gameInstance) {}
    void playBackgroundMusic() override;
    void setupQuestionText(const std::string& text) override;
    bool isCorrectAnswer(const sf::Vector2f& pos) override;
    bool isWrongAnswer(const sf::Vector2f& pos) override;
    void handleCorrectAnswer() override;
    void loadAssets() override;
};

#endif // INFRAROOM_HPP
