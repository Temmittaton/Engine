#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Render/Renderer.hpp"
#include "World/World.h"

static Renderer renderer = Renderer ();
static World world = World ();

int main (void) {
    renderer.RenderInit ();

    renderer.RenderFrame (&world);

    return 0;
}