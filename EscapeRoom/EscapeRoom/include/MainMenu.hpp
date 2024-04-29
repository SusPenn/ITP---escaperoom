#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"
#include "Scene.hpp"
#include "Intro.hpp"
#include "AudioManager.hpp"
#include <iostream>
#include <vector>
#include "Intro.hpp"

class MainMenu : public Scene {
public:
    explicit MainMenu();
    //MainMenu(SoundManager& soundManager);
    void handleInput(sf::Event& event, sf::RenderWindow& window) override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    void activateButton();
    void enter() override;
    void exit() override;
    sf::Sprite getNewGameSprite() const;
    sf::Sprite getExitSprite() const;
    sf::Sprite getHighScoreSprite() const;


private:
    std::vector<Button> buttons;
    sf::Sprite menuSprite;
    sf::Sprite newGameSprite;
    sf::Sprite exitSprite;
    sf::Sprite highScoreSprite;
    sf::Texture menuTexture;
    sf::Texture newGameTexture;
    sf::Texture exitTexture;
    sf::Texture highScoreTexture;
    //SoundManager& soundManager;
};

#endif // MAINMENU_HPP
