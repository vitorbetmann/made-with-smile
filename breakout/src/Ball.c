// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Ball.h"

#include "Constants.h"
#include "Paddle.h"
#include "SoundDict.h"
#include "TextureDict.h"
#include "Util.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

Ball balls[3];
const int BALL_SIZE = 8;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void BallInit(Ball *b, const int skin)
{
    BallReset(b);
    b->skin = skin;
}

void BallUpdate(Ball *b, const float dt)
{
    b->x += b->dx * dt;
    b->y += b->dy * dt;

    if (b->x <= 0)
    {
        b->x = 0;
        b->dx *= -1;
        PlaySound(*sdFind(WALL_HIT));
    }

    if (b->x >= (float)VIRTUAL_WIDTH - 8)
    {
        b->x = (float)VIRTUAL_WIDTH - 8;
        b->dx *= -1;
        PlaySound(*sdFind(WALL_HIT));
    }

    if (b->y <= 0)
    {
        b->y = 0;
        b->dy *= -1;
        PlaySound(*sdFind(WALL_HIT));
    }
}

void BallDraw(const Ball *b)
{
    const Rectangle dest = {b->x, b->y, (float)BALL_SIZE, (float)BALL_SIZE};
    DrawTexturePro(*tdFind(MAIN), GetBallRect(b), dest, (Vector2){0}, 0, WHITE);
}

void BallReset(Ball *b)
{
    b->x = paddle.x + (float)(paddle.width - BALL_SIZE) / 2;
    b->y = paddle.y - (float)BALL_SIZE;

    b->dx = (float)GetRandomValue(-200, 200);
    b->dy = (float)GetRandomValue(-60, -50);
}

Rectangle BallGetRect(const Ball *b)
{
    return (Rectangle){b->x, b->y, (float)BALL_SIZE, (float)BALL_SIZE};
}
