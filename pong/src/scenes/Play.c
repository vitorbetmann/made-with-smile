// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <SceneManager.h>

#include "Ball.h"
#include "Paddle.h"
#include "Settings.h"

#include "Play.h"
#include "Serve.h"
#include "GameOver.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static bool isScore, isGameOver;
static Player server, winner;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void PlayUpdate(float dt)
{
    ballUpdate(dt);

    // paddle collision
    if (ball.dx < 0)
    {
        if (CheckCollisionRecs(ballGetRect(), paddleGetRect(&(player1.paddle))))
        {
            PlaySound(paddle_hit);
            ball.dx = -ball.dx * 1.03;
            ball.x = player1.paddle.x + PADDLE_WIDTH;
            int newDy = GetRandomValue(10, 150);
            ball.dy = ball.dy < 0 ? newDy : -newDy;
        }
    }
    else if (CheckCollisionRecs(ballGetRect(), paddleGetRect(&(player2.paddle))))
    {
        PlaySound(paddle_hit);
        ball.dx = -ball.dx * 1.03;
        ball.x = player2.paddle.x - BALL_SIZE;
        int newDy = GetRandomValue(10, 150);
        ball.dy = ball.dy < 0 ? newDy : -newDy;
    }

    // window boundary collision
    if (ball.y <= 0)
    {
        PlaySound(wall_hit);
        ball.y = 0;
        ball.dy *= -1;
    }
    else if (ball.y >= VIRTUAL_HEIGHT)
    {
        PlaySound(wall_hit);
        ball.y = VIRTUAL_HEIGHT - BALL_SIZE;
        ball.dy *= -1;
    }

    if (ball.x + BALL_SIZE <= 0)
    {
        if (++player2.score == MAX_SCORE)
        {
            isGameOver = true;
            winner = player2;
        }
        else
        {
            server = player1;
        }
        isScore = true;
    }
    else if (ball.x >= VIRTUAL_WIDTH)
    {
        if (++player1.score == MAX_SCORE)
        {
            isGameOver = true;
            winner = player1;
        }
        else
        {
            server = player2;
        }
        isScore = true;
    }

    if (isScore)
    {
        PlaySound(score);
        if (isGameOver)
        {
            if (!smSceneExists("game over"))
            {
                smCreateScene("game over", GameOverEnter, GameOverUpdate, GameOverDraw, nullptr);
            }
            smSetScene("game over", &((GameOverData){winner}));
        }
        else
        {
            smSetScene("serve", &((ServeData){server}));
        }
    }
}

void PlayExit(void)
{
    isGameOver = isScore = false;
}
