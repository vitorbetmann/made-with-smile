// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <math.h>

#include "Paddle.h"
#include "Settings.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

const int PADDLE_HEIGHT = 20;
const int PADDLE_WIDTH = 5;
const int PADDLE_SPEED = 200;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void paddleUp(Paddle *p, const float dt)
{
    p->y = fmax(p->y - PADDLE_SPEED * dt, 0);
}
void paddleDown(Paddle *p, const float dt)
{
    p->y = fmin(p->y + PADDLE_SPEED * dt, VIRTUAL_HEIGHT - PADDLE_HEIGHT);
}

void paddleAI(Paddle *p, float dt)
{
    if (ball.y + BALL_SIZE / 2 < p->y + PADDLE_HEIGHT / 2)
    {
        paddleUp(p, dt);
    }
    else
    {
        paddleDown(p, dt);
    }
}

void paddleDraw(const Paddle *p)
{
    DrawRectangle(p->x, p->y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
}

Rectangle paddleGetRect(const Paddle *p)
{
    return (Rectangle){p->x, p->y, PADDLE_WIDTH, PADDLE_HEIGHT};
}
