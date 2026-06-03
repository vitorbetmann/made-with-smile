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
#include "Paddle.h"
#include "Victory.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static bool isPaused;
static int growScore;

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
    const int powerUpCollision = PowerUpCheckPaddleCollision();
    if (powerUpCollision != -1)
    {
        PowerUpTrigger(powerUpCollision);
    }

    int i = 0;
    while (i < gActiveBalls)
    {
        bool ballDied = false;
        BallUpdate(&balls[i], dt);

        if (CheckCollisionRecs(BallGetRect(&balls[i]), PaddleGetRect()))
        {
            balls[i].y = paddle.y - (float)BALL_SIZE;
            balls[i].dy *= -1;

            const bool isPaddleMovingLeft = paddle.dx < 0;
            const bool isPaddleMovingRight = paddle.dx > 0;
            const float paddleCenter = paddle.x + (float)paddle.width / 2;
            const float ballOffset = fabsf(balls[i].x - paddleCenter);

            if (balls[i].x < paddleCenter && isPaddleMovingLeft)
            {
                balls[i].dx = (float)-STARTING_BOUNCE_DX - (float)BOUNCE_ANGLE_MULTIPLIER *
                              ballOffset;
            }
            else if (balls[i].x > paddleCenter && isPaddleMovingRight)
            {
                balls[i].dx = (float)STARTING_BOUNCE_DX + (float)BOUNCE_ANGLE_MULTIPLIER *
                              ballOffset;
            }

            PlaySound(*sdFind(PADDLE_HIT));
        }

        Brick *colBrick = LevelCheckBrickCollision(&balls[i]);
        if (colBrick)
        {
            const int hitScore = (colBrick->tier + 1) * SCORE_TIER + (colBrick->color + 1) *
                                 SCORE_COLOR;
            gScore += hitScore;
            growScore += hitScore;
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
            const float centerBallX = balls[i].x + (float)BALL_SIZE / 2;
            const float centerBallY = balls[i].y + (float)BALL_SIZE / 2;

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
                balls[i].dx *= -1;
                balls[i].x += offsetX > 0 ? -penX : penX;
            }
            else
            {
                balls[i].dy *= -1;
                balls[i].y += offsetY > 0 ? -penY : penY;
            }

            // Slightly scale the y velocity to speed up the game
            balls[i].dy *= 1.02f;

            // Randomly spawn power ups
            if (gScore > 100 && gScore % 100 == 0)
            {
                PowerUpActivate(SPAWN_BALLS, colBrick->x, colBrick->y);
            }

            if (paddle.size < 4 && growScore >= 5000)
            {
                growScore = 0;
                PaddleGrow();
            }
        }

        if (balls[i].y >= (float)VIRTUAL_HEIGHT)
        {
            const Ball temp = balls[i];
            balls[i] = balls[gActiveBalls - 1];
            balls[gActiveBalls - 1] = temp;
            gActiveBalls--;
            ballDied = true;
            PlaySound(*sdFind(HURT));
        }

        if (gActiveBalls == 0)
        {
            growScore = 0;
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
                PaddleShrink();
                smSetScene("serve", nullptr);
            }

            return;
        }

        if (!ballDied) { i++; }
    }

    LevelUpdate(dt);
}

void PlayDraw(void)
{
    PaddleDraw();
    LevelDraw();
    LevelDrawParticles();
    for (int i = 0; i < gActiveBalls; i++)
    {
        BallDraw(&balls[i]);
    }

    if (!isPaused) { return; }

    constexpr float spacing = (float)LARGE_FONT / 10;
    const Vector2 textSize = MeasureTextEx(gFont, "PAUSED", (float)LARGE_FONT, spacing);
    const float textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(gFont, "PAUSED", (Vector2){textX, (float)VIRTUAL_HEIGHT / 2 - 16},
               (float)LARGE_FONT, spacing, WHITE);
}
