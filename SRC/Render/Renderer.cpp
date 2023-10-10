#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.hpp"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

// Settings
void framebuffer_size_callback (GLFWwindow* window, int width, int height);
void processInput (GLFWwindow* window);

int SCR_WIDTH = 960;
int SCR_HEIGHT = 540;

// Constructors

// Methods
static ShaderProgramSource ParseShader (const std::string& filepath) {
    std::ifstream stream (filepath);

    enum class ShaderType {
        NONE = -1, VERT = 0, FRAG = 1
    };

    std::string line;
    std::stringstream ss [2];
    ShaderType type = ShaderType::NONE;
    while (getline (stream, line)) {
        /*if (&line [0] == "/") {
            continue;
        }*/
        if (line.find ("#shader") != std::string::npos) {
            if (line.find ("vertex") != std::string::npos) {
                type = ShaderType::VERT;
            }
            else if (line.find ("fragment") != std::string::npos) {
                type = ShaderType::FRAG;
            }
        }
        else {
            ss [(int)type] << line << '\n';
        }
    }

    return {ss [0].str (), ss [1].str ()};
}
static unsigned int CompileShader (unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader (type);
    const char* src = source.c_str ();
    glShaderSource (id, 1, &src, nullptr);
    glCompileShader (id);

    int result;
    glGetShaderiv (id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv (id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca (length * sizeof (char));
        glGetShaderInfoLog (id, length, &length, message);
        std::cout << "Failed to compile shader !" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader (id);

        return 0;
    }

    return id;
}
static unsigned int CreateShader (const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram ();
    unsigned int vs = CompileShader (GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader (GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader (program, vs);
    glAttachShader (program, fs);
    glLinkProgram (program);
    glValidateProgram (program);

    glDeleteShader (vs);
    glDeleteShader (fs);

    return program;
}
void UpdateQuadVertices (float* vertices, int windowWidth, int windowHeight) {
    float halfWidth = windowWidth / 2.0f;
    float halfHeight = windowHeight / 2.0f;

    vertices [0] = -halfWidth;
    vertices [1] = -halfHeight;
    vertices [5] = halfWidth;
    vertices [6] = -halfHeight;
    vertices [10] = -halfWidth;
    vertices [11] = halfHeight;
    vertices [15] = halfWidth;
    vertices [16] = halfHeight;
}

void Renderer::RenderInit () {
    // Initialize GLFW
    if (!glfwInit ()) {
        std::cerr << "GLFW initialization failed" << std::endl;
    }

    // Configure GLFW
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    window = glfwCreateWindow (SCR_WIDTH, SCR_HEIGHT, "Fullscreen Shader", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate ();
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent (window);

    // Initialize GLEW
    if (glewInit () != GLEW_OK) {
        std::cerr << "GLEW initialization failed" << std::endl;
        glfwTerminate ();
    }

    // Calculate vertices for the centered and resized quad
    quad [0] = -SCR_WIDTH / 2;
    quad [5] = SCR_WIDTH / 2;
    quad [10] = -SCR_WIDTH / 2;
    quad [15] = SCR_WIDTH / 2;
    quad [1] = -SCR_HEIGHT / 2;
    quad [6] = -SCR_HEIGHT / 2;
    quad [11] = SCR_HEIGHT / 2;
    quad [16] = SCR_HEIGHT / 2;

    glGenVertexArrays (1, &VAO);
    glGenBuffers (1, &VBO);

    glBindVertexArray (VAO);
    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (quad), quad, GL_STATIC_DRAW);

    // Specify the vertex attributes
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void*)0);
    glEnableVertexAttribArray (0);

    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void*)(3 * sizeof (float)));
    glEnableVertexAttribArray (1);
}
void Renderer::RenderFrame (World* world) {
    // Compile and link the shaders
    ShaderProgramSource source = ParseShader ("SRC/Render/Shaders/baseShader.shader");

    unsigned int shader = CreateShader (source.VertexSource, source.FragmentSource);

    while (!glfwWindowShouldClose (window)) {
        // Get the window size
        glfwGetWindowSize (window, &SCR_WIDTH, &SCR_HEIGHT);

        // Set shader variables
        int uniform_WindowSize = glGetUniformLocation (shader, "_WindowDimensions");
        int uniform_Camera = glGetUniformLocation (shader, "_Camera");

        // SSBOs for WorldActors and Lights
        unsigned int wSSBO, lSSBO;
        Mesh* wArray = world->GetSceneActors ();
        Light* lArray = world->GetLights ();
        glGenBuffers (1, &wSSBO);
        glBindBuffer (GL_SHADER_STORAGE_BUFFER, wSSBO);
        glBufferData (GL_SHADER_STORAGE_BUFFER, sizeof (wArray), wArray, GL_STATIC_READ);
        glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 3, wSSBO);
        glBindBuffer (GL_SHADER_STORAGE_BUFFER, 0);

        glGenBuffers (1, &lSSBO);
        glBindBuffer (GL_SHADER_STORAGE_BUFFER, lSSBO);
        glBufferData (GL_SHADER_STORAGE_BUFFER, sizeof (lArray), lArray, GL_STATIC_READ);
        glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 4, lSSBO);
        glBindBuffer (GL_SHADER_STORAGE_BUFFER, 0);

        // Use the shader program
        glUseProgram (shader);
        glUniform2f (uniform_WindowSize, SCR_WIDTH, SCR_HEIGHT);

        // Update quad
        UpdateQuadVertices (quad, SCR_WIDTH, SCR_HEIGHT);
        glBindVertexArray (VAO);
        glBindBuffer (GL_ARRAY_BUFFER, VBO);
        glBufferData (GL_ARRAY_BUFFER, sizeof (quad), quad, GL_STATIC_DRAW);

        // Render the full-screen quad
        glBindVertexArray (VAO);
        glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);

        // Swap buffers and poll events
        glfwSwapBuffers (window);
        glfwPollEvents ();
    }

    // Cleanup
    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1, &VBO);
    glDeleteProgram (shader);

    glfwTerminate ();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput (GLFWwindow* window) {
    if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose (window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
    glViewport (0, 0, width, height);
}