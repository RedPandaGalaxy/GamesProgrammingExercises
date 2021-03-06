#include <SDL_events.h>
#include "sre/Camera.hpp"

class FirstPersonController {
public:
    explicit FirstPersonController(sre::Camera * camera);

    void update(float deltaTime);
    void onKey(SDL_Event& event);
    void onMouse(SDL_Event &event);

    void setInitialPosition(glm::vec2 position, float rotation);

    float rotation = 0;
    glm::vec3 position;
private:
    sre::Camera * camera;

    // TODO you can use these to record the state of the keys and mouse movement
    //  remember to initialize if you decide to use these as is
    bool move_forward = false;
    bool move_backward = false;
    bool move_left = false;
    bool move_right = false;

    bool mouseMovement = false;
    bool mouseFirst = false;

    float xrel = 0;
};

