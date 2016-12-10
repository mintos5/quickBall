//
// Created by michal on 9.12.2016.
//

#ifndef PPGSO_GENERATOR_H
#define PPGSO_GENERATOR_H
#include <random>
#include "object.h"
#include "scene.h"
#include "player.h"

class generator  : public Object {
public:
    int maxLives = 2;
    int curLives = 0;
    generator(const PlayerPtr &player);
    ~generator();
    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

private:
    PlayerPtr player;
    std::vector<int> genVector;
    std::random_device rd;
    std::mt19937 rng;
    std::uniform_int_distribution<int> uni1;
    std::uniform_int_distribution<int> uni2;
    void generateEnemy(Scene &scene, int where);
    void generateFence(Scene &scene, int where);
    void generateHeart(Scene &scene, int where);
    void generatePortal(Scene &scene);
};
typedef std::shared_ptr<generator> GeneratorPtr;


#endif //PPGSO_GENERATOR_H
