#ifndef KOKOROOM_HPP
#define KOKOROOM_HPP

#include "Room.hpp"

class KokoRoom : public Room {
public:
    KokoRoom(Game* gameInstance) : Room(gameInstance) {}
    void playBackgroundMusic() override;
    void setupQuestionText(const std::string& text) override;
    bool isCorrectAnswer(const sf::Vector2f& pos) override;
    bool isWrongAnswer(const sf::Vector2f& pos) override;
    void handleCorrectAnswer() override;
    void loadAssets() override;
};

#endif // KOKOROOM_HPP
