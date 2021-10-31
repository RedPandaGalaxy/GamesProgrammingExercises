#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "sre/Renderer.hpp"
#include "iostream"
#include "AsteroidsGame.hpp"
#include "GameObject.hpp"
#include "SpaceShip.hpp"
#include "Asteroid.hpp"
#include "Laser.hpp"

Asteroid::Asteroid(const sre::Sprite &sprite, AsteroidsGame* game, asteroidSize size) :
    GameObject(sprite), ptr_AsteroidGame(game), size(size) {
    scale = glm::vec2(0.5f,0.5f);
    winSize = sre::Renderer::instance->getDrawableSize();
    if(size == Asteroid::L)
        radius = 23;
    if (size == Asteroid::M)
        radius = 15;
    if (size == Asteroid::S)
        radius = 8;

    float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    //position =winSize *x;
    position = {  rand() % ((int)winSize.x), rand() % ((int)winSize.y) };

    //std::cout << "x: " << position.x << " y: " << position.y << std::endl;
    velocity = glm::vec2(rand() % (100), rand() % (100));

}
Asteroid::Asteroid(const sre::Sprite& sprite, AsteroidsGame* game, asteroidSize size, glm::vec2 pos) :
    GameObject(sprite), ptr_AsteroidGame(game), size(size) {
    scale = glm::vec2(0.5f, 0.5f);
    winSize = sre::Renderer::instance->getDrawableSize();
    if (size == Asteroid::L)
        radius = 23;
    if (size == Asteroid::M)
        radius = 15;
    if (size == Asteroid::S)
        radius = 8;

    float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    //position =winSize *x;
    position = pos;

    //std::cout << "x: " << position.x << " y: " << position.y << std::endl;
    velocity = glm::vec2(rand() % (100), rand() % (100));

}
void Asteroid::update(float deltaTime) {

    position += velocity * deltaTime; 
    rotation -= deltaTime * rotationSpeed;


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
}

void Asteroid::onCollision(std::shared_ptr<GameObject> other) {
    if (std::dynamic_pointer_cast<Laser>(other) != nullptr)
    {
        //collision with an asteroid
        ptr_AsteroidGame->DestroyLaser(other.get());
        if (size == Asteroid::L) {
            ptr_AsteroidGame->SpawnAsteroid(Asteroid::M, position);
            ptr_AsteroidGame->SpawnAsteroid(Asteroid::M, position);
        }
        if (size == Asteroid::M) {
            ptr_AsteroidGame->SpawnAsteroid(Asteroid::S, position);
            ptr_AsteroidGame->SpawnAsteroid(Asteroid::S, position);
        }
        ptr_AsteroidGame->DestroyAsteroid(this);
    }
}
