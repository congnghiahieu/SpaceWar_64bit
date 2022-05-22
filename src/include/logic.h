#ifndef LOGIC_H
#define LOGIC_H
#include <basic.h>

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

bool checkCollision(const SDL_Rect &a, const SDL_Rect &b)
{
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    // If none of the sides from A are outside B
    return true;
}

bool checkCollision(const vector<SDL_Rect> &a, const SDL_Rect &b)
{
    for (int order = 0; order < a.size(); order++)
    {
        if (checkCollision(a[order], b))
        {
            return true;
        }
    }

    return false;
}

bool checkCollision(const vector<SDL_Rect> &a, const vector<SDL_Rect> &b)
{
    for (int numA = 0; numA < a.size(); numA++)
    {
        for (int numB = 0; numB < b.size(); numB++)
        {
            if (checkCollision(a[numA], b[numB]))
            {
                return true;
            }
        }
    }

    return false;
}

void generateItem(vector<Item *> &itemList, const int &drop_percent, const int &x, const int &y)
{
    int random = rand() % 100;
    if ((random >= 0 && random <= drop_percent))
    {
        Item *p_item = new Item;
        p_item->initItem(gRenderer, x, y);
        itemList.push_back(p_item);
    }
}

void deleteItem(vector<Item *> &itemList, const int &itemIndex)
{
    int size = itemList.size();
    if (size > 0 && itemIndex < size)
    {
        Item *p_item = itemList.at(itemIndex);
        itemList.erase(itemList.begin() + itemIndex);
        if (p_item != NULL)
        {
            delete p_item;
            p_item = NULL;
        }
    }
}

void clearItemList(vector<Item *> &itemList)
{
    for (int num = 0; num < itemList.size(); num++)
    {
        Item *p_item = itemList.at(num);
        if (p_item != NULL)
        {
            delete p_item;
            p_item = NULL;
        }
    }
    itemList.clear();
}

void getItem(const int &itemType, int &score, const bool &game_sfx)
{
    item.playSound(game_sfx);
    switch (itemType)
    {
    case HEALTH:
        gMainShip.health.gainHealth();
        break;
    case BULLET:
        gMainShip.gainBulletLevel();
        break;
    case SHIELD:
        gMainShip.deleteShieldCD();
        break;
    case SCORE:
        score += 20;
        break;
    }
}

void caculateScore(int &score, const int &threatType)
{
    switch (threatType)
    {
    case RED_SHIP:
        score++;
        break;
    case BLUE_SHIP:
        score += 2;
        break;
    case WHITE_SHIP:
        score += 3;
        break;
    }
}

void resetShipStatus(int &score)
{
    score = 0;
    gMainShip.health.initHealth(gRenderer, DEFAULT_HEALTH);
    gMainShip.resetBulletLevel();
}

int play(SDL_Event &e, int &score, const int &target, const int &total_threat, const int &numOfThreatMoveType, bool &is_target)
{
    // Main loop flag
    bool is_gameOver = false;
    int enemy_destroyed = 0;

    // threat's setting

    Threat *p_multi_threats = new Threat[total_threat];
    for (int threat_num = 0; threat_num < total_threat; threat_num++)
    {
        if (p_multi_threats[threat_num].initThreat(gRenderer, threat_num, numOfThreatMoveType, SCREEN_WIDTH, SCREEN_HEIGHT) == false)
        {
            delete[] p_multi_threats;
            return EXIT;
        }
    }

    // Item
    vector<Item *> itemList;

    // While application is running
    while (!is_gameOver && !is_target)
    {

        if (game_music == true)
        {
            playMissionMusic();
        }
        else
        {
            music_off();
        }

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                delete[] p_multi_threats;
                clearItemList(itemList);
                return EXIT;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                int pauseMenuAction = initPauseMenu(e);
                if (pauseMenuAction == EXIT || pauseMenuAction == QUIT)
                {
                    delete[] p_multi_threats;
                    clearItemList(itemList);
                    return EXIT;
                }
                else if (pauseMenuAction == BACK)
                {
                    delete[] p_multi_threats;
                    clearItemList(itemList);
                    gMainShip.reset(SCREEN_WIDTH, SCREEN_HEIGHT);
                    return BACK;
                }
            }

            gMainShip.handleEvent(gRenderer, e, shootSound, game_sfx);
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render background
        gBG.vertical_scrollingBG(gRenderer);

        // Render player health
        gMainShip.health.renderHealth(gRenderer, SCREEN_HEIGHT - gMainShip.health.getHeight());
        // Render score
        scoreText.render(gRenderer, 0, SCREEN_HEIGHT - gMainShip.health.getHeight() * 2);
        if (scoreNum.loadText(gRenderer, to_string(score), WHITE_COLOR))
        {
            scoreNum.render(gRenderer, scoreText.getWidth() * 5 / 4, SCREEN_HEIGHT - gMainShip.health.getHeight() * 2);
        }
        // Render target
        targetText.render(gRenderer, 0, SCREEN_HEIGHT - gMainShip.health.getHeight() * 2 - scoreText.getHeight() * 2);
        if (targetNum.loadText(gRenderer, to_string(enemy_destroyed) + "/" + to_string(target), WHITE_COLOR))
        {
            targetNum.render(gRenderer, targetText.getWidth() * 5 / 4, SCREEN_HEIGHT - gMainShip.health.getHeight() * 2 - scoreText.getHeight() * 2);
        }

        // Render ship
        gMainShip.move(SCREEN_WIDTH, SCREEN_HEIGHT);
        gMainShip.renderPlayerShip(gRenderer);
        // Render ship bullet
        gMainShip.renderBulletList(gRenderer);

        // Render nulti threats
        for (int threat_num = 0; threat_num < total_threat; threat_num++)
        {
            p_multi_threats[threat_num].threatMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            p_multi_threats[threat_num].renderThreat(gRenderer);
            p_multi_threats[threat_num].renderBullet(gRenderer, SCREEN_HEIGHT);
        }

        // Check collision between threat
        for (int threat_num = 0; threat_num < total_threat; threat_num++)
        {
            // Check collision between main ship's bullet and threats
            vector<Bullet *> p_ship_bullet = gMainShip.getBulletList();
            for (int bullet_num = 0; bullet_num < p_ship_bullet.size(); bullet_num++)
            {
                if (checkCollision(p_multi_threats[threat_num].getThreatCollisionBox(), p_ship_bullet[bullet_num]->getCollisionBox()))
                {
                    if (p_multi_threats[threat_num].getHealth() > 1)
                    {
                        gMainShip.deleteShipBullet(bullet_num);
                        p_multi_threats[threat_num].loseHealth();
                    }
                    else
                    {
                        gMainShip.deleteShipBullet(bullet_num);

                        threatExpSound.playSound(game_sfx);

                        generateItem(itemList, 20, p_multi_threats[threat_num].getThreatX(), p_multi_threats[threat_num].getThreatY());

                        p_multi_threats[threat_num].resetThreat(SCREEN_WIDTH, SCREEN_HEIGHT);
                        caculateScore(score, p_multi_threats[threat_num].getThreatType());
                        enemy_destroyed++;
                        if (enemy_destroyed == target)
                        {
                            is_target = true;
                        }
                    }
                }
            }

            // Check collision between main ship and threats's bullet
            vector<Bullet *> p_threat_bullet = p_multi_threats[threat_num].getThreatBulletList();
            for (int threatBullet_num = 0; threatBullet_num < p_threat_bullet.size(); threatBullet_num++)
            {
                if (checkCollision(gMainShip.getCollisionBox(), p_threat_bullet[threatBullet_num]->getCollisionBox()))
                {
                    p_multi_threats[threat_num].returnThreatBullet();
                    if (gMainShip.getImmortalState() == false)
                    {
                        if (gMainShip.health.getHealthNum() > 1)
                        {
                            mainExpSound[1].playSound(game_sfx);
                            gMainShip.health.loseHealth();
                            gMainShip.renderMainExplosion(gRenderer);

                            gMainShip.respawn(SCREEN_WIDTH, SCREEN_HEIGHT);
                        }
                        else
                        {
                            mainExpSound[1].playSound(game_sfx);
                            gMainShip.health.loseHealth();
                            gMainShip.renderMainExplosion(gRenderer);
                            music_off();
                            is_gameOver = true;
                        }
                    }
                }
            }
            // Check collision between main ship and threats
            if (checkCollision(gMainShip.getCollisionBox(), p_multi_threats[threat_num].getThreatCollisionBox()))
            {
                p_multi_threats[threat_num].resetThreat(SCREEN_WIDTH, SCREEN_HEIGHT);
                threatExpSound.playSound(game_sfx);
                if (gMainShip.getImmortalState() == false)
                {
                    if (gMainShip.health.getHealthNum() > 1)
                    {
                        mainExpSound[0].playSound(game_sfx);

                        gMainShip.health.loseHealth();

                        gMainShip.renderMainExplosion(gRenderer);

                        gMainShip.respawn(SCREEN_WIDTH, SCREEN_HEIGHT);
                    }
                    else
                    {
                        mainExpSound[0].playSound(game_sfx);
                        gMainShip.health.loseHealth();
                        gMainShip.renderMainExplosion(gRenderer);
                        music_off();
                        is_gameOver = true;
                    }
                }
            }
        }
        // Render Item

        for (int item_num = 0; item_num < itemList.size(); item_num++)
        {
            itemList[item_num]->move(SCREEN_HEIGHT + 10);
            if (itemList[item_num]->getMoveStatus() == false)
            {
                deleteItem(itemList, item_num);
            }
            itemList[item_num]->renderItem(gRenderer);
        }

        // Check collision with item
        for (int item_num = 0; item_num < itemList.size(); item_num++)
        {
            if (checkCollision(gMainShip.getCollisionBox(), itemList[item_num]->getCollisionBox()))
            {
                getItem(itemList[item_num]->getType(), score, game_sfx);
                deleteItem(itemList, item_num);
            }
        }

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    delete[] p_multi_threats;
    clearItemList(itemList);
    gMainShip.reset(SCREEN_WIDTH, SCREEN_HEIGHT);
    return -1;
}
int playBoss(SDL_Event &e, int &score, bool &is_target)
{
    // Main loop flag
    bool is_gameOver = false;

    Boss *mainBoss = new Boss;
    if (!mainBoss->initBoss(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        delete mainBoss;
        return EXIT;
    }

    // Item
    vector<Item *> itemList;

    // While application is running
    while (!is_gameOver && !is_target)
    {

        if (game_music == true)
        {
            playBossMusic();
        }
        else
        {
            music_off();
        }

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                delete mainBoss;
                clearItemList(itemList);
                return EXIT;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                int pauseMenuAction = initPauseMenu(e);
                if (pauseMenuAction == EXIT || pauseMenuAction == QUIT)
                {
                    delete mainBoss;
                    clearItemList(itemList);
                    return EXIT;
                }
                else if (pauseMenuAction == BACK)
                {
                    delete mainBoss;
                    clearItemList(itemList);
                    gMainShip.reset(SCREEN_WIDTH, SCREEN_HEIGHT);
                    return BACK;
                }
            }

            if (mainBoss->getDeadState() == false)
            {
                gMainShip.handleEvent(gRenderer, e, shootSound, game_sfx);
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render background
        gBG.vertical_scrollingBG(gRenderer);

        // Render player health
        gMainShip.health.renderHealth(gRenderer, SCREEN_HEIGHT - gMainShip.health.getHeight());
        // Render score
        scoreText.render(gRenderer, 0, SCREEN_HEIGHT - gMainShip.health.getHeight() * 2);
        if (scoreNum.loadText(gRenderer, to_string(score), WHITE_COLOR))
        {
            scoreNum.render(gRenderer, scoreText.getWidth() * 5 / 4, SCREEN_HEIGHT - gMainShip.health.getHeight() * 2);
        }
        // Render target
        targetText.render(gRenderer, 0, SCREEN_HEIGHT - gMainShip.health.getHeight() * 2 - scoreText.getHeight() * 2);
        if (targetNum.loadText(gRenderer, "DEFEAT THE BOSS", WHITE_COLOR))
        {
            targetNum.render(gRenderer, targetText.getWidth() * 5 / 4, SCREEN_HEIGHT - gMainShip.health.getHeight() * 2 - scoreText.getHeight() * 2);
        }

        // Render ship
        if (mainBoss->getDeadState() == false)
        {
            gMainShip.move(SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        gMainShip.renderPlayerShip(gRenderer);
        // Render ship bullet
        gMainShip.renderBulletList(gRenderer);

        // Render Boss
        if (mainBoss->getDeadState() == false)
        {
            mainBoss->move();
            mainBoss->renderBoss(gRenderer);
            mainBoss->generateBullet(gRenderer);
            mainBoss->renderBossBullet(gRenderer);
        }
        else
        {
            mainBoss->renderBoss(gRenderer);
            mainBoss->renderBossExplosion(gRenderer);

            if (SDL_GetTicks() - mainBoss->deadTime >= BOSS_EXP_DURATION)
            {
                is_target = true;
            }
        }

        // Check collsion box between main ship' bullet and boss
        vector<Bullet *> p_ship_bullet = gMainShip.getBulletList();
        for (int bullet_num = 0; bullet_num < p_ship_bullet.size(); bullet_num++)
        {
            if (checkCollision(mainBoss->getCollisionBox(), p_ship_bullet[bullet_num]->getCollisionBox()))
            {
                if (mainBoss->getReadyState() == true && mainBoss->getShieldState() == false)
                {
                    generateItem(itemList, 3, p_ship_bullet[bullet_num]->getX(), p_ship_bullet[bullet_num]->getY());
                }
                gMainShip.deleteShipBullet(bullet_num);

                if (mainBoss->getReadyState() == true)
                {
                    if (mainBoss->getShieldState() == true)
                    {
                        mainBoss->bossHealth.gainHealth();
                    }
                    else
                    {
                        mainBoss->bossHealth.loseHealth();
                        score += 3;
                    }
                }
                if (mainBoss->bossHealth.getHealthNum() == 0 && mainBoss->getDeadState() == false)
                {
                    mainBoss->setDeadState(true);
                    mainBoss->deadTime = SDL_GetTicks();
                    mainBoss->clearBossBulletList();
                    gMainShip.clearBulletList();
                    clearItemList(itemList);
                    bossExpSound.playSound(game_sfx);
                }
            }
        }
        // Check Collision between boss's bullet and main ship
        vector<BossBullet *> p_boss_bullet = mainBoss->getBulletList();
        for (int bullet_num = 0; bullet_num < p_boss_bullet.size(); bullet_num++)
        {
            if (checkCollision(gMainShip.getCollisionBox(), p_boss_bullet[bullet_num]->getCollisionBox()))
            {
                mainBoss->deleteBossBullet(bullet_num);
                if (gMainShip.getImmortalState() == false)
                {
                    if (gMainShip.health.getHealthNum() > 1)
                    {
                        mainExpSound[1].playSound(game_sfx);
                        gMainShip.health.loseHealth();
                        gMainShip.renderMainExplosion(gRenderer);

                        gMainShip.respawn(SCREEN_WIDTH, SCREEN_HEIGHT);
                    }
                    else
                    {
                        mainExpSound[1].playSound(game_sfx);
                        gMainShip.health.loseHealth();
                        gMainShip.renderMainExplosion(gRenderer);
                        music_off();
                        is_gameOver = true;
                    }
                }
            }
        }
        // Check collision box between main ship and boss
        if (checkCollision(gMainShip.getCollisionBox(), mainBoss->getCollisionBox()))
        {
            if (gMainShip.getImmortalState() == false)
            {
                if (gMainShip.health.getHealthNum() > 1)
                {
                    mainExpSound[0].playSound(game_sfx);
                    gMainShip.health.loseHealth();
                    gMainShip.renderMainExplosion(gRenderer);

                    gMainShip.respawn(SCREEN_WIDTH, SCREEN_HEIGHT);
                }
                else
                {
                    mainExpSound[0].playSound(game_sfx);
                    gMainShip.health.loseHealth();
                    gMainShip.renderMainExplosion(gRenderer);
                    music_off();
                    is_gameOver = true;
                }
            }
        }
        // Render Item
        for (int item_num = 0; item_num < itemList.size(); item_num++)
        {
            itemList[item_num]->move(SCREEN_HEIGHT + 10);
            if (itemList[item_num]->getMoveStatus() == false)
            {
                deleteItem(itemList, item_num);
            }
            itemList[item_num]->renderItem(gRenderer);
        }
        // Check collision with item
        for (int item_num = 0; item_num < itemList.size(); item_num++)
        {
            if (checkCollision(gMainShip.getCollisionBox(), itemList[item_num]->getCollisionBox()))
            {
                getItem(itemList[item_num]->getType(), score, game_sfx);
                deleteItem(itemList, item_num);
            }
        }

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    delete mainBoss;
    clearItemList(itemList);
    gMainShip.reset(SCREEN_WIDTH, SCREEN_HEIGHT);
    return -1;
}
int gameStage(const int &stage_number, int &score, const int &target, const int &total_threat, const int &numOfThreatMoveType, SDL_Event &e)
{
Play:
    bool is_target = false;
    int action = play(e, score, target, total_threat, numOfThreatMoveType, is_target);
    if (action == EXIT)
    {
        return EXIT;
    }
    else if (action == BACK)
    {
        music_off();
        // Reset to ready to play or replay
        resetShipStatus(score);
        return BACK;
    }
    else
    {
        save(score);
        if (is_target == true)
        {
            int successMenuAction = initSuccessMenu(e);
            if (successMenuAction == CONTINUE)
            {
                music_off();
                return CONTINUE;
            }
            else if (successMenuAction == BACK)
            {
                music_off();
                // Reset to ready to play or replay
                resetShipStatus(score);
                return BACK;
            }
            else if (successMenuAction == QUIT || successMenuAction == EXIT)
            {
                return QUIT;
            }
        }
        else
        {
            // Reset to ready to play or replay
            resetShipStatus(score);
            int gameoverMenuAction = initGameOverMenu(e);
            if (gameoverMenuAction == REPLAY)
            {
                music_off();
                goto Play;
            }
            else if (gameoverMenuAction == BACK)
            {
                music_off();
                return BACK;
            }
            else if (gameoverMenuAction == QUIT || gameoverMenuAction == EXIT)
            {
                return QUIT;
            }
        }
        return -1;
    }
}
int gameStageBoss(const int &stage_number, int &score, SDL_Event &e)
{
Play:
    bool is_target = false;
    int action = playBoss(e, score, is_target);
    if (action == EXIT)
    {
        return EXIT;
    }
    else if (action == BACK)
    {
        music_off();
        // Reset to ready to play or replay
        resetShipStatus(score);
        return BACK;
    }
    else
    {
        save(score);
        if (is_target == true)
        {
            int victoryMenuAction = initVictoryMenu(e);
            if (victoryMenuAction == BACK)
            {
                music_off();
                // Reset to ready to play or replay
                resetShipStatus(score);
                return BACK;
            }
            else if (victoryMenuAction == QUIT || victoryMenuAction == EXIT)
            {
                return QUIT;
            }
        }
        else
        {
            // Reset to ready to play or replay
            resetShipStatus(score);
            int gameoverMenuAction = initGameOverMenu(e);
            if (gameoverMenuAction == REPLAY)
            {
                music_off();
                goto Play;
            }
            else if (gameoverMenuAction == BACK)
            {
                music_off();
                return BACK;
            }
            else if (gameoverMenuAction == QUIT || gameoverMenuAction == EXIT)
            {
                return QUIT;
            }
        }
        return -1;
    }
}

void save(const int &score)
{
    int a[4];
    a[0] = score;
    ifstream scoreFile("save.txt");
    if (scoreFile.is_open())
    {
        int num = 1;
        while (!scoreFile.eof())
        {
            scoreFile >> a[num];
            num++;
        }
        sort(a, a + 4);
        reverse(a, a + 4);
        scoreFile.close();
        ofstream scoreFile("save.txt", ios::trunc);
        for (int num = 0; num < 3; num++)
        {
            scoreFile << a[num];
            scoreFile << endl;
        }
    }
    else
    {
        cout << "Error could not open save file!\n";
    }
}
#endif