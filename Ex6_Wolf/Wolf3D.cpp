#include "Wolf3D.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>


using namespace std;
using namespace sre;
using namespace glm;

Wolf3D::Wolf3D()
:fpsController(&camera)
{
    r.init();
    init();

    // Enable mouse lock
     //SDL_SetWindowGrab(r.getSDLWindow(),SDL_TRUE);
     //SDL_SetRelativeMouseMode(SDL_TRUE);


    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };
    r.frameRender = [&](){
        render();
    };
    r.keyEvent = [&](SDL_Event& e){
        fpsController.onKey(e);
    };
    r.mouseEvent = [&](SDL_Event& e){
        if (!lockRotation){
            fpsController.onMouse(e);
        }
    };
    r.startEventLoop();
}

void Wolf3D::update(float deltaTime) {
    fpsController.update(deltaTime);
}

void Wolf3D::render() {
    auto renderPass = RenderPass::create()
            .withCamera(camera)
            .build();

    renderPass.draw(walls, glm::mat4(1), wallMaterial);

    if (debugBricks){
        renderDebugBricks(renderPass);
    }

    ImGui::SetNextWindowPos(ImVec2(Renderer::instance->getWindowSize().x/2-100, .0f), ImGuiSetCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Always);
    ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::DragFloat("Rot", &fpsController.rotation);
    ImGui::DragFloat3("Pos", &(fpsController.position.x), 0.1f);
    ImGui::Checkbox("DebugBricks", &debugBricks);
    ImGui::Checkbox("LockRotation", &lockRotation);
    ImGui::End();
}

// Creates a textured cube with a side length of 1 (e.g. from -0.5 to 0.5).
// The cube must be centered at (x,0,z)
// The texturing
void Wolf3D::addCube(std::vector<glm::vec3>& vertexPositions, std::vector<glm::vec4>& textureCoordinates, int x, int z, int type) {
    //original values (default)
    glm::vec3 A1(-0.5, -0.5, 0.5);
    glm::vec3 A2(0.5, -0.5, 0.5);
    glm::vec3 A3(-0.5, 0.5, 0.5);

    glm::vec3 B1(0.5, 0.5, 0.5);
    glm::vec3 B2(-0.5, 0.5, 0.5);
    glm::vec3 B3(0.5, -0.5, 0.5);

    float angle = radians(90.0f);

    vec3 cubePos = vec3(x, 0, z);

    //1 side of the cube
    vector<vec3> base = { glm::vec3(A1), glm::vec3(A2), glm::vec3(A3),
                          glm::vec3(B1), glm::vec3(B2), glm::vec3(B3) };

    for (int j = 0; j < 4; j++)// 4 sides of cube
    {
        for (int i = 0; i < base.size(); i++) // rotate every vertex
        {
            vec3 temp = base[i];
            temp = vec3(rotateY(temp, angle*j)); // 0 - 0 ; 1-90 ; 2-180 ; 3-270
            temp = temp + cubePos; // transform to fit given x and z position

            vertexPositions.insert(vertexPositions.end(), { temp });
        }
    }

    glm::vec2 textureSize(2048, 4096);
    glm::vec2 tileSize(64, 64);
    glm::vec2 tileSizeWithBorder(65, 65);

    int texturesInARow = 8;

    int tilemapStartRow = 42; //X
    int tilemapStartCol = 0; //Y
  
    int tileRow = tilemapStartRow - round((type / texturesInARow));
    int tileCol = tilemapStartCol + (type % 8) * tileSizeWithBorder.x * 2;
    std::cout << " type: " << type << " tileRow: " << tileRow << " tileCol: " << tileCol << std::endl;

    glm::vec2 minLight = vec2(tileCol, tileRow * tileSizeWithBorder.y) / textureSize;
    glm::vec2 maxLight = minLight + tileSize / textureSize;

    glm::vec2 minDark = vec2(tileCol + tileSizeWithBorder.x, tileRow * tileSizeWithBorder.y ) / textureSize;
    glm::vec2 maxDark = minDark + tileSize / textureSize;

    textureCoordinates.insert(textureCoordinates.end(), {
            //light
            glm::vec4(minLight.x,minLight.y,0,0), glm::vec4(maxLight.x,minLight.y,0,0), glm::vec4(minLight.x,maxLight.y,0,0),
            glm::vec4(maxLight.x,maxLight.y,0,0), glm::vec4(minLight.x,maxLight.y,0,0), glm::vec4(maxLight.x,minLight.y,0,0),

            //dark
            glm::vec4(minDark.x,minDark.y,0,0), glm::vec4(maxDark.x,minDark.y,0,0), glm::vec4(minDark.x,maxDark.y,0,0),
            glm::vec4(maxDark.x,maxDark.y,0,0), glm::vec4(minDark.x,maxDark.y,0,0), glm::vec4(maxDark.x,minDark.y,0,0),

            //light
            glm::vec4(minLight.x,minLight.y,0,0), glm::vec4(maxLight.x,minLight.y,0,0), glm::vec4(minLight.x,maxLight.y,0,0),
            glm::vec4(maxLight.x,maxLight.y,0,0), glm::vec4(minLight.x,maxLight.y,0,0), glm::vec4(maxLight.x,minLight.y,0,0),

            //dark
            glm::vec4(minDark.x,minDark.y,0,0), glm::vec4(maxDark.x,minDark.y,0,0), glm::vec4(minDark.x,maxDark.y,0,0),
            glm::vec4(maxDark.x,maxDark.y,0,0), glm::vec4(minDark.x,maxDark.y,0,0), glm::vec4(maxDark.x,minDark.y,0,0),
        });
}

void Wolf3D::init() {
    wallMaterial = Shader::getUnlit()->createMaterial();
    auto texture = Texture::create().withFile("level0.png")
            .withGenerateMipmaps(false)
            .withFilterSampling(false)
            .build();
    wallMaterial->setTexture(texture);

    map.loadMap("level0.json");

    std::vector<glm::vec3> vertexPositions;
    std::vector<glm::vec4> textureCoordinates;

    for (int x=0;x<map.getWidth();x++){
        for (int y=0;y<map.getHeight();y++){
            int field = map.getTile(x,y);
            if (field != -1){
                addCube(vertexPositions,textureCoordinates,x,y,field);
            }
        }
    }

    fpsController.setInitialPosition(map.getStartingPosition(), map.getStartingRotation());

    walls = Mesh::create()
            .withPositions(vertexPositions)
            .withUVs(textureCoordinates)
            .build();
}

void Wolf3D::renderDebugBricks(RenderPass & renderPass){
    static auto cube = Mesh::create().withCube(0.5f).build();
    static vector<shared_ptr<Material> > materials = {
            Shader::getUnlit()->createMaterial(),
            Shader::getUnlit()->createMaterial(),
            Shader::getUnlit()->createMaterial()
    };

    std::vector<vec3> positions = {
            {-1,0,-2},
            { 0,0,-3},
            { 1,0,-4}
    };
    std::vector<sre::Color> colors = {
            {1,0,0,1},
            {0,1,0,1},
            {0,0,1,1},
    };
    for (int i=0;i<positions.size();i++){
        materials[i]->setColor(colors[i]);
        renderPass.draw(cube, glm::translate(positions[i]), materials[i]);
    }
}

int main(){
    new Wolf3D();
    return 0;
}