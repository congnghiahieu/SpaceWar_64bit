#ifndef BUTTON_H
#define BUTTON_H
#include <headers/texture.h>
using namespace std;
const int BUTTON_WIDTH = 235;
const int BUTTON_HEIGHT = 75;
const int SPACE_BETWEEN_BUTTON = 125;
enum buttonType
{
    PLAY,
    TUTORIAL,
    OPTIONS,
    LEADERBOARD,
    MUSIC,
    SFX,
    REPLAY,
    RESUME,
    CONTINUE,
    CANCEL,
    BACK,
    QUIT,
    EXIT,
    TOTAL_BUTTON_TYPE
};
enum buttonState
{
    MOUSE_OUT = 0,
    MOUSE_IN = 1,
    TOTAL_STATE = 2,
    MOUSE_DOWN,
    MOUSE_UP
};
class Button
{
private:
    // Top left position;
    SDL_Point position;

    // button state
    int state;

    // Button type
    int buttonType;

    Texture buttonShape[TOTAL_STATE];

public:
    // Initializes internal variables
    Button();
    ~Button();

    bool loadButtonShape(SDL_Renderer *gRenderer, const string &mouseOut_path);
    // Sets top left position
    void setPosition(const int &x, const int &y);
    // void set button
    bool setButton(SDL_Renderer *gRenderer, const int &type, const int &x, const int &y);
    // Handles mouse event
    int handleEvent(SDL_Event &e);

    // Shows button sprite
    void renderButton(SDL_Renderer *gRenderer);
};

#endif