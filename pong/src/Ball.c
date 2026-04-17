// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Ball.h"
#include "Settings.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

const int BALL_SIZE = 4;
const int BALL_SPEED_X = 100;
const int BALL_SPEED_Y = 50;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void ballReset(Player server)
{
    ball.x = VIRTUAL_WIDTH / 2 - 2;
    ball.y = VIRTUAL_HEIGHT / 2 - 2;

    switch (server.id)
    {
    case 1:
        ball.dx = BALL_SPEED_X;
        break;
    case 2:
        ball.dx = -BALL_SPEED_X;
        break;
    default:
        ball.dx = GetRandomValue(0, 1) == 0 ? BALL_SPEED_X : -BALL_SPEED_X;
    }
    ball.dy = GetRandomValue(-50, 50);
}

void ballUpdate(const float dt)
{
    ball.x += ball.dx * dt;
    ball.y += ball.dy * dt;
}

void ballDraw(void)
{
    DrawRectangle(ball.x, ball.y, BALL_SIZE, BALL_SIZE, WHITE);
}

Rectangle ballGetRect(void)
{
    return (Rectangle){ball.x, ball.y, BALL_SIZE, BALL_SIZE};
}