// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Util.h"

#include "Paddle.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static constexpr int PADDLES_ORIGIN_Y = 64;
static constexpr int PADDLE_SIZES = 4;
static constexpr int PADDLE_COLORS = 4;

static constexpr int PADDLE_ARRAY_SIZE = PADDLE_SIZES * PADDLE_COLORS;
static constexpr int BALL_ARRAY_SIZE = 7;
static constexpr int BRICK_ARRAY_SIZE = 21; // BRICK_COLORS(4) * BRICK_TIERS(5) + BRICK_SPECIAL(1)
static constexpr int HEART_ARRAY_SIZE = 2; // Full or empty

static Rectangle paddleQuads[PADDLE_ARRAY_SIZE];

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void GenPaddleQuads(void)
{
    Vector2 origin = {.x = 0, .y = PADDLES_ORIGIN_Y};
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
    return paddleQuads[1];
}

