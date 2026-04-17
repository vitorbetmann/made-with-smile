// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <raylib.h>
#include <SceneManager.h>

#include "GameOver.h"
#include "Start.h"
#include "Settings.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static Player winner;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void GameOverEnter(void *args)
{
    GameOverData *d = args;
    winner = d->winner;
}

void GameOverUpdate(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        smSetScene("start", &(StartData){winner});
    }
}

void GameOverDraw(void)
{
    char txt[32];
    snprintf(txt, 32, "Player %d wins!", winner.id);
    Vector2 txtSize = MeasureTextEx(font, txt, FONTLARGE, FONTLARGE / FONTRAYLIB);
    Vector2 txtPos = {(VIRTUAL_WIDTH - txtSize.x) / 2, 20};
    DrawTextEx(font, txt, txtPos, FONTLARGE, FONTLARGE / FONTRAYLIB, WHITE);

    snprintf(txt, 32, "Press ENTER to to play again!");
    txtSize = MeasureTextEx(font, txt, FONTSMALL, FONTSMALL / FONTRAYLIB);
    txtPos.x = (VIRTUAL_WIDTH - txtSize.x) / 2;
    txtPos.y = 60;
    DrawTextEx(font, txt, txtPos, FONTSMALL, FONTSMALL / FONTRAYLIB, WHITE);
}
