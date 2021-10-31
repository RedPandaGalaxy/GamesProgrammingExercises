#include "FirstPersonController.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "iostream"

using namespace sre;
using namespace glm;


FirstPersonController::FirstPersonController(sre::Camera * camera)
:camera(camera)
{
    camera->setPerspectiveProjection(45,0.1f,1000);
    position = vec3(0,0,0);
}


void FirstPersonController::update(float deltaTime){
    // TODO implement the camera movement using position and rotation here
   //camera->lookAt(vec3(0,0,0), vec3(0,0,-1), );
    

    //Player Movement
    if (move_forward == true) {
        position.z = position.z + 0.1f;
        //std::cout << "Forward!";
    }
    if (move_backward == true) {
        position.z = position.z - 0.1f;
        // std::cout << "Backward!";
    }
    if (move_right == true) {
        position.x = position.x - 0.1f;

    }
    if (move_left == true) {
        position.x = position.x + 0.1f;
    }


    if (mouseMovement) {
        rotation = rotation - xrel;
    }

    mat4 m = translate(position);
    vec3 axis(0, 1, 0);
    float angle = glm::radians(rotation);
   // mat4 rot = rotateY(-angle, axis);
   // camera->setViewTransform(m * rot);

    //work on it
   //camera->lookAt(position, vec3(position.x, position.y, 0), vec3{ 0,1,0 });


    

    
}

void FirstPersonController::onKey(SDL_Event &event) {
    // TODO implement key input here
    if (event.key.keysym.sym == SDLK_w) 
    {
        move_forward = event.type == SDL_KEYDOWN;
    }

    if (event.key.keysym.sym == SDLK_s) 
    {
        move_backward = event.type == SDL_KEYDOWN;
    }

    if (event.key.keysym.sym == SDLK_a) 
    {
        move_left = event.type == SDL_KEYDOWN;
    }

    if (event.key.keysym.sym == SDLK_d) {
        move_right = event.type == SDL_KEYDOWN;
    }
}

void FirstPersonController::onMouse(SDL_Event &event) {
    // TODO implement mouse input here
    //Mouse
   // Mouse moved ?
    if (event.type == SDL_MOUSEMOTION)
    {
        mouseMovement = true;
        if (!mouseFirst) 
        {
            xrel = event.motion.xrel;
            //MouseRelY = Event.motion.yrel;
        }
        else 
        {
            mouseFirst = false;
            xrel = 0;
            // MouseRelY = 0;
        }
    }
    //std::cout << "  " << xrel;
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation) {
    this->position = glm::vec3(position.x,0,position.y);
    this->rotation = rotation;
}
