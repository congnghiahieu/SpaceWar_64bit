#ifndef BULLET_H
#define BULLET_H
#include <texture.h>
enum shipSize
{
    SHIP_WIDTH = 150,
    SHIP_HEIGHT = 86
};
enum bulletType
{
    NONE,
    RED,    // Used for player's ship
    RED_2,  // Used for red ship
    BLUE,   // Used for player's ship
    BLUE_3, // Used for blue ship
    PURPLE,
    GREEN,  // Used for white ship
    ORANGE, // Used for boss
    YELLOW
};
enum bulletSize
{
    DEFAULT_BULLET_WIDTH = 30,
    DEFAULT_BULLET_HEIGHT = 30,
    DEFAULT_BULLET_VEL = 10,

    RED_BULLET_WIDTH = 40,
    RED_BULLET_HEIGHT = 70,
    RED_BULLET_VEL = 8, // player

    RED_2_BULLET_WIDTH = 28,
    RED_2_BULLET_HEIGHT = 65,
    RED_2_BULLET_VEL = 8, // threat

    BLUE_BULLET_WIDTH = 20,
    BLUE_BULLET_HEIGHT = 50,
    BLUE_BULLET_VEL = 18, // player

    BLUE_3_BULLET_WIDTH = 30,
    BLUE_3_BULLET_HEIGHT = 53,
    BLUE_3_BULLET_VEL = 7, // threat

    GREEN_BULLET_WIDTH = 50,
    GREEN_BULLET_HEIGHT = 70,
    GREEN_BULLET_VEL = 6, // threat

    PURPLE_BULLET_WIDTH = 40,
    PURPLE_BULLET_HEIGHT = 30,
    PURPLE_BULLET_VEL = 28,

    ORANGE_BULLET_WIDTH = 40,
    ORANGE_BULLET_HEIGHT = 65,
    ORANGE_BULLET_VEL = 5,

    YELLOW_BULLET_WIDTH = 70,
    YELLOW_BULLET_HEIGHT = 70,
    YELLOW_BULLET_VEL = 8
};
class Bullet : public Texture
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
    bool move;

    // Collision box of bullet
    SDL_Rect bulletCollisionBox;

public:
    // Initialize bullet
    Bullet();
    // Deallocate bullet
    ~Bullet();

    // Modified bullets
    void setBulletOffset(const int &x, const int &y);
    void setBulletSize(const int &width, const int &height);
    int getBulletWidth();
    int getBulletHeight();
    int getX();
    int getY();

    // Collision
    void updateCollisionBox();
    SDL_Rect getCollisionBox();
    SDL_Rect *p_getCollisionBox();

    // Handling type of bullet
    void setType(const int &type);
    int getType();

    // Handle Event
    void handleEvent(SDL_Event &e);
    void renderBullet(const int &type, SDL_Renderer *gRenderer);

    // Moving handling
    void bulletMoveUp(const int &y_axis_border);
    void bulletMoveDown(const int &y_axis_border);
    void setBulletMoveStatus(const bool &type);
    bool getBulletMoveStatus();
};
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
#endif