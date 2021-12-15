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

void Bubble::SetBubbleSize(BubbleSize s) {
    bubblePhysics = gameObject->addComponent<PhysicsComponent>();
    size = s;
    density = 50;
    auto physicsScale = PlatformerGame::instance->physicsScale;



    switch (size)
    {
    case BubbleSize::XS:
        bubblePhysics->initCircle(
            b2_dynamicBody, 10 / physicsScale,
            { gameObject->getPosition().x / physicsScale,
              gameObject->getPosition().y / physicsScale },
            density
            );
        bubblePhysics->setLinearVelocity((glm::vec2(6, 0)));
        break;
    case BubbleSize::S:
        bubblePhysics->initCircle(
            b2_dynamicBody, 15 / physicsScale,
            { gameObject->getPosition().x / physicsScale,
              gameObject->getPosition().y / physicsScale },
            density
        );
        bubblePhysics->setLinearVelocity((glm::vec2(4, 0)));
        break;
    case BubbleSize::M:
        bubblePhysics->initCircle(
            b2_dynamicBody, 20 / physicsScale,
            { gameObject->getPosition().x / physicsScale,
              gameObject->getPosition().y / physicsScale },
            density
        );
        bubblePhysics->setLinearVelocity((glm::vec2(2, 0)));
        break;
    case BubbleSize::L:
        bubblePhysics->initCircle(
            b2_dynamicBody, 25 / physicsScale,
            { gameObject->getPosition().x / physicsScale,
              gameObject->getPosition().y / physicsScale },
            density
        );
        break;
    case BubbleSize::XL:
        bubblePhysics->initCircle(
            b2_dynamicBody, 30 / physicsScale,
            { gameObject->getPosition().x / physicsScale,
              gameObject->getPosition().y / physicsScale },
            density
        );
        break;
    default:
        break;
    }


    spriteComponent = gameObject->getComponent<SpriteComponent>();

    bubblePhysics->fixRotation();
    bubblePhysics->getFixture()->SetRestitution(1);
}

void Bubble::update(float deltaTime) {
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


