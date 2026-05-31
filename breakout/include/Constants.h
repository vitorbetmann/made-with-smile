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

// High Scores
typedef struct
{
    char name[4];
    char score[32];
} ScoreData;

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

// Score
extern const int SCORE_COLOR;
extern const int SCORE_TIER;

// Bricks
extern const int BRICK_WIDTH;
extern const int BRICK_HEIGHT;

extern const int TIER_THRESHOLD;
extern const int COLOR_THRESHOLD;

// Player
extern int gHealth;
extern int gScore;
extern int gLevel;

// Level Maker
extern int gBricksActive;

// High Scores
extern ScoreData gHighScores[10];
extern char SAVE_FILE[];
