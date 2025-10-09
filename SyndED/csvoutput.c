#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "asprintf.h"
#include "gamedata.h"

#define OFFSET_GLOBAL_TO_RELATIVE(ofs) ofs - 32774

int write_people_to_csv(const char *file_name, Person people[], size_t arrlen, size_t offset_global) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Status,Affect,Unknown[0],Unknown[1],BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,State,Angle,ZAngle,Unique,Hugdistance1,Hugdistance2,Persuaded,ChildHeld,ParentHeld,Command,StartCommand,Target,Data,GotoX,GotoY,GotoZ,LastXpos,LastYpos,HugGotoZ,ChildWeapon,Equipment,ParentRank,RankPosition,Count,WeaponHolding,WeaponInUse,Level1Base,Level1Balance,Level1True,Level1Fixed,Level2Base,Level2Balance,Level2True,Level2Fixed,Level3Base,Level3Balance,Level3True,Level3Fixed,LevelRecovery,Speed,MaxSpeed,BaseSpeed,OldState,NewState,HugChangeDir,HugStartAngle,HitAngle\n");
	for (size_t i = 0; i < arrlen; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global,
				OFFSET_GLOBAL_TO_RELATIVE(offset_global),
				people[i].Child,
				people[i].Parent,
				people[i].Xpos,
				people[i].Ypos,
				people[i].Zpos,
				people[i].Status,
				people[i].Affect,
				people[i].Unknown[0],
				people[i].Unknown[1],
				people[i].BaseFrame,
				people[i].Frame,
				people[i].OldFrame,
				people[i].Life,
				people[i].WhoShotMe,
				people[i].Model,
				people[i].State,
				people[i].Angle,
				people[i].ZAngle,
				people[i].Unique,
				people[i].Hugdistance1,
				people[i].Hugdistance2,
				people[i].Persuaded,
				people[i].ChildHeld,
				people[i].ParentHeld,
				people[i].Command,
				people[i].StartCommand,
				people[i].Target,
				people[i].Data,
				people[i].GotoX,
				people[i].GotoY,
				people[i].GotoZ,
				people[i].LastXpos,
				people[i].LastYpos,
				people[i].HugGotoZ,
				people[i].ChildWeapon,
				people[i].Equipment,
				people[i].ParentRank,
				people[i].RankPosition,
				people[i].Count,
				people[i].WeaponHolding,
				people[i].WeaponInUse,
				people[i].Level1Base,
				people[i].Level1Balance,
				people[i].Level1True,
				people[i].Level1Fixed,
				people[i].Level2Base,
				people[i].Level2Balance,
				people[i].Level2True,
				people[i].Level2Fixed,
				people[i].Level3Base,
				people[i].Level3Balance,
				people[i].Level3True,
				people[i].Level3Fixed,
				people[i].LevelRecovery,
				people[i].Speed,
				people[i].MaxSpeed,
				people[i].BaseSpeed,
				people[i].OldState,
				people[i].NewState,
				people[i].HugChangeDir,
				people[i].HugStartAngle,
				people[i].HitAngle
		);
		offset_global += sizeof(people[i]);
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

int write_vehicles_to_csv(const char *file_name, Vehicle vehicles[], size_t arrlen, size_t offset_global) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Status,Affect,Unknown[0],Unknown[1],BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,State,Angle,ZAngle,ChildHeld,ParentHeld,LinkTo,LinkX,LinkY,LinkZ,MaxSpeed,TravelAngle\n");
	for (size_t i = 0; i < arrlen; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global,
				OFFSET_GLOBAL_TO_RELATIVE(offset_global),
				vehicles[i].Child,
				vehicles[i].Parent,
				vehicles[i].Xpos,
				vehicles[i].Ypos,
				vehicles[i].Zpos,
				vehicles[i].Status,
				vehicles[i].Affect,
				vehicles[i].Unknown[0],
				vehicles[i].Unknown[1],
				vehicles[i].BaseFrame,
				vehicles[i].Frame,
				vehicles[i].OldFrame,
				vehicles[i].Life,
				vehicles[i].WhoShotMe,
				vehicles[i].Model,
				vehicles[i].State,
				vehicles[i].Angle,
				vehicles[i].ZAngle,
				vehicles[i].ChildHeld,
				vehicles[i].ParentHeld,
				vehicles[i].LinkTo,
				vehicles[i].LinkX,
				vehicles[i].LinkY,
				vehicles[i].LinkZ,
				vehicles[i].MaxSpeed,
				vehicles[i].TravelAngle
		);
		offset_global += sizeof(vehicles[i]);
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

int write_objects_to_csv(const char *file_name, Object objects[], size_t arrlen, size_t offset_global) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Status,Affect,Unknown1[0],Unknown1[1],BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,State,Angle,ZAngle,Unknown2[0],Unknown2[1]\n");
	for (size_t i = 0; i < arrlen; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global,
				OFFSET_GLOBAL_TO_RELATIVE(offset_global),
				objects[i].Child,
				objects[i].Parent,
				objects[i].Xpos,
				objects[i].Ypos,
				objects[i].Zpos,
				objects[i].Status,
				objects[i].Affect,
				objects[i].Unknown1[0],
				objects[i].Unknown1[1],
				objects[i].BaseFrame,
				objects[i].Frame,
				objects[i].OldFrame,
				objects[i].Life,
				objects[i].WhoShotMe,
				objects[i].Model,
				objects[i].State,
				objects[i].Angle,
				objects[i].ZAngle,
				objects[i].Unknown2[0],
				objects[i].Unknown2[1]
		);
		offset_global += sizeof(objects[i]);
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

int write_weapons_to_csv(const char *file_name, Weapon weapons[], size_t arrlen, size_t offset_global) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Status,Affect,Unknown[0],Unknown[1],BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,State,Angle,ZAngle,ChildWeapon,ParentWeapon,WhoOwnsWeapon,RepairCount\n");
	for (size_t i = 0; i < arrlen; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global,
				OFFSET_GLOBAL_TO_RELATIVE(offset_global),
				weapons[i].Child,
				weapons[i].Parent,
				weapons[i].Xpos,
				weapons[i].Ypos,
				weapons[i].Zpos,
				weapons[i].Status,
				weapons[i].Affect,
				weapons[i].Unknown[0],
				weapons[i].Unknown[1],
				weapons[i].BaseFrame,
				weapons[i].Frame,
				weapons[i].OldFrame,
				weapons[i].Life,
				weapons[i].WhoShotMe,
				weapons[i].Model,
				weapons[i].State,
				weapons[i].Angle,
				weapons[i].ZAngle,
				weapons[i].ChildWeapon,
				weapons[i].ParentWeapon,
				weapons[i].WhoOwnsWeapon,
				weapons[i].RepairCount
		);
		offset_global += sizeof(weapons[i]);
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

int write_effects_to_csv(const char *file_name, Effect effects[], size_t arrlen, size_t offset_global) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Status,Affect,Unknown[0],Unknown[1],BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,State,Angle,ZAngle,Owner\n");
	for (size_t i = 0; i < arrlen; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global,
				OFFSET_GLOBAL_TO_RELATIVE(offset_global),
				effects[i].Child,
				effects[i].Parent,
				effects[i].Xpos,
				effects[i].Ypos,
				effects[i].Zpos,
				effects[i].Status,
				effects[i].Affect,
				effects[i].Unknown[0],
				effects[i].Unknown[1],
				effects[i].BaseFrame,
				effects[i].Frame,
				effects[i].OldFrame,
				effects[i].Life,
				effects[i].WhoShotMe,
				effects[i].Model,
				effects[i].State,
				effects[i].Angle,
				effects[i].ZAngle,
				effects[i].Owner
		);
		offset_global += sizeof(effects[i]);
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

int write_commands_to_csv(const char *file_name, Command commands[], size_t arrlen, size_t offset_global) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Next,Data,GotoX,GotoY,GotoZ,State\n");
	for (size_t i = 0; i < arrlen; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u\n",
				offset_global,
				OFFSET_GLOBAL_TO_RELATIVE(offset_global),
				commands[i].Next,
				commands[i].Data,
				commands[i].GotoX,
				commands[i].GotoY,
				commands[i].GotoZ,
				commands[i].State
		);
		offset_global += sizeof(commands[i]);
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

int write_worlds_to_csv(const char *file_name, World worlds[], size_t arrlen, size_t offset_global) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,WindXSpeed,WindYSpeed,Population,Temperature,WindSpeed,WindAngle,Industry,Crime,Gravity,Density\n");
	for (size_t i = 0; i < arrlen; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global,
				OFFSET_GLOBAL_TO_RELATIVE(offset_global),
				worlds[i].WindXSpeed,
				worlds[i].WindYSpeed,
				worlds[i].Population,
				worlds[i].Temperature,
				worlds[i].WindSpeed,
				worlds[i].WindAngle,
				worlds[i].Industry,
				worlds[i].Crime,
				worlds[i].Gravity,
				worlds[i].Density
		);
		offset_global += sizeof(worlds[i]);
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

int write_objectives_to_csv(const char *file_name, Objective objectives[], size_t arrlen, size_t offset_global) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Status,Objective,Data,Xpos,Ypos,Zpos\n");
	for (size_t i = 0; i < arrlen; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u\n",
				offset_global,
				OFFSET_GLOBAL_TO_RELATIVE(offset_global),
				objectives[i].Status,
				objectives[i].Objective,
				objectives[i].Data,
				objectives[i].Xpos,
				objectives[i].Ypos,
				objectives[i].Zpos
		);
		offset_global += sizeof(objectives[i]);
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

int write_cpobjectives_to_csv(const char *file_name, CPObjective cpobjectives[], size_t arrlen, size_t offset_global) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,UseCount,Player,Flags,ActionType,Action,X,Y,Z\n");
	for (size_t i = 0; i < arrlen; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global,
				OFFSET_GLOBAL_TO_RELATIVE(offset_global),
				cpobjectives[i].Child,
				cpobjectives[i].Parent,
				cpobjectives[i].UseCount,
				cpobjectives[i].Player,
				cpobjectives[i].Flags,
				cpobjectives[i].ActionType,
				cpobjectives[i].Action,
				cpobjectives[i].X,
				cpobjectives[i].Y,
				cpobjectives[i].Z
		);
		offset_global += sizeof(cpobjectives[i]);
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

int write_structless_to_csv(const char *file_name, GameData *gamedata) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "Seed,PersonCount,Timer,Unknown_1,MapNumber,LoBoundaryx,LoBoundaryy,HiBoundaryx,HiBoundaryy,Unknown_2,CPTeamSize,Unknown_3,CPLvlInit,Unknown_4,Unknown_5,Unknown_6,Unknown_7\n");
	fprintf(file, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
			gamedata->Seed,
			gamedata->PersonCount,
			gamedata->Timer,
			gamedata->Unknown_1,
			gamedata->MapNumber,
			gamedata->LoBoundaryx,
			gamedata->LoBoundaryy,
			gamedata->HiBoundaryx,
			gamedata->HiBoundaryy,
			gamedata->Unknown_2,
			gamedata->CPTeamSize,
			gamedata->Unknown_3,
			gamedata->CPLvlInit,
			gamedata->Unknown_4,
			gamedata->Unknown_5,
			gamedata->Unknown_6,
			gamedata->Unknown_7
	);

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}
