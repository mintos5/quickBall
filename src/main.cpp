// quickBall
// Can you move small ball to soccer goal?
// - Controls: LEFT, RIGHT, "R" to reset, ENTER to continue

#include <iostream>
#include <vector>
#include <map>
#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>

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

#define DEF_LIVES 1
#define DEF_SPEED 3

const unsigned int SIZE = 700;
int currentLevel;
float currentSpeed;
Scene scene;


// Set up the scene
void InitializeScene(int level) {
    scene.objects.clear();
    // Create a camera
    auto camera = CameraPtr(new Camera{ 60.0f, 1.0f, 0.1f, 40.0f});
    //camera->position.z = -10.0f;
    scene.camera = camera;

    //NEW GAME
    if (level==0){
        auto title = WordPtr(new word{"QuickBall",SIZE/3,SIZE/2,1.0f,SIZE,SIZE});
        scene.objects.push_back(title);
        auto controls = WordPtr(new word{"Control with arrows, press Enter to play game",SIZE/20,SIZE/17,0.6f,SIZE,SIZE});
        scene.objects.push_back(controls);
        scene.playerStatus = DEF_LIVES;
        currentLevel = 1;
        currentSpeed = DEF_SPEED;
        //LOAD ALL before loading
        auto objec1 = EnemyPtr(new enemy{});
        auto object2 = HeartPtr(new heart{});
        auto object3 = CombiPtr(new combined{});
        auto object4 = FencePtr(new fence{});
        auto object5 = EnemyAnimPtr(new enemyAnimate{});
        auto object6 = PortalPtr(new portal{});
    }
    //GAME OVER
    if (level==-1){
        auto title = WordPtr(new word{"GAME OVER",SIZE/3,SIZE/2,0.7f,SIZE,SIZE});
        scene.objects.push_back(title);
        std::stringstream ss;
        ss << "ON " << currentLevel << ". LEVEL";
        auto levelTitle = WordPtr(new word{ss.str(),SIZE/3,SIZE/3,0.7f,SIZE,SIZE});
        scene.objects.push_back(levelTitle);
        scene.playerStatus = DEF_LIVES;
        currentLevel = 1;
        currentSpeed = DEF_SPEED;
    }
    if (level==-2){
        currentLevel++;
        currentSpeed +=1.1f;

        std::stringstream ss;
        ss << "NEXT LEVEL " << currentLevel;
        auto title = WordPtr(new word{ss.str(),SIZE/3,SIZE/2,0.7f,SIZE,SIZE});
        scene.objects.push_back(title);
    }

    if (level>0) {
        // Add player to the scene
        auto player = PlayerPtr(new Player{camera});
        player->position.y = -0.8;
        player->position.z = -3;
        player->setSpeed(currentSpeed);
        scene.objects.push_back(player);
        scene.player = player;

        //GROUND
        auto test = GroundPtr(new ground{});
        test->position.z = -100;
        scene.objects.push_back(test);

        //BACKGROUND
        auto background = BackPtr(new back{SIZE,SIZE});
        scene.objects.push_back(background);

        // Add generator to scene
        auto gene = GeneratorPtr(new generator{player});
        scene.objects.push_back(gene);

        //Add OSD
        auto objectOSD2 = WordPtr(new word{"",20,(SIZE/10)*9,0.7f,SIZE,SIZE});
        objectOSD2->setChangeable(true);
        scene.objects.push_back(objectOSD2);
    }
}

// Keyboard press event handler
void OnKeyPress(GLFWwindow* /* window */, int key, int /* scancode */, int action, int /* mods */) {
    scene.keyboard[key] = action;
    // Reset
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        scene.playerStatus = 1;
        InitializeScene(1);
    }
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        InitializeScene(currentLevel);
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

  InitializeScene(0);

  // Track time
  float time = (float)glfwGetTime();

  // Main execution loop
  while (!glfwWindowShouldClose(window)) {
    // Compute time delta
    float dt = (float)glfwGetTime() - time;
    time = (float)glfwGetTime();

    // Set black back
    glClearColor(0.0f,0.0f,0.0f,0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update and render all objects
    int up = scene.Update(dt);
    scene.Render();
      if (up==0){//NORMAL
          ;
      }
      if (up==-1){//GAME OVER
          InitializeScene(-1);
      }
      if (up==1){//NEXT LEVEL
          InitializeScene(-2);
      }
    // Display result
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up
  glfwTerminate();

  return EXIT_SUCCESS;
}
