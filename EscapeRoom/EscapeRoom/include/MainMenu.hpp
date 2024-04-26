#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"
//#include "SoundManager.hpp"
#include "Scene.hpp"

class MainMenu : public Scene {
public:
    MainMenu(SoundManager& soundManager);
    void handleInput() override;
    void update(float dt) override;
    void draw() override;
    void activateButton();

private:
    std::vector<Button> buttons;
    sf::Sprite backgroundSprite;
  //  SoundManager& soundManager;
};

#endif // MAINMENU_HPP
