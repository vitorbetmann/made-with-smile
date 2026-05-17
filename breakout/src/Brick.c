// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>

#include "Brick.h"

#include "SoundDict.h"
#include "TextureDict.h"
#include "Util.h"

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

const int BRICK_WIDTH = 32;
const int BRICK_HEIGHT = 16;

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
    brick->inPlay = false;
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
