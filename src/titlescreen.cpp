//
// Created by michal on 8.12.2016.
//

#include <glm/gtc/matrix_transform.hpp>
#include "titlescreen.h"
#include "text_frag.h"
#include "text_vert.h"


titlescreen::titlescreen(int sizeX,int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->projection = glm::ortho(0.0f, static_cast<GLfloat>(this->sizeX), 0.0f, static_cast<GLfloat>(this->sizeY));
    if (!shader) shader = ShaderPtr(new Shader{text_vert, text_frag});
    init();
}

titlescreen::~titlescreen() {

}

bool titlescreen::Update(Scene &scene, float dt) {
    return true;
}

void titlescreen::Render(Scene &scene) {
    shader->Use();
    shader->SetMatrix(projection,"projection");
    glm::vec4 color = glm::vec4(0.0f,0.0f,0.0f,4.0f);
    shader->SetVector(color,"color");
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void titlescreen::init() {
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // Setup geometry
    std::vector<GLfloat> vertex_buffer{
            // x, y,soma,somb
            sizeX, sizeY,0,0,
            0, sizeY,0,0,
            sizeX, 0,0,0,
            0, 0,0,0,
    };

    // Generate a vertex buffer object, this will feed data to the vertex shader
    GLuint vbo;
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

    // Setup vertex array lookup, this tells the shader how to pick data for the "Position" input
    auto position_attrib = shader->GetAttribLocation("coord");
    glVertexAttribPointer(position_attrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_attrib);
    glBindBuffer(GL_ARRAY_BUFFER, 0);//na nuly to dat
    glBindVertexArray(0);//na nuly to dat
}

ShaderPtr titlescreen::shader;