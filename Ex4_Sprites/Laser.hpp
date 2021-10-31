#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"
#include "AsteroidsGame.hpp"

class Laser : public GameObject, public Collidable 
{
public:
    Laser(const sre::Sprite& sprite, glm::vec2 Lposition, glm::vec2 direction, float rot, AsteroidsGame* game);
    void update(float deltaTime) override;
    void onCollision(std::shared_ptr<GameObject> other) override;

private:
    float rotationSpeed = 0.0f;
    glm::vec2 velocity;;
    glm::vec2 winSize;
    AsteroidsGame* ptr_AsteroidGame;
    float begin_time;
};


