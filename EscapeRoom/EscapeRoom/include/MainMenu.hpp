#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"
#include "Scene.hpp"

class MainMenu : public Scene {
public:
    explicit MainMenu();
    //MainMenu(SoundManager& soundManager);
    void handleInput() override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    void activateButton();
    void enter() override;
    void exit() override;
    sf::Sprite getNewGameSprite() const;
    sf::Sprite getQuidSprite() const;
    sf::Sprite getHighScoreSprite() const;


private:
    std::vector<Button> buttons;
    sf::Sprite menuSprite;
    sf::Sprite newGameSprite;
    sf::Sprite quidSprite;
    sf::Sprite highScoreSprite;
    //SoundManager& soundManager;
};

#endif // MAINMENU_HPP
