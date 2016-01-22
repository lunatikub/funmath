#include <math.h>
#include <SDL.h>

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}

Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;

    return *(Uint32 *)target_pixel;
}

void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{
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

/**
 * x0,y0 +--------+
 *       +        +
 *       +        +
 *       +        +
 *       +--------+ x1,y1
 */
void draw_rec(SDL_Surface *screen, int x0, int y0, int x1, int y1, Uint32 pixel)
{
    draw_line(screen, x0, y0, x1, y0, pixel);
    draw_line(screen, x1, y0, x1, y0, pixel);
    draw_line(screen, x1, y0, x1, y1, pixel);
    draw_line(screen, x1, y1, x0, y1, pixel);
}
