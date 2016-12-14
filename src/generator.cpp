//
// Created by michal on 9.12.2016.
//

#include "generator.h"
#include "fence.h"
#include "enemy.h"
#include "heart.h"
#include "portal.h"
#include "combined.h"
#include "enemyAnimate.h"

#define BUFFER 30.0f
#define LEFT 1
#define CENTER 2
#define RIGHT 3
#define ENEMY 1
#define FENCE 2
#define HEART 3
#define SUPER_HEART 4
#define SUPER_ENEMY 5
#define GEN_LENGHT -95.0f

generator::generator(const PlayerPtr &player) : player(player) {
    this->position = glm::vec3(0.0f,0.0f,-3.0f);
    this->rng = std::mt19937(rd());
    genVector.push_back(ENEMY);
    genVector.push_back(ENEMY);
    genVector.push_back(FENCE);
    genVector.push_back(FENCE);
    genVector.push_back(FENCE);
    genVector.push_back(FENCE);
    genVector.push_back(FENCE);
    genVector.push_back(FENCE);
    genVector.push_back(FENCE);
    genVector.push_back(HEART);
    genVector.push_back(SUPER_ENEMY);
    genVector.push_back(SUPER_HEART);
    this->uni1 = std::uniform_int_distribution<int>(0,genVector.size()-1);
    this->uni2 = std::uniform_int_distribution<int>(1,3);
    this->lives.max = 2;
    this->extraLive.max = 121;
}

generator::~generator() {

}

bool generator::Update(Scene &scene, float dt) {
    //While until is generator moved to front
    while (position.z>=player->position.z-BUFFER){
        //if enables jumps
        if ( (player->position.z-BUFFER) - position.z<=-3.0f && position.z >= GEN_LENGHT){
            position.z -= 3.0f;
            int arrayPos = uni1(rng);
            int location = uni2(rng);
            //Generate only MAX HEARTS
            while (genVector[arrayPos]==HEART){
                if (this->lives.cur >= this->lives.max){
                    arrayPos = uni1(rng);
                }
                else {
                    this->lives.cur++;
                    break;
                }
            }
            //Generate only MAX SUPER_HEARTS
            while (genVector[arrayPos]==SUPER_HEART){
                if (this->extraLive.cur >= this->extraLive.max){
                    arrayPos = uni1(rng);
                }
                else {
                    this->extraLive.cur++;
                    break;
                }
            }
            switch (genVector[arrayPos]){
                case ENEMY: generateEnemy(scene,location);
                    break;
                case FENCE: generateFence(scene,location);
                    break;
                case HEART: generateHeart(scene,location);
                    break;
                case SUPER_HEART: generaSuperteHeart(scene,location);
                    break;
                case SUPER_ENEMY: generateSuperEnemy(scene,location);
                    break;
            }
        }
        else {
            if (position.z <= GEN_LENGHT && this->onePortal){
                onePortal = false;
                generatePortal(scene);
            }
            break;
        }
    }
    return true;
}

void generator::Render(Scene &scene) {}

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
    auto portalPtr = PortalPtr(new portal{});
    portalPtr->position.z = GEN_LENGHT-3.0f;
    std::cout << "Pridavam sa" << std::endl;
    scene.objects.push_back(portalPtr);
}

void generator::generateSuperEnemy(Scene &scene, int where) {
    auto animated = EnemyAnimPtr(new enemyAnimate{});
    animated->position.z = this->position.z;
    scene.objects.push_back(animated);
}

void generator::generaSuperteHeart(Scene &scene, int where) {
    auto combi = CombiPtr(new combined{});
    combi->position.z = this->position.z;
    scene.objects.push_back(combi);
}
