// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <raylib.h>
#include <SceneManager.h>

#include "Settings.h"

#include "Serve.h"
#include "Play.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static int server;

// —————————————————————————————————————————————————————————————————————————————————————————————————

// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void ServeEnter(void *args)
{
    ServeData *d = args ? args : nullptr;
    if (d)
    {
        ballReset(d->server);
    }
    server = ball.dx > 0 ? 1 : 2;
}

void ServeUpdate(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        if (!smSceneExists("play"))
        {
            smCreateScene("play", nullptr, PlayUpdate, nullptr, PlayExit);
        }

        smSetScene("play", nullptr);
    }
}

void ServeDraw(void)
{
    char txt[32];
    snprintf(txt, 32, "Player %d's serve!", server);
    Vector2 txtSize = MeasureTextEx(font, txt, 12, 1.2f);
    Vector2 txtPos = {(VIRTUAL_WIDTH - txtSize.x) / 2, 20};
    DrawTextEx(font, txt, txtPos, 12, 1.2f, WHITE);

    snprintf(txt, 32, "Press ENTER to serve!");
    txtSize = MeasureTextEx(font, txt, 12, 1.2f);
    txtPos.x = (VIRTUAL_WIDTH - txtSize.x) / 2;
    txtPos.y = 40;
    DrawTextEx(font, txt, txtPos, 12, 1.2f, WHITE);
}
