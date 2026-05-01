// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "TextureDict.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static TextureDict *td;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Public
// —————————————————————————————————————————————————————————————————————————————————————————————————

void tdAdd(TextureName name, const char *path)
{

    TextureDict *newTexture = malloc(sizeof(TextureDict));
    newTexture->id = name;

    Image i = LoadImage(path);
    newTexture->texture = LoadTextureFromImage(i);
    UnloadImage(i);

    HASH_ADD_INT(td, id, newTexture);
}

Texture *tdFind(const TextureName name)
{
    if (!td)
    {
        return nullptr;
    }

    TextureDict *res;
    HASH_FIND_INT(td, &name, res);
    return &res->texture;
}

void tdUnloadAll(void)
{
    if (!td)
    {
        return;
    }

    TextureDict *currTexture, *temp;
    HASH_ITER(hh, td, currTexture, temp)
    {
        UnloadTexture(*tdFind(currTexture->id));
        HASH_DEL(td, currTexture);
        free(currTexture);
    }
}
