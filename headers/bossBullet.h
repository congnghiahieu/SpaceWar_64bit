#ifndef BOSS_BULLET_H
#define BOSS_BULLET_H
#include <headers/texture.h>
enum BossBulletType
{
    BOSS_BULLET_RED,
    BOSS_BULLET_RED_WIDTH = 80,
    BOSS_BULLET_RED_HEIGHT = 100,
    BOSS_BULLET_RED_VEL = 6,
    BOSS_BULLET_GREEN,
    BOSS_BULLET_GREEN_WIDTH = 50,
    BOSS_BULLET_GREEN_HEIGHT = 70,
    BOSS_BULLET_GREEN_VEL = 7,
    BOSS_BULLET_GAS,
    BOSS_BULLET_GAS_WIDTH = 130,
    BOSS_BULLET_GAS_HEIGHT = 120,
    BOSS_BULLET_GAS_VEL = 5,
    /*
    BOSS_BULLET_FIRE = 12,
    BOSS_BULLET_FIRE_WIDTH = 180,
    BOSS_BULLET_FIRE_HEIGHT = 200,
    BOSS_BULLET_FIRE_VEL = 4
    */
};
class BossBullet : public Texture
{
private:
    // Offsets of bullet
    int bulletX;
    int bulletY;
    int bulletW;
    int bulletH;
    int bulletVel;

    // Typf of bullet
    int bulletType;

    // Checking bullet is moving
    bool is_move;

    // Collision box of bullet
    SDL_Rect bulletCollisionBox;

public:
    // Initialize bullet
    BossBullet();
    // Deallocate bullet
    ~BossBullet();

    // Modified bullets
    void setBulletOffset(const int &x, const int &y);
    void setBulletSize(const int &width, const int &height);
    // Collision
    void updateCollisionBox();
    SDL_Rect getCollisionBox();
    // move status
    void setBulletMoveStatus(const bool &type);
    bool getBulletMoveStatus();
    // Handling type of bullet
    void setType(const int &type, SDL_Renderer *gRenderer);
    int getType();
    // Move and render
    void move(const int &y_axis_border);
    void renderBullet(SDL_Renderer *gRenderer);
};
#endif