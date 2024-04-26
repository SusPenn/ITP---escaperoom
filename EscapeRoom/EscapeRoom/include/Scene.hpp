#ifndef SCENE_HPP
#define SCENE_HPP
//eventuell löschen
class Scene {
public:
    virtual ~Scene() {}
    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void handleInput() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;
};

#endif // SCENE_HPP
