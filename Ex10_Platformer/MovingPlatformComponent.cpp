//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#include "MovingPlatformComponent.hpp"
#include "PlatformComponent.hpp"
#include "GameObject.hpp"
#include <cmath>
#include <map>
#include <iostream>

#ifndef PI
#define PI 3.1415926545
#endif

MovingPlatformComponent::MovingPlatformComponent(GameObject *gameObject) : Component(gameObject)
{
    platformComponent = gameObject->getComponent<PlatformComponent>();
}

void MovingPlatformComponent::update(float deltaTime) {
    totalTime += deltaTime/1.5f;

    glm::vec2 newPos = movementStart;
    newPos.y = movementStart.y+1.5f + easeInSine(fmod(totalTime, 4.0f))*1.5f;
    platformComponent->moveTo(newPos);
}

void MovingPlatformComponent::setMovementStart(glm::vec2 pos) {
    movementStart = pos;
}

void MovingPlatformComponent::setMovementEnd(glm::vec2 pos) {
    movementEnd = pos;
}

double MovingPlatformComponent::easeInSine(double t) {
    return sin(1.5707963 * t);
}

