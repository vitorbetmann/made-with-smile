// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>
#include <SceneManager.h>

#include "PaddleSelect.h"

#include "Paddle.h"
#include "Serve.h"
#include "SoundDict.h"
#include "TextureDict.h"
#include "Util.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static constexpr char PADDLE_SELECT_TEXT[] = "Select your paddle with left and right";
static constexpr char CONFIRM_TEXT[] = "Press Enter to Continue";

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void PaddleSelectEnter(void *args)
{
    PaddleInit();
}

void PaddleSelectUpdate(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        if (!smSceneExists("serve"))
        {
            smAddScene("serve", ServeEnter, ServeUpdate, ServeDraw, nullptr);
        }
        smSetScene("serve", nullptr);
        return;
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        if (paddle.skin == 4)
        {
            PlaySound(*sdFind(NO_SELECT));
        }
        else
        {
            paddle.skin++;
            PlaySound(*sdFind(SELECT));
        }
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        if (paddle.skin == 1)
        {
            PlaySound(*sdFind(NO_SELECT));
        }
        else
        {
            paddle.skin--;
            PlaySound(*sdFind(SELECT));
        }
    }
}

void PaddleSelectDraw(void)
{
    Vector2 textSize = MeasureTextEx(gFont, PADDLE_SELECT_TEXT, MEDIUM_FONT, 0);
    Vector2 textPos = {((float)VIRTUAL_WIDTH - textSize.x) / 2, (float)VIRTUAL_HEIGHT / 4};
    DrawTextEx(gFont, PADDLE_SELECT_TEXT, textPos, MEDIUM_FONT, 0, WHITE);

    textSize = MeasureTextEx(gFont, CONFIRM_TEXT, SMALL_FONT, 0);
    textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
    textPos.y = (float)VIRTUAL_HEIGHT / 3;
    DrawTextEx(gFont, CONFIRM_TEXT, textPos, SMALL_FONT, 0, WHITE);

    constexpr Vector2 origin = {0};
    Color color = WHITE;

    if (paddle.skin == 1) { color = GRAY; }
    Rectangle source = GetArrowRect(ARROW_LEFT);
    Rectangle dest = {(float)VIRTUAL_WIDTH / 4 - 24, (float)VIRTUAL_HEIGHT - 36, source.width,
                      source.height};
    DrawTexturePro(*tdFind(ARROWS), source, dest, origin, 0.0f, color);
    color = WHITE;

    if (paddle.skin == 4) { color = GRAY; }
    source = GetArrowRect(ARROW_RIGHT);
    dest.x = (float)VIRTUAL_WIDTH * 3 / 4;
    DrawTexturePro(*tdFind(ARROWS), source, dest, origin, 0.0f, color);

    PaddleDraw();
}
