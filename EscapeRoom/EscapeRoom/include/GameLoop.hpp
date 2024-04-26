#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "SoundManager.hpp"

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

    void initialize();
    void run();
    void handleEvents();
    void update(float deltaTime);
    void render();
    void changeScene(Scene* scene);
    void shutdown();

private:
    sf::RenderWindow window;
    Scene* currentScene;
    SoundManager soundManager;
};

#endif // GAMELOOP_HPP