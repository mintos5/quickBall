//
// Created by michal on 8.12.2016.
//

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "test1.h"
#include "text_frag.h"
#include "text_vert.h"

test1::test1() {
    if (!shader) shader = ShaderPtr(new Shader{text_vert, text_frag});
}
test1::~test1() {}

bool test1::Update(Scene &scene, float dt) {
    return true;
}

void test1::Render(Scene &scene) {
    shader->Use();
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Setup geometry
    std::vector<GLfloat> vertex_buffer{
            // x, y,soma,somb
            10, 10,0,0,
            20, 20,0,0,
            40, 60,0,0,
            90, 120,0,0
    };

    // Generate a vertex buffer object, this will feed data to the vertex shader
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

    // Setup vertex array lookup, this tells the shader how to pick data for the "Position" input
    auto position_attrib = shader->GetAttribLocation("coord");
    glVertexAttribPointer(position_attrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_attrib);
    std::cout << "Testing" << std::endl;
    glDrawArrays(GL_LINES, 0, 4);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(600), 0.0f, static_cast<GLfloat>(600));
    shader->SetMatrix(projection,"projection");
}
ShaderPtr test1::shader;