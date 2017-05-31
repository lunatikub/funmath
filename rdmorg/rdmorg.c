#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <SDL.h>

#include "sdl_common.h"

#define H (1024)
#define W (1024)
#define N (256)

#define WN  (W / N)
#define H2  (H / 2)
#define H2N ((H / 2) / N)

int main(void)
{
    long int rdm = 0;
    SDL_Surface *screen = NULL;

    srandom(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	return -1;
    }

    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(W, H, 0, SDL_DOUBLEBUF);

    if (screen == NULL) {
        return -2;
    }

    uint32_t i = 0;

    for (i = 0; i < 30; ++i) {

        SDL_LockSurface(screen);

        SDL_FillRect(screen, NULL, 0x00000000);

        draw_line(screen, 0, H2, W, 0, 0xffffffff);
        draw_line(screen, 0, H2, W, H, 0xffffffff);

        uint32_t n  = 0;
        int32_t  _w = 0;

        for (n = 0; n < N - 1; ++n) {
            _w = (N - 2) - (2 * n);

            draw_line(screen,
                      W, H2 + (_w * H2N),
                      ((n + 1) * W) / N, H2 - (n + 1) * (H2 / N),
                      WHITE);

            draw_line(screen,
                      W, H2 - (_w * H2N),
                      ((n + 1) * W) / N, H2 + (n + 1) * (H2 / N),
                      0xffffffff);
        }

        uint32_t cx = 0;
        uint32_t cy = H2;
        uint32_t nx = 0;
        uint32_t ny = 0;

        for (n = 0; n < N; ++n) {
            rdm = random() % 2;
            if (rdm) {
                ny = cy - H2N;
            } else {
                ny = cy + H2N;
            }
            nx = cx + WN;

            draw_line(screen, cx, cy, nx, ny, RED);

            cx = nx;
            cy = ny;

            /* usleep(N * 10); */

            SDL_FreeSurface(screen);
            SDL_Flip(screen);
        }

        SDL_FreeSurface(screen);
        SDL_Flip(screen);
        usleep(50000);
    }

    pause();

    return 0;
}
