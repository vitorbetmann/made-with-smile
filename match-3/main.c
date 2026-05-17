// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Constants.h"
#include "dicts/SoundDict.h"
#include "dicts/TextureDict.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

static void load(void);

static void update(float dt);

static void draw(void);
static void drawVWindow(void);

static void unload(void);

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
    while (!WindowShouldClose())
    {
        update(GetFrameTime());
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
    SetTargetFPS(60);
    vWindow = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    InitAudioDevice();

    // sprites
    tdAdd(MATCH_3, "assets/graphics/match3.png");

    // fonts

    // sounds

    // music

    // SceneManager

    // Generate Quads
}

void update(const float dt)
{
    // quit
    if (IsKeyPressed(KEY_ESCAPE))
    {
        // smStop();
    }

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

    const Texture bg = *tdFind(MATCH_3);
    const Rectangle source = {0, 0, (float)bg.width, (float)bg.height};
    const Rectangle dest = {0, 0, (float)bg.width, (float)bg.height};
    DrawTexturePro(bg, source, dest, (Vector2){0}, 0, WHITE);


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
    UnloadRenderTexture(vWindow);
    tdUnloadAll();

    // fonts

    // sounds
    sdUnloadAll();

    // music
    UnloadMusicStream(music);

    CloseAudioDevice();
    CloseWindow();
}
