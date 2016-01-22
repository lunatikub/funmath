#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <SDL.h>

/*
 * This is a 32-bit pixel function created with help from this
 * website: http://www.libsdl.org/intro.en/usingvideo.html
 *
 * You will need to make changes if you want it to work with
 * 8-, 16- or 24-bit surfaces.  Consult the above website for
 * more information.
 */
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}

/*
 * This is an implementation of the Midpoint Circle Algorithm
 * found on Wikipedia at the following link:
 *
 *   http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
 *
 * The algorithm elegantly draws a circle quickly, using a
 * set_pixel function for clarity.
 */
void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{
    // if the first pixel in the screen is represented by (0,0) (which is in sdl)
    // remember that the beginning of the circle is not in the middle of the pixel
    // but to the left-top from it:

    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;

    while (x >= y)
    {
        set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
        set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);

        if (x != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
            set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }

        if (y != 0)
        {
            set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }

        if (x != 0 && y != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void draw_line(SDL_Surface *screen, int x0, int y0, int x1, int y1, Uint32 pixel)
{
  int i;
  double x = x1 - x0;
  double y = y1 - y0;
  double length = sqrt( x*x + y*y );
  double addx = x / length;
  double addy = y / length;

  x = x0;
  y = y0;

  for (i = 0; i < length; i += 1) {
      set_pixel(screen, x, y, pixel);
      x += addx;
      y += addy;
  }
}


int main(void)
{
    static const int width = 1024;
    static const int height = 1024;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	return 1;
    }

    atexit(SDL_Quit);

    SDL_Surface *screen = SDL_SetVideoMode(width, height, 0, SDL_DOUBLEBUF);

    if (screen == NULL) {
        return 2;
    }

    SDL_LockSurface(screen);

    /**
     * Configuration
     */
    double mod = 269;
    double src = 2;
    int    r   = 500;

    for (src = 2; src < 100; src += 0.01) {

        SDL_FillRect(screen, NULL, 0x00000000);
        draw_circle(screen, 512, 512, r, 0xffffffff);

        double n = 0;
        double dst = 0;

        for (n = 0; n < mod; ++n) {

            /* dst = (src * n) % mod; */
            dst = fmod((src * n), mod);

            double x_src = (cos(((M_PI * 2) / mod) * n) * r) + 512;
            double y_src = (sin(((M_PI * 2) / mod) * n) * r) + 512;

            double x_dst = (cos(((M_PI * 2) / mod) * dst) * r) + 512;
            double y_dst = (sin(((M_PI * 2) / mod) * dst) * r) + 512;

            uint32_t res = ((uint32_t)n) % 3;
            uint32_t color = 0;

            /* switch (res) { */
            /*     case 0: color = 0xff0000ff; break; */
            /*     case 1: color = 0xff00ff00; break; */
            /*     case 2: color = 0xffff0000; break; */
            /* } */

            draw_line(screen, x_src, y_src, x_dst, y_dst, 0xffffffff);
        }

        SDL_FreeSurface(screen);
        SDL_Flip(screen);
    }

    return 0;
}
