/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - Main                                                   *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/14/25                                                 *
 *                                                                            *
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "asprintf.h"
#include "gamedata.h"
#include "gdenums.h"
#include "csvoutput.h"
#include "mapwho.h"

int main(int argc, char *argv[]) {

	// Game data struct
	GameData gamedata;


	// Process command line
	if (argc != 3) {
		fprintf(stderr, "Usage:   %s INFILE OUTFILE\n", argv[0]);
		fprintf(stderr, "Example: %s GAMExx.DAT GAMExx.DAT_mod\n", argv[0]);
		return 2;
	}
	const char *infile_name = argv[1];
	const char *outfile_name = argv[2];


	// Open input file
	printf("Opening input file '%s'...\n", infile_name);
	FILE *infile = fopen(infile_name, "rb"); // read, binary mode
	if (infile == NULL) {
		fprintf(stderr, "Error: failed to open input file '%s': %s\n", infile_name, strerror(errno));
		return 1;
	}

	// Check input file size (to rule out incompatible input files, e.g. RNCed or Beta version)
	// Should be the most portable approach (https://stackoverflow.com/a/238609/1976617)
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


	// Editing/modification examples: make GAME01.DAT and GAME10.DAT more interesting
	if (strstr(infile_name, "GAME01.DAT") != NULL) {  // Western Europe

		printf("Modifying GAME01.DAT...\n");
		Vehicle vehicle = gamedata.Vehicles[0];       // Existing Vehicle
		Person person = gamedata.People[9];           // Existing Guard
		Weapon weapon = gamedata.Weapons[0];          // Existing Uzi (belongs to last guard at road)

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

		// Rebuild MapWho to account for added things
		rebuild_mapwho(&gamedata);

#ifdef DEBUG
		// TESTING: Command your own agents to be useful on their own
		gamedata.LoBoundaryx = 0;
		gamedata.LoBoundaryy = 0;
		gamedata.HiBoundaryx = 255;
		gamedata.HiBoundaryy = 255;
		Command command; memset(&command, 0, sizeof(Command)); size_t command_slot = 63;
		for (size_t i = 0; i <= 7; i++) {
			gamedata.People[i].NewState = PS_NEXT_COMMAND;
			gamedata.People[i].StartCommand = gamedata.People[i].Command = sizeof(Command) * command_slot;
		}
		command.Next = sizeof(Command) * (command_slot+1);
		command.GotoX = ((gamedata.People[0].Xpos >> 8) - 14) * 2;  // Goto 14 tiles north-west of starting point
		command.GotoY = (gamedata.People[0].Ypos >> 8) * 2;         // (more or less central court after bridge)
		command.State = CS_GOTO_POINT;
		gamedata.Commands[command_slot++] = command;
		for (size_t i = 0; i < PEOPLE_COUNT; i++) {
			if (gamedata.People[i].Unique != PU_GUARD)
				continue;
			command.Next = sizeof(Command) * (command_slot+1);
			command.GotoX = (gamedata.People[i].Xpos >> 8) * 2;     // Hunt down guards
			command.GotoY = (gamedata.People[i].Ypos >> 8) * 2;
			command.State = CS_GOTO_POINT;
			gamedata.Commands[command_slot++] = command;
		}
		/*memset(&command, 0, sizeof(Command));                     // End of command list
		command.State = CS_END_COMMANDS;
		gamedata.Commands[command_slot++] = command;*/
		gamedata.Commands[command_slot-1].Next = 456;               // Let's get that shiny black car (pre-existing command)
#endif

#ifdef DEBUG
		// TESTING: Macros GET_RELOFS_FOR_THING + GET_THING_FOR_RELOFS
		printf("Relative offset of gamedata.People[12]:   %u\n", GET_RELOFS_FOR_THING(&gamedata, &gamedata.People[12]));
		printf("Relative offset of gamedata.Vehicles[20]: %u\n", GET_RELOFS_FOR_THING(&gamedata, &gamedata.Vehicles[20]));
		Thing *t = GET_THING_FOR_RELOFS(&gamedata, 1106);   // Retrieved thing must match gamedata.People[12]
		printf("Thing.RelOfs:  %u, Thing.Xpos:  %u, Thing.Ypos:  %u\n", 1106, t->Xpos, t->Ypos);
		printf("Person.RelOfs: %u, Person.Xpos: %u, Person.Ypos: %u\n", (uint16_t)(PEOPLE_RELATIVE_OFFSET + sizeof(Person) * 12), gamedata.People[12].Xpos, gamedata.People[12].Ypos);
		Thing *t2 = GET_THING_FOR_RELOFS(&gamedata, 24394); // Retrieved thing must match gamedata.Vehicles[20]
		printf("Thing.RelOfs:   %u, Thing.Xpos:   %u, Thing.Ypos:   %u\n", 24394, t2->Xpos, t2->Ypos);
		printf("Vehicle.RelOfs: %u, Vehicle.Xpos: %u, Vehicle.Ypos: %u\n", (uint16_t)(VEHICLES_RELATIVE_OFFSET + sizeof(Vehicle) * 20), gamedata.Vehicles[20].Xpos, gamedata.Vehicles[20].Ypos);
#endif

	} else if (strstr(infile_name, "GAME10.DAT") != NULL) {  // Eastern Europe

		printf("Modifying GAME10.DAT...\n");
		Weapon weapon = gamedata.Weapons[1];                 // Existing Uzi
		size_t weapon_slot = 30;                             // Lots of free space
		for (size_t i = 0; i < sizeof(gamedata.People) / sizeof(gamedata.People[0]); i++) {                             // Power to the People
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

	} else if (strstr(infile_name, "GAME20.DAT") != NULL) {  // Scandinavia

		printf("Modifying GAME20.DAT...\n");
		size_t person_slot = 65;                             // Lots of free space
		for (size_t i = 8; i < 60; i++) {                    // Twice the civilians == twice the fun
			if (gamedata.People[i].Unique == PU_CIVILIAN) {
				Person person = gamedata.People[i];          // Two tiles variation in positioning
				person.Xpos += (rand() % (POS_PER_TILE * 2)) - POS_PER_TILE;
				person.Ypos += (rand() % (POS_PER_TILE * 2)) - POS_PER_TILE;
				person.Angle = rand() % 256;                 // Wander somewhere nice
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

		// Rebuild MapWho to account for added things
		rebuild_mapwho(&gamedata);

	} else {
		printf("Not modifying game data (see sources).\n");
	}
	printf("\n");


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


	// ----------------------------------------------------------------------------------------------------------------------


	// CSV file name
	char *csvfile_name;

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


	// ----------------------------------------------------------------------------------------------------------------------

#ifdef DEBUG
	printf("\n");

	// Print struct sizes
	printf("Struct sizes:\n");
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

	// Print offsets of GameData struct members
	printf("GameData offsets:\n");
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

	// ----------------------------------------------------------------------------------------------------------------------


	// Get home safely
	return 0;
}
