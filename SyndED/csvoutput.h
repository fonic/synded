#ifndef CSVOUTPUT_H
#define CSVOUTPUT_H

#include <stddef.h>

#include "gamedata.h"

int write_mapwho_to_csv(const char *file_name, MapWho *mapwho, size_t row_count, size_t col_count);
int write_people_to_csv(const char *file_name, Person people[], size_t arrlen, size_t offset);
int write_vehicles_to_csv(const char *file_name, Vehicle vehicles[], size_t arrlen, size_t offset);
int write_objects_to_csv(const char *file_name, Object objects[], size_t arrlen, size_t offset);
int write_weapons_to_csv(const char *file_name, Weapon weapons[], size_t arrlen, size_t offset);
int write_effects_to_csv(const char *file_name, Effect effects[], size_t arrlen, size_t offset);
int write_commands_to_csv(const char *file_name, Command commands[], size_t arrlen, size_t offset);
int write_worlds_to_csv(const char *file_name, World worlds[], size_t arrlen, size_t offset);
int write_objectives_to_csv(const char *file_name, Objective objectives[], size_t arrlen, size_t offset);
int write_cpobjectives_to_csv(const char *file_name, CPObjective cpobjectives[], size_t arrlen, size_t offset);
int write_structless_to_csv(const char *file_name, GameData *gamedata);

#endif // CSVOUTPUT_H
