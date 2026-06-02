#pragma once

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>

#include "Brick.h"
#include "Ball.h"
#include "Constants.h"
#include "PowerUp.h"

typedef enum
{
    ARROW_LEFT,
    ARROW_RIGHT,
} ArrowOrientation;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

void GenPaddleQuads(void);
Rectangle GetPaddleRect(void);

void GenBallQuads(void);
Rectangle GetBallRect(const Ball *b);

void GenBrickQuads(void);
Rectangle GetBrickRect(const Brick *brick);

void GenHeartsQuads(void);
Rectangle GetHeartRect(HeartStatus status);

void GenArrowQuads(void);
Rectangle GetArrowRect(ArrowOrientation orientation);

void GenPowerUpQuads(void);
Rectangle GetPowerUpRect(Type type);

void LoadHighScores(void);
void SaveHighScores(void);
