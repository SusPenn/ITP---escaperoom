#include "Intro.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Es geht um nix!");
    window.setFramerateLimit(60);  // Limit the frame rate for smoother animations

    // Intro implementation
    std::string introFileName = "assets/intro/intro.txt";
    Intro intro(introFileName, window);
    intro.play();  // Play the intro sequence


    return 0;
}