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
constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

// Virtual Window
constexpr int VIRTUAL_WIDTH = 432;
constexpr int VIRTUAL_HEIGHT = 243;

// Balls
int gActiveBalls;
constexpr int STARTING_BOUNCE_DX = 50;
constexpr int BOUNCE_ANGLE_MULTIPLIER = 8;

// Health & Heart
constexpr int MAX_HEALTH = 3;

constexpr int HEART_WIDTH = 10;
constexpr int HEART_HEIGHT = 9;

// Score
constexpr int SCORE_COLOR = 25;
constexpr int SCORE_TIER = 200;

// Brick
constexpr int BRICK_WIDTH = 32;
constexpr int BRICK_HEIGHT = 16;

constexpr int TIER_THRESHOLD = 4;
constexpr int COLOR_THRESHOLD = 4;

// Player
extern int gHealth;
extern int gScore;
extern int gLevel;

// Level Maker
extern int gBricksActive;

// High Scores
extern ScoreData gHighScores[10];
extern char SAVE_FILE[];
constexpr int MAX_NAME_LENGTH = 3;

// Power Ups
constexpr int POWER_UP_AMOUNT = 10;
constexpr int POWER_UP_SIZE = 16;
constexpr int POWER_UP_SPEED = 50;
