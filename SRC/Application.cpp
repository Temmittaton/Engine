#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Render/Renderer.hpp"
#include "World/World.h"
#include "GameManager/GameManager.hpp"

static Renderer renderer = Renderer ();
static World* world = new World (glm::vec3 (64), 16, 16, glm::vec3 (0.6, 0.6, 1));
static GameManager* gameManager = new GameManager ();

int main (void) {
    gameManager->Init ();
    renderer.RenderInit ();

    renderer.RenderFrame (gameManager);

    return 0;
}