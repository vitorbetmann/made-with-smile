// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Util.h"

#include "Ball.h"
#include "Paddle.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

// Atlas data
static constexpr int PADDLES_ORIGIN_X = 0;
static constexpr int PADDLES_ORIGIN_Y = 64;

static constexpr int BALLS_ORIGIN_X = 96;
static constexpr int BALLS_ORIGIN_Y = 48;
static constexpr int BALLS_AMOUNT_ROW_1 = 4;
static constexpr int BALLS_AMOUNT_ROW_2 = 3;

// Paddle data
static constexpr int PADDLE_SIZES = 4;
static constexpr int PADDLE_COLORS = 4;

// Quad arrays data
static constexpr int PADDLE_ARRAY_SIZE = PADDLE_SIZES * PADDLE_COLORS;
static constexpr int BALL_ARRAY_SIZE = 7;
static constexpr int HEART_ARRAY_SIZE = 2; // Full or empty
static constexpr int BRICK_ARRAY_SIZE = 21; // BRICK_COLORS(4) * BRICK_TIERS(5) + BRICK_SPECIAL(1)

// Quad arrays declaration
static Rectangle paddleQuads[PADDLE_ARRAY_SIZE];
static Rectangle ballQuads[BALL_ARRAY_SIZE];

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void GenPaddleQuads(void)
{
    Vector2 origin = {PADDLES_ORIGIN_X, PADDLES_ORIGIN_Y};
    int counter = 0;

    for (int i = 0; i < PADDLE_SIZES; i++)
    {
        Rectangle small = {0}, medium = {0}, large = {0}, huge = {0};

        // Small
        small.x = origin.x;
        small.y = origin.y;
        small.width = P_SMALL;
        small.height = P_HEIGHT;

        // Medium
        origin.x += P_SMALL;
        medium.x = origin.x;
        medium.y = origin.y;
        medium.width = P_MEDIUM;
        medium.height = P_HEIGHT;

        // Large
        origin.x += P_MEDIUM;
        large.x = origin.x;
        large.y = origin.y;
        large.width = P_LARGE;
        large.height = P_HEIGHT;

        // Huge
        origin.x = 0;
        origin.y += 16;
        huge.x = origin.x;
        huge.y = origin.y;
        huge.width = P_HUGE;
        huge.height = P_HEIGHT;

        // Add all to paddles array
        paddleQuads[counter++] = small;
        paddleQuads[counter++] = medium;
        paddleQuads[counter++] = large;
        paddleQuads[counter++] = huge;

        // Shift y for next iteration
        origin.y += 16;
    }
}

Rectangle GetPaddleQuad(void)
{
    return paddleQuads[paddle.size - 1 + 4 * (paddle.skin - 1)];
}

void GenBallQuads(void)
{
    Vector2 origin = {.x = BALLS_ORIGIN_X, .y = BALLS_ORIGIN_Y};

    for (int i = 0; i < BALLS_AMOUNT_ROW_1; i++)
    {
        Rectangle ballRect = {0};

        ballRect.x = origin.x;
        ballRect.y = origin.y;
        ballRect.width = (float)BALL_SIZE;
        ballRect.height = (float)BALL_SIZE;

        ballQuads[i] = ballRect;
        origin.x += (float)BALL_SIZE;
    }

    origin.x = BALLS_ORIGIN_X;
    origin.y = BALLS_ORIGIN_Y + BALL_SIZE;

    for (int i = 0; i < BALLS_AMOUNT_ROW_2; i++)
    {
        Rectangle ballRect;
        ballRect.x = origin.x;
        ballRect.y = origin.y;
        ballRect.width = (float)BALL_SIZE;
        ballRect.height = (float)BALL_SIZE;

        ballQuads[i + BALLS_AMOUNT_ROW_1] = ballRect;
        origin.x += (float)BALL_SIZE;
    }
}

Rectangle GetBallQuad(void)
{
    return ballQuads[ball.skin];
}
