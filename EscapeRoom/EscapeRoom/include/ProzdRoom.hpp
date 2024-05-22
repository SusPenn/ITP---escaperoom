#ifndef FINALROOM_HPP
#define FINALROOM_HPP

#include "Room.hpp"

class ProzdRoom : public Room {
public:
    ProzdRoom(Game* gameInstance) : Room(gameInstance) {}
    void playBackgroundMusic() override;
    void setupQuestionText(const std::string& text) override;
    bool isCorrectAnswer(const sf::Vector2f& pos) override;
    bool isWrongAnswer(const sf::Vector2f& pos) override;
    void handleCorrectAnswer() override;
    void loadAssets() override;
};

#endif // FINALROOM_HPP
