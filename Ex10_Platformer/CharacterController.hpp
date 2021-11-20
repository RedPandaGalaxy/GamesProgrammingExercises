#pragma once

#include <Box2D/Box2D.h>
#include "Component.hpp"
#include "SpriteComponent.hpp"
#include "sre/Sprite.hpp"

class CharacterController : public Component, public b2RayCastCallback {
public:
    explicit CharacterController(GameObject *gameObject);

    void setSprites(sre::Sprite standing,
                    sre::Sprite walk1,
                    sre::Sprite walk2,
                    sre::Sprite flyUp,
                    sre::Sprite fly,
                    sre::Sprite flyDown);

    void updateSprite(float deltaTime);

    void update(float deltaTime) override;

    bool onKey(SDL_Event &event) override;

    void jump();

    // raycast callback
    virtual float32 ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
                                      const b2Vec2& normal, float32 fraction) override;

    void onCollisionStart(PhysicsComponent *comp) override;

    void onCollisionEnd(PhysicsComponent *comp) override;
private:
    sre::Sprite standing;
    sre::Sprite walk1;
    sre::Sprite walk2;
    sre::Sprite flyUp;
    sre::Sprite fly;
    sre::Sprite flyDown;

    std::shared_ptr<SpriteComponent> spriteComponent;
    std::shared_ptr<PhysicsComponent> characterPhysics;
    bool isGrounded = false;
    float radius;
    bool left = false;
    bool right = false;

    std::vector<sre::Sprite> spritesWalk { this->walk1,  this->walk2 };
    std::vector<sre::Sprite> spritesJump {this->flyUp, this->fly, this->flyDown};
    float time=0;
    float animTime_jump= 0.9f;
    float animTime_walk=0.4f;
    int spriteIndex = 0;
};
