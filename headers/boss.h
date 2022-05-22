#ifndef BOSS_H
#define BOSS_H
#include <headers/texture.h>
#include <headers/bossBullet.h>
#include <headers/health.h>
#include <headers/explosion.h>
#include <vector>
#include <cstdlib>

enum boss
{
    BOSS_WIDTH = 1800,
    BOSS_HEIGHT = 600,
    BOSS_VEL = 1,
    TOTAL_RED_BULLET = 6,
    TOTAL_GREEN_BULLET = 11,
    TOTAL_GAS_BULLET = 4,
    TOTAL_FIRE_BULLET = 2
};
const int BOSS_SHIELD_TIME = 10 * 1000;
class Boss : public Texture
{
private:
    int bossX;
    int bossY;
    int bossW;
    int bossH;

    bool is_ready;
    bool is_dead;

    Uint32 bossSideShootTime;
    Uint32 bossMidShootTime;
    Uint32 recent_bossSideShoot;
    Uint32 recent_bossMidShoot;

    // Boss shield
    Texture bossShiled;
    int32_t recent_shieldUsed;
    bool isShieldReady_75;
    bool isShieldReady_50;
    bool isShieldReady_25;
    bool isInShield;

    vector<SDL_Rect> bossCollisionbox;
    vector<BossBullet *> bossBulletList;

    // boss explosion
    Explosion explosion_boss;

public:
    HealthBar bossHealth;
    Uint32 deadTime;

    Boss();
    ~Boss();
    bool loadBossStuff(SDL_Renderer *gRenderer);
    bool initBoss(SDL_Renderer *gRenderer, const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT);
    void initBossBullet(SDL_Renderer *gRenderer, BossBullet *p_bullet);

    void setBossOffset(const int &x, const int &y);
    void move();
    void checkState();
    bool getShieldState();
    bool getReadyState();
    void setDeadState(const bool &type);
    bool getDeadState();

    void updateCollisionBox();
    vector<SDL_Rect> getCollisionBox();

    void renderBoss(SDL_Renderer *gRenderer);
    void renderBossBullet(SDL_Renderer *gRenderer);
    void renderBossExplosion(SDL_Renderer *gRenderer);

    // Bullet
    void setBulletList(vector<BossBullet *> p_bulletList);
    vector<BossBullet *> getBulletList();
    void generateRedBullet(SDL_Renderer *gRenderer);
    void generateGreenBullet(SDL_Renderer *gRenderer);
    void generateGasBullet(SDL_Renderer *gRenderer);
    // void generateFireBullet(SDL_Renderer *gRenderer);
    void generateSideBullet(SDL_Renderer *gRenderer);
    void generateMidBullet(SDL_Renderer *gRenderer);
    void generateBullet(SDL_Renderer *gRenderer);
    void deleteBossBullet(const int &index);
    void clearBossBulletList();
};
#endif