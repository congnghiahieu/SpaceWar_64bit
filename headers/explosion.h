#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <headers/texture.h>
enum explosion
{
    EXPLOSION_WIDTH = 165,
    EXPLOSION_HEIGHT = 165,
    TOTAL_CLIPS = 4,
    FRAME_DELAY_MAIN = 10,
    FRAME_DELAY_BOSS = 10,
    BOSS_EXP_DURATION = 1800
};
class Explosion : public Texture
{
private:
    int explosion_frame;

    SDL_Rect clips[TOTAL_CLIPS];

public:
    Explosion();
    ~Explosion();

    void setClips();
    void setFrame(const int &_frame, const int &frameDelay);
    void renderExplosion(SDL_Renderer *gRenderer, const int &x, const int &y);
};

#endif