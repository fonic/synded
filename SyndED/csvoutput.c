#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "gamedata.h"
#include "gdenums.h"

int write_mapwho_to_csv(const char *file_name, const uint16_t mapwho[], const size_t count_x, const size_t count_y) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	for (size_t x = 0; x < count_x; x++) {  // First row contains X indices (first column left empty)
		fprintf(file, ",%zu", x);
	}
	fprintf(file, "\n");
	for (size_t y = 0; y < count_y; y++) {
		fprintf(file, "%zu", y);            // Each row starts with Y index in first column
		for (size_t x = 0; x < count_x; x++) {
			fprintf(file, ",%u", mapwho[(y * count_x) + x]);
		}
		fprintf(file, "\n");
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

int write_people_to_csv(const char *file_name, const Person people[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,Affect_S,BaseFrame,BaseFrame_S,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,State_S,Angle,Angle_S,ZAngle,Unique,Unique_S,HugDistance,Persuaded,ChildHeld,ParentHeld,Command,StartCommand,Target,Data,GotoX,GotoY,GotoZ,LastXpos,LastYpos,HugGotoZ,ChildWeapon,Equipment,ParentRank,RankPosition,Count,WeaponHolding,WeaponInUse,Level1Base,Level1Balance,Level1True,Level1Fixed,Level2Base,Level2Balance,Level2True,Level2Fixed,Level3Base,Level3Balance,Level3True,Level3Fixed,LevelRecovery,Speed,MaxSpeed,BaseSpeed,OldState,OldState_S,NewState,NewState_S,HugChangeDir,HugStartAngle,HitAngle\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%s,%u,%s,%u,%s,%u,%u,%u,%u,%u,%s,%u,%s,%u,%s,%u,%u,%s,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%s,%u,%s,%u,%u,%u\n",
				offset_global + sizeof(Person) * i,
				offset_relative + sizeof(Person) * i,
				people[i].Child,
				people[i].Parent,
				people[i].Xpos,
				people[i].Ypos,
				people[i].Zpos,
				people[i].Xpos >> 8,
				people[i].Ypos >> 8,
				people[i].Status,
				thing_status_to_str(people[i].Status),
				people[i].Affect,
				person_affect_to_str(people[i].Affect),
				people[i].BaseFrame,
				person_baseframe_to_str(people[i].BaseFrame),
				people[i].Frame,
				people[i].OldFrame,
				people[i].Life,
				people[i].WhoShotMe,
				people[i].Model,
				thing_model_to_str(people[i].Model),
				people[i].State,
				person_state_to_str(people[i].State),
				people[i].Angle,
				thing_angle_to_str(people[i].Angle),
				people[i].ZAngle,
				people[i].Unique,
				person_unique_to_str(people[i].Unique),
				people[i].HugDistance,
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
				person_state_to_str(people[i].OldState),
				people[i].NewState,
				person_state_to_str(people[i].NewState),
				people[i].HugChangeDir,
				people[i].HugStartAngle,
				people[i].HitAngle
		);
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

int write_vehicles_to_csv(const char *file_name, const Vehicle vehicles[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,State_S,Angle,Angle_S,ZAngle,ChildHeld,ParentHeld,LinkTo,LinkX,LinkY,LinkZ,MaxSpeed,TravelAngle\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%s,%u,%u,%u,%u,%u,%u,%u,%s,%u,%s,%u,%s,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global + sizeof(Vehicle) * i,
				offset_relative + sizeof(Vehicle) * i,
				vehicles[i].Child,
				vehicles[i].Parent,
				vehicles[i].Xpos,
				vehicles[i].Ypos,
				vehicles[i].Zpos,
				vehicles[i].Xpos >> 8,
				vehicles[i].Ypos >> 8,
				vehicles[i].Status,
				thing_status_to_str(vehicles[i].Status),
				vehicles[i].Affect,
				vehicles[i].BaseFrame,
				vehicles[i].Frame,
				vehicles[i].OldFrame,
				vehicles[i].Life,
				vehicles[i].WhoShotMe,
				vehicles[i].Model,
				thing_model_to_str(vehicles[i].Model),
				vehicles[i].State,
				vehicle_state_to_str(vehicles[i].State),
				vehicles[i].Angle,
				thing_angle_to_str(vehicles[i].Angle),
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

int write_objects_to_csv(const char *file_name, const Object objects[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,Angle,Angle_S,ZAngle,Unknown[0],Unknown[1]\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%s,%u,%u,%u,%u,%u,%u,%u,%s,%u,%u,%s,%u,%u,%u\n",
				offset_global + sizeof(Object) * i,
				offset_relative + sizeof(Object) * i,
				objects[i].Child,
				objects[i].Parent,
				objects[i].Xpos,
				objects[i].Ypos,
				objects[i].Zpos,
				objects[i].Xpos >> 8,
				objects[i].Ypos >> 8,
				objects[i].Status,
				thing_status_to_str(objects[i].Status),
				objects[i].Affect,
				objects[i].BaseFrame,
				objects[i].Frame,
				objects[i].OldFrame,
				objects[i].Life,
				objects[i].WhoShotMe,
				objects[i].Model,
				thing_model_to_str(objects[i].Model),
				objects[i].State,
				objects[i].Angle,
				thing_angle_to_str(objects[i].Angle),
				objects[i].ZAngle,
				objects[i].Unknown[0],
				objects[i].Unknown[1]
		);
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

int write_weapons_to_csv(const char *file_name, const Weapon weapons[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,State_S,Angle,Angle_S,ZAngle,ChildWeapon,ParentWeapon,WhoOwnsWeapon,RepairCount\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%s,%u,%u,%u,%u,%u,%u,%u,%s,%u,%s,%u,%s,%u,%u,%u,%u,%u\n",
				offset_global + sizeof(Weapon) * i,
				offset_relative + sizeof(Weapon) * i,
				weapons[i].Child,
				weapons[i].Parent,
				weapons[i].Xpos,
				weapons[i].Ypos,
				weapons[i].Zpos,
				weapons[i].Xpos >> 8,
				weapons[i].Ypos >> 8,
				weapons[i].Status,
				thing_status_to_str(weapons[i].Status),
				weapons[i].Affect,
				weapons[i].BaseFrame,
				weapons[i].Frame,
				weapons[i].OldFrame,
				weapons[i].Life,
				weapons[i].WhoShotMe,
				weapons[i].Model,
				thing_model_to_str(weapons[i].Model),
				weapons[i].State,
				weapon_state_to_str(weapons[i].State),
				weapons[i].Angle,
				thing_angle_to_str(weapons[i].Angle),
				weapons[i].ZAngle,
				weapons[i].ChildWeapon,
				weapons[i].ParentWeapon,
				weapons[i].WhoOwnsWeapon,
				weapons[i].RepairCount
		);
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

int write_effects_to_csv(const char *file_name, const Effect effects[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,Angle,Angle_S,ZAngle,Owner\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%s,%u,%u,%u,%u,%u,%u,%u,%s,%u,%u,%s,%u,%u\n",
				offset_global + sizeof(Effect) * i,
				offset_relative + sizeof(Effect) * i,
				effects[i].Child,
				effects[i].Parent,
				effects[i].Xpos,
				effects[i].Ypos,
				effects[i].Zpos,
				effects[i].Xpos >> 8,
				effects[i].Ypos >> 8,
				effects[i].Status,
				thing_status_to_str(effects[i].Status),
				effects[i].Affect,
				effects[i].BaseFrame,
				effects[i].Frame,
				effects[i].OldFrame,
				effects[i].Life,
				effects[i].WhoShotMe,
				effects[i].Model,
				thing_model_to_str(effects[i].Model),
				effects[i].State,
				effects[i].Angle,
				thing_angle_to_str(effects[i].Angle),
				effects[i].ZAngle,
				effects[i].Owner
		);
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

int write_commands_to_csv(const char *file_name, const Command commands[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,LocOfs,Next,Data,GotoX,GotoY,GotoZ,State,State_S\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,%zu,%zu,%u,%u,%u,%u,%u,%u,%s\n",
				offset_global + sizeof(Command) * i,
				offset_relative + sizeof(Command) * i,
				sizeof(Command) * i,
				commands[i].Next,
				commands[i].Data,
				commands[i].GotoX,
				commands[i].GotoY,
				commands[i].GotoZ,
				commands[i].State,
				command_state_to_str(commands[i].State)
		);
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

int write_worlds_to_csv(const char *file_name, const World worlds[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,WindXSpeed,WindYSpeed,Population,Temperature,WindSpeed,WindAngle,Industry,Crime,Gravity,Density,Unknown\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global + sizeof(World) * i,
				offset_relative + sizeof(World) * i,
				worlds[i].WindXSpeed,
				worlds[i].WindYSpeed,
				worlds[i].Population,
				worlds[i].Temperature,
				worlds[i].WindSpeed,
				worlds[i].WindAngle,
				worlds[i].Industry,
				worlds[i].Crime,
				worlds[i].Gravity,
				worlds[i].Density,
				worlds[i].Unknown
		);
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

int write_objectives_to_csv(const char *file_name, const Objective objectives[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Status,Objective,Data,Xpos,Ypos,Zpos,Xtile,Ytile\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global + sizeof(Objective) * i,
				offset_relative + sizeof(Objective) * i,
				objectives[i].Status,
				objectives[i].Objective,
				objectives[i].Data,
				objectives[i].Xpos,
				objectives[i].Ypos,
				objectives[i].Zpos,
				objectives[i].Xpos >> 8,
				objectives[i].Ypos >> 8
		);
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

int write_cpobjectives_to_csv(const char *file_name, const CPObjective cpobjectives[], const size_t count, const size_t offset_global, const size_t offset_relative) {

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
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,%zu,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
				offset_global + sizeof(CPObjective) * i,
				offset_relative + sizeof(CPObjective) * i,
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

int write_structless_to_csv(const char *file_name, const GameData *gamedata) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (!file) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "Seed,PersonCount,Timer,Unknown,MapNumber,LoBoundaryx,LoBoundaryy,HiBoundaryx,HiBoundaryy,CPCount,CPTeamSize,CPProcInt,CPLvlInit,CPIsBombTeam,CPIsPersTeam,CPFlags,CPWeapon\n");
	fprintf(file, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
			gamedata->Seed,
			gamedata->PersonCount,
			gamedata->Timer,
			gamedata->Unknown,
			gamedata->MapNumber,
			gamedata->LoBoundaryx,
			gamedata->LoBoundaryy,
			gamedata->HiBoundaryx,
			gamedata->HiBoundaryy,
			gamedata->CPCount,
			gamedata->CPTeamSize,
			gamedata->CPProcInt,
			gamedata->CPLvlInit,
			gamedata->CPIsBombTeam,
			gamedata->CPIsPersTeam,
			gamedata->CPFlags,
			gamedata->CPWeapon
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
