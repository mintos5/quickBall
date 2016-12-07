//
// Created by michal on 23.11.2016.
//

#include "ground.h"
#include "scene.h"
#include "object_frag.h"
#include "object_vert.h"

ground::ground() {
    std::vector<glm::vec3> startPoints{
            {-1.0f,-1.0f,0.0f},
            {1.0f,-1.0f,0.0f},

            {-1.0f,-1.0f,30.0f},
            {1.0f,-1.0f,30.0f},
    };


    if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
    if (!texture) texture = TexturePtr(new Texture{"ground.rgb", 512, 512});
    if (!planeR) planeR = PlanePtr(new plane{shader,startPoints,2,2});
    GenerateModelMatrix();
}
ground::ground(bool ground){
    if (!shader) shader = ShaderPtr(new Shader{object_vert, object_frag});
    if (!texture) texture = TexturePtr(new Texture{"ground.rgb", 512, 512});
    if (!planeR) planeR = PlanePtr(new plane{shader});
    GenerateModelMatrix();
}

ground::~ground() {

}

bool ground::Update(Scene &scene, float dt) {
    GenerateModelMatrix();
    return true;
}

void ground::Render(Scene &scene) {

    shader->Use();

    // use camera
    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    // render mesh
    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "Texture");
    planeR->render();
}

// shared resources
PlanePtr ground::planeR;
ShaderPtr ground::shader;
TexturePtr ground::texture;