// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>
#include <ParticleSystem.h>

#include "Brick.h"

#include "SoundDict.h"
#include "TextureDict.h"
#include "Util.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

static void DrawParticle(const Particle *p, void *args);

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static constexpr int PARTICLES_TOTAL = 64;

typedef enum
{
    BRICK_BLUE,
    BRICK_GREEN,
    BRICK_RED,
    BRICK_PURPLE,
    BRICK_GOLD,
} BrickColor;

static const Color VALUE_BLUE = {99, 155, 255, 255};
static const Color VALUE_GREEN = {106, 190, 47, 255};
static const Color VALUE_RED = {217, 87, 99, 255};
static const Color VALUE_PURPLE = {215, 123, 186, 255};
static const Color VALUE_GOLD = {251, 242, 54, 255};

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

    b->ps = psCreate(PARTICLES_TOTAL, b->x + (float)BRICK_WIDTH / 2,
                     b->y + (float)BRICK_HEIGHT / 2);
    // Lasts between 0.5-1 seconds
    psSetLifetime(b->ps, 0.5f, 1.0f);
    // Give it an acceleration of anywhere between X1,Y1 and X2,Y2 (0, 0) and (80, 80) here
    // gives generally downward
    psSetAcceleration(b->ps, -15, 0, 15, 80);
    // Spread of particles; normal looks more natural than uniform, which is clumpy; numbers
    // are amount of standard deviation away in X and Y axis
    psSetEmissionShape(b->ps, PS_SHAPE_RECT);
    psSetSpread(b->ps, 0, 0, (float)BRICK_WIDTH, (float)BRICK_HEIGHT);

    return b;
}

void BrickHit(Brick *brick)
{
    switch (brick->color)
    {
    case BRICK_BLUE:
        brick->particleColor = VALUE_BLUE;
        break;
    case BRICK_GREEN:
        brick->particleColor = VALUE_GREEN;
        break;
    case BRICK_RED:
        brick->particleColor = VALUE_RED;
        break;
    case BRICK_PURPLE:
        brick->particleColor = VALUE_PURPLE;
        break;
    case BRICK_GOLD:
        brick->particleColor = VALUE_GOLD;
        break;
    }

    psBurst(brick->ps, PARTICLES_TOTAL);

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

void BrickUpdate(const Brick *brick, const float dt)
{
    psUpdate(brick->ps, dt);
}

void BrickDraw(const Brick *brick)
{
    if (!brick->inPlay) { return; }

    const Rectangle dest = BrickGetRect(brick);
    DrawTexturePro(*tdFind(MAIN), GetBrickQuad(brick), dest, (Vector2){0}, 0, WHITE);
}

void BrickDrawParticles(const Brick *brick)
{
    psForEach(brick->ps, DrawParticle, (void *)&brick->particleColor);
}

Rectangle BrickGetRect(const Brick *brick)
{
    return (Rectangle){(float)brick->x, (float)brick->y, (float)BRICK_WIDTH, (float)BRICK_HEIGHT};
}

void BrickUnload(Brick *brick)
{
    psDestroy(brick->ps);
    free(brick);
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Static
// —————————————————————————————————————————————————————————————————————————————————————————————————

void DrawParticle(const Particle *p, void *args)
{
    Color color = *(Color *)args;
    color.a = (unsigned char)((1.0f - p->age / p->lifetime) * 255);
    DrawTexture(*tdFind(PARTICLE), (int)p->x, (int)p->y, color);
}
