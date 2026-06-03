// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "PowerUp.h"

#include "TextureDict.h"
#include "Constants.h"
#include "Paddle.h"
#include "SoundDict.h"
#include "Util.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static PowerUp powerUps[POWER_UP_AMOUNT];

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

static void ActivateBallPowerUp(void);
static void ActivateKeyPowerUp(void);

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void PowerUpActivate(const Type type, const float x, const float y)
{
    if (powerUps[type].isActive) { return; }
    powerUps[type].isActive = true;
    powerUps[type].x = x;
    powerUps[type].y = y;
    powerUps[type].dy = POWER_UP_SPEED;
}

int PowerUpCheckPaddleCollision(void)
{
    for (int i = 0; i < POWER_UP_AMOUNT; i++)
    {
        if (!powerUps[i].isActive) { continue; }
        const bool hasCollision = CheckCollisionRecs(
            (Rectangle){paddle.x, paddle.y, (float)paddle.width, (float)paddle.height},
            (Rectangle){powerUps[i].x, powerUps[i].y, POWER_UP_SIZE, POWER_UP_SIZE}
            );
        if (hasCollision)
        {
            powerUps[i].isActive = false;
            return i;
        }
    }
    return -1;
}

void PowerUpTrigger(const Type type)
{
    switch (type)
    {
    case SPAWN_BALLS:
        ActivateBallPowerUp();
        return;
    case SPAWN_KEY:
        ActivateKeyPowerUp();
        break;
    default:
        break;
    }
}

void PowerUpsInit(void)
{
    for (int i = 0; i < POWER_UP_AMOUNT; i++)
    {
        powerUps[i].type = i;
    }
}

void PowerUpsUpdate(const float dt)
{
    for (int i = 0; i < POWER_UP_AMOUNT; i++)
    {
        if (!powerUps[i].isActive) { continue; }
        powerUps[i].y += powerUps[i].dy * dt;

        if (powerUps[i].y > VIRTUAL_HEIGHT)
        {
            powerUps[i].isActive = false;
        }
    }
}

void PowerUpsDraw(void)
{
    for (int i = 0; i < POWER_UP_AMOUNT; i++)
    {
        if (!powerUps[i].isActive) { continue; }
        const Rectangle dest = {powerUps[i].x, powerUps[i].y, (float)POWER_UP_SIZE,
                                (float)POWER_UP_SIZE};
        DrawTexturePro(*tdFind(MAIN), GetPowerUpRect(powerUps[i].type), dest, (Vector2){0}, 0,
                       WHITE);
    }
}

void PowerUpDeactivate(const Type type)
{
    powerUps[type].isActive = false;
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Static
// —————————————————————————————————————————————————————————————————————————————————————————————————

void ActivateBallPowerUp(void)
{
    if (gActiveBalls == 3)
    {
        PlaySound(*sdFind(SCORE));
        gScore += 500;
        return;
    }
    for (int i = gActiveBalls; i < 3; i++)
    {
        BallReset(&balls[i]);
    }
    gActiveBalls = 3;
}

void ActivateKeyPowerUp(void)
{
    UnlockSpecialBrick();
}
