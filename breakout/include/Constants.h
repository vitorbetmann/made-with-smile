#pragma once

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Data types
// —————————————————————————————————————————————————————————————————————————————————————————————————

// Font
typedef enum
{
    SMALL_FONT = 8,
    MEDIUM_FONT = 16,
    LARGE_FONT = 32,
} FontSize;

// Health & Heart
typedef enum
{
    FULL,
    EMPTY
} HeartStatus;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

// Font
extern Font gFont;

// Window
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

// Virtual Window
extern const int VIRTUAL_WIDTH;
extern const int VIRTUAL_HEIGHT;

// Ball Behaviour
extern const int STARTING_BOUNCE_DX;
extern const int BOUNCE_ANGLE_MULTIPLIER;

// Health & Heart
extern const int MAX_HEALTH;

extern const int HEART_WIDTH;
extern const int HEART_HEIGHT;

// Player
extern int gHealth;
extern int gScore;
extern int gLevel;
