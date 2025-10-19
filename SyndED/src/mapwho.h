/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - MapWho Management                                      *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/19/25                                                 *
 *                                                                            *
 ******************************************************************************/

#ifndef MAPWHO_H
#define MAPWHO_H

#include <stdint.h>    // int16_t
#include <stdbool.h>   // bool

#include "gamedata.h"  // GameData, Thing

bool add_thing_to_mapwho(GameData *gamedata, Thing *thing); // Thing is not const here as position might be corrected
void remove_thing_from_mapwho(GameData *gamedata, Thing *thing);
bool move_thing_within_mapwho(GameData *gamedata, Thing *thing, int16_t new_xpos, int16_t new_ypos, int16_t new_zpos);
bool verify_mapwho(const GameData *gamedata);
void rebuild_mapwho(GameData *gamedata);

#endif // MAPWHO_H
