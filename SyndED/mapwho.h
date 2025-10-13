#ifndef MAPWHO_H
#define MAPWHO_H

#include <stdint.h>
#include <stdbool.h>

#include "gamedata.h"

bool add_thing_to_mapwho(GameData *gamedata, Thing *thing); // Thing is not const here as position might be corrected
void remove_thing_from_mapwho(GameData *gamedata, Thing *thing);
bool move_thing_within_mapwho(GameData *gamedata, Thing *thing, int16_t new_xpos, int16_t new_ypos, int16_t new_zpos);
bool verify_mapwho(const GameData *gamedata);
void rebuild_mapwho(GameData *gamedata);

#endif // MAPWHO_H
