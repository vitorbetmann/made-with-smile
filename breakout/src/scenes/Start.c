// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>
#include <SceneManager.h>

#include "Start.h"
#include "PaddleSelect.h"
#include "HighScore.h"

#include "Settings.h"
#include "SoundDict.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static constexpr char GAME_TITLE[] = "BREAKOUT";
static constexpr char START_OPTION[] = "START";
static constexpr char HIGH_SCORES_OPTION[] = "HIGH SCORES";

static constexpr Color HIGHLIGHT = {103, 255, 255, 255};
static int highlighted;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void StartUpdate(float dt)
{
    if (IsKeyPressed(KEY_UP))
    {
        PlaySound(*sdFind(PADDLE_HIT));
        highlighted--;
        highlighted = highlighted < 0 ? 1 : highlighted;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        PlaySound(*sdFind(PADDLE_HIT));
        highlighted++;
        highlighted %= 2;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        switch (highlighted)
        {
        case 1:
            if (!smSceneExists("paddle select"))
            {
                smCreateScene("paddle select", PaddleSelectEnter, PaddleSelectUpdate,
                              PaddleSelectDraw, PaddleSelectExit);
            }
            smSetScene("paddle select", nullptr);
            break;
        case 2:
            if (!smSceneExists("high score"))
            {
                smCreateScene("high score", HighScoreEnter, HighScoreUpdate, HighScoreDraw,
                              HighScoreExit);
            }
            smSetScene("high score", nullptr);
            break;
        default:
            break;
        }
    }
}

void StartDraw(void)
{
    float spacing = (float)LARGE_FONT / 10;
    Vector2 textSize = MeasureTextEx(gFont, GAME_TITLE, (float)LARGE_FONT, spacing);
    float textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(gFont, GAME_TITLE, (Vector2){textX, (float)VIRTUAL_HEIGHT / 3},
               (float)LARGE_FONT, spacing, WHITE);

    Color currColor = highlighted == 0 ? HIGHLIGHT : WHITE;
    spacing = (float)MEDIUM_FONT / 10;
    textSize = MeasureTextEx(gFont, START_OPTION, (float)MEDIUM_FONT, spacing);
    textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(gFont, START_OPTION, (Vector2){textX, (float)VIRTUAL_HEIGHT / 2 + 70},
               (float)MEDIUM_FONT, spacing, currColor);

    currColor = highlighted == 1 ? HIGHLIGHT : WHITE;
    spacing = (float)MEDIUM_FONT / 10;
    textSize = MeasureTextEx(gFont, HIGH_SCORES_OPTION, (float)MEDIUM_FONT, spacing);
    textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(gFont, HIGH_SCORES_OPTION, (Vector2){textX, (float)VIRTUAL_HEIGHT / 2 + 90},
               (float)MEDIUM_FONT, spacing, currColor);
}

void StartExit(void)
{
    // TODO
}
