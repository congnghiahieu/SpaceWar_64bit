#ifndef BOSS_H
#define BOSS_H
#include <texture.h>
#include <bossBullet.h>
#include <health.h>
#include <explosion.h>
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

Boss::Boss()
{
    bossX = 0;
    bossY = 0;
    bossW = BOSS_WIDTH;
    bossH = BOSS_HEIGHT;

    is_ready = false;
    is_dead = false;
    deadTime = 0;

    bossSideShootTime = 3 * 1000,
    bossMidShootTime = 4 * 1000,
    recent_bossSideShoot = 100 * 1000;
    recent_bossMidShoot = 100 * 1000;

    recent_shieldUsed = -BOSS_SHIELD_TIME;
    isShieldReady_75 = true;
    isShieldReady_50 = true;
    isShieldReady_25 = true;
    isInShield = false;

    bossCollisionbox.resize(9);
    updateCollisionBox();
}
Boss::~Boss()
{
    for (int num = 0; num > bossBulletList.size(); num++)
    {
        BossBullet *p_bullet = bossBulletList.at(num);
        if (p_bullet != NULL)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
    bossBulletList.clear();
    free();
}

bool Boss::loadBossStuff(SDL_Renderer *gRenderer)
{
    bool success = true;
    if (!bossShiled.loadFromFile(gRenderer, "res/boss_shield.png"))
    {
        printf("Failed to load boss stuff!\n");
        success = false;
    }
    else
    {
        bossShiled.setBlendMode(SDL_BLENDMODE_BLEND);
    }
    if (!explosion_boss.loadFromFile(gRenderer, "res/exp_boss.png"))
    {
        printf("Failed to load boss's explosion effect!\n");
        success = false;
    }
    else
    {
        explosion_boss.setClips();
    }
    return success;
}

bool Boss::initBoss(SDL_Renderer *gRenderer, const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT)
{
    bool success = true;
    if (!loadFromFile(gRenderer, "res/boss.png"))
    {
        printf("Failed to load boss image!\n");
        success = false;
    }
    if (success)
    {
        setBossOffset((SCREEN_WIDTH - BOSS_WIDTH) / 2, -1000);
        bossHealth.initHealth(BOSS_HEALTH, (SCREEN_WIDTH - BOSS_HEALTH * WIDTH_PER_HEALTH_NUM) / 2, 5);
        if (!this->loadBossStuff(gRenderer))
        {
            success = false;
        }
    }
    return success;
}
void Boss::initBossBullet(SDL_Renderer *gRenderer, BossBullet *p_bullet)
{
}

void Boss::setBossOffset(const int &x, const int &y)
{
    bossX = x;
    bossY = y;
    updateCollisionBox();
}
void Boss::move()
{
    if (bossY < 25)
    {
        bossY += BOSS_VEL;
        updateCollisionBox();
    }
    else
    {
        is_ready = true;
    }
    checkState();
}
void Boss::checkState()
{
    // boss shoot time
    if (bossHealth.getHealthNum() > BOSS_HEALTH * 75 / 100)
    {
        bossSideShootTime = 3500;
        bossMidShootTime = 4000;
    }
    else if (bossHealth.getHealthNum() > BOSS_HEALTH * 50 / 100 && bossHealth.getHealthNum() <= BOSS_HEALTH * 75 / 100)
    {
        bossSideShootTime = 3000;
        bossMidShootTime = 3500;
    }
    else if (bossHealth.getHealthNum() > BOSS_HEALTH * 25 / 100 && bossHealth.getHealthNum() <= BOSS_HEALTH * 50 / 100)
    {
        bossSideShootTime = 2500;
        bossMidShootTime = 3000;
    }
    else if (bossHealth.getHealthNum() >= BOSS_HEALTH * 0 / 100 && bossHealth.getHealthNum() <= BOSS_HEALTH * 25 / 100)
    {
        bossSideShootTime = 2000;
        bossMidShootTime = 2500;
    }

    // boss shield
    if (bossHealth.getHealthNum() >= BOSS_HEALTH * 74 / 100 && bossHealth.getHealthNum() <= BOSS_HEALTH * 75 / 100 && isShieldReady_75 == true)
    {
        isShieldReady_75 = false;
        recent_shieldUsed = SDL_GetTicks();
    }
    if (bossHealth.getHealthNum() >= BOSS_HEALTH * 49 / 100 && bossHealth.getHealthNum() <= BOSS_HEALTH * 50 / 100 && isShieldReady_50 == true)
    {
        isShieldReady_50 = false;
        recent_shieldUsed = SDL_GetTicks();
    }
    if (bossHealth.getHealthNum() >= BOSS_HEALTH * 24 / 100 && bossHealth.getHealthNum() <= BOSS_HEALTH * 25 / 100 && isShieldReady_25 == true)
    {
        isShieldReady_25 = false;
        recent_shieldUsed = SDL_GetTicks();
    }
    if (SDL_GetTicks() - recent_shieldUsed <= BOSS_SHIELD_TIME)
    {
        isInShield = true;
    }
    else
    {
        isInShield = false;
    }
}
bool Boss::getShieldState()
{
    return isInShield;
}
bool Boss::getReadyState()
{
    return is_ready;
}
void Boss::setDeadState(const bool &type)
{
    is_dead = type;
}
bool Boss::getDeadState()
{
    return is_dead;
}
void Boss::updateCollisionBox()
{
    // Mid collision
    bossCollisionbox[0] = {bossX + (BOSS_WIDTH - 580) / 2, bossY + 220, 580, 180};
    // RIGHT HAND 1
    bossCollisionbox[1] = {bossX + 980, bossY + 500, 200, 60};
    // RGIHT HAND 2
    bossCollisionbox[2] = {bossX + 1340, bossY + 350, 90, 50};
    bossCollisionbox[3] = {bossX + 1450, bossY + 400, 90, 40};
    // RIGHT HAND 3
    bossCollisionbox[4] = {bossX + 1655, bossY + 255, 120, 65};
    // LEFT HAND 1
    bossCollisionbox[5] = {bossX + 390, bossY + 500, 80, 45};
    bossCollisionbox[6] = {bossX + 310, bossY + 480, 80, 40};
    // LEFT HAND 2
    bossCollisionbox[7] = {bossX + 250, bossY + 405, 80, 40};
    // LEFT HAND 3
    bossCollisionbox[8] = {bossX + 20, bossY + 370, 160, 20};
}
vector<SDL_Rect> Boss::getCollisionBox()
{
    return bossCollisionbox;
}

void Boss::renderBoss(SDL_Renderer *gRenderer)
{
    render(gRenderer, bossX, bossY);
    if (bossY >= 25)
    {
        bossHealth.renderHealth(gRenderer);
    }
    if (isInShield == true)
    {
        bossShiled.render(gRenderer, bossCollisionbox[0].x + (bossCollisionbox[0].w - bossShiled.getWidth()) / 2, bossCollisionbox[0].y - (bossShiled.getHeight() - bossCollisionbox[0].h) / 2);
    }
}
void Boss::renderBossBullet(SDL_Renderer *gRenderer)
{
    // Render bullet
    if (bossBulletList.size() > 0)
    {
        vector<BossBullet *> p_bossBulletList = this->getBulletList();
        for (int i = 0; i < this->getBulletList().size(); i++)
        {
            BossBullet *p_bullet = p_bossBulletList.at(i);
            if (p_bullet != NULL)
            {
                if (p_bullet->getBulletMoveStatus())
                {
                    p_bullet->move(1000);
                    p_bullet->renderBullet(gRenderer);
                }
                else
                {
                    // If the bullet cross the border
                    if (p_bullet != NULL)
                    {
                        p_bossBulletList.erase(p_bossBulletList.begin() + i);
                        this->setBulletList(p_bossBulletList);

                        delete p_bullet;
                        p_bullet = NULL;
                    }
                }
            }
        }
    }
}
void Boss::renderBossExplosion(SDL_Renderer *gRenderer)
{
    for (int frame = 0; frame < TOTAL_CLIPS * FRAME_DELAY_BOSS; frame++)
    {
        explosion_boss.setFrame(frame, FRAME_DELAY_BOSS);
        explosion_boss.renderExplosion(gRenderer, bossCollisionbox[0].x, bossCollisionbox[0].y);
        explosion_boss.renderExplosion(gRenderer, bossCollisionbox[1].x, bossCollisionbox[1].y);
        explosion_boss.renderExplosion(gRenderer, bossCollisionbox[2].x, bossCollisionbox[2].y);
        explosion_boss.renderExplosion(gRenderer, bossCollisionbox[4].x, bossCollisionbox[4].y);
        explosion_boss.renderExplosion(gRenderer, bossCollisionbox[5].x, bossCollisionbox[5].y);
        explosion_boss.renderExplosion(gRenderer, bossCollisionbox[7].x, bossCollisionbox[7].y);
        explosion_boss.renderExplosion(gRenderer, bossCollisionbox[8].x, bossCollisionbox[8].y);
        SDL_RenderPresent(gRenderer);
    }
}
// Bullet
void Boss::setBulletList(vector<BossBullet *> p_bulletList)
{
    bossBulletList = p_bulletList;
}
vector<BossBullet *> Boss::getBulletList()
{
    return bossBulletList;
}
void Boss::generateRedBullet(SDL_Renderer *gRenderer)
{
    BossBullet *p_red_bullet[TOTAL_RED_BULLET];
    for (int num = 0; num < TOTAL_RED_BULLET; num++)
    {
        p_red_bullet[num] = new BossBullet;
    }
    for (int num = 0; num < TOTAL_RED_BULLET; num++)
    {
        p_red_bullet[num]->setType(BOSS_BULLET_RED, gRenderer);
        p_red_bullet[num]->setBulletMoveStatus(true);
    }
    // Set offset for each bullet
    p_red_bullet[0]->setBulletOffset(rand() % (bossCollisionbox[1].w * 1 / 4) + bossCollisionbox[1].x, bossCollisionbox[1].y + bossCollisionbox[1].h);
    p_red_bullet[1]->setBulletOffset(rand() % (bossCollisionbox[1].w * 1 / 4) + (bossCollisionbox[1].x + bossCollisionbox[1].w * 3 / 4), bossCollisionbox[1].y + bossCollisionbox[1].h);
    p_red_bullet[2]->setBulletOffset(rand() % (bossCollisionbox[2].w) + bossCollisionbox[2].x, bossCollisionbox[2].y + bossCollisionbox[2].h);
    p_red_bullet[3]->setBulletOffset(rand() % (bossCollisionbox[4].w) + bossCollisionbox[4].x, bossCollisionbox[4].y + bossCollisionbox[4].h);
    p_red_bullet[4]->setBulletOffset(rand() % (bossCollisionbox[5].w) + bossCollisionbox[5].x, bossCollisionbox[5].y + bossCollisionbox[5].h);
    p_red_bullet[5]->setBulletOffset(rand() % (bossCollisionbox[8].w) + bossCollisionbox[8].x, bossCollisionbox[8].y + bossCollisionbox[8].h);
    for (int num = 0; num < TOTAL_RED_BULLET; num++)
    {
        bossBulletList.push_back(p_red_bullet[num]);
    }
}
void Boss::generateGreenBullet(SDL_Renderer *gRenderer)
{
    BossBullet *p_green_bullet[TOTAL_GREEN_BULLET];
    for (int num = 0; num < TOTAL_GREEN_BULLET; num++)
    {
        p_green_bullet[num] = new BossBullet;
    }
    for (int num = 0; num < TOTAL_GREEN_BULLET; num++)
    {
        p_green_bullet[num]->setType(BOSS_BULLET_GREEN, gRenderer);
        p_green_bullet[num]->setBulletMoveStatus(true);
    }
    // Set offset for each bullet
    p_green_bullet[0]->setBulletOffset(rand() % (bossCollisionbox[1].w * 1 / 3) + bossCollisionbox[1].x, bossCollisionbox[1].y + bossCollisionbox[1].h);
    p_green_bullet[1]->setBulletOffset(rand() % (bossCollisionbox[1].w * 1 / 3) + (bossCollisionbox[1].x + bossCollisionbox[1].w * 1 / 3), bossCollisionbox[1].y + bossCollisionbox[1].h);
    p_green_bullet[2]->setBulletOffset(rand() % (bossCollisionbox[1].w * 1 / 3) + (bossCollisionbox[1].x + bossCollisionbox[1].w * 2 / 3), bossCollisionbox[1].y + bossCollisionbox[1].h);
    p_green_bullet[3]->setBulletOffset(rand() % (bossCollisionbox[2].w) + bossCollisionbox[2].x, bossCollisionbox[2].y + bossCollisionbox[2].h);
    p_green_bullet[4]->setBulletOffset(rand() % (bossCollisionbox[3].w) + bossCollisionbox[3].x, bossCollisionbox[3].y + bossCollisionbox[3].h);
    p_green_bullet[5]->setBulletOffset(rand() % (bossCollisionbox[4].w) + bossCollisionbox[4].x, bossCollisionbox[4].y + bossCollisionbox[4].h);
    p_green_bullet[6]->setBulletOffset(rand() % (bossCollisionbox[5].w) + bossCollisionbox[5].x, bossCollisionbox[5].y + bossCollisionbox[5].h);
    p_green_bullet[7]->setBulletOffset(rand() % (bossCollisionbox[6].w) + bossCollisionbox[6].x, bossCollisionbox[6].y + bossCollisionbox[6].h);
    p_green_bullet[8]->setBulletOffset(rand() % (bossCollisionbox[7].w) + bossCollisionbox[7].x, bossCollisionbox[7].y + bossCollisionbox[7].h);
    p_green_bullet[9]->setBulletOffset(rand() % (bossCollisionbox[8].w * 1 / 2) + bossCollisionbox[8].x, bossCollisionbox[8].y + bossCollisionbox[8].h);
    p_green_bullet[10]->setBulletOffset(rand() % (bossCollisionbox[8].w * 1 / 2) + (bossCollisionbox[8].x + bossCollisionbox[8].w * 1 / 2), bossCollisionbox[8].y + bossCollisionbox[8].h);

    for (int num = 0; num < TOTAL_GREEN_BULLET; num++)
    {
        bossBulletList.push_back(p_green_bullet[num]);
    }
}
void Boss::generateGasBullet(SDL_Renderer *gRenderer)
{
    BossBullet *p_gas_bullet[TOTAL_GAS_BULLET];
    for (int num = 0; num < TOTAL_GAS_BULLET; num++)
    {
        p_gas_bullet[num] = new BossBullet;
    }
    for (int num = 0; num < TOTAL_GAS_BULLET; num++)
    {
        p_gas_bullet[num]->setType(BOSS_BULLET_GAS, gRenderer);
        p_gas_bullet[num]->setBulletMoveStatus(true);
    }
    // Set offset for each bullet
    p_gas_bullet[0]->setBulletOffset(rand() % (1) + bossCollisionbox[0].x, bossCollisionbox[0].y + bossCollisionbox[0].h * 3 / 4);
    p_gas_bullet[1]->setBulletOffset(rand() % (bossCollisionbox[0].w * 1 / 4) + (bossCollisionbox[0].x + bossCollisionbox[0].w * 1 / 4), bossCollisionbox[0].y + bossCollisionbox[0].h * 3 / 4);
    p_gas_bullet[2]->setBulletOffset(rand() % (bossCollisionbox[0].w * 1 / 4) + (bossCollisionbox[0].x + bossCollisionbox[0].w * 2 / 4), bossCollisionbox[0].y + bossCollisionbox[0].h * 3 / 4);
    p_gas_bullet[3]->setBulletOffset(rand() % (bossCollisionbox[0].w * 1 / 4) + (bossCollisionbox[0].x + bossCollisionbox[0].w * 3 / 4), bossCollisionbox[0].y + bossCollisionbox[0].h * 3 / 4);

    for (int num = 0; num < TOTAL_GAS_BULLET; num++)
    {
        bossBulletList.push_back(p_gas_bullet[num]);
    }
}
/*
void Boss::generateFireBullet(SDL_Renderer *gRenderer)
{
    BossBullet *p_fire_bullet[TOTAL_FIRE_BULLET];
    for (int num = 0; num < TOTAL_FIRE_BULLET; num++)
    {
        p_fire_bullet[num] = new BossBullet;
    }
    for (int num = 0; num < TOTAL_FIRE_BULLET; num++)
    {
        p_fire_bullet[num]->setType(BOSS_BULLET_FIRE, gRenderer);
        p_fire_bullet[num]->setBulletMoveStatus(true);
    }
    // Set offset for each bullet
    p_fire_bullet[0]->setBulletOffset(rand() % (bossCollisionbox[0].w * 1 / 3) + bossCollisionbox[0].x, bossCollisionbox[0].y + bossCollisionbox[0].h * 1 / 2);
    p_fire_bullet[1]->setBulletOffset(rand() % (bossCollisionbox[0].w * 1 / 3) + (bossCollisionbox[0].x + bossCollisionbox[0].w * 1 / 2), bossCollisionbox[0].y + bossCollisionbox[0].h * 1 / 2);
    for (int num = 0; num < TOTAL_FIRE_BULLET; num++)
    {
        bossBulletList.push_back(p_fire_bullet[num]);
    }
}
*/
void Boss::generateSideBullet(SDL_Renderer *gRenderer)
{
    if (this->getReadyState() == true && (SDL_GetTicks() - recent_bossSideShoot >= bossSideShootTime))
    {
        recent_bossSideShoot = SDL_GetTicks();
        switch (rand() % 2)
        {
        case 0:
            generateRedBullet(gRenderer);
            break;
        case 1:
            generateGreenBullet(gRenderer);
            break;
        }
    }
}
void Boss::generateMidBullet(SDL_Renderer *gRenderer)
{
    if (this->getReadyState() == true && (SDL_GetTicks() - recent_bossMidShoot >= bossMidShootTime))
    {
        recent_bossMidShoot = SDL_GetTicks();
        generateGasBullet(gRenderer);
    }
}
void Boss::generateBullet(SDL_Renderer *gRenderer)
{
    generateSideBullet(gRenderer);
    generateMidBullet(gRenderer);
}
void Boss::deleteBossBullet(const int &index)
{
    int size = bossBulletList.size();
    if (size > 0 && index < size)
    {
        BossBullet *p_bullet = bossBulletList.at(index);
        bossBulletList.erase(bossBulletList.begin() + index);
        if (p_bullet != NULL)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
void Boss::clearBossBulletList()
{
    if (bossBulletList.size() > 0)
    {
        for (int bullet_num = 0; bullet_num < bossBulletList.size(); bullet_num++)
        {
            this->deleteBossBullet(bullet_num);
        }
        bossBulletList.clear();
    }
}
#endif