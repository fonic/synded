/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - CSV Input                                              *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/30/25                                                 *
 *                                                                            *
 ******************************************************************************/

#include "csvinput.h"  // related header

#include <stdio.h>     // printf, fprintf, fopen, fclose, stderr, FILE, fscanf, fgets, ferror, sscanf
#include <string.h>    // strerror, strnlen
#include <errno.h>     // errno

int read_mapwho_from_csv(const char *file_name, uint16_t mapwho[], const size_t count_x, const size_t count_y) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	char line[1024]; size_t llen, lpos; int assigned, consumed;  // Maximum expected line length: (4+1) + 128 * (5+1) + 1 ('Y127' + ',' + uint16_t + ',' -or- '\n' + '\0') == 774
	fgets(line, sizeof(line), file);                             // Skip first line (contains column indices)
	for (size_t y = 0; y < count_y; y++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		lpos = 0;                                                // Point sscanf to first column in line
		sscanf(line + lpos, "%*[^,]%n", &consumed);              // Skip first column (contains row index)
		if (consumed <= 0) {                                     // Not assigning here, thus resorting to check consumed
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (consumed: %d, lpos: %zu, llen: %lu): '%s'\n", file_name, y+2, consumed, lpos, llen, line);
			fclose(file);
			return 1;
		}
		lpos += consumed;                                        // Point sscanf to next column in line

		for (size_t x = 0; x < count_x; x++) {
			if (lpos >= llen) {
				fprintf(stderr, "Failed to parse line from CSV file '%s': reached end of line %zu prematurely, expected further contents (lpos: %zu, llen: %lu): '%s'\n", file_name, y+2, lpos, llen, line);
				fclose(file);
				return 1;
			}
			assigned = sscanf(line + lpos, ",%hu%n", &mapwho[(y * count_x) + x], &consumed);
			if (assigned != 1) {
				fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, lpos: %zu, llen: %lu): '%s'\n", file_name, y+2, assigned, consumed, lpos, llen, line);
				fclose(file);
				return 1;
			}
			lpos += consumed;                                    // Point sscanf to next column in line
		}
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_people_from_csv(const char *file_name, Person people[], const size_t count) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	Person person;
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		assigned = sscanf(line,
						"%*[^,],"  // Index
						"%*[^,],"  // GloOfs
						"%*[^,],"  // RelOfs
						"%hu,"     // Child
						"%hu,"     // Parent
						"%hd,"     // Xpos
						"%hd,"     // Ypos
						"%hd,"     // Zpos
						"%*[^,],"  // Xtile
						"%*[^,],"  // Ytile
						"%hu,"     // Status
						"%*[^,],"  // Status_S
						"%hu,"     // Affect
						"%*[^,],"  // Affect_S
						"%hu,"     // BaseFrame
						"%*[^,],"  // BaseFrame_S
						"%hu,"     // Frame
						"%hu,"     // OldFrame
						"%hu,"     // Life
						"%hu,"     // WhoShotMe
						"%hhu,"    // Model
						"%*[^,],"  // Model_S
						"%hhu,"    // State
						"%*[^,],"  // State_S
						"%hhu,"    // Angle
						"%*[^,],"  // Angle_S
						"%hhu,"    // ZAngle
						"%hu,"     // Unique
						"%*[^,],"  // Unique_S
						"%hu,"     // HugDistance
						"%hu,"     // Persuaded
						"%hu,"     // ChildHeld
						"%hu,"     // ParentHeld
						"%hu,"     // Command
						"%hu,"     // StartCommand
						"%hu,"     // Target
						"%hu,"     // Data
						"%hd,"     // GotoX
						"%hd,"     // GotoY
						"%hd,"     // GotoZ
						"%hd,"     // LastXpos
						"%hd,"     // LastYpos
						"%hu,"     // HugGotoZ
						"%hu,"     // ChildWeapon
						"%hu,"     // Equipment
						"%hu,"     // ParentRank
						"%hu,"     // RankPosition
						"%hu,"     // Count
						"%hu,"     // WeaponHolding
						"%hhu,"    // WeaponInUse
						"%hhu,"    // Level1Base
						"%hhu,"    // Level1Balance
						"%hhu,"    // Level1True
						"%hhu,"    // Level1Fixed
						"%hhu,"    // Level2Base
						"%hhu,"    // Level2Balance
						"%hhu,"    // Level2True
						"%hhu,"    // Level2Fixed
						"%hhu,"    // Level3Base
						"%hhu,"    // Level3Balance
						"%hhu,"    // Level3True
						"%hhu,"    // Level3Fixed
						"%hhu,"    // LevelRecovery
						"%hhu,"    // Speed
						"%hhu,"    // MaxSpeed
						"%hhu,"    // BaseSpeed
						"%hhu,"    // OldState
						"%*[^,],"  // OldState_S
						"%hhu,"    // NewState
						"%*[^,],"  // NewState_S
						"%hhu,"    // HugChangeDir
						"%hhu,"    // HugStartAngle
						"%hhu"     // HitAngle
						"%n",
						&person.Child,
						&person.Parent,
						&person.Xpos,
						&person.Ypos,
						&person.Zpos,
						&person.Status,
						&person.Affect,
						&person.BaseFrame,
						&person.Frame,
						&person.OldFrame,
						&person.Life,
						&person.WhoShotMe,
						&person.Model,
						&person.State,
						&person.Angle,
						&person.ZAngle,
						&person.Unique,
						&person.HugDistance,
						&person.Persuaded,
						&person.ChildHeld,
						&person.ParentHeld,
						&person.Command,
						&person.StartCommand,
						&person.Target,
						&person.Data,
						&person.GotoX,
						&person.GotoY,
						&person.GotoZ,
						&person.LastXpos,
						&person.LastYpos,
						&person.HugGotoZ,
						&person.ChildWeapon,
						&person.Equipment,
						&person.ParentRank,
						&person.RankPosition,
						&person.Count,
						&person.WeaponHolding,
						&person.WeaponInUse,
						&person.Level1Base,
						&person.Level1Balance,
						&person.Level1True,
						&person.Level1Fixed,
						&person.Level2Base,
						&person.Level2Balance,
						&person.Level2True,
						&person.Level2Fixed,
						&person.Level3Base,
						&person.Level3Balance,
						&person.Level3True,
						&person.Level3Fixed,
						&person.LevelRecovery,
						&person.Speed,
						&person.MaxSpeed,
						&person.BaseSpeed,
						&person.OldState,
						&person.NewState,
						&person.HugChangeDir,
						&person.HugStartAngle,
						&person.HitAngle,
						&consumed);
		if (assigned != 59 || (size_t)consumed != llen) {        // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, i+2, assigned, consumed, llen, line);
			fclose(file);
			return 1;
		}
		people[i] = person;
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_vehicles_from_csv(const char *file_name, Vehicle vehicles[], const size_t count) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	Vehicle vehicle;
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		assigned = sscanf(line,
						"%*[^,],"  // Index
						"%*[^,],"  // GloOfs
						"%*[^,],"  // RelOfs
						"%hu,"     // Child
						"%hu,"     // Parent
						"%hd,"     // Xpos
						"%hd,"     // Ypos
						"%hd,"     // Zpos
						"%*[^,],"  // Xtile
						"%*[^,],"  // Ytile
						"%hu,"     // Status
						"%*[^,],"  // Status_S
						"%hu,"     // Affect
						"%*[^,],"  // Affect_S
						"%hu,"     // BaseFrame
						"%hu,"     // Frame
						"%hu,"     // OldFrame
						"%hu,"     // Life
						"%hu,"     // WhoShotMe
						"%hhu,"    // Model
						"%*[^,],"  // Model_S
						"%hhu,"    // State
						"%*[^,],"  // State_S
						"%hhu,"    // Angle
						"%*[^,],"  // Angle_S
						"%hhu,"    // ZAngle
						"%hu,"     // ChildHeld
						"%hu,"     // ParentHeld
						"%hu,"     // LinkTo
						"%hd,"     // LinkX
						"%hd,"     // LinkY
						"%hd,"     // LinkZ
						"%hhu,"    // MaxSpeed
						"%hhu"     // TravelAngle
						"%n",
						&vehicle.Child,
						&vehicle.Parent,
						&vehicle.Xpos,
						&vehicle.Ypos,
						&vehicle.Zpos,
						&vehicle.Status,
						&vehicle.Affect,
						&vehicle.BaseFrame,
						&vehicle.Frame,
						&vehicle.OldFrame,
						&vehicle.Life,
						&vehicle.WhoShotMe,
						&vehicle.Model,
						&vehicle.State,
						&vehicle.Angle,
						&vehicle.ZAngle,
						&vehicle.ChildHeld,
						&vehicle.ParentHeld,
						&vehicle.LinkTo,
						&vehicle.LinkX,
						&vehicle.LinkY,
						&vehicle.LinkZ,
						&vehicle.MaxSpeed,
						&vehicle.TravelAngle,
						&consumed);
		if (assigned != 24 || (size_t)consumed != llen) {        // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, i+2, assigned, consumed, llen, line);
			fclose(file);
			return 1;
		}
		vehicles[i] = vehicle;
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_objects_from_csv(const char *file_name, Object objects[], const size_t count) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	Object object;
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		assigned = sscanf(line,
						"%*[^,],"  // Index
						"%*[^,],"  // GloOfs
						"%*[^,],"  // RelOfs
						"%hu,"     // Child
						"%hu,"     // Parent
						"%hd,"     // Xpos
						"%hd,"     // Ypos
						"%hd,"     // Zpos
						"%*[^,],"  // Xtile
						"%*[^,],"  // Ytile
						"%hu,"     // Status
						"%*[^,],"  // Status_S
						"%hu,"     // Affect
						"%hu,"     // BaseFrame
						"%*[^,],"  // BaseFrame_S
						"%hu,"     // Frame
						"%hu,"     // OldFrame
						"%hu,"     // Life
						"%hu,"     // WhoShotMe
						"%hhu,"    // Model
						"%*[^,],"  // Model_S
						"%hhu,"    // State
						"%*[^,],"  // State_S
						"%hhu,"    // Angle
						"%*[^,],"  // Angle_S
						"%hhu,"    // ZAngle
						"%hu"      // Connected
						"%n",
						&object.Child,
						&object.Parent,
						&object.Xpos,
						&object.Ypos,
						&object.Zpos,
						&object.Status,
						&object.Affect,
						&object.BaseFrame,
						&object.Frame,
						&object.OldFrame,
						&object.Life,
						&object.WhoShotMe,
						&object.Model,
						&object.State,
						&object.Angle,
						&object.ZAngle,
						&object.Connected,
						&consumed);
		if (assigned != 17 || (size_t)consumed != llen) {        // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, i+2, assigned, consumed, llen, line);
			fclose(file);
			return 1;
		}
		objects[i] = object;
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_weapons_from_csv(const char *file_name, Weapon weapons[], const size_t count) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	Weapon weapon;
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		assigned = sscanf(line,
					"%*[^,],"  // Index
					"%*[^,],"  // GloOfs
					"%*[^,],"  // RelOfs
					"%hu,"     // Child
					"%hu,"     // Parent
					"%hd,"     // Xpos
					"%hd,"     // Ypos
					"%hd,"     // Zpos
					"%*[^,],"  // Xtile
					"%*[^,],"  // Ytile
					"%hu,"     // Status
					"%*[^,],"  // Status_S
					"%hu,"     // Affect
					"%hu,"     // BaseFrame
					"%hu,"     // Frame
					"%hu,"     // OldFrame
					"%hu,"     // Life
					"%hu,"     // WhoShotMe
					"%hhu,"    // Model
					"%*[^,],"  // Model_S
					"%hhu,"    // State
					"%*[^,],"  // State_S
					"%hhu,"    // Angle
					"%*[^,],"  // Angle_S
					"%hhu,"    // ZAngle
					"%hu,"     // ChildWeapon
					"%hu,"     // ParentWeapon
					"%hu,"     // WhoOwnsWeapon
					"%hu"      // RepairCount
					"%n",
					&weapon.Child,
					&weapon.Parent,
					&weapon.Xpos,
					&weapon.Ypos,
					&weapon.Zpos,
					&weapon.Status,
					&weapon.Affect,
					&weapon.BaseFrame,
					&weapon.Frame,
					&weapon.OldFrame,
					&weapon.Life,
					&weapon.WhoShotMe,
					&weapon.Model,
					&weapon.State,
					&weapon.Angle,
					&weapon.ZAngle,
					&weapon.ChildWeapon,
					&weapon.ParentWeapon,
					&weapon.WhoOwnsWeapon,
					&weapon.RepairCount,
					&consumed);
		if (assigned != 20 || (size_t)consumed != llen) {        // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, i+2, assigned, consumed, llen, line);
			fclose(file);
			return 1;
		}
		weapons[i] = weapon;
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_effects_from_csv(const char *file_name, Effect effects[], const size_t count) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	Effect effect;
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		assigned = sscanf(line,
						"%*[^,],"  // Index
						"%*[^,],"  // GloOfs
						"%*[^,],"  // RelOfs
						"%hu,"     // Child
						"%hu,"     // Parent
						"%hd,"     // Xpos
						"%hd,"     // Ypos
						"%hd,"     // Zpos
						"%*[^,],"  // Xtile
						"%*[^,],"  // Ytile
						"%hu,"     // Status
						"%*[^,],"  // Status_S
						"%hu,"     // Affect
						"%hu,"     // BaseFrame
						"%hu,"     // Frame
						"%hu,"     // OldFrame
						"%hu,"     // Life
						"%hu,"     // WhoShotMe
						"%hhu,"    // Model
						"%*[^,],"  // Model_S
						"%hhu,"    // State
						"%hhu,"    // Angle
						"%*[^,],"  // Angle_S
						"%hhu,"    // ZAngle
						"%hu,"     // WhoShot
						"%*[^,]"   // WhoShotType
						"%n",
						&effect.Child,
						&effect.Parent,
						&effect.Xpos,
						&effect.Ypos,
						&effect.Zpos,
						&effect.Status,
						&effect.Affect,
						&effect.BaseFrame,
						&effect.Frame,
						&effect.OldFrame,
						&effect.Life,
						&effect.WhoShotMe,
						&effect.Model,
						&effect.State,
						&effect.Angle,
						&effect.ZAngle,
						&effect.WhoShot,
						&consumed);
		if (assigned != 17 || (size_t)consumed != llen) {        // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, i+2, assigned, consumed, llen, line);
			fclose(file);
			return 1;
		}
		effects[i] = effect;
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_commands_from_csv(const char *file_name, Command commands[], const size_t count) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	//
	// NOTE:
	// This function was the nucleus, all others were derived from this one.
	// Function 'read_mapwho_from_csv' and 'read_structless_from_csv' are a bit
	// different due to their respective data structures / formats
	//
	// CAUTION:
	//
	// - fscanf is notoriously difficult to get right since there is no helpful
	//   debug output possible except for the return value (# of assigned items)
	//
	// - fscanf has no concept of lines, it SKIPS whitespace (including newlines)
	//   and just parses non-whitespace contents, thus there is no way of knowing
	//   if an ENTIRE LINE conforms to a certain format (like regex '^...$' would
	//   do)
	//
	// -> Better solution: read lines using fgets + use sscanf with a '%n' token
	//    at the end of the template to verify that the entire line was consumed
	//    (value returned for token must equal strlen(line))
	//

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	/*Command command;                                           // Quick and dirty solution (works fine, but difficult to debug due to lack of helpful error output)
	fscanf(file, "%*s\n");                                       // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fscanf(file, "%*[^,],%*[^,],%*[^,],%*[^,],%hu,%hu,%*[^,],%hhu,%hhu,%hhu,%hhu,%*[^\n]", &command.Next, &command.Data, &command.GotoX, &command.GotoY, &command.GotoZ, &command.State) != 6) {
			fprintf(stderr, "Failed to read/parse contents of CSV file '%s': malformed content in line %zu\n", file_name, i+2);
			fclose(file);
			return 1;
		}
		commands[i] = command;
	}*/
	Command command;
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		assigned = sscanf(line,
						"%*[^,],"  // Index
						"%*[^,],"  // GloOfs
						"%*[^,],"  // RelOfs
						"%*[^,],"  // LocOfs
						"%hu,"     // Next
						"%hu,"     // Data
						"%*[^,],"  // DataType
						"%hhu,"    // GotoX
						"%hhu,"    // GotoY
						"%hhu,"    // GotoZ
						"%hhu,"    // State
						"%*[^,]"   // State_S
						"%n",
						&command.Next,
						&command.Data,
						&command.GotoX,
						&command.GotoY,
						&command.GotoZ,
						&command.State,
						&consumed);
		if (assigned != 6 || (size_t)consumed != llen) {         // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, i+2, assigned, consumed, llen, line);
			fclose(file);
			return 1;
		}
		commands[i] = command;
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_worlds_from_csv(const char *file_name, World worlds[], const size_t count) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	World world;
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		assigned = sscanf(line,
						"%*[^,],"  // Index
						"%*[^,],"  // GloOfs
						"%*[^,],"  // RelOfs
						"%hu,"     // WindXSpeed
						"%hu,"     // WindYSpeed
						"%hu,"     // Population
						"%hhu,"    // Temperature
						"%hhu,"    // WindSpeed
						"%hhu,"    // WindAngle
						"%hhu,"    // Industry
						"%hhu,"    // Crime
						"%hhu,"    // Gravity
						"%hhu,"    // Density
						"%hhu"     // Unknown
						"%n",
						&world.WindXSpeed,
						&world.WindYSpeed,
						&world.Population,
						&world.Temperature,
						&world.WindSpeed,
						&world.WindAngle,
						&world.Industry,
						&world.Crime,
						&world.Gravity,
						&world.Density,
						&world.Unknown,
						&consumed);
		if (assigned != 11 || (size_t)consumed != llen) {        // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, i+2, assigned, consumed, llen, line);
			fclose(file);
			return 1;
		}
		worlds[i] = world;
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_objectives_from_csv(const char *file_name, Objective objectives[], const size_t count) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	Objective objective;
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		assigned = sscanf(line,
						"%*[^,],"  // Index
						"%*[^,],"  // GloOfs
						"%*[^,],"  // RelOfs
						"%u,"      // Status
						"%hu,"     // Type
						"%*[^,],"  // Type_S
						"%hu,"     // Data
						"%*[^,],"  // DataType
						"%hd,"     // Xpos
						"%hd,"     // Ypos
						"%hd,"     // Zpos
						"%*[^,],"  // Xtile
						"%*[^,]"   // Ytile
						"%n",
						&objective.Status,
						&objective.Type,
						&objective.Data,
						&objective.Xpos,
						&objective.Ypos,
						&objective.Zpos,
						&consumed);
		if (assigned != 6 || (size_t)consumed != llen) {         // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, i+2, assigned, consumed, llen, line);
			fclose(file);
			return 1;
		}
		objectives[i] = objective;
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_cpobjectives_from_csv(const char *file_name, CPObjective cpobjectives[], const size_t count) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	CPObjective cpobjective;
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	for (size_t i = 0; i < count; i++) {
		if (fgets(line, sizeof(line), file) == NULL) {           // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
			if (ferror(file) != 0) {                             // Error?
				fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
				fclose(file);
				return 1;
			}
			fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
			fclose(file);
			return 1;
		}

		llen = strnlen(line, sizeof(line));
		if (llen > 0 && line[llen-1] == '\n') {                  // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
			line[llen-1] = '\0'; llen--;
		}

		assigned = sscanf(line,
						"%*[^,],"  // GloOfs
						"%*[^,],"  // RelOfs
						"%*[^,],"  // Index
						"%hu,"     // Parent
						"%hu,"     // Child
						"%hhu,"    // UseCount
						"%hhu,"    // Player
						"%hhu,"    // Flags
						"%hhu,"    // ActionType
						"%*[^,],"  // ActionType_S
						"%hhu,"    // Action
						"%*[^,],"  // Action_S
						"%hd,"     // X
						"%hd,"     // Y
						"%hd"      // Z
						"%n",
						&cpobjective.Parent,
						&cpobjective.Child,
						&cpobjective.UseCount,
						&cpobjective.Player,
						&cpobjective.Flags,
						&cpobjective.ActionType,
						&cpobjective.Action,
						&cpobjective.X,
						&cpobjective.Y,
						&cpobjective.Z,
						&consumed);
		if (assigned != 10 || (size_t)consumed != llen) {        // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
			fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, i+2, assigned, consumed, llen, line);
			fclose(file);
			return 1;
		}
		cpobjectives[i] = cpobjective;
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}

int read_structless_from_csv(const char *file_name, GameData *gamedata) {

	// Open CSV file
	printf("Opening CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "rt");
	if (file == NULL) {
		fprintf(stderr, "Failed to open CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Read and parse CSV contents
	printf("Reading and parsing contents of CSV file '%s'...\n", file_name);
	char line[1024]; size_t llen; int assigned, consumed;
	fgets(line, sizeof(line), file);                             // Skip first line (contains column names)
	if (fgets(line, sizeof(line), file) == NULL) {               // NULL can be error -or- EOF; line can contain a trailing newline (if one was read)
		if (ferror(file) != 0) {                                 // Error?
			fprintf(stderr, "Failed to read line from CSV file '%s': %s\n", file_name, strerror(errno));
			fclose(file);
			return 1;
		}
		fprintf(stderr, "Failed to read line from CSV file '%s': reached EOF prematurely, expected further contents\n", file_name);
		fclose(file);
		return 1;
	}

	llen = strnlen(line, sizeof(line));
	if (llen > 0 && line[llen-1] == '\n') {                      // Cut trailing newline (both for easier sscanf and for nicer debug/error output of line)
		line[llen-1] = '\0'; llen--;
	}

	assigned = sscanf(line,
					"%hu,"     // Seed
					"%hu,"     // PersonCount
					"%hu,"     // Timer
					"%hu,"     // RelOfsBase
					"%hu,"     // MapNumber
					"%hu,"     // LoBoundaryx
					"%hu,"     // LoBoundaryy
					"%hu,"     // HiBoundaryx
					"%hu,"     // HiBoundaryy
					"%hhu,"    // CPCount
					"%hhu,"    // CPTeamSize
					"%hhu,"    // CPProcInt
					"%hhu,"    // CPLvlInit
					"%hhu,"    // CPIsBombTeam
					"%hhu,"    // CPIsPersTeam
					"%hhu,"    // CPFlags
					"%*[^,],"  // CPFlags_S
					"%hhu,"    // CPWeapon
					"%*[^,]"   // CPWeapon_S
					"%n",
					&gamedata->Seed,
					&gamedata->PersonCount,
					&gamedata->Timer,
					&gamedata->RelOfsBase,
					&gamedata->MapNumber,
					&gamedata->LoBoundaryx,
					&gamedata->LoBoundaryy,
					&gamedata->HiBoundaryx,
					&gamedata->HiBoundaryy,
					&gamedata->CPCount,
					&gamedata->CPTeamSize,
					&gamedata->CPProcInt,
					&gamedata->CPLvlInit,
					&gamedata->CPIsBombTeam,
					&gamedata->CPIsPersTeam,
					&gamedata->CPFlags,
					&gamedata->CPWeapon,
					&consumed);
	if (assigned != 17 || (size_t)consumed != llen) {            // Entire line must be consumed by sscanf, otherwise line is malformed (i.e. contains trailing stuff)
		fprintf(stderr, "Failed to parse line from CSV file '%s': malformed content in line %zu (assigned: %d, consumed: %d, llen: %lu): '%s'\n", file_name, (size_t)2, assigned, consumed, llen, line);
	}

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}
