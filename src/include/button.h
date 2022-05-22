#ifndef BUTTON_H
#define BUTTON_H
#include <texture.h>
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
Button::Button()
{
    position.x = 0;
    position.y = 0;

    state = MOUSE_OUT;
}
Button::~Button()
{
    for (int i = 0; i < TOTAL_STATE; i++)
    {
        buttonShape[i].free();
    }
}
bool Button::loadButtonShape(SDL_Renderer *gRenderer, const string &mouseOut_path)
{
    string mouseIn_path = mouseOut_path.substr(0, mouseOut_path.find('.') - 0) + "_gold.png";
    if ((!buttonShape[MOUSE_OUT].loadFromFile(gRenderer, mouseOut_path.c_str())) || (!buttonShape[MOUSE_IN].loadFromFile(gRenderer, mouseIn_path.c_str())))
    {
        return false;
    }
    return true;
}
void Button::setPosition(const int &x, const int &y)
{
    position.x = x;
    position.y = y;
}
bool Button::setButton(SDL_Renderer *gRenderer, const int &type, const int &x, const int &y)
{
    bool success = true;
    buttonType = type;
    switch (buttonType)
    {
    case PLAY:
        if (!this->loadButtonShape(gRenderer, "res/play.png"))
        {
            printf("Failed to load play menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case TUTORIAL:
        if (!this->loadButtonShape(gRenderer, "res/tutorial.png"))
        {
            printf("Failed to load tutorial menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case OPTIONS:
        if (!this->loadButtonShape(gRenderer, "res/options.png"))
        {
            printf("Failed to load options menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case LEADERBOARD:
        if (!this->loadButtonShape(gRenderer, "res/leaderboard.png"))
        {
            printf("Failed to load leaderboard menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case MUSIC:
        if (!this->loadButtonShape(gRenderer, "res/music.png"))
        {
            printf("Failed to load music menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case SFX:
        if (!this->loadButtonShape(gRenderer, "res/sfx.png"))
        {
            printf("Failed to load sfx menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case REPLAY:
        if (!this->loadButtonShape(gRenderer, "res/replay.png"))
        {
            printf("Failed to load replay menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case RESUME:
        if (!this->loadButtonShape(gRenderer, "res/resume.png"))
        {
            printf("Failed to load resume menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case CONTINUE:
        if (!this->loadButtonShape(gRenderer, "res/continue.png"))
        {
            printf("Failed to load continue menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case CANCEL:
        if (!this->loadButtonShape(gRenderer, "res/cancel.png"))
        {
            printf("Failed to load cancel menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case BACK:
        if (!this->loadButtonShape(gRenderer, "res/back.png"))
        {
            printf("Failed to load back menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case QUIT:
        if (!this->loadButtonShape(gRenderer, "res/quit.png"))
        {
            printf("Failed to load quit menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    case EXIT:
        if (!this->loadButtonShape(gRenderer, "res/exit.png"))
        {
            printf("Failed to load exit menu button!\n SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            this->setPosition(x, y);
        }
        break;
    }
    return success;
}
int Button::handleEvent(SDL_Event &e)
{
    // If mouse event happened
    int mouseX = e.motion.x;
    int mouseY = e.motion.y;
    switch (e.type)
    {
    case SDL_MOUSEMOTION:
        if (mouseX >= position.x && mouseX <= position.x + BUTTON_WIDTH && mouseY >= position.y && mouseY <= position.y + BUTTON_HEIGHT)
        {
            state = MOUSE_IN;
        }
        else
        {
            state = MOUSE_OUT;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (state == MOUSE_IN)
        {
            return buttonType;
        }
        break;
    }
    return -1;
}
void Button::renderButton(SDL_Renderer *gRenderer)
{
    buttonShape[state].render(gRenderer, position.x, position.y);
}
#endif