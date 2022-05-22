#include <headers/music.h>
Music::Music()
{
    sound = NULL;
    music = NULL;
}
Music::~Music()
{
    Mix_FreeChunk(sound);
    Mix_FreeMusic(music);
    sound = NULL;
    music = NULL;
}

bool Music::loadSound(string path)
{
    sound = Mix_LoadWAV(path.c_str());
    return sound != NULL;
}
bool Music::loadMusic(string path)
{
    music = Mix_LoadMUS(path.c_str());
    return music != NULL;
}
void Music::playSound(const bool &game_sfx)
{
    if (game_sfx == true)
    {
        Mix_PlayChannel(-1, sound, NO_LOOP);
    }
}
void Music::playMusic(const int &loops)
{
    // If there is no music playing
    if (Mix_PlayingMusic() == 0)
    {
        // Play the music
        Mix_PlayMusic(music, loops);
    }
}