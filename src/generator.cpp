//
// Created by michal on 9.12.2016.
//

#include "generator.h"
#include "fence.h"
#include "enemy.h"
#include "heart.h"

#define BUFFER 30.0f
#define LEFT 1
#define CENTER 2
#define RIGHT 3
#define ENEMY 1
#define FENCE 2
#define HEART 3

generator::generator(const PlayerPtr &player) : player(player) {
    this->position = glm::vec3(0.0f,0.0f,-3.0f);
    this->rng = std::mt19937(rd());
    genVector.push_back(ENEMY);
    genVector.push_back(FENCE);
    genVector.push_back(ENEMY);
    genVector.push_back(ENEMY);
    genVector.push_back(FENCE);
    genVector.push_back(ENEMY);
    genVector.push_back(HEART);
    this->uni1 = std::uniform_int_distribution<int>(0,genVector.size()-1);
    this->uni2 = std::uniform_int_distribution<int>(1,3);
}

generator::~generator() {

}

bool generator::Update(Scene &scene, float dt) {
    while (position.z>=player->position.z-BUFFER){
        if ( (player->position.z-BUFFER) - position.z<=-3.0f){
            position.z -= 3.0f;
            int pos = uni1(rng);
            int location = uni2(rng);
            while (genVector[pos]==HEART){
                this->curLives++;
                if (this->curLives>this->maxLives){
                    pos = uni1(rng);
                }
                else {
                    break;
                }
            }
            switch (genVector[pos]){
                case ENEMY: generateEnemy(scene,location);
                    break;
                case FENCE: generateFence(scene,location);
                    break;
                case HEART: generateHeart(scene,location);
                    break;
            }
        }
        else {
            break;
        }
    }
    return true;
}

void generator::Render(Scene &scene) {

}

void generator::generateEnemy(Scene &scene, int where) {
    auto spider = EnemyPtr(new enemy{});
    spider->position.z = this->position.z;
    switch (where){
        case LEFT: spider->position.x = -0.5f;
            break;
        case RIGHT: spider->position.x = 0.5f;
            break;
        case CENTER: spider->position.x = 0.0f;
    }
    spider->setWorldPosition(spider->position);
    scene.objects.push_back(spider);
}

void generator::generateFence(Scene &scene, int where) {
    auto fence1 = FencePtr(new fence{});
    auto fence2 = FencePtr(new fence{});
    switch (where){
        case LEFT:
            fence1->position.z = this->position.z;
            fence1->position.x = -0.5;
            scene.objects.push_back(fence1);
            fence2->position.z = this->position.z;
            fence2->position.x = 0;
            scene.objects.push_back(fence2);
            break;
        case RIGHT:
            fence1->position.z = this->position.z;
            fence1->position.x = 0.5;
            scene.objects.push_back(fence1);
            fence2->position.z = this->position.z;
            fence2->position.x = 0;
            scene.objects.push_back(fence2);
            break;
        case CENTER:
            fence1->position.z = this->position.z;
            fence1->position.x = -0.5;
            scene.objects.push_back(fence1);
            fence2->position.z = this->position.z;
            fence2->position.x = 0.5;
            scene.objects.push_back(fence2);
            break;
    }
}

void generator::generateHeart(Scene &scene, int where) {
    auto heartPtr = HeartPtr(new heart{});
    heartPtr->position.z = this->position.z;
    switch (where){
        case LEFT: heartPtr->position.x = -0.5f;
            break;
        case RIGHT: heartPtr->position.x = 0.5f;
            break;
        case CENTER: heartPtr->position.x = 0.0f;
    }
    scene.objects.push_back(heartPtr);
}

void generator::generatePortal(Scene &scene) {

}
