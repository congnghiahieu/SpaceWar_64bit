#ifndef BG_H
#define BG_H
#include <headers/texture.h>

const double FLOAT_SPEED = 0.75;

class Background : public Texture
{
public:
    Background();
    ~Background();

    void vertical_scrollingBG(SDL_Renderer *gRenderer);
    void horizontal_scrollingBG(SDL_Renderer *gRenderer);
};

#endif