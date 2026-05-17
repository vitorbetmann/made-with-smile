// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Constants.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

// Font
Font gFont;

// Window
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// Virtual Window
const int VIRTUAL_WIDTH = 432;
const int VIRTUAL_HEIGHT = 243;

// Ball Behaviour
const int STARTING_BOUNCE_DX = 50;
const int BOUNCE_ANGLE_MULTIPLIER = 8;

// Health & Heart
const int MAX_HEALTH = 3;

const int HEART_WIDTH = 10;
const int HEART_HEIGHT = 9;

// Score
const int SCORE_COLOR = 25;
const int SCORE_TIER = 200;

// Brick
const int BRICK_WIDTH = 32;
const int BRICK_HEIGHT = 16;

const int TIER_THRESHOLD = 4;
const int COLOR_THRESHOLD = 4;

// Player
int gHealth = MAX_HEALTH;
int gScore = 0;
int gLevel = 1;
