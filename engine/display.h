#ifndef FTM_DISPLAY_H
#define FTM_DISPLAY_H


#include "SDL.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

typedef uint32_t color_t;

bool initializeWindow();
void destroyWindow();
void renderColorBuffer();
void clearColorBuffer(color_t color);
SDL_Event processInput();
void drawPixel(int x, int y, color_t color);

#endif //FTM_DISPLAY_H
