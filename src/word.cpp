//
// Created by michal on 8.12.2016.
//

#include <iostream>
#include <sstream>
#include "word.h"
#include "text_frag.h"
#include "text_vert.h"
#include "scene.h"

word::word(std::string text,int x,int y,float scale,int sizeX,int sizeY) {
    this->x = x;
    this->y = y;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->scale = scale;
    this->textString = text;
    if (!shader) shader = ShaderPtr(new Shader{text_vert, text_frag});
    if (!textR) textR = TextPtr(new texts{shader,text});
}
word::~word() {}

bool word::Update(Scene &scene, float dt) {
    if (changeable){
        std::stringstream ss;
        ss << "LIVES: " << scene.playerStatus;
        textString = ss.str();
    }
    return true;
}

void word::Render(Scene &scene) {
    shader->Use();
    glm::vec4 color = glm::vec4(1.0f,1.0f,1.0f,1.0f);
    shader->SetVector(color,"color");
    //TODO dostat tu spravnu velkost okna
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(sizeX), 0.0f, static_cast<GLfloat>(sizeY));
    shader->SetMatrix(projection,"projection");
    textR->setWords(textString);
    textR->render(this->x,this->y,this->scale);
}

void word::setChangeable(bool changeable) {
    this->changeable = changeable;
}

ShaderPtr word::shader;
TextPtr word::textR;
