// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "LevelMaker.h"

#include <stdlib.h>

#include "Ball.h"
#include "Brick.h"
#include "raylib.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static Brick **bricks;
static int rows, cols;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void LevelCreate(void)
{
    rows = GetRandomValue(1, 5);
    cols = GetRandomValue(7, 13);


    bricks = malloc(rows * cols * sizeof(Brick *));
    if (!bricks) { return; }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            bricks[i * cols + j] = BrickInit(
                j * BRICK_WIDTH + 8 + (13 - cols) * BRICK_WIDTH / 2,
                i * BRICK_HEIGHT + 16);
        }
    }
}

bool IsLevelActive(void)
{
    return bricks;
}

void LevelDraw(void)
{
    for (int i = 0; i < rows * cols; i++)
    {
        BrickDraw(bricks[i]);
    }
}

void LevelUnload(void)
{
    if (!IsLevelActive()) { return; }
    
    for (int i = 0; i < rows * cols; i++)
    {
        BrickUnload(bricks[i]);
        bricks[i] = nullptr;
    }
    free(bricks);
    bricks = nullptr;
}

Brick *LevelCheckBrickCollision(void)
{
    for (int i = 0; i < rows * cols; i++)
    {
        if (!bricks[i]->inPlay) { continue; }
        if (CheckCollisionRecs(BallGetRect(), BrickGetRect(bricks[i])))
        {
            BrickHit(bricks[i]);
            // Only allow colliding with one brick, for corners
            return bricks[i];
        }
    }
    return nullptr;
}
