/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - CSV Input                                              *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/30/25                                                 *
 *                                                                            *
 ******************************************************************************/

#ifndef CSVINPUT_H
#define CSVINPUT_H

// Needed for strnlen, affects '#include <string.h>'
#if defined(__GNUC__) && ! defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdint.h>    // uint16_t
#include <stddef.h>    // size_t

#include "gamedata.h"  // GameData, Person, Vehicle, ...

int read_mapwho_from_csv(const char *file_name, uint16_t mapwho[], const size_t count_x, const size_t count_y);
int read_people_from_csv(const char *file_name, Person people[], const size_t count);
int read_vehicles_from_csv(const char *file_name, Vehicle vehicles[], const size_t count);
int read_objects_from_csv(const char *file_name, Object objects[], const size_t count);
int read_weapons_from_csv(const char *file_name, Weapon weapons[], const size_t count);
int read_effects_from_csv(const char *file_name, Effect effects[], const size_t count);
int read_commands_from_csv(const char *file_name, Command commands[], const size_t count);
int read_worlds_from_csv(const char *file_name, World worlds[], const size_t count);
int read_objectives_from_csv(const char *file_name, Objective objectives[], const size_t count);
int read_cpobjectives_from_csv(const char *file_name, CPObjective cpobjectives[], const size_t count);
int read_structless_from_csv(const char *file_name, GameData *gamedata);

#endif // CSVINPUT_H
