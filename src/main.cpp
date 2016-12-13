// Example gl_scene
// - Demonstrates the concept of a scene
// - Uses abstract object interface for Update and Render steps
// - Creates a simple game scene with Player, Asteroid and Space objects
// - Contains a generator object that does not render but adds Asteroids to the scene
// - Some objects use shared resources and all object deallocations are handled automatically
// - Controls: LEFT, RIGHT, "R" to reset, SPACE to fire

#include <iostream>
#include <vector>
#include <map>
#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene.h"
#include "camera.h"
#include "player.h"
#include "ground.h"
#include "fence.h"
#include "portal.h"
#include "heart.h"
#include "enemy.h"
#include "word.h"
#include "back.h"
#include "generator.h"
#include "combined.h"
#include "enemyAnimate.h"

#define DEF_LIVES 3

const unsigned int SIZE = 700;
int currentLevel = 1;
Scene scene;


// Set up the scene
void InitializeScene(int lives,int level) {
  scene.objects.clear();

  // Create a camera
  auto camera = CameraPtr(new Camera{ 60.0f, 1.0f, 0.1f, 40.0f});
  //camera->position.z = -10.0f;
  scene.camera = camera;

  // Add generator to scene

  // Add player to the scene
  auto player = PlayerPtr(new Player{camera});
  player->position.y = -0.8;
  player->position.z = -3;
    player->scale = glm::vec3(0.3,0.3,0.3);
  scene.objects.push_back(player);
  scene.player = player;

  //add test object
    auto test = GroundPtr(new ground{});
    test->position.z = -100;
    scene.objects.push_back(test);

    auto object = EnemyPtr(new enemy{});
//    object->scale = glm::vec3(3,3,3);
//    object->position.y = -5.7;
    object->position.z = -5;
    object->position.x = 1.0;
//    object->rotation.z = PI;
    //scene.objects.push_back(object);

    auto object4 = PortalPtr(new portal{});
    object4->position.z = -100;
    object4->position.x = 1.0;
    //scene.objects.push_back(object4);

  auto background = BackPtr(new back{SIZE,SIZE});
  scene.objects.push_back(background);

    auto objectOSD = WordPtr(new word{"Xww: ",20,50,0.7f,SIZE,SIZE});
    scene.objects.push_back(objectOSD);

  auto objectOSD2 = WordPtr(new word{"Yzz: ",20,(SIZE/10)*9,0.7f,SIZE,SIZE});
  objectOSD2->setChangeable(true);
  scene.objects.push_back(objectOSD2);


    auto object2 = HeartPtr(new heart{});
    object2->position.z = -4;
    object2->position.x = 1.0;
    //scene.objects.push_back(object2);

    auto gene = GeneratorPtr(new generator{player});
    scene.objects.push_back(gene);

    auto combi = CombiPtr(new combined{});
    //scene.objects.push_back(combi);
    auto animacny = EnemyAnimPtr(new enemyAnimate{});
    //scene.objects.push_back(animacny);
    auto animacny2 = EnemyAnimPtr(new enemyAnimate{});
    animacny2->position.z = -6.0f;
    //scene.objects.push_back(animacny2);

  auto object3 = FencePtr(new fence{});
  object3->position.z = -3;
  object3->position.x = 1.0;
  //scene.objects.push_back(object3);
  scene.playerStatus = 4;
}

// Keyboard press event handler
void OnKeyPress(GLFWwindow* /* window */, int key, int /* scancode */, int action, int /* mods */) {
  scene.keyboard[key] = action;

  // Reset
  if (key == GLFW_KEY_R && action == GLFW_PRESS) {
    InitializeScene(DEF_LIVES,0);
  }
}

// Mouse move event handler
void OnMouseMove(GLFWwindow* /* window */, double xpos, double ypos) {
  scene.mouse.x = xpos;
  scene.mouse.y = ypos;
}

int main() {
    // vytvorit generator a spravanie hraca,
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW!" << std::endl;
    return EXIT_FAILURE;
  }

  // Setup OpenGL context
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Try to create a window
  auto window = glfwCreateWindow(SIZE, SIZE, "QuickBall", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to open GLFW window, your graphics card is probably only capable of OpenGL 2.1" << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }

  // Finalize window setup
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  glewInit();
  if (!glewIsSupported("GL_VERSION_3_3")) {
    std::cerr << "Failed to initialize GLEW with OpenGL 3.3!" << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }

  // Add keyboard and mouse handlers
  glfwSetKeyCallback(window, OnKeyPress);
  glfwSetCursorPosCallback(window, OnMouseMove);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // Hide mouse cursor
  glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

  // Initialize OpenGL state
  // Enable Z-buffer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  // Enable polygon culling
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
    // Set OpenGL options
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  InitializeScene(DEF_LIVES,0);

  // Track time
  float time = (float)glfwGetTime();

  // Main execution loop
  while (!glfwWindowShouldClose(window)) {
    // Compute time delta
    float dt = (float)glfwGetTime() - time;
    time = (float)glfwGetTime();

    // Set gray back
    glClearColor(0.0f,0.0f,0.0f,0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update and render all objects
    int up = scene.Update(dt);
    scene.Render();
    std::cout << scene.playerStatus << std::endl;
      if (up==0){//NORMAL
          ;
      }
      if (up==-1){//GAME OVER
          InitializeScene(DEF_LIVES,-1);
      }
      if (up==-1){//NEXT LEVEL
          InitializeScene(scene.playerStatus,++currentLevel);
      }
    // Display result
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up
  glfwTerminate();

  return EXIT_SUCCESS;
}
