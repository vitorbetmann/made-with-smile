#pragma once

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Brick.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

void LevelCreate(int level);
bool IsLevelActive(void);
void LevelUpdate(float dt);
void LevelDraw(void);
void LevelDrawParticles(void);
Brick *LevelCheckBrickCollision(void);
void LevelUnload(void);
