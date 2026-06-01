// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <SceneManager.h>

#include "GameOver.h"

#include "Constants.h"
#include "EnterHighScore.h"
#include "HighScore.h"
#include "LevelMaker.h"
#include "Paddle.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

constexpr char GAME_OVER_TEXT[] = "GAME OVER";
constexpr char FINAL_SCORE_TEXT[] = "Final Score:";
constexpr char CONTINUE_TEXT[] = "Press Enter to continue!";

static int scoreIndex;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void GameOverUpdate(float dt)
{
    if (!IsKeyPressed(KEY_ENTER)) { return; }

    bool highScore = false;
    scoreIndex = 10;

    for (int i = 9; i >= 0; i--)
    {
        void *endptr = nullptr;
        const int currHighScore = (int)strtol(gHighScores[i].score, endptr, 10);
        if (gScore <= currHighScore)
            break;
        scoreIndex--;
        highScore = true;
    }

    if (highScore)
    {
        if (!smSceneExists("enter high score"))
        {
            smAddScene("enter high score", EnterHighScoreEnter, EnterHighScoreUpdate,
                       EnterHighScoreDraw, EnterHighScoreExit);
        }
        smSetScene("enter high score", &(GameOverData){scoreIndex});
        return;
    }

    smSetScene("start", nullptr);
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
}
