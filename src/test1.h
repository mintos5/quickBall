//
// Created by michal on 8.12.2016.
//

#ifndef PPGSO_TEST1_H
#define PPGSO_TEST1_H


#include <shader.h>
#include "object.h"

class test1 : public Object {
public:
    GLuint vao;
    GLuint vbo;
    test1();
    ~test1();
    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;
private:
    // Static resources (Shared between instances)
    static ShaderPtr shader;
};
typedef std::shared_ptr<test1> TestPtr;

#endif //PPGSO_TEST1_H
