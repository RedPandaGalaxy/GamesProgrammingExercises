#include <ctime>
#include <glm/gtc/constants.hpp>
#include "AsteroidsGame.hpp"
#include "GameObject.hpp"
#include "SpaceShip.hpp"
#include "Asteroid.hpp"
#include "Laser.hpp"
#include "iostream"


using namespace sre;

AsteroidsGame::AsteroidsGame() {
    r.setWindowTitle("Asteroids");

    r.init().withSdlInitFlags(SDL_INIT_EVERYTHING)
            .withSdlWindowFlags(SDL_WINDOW_OPENGL);

    time_t t;
    // random seed based on time
    srand((unsigned) time(&t));

    atlas = SpriteAtlas::create("asteroids.json","asteroids.png");

    SpawnManager();

    camera.setWindowCoordinates();

    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };

    r.keyEvent = [&](SDL_Event& event){
        keyEvent(event);
    };

    r.frameRender = [&](){
        render();
    };

    r.startEventLoop();
}

void AsteroidsGame::update(float deltaTime) {
    if (isGameOn) {
        for (int i = 0; i < gameObjects.size();i++) 
        {
		    gameObjects[i]->update(deltaTime);
        }
        DetectCollision();
    }
	
}

void drawCircle(std::vector<glm::vec3>& lines, glm::vec2 position, float radius){
    int sides = 15;
    float quaterPi = glm::two_pi<float>() / (float)sides;
    for (float f = 0; f<glm::two_pi<float>(); f += quaterPi){
        // line from
        lines.push_back(glm::vec3{position.x + cosf(f)*radius,
                                  position.y + sinf(f)*radius,
                                  0
        });
        // line to
        lines.push_back(glm::vec3{position.x + cosf(f+quaterPi)*radius,
                                  position.y + sinf(f+quaterPi)*radius,
                                  0
        });
    }
}

void AsteroidsGame::render() {
    auto renderPass = RenderPass::create()
            .withCamera(camera)
            .withClearColor(true, {.20, .60, .86, 1})
            .build();
    auto spriteBatchBuilder = SpriteBatch::create();

    for (int i = 0; i < gameObjects.size();i++) {
        gameObjects[i]->render(spriteBatchBuilder);
    }
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);

    if (debugCollisionCircles){
        std::vector<glm::vec3> lines;
        for (auto & go : gameObjects){
            auto col = std::dynamic_pointer_cast<Collidable>(go);
            if (col != nullptr){
                drawCircle(lines, go->position, col->getRadius());
            }
        }
        renderPass.drawLines(lines);
    }

    //GUI
    ImGui::SetNextWindowPos(ImVec2(Renderer::instance->getWindowSize().x/2 - 100, .0f), ImGuiSetCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 70), ImGuiSetCond_Always);
    ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::LabelText("GOs", "%i", (int)gameObjects.size());
    ImGui::LabelText("Score", "%i",score);
    ImGui::End();
}

void AsteroidsGame::keyEvent(SDL_Event &event) {
    for (int i = 0; i < gameObjects.size();i++) {
        gameObjects[i]->onKey(event);
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d){
        debugCollisionCircles = !debugCollisionCircles;
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !isGameOn)
    {
        RestartGame();
    }
}

void AsteroidsGame::FireLaser(glm::vec2 pos, float rot, glm::vec2 direction){
    auto laserSprite = atlas->get("laserRed01.png");
    this->gameObjects.push_back(std::make_shared<Laser>(laserSprite, pos, direction,rot,this));
}

void AsteroidsGame::DestroyLaser( GameObject*  laserRay) 
{
    int index = 0;
    for ( int i = 0; i < gameObjects.size(); i++) 
    {
        if (gameObjects[i].get() == laserRay) 
        {
            index = i;
            gameObjects.erase((gameObjects.begin() + index));
            break;
        }
    }
}

void AsteroidsGame::DestroyAsteroid(GameObject* asteroid)
{
    int index = 0;
    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i].get() == asteroid)
        {
            index = i;
            gameObjects.erase((gameObjects.begin() + index));
            score++;
            break;
        }
    }
}

void AsteroidsGame::DestroyShip(GameObject* spaceship, glm::vec2 pos) {
    int index = 0;
    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i].get() == spaceship)
        {
            index = i;
            gameObjects.erase((gameObjects.begin() + index));
            auto bang = atlas->get("bang.png");
            gameObjects.push_back(std::make_shared<SpaceShip>(bang, this, pos));
            isGameOn = false;
            break;
        }
    }
}

void AsteroidsGame::SpawnAsteroid(Asteroid::asteroidSize size, glm::vec2 pos) {
    auto asteroidBigSprite = atlas->get("meteorBrown_big4.png");
    auto asteroidMediumSprite = atlas->get("meteorBrown_med3.png");
    auto asteroidSmallSprite = atlas->get("meteorBrown_small2.png");

    if (size == Asteroid::L) {
        gameObjects.push_back(std::make_shared<Asteroid>(asteroidBigSprite, this, Asteroid::L, pos));
    }
    if (size == Asteroid::M) {
        gameObjects.push_back(std::make_shared<Asteroid>(asteroidMediumSprite, this, Asteroid::M, pos));
    }
    if (size == Asteroid::S) {
        gameObjects.push_back(std::make_shared<Asteroid>(asteroidSmallSprite, this, Asteroid::S, pos));
    }
}

void AsteroidsGame::DetectCollision() 
{
    int size = gameObjects.size();

    for (int i = 0; i < size; i++) 
    {
        size = gameObjects.size();
        if (i >= size)
            i = size - 1;
        std::dynamic_pointer_cast<Collidable>(gameObjects[i]);
        if (std::dynamic_pointer_cast<Collidable>(gameObjects[i]) != nullptr) 
        {
            //it can collide with other objects
            size = gameObjects.size();
            for (int j = 0; j < size; j++) 
            {
                if (j >= size)
                    j = size - 1;
                if (i >= size)
                    i = size - 1;
                if (std::dynamic_pointer_cast<Collidable>(gameObjects[j]) != nullptr) 
                {
                    //both can collide
                    //check for collision
                    if (j >= size)
                        j = size - 1;
                    if (i >= size)
                        i = size - 1;
                    auto obj1 = gameObjects[i];
                    auto obj2 = gameObjects[j];
                    float distance = glm::distance(obj1->position, obj2->position);
                    if (distance <= std::dynamic_pointer_cast<Collidable>(obj1)->getRadius() + std::dynamic_pointer_cast<Collidable>(obj2)->getRadius()) 
                    {
                        //collision happened
                        std::dynamic_pointer_cast<Collidable>(obj1)->onCollision(obj2);
                        std::dynamic_pointer_cast<Collidable>(obj1)->onCollision(obj1);
                    }
                }
                size = gameObjects.size();
                if (j >= size)
                    j = size - 1;
                if (i >= size)
                    i = size - 1;
            }
            size = gameObjects.size();
            if (i >= size)
                i = size - 1;
        }
    }
}

void AsteroidsGame::RestartGame() {
    gameObjects.clear();
    score = 0;
    SpawnManager();
    isGameOn = true;
}

void AsteroidsGame::SpawnManager() 
{
    auto asteroidBigSprite = atlas->get("meteorBrown_big4.png");
    auto asteroidMediumSprite = atlas->get("meteorBrown_med3.png");
    auto asteroidSmallSprite = atlas->get("meteorBrown_small2.png");
    auto spaceshipSprite = atlas->get("playerShip1_red.png");  

    gameObjects.push_back(std::make_shared<SpaceShip>(spaceshipSprite, this));
    //asteroids

    for (int i = 0; i < 5; i++) {
        gameObjects.push_back(std::make_shared<Asteroid>(asteroidBigSprite, this, Asteroid::L));
    }
}

int main(){
    new AsteroidsGame();
    return 0;
}