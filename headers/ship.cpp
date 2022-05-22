#include <headers/ship.h>
Ship::Ship(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    // Initilize size of ship
    Width = PLAYER_SHIP_WIDTH;
    Height = PLAYER_SHIP_HEIGHT;

    // Initialize the offsets
    mPosX = (SCREEN_WIDTH - Width) / 2;
    mPosY = (SCREEN_HEIGHT - Height);

    // Initialize the velocity
    shipVel = NORMAL_SHIP_VEL;
    mVelX = 0;
    mVelY = 0;

    // bullet type
    bulletType_current = BLUE;
    bulletLevel = 1;

    immortal = false;
    dead_time = -IMMORTAL_TIME;
    recent_shieldUsed = -SHIELD_CD;
    // Initialize the collision box
    CollisionBox.resize(5);
    updateCollisionBox();
    checkState();
}
Ship::~Ship()
{
    free();
}
bool Ship::loadShipStuff(SDL_Renderer *gRenderer)
{
    bool success = true;
    if (!shieldSymbol.loadFromFile(gRenderer, "res/shield_sym.png"))
    {
        success = false;
    }
    if (!shieldCD.loadFont("res/zag_regular.ttf", 30))
    {
        success = false;
    }
    if (!shield.loadFromFile(gRenderer, "res/shield.png"))
    {
        success = false;
    }
    else
    {
        shield.setBlendMode(SDL_BLENDMODE_BLEND);
        shield.setAlpha(100);
    }
    // Load explosion
    if (!explosion_main.loadFromFile(gRenderer, "res/exp_main.png"))
    {
        printf("Failed to load main ship's explosion effect!\n");
        success = false;
    }
    else
    {
        explosion_main.setClips();
    }

    return success;
}
int Ship::getShipX()
{
    return mPosX;
}
int Ship::getShipY()
{
    return mPosY;
}
int Ship::getWidth()
{
    return Width;
}

int Ship::getHeight()
{
    return Height;
}
void Ship::handleEvent(SDL_Renderer *gRenderer, SDL_Event &e, Music shooting[TOTAL_SHOOT_SOUND], const bool &game_sfx)
{
    // Handle move event
    // If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        // Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
            mVelY -= shipVel;
            break;
        case SDLK_s:
            mVelY += shipVel;
            break;
        case SDLK_a:
            mVelX -= shipVel;
            break;
        case SDLK_d:
            mVelX += shipVel;
            break;
        // Handle ship's shiled
        case SDLK_u:
            if (SDL_GetTicks() - recent_shieldUsed > SHIELD_CD && immortal == false)
            {
                recent_shieldUsed = SDL_GetTicks();
            }
            break;
        case SDLK_j:
            shooting[LEFT_SHOOT].playSound(game_sfx);
            // shooting[RIGHT_SHOOT].playSound();
            generateBullet(gRenderer);
            break;
        }
    }
    // If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        // Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
            mVelY += shipVel;
            break;
        case SDLK_s:
            mVelY -= shipVel;
            break;
        case SDLK_a:
            mVelX += shipVel;
            break;
        case SDLK_d:
            mVelX -= shipVel;
            break;
        }
    }
}
void Ship::move(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    // Move the dot left or right
    mPosX += mVelX;
    updateCollisionBox();
    // If the dot went too far to the left or right
    if ((mPosX < 0) || (mPosX + Width > SCREEN_WIDTH))
    {
        // Move back
        mPosX -= mVelX;
    }

    updateCollisionBox();

    // Move the dot up or down
    mPosY += mVelY;
    updateCollisionBox();
    // If the dot went too far up or down
    if ((mPosY < 0) || (mPosY + Height > SCREEN_HEIGHT))
    {
        // Move back
        mPosY -= mVelY;
    }

    updateCollisionBox();
    checkState();
}
void Ship::renderPlayerShip(SDL_Renderer *gRenderer)
{
    render(gRenderer, mPosX, mPosY);

    // Load ship shiled
    shieldSymbol.render(gRenderer, 150, 895);
    int time = (SHIELD_CD - (int32_t(SDL_GetTicks()) - recent_shieldUsed)) / 1000;
    if (time > 0)
    {
        shieldCD.loadText(gRenderer, to_string(time), WHITE_COLOR);
    }
    else
    {
        shieldCD.loadText(gRenderer, "READY", WHITE_COLOR);
    }
    shieldCD.render(gRenderer, 195, 900);

    if (immortal)
    {
        shield.render(gRenderer, mPosX + (PLAYER_SHIP_WIDTH - shield.getWidth()) / 2, mPosY + (PLAYER_SHIP_HEIGHT - shield.getHeight()) / 2);
    }
}
void Ship::renderMainExplosion(SDL_Renderer *gRenderer)
{
    for (int frame = 0; frame < TOTAL_CLIPS * FRAME_DELAY_MAIN; frame++)
    {
        int explosionX = mPosX + (PLAYER_SHIP_WIDTH - EXPLOSION_WIDTH) / 2;
        int explosionY = mPosY - (EXPLOSION_HEIGHT / 2);
        explosion_main.setFrame(frame, FRAME_DELAY_MAIN);
        explosion_main.renderExplosion(gRenderer, explosionX, explosionY);
        SDL_RenderPresent(gRenderer);
    }
}
void Ship::updateCollisionBox()
{
    CollisionBox[0] = {mPosX + 60, mPosY, 30, 14};
    CollisionBox[1] = {mPosX + 45, mPosY + 15, 60, 16};
    CollisionBox[2] = {mPosX + 20, mPosY + 14 + 16, 110, 24};
    CollisionBox[3] = {mPosX + 5, mPosY + 14 + 16 + 24, 26, 20};
    CollisionBox[4] = {mPosX + PLAYER_SHIP_WIDTH - (5 + 26), mPosY + 14 + 16 + 24, 26, 20};
}
vector<SDL_Rect> Ship::getCollisionBox()
{
    return CollisionBox;
}
void Ship::renderBulletList(SDL_Renderer *gRenderer)
{
    // Render bullet
    vector<Bullet *> bulletList = this->getBulletList();
    for (int i = 0; i < this->getBulletList().size(); i++)
    {
        Bullet *p_bullet = bulletList.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->getBulletMoveStatus())
            {
                p_bullet->bulletMoveUp(-10);
                p_bullet->renderBullet(p_bullet->getType(), gRenderer);
            }
            else
            {
                // If the bullet cross the border
                if (p_bullet != NULL)
                {
                    bulletList.erase(bulletList.begin() + i);
                    this->setBulletList(bulletList);

                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}
void Ship::generateBullet(SDL_Renderer *gRenderer)
{

    Bullet *p_bullet[bulletLevel];
    for (int num = 0; num < bulletLevel; num++)
    {
        p_bullet[num] = new Bullet;
        p_bullet[num]->loadFromFile(gRenderer, "res/blue_bullet.png");
        p_bullet[num]->setType(BLUE);
        p_bullet[num]->setBulletMoveStatus(true);
    }
    switch (bulletLevel)
    {
    case 1:
        p_bullet[0]->setBulletOffset(this->mPosX + ((this->getWidth() - p_bullet[0]->getBulletWidth()) / 2), this->mPosY - p_bullet[0]->getBulletHeight());
        break;
    case 2:
        p_bullet[0]->setBulletOffset(CollisionBox[1].x - p_bullet[0]->getWidth() / 2, CollisionBox[1].y - 50);
        p_bullet[1]->setBulletOffset(CollisionBox[1].x + CollisionBox[1].w - p_bullet[0]->getWidth() / 2, CollisionBox[1].y - 50);
        break;
    case 3:
        p_bullet[0]->setBulletOffset(this->mPosX + ((this->getWidth() - p_bullet[0]->getBulletWidth()) / 2), this->mPosY - p_bullet[0]->getBulletHeight());

        p_bullet[1]->setBulletOffset(CollisionBox[3].x + (CollisionBox[3].w - p_bullet[1]->getWidth()) / 2, CollisionBox[3].y - 55);
        p_bullet[2]->setBulletOffset(CollisionBox[4].x + (CollisionBox[4].w - p_bullet[2]->getWidth()) / 2, CollisionBox[4].y - 55);

        break;
    case 4:
        p_bullet[0]->setBulletOffset(CollisionBox[1].x - p_bullet[0]->getWidth() / 2, CollisionBox[1].y - 50);
        p_bullet[1]->setBulletOffset(CollisionBox[1].x + CollisionBox[1].w - p_bullet[1]->getWidth() / 2, CollisionBox[1].y - 50);

        p_bullet[2]->setBulletOffset(CollisionBox[3].x + (CollisionBox[3].w - p_bullet[2]->getWidth()) / 2, CollisionBox[3].y - 55);
        p_bullet[3]->setBulletOffset(CollisionBox[4].x + (CollisionBox[4].w - p_bullet[3]->getWidth()) / 2, CollisionBox[4].y - 55);

        break;
    case BULLET_LEVEL_MAX:
        p_bullet[0]->setBulletOffset(this->mPosX + ((this->getWidth() - p_bullet[0]->getBulletWidth()) / 2), this->mPosY - p_bullet[0]->getBulletHeight());
        p_bullet[1]->setBulletOffset(CollisionBox[1].x - p_bullet[1]->getWidth() / 2, CollisionBox[1].y - 50);
        p_bullet[2]->setBulletOffset(CollisionBox[1].x + CollisionBox[1].w - p_bullet[2]->getWidth() / 2, CollisionBox[1].y - 50);

        p_bullet[3]->setBulletOffset(CollisionBox[3].x + (CollisionBox[3].w - p_bullet[3]->getWidth()) / 2, CollisionBox[3].y - 55);
        p_bullet[4]->setBulletOffset(CollisionBox[4].x + (CollisionBox[4].w - p_bullet[4]->getWidth()) / 2, CollisionBox[4].y - 55);

        break;
    }
    for (int num = 0; num < bulletLevel; num++)
    {
        bulletList.push_back(p_bullet[num]);
    }
}
void Ship::deleteShipBullet(const int &index)
{
    int size = bulletList.size();
    if (size > 0 && index < size)
    {
        Bullet *p_bullet = bulletList.at(index);
        bulletList.erase(bulletList.begin() + index);
        if (p_bullet != NULL)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
void Ship::setBulletList(vector<Bullet *> bulletList_)
{
    bulletList = bulletList_;
}
vector<Bullet *> Ship::getBulletList()
{
    return bulletList;
}
void Ship::setBulletType(const int &bullet_type)
{
    bulletType_current = bullet_type;
}
int Ship::getBulletType()
{
    return bulletType_current;
}
void Ship::gainBulletLevel()
{
    if (bulletLevel < BULLET_LEVEL_MAX)
    {
        bulletLevel++;
    }
}
void Ship::loseBulletLevel()
{
    if (bulletLevel > 1)
    {
        bulletLevel--;
    }
}
void Ship::respawn(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT)
{
    dead_time = SDL_GetTicks();
    mPosX = (SCREEN_WIDTH - Width) / 2;
    mPosY = (SCREEN_HEIGHT - Height);
    shipVel = NORMAL_SHIP_VEL;
    loseBulletLevel();
    checkState();
    updateCollisionBox();
}
void Ship::reset(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT)
{
    // Initialize the offsets
    mPosX = (SCREEN_WIDTH - Width) / 2;
    mPosY = (SCREEN_HEIGHT - Height);

    // Initialize the velocity
    shipVel = NORMAL_SHIP_VEL;
    mVelX = 0;
    mVelY = 0;

    immortal = false;
    dead_time = -IMMORTAL_TIME;
    recent_shieldUsed = -SHIELD_CD;
    // Initialize the collision box
    CollisionBox.resize(5);
    updateCollisionBox();
    checkState();
    clearBulletList();
}
void Ship::clearBulletList()
{
    for (int bullet_num = 0; bullet_num < bulletList.size(); bullet_num++)
    {
        this->deleteShipBullet(bullet_num);
    }
    bulletList.clear();
}
void Ship::resetBulletLevel()
{
    bulletLevel = 1;
    bulletType_current = BLUE;
}
// Handle immortal state
void Ship::checkState()
{
    if ((SDL_GetTicks() - dead_time <= IMMORTAL_TIME) || (SDL_GetTicks() - recent_shieldUsed <= SHIELD_TIME))
    {
        immortal = true;
    }
    else
    {
        immortal = false;
    }
}
bool Ship::getImmortalState()
{
    return immortal;
}
void Ship::deleteShieldCD()
{
    recent_shieldUsed = -SHIELD_CD;
}