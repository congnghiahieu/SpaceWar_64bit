#ifndef BOSS_BULLET_H
#define BOSS_BULLET_H
#include <texture.h>
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
BossBullet::BossBullet()
{
    bulletX = 0;
    bulletY = 0;
    bulletW = 0;
    bulletH = 0;
    bulletVel = 0;
    is_move = false;
    bulletCollisionBox = {0, 0, 0, 0};
}
BossBullet::~BossBullet()
{
    free();
}
void BossBullet::setBulletOffset(const int &x, const int &y)
{
    bulletX = x;
    bulletY = y;
    updateCollisionBox();
}
void BossBullet::setBulletSize(const int &width, const int &height)
{
    bulletW = width;
    bulletH = height;
    updateCollisionBox();
}
void BossBullet::updateCollisionBox()
{
    switch (bulletType)
    {
    case BOSS_BULLET_RED:
        bulletCollisionBox = {bulletX + (BOSS_BULLET_RED_WIDTH - 66) / 2, bulletY + 60, 66, 30};
        break;
    case BOSS_BULLET_GREEN:
        bulletCollisionBox = {bulletX + (BOSS_BULLET_GREEN_WIDTH - 44) / 2, bulletY + 40, 44, 22};
        break;
    case BOSS_BULLET_GAS:
        bulletCollisionBox = {bulletX + 10, bulletY + 70, 96, 40};
        break;
        /*
        case BOSS_BULLET_FIRE:
            bulletCollisionBox = {bulletX + 5, bulletY + 120, 170, 65};
            break;
        */
    }
}
SDL_Rect BossBullet::getCollisionBox()
{
    return bulletCollisionBox;
}
void BossBullet::setBulletMoveStatus(const bool &type)
{
    is_move = type;
}
bool BossBullet::getBulletMoveStatus()
{
    return is_move;
}
void BossBullet::setType(const int &type, SDL_Renderer *gRenderer)
{

    bulletType = type;
    switch (bulletType)
    {
    case BOSS_BULLET_RED:
        this->loadFromFile(gRenderer, "res/boss_bullet_1.png");
        setBulletSize(BOSS_BULLET_RED_WIDTH, BOSS_BULLET_RED_HEIGHT);
        bulletVel = BOSS_BULLET_RED_VEL;
        break;
    case BOSS_BULLET_GREEN:
        this->loadFromFile(gRenderer, "res/boss_bullet_2.png");
        setBulletSize(BOSS_BULLET_GREEN_WIDTH, BOSS_BULLET_GREEN_HEIGHT);
        bulletVel = BOSS_BULLET_GREEN_VEL;
        break;
    case BOSS_BULLET_GAS:
        this->loadFromFile(gRenderer, "res/boss_bullet_3.png");
        setBulletSize(BOSS_BULLET_GAS_WIDTH, BOSS_BULLET_GAS_HEIGHT);
        bulletVel = BOSS_BULLET_GAS_VEL;
        break;
        /*
        case BOSS_BULLET_FIRE:
            this->loadFromFile(gRenderer, "res/boss_bullet_4.png");
            setBulletSize(BOSS_BULLET_FIRE_WIDTH, BOSS_BULLET_FIRE_HEIGHT);
            bulletVel = BOSS_BULLET_FIRE_VEL;
            break;
        */
    }
}
int BossBullet::getType()
{
    return bulletType;
}
void BossBullet::move(const int &y_axis_border)
{
    bulletY += bulletVel;
    updateCollisionBox();
    if (bulletY > y_axis_border)
    {
        is_move = false;
    }
}
void BossBullet::renderBullet(SDL_Renderer *gRenderer)
{
    render(gRenderer, bulletX, bulletY);
}
#endif