#ifndef THREAT_H
#define THREAT_H
#include <headers/texture.h>
#include <headers/bullet.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
enum ThreatType
{
    RED_SHIP,
    BLUE_SHIP,
    WHITE_SHIP,
    RED_SHIP_WIDTH = 90,
    RED_SHIP_HEIGHT = 84,
    RED_SHIP_VEL = 7,
    RED_SHIP_HEALTH = 3,
    BLUE_SHIP_WIDTH = 80,
    BLUE_SHIP_HEIGHT = 100,
    BLUE_SHIP_VEL = 6,
    BLUE_SHIP_HEALTH = 4,
    WHITE_SHIP_WIDTH = 120,
    WHITE_SHIP_HEIGHT = 116,
    WHITE_SHIP_VEL = 5,
    WHITE_SHIP_HEALTH = 6
};
enum ThreatMoveType
{
    FROM_LEFT,
    FROM_RIGHT,
    UP_TO_DOWN,
};
class Threat : public Texture
{
private:
    int threatX;
    int threatY;
    int threatW;
    int threatH;

    int threatType;
    int threatMoveType;
    int threatVel;
    vector<SDL_Rect> threatCollisionBox;

    vector<Bullet *> threatBulletList;

    int threatHealth;

public:
    Threat();
    ~Threat();

    // Set and get Threat index
    void setThreatOffset(const int &x, const int &y);
    void setThreatSize(const int &width, const int &height);
    int getThreatX();
    int getThreatY();

    // Collision box
    void updateThreatCollisionBox();
    vector<SDL_Rect> getThreatCollisionBox();

    // set type and get type
    void setThreatType(const int &type);
    void setThreatMoveType(const int &type, const int &order, const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT);
    int getThreatType();
    int getThreatMoveType();

    // Move, event, render
    void threatMove(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT);
    void renderThreat(SDL_Renderer *gRenderer);
    void handleInputEvent(SDL_Event &e);

    // Create threats
    bool initThreat(SDL_Renderer *gRenderer, const int &order, const int &numOfThreatMoveType, const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT);
    // Handle threat bullet
    void initBullet(SDL_Renderer *gRenderer, Bullet *p_bullet, const int &type);

    // Handle threat's health
    void setHealth(const int &type);
    void loseHealth();
    int getHealth();

    // Handle bullet
    void renderBullet(SDL_Renderer *gRenderer, const int &y_axis_border);
    void setThreatBulletList(vector<Bullet *> bulletlist);
    vector<Bullet *> getThreatBulletList();

    // Reset threats when destroyed
    void resetThreat(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT);
    void resetThreatBullet();
    void returnThreatBullet();
};

#endif