#ifndef MATHROOM_HPP
#define MATHROOM_HPP

#include "Room.hpp"

class MATHRoom : public Room {
public:
    MATHRoom(Game* gameInstance) : Room(gameInstance) {}
    void playBackgroundMusic() override;
    void setupQuestionText(const std::string& text) override;
    bool isCorrectAnswer(const sf::Vector2f& pos) override;
    bool isWrongAnswer(const sf::Vector2f& pos) override;
    void handleCorrectAnswer() override;
    void loadAssets() override;
};

#endif // MATHROOM_HPP
