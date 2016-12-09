//
// Created by michal on 9.12.2016.
//

#include "back.h"
#include "back_frag.h"
#include "back_vert.h"

back::~back() {

}

back::back(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {
    this->projection = glm::ortho(0.0f, static_cast<GLfloat>(this->sizeX), 0.0f, static_cast<GLfloat>(this->sizeY));
    if (!shader) shader = ShaderPtr(new Shader{back_vert, back_frag});
    if (!texture) texture = TexturePtr(new Texture{"background.rgb", 600, 600});
    init();
}

void back::init() {
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // Setup geometry
    std::vector<GLfloat> vertex_buffer{
            // x, y,texCoord 2x
            sizeX, sizeY,1,0,
            0, sizeY,0,0,
            sizeX, 0,1,1,
            0, 0,0,1,
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

bool back::Update(Scene &scene, float dt) {
    return true;
}

void back::Render(Scene &scene) {
    shader->Use();
    shader->SetMatrix(projection,"projection");
    shader->SetTexture(texture, "tex");
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

ShaderPtr back::shader;
TexturePtr back::texture;