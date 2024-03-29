#include <cassert>
#include <iostream>
#include "display.h"
#include "mesh.h"

SDL_Window* window = nullptr;
//SDL_Renderer* renderer = nullptr;
//SDL_Texture* colorBufferTexture;

// Notice that this is a pointer. It acts as an array of memory where the pointer is
// the first element in the allocated array.
//color_t* colorBuffer = nullptr;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

int windowWidth = 800;
int windowHeight = 500;

unsigned int VAO;
unsigned int VBO;
unsigned int EBO;
unsigned int shaderProgram;

Mesh mesh;

bool initializeWindow() {
    // A good resource:
    // https://github.com/Gaetz/SDL-OpenGL

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    window = SDL_CreateWindow(
            "FtM",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_OPENGL
    );

    SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    GLenum initGLEW(glewInit());
    if (initGLEW != GLEW_OK) {
        return false;
    }

    // Get graphics info
//    const GLubyte* renderer = glGetString(GL_RENDERER);
//    const GLubyte* version = glGetString(GL_VERSION);

    glViewport(0, 0, windowWidth, windowHeight);
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ///// SHADERS /////
    ////////////////////
    int shaderCompileSuccess;
    char infoLog[512];

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompileSuccess);
    if (!shaderCompileSuccess) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompileSuccess);
    if (!shaderCompileSuccess) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Check for linking errors
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if(!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        ...
//    }

    ///// VERTICES /////
    ////////////////////
    mesh = Mesh::LoadFileObj("../assets/free_car_001.obj");

    // move the car down
    for (auto &v : mesh.vertices) {
        v.y -= 0.95f;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * mesh.vertices.size(), &mesh.vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mesh.faces.size() * 3, mesh.GetAllIndices(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return true;
}

void displayUpdate() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, mesh.vertices.size(), GL_UNSIGNED_INT, nullptr);

    // unbind VAO
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
}

void destroyWindow() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderColorBuffer() {
//    SDL_UpdateTexture(
//            colorBufferTexture,
//            nullptr,
//            colorBuffer,
//            (int) (windowWidth * sizeof(color_t))
//    );
//
//    SDL_RenderCopy(renderer, colorBufferTexture, nullptr, nullptr);
//    SDL_RenderPresent(renderer);
}

void clearColorBuffer(color_t color) {
//    for (int y = 0; y < windowHeight; y++) {
//        for (int x = 0; x < windowWidth; x++) {
//            drawPixel(x, y, color);
//        }
//    }
}

SDL_Event processInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    return event;
}

void drawPixel(int x, int y, color_t color) {
//    if (x >= 0 && x < windowWidth && y >= 0 && y < windowHeight) {
//        colorBuffer[(windowWidth * y) + x] = color;
//    }
}