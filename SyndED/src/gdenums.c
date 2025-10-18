/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - Game Data Enums                                        *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/14/25                                                 *
 *                                                                            *
 ******************************************************************************/

#include "gdenums.h"   // related header

#include "gamedata.h"  // *_RELATIVE_OFFSET

const char* thing_status_to_str(const ThingStatus value) {
	GENERATE_TOSTR_FLAGS(THING_STATUS_FLAGS, TS_NONE)
}

const char* thing_model_to_str(const ThingModel value) {
	GENERATE_TOSTR_VALUES(THING_MODEL_VALUES)
}

const char* thing_angle_to_str(const ThingAngle value) {
	//GENERATE_TOSTR_VALUES(THING_ANGLE_VALUES)
	if (value >= 0xF0 || value <= 0x0F)
		return "TA_SOUTHWEST";
	else if (value >= 0x10 && value <= 0x2F)
		return "TA_SOUTH";
	else if (value >= 0x30 && value <= 0x4F)
		return "TA_SOUTHEAST";
	else if (value >= 0x50 && value <= 0x6F)
		return "TA_EAST";
	else if (value >= 0x70 && value <= 0x8F)
		return "TA_NORTHEAST";
	else if (value >= 0x90 && value <= 0xAF)
		return "TA_NORTH";
	else if (value >= 0xB0 && value <= 0xCF)
		return "TA_NORTHWEST";
	//else if (value >= 0xD0 && value <= 0xEF)
	else
		return "TA_WEST";
}

const char* thing_type_to_str(const uint16_t relofs) {
	if (relofs == 0)
		return "TT_NONE";
	else if (relofs >= PEOPLE_RELATIVE_OFFSET && relofs < VEHICLES_RELATIVE_OFFSET)
		return "TT_PERSON";
	else if (relofs >= VEHICLES_RELATIVE_OFFSET && relofs < OBJECTS_RELATIVE_OFFSET)
		return "TT_VEHICLE";
	else if (relofs >= OBJECTS_RELATIVE_OFFSET && relofs < WEAPONS_RELATIVE_OFFSET)
		return "TT_OBJECT";
	else if (relofs >= WEAPONS_RELATIVE_OFFSET && relofs < EFFECTS_RELATIVE_OFFSET)
		return "TT_WEAPON";
	else if (relofs >= EFFECTS_RELATIVE_OFFSET && relofs < COMMANDS_RELATIVE_OFFSET)
		return "TT_EFFECT";
	else
		return "TT_NOT_A_THING";
}

const char* person_affect_to_str(const PersonAffect value) {
	GENERATE_TOSTR_FLAGS(PERSON_AFFECT_FLAGS, PA_NONE)
}

const char* person_baseframe_to_str(const PersonBaseframe value) {
	GENERATE_TOSTR_VALUES(PERSON_BASEFRAME_VALUES)
}

const char* person_state_to_str(const PersonState value) {
	GENERATE_TOSTR_VALUES(PERSON_STATE_VALUES)
}

const char* person_unique_to_str(const PersonUnique value) {
	GENERATE_TOSTR_FLAGS(PERSON_UNIQUE_FLAGS, PU_NONE)
}

const char* vehicle_state_to_str(const VehicleState value) {
	GENERATE_TOSTR_VALUES(VEHICLE_STATE_VALUES)
}

const char* weapon_state_to_str(const WeaponState value) {
	GENERATE_TOSTR_VALUES(WEAPON_STATE_VALUES)
}

const char* command_state_to_str(const CommandState value) {
	GENERATE_TOSTR_VALUES(COMMAND_STATE_VALUES)
}

const char* objective_type_to_str(const ObjectiveType value) {
	GENERATE_TOSTR_VALUES(OBJECTIVE_TYPE_VALUES)
}

const char* cpobjective_actiontype_to_str(const CPObjectiveActionType value) {
	GENERATE_TOSTR_VALUES(CPOBJECTIVE_ACTIONTYPE_VALUES)
}

const char* cpobjective_atmove_action_to_str(const CPObjectiveATMoveAction value) {
	GENERATE_TOSTR_VALUES(CPOBJECTIVE_ATMOVE_ACTION_VALUES)
}

const char* cpobjective_action_to_str(const CPObjectiveActionType actiontype, const int action) {
	switch (actiontype) {
		case CPOAT_MOVE:
			return cpobjective_atmove_action_to_str(action);
		default:
			if (action == 0)
				return "CPOA_NONE";
			else
				return "VALUE_UNDEFINED";
	}
}

const char* structless_cpflags_to_str(const StructlessCPFlags value) {
	GENERATE_TOSTR_FLAGS(STRUCTLESS_CPFLAGS_FLAGS, CPF_NONE)
}
