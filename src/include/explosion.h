#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <texture.h>
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
Explosion::Explosion()
{
    explosion_frame = 0;
}
Explosion::~Explosion()
{
    free();
}
void Explosion::setClips()
{
    for (int order = 0; order < TOTAL_CLIPS; order++)
    {
        clips[order] = {EXPLOSION_WIDTH * order, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};
    }
}
void Explosion::setFrame(const int &_frame, const int &frameDelay)
{
    explosion_frame = _frame / frameDelay;
}
void Explosion::renderExplosion(SDL_Renderer *gRenderer, const int &x, const int &y)
{
    if (explosion_frame >= TOTAL_CLIPS)
    {
        explosion_frame = 0;
    }
    SDL_Rect *p_clip = &clips[explosion_frame];
    render(gRenderer, x, y, p_clip);
}
#endif