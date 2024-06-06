#ifndef ENGROOM_HPP
#define ENgROOM_HPP

#include "Room.hpp"

class EngRoom : public Room {
public:
    EngRoom(Game* gameInstance) : Room(gameInstance) {}
    void playBackgroundMusic() override;
    void setupQuestionText(const std::string& text) override;
    bool isCorrectAnswer(const sf::Vector2f& pos) override;
    bool isWrongAnswer(const sf::Vector2f& pos) override;
    void handleCorrectAnswer() override;
    void loadAssets() override;
};

#endif // ENgROOM_HPP
