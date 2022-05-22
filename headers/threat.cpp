#include <headers/threat.h>
Threat::Threat()
{
    threatX = 0;
    threatY = 0;
    threatW = 0;
    threatH = 0;
    threatVel = 0;
    threatHealth = 0;
    threatCollisionBox.resize(3);
    updateThreatCollisionBox();
}
Threat::~Threat()
{
    if (threatBulletList.size() > 0)
    {
        for (int i = 0; i < threatBulletList.size(); i++)
        {
            Bullet *p_bullet = threatBulletList.at(i);
            if (p_bullet != NULL)
            {
                delete threatBulletList.at(i);
                p_bullet = NULL;
            }
        }
        threatBulletList.clear();
        threatBulletList.resize(0);
    }
    free();
}
void Threat::setThreatOffset(const int &x, const int &y)
{
    threatX = x;
    threatY = y;
    updateThreatCollisionBox();
}
void Threat::setThreatSize(const int &width, const int &height)
{
    threatW = width;
    threatH = height;
    updateThreatCollisionBox();
}
int Threat::getThreatX()
{
    return threatX;
}
int Threat::getThreatY()
{
    return threatY;
}
void Threat::updateThreatCollisionBox()
{
    switch (threatType)
    {
    case RED_SHIP:
        threatCollisionBox[0] = {threatX + 5, threatY + 4, 80, 32};
        threatCollisionBox[1] = {threatX + (RED_SHIP_WIDTH - 20) / 2, threatY + 36, 20, 46};
        break;
    case BLUE_SHIP:
        threatCollisionBox[0] = {threatX + 5, threatY + 24, 70, 18};
        threatCollisionBox[1] = {threatX + (BLUE_SHIP_WIDTH - 20) / 2, threatY + 24 + 18, 20, 50};
        break;
    case WHITE_SHIP:
        threatCollisionBox[0] = {threatX + 7, threatY, 106, 26};
        threatCollisionBox[1] = {threatX + (WHITE_SHIP_WIDTH - 56) / 2, threatY + 26, 56, 40};
        threatCollisionBox[2] = {threatX + (WHITE_SHIP_WIDTH - 48) / 2, threatY + 26 + 40, 48, 40};
        break;
    }
}
vector<SDL_Rect> Threat::getThreatCollisionBox()
{
    return threatCollisionBox;
}
void Threat::setThreatType(const int &type)
{
    threatType = type;
    switch (threatType)
    {
    case RED_SHIP:
        setThreatSize(RED_SHIP_WIDTH, RED_SHIP_HEIGHT);
        threatVel = RED_SHIP_VEL;
        threatCollisionBox.resize(2);
        updateThreatCollisionBox();
        setHealth(RED_SHIP);
        break;
    case BLUE_SHIP:
        setThreatSize(BLUE_SHIP_WIDTH, BLUE_SHIP_HEIGHT);
        threatVel = BLUE_SHIP_VEL;
        threatCollisionBox.resize(2);
        updateThreatCollisionBox();
        setHealth(BLUE_SHIP);
        break;
    case WHITE_SHIP:
        setThreatSize(WHITE_SHIP_WIDTH, WHITE_SHIP_HEIGHT);
        threatVel = WHITE_SHIP_VEL;
        threatCollisionBox.resize(3);
        updateThreatCollisionBox();
        setHealth(WHITE_SHIP);
        break;
    }
}
void Threat::setThreatMoveType(const int &type, const int &order, const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT)
{
    threatMoveType = type;
    switch (threatMoveType)
    {
    case FROM_LEFT:
        this->setThreatOffset(-SCREEN_WIDTH - (order + 1) * 300, rand() % SCREEN_HEIGHT / 2);
        break;
    case FROM_RIGHT:
        this->setThreatOffset(SCREEN_WIDTH * 2 + (order + 1) * 300, rand() % SCREEN_HEIGHT / 2);
        break;
    case UP_TO_DOWN:
        this->setThreatOffset(rand() % (SCREEN_WIDTH - threatW * 2) + 0, -SCREEN_HEIGHT - (order + 1) * 300);
        break;
    }
}
int Threat::getThreatType()
{
    return threatType;
}
int Threat::getThreatMoveType()
{
    return threatMoveType;
}
void Threat::threatMove(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT)
{
    switch (threatMoveType)
    {
    case FROM_LEFT:
        threatX += threatVel;
        updateThreatCollisionBox();
        if (threatX > SCREEN_WIDTH)
        {
            this->setThreatOffset(rand() % (SCREEN_WIDTH) + (-SCREEN_WIDTH), rand() % (SCREEN_HEIGHT / 2));
        }
        updateThreatCollisionBox();
        break;
    case FROM_RIGHT:
        threatX -= threatVel;
        updateThreatCollisionBox();
        if (threatX + threatW < 0)
        {
            this->setThreatOffset(SCREEN_WIDTH + rand() % 1000 + 300, rand() % (SCREEN_HEIGHT / 2));
        }
        updateThreatCollisionBox();
        break;
    case UP_TO_DOWN:
        threatY += threatVel;
        updateThreatCollisionBox();
        if (threatY > SCREEN_HEIGHT)
        {
            this->setThreatOffset(rand() % (SCREEN_WIDTH - threatW * 2), 0 - (rand() % SCREEN_HEIGHT));
        }
        updateThreatCollisionBox();
        break;
    }
}
void Threat::renderThreat(SDL_Renderer *gRenderer)
{
    render(gRenderer, threatX, threatY);
}
void Threat::handleInputEvent(SDL_Event &e)
{
}
// Handle threat's health
void Threat::setHealth(const int &type)
{
    switch (type)
    {
    case RED_SHIP:
        threatHealth = RED_SHIP_HEALTH;
        break;
    case BLUE_SHIP:
        threatHealth = BLUE_SHIP_HEALTH;
        break;
    case WHITE_SHIP:
        threatHealth = WHITE_SHIP_HEALTH;
        break;
    }
}
void Threat::loseHealth()
{
    threatHealth--;
}
int Threat::getHealth()
{
    return threatHealth;
}
bool Threat::initThreat(SDL_Renderer *gRenderer, const int &order, const int &numOfThreatMoveType, const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT)
{
    bool success = true;

    switch (rand() % 3)
    {
    case 0:
        if (!this->loadFromFile(gRenderer, "res/red_ship.png"))
        {
            printf("Failed to make threat!\n");
            success = false;
        }
        this->setThreatType(RED_SHIP);
        break;
    case 1:
        if (!this->loadFromFile(gRenderer, "res/blue_ship.png"))
        {
            printf("Failed to make threa!\n");
            success = false;
        }
        this->setThreatType(BLUE_SHIP);
        break;
    case 2:
        if (!this->loadFromFile(gRenderer, "res/white_ship.png"))
        {
            printf("Failed to make threat\n");
            success = false;
        }
        this->setThreatType(WHITE_SHIP);
        break;
    }
    if (success)
    {
        this->setThreatMoveType(rand() % numOfThreatMoveType, order, SCREEN_WIDTH, SCREEN_HEIGHT);
        Bullet *p_multi_threatBullet = new Bullet();
        this->initBullet(gRenderer, p_multi_threatBullet, threatType);
    }
    return success;
}
void Threat::initBullet(SDL_Renderer *gRenderer, Bullet *p_bullet, const int &type)
{
    switch (type)
    {
    case RED_SHIP:
        if (p_bullet != NULL)
        {
            bool load_success = p_bullet->loadFromFile(gRenderer, "res/red_bullet_2.png");
            if (load_success)
            {
                p_bullet->setType(RED_2);
                p_bullet->setBulletMoveStatus(true);
                p_bullet->setBulletOffset(this->threatX + (this->threatW - p_bullet->getBulletWidth()) / 2, this->threatY + this->threatH);
            }
        }
        break;
    case BLUE_SHIP:
        if (p_bullet != NULL)
        {
            bool load_success = p_bullet->loadFromFile(gRenderer, "res/blue_bullet_3.png");
            if (load_success)
            {
                p_bullet->setType(BLUE_3);
                p_bullet->setBulletMoveStatus(true);
                p_bullet->setBulletOffset(this->threatX + (this->threatW - p_bullet->getBulletWidth()) / 2, this->threatY + this->threatH);
            }
        }
        break;
    case WHITE_SHIP:
        if (p_bullet != NULL)
        {
            bool load_success = p_bullet->loadFromFile(gRenderer, "res/green_bullet_3.png");
            if (load_success)
            {
                p_bullet->setType(GREEN);
                p_bullet->setBulletMoveStatus(true);
                p_bullet->setBulletOffset(this->threatX + (this->threatW - p_bullet->getBulletWidth()) / 2, this->threatY + this->threatH);
            }
        }
        break;
    }
    threatBulletList.push_back(p_bullet);
}

void Threat::renderBullet(SDL_Renderer *gRenderer, const int &y_axis_border)
{
    for (int i = 0; i < threatBulletList.size(); i++)
    {
        Bullet *p_bullet = threatBulletList.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->getBulletMoveStatus())
            {
                p_bullet->bulletMoveDown(y_axis_border);
                p_bullet->renderBullet(p_bullet->getType(), gRenderer);
            }
            else
            {
                p_bullet->setBulletMoveStatus(true);
                p_bullet->setBulletOffset(this->threatX + (this->threatW - p_bullet->getBulletWidth()) / 2, this->threatY + this->threatH);
            }
        }
    }
}
void Threat::setThreatBulletList(vector<Bullet *> bulletlist)
{
    threatBulletList = bulletlist;
}
vector<Bullet *> Threat::getThreatBulletList()
{
    return threatBulletList;
}

void Threat::resetThreat(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT)
{
    switch (threatMoveType)
    {
    case FROM_LEFT:
        this->setThreatOffset(rand() % (SCREEN_WIDTH * 3 / 5) + (-SCREEN_WIDTH), rand() % (SCREEN_HEIGHT / 2));
        break;
    case FROM_RIGHT:
        this->setThreatOffset(rand() % (SCREEN_WIDTH * 3 / 5) + (SCREEN_WIDTH), rand() % (SCREEN_HEIGHT / 2));
        break;
    case UP_TO_DOWN:
        this->setThreatOffset(rand() % SCREEN_WIDTH, rand() % (SCREEN_HEIGHT * 4 / 5) + (-SCREEN_HEIGHT));
        break;
    }
    resetThreatBullet();
    updateThreatCollisionBox();
    setHealth(threatType);
}
void Threat::resetThreatBullet()
{
    for (int bullet_num = 0; bullet_num < threatBulletList.size(); bullet_num++)
    {
        if (threatBulletList[bullet_num]->getBulletMoveStatus() == false)
        {
            threatBulletList[bullet_num]->setBulletOffset(this->threatX + (this->threatW - threatBulletList[bullet_num]->getBulletWidth()) / 2, this->threatY + this->threatH);
        }
    }
}
void Threat::returnThreatBullet()
{
    for (int bullet_num = 0; bullet_num < threatBulletList.size(); bullet_num++)
    {
        if (threatBulletList[bullet_num]->getBulletMoveStatus() == true)
        {
            threatBulletList[bullet_num]->setBulletOffset(this->threatX + (this->threatW - threatBulletList[bullet_num]->getBulletWidth()) / 2, this->threatY + this->threatH);
        }
    }
}