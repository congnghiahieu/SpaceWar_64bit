#include <headers/bullet.h>
Bullet::Bullet()
{
    bulletX = 0;
    bulletY = 0;
    bulletW = DEFAULT_BULLET_WIDTH;
    bulletH = DEFAULT_BULLET_HEIGHT;
    bulletVel = DEFAULT_BULLET_VEL;
    bulletType = NONE;
    move = false;

    updateCollisionBox();
}
Bullet::~Bullet()
{
    free();
}
void Bullet::setBulletOffset(const int &x, const int &y)
{
    bulletX = x;
    bulletY = y;
    updateCollisionBox();
}
void Bullet::setBulletSize(const int &width, const int &height)
{
    bulletW = width;
    bulletH = height;
    updateCollisionBox();
}
int Bullet::getBulletWidth()
{
    return bulletW;
}
int Bullet::getBulletHeight()
{
    return bulletH;
}
int Bullet::getX()
{
    return bulletX;
}
int Bullet::getY()
{
    return bulletY;
}
void Bullet::updateCollisionBox()
{
    //
    switch (bulletType)
    {
    case RED_2:
        bulletCollisionBox = {bulletX + 4, bulletY + (RED_2_BULLET_HEIGHT - 32), RED_2_BULLET_WIDTH - 8, 32};
        break;
    case BLUE_3:
        bulletCollisionBox = {bulletX + 4, bulletY + (BLUE_3_BULLET_HEIGHT - 27), BLUE_3_BULLET_WIDTH - 8, 27};
        break;
    case GREEN:
        bulletCollisionBox = {bulletX + 7, bulletY + (GREEN_BULLET_HEIGHT - 30), GREEN_BULLET_WIDTH - 14, 30};
        break;
    case RED:
        bulletCollisionBox = {bulletX + 10, bulletY + 1, RED_BULLET_WIDTH - 20, RED_BULLET_HEIGHT - 10};
        break;
    default:
        bulletCollisionBox = {bulletX, bulletY, bulletW, bulletH};
        break;
        ;
    }
}
SDL_Rect Bullet::getCollisionBox()
{
    return bulletCollisionBox;
}
SDL_Rect *Bullet::p_getCollisionBox()
{
    return &bulletCollisionBox;
}
void Bullet::setType(const int &type)
{
    bulletType = type;
    switch (bulletType)
    {
    case RED:
        setBulletSize(RED_BULLET_WIDTH, RED_BULLET_HEIGHT);
        bulletVel = RED_BULLET_VEL;
        break;
    case RED_2:
        setBulletSize(RED_2_BULLET_WIDTH, RED_2_BULLET_HEIGHT);
        bulletVel = RED_2_BULLET_VEL;
        break;
    case BLUE:
        setBulletSize(BLUE_BULLET_WIDTH, BLUE_BULLET_HEIGHT);
        bulletVel = BLUE_BULLET_VEL;
        break;
    case BLUE_3:
        setBulletSize(BLUE_3_BULLET_WIDTH, BLUE_3_BULLET_HEIGHT);
        bulletVel = BLUE_3_BULLET_VEL;
        break;
    case GREEN:
        setBulletSize(GREEN_BULLET_WIDTH, GREEN_BULLET_HEIGHT);
        bulletVel = GREEN_BULLET_VEL;
        break;
    case PURPLE:
        setBulletSize(PURPLE_BULLET_WIDTH, PURPLE_BULLET_HEIGHT);
        bulletVel = PURPLE_BULLET_VEL;
        break;
    case ORANGE:
        setBulletSize(ORANGE_BULLET_WIDTH, ORANGE_BULLET_HEIGHT);
        bulletVel = ORANGE_BULLET_VEL;
        break;
    case YELLOW:
        setBulletSize(YELLOW_BULLET_WIDTH, YELLOW_BULLET_HEIGHT);
        bulletVel = YELLOW_BULLET_VEL;
        break;
    }
}
int Bullet::getType()
{
    return bulletType;
}
void Bullet::handleEvent(SDL_Event &e)
{
}
void Bullet::renderBullet(const int &type, SDL_Renderer *gRenderer)
{
    render(gRenderer, bulletX, bulletY);
}
void Bullet::bulletMoveUp(const int &y_axis_border)
{
    bulletY -= bulletVel;
    updateCollisionBox();
    if (bulletY + bulletH < y_axis_border)
    {
        move = false;
    }
}
void Bullet::bulletMoveDown(const int &y_axis_border)
{
    bulletY += bulletVel;
    updateCollisionBox();
    if (bulletY > y_axis_border)
    {
        move = false;
    }
}
void Bullet::setBulletMoveStatus(const bool &type)
{
    move = type;
}
bool Bullet::getBulletMoveStatus()
{
    return move;
}