#include "Timer.hpp"

Timer::Timer(float initialTime)
    : countdownTime(initialTime), isPaused(true), elapsedTime(0.0f) {
    // Überprüfe, ob die Schriftart korrekt geladen wird
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Fehler beim Laden der Schriftart von " << fontPath << std::endl;
    }

    timerText.setFont(font);
    timerText.setCharacterSize(characterSize);
    timerText.setFillColor(sf::Color::White);

    // Initialisiere die Position und den String, um die richtigen Dimensionen zu messen
    timerText.setString("00:00");
    timerText.setPosition(50, 50);  // Anfängliche Position, später anpassen

    // Richte das Hintergrund-Rechteck ein, Abmessungen werden unten angepasst
    background.setFillColor(sf::Color(128, 128, 128));  // Graue Farbe
    background.setPosition(95, 95);  // Anfängliche Position, später anpassen

    // Passe die anfängliche Größe und Position basierend auf dem Text an
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

void Timer::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(timerText);
}

bool Timer::getIsTimeUp() const {
    return elapsedTime + clock.getElapsedTime().asSeconds() >= countdownTime;
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