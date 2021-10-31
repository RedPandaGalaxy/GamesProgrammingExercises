#include "GameObject.hpp"

GameObject::GameObject(sre::Sprite sprite)
:position(0,0),
 rotation(0),
 scale(1,1),
 sprite(sprite)
{
}

GameObject::GameObject(sre::Sprite sprite, glm::vec2 Gposition, float Grotation)
{
    position = Gposition;
    rotation = Grotation;
    scale = glm::vec2(1,1);
    sprite= sprite;
}

GameObject::~GameObject(){
}

void GameObject::update(float deltaTime) {
}

void GameObject::render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) {
    sprite.setPosition(position);
    sprite.setRotation(rotation);
    sprite.setScale(scale);
    spriteBatchBuilder.addSprite(sprite);
}

void GameObject::onKey(SDL_Event &keyEvent) {

}

