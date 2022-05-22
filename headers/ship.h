#ifndef SHIP_H
#define SHIP_H
#include <headers/texture.h>
#include <headers/bullet.h>
#include <headers/music.h>
#include <headers/health.h>
#include <headers/text.h>
#include <headers/explosion.h>
#include <vector>
using namespace std;
enum playerShip
{
    PLAYER_SHIP_WIDTH = 150,
    PLAYER_SHIP_HEIGHT = 86,
    NORMAL_SHIP_VEL = 9,
    BULLET_LEVEL_MAX = 5
};
const int IMMORTAL_TIME = 5 * 1000;
const int SHIELD_TIME = 3 * 1000;
const int SHIELD_CD = 45 * 1000;
class Ship : public Texture
{
private:
    // The X and Y offsets of the ship
    int mPosX, mPosY;

    // The velocity of the ship
    int shipVel;
    int mVelX, mVelY;

    // Size of ships
    int Width;
    int Height;

    //  Bullet type
    int bulletType_current;
    int bulletLevel;

    // Ship buff
    // Check if is immortal
    bool immortal;
    Uint32 dead_time;
    // Handle ship shiled effect
    Texture shield;
    Texture shieldSymbol;
    Text shieldCD;
    int32_t recent_shieldUsed;

    // Collision box of ship
    vector<SDL_Rect> CollisionBox;

    // Bullet
    vector<Bullet *> bulletList;

    // Explosion
    Explosion explosion_main;

public:
    // Player health
    Health health;

    // Initializes the variables
    Ship(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    ~Ship();
    bool loadShipStuff(SDL_Renderer *gRenderer);
    // Accessor
    int getShipX();
    int getShipY();
    int getWidth();
    int getHeight();

    // Takes key presses and adjusts the dot's velocity
    void handleEvent(SDL_Renderer *gRenderer, SDL_Event &e, Music shooting[TOTAL_SHOOT_SOUND], const bool &game_sfx);
    // Moves
    void move(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    // Render on screen
    void renderPlayerShip(SDL_Renderer *gRenderer);
    // Explosion
    void renderMainExplosion(SDL_Renderer *gRenderer);

    // Update collision box
    void updateCollisionBox();
    vector<SDL_Rect> getCollisionBox();

    // Handling bullet
    void renderBulletList(SDL_Renderer *gRenderer);
    void generateBullet(SDL_Renderer *gRenderer);
    void deleteShipBullet(const int &index);
    void setBulletList(vector<Bullet *> bulletList_);
    void setBulletType(const int &bullet_type);
    int getBulletType();
    vector<Bullet *> getBulletList();
    void gainBulletLevel();
    void loseBulletLevel();

    void respawn(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT);
    void reset(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT);
    void clearBulletList();
    void resetBulletLevel();

    // Handle immortal state
    void checkState();
    bool getImmortalState();
    void deleteShieldCD();
};

#endif