// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "LevelMaker.h"

#include <math.h>
#include <stdlib.h>

#include "Ball.h"
#include "Brick.h"
#include "raylib.h"
#include "Constants.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static constexpr int ROWS_MIN = 1;
static constexpr int ROWS_MAX = 5;
static constexpr int COLS_MIN = 7;
static constexpr int COLS_MAX = 13;

static Brick **bricks;
static int rows, cols;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void LevelCreate(const int level)
{
    rows = GetRandomValue(ROWS_MIN, ROWS_MAX);
    cols = GetRandomValue(COLS_MIN, COLS_MAX);
    cols += cols % 2 == 0 ? 1 : 0; // Make it odd for simmetry

    const int highestTier = (int)fmin(3, (float)level / (float)TIER_THRESHOLD);
    const int highestColor = (int)fmin(4, level % 4 + 3);

    bricks = malloc(rows * cols * sizeof(Brick *));
    if (!bricks) { return; }

    const float startingX = (float)(VIRTUAL_WIDTH - cols * BRICK_WIDTH) / 2 - (float)BRICK_WIDTH;
    Vector2 origin = {startingX, (float)BRICK_HEIGHT};

    for (int i = 0; i < rows; i++)
    {
        // Whether to skip or alternate bricks for this row
        const bool skipPattern = GetRandomValue(0, 1) == 0;
        const bool alternatePattern = GetRandomValue(0, 1) == 0;

        // Choose 2 colors/tiers to alternate between
        const int color1 = GetRandomValue(0, highestColor);
        const int color2 = GetRandomValue(0, highestColor);
        const int tier1 = GetRandomValue(0, highestTier);
        const int tier2 = GetRandomValue(0, highestTier);

        // Flags to use when skipping/alternating a brick for the given pattern
        bool skipFlag = GetRandomValue(0, 1) == 0;
        bool alternateFlag = GetRandomValue(0, 1) == 0;

        // Color to use if not alternating
        const int solidColor = GetRandomValue(0, highestColor);
        const int solidTier = GetRandomValue(0, highestTier);

        for (int j = 0; j < cols; j++)
        {
            origin.x += (float)BRICK_WIDTH;

            skipFlag = !skipFlag;
            if (skipPattern && skipFlag)
            {
                bricks[i * cols + j] = nullptr;
                continue;
            }

            int tempColor, tempTier;
            alternateFlag = !alternateFlag;
            if (alternatePattern && alternateFlag)
            {
                tempColor = color1;
                tempTier = tier1;
            }
            else
            {
                tempColor = color2;
                tempTier = tier2;
            }

            if (!alternatePattern)
            {
                tempColor = solidColor;
                tempTier = solidTier;
            }

            // bricks[i * cols + j] = BrickInit(
            //     j * BRICK_WIDTH + 8 + (13 - cols) * BRICK_WIDTH / 2,
            //     i * BRICK_HEIGHT + 16);

            bricks[i * cols + j] = BrickInit(tempColor, tempTier, origin.x, origin.y);

        }
        origin.x = startingX;
        origin.y += (float)BRICK_HEIGHT;
    }
}

bool IsLevelActive(void)
{
    return bricks;
}

void LevelUpdate(const float dt)
{
    for (int i = 0; i < rows * cols; i++)
    {
        if (!bricks[i]) { continue; }
        BrickUpdate(bricks[i], dt);
    }
}

void LevelDraw(void)
{
    for (int i = 0; i < rows * cols; i++)
    {
        if (!bricks[i]) { continue; }
        BrickDraw(bricks[i]);
    }
}

void LevelDrawParticles(void)
{
    for (int i = 0; i < rows * cols; i++)
    {
        if (!bricks[i]) { continue; }

        BrickDrawParticles(bricks[i]);
    }
}

void LevelUnload(void)
{
    if (!IsLevelActive()) { return; }

    for (int i = 0; i < rows * cols; i++)
    {
        if (!bricks[i]) { continue; }

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
        if (!bricks[i]) { continue; }
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
