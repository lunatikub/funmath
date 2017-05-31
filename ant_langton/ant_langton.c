#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <SDL.h>

#include "sdl_common.h"
#include "ant_langton.h"
#include "ant_langton_cfg.h"

/**
 * configuration
 */
#define __SZ (2)
static ant_trans_t *cfg = cfg_3;

static const int width  = 1024;
static const int height = 1024;
#define __SZ_2 (__SZ / 2)

void quad(SDL_Surface *screen)
{
    int n =0;

    for (n = 0; n < width; n += __SZ) {
        draw_line(screen, n, 0, n, height, BLACK);
    }

    for (n = 0; n < height; n += __SZ) {
        draw_line(screen, 0, n, width, n, BLACK);
    }
}

void fill_rec(SDL_Surface *screen, int x, int y, Uint32 color)
{
    SDL_Rect rect = {
        .x = x,
        .y = y,
        .w = __SZ,
        .h = __SZ,
    };

    SDL_FillRect(screen, &rect, color);
}

int next_s(int s, int r)
{
    if (r == __LR) {
        switch (s) {
            case __U: return __L;
            case __L: return __D;
            case __D: return __R;
            case __R: return __U;
        }
    }

    switch (s) {
        case __U: return __R;
        case __L: return __U;
        case __D: return __L;
        case __R: return __D;
    }

    return 0;
}

int move(int *x, int *y, int s)
{
    switch(s) {
        case __U: *y -= __SZ; break;
        case __L: *x -= __SZ; break;
        case __D: *y += __SZ; break;
        case __R: *x += __SZ; break;
    }

    if (*y < 0 ||
        *y >= height ||
        *x < 0 ||
        *x >= width) {
        return 1;
    }
    return 0;
}

static inline int color2idx(int color)
{
    switch (color) {
        case WHITE:  return __WHITE;
        case BLACK:  return __BLACK;
        case RED:    return __RED;
        case GREEN:  return __GREEN;
        case BLUE:   return __BLUE;
        case SKY:    return __SKY;
        case PURPLE: return __PURPLE;
        case GREY:   return __GREY;
        case YELLOW: return __YELLOW;
        case DRED:   return __DRED;
        case DGREEN: return __DGREEN;
    };

    return __WHITE;
}

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	return 1;
    }

    atexit(SDL_Quit);

    SDL_Surface *screen = SDL_SetVideoMode(width, height, 0, SDL_DOUBLEBUF);

    if (screen == NULL) {
        return 2;
    }

    SDL_LockSurface(screen);

    SDL_FillRect(screen, NULL, WHITE);

    int x = 512 + __SZ_2;
    int y = 512 + __SZ_2;
    int s = __U;

    Uint32 curr_color = 0;
    Uint32 next_color = 0;
    Uint32 rotation = 0;

    while (1) {

        curr_color = get_pixel(screen, x, y);
        next_color = cfg[color2idx(curr_color)].color;

        fill_rec(screen, x - __SZ_2, y - __SZ_2, next_color);

        curr_color = get_pixel(screen, x, y);
        rotation   = cfg[color2idx(curr_color)].rotation;
        s = next_s(s, rotation);

        if (move(&x, &y, s)) {
            break;
        }

        SDL_Flip(screen);
    }

    getchar();
    SDL_FreeSurface(screen);

    return 0;
}
