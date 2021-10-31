#pragma once

#include <vector>
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "Asteroid.hpp"

class GameObject;

class AsteroidsGame {
public:
    AsteroidsGame();
    void FireLaser(glm::vec2 pos, float rot, glm::vec2 direction);
    void DestroyLaser(GameObject*  laserRay);
    void DestroyAsteroid(GameObject* asteroid);
    void DestroyShip(GameObject* spaceship, glm::vec2 pos);
    void SpawnAsteroid(Asteroid::asteroidSize sizeToSpawn, glm::vec2 pos);

private:
    void update(float deltaTime);
    void render();
    void keyEvent(SDL_Event &event);
    void AsteroidsGame::DetectCollision();
    void RestartGame();
    void SpawnManager();
   
    sre::Camera camera;
    sre::SDLRenderer r;
    std::shared_ptr<sre::SpriteAtlas> atlas;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    bool debugCollisionCircles = false;
    bool isGameOn = true;
    int score = 0;
};


