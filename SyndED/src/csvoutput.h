/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - CSV Output                                             *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/14/25                                                 *
 *                                                                            *
 ******************************************************************************/

#ifndef CSVOUTPUT_H
#define CSVOUTPUT_H

#include <stddef.h>

#include "gamedata.h"

int write_mapwho_to_csv(const char *file_name, const uint16_t mapwho[], const size_t count_x, const size_t count_y);
int write_people_to_csv(const char *file_name, const Person people[], const size_t count, const size_t offset_global, const size_t offset_relative);
int write_vehicles_to_csv(const char *file_name, const Vehicle vehicles[], const size_t count, const size_t offset_global, const size_t offset_relative);
int write_objects_to_csv(const char *file_name, const Object objects[], const size_t count, const size_t offset_global, const size_t offset_relative);
int write_weapons_to_csv(const char *file_name, const Weapon weapons[], const size_t count, const size_t offset_global, const size_t offset_relative);
int write_effects_to_csv(const char *file_name, const Effect effects[], const size_t count, const size_t offset_global, const size_t offset_relative);
int write_commands_to_csv(const char *file_name, const Command commands[], const size_t count, const size_t offset_global, const size_t offset_relative);
int write_worlds_to_csv(const char *file_name, const World worlds[], const size_t count, const size_t offset_global, const size_t offset_relative);
int write_objectives_to_csv(const char *file_name, const Objective objectives[], const size_t count, const size_t offset_global, const size_t offset_relative);
int write_cpobjectives_to_csv(const char *file_name, const CPObjective cpobjectives[], const size_t count, const size_t offset_global, const size_t offset_relative);
int write_structless_to_csv(const char *file_name, const GameData *gamedata);

#endif // CSVOUTPUT_H
