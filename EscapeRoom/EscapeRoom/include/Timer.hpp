#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <iomanip> 
#include <sstream>

using namespace std;

class Timer {
public:
    Timer(float initialTime);
    ~Timer();
    void start();
    void pause();
    void update();
    void draw(sf::RenderWindow& window) const;
    void adjustBackgroundToText();
    bool getIsTimeUp() const;
    int getScore() const;
    void resetTimer(float time);

private:
    sf::Clock clock;
    sf::Text timerText;
    sf::Font font;
    sf::RectangleShape background;
    string fontPath = "assets/fonts/arial.ttf";
    int characterSize = 40;
    float countdownTime;
    float elapsedTime;
    bool isPaused;
};

#endif // TIMER_HPP
