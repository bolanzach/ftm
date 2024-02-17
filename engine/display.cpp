#include <cassert>
#include "display.h"

SDL_Window* window = nullptr;
//SDL_Renderer* renderer = nullptr;
//SDL_Texture* colorBufferTexture;

// Notice that this is a pointer. It acts as an array of memory where the pointer is
// the first element in the allocated array.
//color_t* colorBuffer = nullptr;

int windowWidth = 800;
int windowHeight = 500;

bool initializeWindow() {
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
            "Zengine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_OPENGL
    );

    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    GLenum initGLEW(glewInit());

    // Get graphics info
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    return true;
}

void displayUpdate() {
    SDL_GL_SwapWindow(window);
}

void destroyWindow() {
//    free(colorBuffer);
//    SDL_DestroyRenderer(renderer);
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