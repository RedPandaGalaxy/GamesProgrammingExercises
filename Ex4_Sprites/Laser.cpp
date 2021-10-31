#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "Laser.hpp"
#include "sre/Renderer.hpp"
#include "iostream"
#include "AsteroidsGame.hpp"
#include "GameObject.hpp"
#include "SpaceShip.hpp"
#include "Asteroid.hpp"
#include <time.h>

Laser::Laser(const sre::Sprite& sprite, glm::vec2 Lposition, glm::vec2 direction, float rot, AsteroidsGame* game) : 
    GameObject(sprite), ptr_AsteroidGame(game)
{
    scale = glm::vec2(0.5f, 0.5f);
    position = Lposition;
    rotation = rot;
    velocity = direction;
    begin_time = 0.0f;

   // std::time_t result = std::time(nullptr);

    winSize = sre::Renderer::instance->getDrawableSize();
    radius = 23;  
}

void Laser::update(float deltaTime) {


    begin_time += deltaTime;
    if (begin_time >= 1.5f) {
        //delete object
        ptr_AsteroidGame->DestroyLaser(this);
    }

    // wrap around
    if (position.x < 0){
        position.x += winSize.x;
    } else if (position.x > winSize.x){
        position.x -= winSize.x;
    }
    if (position.y < 0){
        position.y += winSize.y;
    } else if (position.y > winSize.y){
        position.y -= winSize.y;
    }
   // std:: cout << "v: " << velocity.x << " "<< velocity.y << std::endl;
    ///std::cout << " pos : " << position.y << " ---------------- " << std::endl;
    position += velocity * deltaTime;
}

void Laser::onCollision(std::shared_ptr<GameObject> other) {
    if (std::dynamic_pointer_cast<Asteroid>(other) != nullptr) 
    {
        //collision with an asteroid
        ptr_AsteroidGame->DestroyLaser(this);
    }
}

