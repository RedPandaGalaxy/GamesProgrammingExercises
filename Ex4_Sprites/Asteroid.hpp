#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"

class Asteroid : public GameObject, public Collidable  {
public:
    enum asteroidSize { S, M, L };
    Asteroid(const sre::Sprite& sprite, AsteroidsGame* game, asteroidSize size);
    Asteroid::Asteroid(const sre::Sprite& sprite, AsteroidsGame* game, asteroidSize size, glm::vec2 pos);

    void update(float deltaTime) override;
    void onCollision(std::shared_ptr<GameObject> other) override;
private:
   
    asteroidSize size;
    bool rotateCW = false;
    float rotationSpeed = 100.0f;
    glm::vec2 velocity = { 50.0f, 12.2f };
    glm::vec2 winSize;

    AsteroidsGame* ptr_AsteroidGame;




};


