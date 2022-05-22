#ifndef ITEM_H
#define ITEM_H
#include <texture.h>
#include <cstdlib>
enum itemType
{
    HEALTH,
    BULLET,
    SHIELD,
    SCORE,
    TOTAL_ITEM,
    ITEM_WIDTH = 50,
    ITEM_HEIGHT = 60,
    ITEM_VEL = 1,
};
class Item : public Texture
{
private:
    int itemX;
    int itemY;
    int itemW;
    int itemH;

    int itemVel;
    bool is_move;

    int itemType;

    SDL_Rect itemCollisionBox;

public:
    Item();
    ~Item();

    void setItemOffset(const int &x, const int &y);

    void updateCollisionBox();
    SDL_Rect getCollisionBox();

    void setType(SDL_Renderer *gRenderer, const int &type);
    int getType();

    void setMoveStatus(const bool &type);
    bool getMoveStatus();

    void move(const int &y_axis_border);
    void renderItem(SDL_Renderer *gRenderer);

    void initItem(SDL_Renderer *gRenderer, const int &x, const int &y);
};
Item::Item()
{
    itemX = 0;
    itemY = 0;
    itemW = ITEM_WIDTH;
    itemH = ITEM_HEIGHT;
    itemVel = ITEM_VEL;
    is_move = false;
    updateCollisionBox();
}
Item::~Item()
{
    free();
}

void Item::setItemOffset(const int &x, const int &y)
{
    itemX = x;
    itemY = y;
    updateCollisionBox();
}

void Item::updateCollisionBox()
{
    itemCollisionBox = {itemX, itemY + 16, itemW, 32};
}
SDL_Rect Item::getCollisionBox()
{
    return itemCollisionBox;
}

void Item::setType(SDL_Renderer *gRenderer, const int &type)
{
    itemType = type;
    switch (itemType)
    {
    case HEALTH:
        this->loadFromFile(gRenderer, "res/item_1.png");
        break;
    case BULLET:
        this->loadFromFile(gRenderer, "res/item_2.png");
        break;
    case SHIELD:
        this->loadFromFile(gRenderer, "res/item_3.png");
        break;
    case SCORE:
        this->loadFromFile(gRenderer, "res/item_4.png");
        break;
    }
}
int Item::getType()
{
    return itemType;
}

void Item::setMoveStatus(const bool &type)
{
    is_move = type;
}
bool Item::getMoveStatus()
{
    return is_move;
}

void Item::move(const int &y_axis_border)
{
    if (is_move == true)
    {
        itemY += itemVel;
        updateCollisionBox();
        if (itemY > y_axis_border)
        {
            is_move = false;
        }
    }
}
void Item::renderItem(SDL_Renderer *gRenderer)
{
    render(gRenderer, itemX, itemY);
}

void Item::initItem(SDL_Renderer *gRenderer, const int &x, const int &y)
{
    switch (rand() % TOTAL_ITEM)
    {
    case HEALTH:
        setType(gRenderer, HEALTH);
        break;
    case BULLET:
        setType(gRenderer, BULLET);
        break;
    case SHIELD:
        setType(gRenderer, SHIELD);
        break;
    case SCORE:
        setType(gRenderer, SCORE);
        break;
    }
    setMoveStatus(true);
    setItemOffset(x, y);
}
#endif