#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"
#include "Asteroid.hpp"
#include "AsteroidsGame.hpp"
#include <vector>

class SpaceShip : public GameObject, public Collidable  {
public:
    SpaceShip(const sre::Sprite &sprite, AsteroidsGame* prt_game );
    SpaceShip(const sre::Sprite& sprite, AsteroidsGame* game, glm::vec2 pos);

    void update(float deltaTime) override;
    void onCollision(std::shared_ptr<GameObject> other) override;
    void onKey(SDL_Event &keyEvent) override;


private:
    bool rotateCW = false;
    bool rotateCCW = false;
    bool thrust = false;
    bool fire = false;

    AsteroidsGame* ptr_AsteroidGame;

    float drag = 0.80f;
    float maxSpeed = 350.0f;
    float thrustPower = 250.0f;
    float rotationSpeed = 250.0f;
    glm::vec2 velocity;
    glm::vec2 winSize;
    glm::vec2 directionL;

};


