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
    vec3 pos = position;
    vec3 at (pos.x,pos.y, pos.z-100);
    vec3 up(0, 1, 0);
    float angle = rotation;
    angle = radians(angle);
    vec3 atRotated = rotateY(at, angle);
    camera->lookAt(pos, atRotated, up); // +position might be skipped?

    vec3 direction = glm::normalize(atRotated);
    if (fwd==true) {
        vec3 moveFwd(0, 0, -1); 
        vec3 rotated = rotateY(moveFwd, angle);
        position += (rotated * deltaTime * speed);
    }
    if (bwd == true) {
        vec3 moveBwd(0, 0, 1); 
        vec3 rotated = rotateY(moveBwd, angle);
        position += (rotated * deltaTime * speed);
    }
    if (right == true) {
        vec3 moveRight(1, 0, 0); 
        vec3 rotated = rotateY(moveRight, angle);
        position += (rotated * deltaTime * speed);
    }
    if (left == true) {
        vec3 moveLeft(-1, 0, 0); 
        vec3 rotated = rotateY(moveLeft, angle);
        position += (rotated * deltaTime * speed);
    }

}

void FirstPersonController::onKey(SDL_Event &keyEvent) {
    // TODO implement key input here
    if (keyEvent.key.keysym.sym == SDLK_w) {
        fwd = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_a) {
        left = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_d) {
        right = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_s) {
        bwd = keyEvent.type == SDL_KEYDOWN;
    }
}

void FirstPersonController::onMouse(SDL_Event& event) {
    // TODO implement mouse input here
    // Mouse moved ?
    if (event.type == SDL_MOUSEMOTION)
    {
        xrel = event.motion.xrel;
        rotation -= xrel;
    }
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation) {
    this->position = glm::vec3(position.x,0,position.y);
    this->rotation = rotation;
}
