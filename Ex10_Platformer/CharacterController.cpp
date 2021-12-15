//
// Created by Morten Nobel-Jørgensen on 19/10/2017.
//

#include <SDL_events.h>
#include <iostream>
#include "CharacterController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "PlatformerGame.hpp"
#include "SpriteComponent.hpp"

CharacterController::CharacterController(GameObject *gameObject) : Component(gameObject) {
    characterPhysics = gameObject->addComponent<PhysicsComponent>();

    auto physicsScale = PlatformerGame::instance->physicsScale;
    radius = 10/physicsScale;
    characterPhysics->initCircle(b2_dynamicBody, radius, glm::vec2{1.5,1.5}*Level::tileSize/physicsScale,1);
    characterPhysics->getFixture()->SetRestitution(0);
    characterPhysics->fixRotation();
    spriteComponent = gameObject->getComponent<SpriteComponent>();

}

bool CharacterController::onKey(SDL_Event &event) {
        switch (event.key.keysym.sym){
            case SDLK_SPACE:
            {
                if (isGrounded && event.type == SDL_KEYDOWN){ // prevents double jump
                    jump();
                }
            }
            break;
                case SDLK_LEFT:
            {
                left = event.type == SDL_KEYDOWN;
            }
            break;
                case SDLK_RIGHT:
            {
                right = event.type == SDL_KEYDOWN;
            }
            break;
        }

    return false;
}

void CharacterController::update(float deltaTime) {
    // raycast ignores any shape in the starting point
    auto from = characterPhysics->getBody()->GetWorldCenter();
    b2Vec2 to {from.x,from.y -radius*1.3f};
    isGrounded = false;
    PlatformerGame::instance->world->RayCast(this, from, to);

    characterPhysics->fixRotation();
    glm::vec2 movement{0,0};
    if (left){
        movement.x --;
    }
    if (right){
        movement.x ++;
    }
    float accelerationSpeed = 0.010f;
    characterPhysics->addImpulse(movement*accelerationSpeed);
    float maximumVelocity = 2;
    auto linearVelocity = characterPhysics->getLinearVelocity();
    float currentVelocity = linearVelocity.x;
    if (abs(currentVelocity) > maximumVelocity){
        linearVelocity.x = glm::sign(linearVelocity.x)*maximumVelocity;
        characterPhysics->setLinearVelocity(linearVelocity);
    }
    updateSprite(deltaTime);
}

void CharacterController::jump() {
    characterPhysics->addImpulse({0,0.15f});
}

void CharacterController::onCollisionStart(PhysicsComponent *comp) {

}

void CharacterController::onCollisionEnd(PhysicsComponent *comp) {

}

float32 CharacterController::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) {
    isGrounded = true;
    return 0; // terminate raycast
}

void CharacterController::setSprites(sre::Sprite standing, sre::Sprite walk1, sre::Sprite walk2, sre::Sprite flyUp,
                                     sre::Sprite fly, sre::Sprite flyDown) {
    this->standing = standing;
    this->walk1 = walk1;
    this->walk2 = walk2;
    this->flyUp = flyUp;
    this->fly = fly;
    this->flyDown = flyDown;
}

void CharacterController::updateSprite(float deltaTime) {
    auto velocity = characterPhysics->getLinearVelocity();
    //std::cout << velocity.x << std::endl;
    animTime_walk = 1 / (velocity.x+0.1f);
    //std::cout << animTime_walk<< std::endl;
    time += deltaTime;
    // todo implement
    if (velocity == glm::vec2(0, 0)) {
        spriteComponent->setSprite(standing);
    }
    else if (isGrounded)
    {
        time = fmod(time, animTime_walk);
        //std::cout << time << std::endl;
        //animation  
        if (time > animTime_walk/2) {
           
            spriteComponent->setSprite(walk2);
            //std::cout << "walk2" << std::endl;
        }
        else {
            
            spriteComponent->setSprite(walk1);
            //std::cout << "walk1" << std::endl;
        }
    }
    else {
        /*
        --------------------------------------------------------------------------------------------------------------
        Here, I know it is not the most correct way to do it, but I didn't manage to implement the other solution T-T...
        Which was basically inspired by previous exercise - The Bird SpriteAnimationComponent
        I tried to set the animation time to 0.3f and then iterate through vector corrseponding to specigic animation sequence (like walk or jump)
        (as in Bird exercise)

        What would be the best way to solve this task?
        -----------------------------------------------------------------------------------------------------------------
        */
        time = fmod(time, animTime_jump);
        //std::cout << time << std::endl;
        if (time < animTime_jump / 3) {
            spriteComponent->setSprite(flyUp);
            //std::cout << "fly up" << std::endl;
        }
        else if (time > animTime_jump / 3 && time < 2 * (animTime_jump / 3)) {
            spriteComponent->setSprite(fly);
            //std::cout << "fly" << std::endl;
        }
        else {
            spriteComponent->setSprite(flyDown);
            //std::cout << "fly Down" << std::endl;
        }
    }
           
    if (velocity.x < 0) {
       standing.setFlip({ true,false });
       walk1.setFlip({ true,false });
       walk2.setFlip({ true,false });
       flyUp.setFlip({ true,false });
       fly.setFlip({ true,false });
       flyDown.setFlip({ true,false });
    }
    else {
        standing.setFlip({ false,false });
        walk1.setFlip({ false,false });
        walk2.setFlip({ false,false });
        flyUp.setFlip({ false,false });
        fly.setFlip({ false,false });
        flyDown.setFlip({ false,false });
    }
}


