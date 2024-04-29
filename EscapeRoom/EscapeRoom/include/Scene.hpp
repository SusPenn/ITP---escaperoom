#ifndef SCENE_HPP
#define SCENE_HPP
//eventuell l�schen
class Scene {
public:
    virtual ~Scene() {}
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void handleInput(sf::Vector2f translated_pos, sf::RenderWindow &window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

#endif // SCENE_HPP
