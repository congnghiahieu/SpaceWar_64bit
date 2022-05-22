#include <headers/text.h>
Text::Text()
{
}
Text::~Text()
{
    TTF_CloseFont(font);
    font = NULL;
    free();
}
bool Text::loadFont(const string &font_path, const int &font_size)
{
    font = TTF_OpenFont(font_path.c_str(), font_size);
    return font != NULL;
}
bool Text::loadText(SDL_Renderer *gRenderer, const string &content, const SDL_Color &color)
{
    return loadFromRenderedText(gRenderer, font, content.c_str(), color);
}