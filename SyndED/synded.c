#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "gamedata.h"

#define PA_OFFSET 32776                // Offset of People array in GAMExx.DAT
#define PA_LENGTH 256                  // Number of items in People array


int main(int argc, char *argv[]) {

	// Check command line
	if (argc != 2) {
		fprintf(stderr, "Usage: %s GAMExx.DAT\n", argv[0]);
		return 1;
	}

	// Create People array (256 Person structs)
	Person people[PA_LENGTH];

	// Open file specified on command line
	char *file_name = argv[1];
	printf("Opening file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "r+b"); // read/write binary mode
	if (!file) {
		fprintf(stderr, "Failed to open file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Seek to offset of People array in file
	printf("Seeking in file '%s'...\n", file_name);
	if (fseek(file, PA_OFFSET, SEEK_SET) != 0 ) {
		fprintf(stderr, "Failed to seek in file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read data from file into array
	printf("Reading from file '%s'...\n", file_name);
	size_t read_count = fread(people, sizeof(Person), PA_LENGTH, file);
	if (read_count != PA_LENGTH) {
		fprintf(stderr, "Error reading from file '%s': %s\n", file_name, strerror(errno));
		fclose(file);
		return 1;
	}


	// Print fields of each Person in People array
	printf("\n");
	size_t defined_people = 0;
	for (size_t i = 0; i < PA_LENGTH; ++i) {
		Person* person = &people[i];
		if ((person->Model == 0) && (person->Unique == 0)) {
			defined_people = i;
			break; // End of defined People reached
		}
		printf("Person %zu:\n", i+1);
		printf("  Child: %u, Parent: %u\n", person->Child, person->Parent);
		printf("  Xpos: %u, Ypos: %u, Zpos: %u\n", person->Xpos, person->Ypos, person->Zpos);
		printf("  Status: %u, Affect: %u\n", person->Status, person->Affect);
		printf("  Unknown: %u, %u\n", person->Unknown[0], person->Unknown[1]);
		printf("  BaseFrame: %u, Frame: %u, OldFrame: %u\n", person->BaseFrame, person->Frame, person->OldFrame);
		printf("  Life: %u\n", person->Life);
		printf("  WhoShotMe: %u\n", person->WhoShotMe);
		printf("  Model: %u, State: %u\n", person->Model, person->State);
		printf("  Angle: %u, ZAngle: %u\n", person->Angle, person->ZAngle);
		printf("  Unique: %u\n", person->Unique);
		printf("  Hugdistance1: %u, Hugdistance2: %u\n", person->Hugdistance1, person->Hugdistance2);
		printf("  Persuaded: %u\n", person->Persuaded);
		printf("  ChildHeld: %u, ParentHeld: %u\n", person->ChildHeld, person->ParentHeld);
		printf("  Command: %u, StartCommand: %u\n", person->Command, person->StartCommand);
		printf("  Target: %u, Data: %u\n", person->Target, person->Data);
		printf("  GotoX: %u, GotoY: %u, GotoZ: %u\n", person->GotoX, person->GotoY, person->GotoZ);
		printf("  LastXpos: %u, LastYpos: %u, HugGotoZ: %u\n", person->LastXpos, person->LastYpos, person->HugGotoZ);
		printf("  ChildWeapon: %u, Equipment: %u\n", person->ChildWeapon, person->Equipment);
		printf("  ParentRank: %u, RankPosition: %u\n", person->ParentRank, person->RankPosition);
		printf("  WeaponHolding: %u, WeaponInUse: %u\n", person->WeaponHolding, person->WeaponInUse);
		printf("  Level1Base: %u, Level1Balance: %u, Level1True: %u, Level1Fixed: %u\n", person->Level1Base, person->Level1Balance, person->Level1True, person->Level1Fixed);
		printf("  Level2Base: %u, Level2Balance: %u, Level2True: %u, Level2Fixed: %u\n", person->Level2Base, person->Level2Balance, person->Level2True, person->Level2Fixed);
		printf("  Level3Base: %u, Level3Balance: %u, Level3True: %u, Level3Fixed: %u\n", person->Level3Base, person->Level3Balance, person->Level3True, person->Level3Fixed);
		printf("  LevelRecovery: %u\n", person->LevelRecovery);
		printf("  Speed: %u, MaxSpeed: %u, BaseSpeed: %u\n", person->Speed, person->MaxSpeed, person->BaseSpeed);
		printf("  OldState: %u, NewState: %u\n", person->OldState, person->NewState);
		printf("  HugChangeDir: %u, HugStartAngle: %u, HitAngle: %u\n", person->HugChangeDir, person->HugStartAngle, person->HitAngle);
		printf("\n");
	}


	// Print struct sizes
	printf("MapWho:      %zu\n", sizeof(MapWho));
	printf("Person:      %zu\n", sizeof(Person));
	printf("Vehicle:     %zu\n", sizeof(Vehicle));
	printf("Object:      %zu\n", sizeof(Object));
	printf("Weapon:      %zu\n", sizeof(Weapon));
	printf("Effect:      %zu\n", sizeof(Effect));
	printf("Command:     %zu\n", sizeof(Command));
	printf("World:       %zu\n", sizeof(World));
	printf("MapInfo:     %zu\n", sizeof(MapInfo));
	printf("Objective:   %zu\n", sizeof(Objective));
	printf("CPObjective: %zu\n", sizeof(CPObjective));
	printf("GameData:    %zu\n", sizeof(GameData));


	// Example modification: add more people!
	/*Person person;
	person = people[defined_people-1];
	person.Parent = 0; person.Xpos += 100; person.Ypos += 100; person.Unique = 2;
	people[defined_people] = person;
	person.Parent = 0; person.Xpos += 100; person.Ypos += 100; person.Unique = 8;
	people[defined_people+1] = person;
	person.Parent = 0; person.Xpos += 100; person.Ypos += 100; person.Unique = 1;
	people[defined_people+2] = person;
	person.Parent = 0; person.Xpos += 100; person.Ypos += 100; person.Unique = 1;
	people[defined_people+3] = person;
	person.Parent = 0; person.Xpos += 100; person.Ypos += 100; person.Unique = 1;
	people[defined_people+4] = person;*/


	// Seek to offset of People array in file
	/*printf("Seeking in file '%s'...\n", file_name);
	if (fseek(file, PA_OFFSET, SEEK_SET) != 0 ) {
		fprintf(stderr, "Failed to seek in file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write modified array to file
	printf("Writing to file '%s'...\n", file_name);
	size_t write_count = fwrite(people, sizeof(Person), PA_LENGTH, file);
	if (write_count != PA_LENGTH) {
		fprintf(stderr, "Error writing to file '%s': %s\n", file_name, strerror(errno));
		fclose(file);
		return 1;
	}

	// Close file and we're done
	fclose(file);
	printf("Successfully updated file '%s'.\n", file_name);*/
	return 0;
}
