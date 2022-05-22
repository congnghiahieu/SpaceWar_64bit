#include <headers/basic.h>
bool init(string path)
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        gWindow = SDL_CreateWindow(path.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image PNG could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                // Initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }

                // Initialize mixer music and sound
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load BG
    if (!gBG.loadFromFile(gRenderer, "res/spacebg.png"))
    {
        printf("Failed to load space background!\n");
        success = false;
    }
    if (!gBGEarth.loadFromFile(gRenderer, "res/earthbg.png"))
    {
        printf("Failed to load earth background");
        success = false;
    }
    if (!gameOver.loadFromFile(gRenderer, "res/end.png"))
    {
        printf("Failed to load end background");
        success = false;
    }
    if (!spaceWar.loadFromFile(gRenderer, "res/title.png"))
    {
        printf("Failed to load title background \n");
        success = false;
    }
    if (!misson.loadFromFile(gRenderer, "res/misson.png"))
    {
        printf("Failed to load misson background!\n");
        success = false;
    }
    if (!victory.loadFromFile(gRenderer, "res/victory.png"))
    {
        printf("Failed to load victory background!\n");
        success = false;
    }
    if (!leader.loadFromFile(gRenderer, "res/leader.png"))
    {
        printf("Failed to load leader background!\n");
        success = false;
    }
    if (!instruction.loadFromFile(gRenderer, "res/instruction.png"))
    {
        printf("Failed to load instruction background! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    if (!setting.loadFromFile(gRenderer, "res/setting.png"))
    {
        printf("Failed to load setting text background! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    // Load start menu
    if (!startMenu.loadBG(gRenderer, "res/earthbg.png"))
    {
        success = false;
    }
    if (!startMenu.addButton(gRenderer, PLAY, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 300))
    {
        success = false;
    }
    if (!startMenu.addButton(gRenderer, TUTORIAL, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 425))
    {
        success = false;
    }
    if (!startMenu.addButton(gRenderer, OPTIONS, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 550))
    {
        success = false;
    }
    if (!startMenu.addButton(gRenderer, LEADERBOARD, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 675))
    {
        success = false;
    }
    if (!startMenu.addButton(gRenderer, EXIT, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 800))
    {
        success = false;
    }

    // Load tutorial menu
    if (!tutorialMenu.loadBG(gRenderer, "res/earthbg.png"))
    {
        success = false;
    }
    if (!tutorialMenu.addButton(gRenderer, BACK, 40, SCREEN_HEIGHT - BUTTON_HEIGHT - 40))
    {
        success = false;
    }
    // Load option menu
    if (!optionMenu.loadBG(gRenderer, "res/earthbg.png"))
    {
        success = false;
    }
    if (!optionMenu.addButton(gRenderer, BACK, 40, SCREEN_HEIGHT - BUTTON_HEIGHT - 40))
    {
        success = false;
    }
    if (!optionMenu.addButton(gRenderer, MUSIC, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 400))
    {
        success = false;
    }
    if (!optionMenu.addButton(gRenderer, SFX, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 600))
    {
        success = false;
    }

    // Load gameover menu
    if (!gameoverMenu.loadBG(gRenderer, "res/earthbg.png"))
    {
        success = false;
    }
    if (!gameoverMenu.addButton(gRenderer, REPLAY, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 400))
    {
        success = false;
    }
    if (!gameoverMenu.addButton(gRenderer, BACK, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 600))
    {
        success = false;
    }
    if (!gameoverMenu.addButton(gRenderer, QUIT, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 800))
    {
        success = false;
    }

    // Load success menu
    if (!successMenu.loadBG(gRenderer, "res/earthbg.png"))
    {
        success = false;
    }
    if (!successMenu.addButton(gRenderer, CONTINUE, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 350))
    {
        success = false;
    }
    if (!successMenu.addButton(gRenderer, BACK, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 525))
    {
        success = false;
    }
    if (!successMenu.addButton(gRenderer, QUIT, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 700))
    {
        success = false;
    }

    // Load victory menu
    if (!victoryMenu.loadBG(gRenderer, "res/earthbg.png"))
    {
        success = false;
    }
    if (!victoryMenu.addButton(gRenderer, BACK, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 400))
    {
        success = false;
    }
    if (!victoryMenu.addButton(gRenderer, QUIT, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 600))
    {
        success = false;
    }

    // load rank menu
    for (int i = 0; i < 3; i++)
    {
        if (!medal[i].loadFromFile(gRenderer, "res/medal_" + to_string(i + 1) + ".png"))
        {
            printf("Failed to load medal !\n");
            success = false;
        }
    }
    if (!rankMenu.loadBG(gRenderer, "res/earthbg.png"))
    {
        success = false;
    }
    if (!rankMenu.addButton(gRenderer, BACK, 40, SCREEN_HEIGHT - BUTTON_HEIGHT - 40))
    {
        success = false;
    }

    // Load pause menu
    if (!pause.loadFromFile(gRenderer, "res/pause.png"))
    {
        printf("Failed to load pause text background!\n");
        success = false;
    }
    if (!pauseMenu.loadBG(gRenderer, "res/earthbg.png"))
    {
        success = false;
    }
    if (!pauseMenu.addButton(gRenderer, RESUME, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 300))
    {
        success = false;
    }
    if (!pauseMenu.addButton(gRenderer, MUSIC, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 450))
    {
        success = false;
    }
    if (!pauseMenu.addButton(gRenderer, SFX, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 600))
    {
        success = false;
    }
    if (!pauseMenu.addButton(gRenderer, BACK, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 750))
    {
        success = false;
    }
    if (!pauseMenu.addButton(gRenderer, QUIT, (SCREEN_WIDTH - BUTTON_WIDTH) / 2, 900))
    {
        success = false;
    }

    // Load player's ship
    if (!gMainShip.loadFromFile(gRenderer, "res/thanos_spaceship.png"))
    {
        printf("Failed to load player's ship!\n");
        success = false;
    }
    else
    {
        if (!gMainShip.health.initHealth(gRenderer, DEFAULT_HEALTH))
        {
            printf("Failed to initialize player's health!\n");
            success = false;
        }
        if (!gMainShip.loadShipStuff(gRenderer))
        {
            printf("Failed to load ship stuff!\n SDL Error: %s\n", SDL_GetError());
            success = false;
        }
    }

    // Load text
    if ((!scoreText.loadFont("res/zag_bold.ttf", 30)) || (!scoreNum.loadFont("res/zag_regular.ttf", 30)))
    {
        printf("Failed to load TTF Font! SDL Error %s\n", TTF_GetError());
        success = false;
    }
    else
    {
        if ((!scoreText.loadText(gRenderer, "SCORE", GOLD_COLOR)) || (!scoreNum.loadText(gRenderer, " ", WHITE_COLOR)))
        {
            printf("Failed to load Text!\n");
            success = false;
        }
    }
    for (int num = 0; num < 3; num++)
    {
        if (!scoreData[num].loadFont("res/oswald.ttf", 120))
        {
            printf("Failed to load TTF Font! SDL Error: %s\n", TTF_GetError());
            success = false;
        }
        else
        {
            if (!scoreData[num].loadText(gRenderer, "-1", GOLD_COLOR))
            {
                printf("Failed to load Text!\n");
                success = false;
            }
        }
    }
    for (int num = 0; num < 3; num++)
    {
        if (!tutorial[num].loadFont("res/oswald.ttf", 80))
        {
            printf("Failed to load TTF Font! SDL Error: %s\n", TTF_GetError());
            success = false;
        }
    }
    tutorial[0].loadText(gRenderer, "PRESS W,A,S,D: MOVE", WHITE_COLOR);
    tutorial[1].loadText(gRenderer, "PRESS J: SHOOT", WHITE_COLOR);
    tutorial[2].loadText(gRenderer, "PRESS U: SPECIAL SKILL", WHITE_COLOR);
    if ((!targetText.loadFont("res/zag_bold.ttf", 30)) || (!targetNum.loadFont("res/zag_regular.ttf", 30)))
    {
        printf("Failed to load TTF Font! SDL Error %s\n", TTF_GetError());
        success = false;
    }
    else
    {
        if ((!targetText.loadText(gRenderer, "TARGET", GOLD_COLOR)) || (!targetNum.loadText(gRenderer, "1", WHITE_COLOR)))
        {
            printf("Failed to load Text!\n");
            success = false;
        }
    }

    // Load music
    // Load game over music
    for (int num = 0; num < TOTAL_GAMEOVER_MUSIC; num++)
    {
        string path = "res/gameover_" + to_string(num + 1) + ".wav";
        if (!gameOverMusic[num].loadMusic(path))
        {
            printf("Failed to load game over music %d !\n", num + 1);
            success = false;
        }
    }

    // Load theme music
    for (int num = 0; num < TOTAL_THEME_MUSIC; num++)
    {
        string path = "res/theme_" + to_string(num + 1) + ".wav";
        if (!themeMusic[num].loadMusic(path))
        {
            printf("Failed to load theme music %d !\n", num + 1);
            success = false;
        }
    }

    // Load misson music
    for (int num = 0; num < TOTAL_MISSON_MUSIC; num++)
    {
        string path = "res/misson_" + to_string(num + 1) + ".wav";
        if (!missonMusic[num].loadMusic(path))
        {
            printf("Failed to load misson music %d !\n", num + 1);
            success = false;
        }
    }

    // Load victory music
    for (int num = 0; num < TOTAL_VICTORY_MUSIC; num++)
    {
        string path = "res/victory_" + to_string(num + 1) + ".wav";
        if (!victoryMusic[num].loadMusic(path))
        {
            printf("Failed to load victory music %d !\n", num + 1);
            success = false;
        }
    }

    // Load success music
    for (int num = 0; num < TOTAL_SUCCESS_MUSIC; num++)
    {
        string path = "res/success_" + to_string(num + 1) + ".wav";
        if (!successMusic[num].loadMusic(path))
        {
            printf("Failed to load success music %d !\n", num + 1);
            success = false;
        }
    }

    // Load boss music
    for (int num = 0; num < TOTAL_BOSS_MUSIC; num++)
    {
        string path = "res/boss_" + to_string(num + 1) + ".wav";
        if (!bossMusic[num].loadMusic(path))
        {
            printf("Failed to load boss music %d !\n", num + 1);
            success = false;
        }
    }

    // Load main ship explosion sound
    if (!mainExpSound[0].loadSound("res/main_exp.wav"))
    {
        printf("Failed to load main ship explosion sound!\n");
        success = false;
    }
    if (!mainExpSound[1].loadSound("res/main_exp_2.wav"))
    {
        printf("Failed to load main ship explosion sound!\n");
        success = false;
    }
    // Load threat explosion sound
    if (!threatExpSound.loadSound("res/threat_exp.wav"))
    {
        printf("Failed to load threat explosion sound!\n");
        success = false;
    }
    // Load boss explosion sound
    if (!bossExpSound.loadSound("res/boss_exp.wav"))
    {
        printf("Failed to load boss explosion sound! SDL Error: %s\n", Mix_GetError());
        success = false;
    }
    // Load shooting sounds
    if (!shootSound[LEFT_SHOOT].loadSound("res/shot_1.wav"))
    {
        printf("Failed to load left shooting sound!\n");
        success = false;
    }
    if (!shootSound[RIGHT_SHOOT].loadSound("res/shot_2.wav"))
    {
        printf("Failed to load right shooting sound!\n");
        success = false;
    }
    if (!item.loadSound("res/item.wav"))
    {
        printf("Failed to load item sound!\n SDL_Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}

void close()
{
    // Free loaded images
    gMainShip.free();
    gBG.free();
    gBGEarth.free();
    gameOver.free();
    spaceWar.free();
    misson.free();
    victory.free();
    leader.free();
    instruction.free();
    pause.free();
    setting.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void playMissionMusic()
{
    int random = rand() % TOTAL_MISSON_MUSIC + 0;
    missonMusic[random].playMusic(NO_LOOP);
}

void playGameOverMusic()
{
    int random = rand() % TOTAL_GAMEOVER_MUSIC + 0;
    gameOverMusic[random].playMusic(NO_LOOP);
}

void playThemeMusic()
{
    int random = rand() % TOTAL_THEME_MUSIC + 0;
    themeMusic[random].playMusic(NO_LOOP);
}

void playVictoryMusic()
{
    int random = rand() % TOTAL_VICTORY_MUSIC + 0;
    victoryMusic[random].playMusic(NO_LOOP);
}

void playSuccessMusic()
{
    int random = rand() % TOTAL_SUCCESS_MUSIC + 0;
    successMusic[random].playMusic(NO_LOOP);
}

void playBossMusic()
{
    int random = rand() % TOTAL_BOSS_MUSIC + 0;
    bossMusic[random].playMusic(NO_LOOP);
}

void music_off()
{
    // Check if there is music playing
    if (Mix_PlayingMusic() == 1)
    {
        Mix_HaltMusic();
    }
}

void music_pause()
{
    // Check if there is music playing and not paused yet
    if (Mix_PlayingMusic() == 1 && Mix_PausedMusic() == 0)
    {
        Mix_PauseMusic();
    }
}

void music_resume()
{
    // Check if there is music playing and paused
    if (Mix_PlayingMusic() == 1 && Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
    }
}

// Handle menu
int initStartMenu(SDL_Event &e)
{
    int menu_action;

    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            menu_action = startMenu.handleEvent(e);
            if (menu_action != -1)
            {
                return menu_action;
            }
        }

        if (game_music == true)
        {
            playThemeMusic();
        }
        else
        {
            music_off();
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render menu
        startMenu.render(gRenderer);
        spaceWar.render(gRenderer, (SCREEN_WIDTH - spaceWar.getWidth()) / 2, 100);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}

int initTutorialMenu(SDL_Event &e)
{
    int menu_action;

    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            menu_action = tutorialMenu.handleEvent(e);
            if (menu_action != -1)
            {
                return menu_action;
            }
        }

        if (game_music == true)
        {
            playThemeMusic();
        }
        else
        {
            music_off();
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render menu
        tutorialMenu.render(gRenderer);
        instruction.render(gRenderer, (SCREEN_WIDTH - instruction.getWidth()) / 2, 50);
        tutorial[0].render(gRenderer, 400, 250);
        tutorial[1].render(gRenderer, 400, 440);
        tutorial[2].render(gRenderer, 400, 630);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}
int initOptionMenu(SDL_Event &e)
{
    int menu_action;

    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            menu_action = optionMenu.handleEvent(e);
            if (menu_action == MUSIC)
            {
                if (game_music == true)
                {
                    game_music = false;
                }
                else
                {
                    game_music = true;
                }
            }
            else if (menu_action == SFX)
            {
                if (game_sfx == true)
                {
                    game_sfx = false;
                }
                else
                {
                    game_sfx = false;
                }
            }
            else if (menu_action == BACK)
            {
                return BACK;
            }
        }

        if (game_music == true)
        {
            playThemeMusic();
        }
        else
        {
            music_off();
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render menu
        optionMenu.render(gRenderer);
        setting.render(gRenderer, (SCREEN_WIDTH - setting.getWidth()) / 2, 50);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}

int initGameOverMenu(SDL_Event &e)
{
    int menu_action;
    music_off();
    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            menu_action = gameoverMenu.handleEvent(e);
            if (menu_action != -1)
            {
                return menu_action;
            }
        }

        if (game_music == true)
        {
            playGameOverMusic();
        }
        else
        {
            music_off();
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render menu
        gameoverMenu.render(gRenderer);
        gameOver.render(gRenderer, (SCREEN_WIDTH - gameOver.getWidth()) / 2, 100);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}

int initSuccessMenu(SDL_Event &e)
{
    int menu_action;
    music_off();
    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            menu_action = successMenu.handleEvent(e);
            if (menu_action != -1)
            {
                return menu_action;
            }
        }

        if (game_music == true)
        {
            playSuccessMusic();
        }
        else
        {
            music_off();
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render menu
        successMenu.render(gRenderer);
        misson.render(gRenderer, (SCREEN_WIDTH - misson.getWidth()) / 2, 50);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}

int initVictoryMenu(SDL_Event &e)
{
    int menu_action;
    music_off();
    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            menu_action = victoryMenu.handleEvent(e);
            if (menu_action != -1)
            {
                return menu_action;
            }
        }

        if (game_music == true)
        {
            playVictoryMusic();
        }
        else
        {
            music_off();
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render menu
        victoryMenu.render(gRenderer);
        victory.render(gRenderer, (SCREEN_WIDTH - victory.getWidth()) / 2, 100);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}

int initRankMenu(SDL_Event &e)
{
    // Load score data
    ifstream scoreFile("save.txt");
    int array[3];
    for (int num = 0; num < 3; num++)
    {
        scoreFile >> array[num];
        scoreData[num].loadText(gRenderer, to_string(array[num]), WHITE_COLOR);
    }

    int menu_action;

    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            menu_action = rankMenu.handleEvent(e);
            if (menu_action != -1)
            {
                return menu_action;
            }
        }

        if (game_music == true)
        {
            playThemeMusic();
        }
        else
        {
            music_off();
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render menu
        rankMenu.render(gRenderer);
        leader.render(gRenderer, (SCREEN_WIDTH - leader.getWidth()) / 2, 50);
        for (int num = 0; num < 3; num++)
        {
            medal[num].render(gRenderer, 500, num * 300 + 150);
            scoreData[num].render(gRenderer, (SCREEN_WIDTH - scoreData[num].getWidth()) / 2, num * 300 + 165);
        }

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}

int initPauseMenu(SDL_Event &e)
{
    int menu_action;
    music_pause();
    while (true)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return EXIT;
            }
            menu_action = pauseMenu.handleEvent(e);
            if (menu_action == MUSIC)
            {
                if (game_music == true)
                {
                    game_music = false;
                }
                else
                {
                    game_music = true;
                }
            }
            else if (menu_action == SFX)
            {
                if (game_sfx == true)
                {
                    game_sfx = false;
                }
                else
                {
                    game_sfx = true;
                }
            }
            else if (menu_action != -1)
            {
                if (game_music == true)
                {
                    music_resume();
                }
                return menu_action;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render menu
        pauseMenu.render(gRenderer);
        pause.render(gRenderer, (SCREEN_WIDTH - pause.getWidth()) / 2, 50);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }
}