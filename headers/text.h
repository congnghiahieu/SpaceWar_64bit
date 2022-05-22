#ifndef TEXT_H
#define TEXT_H
#include <SDL_ttf.h>
#include <headers/texture.h>
#include <string>
#include <cstring>
#include <sstream>
// Colors
const SDL_Color BLACK_COLOR = {0, 0, 0, 255};
const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
const SDL_Color RED_COLOR = {255, 0, 0, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255, 255};
const SDL_Color GREEN_COLOR = {0, 255, 0, 255};
const SDL_Color SILVER_COLOR = {192, 192, 192, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0, 255};
const SDL_Color YELLOW_COLOR = {255, 255, 0, 255};
const SDL_Color GOLD_COLOR = {255, 215, 0, 255};
const SDL_Color CHOCOLATE_COLOR = {210, 105, 30, 255};
const SDL_Color CYAN_COLOR = {0, 255, 255, 255};

class Text : public Texture
{
private:
    TTF_Font *font;

public:
    Text();
    ~Text();

    bool loadFont(const string &font_path, const int &font_size);
    bool loadText(SDL_Renderer *gRenderer, const string &content, const SDL_Color &color);
};

#endif