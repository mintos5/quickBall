//
// Created by michal on 5.11.2016.
//

#ifndef PPGSO_PLANE_H
#define PPGSO_PLANE_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <shader.h>

enum animation_t {none,scale,rotate,squash,translate};

class plane{
    GLuint vao;
    GLuint vbo, tbo, nbo;
    GLuint ibo;
    ShaderPtr program;
    std::vector<GLfloat> vertex_buffer;
    std::vector<GLfloat> texcoord_buffer;
    std::vector<GLuint> indices;
    float animateTime;

    void generatePoints(std::vector<glm::vec3> allPoints, int points,int lines,int resX,int resY);
    void generateIndices(int resX, int resY,std::vector<GLuint>& out);
    void generateSurface(int resY,int resX,int num_lines,std::vector<glm::vec3> pointsAll);
    void initialize();

public:
    plane(ShaderPtr program);
    plane(ShaderPtr program,std::vector<glm::vec3> points,int rows,int lines);
    void render();
    void animate(float time);
};


#endif //PPGSO_PLANE_H
