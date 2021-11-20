#pragma once

#include <memory>
#include "Component.hpp"
#include "glm/glm.hpp"

class PlatformComponent;

class MovingPlatformComponent : public Component {
public:
    explicit MovingPlatformComponent(GameObject *gameObject);

    void setMovementStart(glm::vec2 pos);
    void setMovementEnd(glm::vec2 pos);

    void update(float deltaTime) override;
    double easeInSine(double t);

private:
    float totalTime = 0;
    glm::vec2 movementStart = glm::vec2(2,4);
    glm::vec2 movementEnd = glm::vec2(movementStart.x,movementStart.y +2);
    std::shared_ptr<PlatformComponent> platformComponent;
};
