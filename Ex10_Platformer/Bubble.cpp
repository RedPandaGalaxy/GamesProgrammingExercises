//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#include <iostream>
#include <SDL_events.h>
#include "Bubble.hpp"
#include "GameObject.hpp"
#include <sre/Inspector.hpp>
#include "sre/RenderPass.hpp"
#include "SpriteComponent.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "PhysicsComponent.hpp"
#include "PlatformerGame.hpp"


Bubble::Bubble(GameObject *gameObject) : Component(gameObject) {
    bubblePhysics = gameObject->addComponent<PhysicsComponent>();

    auto physicsScale = PlatformerGame::instance->physicsScale;
    radius = 10 / physicsScale;
    bubblePhysics->initCircle(
        b2_dynamicBody, 10 / physicsScale, 
        { gameObject->getPosition().x / physicsScale,
          gameObject->getPosition().y / physicsScale }, 
        1);
    spriteComponent = gameObject->getComponent<SpriteComponent>();
}


void Bubble::SpawnBubble(BubbleSize size, glm::vec2 pos) {
    std::cout << "Spawn smaller bubble!" << std::endl;
    //auto asteroidBigSprite = atlas->get("meteorBrown_big4.png");
    //auto asteroidMediumSprite = atlas->get("meteorBrown_med3.png");
    //auto asteroidSmallSprite = atlas->get("meteorBrown_small2.png");

    //if (size == Asteroid::L) {
    //    gameObjects.push_back(std::make_shared<Asteroid>(asteroidBigSprite, this, Asteroid::L, pos));
    //}
    //if (size == Asteroid::M) {
    //    gameObjects.push_back(std::make_shared<Asteroid>(asteroidMediumSprite, this, Asteroid::M, pos));
    //}
    //if (size == Asteroid::S) {
    //    gameObjects.push_back(std::make_shared<Asteroid>(asteroidSmallSprite, this, Asteroid::S, pos));
    //}
}

bool Bubble::onKey(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        std::cout << "Bubble Split!" << std::endl;
    }
    return false;
}

void Bubble::onCollisionStart(PhysicsComponent* comp) {
    std::cout << "Bubble Collided with something" << std::endl;
}

void Bubble::onCollisionEnd(PhysicsComponent* comp) {

}


