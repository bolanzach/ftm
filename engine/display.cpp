#include <cassert>
#include "display.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* colorBufferTexture;

// Notice that this is a pointer. It acts as an array of memory where the pointer is
// the first element in the allocated array.
color_t* colorBuffer = nullptr;

int windowWidth = 800;
int windowHeight = 500;

bool initializeWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "error initializing SDL!\n");
        return false;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    windowWidth = displayMode.w;
    windowHeight = displayMode.h;

    window = SDL_CreateWindow(
            "Zengine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window!\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer!\n");
        return false;
    }

    /// This is where we allocate memory to hold all the pixels
    colorBuffer = (color_t*) malloc(sizeof(color_t) * windowWidth * windowHeight);
    assert(colorBuffer);

    // Texture used to display the color_buffer
    colorBufferTexture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            windowWidth,
            windowHeight
    );

    return true;
}

void destroyWindow() {
    free(colorBuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderColorBuffer() {
    SDL_UpdateTexture(
            colorBufferTexture,
            nullptr,
            colorBuffer,
            (int) (windowWidth * sizeof(color_t))
    );
    
    SDL_RenderCopy(renderer, colorBufferTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void clearColorBuffer(color_t color) {
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            drawPixel(x, y, color);
        }
    }
}

SDL_Event processInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    return event;
}

void drawPixel(int x, int y, color_t color) {
    if (x >= 0 && x < windowWidth && y >= 0 && y < windowHeight) {
        colorBuffer[(windowWidth * y) + x] = color;
    }
}