#ifndef SDL_COMMON_H_
# define SDL_COMMON_H_

#define WHITE  (0xffffffff)
#define BLACK  (0xff000000)
#define RED    (0xffff0000)
#define GREEN  (0xff00ff00)
#define BLUE   (0xff0000ff)
#define SKY    (0xff00ffff)
#define PURPLE (0xffff00ff)
#define GREY   (0xff888888)
#define YELLOW (0xffffff00)
#define DRED   (0xff8A0808)
#define DGREEN (0xff0B3B0B)

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 get_pixel(SDL_Surface *surface, int x, int y);

void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);
void draw_line(SDL_Surface *screen, int x0, int y0, int x1, int y1, Uint32 pixel);
void draw_rec(SDL_Surface *screen, int x0, int y0, int x1, int y1, Uint32 pixel);
void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);

#endif /* !SDL_COMMON_H_ */
