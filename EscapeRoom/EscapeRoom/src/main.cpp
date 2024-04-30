#include "EscapeRoom.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "MainMenu.hpp"
#include "AudioManager.hpp"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Spritzer through the looking glass", sf::Style::Close | sf::Style::Titlebar);

    MainMenu mainMenu;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
                if (event.text.unicode < 128) {
                    std::cout << static_cast<char>(event.text.unicode);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Handle input within the event loop
                    mainMenu.handleInput(event, window);
                }
                break;
            }
        }

        window.clear(sf::Color::White);
        mainMenu.draw(window);
        window.display();

        //Show position of mouse in console on left mouse button click
        /*sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::Vector2f translated_pos = window.mapPixelToCoords(mouse_pos);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Mouse x: " << translated_pos.x << " Mouse y: " << translated_pos.y << std::endl;
            }
        }*/
    }

    return 0;
}