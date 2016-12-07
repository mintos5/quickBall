//
// Created by michal on 5.11.2016.
//

#include "plane.h"
#include <GL/glew.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

plane::plane(ShaderPtr program) {
    this->program = program;
    std::vector<glm::vec3> startPoints{
            {-0.7f,0.8f,0.f},
            {-0.3f,0.9f,0.0f},
            {0.3f,0.9f,0.0f},
            {0.7f,0.8f,0.0f},

            {-0.7f,0.6f,0.0f},
            {-0.3f,0.7f,0.0f},
            {0.3f,0.7f,0.0f},
            {0.7f,0.6f,0.0f},

            {-0.7f,0.4f,0.0f},
            {-0.3f,0.5f,0.0f},
            {0.3f,0.5f,0.0f},
            {0.7f,0.4f,0.0f},

            {-0.7f,0.1f,0.0f},
            {-0.3f,0.3f,0.0f},
            {0.3f,0.3f,0.0f},
            {0.7f,0.1f,0.0f},
    };
    generatePoints(startPoints,4,4,5,8);
    generateIndices(5, 8,this->indices);
    //generateTextCoord(15,8);
    initialize();
}

plane::plane(ShaderPtr program, std::vector<glm::vec3> points, int rows, int lines) {
    this->program = program;
    generatePoints(points,rows,lines,8,8);
    generateIndices(8, 8,this->indices);
    //generateTextCoord(8,8);
    initialize();
}

glm::vec3 getBezierPoint(std::vector<glm::vec3> points, float t){
    std::vector<glm::vec3> tmp(points);
    int i = points.size()-1;
    while (i > 0) {
        for (int k = 0; k < i; k++)
            tmp[k] = tmp[k] + t * ( tmp[k+1] - tmp[k] );
        i--;
    }
    glm::vec3 answer = tmp[0];
    return answer;
}

void addBezierPoints(int resolution,std::vector<glm::vec3> points,std::vector<glm::vec3>& out){
    for (int i = 0;i<resolution;i++){
        float t = (float)i / (float)(resolution-1);
        glm::vec3 result = getBezierPoint(points,t);
        out.push_back(result);
    }
}

void plane::generateSurface(int resY,int resX,int num_lines,std::vector<glm::vec3> pointsAll) {
    std::vector<glm::vec3> points;
    for (int j = 0;j<resX;j++) {
        //just for generating column of points
        points.clear();
        for (int k = 0; k < num_lines; k++) {
            int row = k * resX;
            points.push_back(pointsAll[row + j]);
        }
        float u = (float)j / (float)(resX-1);
        for (int i = 0; i < resY; i++) {
            float v = (float) i / (float) (resY - 1);
            glm::vec3 result = getBezierPoint(points, v);
            this->vertex_buffer.push_back(result.x);
            this->vertex_buffer.push_back(result.y);
            this->vertex_buffer.push_back(result.z);
            this->texcoord_buffer.push_back(u);
            this->texcoord_buffer.push_back(v);
        }
    }
}

void plane::generatePoints(std::vector<glm::vec3> allPoints, int points, int lines,int resX,int resY) {
    std::vector<glm::vec3> linesPoints;
    int position = 0;
    for (int i=0;i<lines;i++){
        std::vector<glm::vec3>::const_iterator first = allPoints.begin() + position;
        std::vector<glm::vec3>::const_iterator last = allPoints.begin() + (position+points);
        std::vector<glm::vec3> subPoints(first, last);
        addBezierPoints(resX,subPoints,linesPoints);
        position += points;
    }
    linesPoints.size();
    generateSurface(resY,resX,lines,linesPoints);
    this->vertex_buffer.size();
}

void plane::generateIndices(int resX, int resY,std::vector<GLuint>& out) {
    for (int i=0;i<resX-1;i++){
        for (int j=0;j<resY-1;j++){
            int corner = (resY*i)+j;
            out.push_back(corner);
            out.push_back(corner+1);
            out.push_back(corner+resY);
            //next triangle
            out.push_back(corner+resY);
            out.push_back(corner+1);
            out.push_back(corner+resY+1);
        }
    }
}

void plane::initialize() {
    // Generate a vertex array object
    // This keeps track of what attributes are associated with buffers
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // Generate a vertex buffer object, this will feed data to the vertex shader
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertex_buffer.size() * sizeof(GLfloat), this->vertex_buffer.data(), GL_STATIC_DRAW);

    // Setup vertex array lookup, this tells the shader how to pick data for the "Position" input
    auto position_attrib = program->GetAttribLocation("Position");
    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_attrib);


    // --- Texture coordinates ---
    // Generate and upload a buffer with texture coordinates to GPU
    glGenBuffers(1, &this->tbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->tbo);
    glBufferData(GL_ARRAY_BUFFER, texcoord_buffer.size() * sizeof(GLfloat),
                 texcoord_buffer.data(), GL_STATIC_DRAW);

    // Bind the buffer to "TexCoord" attribute in program
    auto texcoord_attrib = program->GetAttribLocation("TexCoord");
    glEnableVertexAttribArray(texcoord_attrib);
    glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);


    // Setup indices for glDrwaElement
    glGenBuffers(1,&this->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()* sizeof(GLuint),this->indices.data(),GL_STATIC_DRAW);

    animateTime = 0.0f;
}

void plane::render() {
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_POINTS, 0, this->vertex_buffer.size()/3);
}

void plane::animate(float dt) {
    this->vertex_buffer.clear();
    animateTime+=dt*0.5;
    std::vector<glm::vec3> startPoints{
            {-0.7f,0.8f,std::sin(animateTime)/4.0f},
            {-0.3f,0.9f,std::sin(animateTime)},
            {0.3f,0.9f,std::sin(animateTime)},
            {0.7f,0.8f,std::sin(animateTime)/4.0f},

            {-0.7f,0.6f,0.0f},
            {-0.3f,0.7f,0.0f},
            {0.3f,0.7f,0.0f},
            {0.7f,0.6f,0.0f},

            {-0.7f,0.4f,0.0f},
            {-0.3f,0.5f,0.0f},
            {0.3f,0.5f,0.0f},
            {0.7f,0.4f,0.0f},

            {-0.7f,0.1f,-std::sin(animateTime)/3.0f},
            {-0.3f,0.3f,0.0f},
            {0.3f,0.3f,0.0f},
            {0.7f,0.1f,-std::sin(animateTime)/3.0f},
    };
    generatePoints(startPoints,4,4,15,8);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertex_buffer.size() * sizeof(GLfloat), this->vertex_buffer.data(), GL_STATIC_DRAW);
}