#include <headers/explosion.h>
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