// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <math.h>
#include <raylib.h>
#include <SceneManager.h>

#include "Play.h"

#include "Ball.h"
#include "Dependencies.h"
#include "GameOver.h"
#include "LevelMaker.h"
#include "Log.h"
#include "Paddle.h"
#include "Victory.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static bool isPaused;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void PlayUpdate(const float dt)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        isPaused = !isPaused;
        PlaySound(*sdFind(PAUSE));
    }

    if (isPaused) { return; }

    PaddleUpdate(dt);
    BallUpdate(dt);

    if (CheckCollisionRecs(BallGetRect(), PaddleGetRect()))
    {
        ball.y = paddle.y - (float)BALL_SIZE;
        ball.dy *= -1;

        const bool isPaddleMovingLeft = paddle.dx < 0;
        const bool isPaddleMovingRight = paddle.dx > 0;
        const float paddleCenter = paddle.x + (float)paddle.width / 2;
        const float ballOffset = fabsf(ball.x - paddleCenter);

        if (ball.x < paddleCenter && isPaddleMovingLeft)
        {
            ball.dx = (float)-STARTING_BOUNCE_DX - (float)BOUNCE_ANGLE_MULTIPLIER * ballOffset;
        }
        else if (ball.x > paddleCenter && isPaddleMovingRight)
        {
            ball.dx = (float)STARTING_BOUNCE_DX + (float)BOUNCE_ANGLE_MULTIPLIER * ballOffset;
        }

        PlaySound(*sdFind(PADDLE_HIT));
    }

    Brick *colBrick = LevelCheckBrickCollision();
    if (colBrick)
    {
        gScore += colBrick->tier * SCORE_TIER + colBrick->color * SCORE_COLOR;
        BrickHit(colBrick);

        // Check game over
        if (!colBrick->inPlay && --gBricksActive == 0)
        {
            if (!smSceneExists("victory"))
            {
                smAddScene("victory", VictoryEnter, VictoryUpdate, VictoryDraw, VictoryExit);
            }
            smSetScene("victory", nullptr);
            return;
        }

        // Centers of X and Y of brick
        const float centerBrickX = colBrick->x + (float)BRICK_WIDTH / 2;
        const float centerBrickY = colBrick->y + (float)BRICK_HEIGHT / 2;

        // Centers of X and Y of ball
        const float centerBallX = ball.x + (float)BALL_SIZE / 2;
        const float centerBallY = ball.y + (float)BALL_SIZE / 2;

        // Signed collision offsets between brick and ball
        const float offsetX = centerBrickX - centerBallX;
        const float offsetY = centerBrickY - centerBallY;

        // Penetration depth of the ball on X and Y;
        // Add half-extents of brick and ball, then subtract
        // amount of overlap on that axis; the higher penetration
        // depth is the prioritized collision and axis of bounce
        const float penX = (float)(BRICK_WIDTH + BALL_SIZE) / 2 - fabsf(offsetX);
        const float penY = (float)(BRICK_HEIGHT + BALL_SIZE) / 2 - fabsf(offsetY);

        if (penX < penY)
        {
            ball.dx *= -1;
            ball.x += offsetX > 0 ? -penX : penX;
        }
        else
        {
            ball.dy *= -1;
            ball.y += offsetY > 0 ? -penY : penY;
        }

        // Slightly scale the y velocity to speed up the game
        ball.dy *= 1.02f;
    }

    if (ball.y >= (float)VIRTUAL_HEIGHT)
    {
        gHealth--;
        if (gHealth == 0)
        {
            if (!smSceneExists("game over"))
            {
                smAddScene("game over", nullptr, GameOverUpdate, GameOverDraw, GameOverExit);
            }
            smSetScene("game over", nullptr);
        }
        else
        {
            smSetScene("serve", nullptr);
        }

        PlaySound(*sdFind(HURT));
    }

    LevelUpdate(dt);
}

void PlayDraw(void)
{
    PaddleDraw();
    LevelDraw();
    LevelDrawParticles();
    BallDraw();

    if (!isPaused) { return; }

    constexpr float spacing = (float)LARGE_FONT / 10;
    const Vector2 textSize = MeasureTextEx(gFont, "PAUSED", (float)LARGE_FONT, spacing);
    const float textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(gFont, "PAUSED", (Vector2){textX, (float)VIRTUAL_HEIGHT / 2 - 16},
               (float)LARGE_FONT, spacing, WHITE);
}
