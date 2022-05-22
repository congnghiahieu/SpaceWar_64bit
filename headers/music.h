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

#endif