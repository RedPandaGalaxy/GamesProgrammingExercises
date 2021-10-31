#pragma once

#include "Component.hpp"

class BirdController : public Component {
public:
    explicit BirdController(GameObject *gameObject);

    bool onKey(SDL_Event &event) override;

    void onCollisionStart(PhysicsComponent *comp) override;

    void onCollisionEnd(PhysicsComponent *comp) override;

    bool getAddImpulse() {
        return m_addImpulse;
    }

private:
    bool m_addImpulse = false;
};
