#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Render/Renderer.hpp"

static Renderer renderer = Renderer ();

int main (void) {

    renderer.RenderFrame ();

    return 0;
}