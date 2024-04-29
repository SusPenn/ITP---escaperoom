#include "EscapeRoom.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "MainMenu.hpp"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Spritzer through the looking glass", sf::Style::Close | sf::Style::Titlebar);


    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if (evnt.text.unicode < 128) {
                        std::cout << static_cast<char>(evnt.text.unicode);
                    }
                    break;
            }
        }
        MainMenu mainMenu = MainMenu();

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
        sf::Vector2f translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
        if(mainMenu.getNewGameSprite().getGlobalBounds().contains(translated_pos)) { // Rectangle-contains-point check
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                mainMenu.handleInput();
                std::cout << "Left mouse button is pressed" << std::endl;
            }
        }

        window.clear(sf::Color::White);
        mainMenu.draw(window);
        window.display();
    }
    
    return 0;
}