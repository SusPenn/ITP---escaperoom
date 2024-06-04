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

    // den Hintergrund an den Text anpassen
    adjustBackgroundToText();
}

Timer::~Timer() {
    // Bereinigung kann hier behandelt werden, falls notwendig
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
            pause(); // Pausiere automatisch, wenn der Countdown null erreicht
        }

        // Konvertiere die aktuelle Zeit in Sekunden zu Minuten und Sekunden
        int totalSeconds = static_cast<int>(currentTime);
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;

        // Formatieren der Zeit als MM:SS
        std::ostringstream timeStream;
        timeStream << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;

        // Aktualisiere den Timer-Text
        timerText.setString(timeStream.str());
        // Passe die Größe und Position des Hintergrunds basierend auf dem neuen Text an
        adjustBackgroundToText();
    }
}

void Timer::draw(sf::RenderWindow& window) const {
    window.draw(background);
    window.draw(timerText);
}
/*
bool Timer::getIsTimeUp() const {
    if (countdownTime == 0.0f) {
        return true;
    }
    else {
        return false;
    }
}*/

bool Timer::getIsTimeUp() const {
    float remainingTime = countdownTime - (elapsedTime + clock.getElapsedTime().asSeconds());
    return remainingTime <= 0; 
}

void Timer::adjustBackgroundToText() {
    // Hole das umgebende Rechteck des Textes
    sf::FloatRect textBounds = timerText.getLocalBounds();

    // Setze die Größe des Hintergrunds mit etwas Abstand um den Text
    background.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20));

    // Zentriere den Text innerhalb des Hintergrunds
    timerText.setPosition(
        background.getPosition().x + (background.getSize().x - textBounds.width) / 2.0f - textBounds.left,
        background.getPosition().y + (background.getSize().y - textBounds.height) / 2.0f - textBounds.top
    );
}

int Timer::getScore() const {
    // Berechne die verbleibende Zeit in Sekunden
    float remainingTime = countdownTime - (elapsedTime + clock.getElapsedTime().asSeconds());

    // Verhindere negative Werte
    if (remainingTime < 0) {
        remainingTime = 0;
    }

    // Konvertiere die verbleibende Zeit zu einer Ganzzahl in Sekunden
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