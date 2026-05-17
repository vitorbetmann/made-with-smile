// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <raylib.h>
#include <SceneManager.h>

#include "GameOver.h"

#include "Constants.h"
#include "LevelMaker.h"
#include "Paddle.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Defines
// —————————————————————————————————————————————————————————————————————————————————————————————————


// —————————————————————————————————————————————————————————————————————————————————————————————————
// Data Types
// —————————————————————————————————————————————————————————————————————————————————————————————————


// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————


// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

constexpr char GAME_OVER_TEXT[] = "GAME OVER";
constexpr char FINAL_SCORE_TEXT[] = "Final Score:";
constexpr char CONTINUE_TEXT[] = "Press Enter to continue!";

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void GameOverUpdate(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        smSetScene("start", NULL);
    }
}

void GameOverDraw(void)
{
    Vector2 textSize = MeasureTextEx(gFont, GAME_OVER_TEXT, LARGE_FONT, 0);
    Vector2 textPos = {((float)VIRTUAL_WIDTH - textSize.x) / 2, (float)VIRTUAL_HEIGHT / 3};
    DrawTextEx(gFont, GAME_OVER_TEXT, textPos, LARGE_FONT, 0, WHITE);

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%s %04d", FINAL_SCORE_TEXT, gScore);
    textSize = MeasureTextEx(gFont, buffer, MEDIUM_FONT, 0);
    textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
    textPos.y = (float)VIRTUAL_HEIGHT / 2;
    DrawTextEx(gFont, buffer, textPos, MEDIUM_FONT, 0, WHITE);

    textSize = MeasureTextEx(gFont, CONTINUE_TEXT, MEDIUM_FONT, 0);
    textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
    textPos.y = (float)VIRTUAL_HEIGHT - (float)VIRTUAL_HEIGHT / 4;
    DrawTextEx(gFont, CONTINUE_TEXT, textPos, MEDIUM_FONT, 0, WHITE);
}

void GameOverExit(void)
{
    LevelUnload();
    PaddleReset();
    gHealth = MAX_HEALTH;
    gScore = 0;
}
