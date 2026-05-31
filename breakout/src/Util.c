// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <string.h>

#include "Util.h"

#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

// Paddle data
static constexpr int PADDLES_ORIGIN_X = 0;
static constexpr int PADDLES_ORIGIN_Y = 64;

static constexpr int PADDLE_SIZES = 4;
static constexpr int PADDLE_COLORS = 4;

// Ball data
static constexpr int BALLS_ORIGIN_X = 96;
static constexpr int BALLS_ORIGIN_Y = 48;

static constexpr int BALLS_IN_ROW_1 = 4;
static constexpr int BALLS_IN_ROW_2 = 3;

// Brick data
static constexpr int BRICK_COLORS = 4;
static constexpr int BRICK_TIERS = 5;
static constexpr int BRICK_SPECIAL = 1;

static constexpr int BRICK_ROWS = 4;
static constexpr int BRICK_COLS = 6;

// Quad arrays data
static constexpr int PADDLE_ARRAY_SIZE = PADDLE_SIZES * PADDLE_COLORS;
static constexpr int BALL_ARRAY_SIZE = BALLS_IN_ROW_1 + BALLS_IN_ROW_2;
static constexpr int BRICK_ARRAY_SIZE = BRICK_COLORS * BRICK_TIERS + BRICK_SPECIAL;
static constexpr int HEART_ARRAY_SIZE = 2; // Full or empty

// Quad arrays declaration
static Rectangle paddleQuads[PADDLE_ARRAY_SIZE];
static Rectangle ballQuads[BALL_ARRAY_SIZE];
static Rectangle brickQuads[BRICK_ARRAY_SIZE];
static Rectangle heartQuads[HEART_ARRAY_SIZE];

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

    for (int i = 0; i < BALLS_IN_ROW_1; i++)
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
    origin.y = (float)(BALLS_ORIGIN_Y + BALL_SIZE);

    for (int i = 0; i < BALLS_IN_ROW_2; i++)
    {
        Rectangle ballRect;
        ballRect.x = origin.x;
        ballRect.y = origin.y;
        ballRect.width = (float)BALL_SIZE;
        ballRect.height = (float)BALL_SIZE;

        ballQuads[i + BALLS_IN_ROW_1] = ballRect;
        origin.x += (float)BALL_SIZE;
    }
}

Rectangle GetBallQuad(void)
{
    return ballQuads[ball.skin];
}

void GenBrickQuads(void)
{
    int counter = 0, skin = 0;
    Vector2 origin = {0, 0};
    for (int i = 0; i < BRICK_ROWS; i++)
    {
        for (int j = 0; j < BRICK_COLS; j++)
        {
            Rectangle brick;
            brick.x = origin.x;
            brick.y = origin.y;
            brick.width = (float)BRICK_WIDTH;
            brick.height = (float)BRICK_HEIGHT;

            brickQuads[counter] = brick;

            counter++;
            if (counter == BRICK_ARRAY_SIZE) { break; }

            skin++;
            skin %= BRICK_TIERS;
            origin.x += (float)BRICK_WIDTH;
        }
        origin.y += (float)BRICK_HEIGHT;
    }
}

Rectangle GetBrickQuad(const Brick *brick)
{
    return brickQuads[brick->color * BRICK_COLORS + brick->tier];
}

void GenHeartsQuads(void)
{
    Vector2 origin = {0};
    for (int i = 0; i < 2; i++)
    {
        Rectangle heart;
        heart.x = origin.x;
        heart.y = origin.y;
        heart.width = (float)HEART_WIDTH;
        heart.height = (float)HEART_HEIGHT;
        heartQuads[i] = heart;

        origin.x += (float)HEART_WIDTH;
    }
}

Rectangle GetHeartRect(const HeartStatus status)
{
    return heartQuads[status];
}

void LoadHighScores(void)
{
    FILE *file = fopen(SAVE_FILE, "r");
    char c;
    int i = 0, len = 0, line = 0;;
    char buf[32];
    while (fread(&c, sizeof(char), 1, file))
    {
        buf[len++] = c;
        if (c == '\n')
        {
            buf[len - 1] = '\0';
            if (line % 2 == 0)
            {
                strcpy(gHighScores[i].name, buf);
            }
            else
            {
                strcpy(gHighScores[i].score, buf);
            }
            buf[0] = '\0';
            len = 0;
            line++;
            i = line / 2;
        }
    }
    fclose(file);
}
