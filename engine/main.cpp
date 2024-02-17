#include "display.h"


bool isRunning = false;

void setup() {
    isRunning = initializeWindow();
}

void render() {
    displayUpdate();
//    renderColorBuffer();
//    clearColorBuffer(0xFF000000);
//    renderColorBuffer();
//    clearColorBuffer(0xFF000000);
}

void handleInput() {
    SDL_Event event = processInput();

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
    }
}

void update() {
//    drawPixel(100, 100, 0xFFFFFFFF);
//    drawPixel(101, 100, 0xFFFFFFFF);
//    drawPixel(101, 101, 0xFFFFFFFF);
//    drawPixel(100, 101, 0xFFFFFFFF);
}

int main() {
    setup();

    while (isRunning) {
        handleInput();
        update();
        render();
    }

    destroyWindow();
    return 0;
}