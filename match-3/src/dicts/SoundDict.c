// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "SoundDict.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static SoundDict *sd;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Public
// —————————————————————————————————————————————————————————————————————————————————————————————————

void sdAdd(SoundName name, const char *path) {
  SoundDict *newSound = malloc(sizeof(SoundDict));
  newSound->id = name;
  newSound->sound = LoadSound(path);

  HASH_ADD_INT(sd, id, newSound);
}

Sound *sdFind(const SoundName name) {
  SoundDict *res;
  HASH_FIND_INT(sd, &name, res);
  return &res->sound;
}

void sdUnloadAll(void) {
  SoundDict *currSound, *temp;
  HASH_ITER(hh, sd, currSound, temp) {
    UnloadSound(*sdFind(currSound->id));
    HASH_DEL(sd, currSound);
    free(currSound);
  }
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Static
// —————————————————————————————————————————————————————————————————————————————————————————————————