#ifndef HEALTH_H
#define HEALTH_H
#include <headers/texture.h>
#include <vector>
using namespace std;
const int DEFAULT_HEALTH = 5;
const int HEART_DISTANCE = 10;
const int HEALTH_LIMIT = 10;
class Health : public Texture
{
private:
    int healthNum;
    vector<int> posX_list;

public:
    Health();
    ~Health();

    void setNumber(const int &num);
    void addPosX(const int &posX);
    int getHealthNum();

    bool initHealth(SDL_Renderer *gRenderer, const int &default_health);
    void loseHealth();
    void gainHealth();
    void renderHealth(SDL_Renderer *gRenderer, const int &posY);
};

enum healthBar
{
    WIDTH_PER_HEALTH_NUM = 5,
    HEALTH_BAR_LENGTH = 20,
    BOSS_HEALTH = 300,
};
const SDL_Color HEALTH_BAR_COLOR = {117, 0, 0, 255};
class HealthBar : public Texture
{
private:
    int healthNum;
    SDL_Rect healthBar;

public:
    HealthBar();
    ~HealthBar();

    void setNumber(const int &num);
    int getHealthNum();

    void initHealth(const int &default_health, const int &posX, const int &PosY);
    void loseHealth();
    void gainHealth();
    void renderHealth(SDL_Renderer *gRenderer);
};

#endif