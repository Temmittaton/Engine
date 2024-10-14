#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Render/Renderer.hpp"
#include "World/World.h"

static Renderer renderer = Renderer ();
static World world = World (glm::vec3 (64), 16, 16, glm::vec3 (0.6, 0.6, 1));

int main (void) {
    renderer.RenderInit ();

    renderer.RenderFrame (world);

    return 0;
}