#ifndef LOGIC_H
#define LOGIC_H
#include <headers/basic.h>

bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);

bool checkCollision(const vector<SDL_Rect> &a, const SDL_Rect &b);

bool checkCollision(const vector<SDL_Rect> &a, const vector<SDL_Rect> &b);

// Handle item
void generateItem(vector<Item *> &itemList, const int &drop_percent, const int &x, const int &y);

void deleteItem(vector<Item *> &itemList, const int &itemIndex);

void clearItemList(vector<Item *> &itemList);

void getItem(const int &itemType, int &score, const bool &game_sfx);

void caculateScore(int &score, const int &threatType);

void resetShipStatus(int &score);

int play(SDL_Event &e, int &score, const int &target, const int &total_threat, const int &numOfThreatMoveType, bool &is_target);

int playBoss(SDL_Event &e, int &score, bool &is_target);

int gameStage(const int &stage_number, int &score, const int &target, const int &total_threat, const int &numOfThreatMoveType, SDL_Event &e);

int gameStageBoss(const int &stage_number, int &score, SDL_Event &e);

void save(const int &score);

#endif