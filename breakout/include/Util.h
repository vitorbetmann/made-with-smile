#pragma once

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>

#include "Brick.h"
#include "Constants.h"

typedef enum
{
    ARROW_LEFT,
    ARROW_RIGHT,
} ArrowOrientation;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

void GenPaddleQuads(void);
Rectangle GetPaddleQuad(void);

void GenBallQuads(void);
Rectangle GetBallQuad(void);

void GenBrickQuads(void);
Rectangle GetBrickQuad(const Brick *brick);

void GenHeartsQuads(void);
Rectangle GetHeartRect(HeartStatus status);

void GenArrowQuads(void);
Rectangle GetArrowRect(ArrowOrientation orientation);

void LoadHighScores(void);
void SaveHighScores(void);
