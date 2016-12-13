//
// Created by michal on 8.12.2016.
//

#ifndef PPGSO_WORD_H
#define PPGSO_WORD_H
#include <texts.h>
#include "object.h"

class word : public Object {
public:
    word(std::string text,int x,int y,float scale,int sizeX,int sizeY);
    ~word();
    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

    void setChangeable(bool changeable);

private:
    int sizeX;
    int sizeY;
    int x;
    int y;
    float scale;
    bool changeable = false;
    // Static resources (Shared between instances)
    TextPtr textR;
    static ShaderPtr shader;

};
typedef std::shared_ptr<word> WordPtr;

#endif //PPGSO_WORD_H
