#ifndef MUSIC_H
#define MUSIC_H
#include <SDL_mixer.h>
#include <iostream>
#include <string>
using namespace std;
enum music
{
    NO_LOOP = 0,
    INFINITE_LOOP = -1,
    TOTAL_GAMEOVER_MUSIC = 5,
    TOTAL_MISSON_MUSIC = 5,
    TOTAL_THEME_MUSIC = 3,
    TOTAL_SUCCESS_MUSIC = 3,
    TOTAL_BOSS_MUSIC = 3,
    TOTAL_VICTORY_MUSIC = 2,
    TOTAL_MAIN_EXP_SOUND = 2,
    TOTAL_SHOOT_SOUND = 2,
    LEFT_SHOOT = 0,
    RIGHT_SHOOT = 1
};
class Music
{
private:
    Mix_Chunk *sound;
    Mix_Music *music;

public:
    Music();
    ~Music();

    bool loadSound(string path);
    bool loadMusic(string path);
    void playSound(const bool &game_sfx);
    void playMusic(const int &loops);
};
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
#endif