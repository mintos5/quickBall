//
// Created by michal on 8.12.2016.
//

#ifndef PPGSO_TITLESCREEN_H
#define PPGSO_TITLESCREEN_H
#include <shader.h>
#include "object.h"

class titlescreen : public Object {
public:
    GLuint vao;
    GLuint vbo;

    titlescreen(int sizeX,int sizeY);
    ~titlescreen();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;
private:
    // Static resources (Shared between instances)
    glm::mat4 projection;
    static ShaderPtr shader;
    int sizeX;
    int sizeY;
    void init();
};
typedef std::shared_ptr<titlescreen> TitlePtr;

#endif //PPGSO_TITLESCREEN_H
