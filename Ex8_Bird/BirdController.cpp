//
// Created by Morten Nobel-Jørgensen on 19/10/2017.
//

#include <SDL_events.h>
#include <iostream>
#include "BirdController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "BirdGame.hpp"
#include "SpriteComponent.hpp"

BirdController::BirdController(GameObject *gameObject) : Component(gameObject) {
    // initiate bird physics
}

bool BirdController::onKey(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN){
        std::cout << "some key pressed" << std::endl;
        m_addImpulse = true;
    } else if (event.type == SDL_KEYUP){
        std::cout << "some key released" << std::endl;
        m_addImpulse = false;
    }
    return false;


}

void BirdController::onCollisionStart(PhysicsComponent *comp) {
    std::cout << "bird collided with something" << std::endl;
    m_resetGame = true;
}

void BirdController::onCollisionEnd(PhysicsComponent *comp) {

}

bool BirdController::getAddImpulse() {
    return m_addImpulse;
}
bool BirdController::getResetGame() {
    return m_resetGame;
}



