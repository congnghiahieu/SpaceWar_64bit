#include <logic.h>

int main(int argc, char *args[])
{
    srand(time(0));
    // Start up SDL and create window
    if (!init("Space War"))
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Event handler
            SDL_Event e;

        StartMenu:

            int startMenuAction = initStartMenu(e);
            if (startMenuAction == EXIT)
            {
                goto Quit;
            }
            else if (startMenuAction == PLAY)
            {

                music_off();

                int score = 0;
                int gamePlayAction;

                gamePlayAction = gameStage(1, score, 20, 8, 2, e);
                if (gamePlayAction == EXIT || gamePlayAction == QUIT)
                {
                    goto Quit;
                }
                else if (gamePlayAction == BACK)
                {
                    goto StartMenu;
                }

                gamePlayAction = gameStage(2, score, 30, 12, 3, e);
                if (gamePlayAction == EXIT || gamePlayAction == QUIT)
                {
                    goto Quit;
                }
                else if (gamePlayAction == BACK)
                {
                    goto StartMenu;
                }

                gamePlayAction = gameStageBoss(3, score, e);
                if (gamePlayAction == EXIT || gamePlayAction == QUIT)
                {
                    goto Quit;
                }
                else if (gamePlayAction == BACK)
                {
                    goto StartMenu;
                }
            }
            else if (startMenuAction == OPTIONS)
            {
                int optionMenuAction = initOptionMenu(e);

                if (optionMenuAction == BACK)
                {
                    goto StartMenu;
                }
                else if (optionMenuAction == QUIT || optionMenuAction == EXIT)
                {
                    goto Quit;
                }
            }
            else if (startMenuAction == TUTORIAL)
            {
                int tutorialMenuAction = initTutorialMenu(e);

                if (tutorialMenuAction == BACK)
                {
                    goto StartMenu;
                }
                else if (tutorialMenuAction == QUIT || tutorialMenuAction == EXIT)
                {
                    goto Quit;
                }
            }
            else if (startMenuAction == LEADERBOARD)
            {
                int rankMenuAction = initRankMenu(e);

                if (rankMenuAction == BACK)
                {
                    goto StartMenu;
                }
                else if (rankMenuAction == QUIT || rankMenuAction == EXIT)
                {
                    goto Quit;
                }
            }
        }
    }
Quit:
    // Free resources and close SDL
    close();
    return 0;
}
