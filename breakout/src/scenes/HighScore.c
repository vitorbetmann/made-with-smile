// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include <SceneManager.h>

#include "HighScore.h"

#include <stdlib.h>

#include "Constants.h"
#include "Util.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static constexpr char HIGH_SCORES_TEXT[] = "HIGH SCORES";
static constexpr char BLANK_TEXT[] = "---";
static constexpr char RETURN_TEXT[] = "Press Enter to return to the main menu";

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void HighScoreEnter(void *args)
{
    if (!FileExists(SAVE_FILE))
    {
        FILE *file = fopen(SAVE_FILE, "w");
        fclose(file);
    }

    if (strlen(gHighScores[0].name) == 0)
    {
        LoadHighScores();
    }
}

void HighScoreUpdate(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        smSetScene("start", nullptr);
    }
}

void HighScoreDraw(void)
{
    Vector2 textPos;
    Vector2 textSize = MeasureTextEx(gFont, HIGH_SCORES_TEXT, LARGE_FONT, 0);
    textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
    textPos.y = 20.0f;
    DrawTextEx(gFont, HIGH_SCORES_TEXT, textPos, LARGE_FONT, 0, WHITE);

    for (int i = 0; i < 10; i++)
    {
        textPos.y = 60 + 13.0f * (float)i;

        char buf[8];
        snprintf(buf, 8, "%d", i + 1);
        textSize = MeasureTextEx(gFont, buf, MEDIUM_FONT, 0);
        textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 4;
        DrawTextEx(gFont, buf, textPos, MEDIUM_FONT, 0, WHITE);

        const char *entry = strlen(gHighScores[i].name) != 0 ? gHighScores[i].name : BLANK_TEXT;
        textSize = MeasureTextEx(gFont, entry, MEDIUM_FONT, 0);
        textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
        DrawTextEx(gFont, entry, textPos, MEDIUM_FONT, 0, WHITE);

        entry = strlen(gHighScores[i].score) != 0 ? gHighScores[i].score : BLANK_TEXT;
        textSize = MeasureTextEx(gFont, entry, MEDIUM_FONT, 0);
        textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 4 * 3;
        DrawTextEx(gFont, entry, textPos, MEDIUM_FONT, 0, WHITE);
    }

    textSize = MeasureTextEx(gFont, RETURN_TEXT, SMALL_FONT, 0);
    textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
    textPos.y = (float)VIRTUAL_HEIGHT - 18;
    DrawTextEx(gFont, RETURN_TEXT, textPos, SMALL_FONT, 0, WHITE);

}
