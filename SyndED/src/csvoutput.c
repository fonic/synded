/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - CSV Output                                             *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/14/25                                                 *
 *                                                                            *
 ******************************************************************************/

#include "csvoutput.h"  // related header

#include <stdio.h>      // printf, fprintf, fopen, fclose, stderr, FILE
#include <string.h>     // strerror
#include <errno.h>      // errno

#include "gdenums.h"    // <struct>_<member>_to_str

int write_mapwho_to_csv(const char *file_name, const uint16_t mapwho[], const size_t count_x, const size_t count_y) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
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
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,Affect_S,BaseFrame,BaseFrame_S,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,State_S,Angle,Angle_S,ZAngle,Unique,Unique_S,HugDistance,Persuaded,ChildHeld,ParentHeld,Command,StartCommand,Target,Data,GotoX,GotoY,GotoZ,LastXpos,LastYpos,HugGotoZ,ChildWeapon,Equipment,ParentRank,RankPosition,Count,WeaponHolding,WeaponInUse,Level1Base,Level1Balance,Level1True,Level1Fixed,Level2Base,Level2Balance,Level2True,Level2Fixed,Level3Base,Level3Balance,Level3True,Level3Fixed,LevelRecovery,Speed,MaxSpeed,BaseSpeed,OldState,OldState_S,NewState,NewState_S,HugChangeDir,HugStartAngle,HitAngle\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,", offset_global + sizeof(Person) * i);
		fprintf(file, "%zu,", offset_relative + sizeof(Person) * i);
		fprintf(file, "%u,",  people[i].Child);
		fprintf(file, "%u,",  people[i].Parent);
		fprintf(file, "%i,",  people[i].Xpos);
		fprintf(file, "%i,",  people[i].Ypos);
		fprintf(file, "%i,",  people[i].Zpos);
		fprintf(file, "%i,",  POS_TO_TILE(people[i].Xpos));
		fprintf(file, "%i,",  POS_TO_TILE(people[i].Ypos));
		fprintf(file, "%u,",  people[i].Status);
		fprintf(file, "%s,",  thing_status_to_str(people[i].Status));
		fprintf(file, "%u,",  people[i].Affect);
		fprintf(file, "%s,",  person_affect_to_str(people[i].Affect));
		fprintf(file, "%u,",  people[i].BaseFrame);
		fprintf(file, "%s,",  person_baseframe_to_str(people[i].BaseFrame));
		fprintf(file, "%u,",  people[i].Frame);
		fprintf(file, "%u,",  people[i].OldFrame);
		fprintf(file, "%u,",  people[i].Life);
		fprintf(file, "%u,",  people[i].WhoShotMe);
		fprintf(file, "%u,",  people[i].Model);
		fprintf(file, "%s,",  thing_model_to_str(people[i].Model));
		fprintf(file, "%u,",  people[i].State);
		fprintf(file, "%s,",  person_state_to_str(people[i].State));
		fprintf(file, "%u,",  people[i].Angle);
		fprintf(file, "%s,",  thing_angle_to_str(people[i].Angle));
		fprintf(file, "%u,",  people[i].ZAngle);
		fprintf(file, "%u,",  people[i].Unique);
		fprintf(file, "%s,",  person_unique_to_str(people[i].Unique));
		fprintf(file, "%u,",  people[i].HugDistance);
		fprintf(file, "%u,",  people[i].Persuaded);
		fprintf(file, "%u,",  people[i].ChildHeld);
		fprintf(file, "%u,",  people[i].ParentHeld);
		fprintf(file, "%u,",  people[i].Command);
		fprintf(file, "%u,",  people[i].StartCommand);
		fprintf(file, "%u,",  people[i].Target);
		fprintf(file, "%u,",  people[i].Data);
		fprintf(file, "%i,",  people[i].GotoX);
		fprintf(file, "%i,",  people[i].GotoY);
		fprintf(file, "%i,",  people[i].GotoZ);
		fprintf(file, "%i,",  people[i].LastXpos);
		fprintf(file, "%i,",  people[i].LastYpos);
		fprintf(file, "%u,",  people[i].HugGotoZ);
		fprintf(file, "%u,",  people[i].ChildWeapon);
		fprintf(file, "%u,",  people[i].Equipment);
		fprintf(file, "%u,",  people[i].ParentRank);
		fprintf(file, "%u,",  people[i].RankPosition);
		fprintf(file, "%u,",  people[i].Count);
		fprintf(file, "%u,",  people[i].WeaponHolding);
		fprintf(file, "%u,",  people[i].WeaponInUse);
		fprintf(file, "%u,",  people[i].Level1Base);
		fprintf(file, "%u,",  people[i].Level1Balance);
		fprintf(file, "%u,",  people[i].Level1True);
		fprintf(file, "%u,",  people[i].Level1Fixed);
		fprintf(file, "%u,",  people[i].Level2Base);
		fprintf(file, "%u,",  people[i].Level2Balance);
		fprintf(file, "%u,",  people[i].Level2True);
		fprintf(file, "%u,",  people[i].Level2Fixed);
		fprintf(file, "%u,",  people[i].Level3Base);
		fprintf(file, "%u,",  people[i].Level3Balance);
		fprintf(file, "%u,",  people[i].Level3True);
		fprintf(file, "%u,",  people[i].Level3Fixed);
		fprintf(file, "%u,",  people[i].LevelRecovery);
		fprintf(file, "%u,",  people[i].Speed);
		fprintf(file, "%u,",  people[i].MaxSpeed);
		fprintf(file, "%u,",  people[i].BaseSpeed);
		fprintf(file, "%u,",  people[i].OldState);
		fprintf(file, "%s,",  person_state_to_str(people[i].OldState));
		fprintf(file, "%u,",  people[i].NewState);
		fprintf(file, "%s,",  person_state_to_str(people[i].NewState));
		fprintf(file, "%u,",  people[i].HugChangeDir);
		fprintf(file, "%u,",  people[i].HugStartAngle);
		fprintf(file, "%u",   people[i].HitAngle);
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

int write_vehicles_to_csv(const char *file_name, const Vehicle vehicles[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,State_S,Angle,Angle_S,ZAngle,ChildHeld,ParentHeld,LinkTo,LinkToType,LinkX,LinkY,LinkZ,MaxSpeed,TravelAngle\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,", offset_global + sizeof(Vehicle) * i);
		fprintf(file, "%zu,", offset_relative + sizeof(Vehicle) * i);
		fprintf(file, "%u,",  vehicles[i].Child);
		fprintf(file, "%u,",  vehicles[i].Parent);
		fprintf(file, "%i,",  vehicles[i].Xpos);
		fprintf(file, "%i,",  vehicles[i].Ypos);
		fprintf(file, "%i,",  vehicles[i].Zpos);
		fprintf(file, "%i,",  POS_TO_TILE(vehicles[i].Xpos));
		fprintf(file, "%i,",  POS_TO_TILE(vehicles[i].Ypos));
		fprintf(file, "%u,",  vehicles[i].Status);
		fprintf(file, "%s,",  thing_status_to_str(vehicles[i].Status));
		fprintf(file, "%u,",  vehicles[i].Affect);
		fprintf(file, "%u,",  vehicles[i].BaseFrame);
		fprintf(file, "%u,",  vehicles[i].Frame);
		fprintf(file, "%u,",  vehicles[i].OldFrame);
		fprintf(file, "%u,",  vehicles[i].Life);
		fprintf(file, "%u,",  vehicles[i].WhoShotMe);
		fprintf(file, "%u,",  vehicles[i].Model);
		fprintf(file, "%s,",  thing_model_to_str(vehicles[i].Model));
		fprintf(file, "%u,",  vehicles[i].State);
		fprintf(file, "%s,",  vehicle_state_to_str(vehicles[i].State));
		fprintf(file, "%u,",  vehicles[i].Angle);
		fprintf(file, "%s,",  thing_angle_to_str(vehicles[i].Angle));
		fprintf(file, "%u,",  vehicles[i].ZAngle);
		fprintf(file, "%u,",  vehicles[i].ChildHeld);
		fprintf(file, "%u,",  vehicles[i].ParentHeld);
		fprintf(file, "%u,",  vehicles[i].LinkTo);
		fprintf(file, "%s,",  thing_type_to_str(vehicles[i].LinkTo));  // Not sure yet if translation makes sense here
		fprintf(file, "%i,",  vehicles[i].LinkX);
		fprintf(file, "%i,",  vehicles[i].LinkY);
		fprintf(file, "%i,",  vehicles[i].LinkZ);
		fprintf(file, "%u,",  vehicles[i].MaxSpeed);
		fprintf(file, "%u",   vehicles[i].TravelAngle);
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

int write_objects_to_csv(const char *file_name, const Object objects[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,Angle,Angle_S,ZAngle,Unknown\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,", offset_global + sizeof(Object) * i);
		fprintf(file, "%zu,", offset_relative + sizeof(Object) * i);
		fprintf(file, "%u,",  objects[i].Child);
		fprintf(file, "%u,",  objects[i].Parent);
		fprintf(file, "%i,",  objects[i].Xpos);
		fprintf(file, "%i,",  objects[i].Ypos);
		fprintf(file, "%i,",  objects[i].Zpos);
		fprintf(file, "%i,",  POS_TO_TILE(objects[i].Xpos));
		fprintf(file, "%i,",  POS_TO_TILE(objects[i].Ypos));
		fprintf(file, "%u,",  objects[i].Status);
		fprintf(file, "%s,",  thing_status_to_str(objects[i].Status));
		fprintf(file, "%u,",  objects[i].Affect);
		fprintf(file, "%u,",  objects[i].BaseFrame);
		fprintf(file, "%u,",  objects[i].Frame);
		fprintf(file, "%u,",  objects[i].OldFrame);
		fprintf(file, "%u,",  objects[i].Life);
		fprintf(file, "%u,",  objects[i].WhoShotMe);
		fprintf(file, "%u,",  objects[i].Model);
		fprintf(file, "%s,",  thing_model_to_str(objects[i].Model));
		fprintf(file, "%u,",  objects[i].State);
		fprintf(file, "%u,",  objects[i].Angle);
		fprintf(file, "%s,",  thing_angle_to_str(objects[i].Angle));
		fprintf(file, "%u,",  objects[i].ZAngle);
		fprintf(file, "%u,",  objects[i].Unknown);
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

int write_weapons_to_csv(const char *file_name, const Weapon weapons[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,State_S,Angle,Angle_S,ZAngle,ChildWeapon,ParentWeapon,WhoOwnsWeapon,RepairCount\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,", offset_global + sizeof(Weapon) * i);
		fprintf(file, "%zu,", offset_relative + sizeof(Weapon) * i);
		fprintf(file, "%u,",  weapons[i].Child);
		fprintf(file, "%u,",  weapons[i].Parent);
		fprintf(file, "%i,",  weapons[i].Xpos);
		fprintf(file, "%i,",  weapons[i].Ypos);
		fprintf(file, "%i,",  weapons[i].Zpos);
		fprintf(file, "%i,",  POS_TO_TILE(weapons[i].Xpos));
		fprintf(file, "%i,",  POS_TO_TILE(weapons[i].Ypos));
		fprintf(file, "%u,",  weapons[i].Status);
		fprintf(file, "%s,",  thing_status_to_str(weapons[i].Status));
		fprintf(file, "%u,",  weapons[i].Affect);
		fprintf(file, "%u,",  weapons[i].BaseFrame);
		fprintf(file, "%u,",  weapons[i].Frame);
		fprintf(file, "%u,",  weapons[i].OldFrame);
		fprintf(file, "%u,",  weapons[i].Life);
		fprintf(file, "%u,",  weapons[i].WhoShotMe);
		fprintf(file, "%u,",  weapons[i].Model);
		fprintf(file, "%s,",  thing_model_to_str(weapons[i].Model));
		fprintf(file, "%u,",  weapons[i].State);
		fprintf(file, "%s,",  weapon_state_to_str(weapons[i].State));
		fprintf(file, "%u,",  weapons[i].Angle);
		fprintf(file, "%s,",  thing_angle_to_str(weapons[i].Angle));
		fprintf(file, "%u,",  weapons[i].ZAngle);
		fprintf(file, "%u,",  weapons[i].ChildWeapon);
		fprintf(file, "%u,",  weapons[i].ParentWeapon);
		fprintf(file, "%u,",  weapons[i].WhoOwnsWeapon);
		fprintf(file, "%u",   weapons[i].RepairCount);
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

int write_effects_to_csv(const char *file_name, const Effect effects[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Child,Parent,Xpos,Ypos,Zpos,Xtile,Ytile,Status,Status_S,Affect,BaseFrame,Frame,OldFrame,Life,WhoShotMe,Model,Model_S,State,Angle,Angle_S,ZAngle,Owner\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,", offset_global + sizeof(Effect) * i);
		fprintf(file, "%zu,", offset_relative + sizeof(Effect) * i);
		fprintf(file, "%u,",  effects[i].Child);
		fprintf(file, "%u,",  effects[i].Parent);
		fprintf(file, "%i,",  effects[i].Xpos);
		fprintf(file, "%i,",  effects[i].Ypos);
		fprintf(file, "%i,",  effects[i].Zpos);
		fprintf(file, "%i,",  POS_TO_TILE(effects[i].Xpos));
		fprintf(file, "%i,",  POS_TO_TILE(effects[i].Ypos));
		fprintf(file, "%u,",  effects[i].Status);
		fprintf(file, "%s,",  thing_status_to_str(effects[i].Status));
		fprintf(file, "%u,",  effects[i].Affect);
		fprintf(file, "%u,",  effects[i].BaseFrame);
		fprintf(file, "%u,",  effects[i].Frame);
		fprintf(file, "%u,",  effects[i].OldFrame);
		fprintf(file, "%u,",  effects[i].Life);
		fprintf(file, "%u,",  effects[i].WhoShotMe);
		fprintf(file, "%u,",  effects[i].Model);
		fprintf(file, "%s,",  thing_model_to_str(effects[i].Model));
		fprintf(file, "%u,",  effects[i].State);
		fprintf(file, "%u,",  effects[i].Angle);
		fprintf(file, "%s,",  thing_angle_to_str(effects[i].Angle));
		fprintf(file, "%u,",  effects[i].ZAngle);
		fprintf(file, "%u",   effects[i].Owner);
		fprintf(file, "%s",   thing_type_to_str(effects[i].Owner));  // Not sure yet if translation makes sense here
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

int write_commands_to_csv(const char *file_name, const Command commands[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,LocOfs,Next,Data,DataType,GotoX,GotoY,GotoZ,State,State_S\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,", offset_global + sizeof(Command) * i);
		fprintf(file, "%zu,", offset_relative + sizeof(Command) * i);
		fprintf(file, "%zu,", sizeof(Command) * i);
		fprintf(file, "%u,",  commands[i].Next);
		fprintf(file, "%u,",  commands[i].Data);
		fprintf(file, "%s,",  thing_type_to_str(commands[i].Data));
		fprintf(file, "%u,",  commands[i].GotoX);
		fprintf(file, "%u,",  commands[i].GotoY);
		fprintf(file, "%u,",  commands[i].GotoZ);
		fprintf(file, "%u,",  commands[i].State);
		fprintf(file, "%s",   command_state_to_str(commands[i].State));
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

int write_worlds_to_csv(const char *file_name, const World worlds[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,WindXSpeed,WindYSpeed,Population,Temperature,WindSpeed,WindAngle,Industry,Crime,Gravity,Density,Unknown\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,", offset_global + sizeof(World) * i);
		fprintf(file, "%zu,", offset_relative + sizeof(World) * i);
		fprintf(file, "%u,",  worlds[i].WindXSpeed);
		fprintf(file, "%u,",  worlds[i].WindYSpeed);
		fprintf(file, "%u,",  worlds[i].Population);
		fprintf(file, "%u,",  worlds[i].Temperature);
		fprintf(file, "%u,",  worlds[i].WindSpeed);
		fprintf(file, "%u,",  worlds[i].WindAngle);
		fprintf(file, "%u,",  worlds[i].Industry);
		fprintf(file, "%u,",  worlds[i].Crime);
		fprintf(file, "%u,",  worlds[i].Gravity);
		fprintf(file, "%u,",  worlds[i].Density);
		fprintf(file, "%u",   worlds[i].Unknown);
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

int write_objectives_to_csv(const char *file_name, const Objective objectives[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "GloOfs,RelOfs,Status,Type,Type_S,Data,DataType,Xpos,Ypos,Zpos,Xtile,Ytile\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,", offset_global + sizeof(Objective) * i);
		fprintf(file, "%zu,", offset_relative + sizeof(Objective) * i);
		fprintf(file, "%u,",  objectives[i].Status);
		fprintf(file, "%u,",  objectives[i].Type);
		fprintf(file, "%s,",  objective_type_to_str(objectives[i].Type));
		fprintf(file, "%u,",  objectives[i].Data);
		fprintf(file, "%s,",  thing_type_to_str(objectives[i].Data));
		fprintf(file, "%i,",  objectives[i].Xpos);
		fprintf(file, "%i,",  objectives[i].Ypos);
		fprintf(file, "%i,",  objectives[i].Zpos);
		fprintf(file, "%i,",  POS_TO_TILE(objectives[i].Xpos));
		fprintf(file, "%i",   POS_TO_TILE(objectives[i].Ypos));
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

int write_cpobjectives_to_csv(const char *file_name, const CPObjective cpobjectives[], const size_t count, const size_t offset_global, const size_t offset_relative) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	//fprintf(file, "GloOfs,RelOfs,Index,Child,Parent,UseCount,Player,Flags,ActionType,ActionType_S,Action,Action_S,X,Y,Z\n");
	//fprintf(file, "GloOfs,RelOfs,Index,Parent,Child,UseCount,Player,Flags,ActionType,ActionType_S,Action,Action_S,X,Y,Z\n");
	fprintf(file, "GloOfs,RelOfs,Index,Prev,Next,UseCount,Player,Flags,ActionType,ActionType_S,Action,Action_S,X,Y,Z\n");
	for (size_t i = 0; i < count; i++) {
		fprintf(file, "%zu,", offset_global + sizeof(CPObjective) * i);
		fprintf(file, "%zu,", offset_relative + sizeof(CPObjective) * i);
		fprintf(file, "%zu,", i);
		//fprintf(file, "%u,",  cpobjectives[i].Child);
		//fprintf(file, "%u,",  cpobjectives[i].Parent);
		fprintf(file, "%u,",  cpobjectives[i].Parent);
		fprintf(file, "%u,",  cpobjectives[i].Child);
		fprintf(file, "%u,",  cpobjectives[i].UseCount);
		fprintf(file, "%u,",  cpobjectives[i].Player);
		fprintf(file, "%u,",  cpobjectives[i].Flags);
		fprintf(file, "%u,",  cpobjectives[i].ActionType);
		fprintf(file, "%s,",  cpobjective_actiontype_to_str(cpobjectives[i].ActionType));
		fprintf(file, "%u,",  cpobjectives[i].Action);
		fprintf(file, "%s,",  cpobjective_action_to_str(cpobjectives[i].ActionType, cpobjectives[i].Action));
		fprintf(file, "%i,",  cpobjectives[i].X);
		fprintf(file, "%i,",  cpobjectives[i].Y);
		fprintf(file, "%i",   cpobjectives[i].Z);
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

int write_structless_to_csv(const char *file_name, const GameData *gamedata) {

	// Create CSV file
	printf("Creating CSV file '%s'...\n", file_name);
	FILE *file = fopen(file_name, "wt");
	if (file == NULL) {
		fprintf(stderr, "Failed to create CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Write contents to CSV file
	printf("Writing contents to CSV file '%s'...\n", file_name);
	fprintf(file, "Seed,PersonCount,Timer,RelOfsBase,MapNumber,LoBoundaryx,LoBoundaryy,HiBoundaryx,HiBoundaryy,CPCount,CPTeamSize,CPProcInt,CPLvlInit,CPIsBombTeam,CPIsPersTeam,CPFlags,CPWeapon\n");
	fprintf(file, "%u,",  gamedata->Seed);
	fprintf(file, "%u,",  gamedata->PersonCount);
	fprintf(file, "%u,",  gamedata->Timer);
	fprintf(file, "%u,",  gamedata->RelOfsBase);
	fprintf(file, "%u,",  gamedata->MapNumber);
	fprintf(file, "%u,",  gamedata->LoBoundaryx);
	fprintf(file, "%u,",  gamedata->LoBoundaryy);
	fprintf(file, "%u,",  gamedata->HiBoundaryx);
	fprintf(file, "%u,",  gamedata->HiBoundaryy);
	fprintf(file, "%u,",  gamedata->CPCount);
	fprintf(file, "%u,",  gamedata->CPTeamSize);
	fprintf(file, "%u,",  gamedata->CPProcInt);
	fprintf(file, "%u,",  gamedata->CPLvlInit);
	fprintf(file, "%u,",  gamedata->CPIsBombTeam);
	fprintf(file, "%u,",  gamedata->CPIsPersTeam);
	fprintf(file, "%s,",  structless_cpflags_to_str(gamedata->CPFlags));
	fprintf(file, "%u",   gamedata->CPWeapon);
	fprintf(file, "\n");

	// Close CSV file
	printf("Closing CSV file '%s'...\n", file_name);
	if (fclose(file) != 0) {
		fprintf(stderr, "Failed to close CSV file '%s': %s\n", file_name, strerror(errno));
		return 1;
	}

	// Success
	return 0;
}
