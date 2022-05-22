#ifndef BULLET_H
#define BULLET_H
#include <headers/texture.h>
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

#endif