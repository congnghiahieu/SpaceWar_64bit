#ifndef BASIC_H
#define BASIC_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <headers/texture.h>
#include <headers/background.h>
#include <headers/ship.h>
#include <headers/bullet.h>
#include <headers/explosion.h>
#include <headers/music.h>
#include <headers/threat.h>
#include <headers/text.h>
#include <headers/button.h>
#include <headers/menu.h>
#include <headers/boss.h>
#include <headers/bossBullet.h>
#include <headers/item.h>

using namespace std;

// Screen dimension constants
const int SCREEN_WIDTH = 1900;
const int SCREEN_HEIGHT = 1000;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Different type of background texture
Background gBG;
Background gBGEarth;
Background gameOver;
Background spaceWar;
Background misson;
Background victory;
Background leader;
Background instruction;
Background pause;
Background setting;

// Game menu
Menu startMenu;
Menu tutorialMenu;
Menu optionMenu;
Menu gameoverMenu;
Menu successMenu;
Menu victoryMenu;
Menu rankMenu;
Menu pauseMenu;

// Player's ship
Ship gMainShip(SCREEN_WIDTH, SCREEN_HEIGHT);

// Text
Text scoreText;
Text scoreNum;
Text scoreData[3];
Text targetText;
Text targetNum;
Text tutorial[3];
Texture medal[3];

// Music for game
bool game_music = true;
bool game_sfx = true;
Music gameOverMusic[TOTAL_GAMEOVER_MUSIC];
Music themeMusic[TOTAL_THEME_MUSIC];
Music missonMusic[TOTAL_MISSON_MUSIC];
Music victoryMusic[TOTAL_VICTORY_MUSIC];
Music successMusic[TOTAL_SUCCESS_MUSIC];
Music bossMusic[TOTAL_BOSS_MUSIC];
Music mainExpSound[TOTAL_MAIN_EXP_SOUND];
Music threatExpSound;
Music bossExpSound;
Music shootSound[TOTAL_SHOOT_SOUND];
Music item;

// Starts up SDL and creates window
bool init(string path);

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

void playMissionMusic();

void playGameOverMusic();

void playThemeMusic();

void playVictoryMusic();

void playSuccessMusic();

void playBossMusic();

void music_off();

void music_pause();

void music_resume();

int initStartMenu(SDL_Event &e);

int initTutorialMenu(SDL_Event &e);

int initOptionMenu(SDL_Event &e);

int initGameOverMenu(SDL_Event &e);

int initSuccessMenu(SDL_Event &e);

int initVictoryMenu(SDL_Event &e);

int initRankMenu(SDL_Event &e);

int initPauseMenu(SDL_Event &e);

#endif