#include "Timer.hpp"

Timer::Timer(float initialTime)
    : countdownTime(initialTime), isPaused(true), elapsedTime(0.0f) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Fehler beim Laden der Schriftart von " << fontPath << std::endl;
    }

    timerText.setFont(font);
    timerText.setCharacterSize(characterSize);
    timerText.setFillColor(sf::Color::White);
    timerText.setString("00:00");

    background.setFillColor(sf::Color(128, 128, 128));
    background.setPosition(610, 25);

    adjustBackgroundToText();
}

Timer::~Timer() {
    // use if needed
}

void Timer::start() {
    if (isPaused) {
        isPaused = false;
        clock.restart();
    }
}

void Timer::pause() {
    if (!isPaused) {
        elapsedTime += clock.getElapsedTime().asSeconds();
        isPaused = true;
    }
}

void Timer::update() {
    if (!isPaused) {
        float currentTime = countdownTime - (elapsedTime + clock.getElapsedTime().asSeconds());
        if (currentTime < 0) {
            currentTime = 0;
            pause(); // pause when timer hits 0
        }

        // convert time to MM:SS
        int totalSeconds = static_cast<int>(currentTime);
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;

        // format time as MM:SS
        std::ostringstream timeStream;
        timeStream << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;

        // update the timer
        timerText.setString(timeStream.str());
        adjustBackgroundToText();
    }
}

void Timer::draw(sf::RenderWindow& window) const {
    window.draw(background);
    window.draw(timerText);
}

bool Timer::getIsTimeUp() const {
    float remainingTime = countdownTime - (elapsedTime + clock.getElapsedTime().asSeconds());
    return remainingTime <= 0; 
}

void Timer::adjustBackgroundToText() {
    // get the bounding rectangle of the text
    sf::FloatRect textBounds = timerText.getLocalBounds();
    // set the size of the background with some padding around the text
    background.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20));

    //center the text inside the background
    timerText.setPosition(
        background.getPosition().x + (background.getSize().x - textBounds.width) / 2.0f - textBounds.left,
        background.getPosition().y + (background.getSize().y - textBounds.height) / 2.0f - textBounds.top
    );
}

int Timer::getScore() const {
    //calculate remaining Time in seconds
    float remainingTime = countdownTime - (elapsedTime + clock.getElapsedTime().asSeconds());

    // prevent negative values
    if (remainingTime < 0) {
        remainingTime = 0;
    }

    // convert remaining time to score
    return static_cast<int>(remainingTime);
}

void Timer::resetTimer(float time) {
    elapsedTime = 0;
  //  countdownTime = 600.0f; 
    countdownTime = time;  // TEST_TIMER
    isPaused = true;  
   // timerText.setString("00:30");  // TEST_TIMER
    timerText.setString("10:00");  
    adjustBackgroundToText();
}