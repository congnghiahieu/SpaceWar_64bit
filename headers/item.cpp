#include <headers/item.h>
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