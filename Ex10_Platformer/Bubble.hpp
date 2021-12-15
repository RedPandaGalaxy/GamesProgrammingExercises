//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#pragma once
#include "Component.hpp"
#include <Box2D/Box2D.h>
#include "Component.hpp"
#include "SpriteComponent.hpp"
#include "sre/Sprite.hpp"

enum class BubbleSize { XS, S, M, L, XL };

class Bubble : public Component{
public:
    explicit Bubble(GameObject *gameObject);
    bool onKey(SDL_Event& event) override;

    void onCollisionStart(PhysicsComponent* comp) override;
    void onCollisionEnd(PhysicsComponent* comp) override;
    void update(float deltaTime) override;
    void Bubble::SpawnBubble(BubbleSize size, glm::vec2 pos);

private:
    BubbleSize size;
    float density;
    std::shared_ptr<PhysicsComponent> bubblePhysics;
    std::shared_ptr<SpriteComponent> spriteComponent;
    float radius;
    bool left = false;
    bool right = false;


};

