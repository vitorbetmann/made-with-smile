// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <SceneManager.h>
#include <stdio.h>

#include "Victory.h"

#include "Ball.h"
#include "Constants.h"
#include "LevelMaker.h"
#include "Paddle.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

constexpr char LEVEL_COMPLETE_TEXT[] = "Level %d Complete!";
constexpr char SERVE_TEXT[] = "Press Enter to serve!";

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void VictoryEnter(void *args)
{
    // TODO
}

void VictoryUpdate(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        smSetScene("serve", nullptr);
    }
}

void VictoryDraw(void)
{
    PaddleDraw();
    BallDraw();

    char buffer[32];
    snprintf(buffer, sizeof(buffer), LEVEL_COMPLETE_TEXT, gLevel);
    Vector2 textSize = MeasureTextEx(gFont, buffer, MEDIUM_FONT, 0);
    Vector2 textPos;
    textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
    textPos.y = (float)VIRTUAL_HEIGHT / 2;
    DrawTextEx(gFont, buffer, textPos, MEDIUM_FONT, 0, WHITE);

    textSize = MeasureTextEx(gFont, SERVE_TEXT, MEDIUM_FONT, 0);
    textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
    textPos.y = (float)VIRTUAL_HEIGHT - (float)VIRTUAL_HEIGHT / 4;
    DrawTextEx(gFont, SERVE_TEXT, textPos, MEDIUM_FONT, 0, WHITE);
}

void VictoryExit(void)
{
    gLevel++;
    gHealth = MAX_HEALTH;
    LevelUnload();
}
