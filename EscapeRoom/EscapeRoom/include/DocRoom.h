#ifndef ESCAPEROOM_DOCROOM_H
#define ESCAPEROOM_DOCROOM_H

#include "Room.hpp"

class DocRoom: public Room{
    public:
        DocRoom(Game* gameInstance) : Room(gameInstance) {}
        void playBackgroundMusic() override;
        void setupQuestionText(const std::string& text) override;
        bool isCorrectAnswer(const sf::Vector2f& pos) override;
        bool isWrongAnswer(const sf::Vector2f& pos) override;
        void handleCorrectAnswer() override;
        void loadAssets() override;
};


#endif //ESCAPEROOM_DOCROOM_H
