#pragma once

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>

#include "Brick.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

void GenPaddleQuads(void);
Rectangle GetPaddleQuad(void);

void GenBallQuads(void);
Rectangle GetBallQuad(void);

void GenBrickQuads(void);
Rectangle GetBrickQuad(const Brick *brick);

