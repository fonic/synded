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
		fprintf(stderr, "Failed to open input file '%s': %s\n", infile_name, strerror(errno));
		return 1;
	}

	// Read contents of input file into game data struct
	printf("Reading input file '%s'...\n", infile_name);
	size_t read_count = fread(&gamedata, sizeof(GameData), 1, infile);
	if (read_count != 1) {
		fprintf(stderr, "Error reading input file '%s': %s\n", infile_name, strerror(errno));
		fclose(infile);
		return 1;
	}

	// Close input file
	printf("Closing input file '%s'...\n", infile_name);
	if (fclose(infile) != 0) {
		fprintf(stderr, "Failed to close input file '%s': %s\n", infile_name, strerror(errno));
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

		weapon.State = WS_MINIGUN; weapon.ParentWeapon = weapon.WhoOwnsWeapon = 2 + sizeof(person) * person_slot;
		gamedata.Weapons[weapon_slot] = weapon;
		person.Xpos = vehicle.Xpos + 50; person.Ypos = vehicle.Ypos + 500; person.BaseFrame = PB_SOLDIER; person.Life = 8;
		person.State = person.NewState = 0;person.Angle = 0; person.ChildWeapon = 38242 + sizeof(weapon) * weapon_slot;
		gamedata.People[person_slot] = person;
		gamedata.MapWho.ObjOfs[(person.Ypos >> 8) * 128 + (person.Xpos >> 8)] = 2 + sizeof(person) * person_slot;
		weapon_slot++; person_slot++;

		vehicle.Xpos -= 500;
		gamedata.Vehicles[vehicle_slot] = vehicle;
		gamedata.MapWho.ObjOfs[(vehicle.Ypos >> 8) * 128 + (vehicle.Xpos >> 8)] = 23554 + sizeof(vehicle) * vehicle_slot;
		vehicle_slot++;

		weapon.State = WS_MINIGUN; weapon.ParentWeapon = weapon.WhoOwnsWeapon = 2 + sizeof(person) * person_slot;
		gamedata.Weapons[weapon_slot] = weapon;
		person.Xpos = vehicle.Xpos + 50; person.Ypos = vehicle.Ypos + 500; person.BaseFrame = PB_SOLDIER; person.Life = 8;
		person.State = person.NewState = 0;person.Angle = 0; person.ChildWeapon = 38242 + sizeof(weapon) * weapon_slot;
		gamedata.People[person_slot] = person;
		gamedata.MapWho.ObjOfs[(person.Ypos >> 8) * 128 + (person.Xpos >> 8)] = 2 + sizeof(person) * person_slot;
		weapon_slot++; person_slot++;

		vehicle.Xpos -= 500;
		gamedata.Vehicles[vehicle_slot] = vehicle;
		gamedata.MapWho.ObjOfs[(vehicle.Ypos >> 8) * 128 + (vehicle.Xpos >> 8)] = 23554 + sizeof(vehicle)*vehicle_slot;
		vehicle_slot++;

		weapon.State = WS_MINIGUN; weapon.ParentWeapon = weapon.WhoOwnsWeapon = 2 + sizeof(person) * person_slot;
		gamedata.Weapons[weapon_slot] = weapon;
		person.Xpos = vehicle.Xpos + 50; person.Ypos = vehicle.Ypos + 500; person.BaseFrame = PB_SOLDIER; person.Life = 8;
		person.State = person.NewState = 0;person.Angle = 0; person.ChildWeapon = 38242 + sizeof(weapon) * weapon_slot;
		gamedata.People[person_slot] = person;
		gamedata.MapWho.ObjOfs[(person.Ypos >> 8) * 128 + (person.Xpos >> 8)] = 2 + sizeof(person) * person_slot;
		weapon_slot++; person_slot++;
	} else if (strstr(infile_name, "GAME10.DAT") != NULL) {
		printf("Modifying GAME10.DAT...\n");
		Weapon weapon = gamedata.Weapons[1];  // existing Uzi
		size_t weapon_slot = 30;              // lots of free space
		for (size_t i = 0; i < sizeof(gamedata.People) / sizeof(gamedata.People[0]); i++) {
			if (gamedata.People[i].BaseFrame == PB_WOMAN_REDHEAD || gamedata.People[i].BaseFrame == PB_WOMAN_BLONDE) {  // women get Uzis
				gamedata.People[i].Unique = PU_GUARD;
				gamedata.People[i].Life = 8;
				gamedata.People[i].ChildWeapon = 38242 + sizeof(weapon) * weapon_slot;
				weapon.State = WS_UZI;
				weapon.ParentWeapon = weapon.WhoOwnsWeapon = 2 + sizeof(gamedata.People[0]) * i;
				gamedata.Weapons[weapon_slot++] = weapon;
			} else if (gamedata.People[i].BaseFrame == PB_MAN_SUIT || gamedata.People[i].BaseFrame == PB_MAN_JACKET) {  // men get Shotguns
				gamedata.People[i].Unique = PU_GUARD;
				gamedata.People[i].Life = 8;
				gamedata.People[i].ChildWeapon = 38242 + sizeof(weapon) * weapon_slot;
				weapon.State = WS_SHOTGUN;
				weapon.ParentWeapon = weapon.WhoOwnsWeapon = 2 + sizeof(gamedata.People[0]) * i;
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
		fprintf(stderr, "Failed to open output file '%s': %s\n", outfile_name, strerror(errno));
		return 1;
	}

	// Write contents of game data struct to output file
	printf("Writing output file '%s'...\n", outfile_name);
	size_t write_count = fwrite(&gamedata, sizeof(GameData), 1, outfile);
	if (write_count != 1) {
		fprintf(stderr, "Error writing output file '%s': %s\n", outfile_name, strerror(errno));
		fclose(outfile);
		return 1;
	}

	// Close output file
	printf("Closing output file '%s'...\n", outfile_name);
	if (fclose(outfile) != 0) {
		fprintf(stderr, "Failed to close output file '%s': %s\n", outfile_name, strerror(errno));
		return 1;
	}
	printf("\n");


	// ----------------------------------------------------------------------------------------------------------------------


	// CSV file name
	char *csvfile_name;

	// Write MapWho array to CSV file
	asprintf(&csvfile_name, "%s_mapwho.csv", infile_name);
	write_mapwho_to_csv(csvfile_name, &gamedata.MapWho, 128, 128);
	free(csvfile_name);

	// Write People array to CSV file
	asprintf(&csvfile_name, "%s_people.csv", infile_name);
	write_people_to_csv(csvfile_name, gamedata.People, sizeof(gamedata.People) / sizeof(gamedata.People[0]), 32776);
	free(csvfile_name);

	// Write Vehicles array to CSV file
	asprintf(&csvfile_name, "%s_vehicles.csv", infile_name);
	write_vehicles_to_csv(csvfile_name, gamedata.Vehicles, sizeof(gamedata.Vehicles) / sizeof(gamedata.Vehicles[0]), 56328);
	free(csvfile_name);

	// Write Objects array to CSV file
	asprintf(&csvfile_name, "%s_objects.csv", infile_name);
	write_objects_to_csv(csvfile_name, gamedata.Objects, sizeof(gamedata.Objects) / sizeof(gamedata.Objects[0]), 59016);
	free(csvfile_name);

	// Write Weapons array to CSV file
	asprintf(&csvfile_name, "%s_weapons.csv", infile_name);
	write_weapons_to_csv(csvfile_name, gamedata.Weapons, sizeof(gamedata.Weapons) / sizeof(gamedata.Weapons[0]), 71016);
	free(csvfile_name);

	// Write Effects array to CSV file
	asprintf(&csvfile_name, "%s_effects.csv", infile_name);
	write_effects_to_csv(csvfile_name, gamedata.Effects, sizeof(gamedata.Effects) / sizeof(gamedata.Effects[0]), 89448);
	free(csvfile_name);

	// Write Commands array to CSV file
	asprintf(&csvfile_name, "%s_commands.csv", infile_name);
	write_commands_to_csv(csvfile_name, gamedata.Commands, sizeof(gamedata.Commands) / sizeof(gamedata.Commands[0]), 97128);
	free(csvfile_name);

	// Write Worlds array to CSV file
	asprintf(&csvfile_name, "%s_worlds.csv", infile_name);
	write_worlds_to_csv(csvfile_name, gamedata.Worlds, sizeof(gamedata.Worlds) / sizeof(gamedata.Worlds[0]), 113512);
	free(csvfile_name);

	// Write Objectives array to CSV file
	asprintf(&csvfile_name, "%s_objectives.csv", infile_name);
	write_objectives_to_csv(csvfile_name, gamedata.Objectives, sizeof(gamedata.Objectives) / sizeof(gamedata.Objectives[0]), 113970);
	free(csvfile_name);

	// Write CPObjectives array to CSV file
	asprintf(&csvfile_name, "%s_cpobjectives.csv", infile_name);
	write_cpobjectives_to_csv(csvfile_name, gamedata.CPObjectives, sizeof(gamedata.CPObjectives) / sizeof(gamedata.CPObjectives[0]), 114090);
	free(csvfile_name);

	// Write structless GameData members to CSV file
	asprintf(&csvfile_name, "%s_structless.csv", infile_name);
	write_structless_to_csv(csvfile_name, &gamedata);
	free(csvfile_name);
	printf("\n");


	// ----------------------------------------------------------------------------------------------------------------------


	// Print struct sizes
	printf("Struct sizes:\n");
	printf("MapWho:      %zu\n", sizeof(MapWho));
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
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint16_t     Seed");               offset += sizeof(gamedata.Seed);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint16_t     PersonCount");        offset += sizeof(gamedata.PersonCount);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint16_t     Timer");              offset += sizeof(gamedata.Timer);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "MapWho       MapWho");             offset += sizeof(gamedata.MapWho);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint16_t     Unknown");            offset += sizeof(gamedata.Unknown);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "Person       People[256]");        offset += sizeof(gamedata.People);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "Vehicle      Vehicles[64]");       offset += sizeof(gamedata.Vehicles);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "Object       Objects[400]");       offset += sizeof(gamedata.Objects);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "Weapon       Weapons[512]");       offset += sizeof(gamedata.Weapons);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "Effect       Effects[256]");       offset += sizeof(gamedata.Effects);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "Command      Commands[2048]");     offset += sizeof(gamedata.Commands);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "World        Worlds[32]");         offset += sizeof(gamedata.Worlds);
	//printf("/* %6zu 0x%05x */  %s\n", offset, offset, "MapInfo      MapInfos");           offset += sizeof(gamedata.MapInfos);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint16_t     MapNumber");          offset += sizeof(gamedata.MapNumber);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint16_t     LoBoundaryx");        offset += sizeof(gamedata.LoBoundaryx);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint16_t     LoBoundaryy");        offset += sizeof(gamedata.LoBoundaryy);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint16_t     HiBoundaryx");        offset += sizeof(gamedata.HiBoundaryx);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint16_t     HiBoundaryy");        offset += sizeof(gamedata.HiBoundaryy);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "Objective    Objectives[8]");      offset += sizeof(gamedata.Objectives);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint8_t      CPCount");            offset += sizeof(gamedata.CPCount);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint8_t      CPTeamSize");         offset += sizeof(gamedata.CPTeamSize);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint8_t      CPProcInt");          offset += sizeof(gamedata.CPProcInt);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint8_t      CPLvlInit");          offset += sizeof(gamedata.CPLvlInit);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint8_t      CPIsBombTeam");       offset += sizeof(gamedata.CPIsBombTeam);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint8_t      CPIsPersTeam");       offset += sizeof(gamedata.CPIsPersTeam);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint8_t      CPFlags");            offset += sizeof(gamedata.CPFlags);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "uint8_t      CPWeapon");           offset += sizeof(gamedata.CPWeapon);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "CPObjective  CPObjectives[128]");  offset += sizeof(gamedata.CPObjectives);
	printf("/* %6zu 0x%05x */  %s\n", offset, offset, "[ End of struct ]");
	printf("\n");


	// ----------------------------------------------------------------------------------------------------------------------


	// Get home safely
	return 0;
}
