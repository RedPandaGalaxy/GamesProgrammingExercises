//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#include <iostream>
#include "BirdMovementComponent.hpp"
#include "GameObject.hpp"

BirdMovementComponent::BirdMovementComponent(GameObject *gameObject) : Component(gameObject) {}

void BirdMovementComponent::update(float deltaTime) {
    time += deltaTime;
    gameObject->setPosition(computePositionAtTime(time));
}

glm::vec2 BirdMovementComponent::computePositionAtTime(float time) {
    int segment = (int)fmod(time, getNumberOfSegments());
    float t = fmod(time,1.0f);

    // todo use Quadratic Bézier spline instead 
    auto A = glm::mix(positions[segment * 2], positions[segment * 2 + 1], t);
    auto B = glm::mix(positions[segment * 2 + 1], positions[segment * 2 + 2], t);
    auto C = glm::mix(A, B, t);
    return C;

}

const std::vector<glm::vec2> &BirdMovementComponent::getPositions() {
    return positions;
}

void BirdMovementComponent::setPositions(std::vector<glm::vec2> positions) {
    this->positions = std::move(positions);
}

int BirdMovementComponent::getNumberOfSegments() {
    // todo return number of Quadratic Bézier spline segments instead
    return (positions.size() -1) / 2;
}

