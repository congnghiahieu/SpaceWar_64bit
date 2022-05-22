#ifndef MENU_H
#define MENU_H
#include <headers/texture.h>
#include <headers/button.h>
#include <headers/background.h>
#include <vector>
class Menu
{
private:
    Background menuBG;
    vector<Button *> menuButtonList;

public:
    Menu();
    ~Menu();

    bool loadBG(SDL_Renderer *gRenderer, const string &path);
    bool addButton(SDL_Renderer *gRenderer, const int &button_type, const int &x, const int &y);
    int handleEvent(SDL_Event &e);
    void render(SDL_Renderer *gRenderer);
};

#endif