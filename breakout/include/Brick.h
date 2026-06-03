#pragma once

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>
#include <ParticleSystem.h>

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Defines
// —————————————————————————————————————————————————————————————————————————————————————————————————

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Data Types
// —————————————————————————————————————————————————————————————————————————————————————————————————

typedef struct
{
    int tier;
    int color;

    float x, y;

    bool inPlay;

    ParticleSystem *ps;
    Color particleColor;

    bool isSpecial;
} Brick;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

Brick *BrickInit(int color, int tier, float x, float y);
void BrickHit(Brick *brick);
void BrickUpdate(const Brick *brick, float dt);
void BrickDraw(const Brick *brick);
void BrickDrawParticles(const Brick *brick);
Rectangle BrickGetRect(const Brick *brick);
void BrickUnload(Brick *brick);
void UnlockSpecialBrick(void);

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

extern const int BRICK_WIDTH;
extern const int BRICK_HEIGHT;
