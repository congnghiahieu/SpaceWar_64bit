#ifndef HEALTH_H
#define HEALTH_H
#include <texture.h>
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

Health::Health()
{
    healthNum = 0;
}
Health::~Health()
{
}
void Health::setNumber(const int &number)
{
    healthNum = number;
}
void Health::addPosX(const int &posX)
{
    posX_list.push_back(posX);
}
int Health::getHealthNum()
{
    return healthNum;
}
bool Health::initHealth(SDL_Renderer *gRenderer, const int &default_health)
{
    bool success = true;
    if (!this->loadFromFile(gRenderer, "res/heart_2.png"))
    {
        printf("Failed to initialize health!\n");
        success = false;
    }
    if (success)
    {
        healthNum = default_health;
        posX_list.clear();
        for (int order = 0; order < default_health; order++)
        {
            addPosX(order * (this->getWidth() + HEART_DISTANCE));
        }
    }
    return success;
}
void Health::loseHealth()
{
    if (healthNum > 0)
    {
        healthNum--;
    }
    posX_list.pop_back();
}
void Health::gainHealth()
{
    if (healthNum < HEALTH_LIMIT)
    {
        healthNum++;
        int last_pos = posX_list.back();
        addPosX(last_pos + this->getWidth() + HEART_DISTANCE);
    }
}
void Health::renderHealth(SDL_Renderer *gRenderer, const int &posY)
{
    if (healthNum == posX_list.size())
    {
        for (int posX : posX_list)
        {
            render(gRenderer, posX, posY);
        }
    }
}
HealthBar::HealthBar()
{
    healthNum = 0;
    healthBar = {0, 0, 0, 0};
}
HealthBar::~HealthBar()
{
}
void HealthBar::setNumber(const int &num)
{
    healthNum = num;
}
int HealthBar::getHealthNum()
{
    return healthNum;
}
void HealthBar::initHealth(const int &default_health, const int &posX, const int &posY)
{
    healthNum = default_health;
    healthBar = {posX, posY, WIDTH_PER_HEALTH_NUM * healthNum, HEALTH_BAR_LENGTH};
}
void HealthBar::loseHealth()
{
    if (healthNum > 0)
    {
        healthNum--;
        healthBar.w = WIDTH_PER_HEALTH_NUM * healthNum;
    }
}
void HealthBar::gainHealth()
{
    if (healthNum < BOSS_HEALTH)
    {
        healthNum++;
        healthBar.w = WIDTH_PER_HEALTH_NUM * healthNum;
    }
}
void HealthBar::renderHealth(SDL_Renderer *gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer, HEALTH_BAR_COLOR.r, HEALTH_BAR_COLOR.g, HEALTH_BAR_COLOR.b, HEALTH_BAR_COLOR.a);
    SDL_RenderFillRect(gRenderer, &healthBar);
}
#endif