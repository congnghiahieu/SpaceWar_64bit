#include <headers/background.h>
Background::Background()
{
}

Background::~Background()
{
    free();
}

void Background::vertical_scrollingBG(SDL_Renderer *gRenderer)
{
    // The background scrolling offset
    static double vertical_scrollingOffsetFloat = 0;
    vertical_scrollingOffsetFloat -= FLOAT_SPEED;

    // Scroll background
    int used_scrollingOffset = (int)vertical_scrollingOffsetFloat;

    if (vertical_scrollingOffsetFloat < -getHeight())
    {
        vertical_scrollingOffsetFloat = 0;
    }

    // Render background
    render(gRenderer, 0, used_scrollingOffset);
    render(gRenderer, 0, used_scrollingOffset + getHeight());
}

void Background::horizontal_scrollingBG(SDL_Renderer *gRenderer)
{
    // The background scrolling offset
    static double horizontal_scrollingOffsetFloat = 0;
    horizontal_scrollingOffsetFloat -= FLOAT_SPEED;

    // Scroll background
    int used_scrollingOffset = (int)horizontal_scrollingOffsetFloat;

    if (horizontal_scrollingOffsetFloat < -getWidth())
    {
        horizontal_scrollingOffsetFloat = 0;
    }

    // Render background
    render(gRenderer, used_scrollingOffset, 0);
    render(gRenderer, used_scrollingOffset + getWidth(), 0);
}