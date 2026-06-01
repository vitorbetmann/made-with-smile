// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SceneManager.h>

#include "EnterHighScore.h"


#include "Constants.h"
#include "GameOver.h"
#include "HighScore.h"
#include "SoundDict.h"
#include "Util.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static constexpr char CONFIRM_TEXT[] = "Press Enter to continue";
static int scoreIndex;
static int highlightChar = 0;
static char name[4];

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void EnterHighScoreEnter(void *args)
{
    PlaySound(*sdFind(HIGH_SCORE));
    for (int i = 0; i < 3; i++)
    {
        name[i] = 'A';
    }
    name[3] = '\0';

    highlightChar = 0;
    scoreIndex = ((GameOverData *)args)->scoreIndex;
}

void EnterHighScoreUpdate(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        if (!smSceneExists("high score"))
        {
            smAddScene("high score", nullptr, HighScoreUpdate, HighScoreDraw, nullptr);
        }
        smSetScene("high score", nullptr);
        return;
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        highlightChar++;
        highlightChar %= MAX_NAME_LENGTH;
        PlaySound(*sdFind(SELECT));
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        highlightChar--;
        highlightChar = highlightChar >= 0 ? highlightChar : MAX_NAME_LENGTH - 1;
        PlaySound(*sdFind(SELECT));
    }

    if (IsKeyPressed(KEY_UP))
    {
        name[highlightChar]++;
        name[highlightChar] = name[highlightChar] > 'Z' ? 'A' : name[highlightChar];
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        name[highlightChar]--;
        name[highlightChar] = name[highlightChar] < 'A' ? 'Z' : name[highlightChar];
    }
}

void EnterHighScoreDraw(void)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "You got a high score: %d", gScore);
    Vector2 textSize = MeasureTextEx(gFont, buf, MEDIUM_FONT, 0);
    Vector2 textPos = {((float)VIRTUAL_WIDTH - textSize.x) / 2, 30};
    DrawTextEx(gFont, buf, textPos, MEDIUM_FONT, 0, WHITE);

    Color color = WHITE;

    // Name letters
    if (highlightChar == 0) { color.r = 103; }
    snprintf(buf, sizeof(buf), "%c", name[0]);
    textPos.x = (float)VIRTUAL_WIDTH / 2 - 28;
    textPos.y = (float)VIRTUAL_HEIGHT / 2;
    DrawTextEx(gFont, buf, textPos, MEDIUM_FONT, 0, color);
    color = WHITE;

    if (highlightChar == 1) { color.r = 103; }
    snprintf(buf, sizeof(buf), "%c", name[1]);
    textPos.x = (float)VIRTUAL_WIDTH / 2 - 6;
    DrawTextEx(gFont, buf, textPos, MEDIUM_FONT, 0, color);
    color = WHITE;

    if (highlightChar == 2) { color.r = 103; }
    snprintf(buf, sizeof(buf), "%c", name[2]);
    textPos.x = (float)VIRTUAL_WIDTH / 2 + 20;
    DrawTextEx(gFont, buf, textPos, MEDIUM_FONT, 0, color);
    color = WHITE;

    // Continue text
    textSize = MeasureTextEx(gFont, CONFIRM_TEXT, SMALL_FONT, 0);
    textPos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2;
    textPos.y = (float)VIRTUAL_HEIGHT - 18;
    DrawTextEx(gFont, CONFIRM_TEXT, textPos, SMALL_FONT, 0, WHITE);
}

void EnterHighScoreExit(void)
{
    for (int i = 8; i >= scoreIndex; i--)
    {
        gHighScores[i + 1] = gHighScores[i];
    }

    char buf[32];
    snprintf(buf, sizeof(buf), "%d", gScore);
    strcpy(gHighScores[scoreIndex].name, name);
    strcpy(gHighScores[scoreIndex].score, buf);

    SaveHighScores();
}
