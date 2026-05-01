// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Dependencies.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

void load(void);

void update(float dt);

void draw(void);
void drawVWindow(void);

void unload(void);

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static RenderTexture2D vWindow;
static bool displayFPS;
static Music music;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Main
// —————————————————————————————————————————————————————————————————————————————————————————————————

int main(void)
{
    load();
    while (smIsRunning())
    {
        update(smGetDt());
        draw();
    }
    unload();
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void load(void)
{
    // raylib
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout");
    SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(24);
    vWindow = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    InitAudioDevice();

    // sprites
    tdAdd(BACKGROUND, "assets/graphics/background.png");
    tdAdd(MAIN, "assets/graphics/breakout.png");
    tdAdd(ARROWS, "assets/graphics/arrows.png");
    tdAdd(HEARTS, "assets/graphics/hearts.png");
    tdAdd(PARTICLE, "assets/graphics/particle.png");

    // fonts
    gFont = LoadFont("assets/fonts/font.ttf");

    // sounds and music
    sdAdd(PADDLE_HIT, "assets/sounds/paddle_hit.wav");
    sdAdd(SCORE, "assets/sounds/score.wav");
    sdAdd(WALL_HIT, "assets/sounds/wall_hit.wav");
    sdAdd(CONFIRM, "assets/sounds/confirm.wav");
    sdAdd(SELECT, "assets/sounds/select.wav");
    sdAdd(NO_SELECT, "assets/sounds/no-select.wav");
    sdAdd(BRICK_HIT_1, "assets/sounds/brick-hit-1.wav");
    sdAdd(BRICK_HIT_2, "assets/sounds/brick-hit-2.wav");
    sdAdd(HURT, "assets/sounds/hurt.wav");
    sdAdd(VICTORY, "assets/sounds/victory.wav");
    sdAdd(RECOVER, "assets/sounds/recover.wav");
    sdAdd(HIGH_SCORE, "assets/sounds/high_score.wav");
    sdAdd(PAUSE, "assets/sounds/pause.wav");

    music = LoadMusicStream("assets/sounds/music.wav");
    PlayMusicStream(music);

    // SceneManager
    smStart();
    smCreateScene("start", nullptr, StartUpdate, StartDraw, StartExit);
    smSetScene("start", nullptr);
}

void update(const float dt)
{
    // quit
    if (IsKeyPressed(KEY_ESCAPE))
    {
        smStop();
    }

    smUpdate(dt);
    UpdateMusicStream(music);

    // toggle fps
    if (IsKeyPressed(KEY_T))
    {
        displayFPS = !displayFPS;
    }
}

void draw(void)
{
    BeginDrawing();
    drawVWindow();
    DrawTexturePro(
        vWindow.texture,
        (Rectangle){0, 0, (float)VIRTUAL_WIDTH, (float)-VIRTUAL_HEIGHT},
        (Rectangle){0, 0, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT},
        (Vector2){0}, 0, WHITE);
    EndDrawing();
}

void drawVWindow(void)
{
    BeginTextureMode(vWindow);

    const Texture bg = *tdFind(BACKGROUND);
    const Rectangle source = {0, 0, (float)bg.width, (float)bg.height};
    const Rectangle dest = {0, 0, (float)VIRTUAL_WIDTH + 1, (float)VIRTUAL_HEIGHT + 2};
    DrawTexturePro(bg, source, dest, (Vector2){0}, 0, WHITE);

    smDraw();

    // fps
    if (displayFPS)
    {
        DrawFPS(10, 10);
    }

    EndTextureMode();
}

void unload(void)
{
    // entities

    // textures
    tdUnloadAll();

    // fonts

    // sounds and music
    sdUnloadAll();
    UnloadMusicStream(music);

    CloseAudioDevice();
    CloseWindow();
}
