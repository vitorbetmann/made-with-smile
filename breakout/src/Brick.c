// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>

#include "Brick.h"

#include "SoundDict.h"
#include "TextureDict.h"
#include "Util.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

Brick *BrickInit(const int color, const int tier, const float x, const float y)
{
    Brick *b = malloc(sizeof(Brick));
    if (!b) { return nullptr; }

    b->color = color;
    b->tier = tier;

    b->x = x;
    b->y = y;

    b->inPlay = true;

    return b;
}

void BrickHit(Brick *brick)
{
    PlaySound(*sdFind(BRICK_HIT_2));
    PlaySound(*sdFind(BRICK_HIT_2));

    if (brick->tier > 0)
    {
        if (brick->color == 0)
        {
            brick->tier -= 1;
            brick->color = COLOR_THRESHOLD;
        }
        else
        {
            brick->color -= 1;
        }
    }
    else
    {
        if (brick->color == 0)
        {
            brick->inPlay = false;
            PlaySound(*sdFind(BRICK_HIT_1));
            PlaySound(*sdFind(BRICK_HIT_1));
        }
        else
        {
            brick->color -= 1;
        }
    }
}

void BrickDraw(const Brick *brick)
{
    if (!brick->inPlay) { return; }

    const Rectangle dest = BrickGetRect(brick);
    DrawTexturePro(*tdFind(MAIN), GetBrickQuad(brick), dest, (Vector2){0}, 0, WHITE);
}

Rectangle BrickGetRect(const Brick *brick)
{
    return (Rectangle){(float)brick->x, (float)brick->y, (float)BRICK_WIDTH, (float)BRICK_HEIGHT};
}

void BrickUnload(Brick *brick)
{
    free(brick);
}
