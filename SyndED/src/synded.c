/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - Main                                                   *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/23/25                                                 *
 *                                                                            *
 ******************************************************************************/

#include "asprintf.h"   // asprintf; needs to be on top, modifies '#include <stdio.h>'
//#include "stpecpy.h"  // stpecpy; needs to be on top, modifies '#include <string.h>'

#include <stdio.h>      // printf, fprintf, fopen, fclose, fread, fwrite, ftell, fseek, stderr, FILE
#include <stdint.h>     // int16_t, , ...
#include <stdlib.h>     // free, rand
#include <string.h>     // strerror, strstr
#include <errno.h>      // errno
#include <stddef.h>     // size_t, offsetof

#include "gamedata.h"
#include "gdenums.h"
#include "csvoutput.h"
#include "mapwho.h"

#define member_size(type, member) (sizeof(((type *)0)->member))          // https://stackoverflow.com/a/3553321

const char* bytes_to_hex_str(const uint8_t *data, const size_t count) {  // https://stackoverflow.com/a/71426890
	static char buffer[1024];
	//memset(&buffer, '\0', sizeof(buffer));                 // not required due to terminating after loop
	size_t i = 0;
	for (i = 0; i < count && i < sizeof(buffer) / 3; i++) {  // 3 buffer bytes per data byte
		buffer[i*3]   = "0123456789ABCDEF"[data[i] >> 4 ];   // high nibble to hex
		buffer[i*3+1] = "0123456789ABCDEF"[data[i] & 0xF];   // low nibble to hex
		buffer[i*3+2] = ' ';
	}
	if (i > 0)
		buffer[(i-1)*3+2] = '\0';                            // replace trailing space
	else
		buffer[0] = '\0';                                    // empty string
	return buffer;
}


int main(int argc, char *argv[]) {


	/******************************************************************************
	 *                                                                            *
	 *  Process command line                                                      *
	 *                                                                            *
	 ******************************************************************************/

	// Process command line
	if (argc != 3) {
		fprintf(stderr, "Usage:   %s INFILE OUTFILE\n", argv[0]);
		fprintf(stderr, "Example: %s GAMExx.DAT_in GAMExx.DAT_out\n", argv[0]);
		return 2;
	}
	const char *infile_name = argv[1];
	const char *outfile_name = argv[2];


	/******************************************************************************
	 *                                                                            *
	 *  Check and read input file                                                 *
	 *                                                                            *
	 ******************************************************************************/

	// Game data struct
	GameData gamedata;

	// Open input file
	printf("Opening input file '%s'...\n", infile_name);
	FILE *infile = fopen(infile_name, "rb"); // read, binary mode
	if (infile == NULL) {
		fprintf(stderr, "Error: failed to open input file '%s': %s\n", infile_name, strerror(errno));
		return 1;
	}

	// Check input file size (to rule out incompatible input files, e.g. RNCed or Beta version)
	// Should be the most portable approach (https://stackoverflow.com/a/238609)
	printf("Checking size of file '%s'...\n", infile_name);
	if (fseek(infile, 0, SEEK_END) != 0) {
		fprintf(stderr, "Error: failed to seek to end of input file '%s': %s\n", infile_name, strerror(errno));
		return 1;
	}
	long file_size = ftell(infile);
	if (file_size == -1) {
		fprintf(stderr, "Error: failed to determine size of input file '%s': %s\n", infile_name, strerror(errno));
		return 1;
	}
	if (file_size != sizeof(GameData)) {
		fprintf(stderr, "Error: incorrect size of input file '%s': got %ld bytes, expected %zu bytes\n", infile_name, file_size, sizeof(GameData));
		return 1;
	}
	if (fseek(infile, 0, SEEK_SET) != 0) { // Important, need to seek back to start!
		fprintf(stderr, "Error: failed to seek to start of input file '%s': %s\n", infile_name, strerror(errno));
		return 1;
	}

	// Read contents of input file into game data struct
	printf("Reading input file '%s'...\n", infile_name);
	size_t read_count = fread(&gamedata, 1, sizeof(GameData), infile);
	if (read_count != sizeof(GameData)) {
		fprintf(stderr, "Error: failed to read input file '%s': read only %ld bytes out of %lu bytes\n", infile_name, read_count, sizeof(GameData));
		fclose(infile);
		return 1;
	}

	// Close input file
	printf("Closing input file '%s'...\n", infile_name);
	if (fclose(infile) != 0) {
		fprintf(stderr, "Error: failed to close input file '%s': %s\n", infile_name, strerror(errno));
		return 1;
	}
	printf("\n");


	/******************************************************************************
	 *                                                                            *
	 *  Print game data hex signatures (debug builds only)                        *
	 *                                                                            *
	 ******************************************************************************/

#ifdef DEBUG
	// Print hex signatures of game data contents
	printf("Game data hex signatures:\n");
	printf("Seed, ..., Timer:            %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.Seed),          6));
	printf("MapWho:                      %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.MapWho),       20));
	printf("RelOfsBase:                  %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.RelOfsBase),    2));
	printf("People:                      %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.People),       20));
	printf("Vehicles:                    %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.Vehicles),     20));
	printf("Objects:                     %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.Objects),      20));
	printf("Weapons:                     %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.Weapons),      20));
	printf("Effects:                     %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.Effects),      20));
	printf("Commands:                    %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.Commands),     20));
	printf("Worlds:                      %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.Worlds),       20));
	printf("MapNumber, ..., HiBoundaryy: %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.MapNumber),    10));
	printf("Objectives:                  %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.Objectives),   20));
	printf("CPCount, ..., CPWeapon:      %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.CPCount),       8));
	printf("CPObjectives:                %s\n", bytes_to_hex_str((const uint8_t *)(&gamedata.CPObjectives), 20));
	printf("\n");
#endif


	/******************************************************************************
	 *                                                                            *
	 *  Generate CSV output (BEFORE editing, reflects INPUT file contents)        *
	 *                                                                            *
	 ******************************************************************************/

	// CSV file name
	char *csvfile_name;

	// Write MapWho array to CSV file
	asprintf(&csvfile_name, "%s_mapwho.csv", infile_name);
	write_mapwho_to_csv(csvfile_name, gamedata.MapWho, TILES_COUNT_X, TILES_COUNT_Y);
	free(csvfile_name);

	// Write People array to CSV file
	asprintf(&csvfile_name, "%s_people.csv", infile_name);
	write_people_to_csv(csvfile_name, gamedata.People, PEOPLE_COUNT, PEOPLE_GLOBAL_OFFSET, PEOPLE_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Vehicles array to CSV file
	asprintf(&csvfile_name, "%s_vehicles.csv", infile_name);
	write_vehicles_to_csv(csvfile_name, gamedata.Vehicles, VEHICLES_COUNT, VEHICLES_GLOBAL_OFFSET, VEHICLES_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Objects array to CSV file
	asprintf(&csvfile_name, "%s_objects.csv", infile_name);
	write_objects_to_csv(csvfile_name, gamedata.Objects, OBJECTS_COUNT, OBJECTS_GLOBAL_OFFSET, OBJECTS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Weapons array to CSV file
	asprintf(&csvfile_name, "%s_weapons.csv", infile_name);
	write_weapons_to_csv(csvfile_name, gamedata.Weapons, WEAPONS_COUNT, WEAPONS_GLOBAL_OFFSET, WEAPONS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Effects array to CSV file
	asprintf(&csvfile_name, "%s_effects.csv", infile_name);
	write_effects_to_csv(csvfile_name, gamedata.Effects, EFFECTS_COUNT, EFFECTS_GLOBAL_OFFSET, EFFECTS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Commands array to CSV file
	asprintf(&csvfile_name, "%s_commands.csv", infile_name);
	write_commands_to_csv(csvfile_name, gamedata.Commands, COMMANDS_COUNT, COMMANDS_GLOBAL_OFFSET, COMMANDS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Worlds array to CSV file
	asprintf(&csvfile_name, "%s_worlds.csv", infile_name);
	write_worlds_to_csv(csvfile_name, gamedata.Worlds, WORLDS_COUNT, WORLDS_GLOBAL_OFFSET, WORLDS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Objectives array to CSV file
	asprintf(&csvfile_name, "%s_objectives.csv", infile_name);
	write_objectives_to_csv(csvfile_name, gamedata.Objectives, OBJECTIVES_COUNT, OBJECTIVES_GLOBAL_OFFSET, OBJECTIVES_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write CPObjectives array to CSV file
	asprintf(&csvfile_name, "%s_cpobjectives.csv", infile_name);
	write_cpobjectives_to_csv(csvfile_name, gamedata.CPObjectives, CPOBJECTIVES_COUNT, CPOBJECTIVES_GLOBAL_OFFSET, CPOBJECTIVES_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write structless GameData members to CSV file
	asprintf(&csvfile_name, "%s_structless.csv", infile_name);
	write_structless_to_csv(csvfile_name, &gamedata);
	free(csvfile_name);
	printf("\n");


	/******************************************************************************
	 *                                                                            *
	 *  Edit/modify game data                                                     *
	 *                                                                            *
	 ******************************************************************************/

	if (strstr(infile_name, "Synd/GAME01/GAME01.DAT_in") != NULL) {  // Western Europe

		printf("Editing/modifying GAME01.DAT (see sources)...\n");
		Vehicle vehicle = gamedata.Vehicles[0];    // Existing Vehicle
		Person person = gamedata.People[9];        // Existing Guard
		Weapon weapon = gamedata.Weapons[0];       // Existing Uzi (belongs to last guard at road)

		size_t vehicle_slot = 20; size_t weapon_slot = 20; size_t person_slot = 20;  // Lots of free space for new stuff

		// Add three people in front of existing car
		for (int16_t shiftx = -50; shiftx <= 50; shiftx += 50) {
			person.Xpos = vehicle.Xpos + shiftx; person.Ypos = vehicle.Ypos + 500; person.BaseFrame = PB_MAN_JACKET; person.Life = 8;
			person.State = person.NewState = 0; person.Angle = TA_SOUTH; person.Parent = person.ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
			weapon.State = WS_MINIGUN; weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * person_slot;
			gamedata.Weapons[weapon_slot++] = weapon; gamedata.People[person_slot++] = person;
		}

		// Add second car + three people in front of it
		vehicle.Xpos -= 500; vehicle.State = VS_POLICECAR; vehicle.Life = 60; vehicle.MaxSpeed = 100;
		gamedata.Vehicles[vehicle_slot++] = vehicle;
		for (int16_t shiftx = -50; shiftx <= 50; shiftx += 50) {
			person.Xpos = vehicle.Xpos + shiftx; person.Ypos = vehicle.Ypos + 500; person.BaseFrame = PB_POLICE; person.Life = 8;
			person.State = person.NewState = 0; person.Angle = TA_SOUTHWEST; person.Parent = person.ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
			weapon.State = WS_MINIGUN; weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * person_slot;
			gamedata.Weapons[weapon_slot++] = weapon; gamedata.People[person_slot++] = person;
		}

		// Add third car + three people in front of it
		vehicle.Xpos -= 500; vehicle.State = VS_APC; vehicle.Life = 90; vehicle.MaxSpeed = 50;
		gamedata.Vehicles[vehicle_slot++] = vehicle;
		for (int16_t shiftx = -50; shiftx <= 50; shiftx += 50) {
			person.Xpos = vehicle.Xpos + shiftx; person.Ypos = vehicle.Ypos + 500; person.BaseFrame = PB_SOLDIER; person.Life = 8;
			person.State = person.NewState = 0; person.Angle = TA_WEST; person.Parent = person.ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
			weapon.State = WS_MINIGUN; weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * person_slot;
			gamedata.Weapons[weapon_slot++] = weapon; gamedata.People[person_slot++] = person;
		}

		// Rebuild MapWho to account for added things (important!)
		rebuild_mapwho(&gamedata);

	} else if (strstr(infile_name, "Synd/GAME10/GAME10.DAT_in") != NULL) {  // Eastern Europe

		printf("Editing/modifying GAME10.DAT (see sources)...\n");
		Weapon weapon = gamedata.Weapons[1];    // Existing Uzi
		size_t weapon_slot = 30;                // Lots of free space
		for (size_t i = 0; i < sizeof(gamedata.People) / sizeof(gamedata.People[0]); i++) {                             // Power to the People!
			if (gamedata.People[i].BaseFrame == PB_WOMAN_REDHEAD || gamedata.People[i].BaseFrame == PB_WOMAN_BLONDE) {  // Women get Uzis
				gamedata.People[i].Unique = PU_GUARD;
				gamedata.People[i].Life = 10;
				gamedata.People[i].Parent = gamedata.People[i].ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
				weapon.State = WS_UZI;
				weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * i;
				gamedata.Weapons[weapon_slot++] = weapon;
			} else if (gamedata.People[i].BaseFrame == PB_MAN_SUIT || gamedata.People[i].BaseFrame == PB_MAN_JACKET) {  // Men get Shotguns
				gamedata.People[i].Unique = PU_GUARD;
				gamedata.People[i].Life = 10;
				gamedata.People[i].Parent = gamedata.People[i].ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
				weapon.State = WS_SHOTGUN;
				weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * i;
				gamedata.Weapons[weapon_slot++] = weapon;
			}
		}

		// No MapWho rebuild required here
		//rebuild_mapwho(&gamedata);

	} else if (strstr(infile_name, "Synd/GAME20/GAME20.DAT_in") != NULL) {  // Scandinavia

		printf("Editing/modifying GAME20.DAT (see sources)...\n");
		size_t person_slot = 65;                                     // Lots of free space
		for (size_t i = 8; i < 60; i++) {                            // Twice the civilians == twice the fun
			if (gamedata.People[i].Unique == PU_CIVILIAN) {
				Person person = gamedata.People[i];                  // Two tiles variation in positioning
				person.Xpos += (rand() % (POS_PER_TILE * 2)) - POS_PER_TILE;
				person.Ypos += (rand() % (POS_PER_TILE * 2)) - POS_PER_TILE;
				person.Angle = rand() % 256;                         // Wander somewhere nice
				person.NewState = PS_WANDER;
				switch (rand() % 4) {
					case 0:
						person.BaseFrame = PB_WOMAN_BLONDE;
						break;
					case 1:
						person.BaseFrame = PB_WOMAN_REDHEAD;
						break;
					case 2:
						person.BaseFrame = PB_MAN_SUIT;
						break;
					default:
						person.BaseFrame = PB_MAN_JACKET;
						break;
				}
				gamedata.People[person_slot++] = person;
			}
		}

		// Rebuild MapWho to account for added things (important!)
		rebuild_mapwho(&gamedata);

	} else if (strstr(infile_name, "Synd/GAME31/GAME31.DAT_in") != NULL) {  // South Africa

		printf("Editing/modifying GAME31.DAT (see sources)...\n");
		//gamedata.CPObjectives[1].Child = 3;    // Bypass execution flow fork -> ALL blue agents will walk to APC
		gamedata.CPObjectives[4].Child = 7;      // Bypass 1,25 + 2,25 -> Agent will NOT emerge from APC after entering it, will NOT drop time bomb, will drive APC (due to go to position)

	} else {
		printf("NOT editing/modifying game data (see sources).\n");
	}
	printf("\n");


	/******************************************************************************
	 *                                                                            *
	 *  Write modified game data to output file                                   *
	 *                                                                            *
	 ******************************************************************************/

	// Open output file
	printf("Opening output file '%s'...\n", outfile_name);
	FILE *outfile = fopen(outfile_name, "wb"); // write, binary mode
	if (outfile == NULL) {
		fprintf(stderr, "Error: failed to open output file '%s': %s\n", outfile_name, strerror(errno));
		return 1;
	}

	// Write contents of game data struct to output file
	printf("Writing output file '%s'...\n", outfile_name);
	size_t write_count = fwrite(&gamedata, 1, sizeof(GameData), outfile);
	if (write_count != sizeof(GameData)) {
		fprintf(stderr, "Error: failed to write output file '%s': wrote only %ld bytes out of %lu bytes\n", infile_name, write_count, sizeof(GameData));
		fclose(outfile);
		return 1;
	}

	// Close output file
	printf("Closing output file '%s'...\n", outfile_name);
	if (fclose(outfile) != 0) {
		fprintf(stderr, "Error: failed to close output file '%s': %s\n", outfile_name, strerror(errno));
		return 1;
	}
	printf("\n");


	/******************************************************************************
	 *                                                                            *
	 *  Generate CSV output (AFTER editing, reflects OUTPUT file contents)        *
	 *                                                                            *
	 ******************************************************************************/

	// CSV file name
	//char *csvfile_name;

	// Write MapWho array to CSV file
	asprintf(&csvfile_name, "%s_mapwho.csv", outfile_name);
	write_mapwho_to_csv(csvfile_name, gamedata.MapWho, TILES_COUNT_X, TILES_COUNT_Y);
	free(csvfile_name);

	// Write People array to CSV file
	asprintf(&csvfile_name, "%s_people.csv", outfile_name);
	write_people_to_csv(csvfile_name, gamedata.People, PEOPLE_COUNT, PEOPLE_GLOBAL_OFFSET, PEOPLE_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Vehicles array to CSV file
	asprintf(&csvfile_name, "%s_vehicles.csv", outfile_name);
	write_vehicles_to_csv(csvfile_name, gamedata.Vehicles, VEHICLES_COUNT, VEHICLES_GLOBAL_OFFSET, VEHICLES_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Objects array to CSV file
	asprintf(&csvfile_name, "%s_objects.csv", outfile_name);
	write_objects_to_csv(csvfile_name, gamedata.Objects, OBJECTS_COUNT, OBJECTS_GLOBAL_OFFSET, OBJECTS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Weapons array to CSV file
	asprintf(&csvfile_name, "%s_weapons.csv", outfile_name);
	write_weapons_to_csv(csvfile_name, gamedata.Weapons, WEAPONS_COUNT, WEAPONS_GLOBAL_OFFSET, WEAPONS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Effects array to CSV file
	asprintf(&csvfile_name, "%s_effects.csv", outfile_name);
	write_effects_to_csv(csvfile_name, gamedata.Effects, EFFECTS_COUNT, EFFECTS_GLOBAL_OFFSET, EFFECTS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Commands array to CSV file
	asprintf(&csvfile_name, "%s_commands.csv", outfile_name);
	write_commands_to_csv(csvfile_name, gamedata.Commands, COMMANDS_COUNT, COMMANDS_GLOBAL_OFFSET, COMMANDS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Worlds array to CSV file
	asprintf(&csvfile_name, "%s_worlds.csv", outfile_name);
	write_worlds_to_csv(csvfile_name, gamedata.Worlds, WORLDS_COUNT, WORLDS_GLOBAL_OFFSET, WORLDS_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write Objectives array to CSV file
	asprintf(&csvfile_name, "%s_objectives.csv", outfile_name);
	write_objectives_to_csv(csvfile_name, gamedata.Objectives, OBJECTIVES_COUNT, OBJECTIVES_GLOBAL_OFFSET, OBJECTIVES_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write CPObjectives array to CSV file
	asprintf(&csvfile_name, "%s_cpobjectives.csv", outfile_name);
	write_cpobjectives_to_csv(csvfile_name, gamedata.CPObjectives, CPOBJECTIVES_COUNT, CPOBJECTIVES_GLOBAL_OFFSET, CPOBJECTIVES_RELATIVE_OFFSET);
	free(csvfile_name);

	// Write structless GameData members to CSV file
	asprintf(&csvfile_name, "%s_structless.csv", outfile_name);
	write_structless_to_csv(csvfile_name, &gamedata);
	free(csvfile_name);


	/******************************************************************************
	 *                                                                            *
	 *  Debug output (debug builds only)                                          *
	 *                                                                            *
	 ******************************************************************************/

#ifdef DEBUG
	printf("\n");

	// Print game data struct sizes
	printf("Game data struct sizes:\n");
	//printf("MapWho:      %zu\n", sizeof(MapWho));
	printf("Thing:       %zu\n", sizeof(Thing));
	printf("Person:      %zu\n", sizeof(Person));
	printf("Vehicle:     %zu\n", sizeof(Vehicle));
	printf("Object:      %zu\n", sizeof(Object));
	printf("Weapon:      %zu\n", sizeof(Weapon));
	printf("Effect:      %zu\n", sizeof(Effect));
	printf("Command:     %zu\n", sizeof(Command));
	printf("World:       %zu\n", sizeof(World));
	//printf("MapInfo:     %zu\n", sizeof(MapInfo));
	printf("Objective:   %zu\n", sizeof(Objective));
	printf("CPObjective: %zu\n", sizeof(CPObjective));
	printf("GameData:    %zu\n", sizeof(GameData));
	printf("\n");

	// Print sizes of GameData array members
	printf("GameData array sizes:\n");
	printf("MapWho:       %zu\n", member_size(GameData, MapWho));
	printf("People:       %zu\n", member_size(GameData, People));
	printf("Vehicles:     %zu\n", member_size(GameData, Vehicles));
	printf("Objects:      %zu\n", member_size(GameData, Objects));
	printf("Weapons:      %zu\n", member_size(GameData, Weapons));
	printf("Effects:      %zu\n", member_size(GameData, Effects));
	printf("Commands:     %zu\n", member_size(GameData, Commands));
	printf("Worlds:       %zu\n", member_size(GameData, Worlds));
	printf("Objectives:   %zu\n", member_size(GameData, Objectives));
	printf("CPObjectives: %zu\n", member_size(GameData, CPObjectives));
	printf("\n");

	// Print offsets of GameData members
	printf("GameData member offsets:\n");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, Seed),         offsetof(GameData, Seed),         "uint16_t     Seed");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, PersonCount),  offsetof(GameData, PersonCount),  "uint16_t     PersonCount");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, Timer),        offsetof(GameData, Timer),        "uint16_t     Timer");
	//printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, MapWho),     offsetof(GameData, MapWho),       "MapWho       MapWho");
	//printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, MapWho),     offsetof(GameData, MapWho),       "uint16_t     MapWho[TILES_COUNT_Y][TILES_COUNT_X];");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, MapWho),       offsetof(GameData, MapWho),       "uint16_t     MapWho[TILES_COUNT_X * TILES_COUNT_Y];");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, RelOfsBase),   offsetof(GameData, RelOfsBase),   "uint16_t     RelOfsBase");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, People),       offsetof(GameData, People),       "Person       People[PEOPLE_COUNT]");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, Vehicles),     offsetof(GameData, Vehicles),     "Vehicle      Vehicles[VEHICLES_COUNT]");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, Objects),      offsetof(GameData, Objects),      "Object       Objects[OBJECTS_COUNT]");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, Weapons),      offsetof(GameData, Weapons),      "Weapon       Weapons[WEAPONS_COUNT]");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, Effects),      offsetof(GameData, Effects),      "Effect       Effects[EFFECTS_COUNT]");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, Commands),     offsetof(GameData, Commands),     "Command      Commands[COMMANDS_COUNT]");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, Worlds),       offsetof(GameData, Worlds),       "World        Worlds[WORLDS_COUNT]");
	//printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, MapInfo),    offsetof(GameData, MapInfo),      "MapInfo      MapInfos");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, MapNumber),    offsetof(GameData, MapNumber),    "uint16_t     MapNumber");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, LoBoundaryx),  offsetof(GameData, LoBoundaryx),  "uint16_t     LoBoundaryx");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, LoBoundaryy),  offsetof(GameData, LoBoundaryy),  "uint16_t     LoBoundaryy");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, HiBoundaryx),  offsetof(GameData, HiBoundaryx),  "uint16_t     HiBoundaryx");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, HiBoundaryy),  offsetof(GameData, HiBoundaryy),  "uint16_t     HiBoundaryy");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, Objectives),   offsetof(GameData, Objectives),   "Objective    Objectives[OBJECTIVES_COUNT]");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, CPCount),      offsetof(GameData, CPCount),      "uint8_t      CPCount");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, CPTeamSize),   offsetof(GameData, CPTeamSize),   "uint8_t      CPTeamSize");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, CPProcInt),    offsetof(GameData, CPProcInt),    "uint8_t      CPProcInt");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, CPLvlInit),    offsetof(GameData, CPLvlInit),    "uint8_t      CPLvlInit");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, CPIsBombTeam), offsetof(GameData, CPIsBombTeam), "uint8_t      CPIsBombTeam");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, CPIsPersTeam), offsetof(GameData, CPIsPersTeam), "uint8_t      CPIsPersTeam");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, CPFlags),      offsetof(GameData, CPFlags),      "uint8_t      CPFlags");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, CPWeapon),     offsetof(GameData, CPWeapon),     "uint8_t      CPWeapon");
	printf("/* %6zu 0x%05lx */  %s\n", offsetof(GameData, CPObjectives), offsetof(GameData, CPObjectives), "CPObjective  CPObjectives[CPOBJECTIVES_COUNT]");
	printf("/* %6zu 0x%05lx */  %s\n", sizeof(GameData),                 sizeof(GameData),                 "[ End of struct ]");
#endif


	/******************************************************************************
	 *                                                                            *
	 *  End of main                                                               *
	 *                                                                            *
	 ******************************************************************************/

	// Get home safely
	return 0;
}
