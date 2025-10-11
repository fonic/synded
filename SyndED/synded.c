#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "gamedata.h"
#include "gdenums.h"
#include "csvoutput.h"

int main(int argc, char *argv[]) {

	// Game data struct
	GameData gamedata;


	// Process command line
	if (argc != 3) {
		fprintf(stderr, "Usage: %s INFILE OUTFILE\n", argv[0]);
		fprintf(stderr, "Usage: %s GAMExx.DAT GAMExx.DAT_modified\n", argv[0]);
		return 2;
	}
	const char *infile_name = argv[1];
	const char *outfile_name = argv[2];


	// Open input file
	printf("Opening input file '%s'...\n", infile_name);
	FILE *infile = fopen(infile_name, "rb"); // read, binary mode
	if (!infile) {
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
	long size = ftell(infile);
	if (size == -1) {
		fprintf(stderr, "Error: failed to determine size of input file '%s': %s\n", infile_name, strerror(errno));
		return 1;
	}
	if (size != sizeof(GameData)) {
		fprintf(stderr, "Error: incorrect size of input file '%s': got %ld bytes, expected %lu bytes\n", infile_name, size, sizeof(GameData));
		return 1;
	}
	if (fseek(infile, 0, SEEK_SET) != 0) { // Important, need to seek back to start!
		fprintf(stderr, "Error: failed to seek to start of input file '%s': %s\n", infile_name, strerror(errno));
		return 1;
	}

	// Read contents of input file into game data struct
	printf("Reading input file '%s'...\n", infile_name);
	size_t read_count = fread(&gamedata, sizeof(GameData), 1, infile);
	if (read_count != 1) {
		fprintf(stderr, "Error: error reading input file '%s': %s\n", infile_name, strerror(errno));
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


	// Edit/modify example: make GAME01.DAT and GAME10.DAT more interesting
	if (strstr(infile_name, "GAME01.DAT") != NULL) {
		printf("Modifying GAME01.DAT...\n");
		Vehicle vehicle = gamedata.Vehicles[0]; // existing Vehicle
		Person person = gamedata.People[9];     // existing Guard
		Weapon weapon = gamedata.Weapons[0];    // existing Uzi (belongs to last guard at road)

		size_t vehicle_slot = 20; size_t weapon_slot = 20; size_t person_slot = 20;  // lots of free space

		weapon.State = WS_MINIGUN; weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * person_slot;
		gamedata.Weapons[weapon_slot] = weapon;
		person.Xpos = vehicle.Xpos + 50; person.Ypos = vehicle.Ypos + 500; person.BaseFrame = PB_MAN_JACKET; person.Life = 8;
		person.State = person.NewState = 0; person.Angle = 0; person.Parent = person.ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
		gamedata.People[person_slot] = person;
		gamedata.MapWho[POSITION_TO_MAPWHO_OFFSET(person.Xpos, person.Ypos)] = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * person_slot;
		weapon_slot++; person_slot++;

		vehicle.Xpos -= 500; vehicle.State = VS_POLICECAR; vehicle.Life = 60; vehicle.MaxSpeed = 100;
		gamedata.Vehicles[vehicle_slot] = vehicle;
		gamedata.MapWho[POSITION_TO_MAPWHO_OFFSET(vehicle.Xpos, vehicle.Ypos)] = VEHICLES_RELATIVE_OFFSET + sizeof(Vehicle) * vehicle_slot;
		vehicle_slot++;
		weapon.State = WS_MINIGUN; weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * person_slot;
		gamedata.Weapons[weapon_slot] = weapon;
		person.Xpos = vehicle.Xpos + 50; person.Ypos = vehicle.Ypos + 500; person.BaseFrame = PB_POLICE; person.Life = 8;
		person.State = person.NewState = 0; person.Angle = 0; person.Parent = person.ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
		gamedata.People[person_slot] = person;
		gamedata.MapWho[POSITION_TO_MAPWHO_OFFSET(person.Xpos, person.Ypos)] = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * person_slot;
		weapon_slot++; person_slot++;

		vehicle.Xpos -= 500; vehicle.State = VS_APC; vehicle.Life = 90; vehicle.MaxSpeed = 50;
		gamedata.Vehicles[vehicle_slot] = vehicle;
		gamedata.MapWho[POSITION_TO_MAPWHO_OFFSET(vehicle.Xpos, vehicle.Ypos)] = VEHICLES_RELATIVE_OFFSET + sizeof(Vehicle)*vehicle_slot;
		vehicle_slot++;
		weapon.State = WS_MINIGUN; weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * person_slot;
		gamedata.Weapons[weapon_slot] = weapon;
		person.Xpos = vehicle.Xpos + 50; person.Ypos = vehicle.Ypos + 500; person.BaseFrame = PB_SOLDIER; person.Life = 8;
		person.State = person.NewState = 0; person.Angle = 0; person.Parent = person.ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
		gamedata.People[person_slot] = person;
		gamedata.MapWho[POSITION_TO_MAPWHO_OFFSET(person.Xpos, person.Ypos)] = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * person_slot;
		weapon_slot++; person_slot++;
	} else if (strstr(infile_name, "GAME10.DAT") != NULL) {
		printf("Modifying GAME10.DAT...\n");
		Weapon weapon = gamedata.Weapons[1];  // existing Uzi
		size_t weapon_slot = 30;              // lots of free space
		for (size_t i = 0; i < sizeof(gamedata.People) / sizeof(gamedata.People[0]); i++) {                             // power to the people
			if (gamedata.People[i].BaseFrame == PB_WOMAN_REDHEAD || gamedata.People[i].BaseFrame == PB_WOMAN_BLONDE) {  // women get Uzis
				gamedata.People[i].Unique = PU_GUARD;
				gamedata.People[i].Life = 10;
				gamedata.People[i].Parent = gamedata.People[i].ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
				weapon.State = WS_UZI;
				weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * i;
				gamedata.Weapons[weapon_slot++] = weapon;
			} else if (gamedata.People[i].BaseFrame == PB_MAN_SUIT || gamedata.People[i].BaseFrame == PB_MAN_JACKET) {  // men get Shotguns
				gamedata.People[i].Unique = PU_GUARD;
				gamedata.People[i].Life = 10;
				gamedata.People[i].Parent = gamedata.People[i].ChildWeapon = WEAPONS_RELATIVE_OFFSET + sizeof(Weapon) * weapon_slot;
				weapon.State = WS_SHOTGUN;
				weapon.ParentWeapon = weapon.WhoOwnsWeapon = PEOPLE_RELATIVE_OFFSET + sizeof(Person) * i;
				gamedata.Weapons[weapon_slot++] = weapon;
			}
		}
	} else {
		printf("Not modifying game data (see sources).\n");
	}
	printf("\n");


	// Open output file
	printf("Opening output file '%s'...\n", outfile_name);
	FILE *outfile = fopen(outfile_name, "wb"); // write, binary mode
	if (!outfile) {
		fprintf(stderr, "Error: failed to open output file '%s': %s\n", outfile_name, strerror(errno));
		return 1;
	}

	// Write contents of game data struct to output file
	printf("Writing output file '%s'...\n", outfile_name);
	size_t write_count = fwrite(&gamedata, sizeof(GameData), 1, outfile);
	if (write_count != 1) {
		fprintf(stderr, "Error: failed to write output file '%s': %s\n", outfile_name, strerror(errno));
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


	// ----------------------------------------------------------------------------------------------------------------------


	// Print struct sizes
	printf("Struct sizes:\n");
	//printf("MapWho:      %zu\n", sizeof(MapWho));
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
	size_t offset = 0;
	printf("GameData offsets:\n");
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     Seed");                                    offset += sizeof(gamedata.Seed);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     PersonCount");                             offset += sizeof(gamedata.PersonCount);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     Timer");                                   offset += sizeof(gamedata.Timer);
	//printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "MapWho       MapWho");                                  offset += sizeof(gamedata.MapWho);
	//printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     MapWho[TILES_COUNT_Y][TILES_COUNT_X];");   offset += sizeof(gamedata.MapWho);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     MapWho[TILES_COUNT_X * TILES_COUNT_Y];");  offset += sizeof(gamedata.MapWho);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     Unknown");                                 offset += sizeof(gamedata.Unknown);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "Person       People[PEOPLE_COUNT]");                    offset += sizeof(gamedata.People);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "Vehicle      Vehicles[VEHICLES_COUNT]");                offset += sizeof(gamedata.Vehicles);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "Object       Objects[OBJECTS_COUNT]");                  offset += sizeof(gamedata.Objects);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "Weapon       Weapons[WEAPONS_COUNT]");                  offset += sizeof(gamedata.Weapons);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "Effect       Effects[EFFECTS_COUNT]");                  offset += sizeof(gamedata.Effects);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "Command      Commands[COMMANDS_COUNT]");                offset += sizeof(gamedata.Commands);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "World        Worlds[WORLDS_COUNT]");                    offset += sizeof(gamedata.Worlds);
	//printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "MapInfo      MapInfos");                                offset += sizeof(gamedata.MapInfos);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     MapNumber");                               offset += sizeof(gamedata.MapNumber);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     LoBoundaryx");                             offset += sizeof(gamedata.LoBoundaryx);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     LoBoundaryy");                             offset += sizeof(gamedata.LoBoundaryy);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     HiBoundaryx");                             offset += sizeof(gamedata.HiBoundaryx);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint16_t     HiBoundaryy");                             offset += sizeof(gamedata.HiBoundaryy);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "Objective    Objectives[OBJECTIVES_COUNT]");            offset += sizeof(gamedata.Objectives);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint8_t      CPCount");                                 offset += sizeof(gamedata.CPCount);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint8_t      CPTeamSize");                              offset += sizeof(gamedata.CPTeamSize);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint8_t      CPProcInt");                               offset += sizeof(gamedata.CPProcInt);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint8_t      CPLvlInit");                               offset += sizeof(gamedata.CPLvlInit);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint8_t      CPIsBombTeam");                            offset += sizeof(gamedata.CPIsBombTeam);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint8_t      CPIsPersTeam");                            offset += sizeof(gamedata.CPIsPersTeam);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint8_t      CPFlags");                                 offset += sizeof(gamedata.CPFlags);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "uint8_t      CPWeapon");                                offset += sizeof(gamedata.CPWeapon);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "CPObjective  CPObjectives[CPOBJECTIVES_COUNT]");        offset += sizeof(gamedata.CPObjectives);
	printf("/* %6zu 0x%05lx */  %s\n", offset, offset, "[ End of struct ]");
	printf("\n");


	// ----------------------------------------------------------------------------------------------------------------------


	// Get home safely
	return 0;
}
