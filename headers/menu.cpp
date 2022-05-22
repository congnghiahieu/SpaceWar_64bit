#include <headers/menu.h>
Menu::Menu()
{
}
Menu::~Menu()
{
    if (menuButtonList.size() > 0)
    {
        for (int i = 0; i < menuButtonList.size(); i++)
        {
            Button *p_button = menuButtonList.at(i);
            if (p_button != NULL)
            {
                delete p_button;
                p_button = NULL;
            }
        }
        menuButtonList.clear();
    }
    menuBG.free();
}
bool Menu::loadBG(SDL_Renderer *gRenderer, const string &path)
{
    if (!menuBG.loadFromFile(gRenderer, path))
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool Menu::addButton(SDL_Renderer *gRenderer, const int &button_type, const int &x, const int &y)
{
    Button *p_button = new Button();
    if (p_button->setButton(gRenderer, button_type, x, y))
    {
        menuButtonList.push_back(p_button);
        return true;
    }
    return false;
}
int Menu::handleEvent(SDL_Event &e)
{
    int action = -1;
    for (int i = 0; i < menuButtonList.size(); i++)
    {
        Button *p_button = menuButtonList.at(i);
        action = p_button->handleEvent(e);
        if (action >= PLAY && action <= EXIT)
        {
            return action;
        }
    }
    return action;
}
void Menu::render(SDL_Renderer *gRenderer)
{
    menuBG.render(gRenderer, 0, 0);
    for (int i = 0; i < menuButtonList.size(); i++)
    {
        Button *p_button = menuButtonList.at(i);
        if (p_button != NULL)
        {
            p_button->renderButton(gRenderer);
        }
    }
}