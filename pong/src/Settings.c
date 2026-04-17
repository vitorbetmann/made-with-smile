// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>

#include "Settings.h"
#include "Ball.h"
#include "Paddle.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

Ball ball;
Player player1, player2;

RenderTexture2D vWindow;
Font font;

Sound paddle_hit, score, wall_hit;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGTH = 720;

const int VIRTUAL_WIDTH = 432;
const int VIRTUAL_HEIGHT = 243;

const int FONTLARGE = 32;
const int FONTSMALL = 8;
const float FONTRAYLIB = 10.0f;

const Color COLORBG = {45, 45, 52, 255};

const int MAX_SCORE = 10;
