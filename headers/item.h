#ifndef ITEM_H
#define ITEM_H
#include <headers/texture.h>
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

#endif