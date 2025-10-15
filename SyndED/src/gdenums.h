/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - Game Data Enums                                        *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/14/25                                                 *
 *                                                                            *
 ******************************************************************************/

#ifndef GDENUMS_H
#define GDENUMS_H

#include "stpecpy.h"  // stpecpy; needs to be on top, modifies '#include <string.h>'

#include <string.h>   // strlen, strlcat


/******************************************************************************
 *                                                                            *
 *  Enum generator macros are based on this approach:                         *
 *  https://stackoverflow.com/a/10966395/1976617                              *
 *  (customized/extended to support flags and non-consecutive values)         *
 *                                                                            *
 *  Usage:                                                                    *
 *  1) Determine if enum should be VALUE-based or FLAG-based (bitmask)        *
 *  2) Copy&paste code from corresponding commented block (see below)         *
 *  3) Replace 'STRUCT_MEMBER' with '<STRUCT-NAME>_<MEMBER-NAME>'             *
 *  4) Replace 'StructMember'  with '<Struct-Name><Member-Name>'              *
 *  5) Replace 'struct_member' with '<struct-name>_<member-name>'             *
 *  6) Replace values/flags list below line                                   *
 *       '#define STRUCT_MEMBER_...(GENERATOR_FUNC)'                          *
 *     using format                                                           *
 *       'GENERATOR_FUNC(<PREFIX>_NAME, <VALUE>)'                             *
 *     with '<PREFIX>' being a unique identifier (e.g. first letter of        *
 *     struct name + first letter of member name)                             *
 *  7) Cut&paste _to_str function implementation from end of block to         *
 *     'gdenums.c'                                                            *
 *                                                                            *
 ******************************************************************************/

#define GENERATE_ENUM_LINES(NAME, VALUE) NAME = VALUE,

#define GENERATE_TOSTR_VALUES(ENUM_MACRO)            \
	switch (value) {                                 \
		ENUM_MACRO(GENERATE_VALUES_LINES)            \
		default: return "VALUE_UNDEFINED";           \
	}

#define GENERATE_VALUES_LINES(NAME, VALUE)           \
	case VALUE: return #NAME;

#define GENERATE_TOSTR_FLAGS(ENUM_MACRO, NAME_NONE)  \
	static char buffer[1024];                        \
	                                                 \
	if (value == NAME_NONE)                          \
		return #NAME_NONE;                           \
	                                                 \
	char *pcur = buffer;                             \
	char *pend = buffer + sizeof(buffer);            \
	buffer[0] = '\0';                                \
	                                                 \
	ENUM_MACRO(GENERATE_FLAGS_LINES)                 \
	                                                 \
	if (pcur == NULL)                                \
		return "STR_TOO_LONG";                       \
	                                                 \
	size_t len = strlen(buffer);                     \
	if (len > 3)                                     \
		buffer[len - 3] = '\0';                      \
	                                                 \
	return buffer;

#define GENERATE_FLAGS_LINES(NAME, VALUE)            \
	if (value & NAME)                                \
		pcur = stpecpy(pcur, pend, #NAME " | ");


/* ----------- For VALUE-based enum -----------

#define STRUCT_MEMBER_VALUES(GENERATOR_FUNC)  \
	GENERATOR_FUNC(SM_VALUE_03, 0x03)         \
	GENERATOR_FUNC(SM_VALUE_05, 0x05)         \
	GENERATOR_FUNC(SM_VALUE_99, 0x99)         \
	GENERATOR_FUNC(SM_VALUE_C0, 0xC0)         \
	GENERATOR_FUNC(SM_VALUE_FB, 0xFB)

typedef enum {
	STRUCT_MEMBER_VALUES(GENERATE_ENUM_LINES)
} StructMember;

const char* struct_member_to_str(const StructMember value);

const char* struct_member_to_str(const StructMember value) {
	GENERATE_TOSTR_VALUES(STRUCT_MEMBER_VALUES)
}

*/


/* ------ For FLAG-based (bitmask) enum ------

#define STRUCT_MEMBER_FLAGS(GENERATOR_FUNC)  \
	GENERATOR_FUNC(SM_NONE,    0x00)         \
	GENERATOR_FUNC(SM_FLAG_01, 0x01)         \
	GENERATOR_FUNC(SM_FLAG_02, 0x02)         \
	GENERATOR_FUNC(SM_FLAG_04, 0x04)         \
	GENERATOR_FUNC(SM_FLAG_08, 0x08)         \
	GENERATOR_FUNC(SM_FLAG_10, 0x10)

typedef enum {
	STRUCT_MEMBER_FLAGS(GENERATE_ENUM_LINES)
} StructMember;

const char* struct_member_to_str(const StructMember value);

const char* struct_member_to_str(const StructMember value) {
	GENERATE_TOSTR_FLAGS(STRUCT_MEMBER_FLAGS, SM_NONE)
}

*/


/******************************************************************************
 *                                                                            *
 *  Thing (universal for Person, Vehicle, Object, Weapon, Effect)             *
 *                                                                            *
 ******************************************************************************/

#define THING_STATUS_FLAGS(GENERATOR_FUNC)   \
	GENERATOR_FUNC(TS_NONE,            0x0)  \
	GENERATOR_FUNC(TS_NODRAW,          0x1)  \
	GENERATOR_FUNC(TS_UNKNOWN_2,       0x2)  \
	GENERATOR_FUNC(TS_MAPWHO,          0x4)  \
	GENERATOR_FUNC(TS_DEAD,            0x8)  \
	GENERATOR_FUNC(TS_UNKNOWN_10,     0x10)  \
	GENERATOR_FUNC(TS_UNKNOWN_20,     0x20)  \
	GENERATOR_FUNC(TS_UNKNOWN_40,     0x40)  \
	GENERATOR_FUNC(TS_UNKNOWN_80,     0x80)  \
	GENERATOR_FUNC(TS_UNKNOWN_100,   0x100)  \
	GENERATOR_FUNC(TS_FLY_BACK,      0x200)  \
	GENERATOR_FUNC(TS_UNKNOWN_400,   0x400)  \
	GENERATOR_FUNC(TS_UNKNOWN_800,   0x800)  \
	GENERATOR_FUNC(TS_UNKNOWN_1000, 0x1000)  \
	GENERATOR_FUNC(TS_UNKNOWN_2000, 0x2000)  \
	GENERATOR_FUNC(TS_UNKNOWN_4000, 0x4000)  \
	GENERATOR_FUNC(TS_UNKNOWN_8000, 0x8000)

typedef enum {
	THING_STATUS_FLAGS(GENERATE_ENUM_LINES)
} ThingStatus;

const char* thing_status_to_str(const ThingStatus value);


#define THING_MODEL_VALUES(GENERATOR_FUNC)  \
	GENERATOR_FUNC(TM_NONE,    0x00)        \
	GENERATOR_FUNC(TM_PERSON,  0x01)        \
	GENERATOR_FUNC(TM_VEHICLE, 0x02)        \
	GENERATOR_FUNC(TM_EFFECT,  0x03)        \
	GENERATOR_FUNC(TM_WEAPON,  0x04)        \
	GENERATOR_FUNC(TM_OBJECT,  0x05)

typedef enum {
	THING_MODEL_VALUES(GENERATE_ENUM_LINES)
} ThingModel;

const char* thing_model_to_str(const ThingModel value);


#define THING_ANGLE_VALUES(GENERATOR_FUNC)  \
	GENERATOR_FUNC(TA_SOUTHWEST, 0x00)      \
	GENERATOR_FUNC(TA_SOUTH,     0x20)      \
	GENERATOR_FUNC(TA_SOUTHEAST, 0x40)      \
	GENERATOR_FUNC(TA_EAST,      0x60)      \
	GENERATOR_FUNC(TA_NORTHEAST, 0x80)      \
	GENERATOR_FUNC(TA_NORTH,     0xA0)      \
	GENERATOR_FUNC(TA_NORTHWEST, 0xC0)      \
	GENERATOR_FUNC(TA_WEST,      0xE0)

typedef enum {
	THING_ANGLE_VALUES(GENERATE_ENUM_LINES)
} ThingAngle;

const char* thing_angle_to_str(const ThingAngle value);


/******************************************************************************
 *                                                                            *
 *  Person                                                                    *
 *                                                                            *
 ******************************************************************************/

#define PERSON_AFFECT_FLAGS(GENERATOR_FUNC)     \
	GENERATOR_FUNC(PA_NONE,               0x0)  \
	GENERATOR_FUNC(PA_HIT_BY_VEHICLE,     0x1)  \
	GENERATOR_FUNC(PA_UNKNOWN_2,          0x2)  \
	GENERATOR_FUNC(PA_UNKNOWN_4,          0x4)  \
	GENERATOR_FUNC(PA_HIT_BY_FIRE,        0x8)  \
	GENERATOR_FUNC(PA_HIT_BY_LASER,      0x10)  \
	GENERATOR_FUNC(PA_UNKNOWN_20,        0x20)  \
	GENERATOR_FUNC(PA_HIT_BY_BULLET,     0x40)  \
	GENERATOR_FUNC(PA_HIT_BY_EXPLOSION,  0x80)  \
	GENERATOR_FUNC(PA_UNKNOWN_100,      0x100)  \
	GENERATOR_FUNC(PA_UNKNOWN_200,      0x200)  \
	GENERATOR_FUNC(PA_HIT_BY_PERSUADER, 0x400)

typedef enum {
	PERSON_AFFECT_FLAGS(GENERATE_ENUM_LINES)
} PersonAffect;

const char* person_affect_to_str(const PersonAffect value);


#define PERSON_BASEFRAME_VALUES(GENERATOR_FUNC)  \
	GENERATOR_FUNC(PB_NONE,             0)       \
	GENERATOR_FUNC(PB_AGENT,            1)       \
	GENERATOR_FUNC(PB_WOMAN_BLONDE,   626)       \
	GENERATOR_FUNC(PB_POLICE,         833)       \
	GENERATOR_FUNC(PB_WOMAN_REDHEAD, 1123)       \
	GENERATOR_FUNC(PB_MAN_SUIT,      1330)       \
	GENERATOR_FUNC(PB_SOLDIER,       1537)       \
	GENERATOR_FUNC(PB_MAN_JACKET,    1744)

typedef enum {
	PERSON_BASEFRAME_VALUES(GENERATE_ENUM_LINES)
} PersonBaseframe;

const char* person_baseframe_to_str(const PersonBaseframe value);


#define PERSON_STATE_VALUES(GENERATOR_FUNC)       \
	GENERATOR_FUNC(PS_NONE,                 0x0)  \
	GENERATOR_FUNC(PS_NEXT_COMMAND,         0x1)  \
	GENERATOR_FUNC(PS_GOTO_POINT2,          0x2)  \
	GENERATOR_FUNC(PS_GOTO_POINT3,          0x3)  \
	GENERATOR_FUNC(PS_GOTO_STRUCTURE4,      0x4)  \
	GENERATOR_FUNC(PS_GOTO_STRUCTURE5,      0x5)  \
	GENERATOR_FUNC(PS_MOVE_INTO_VEHICLE,    0x6)  \
	GENERATOR_FUNC(PS_MOVE_OUT_OF_VEHICLE,  0x7)  \
	GENERATOR_FUNC(PS_PASSENGER,            0x8)  \
	GENERATOR_FUNC(PS_PICKUP_WEAPON,        0x9)  \
	GENERATOR_FUNC(PS_DROP_WEAPON,          0xA)  \
	GENERATOR_FUNC(PS_SELECT_WEAPON,        0xB)  \
	GENERATOR_FUNC(PS_WAIT_FOR_MODEL,       0xC)  \
	GENERATOR_FUNC(PS_WAIT_FOR_TIME,        0xD)  \
	GENERATOR_FUNC(PS_HUG_RIGHT,            0xE)  \
	GENERATOR_FUNC(PS_HUG_LEFT,             0xF)  \
	GENERATOR_FUNC(PS_WAITING_TO_MOVE,     0x10)  \
	GENERATOR_FUNC(PS_HIT_BY_LASER,        0x11)  \
	GENERATOR_FUNC(PS_HIT_BY_BULLET,       0x12)  \
	GENERATOR_FUNC(PS_HIT_BY_VEHICLE,      0x13)  \
	GENERATOR_FUNC(PS_HIT_BY_FIRE,         0x14)  \
	GENERATOR_FUNC(PS_HIT_BY_EXPLOSION,    0x15)  \
	GENERATOR_FUNC(PS_FLY_BACK,            0x16)  \
	GENERATOR_FUNC(PS_ON_FIRE,             0x17)  \
	GENERATOR_FUNC(PS_DYING,               0x18)  \
	GENERATOR_FUNC(PS_DYING_ON_FIRE,       0x19)  \
	GENERATOR_FUNC(PS_DEAD,                0x1A)  \
	GENERATOR_FUNC(PS_DEAD_ON_FIRE,        0x1B)  \
	GENERATOR_FUNC(PS_GUARD_AREA,          0x1C)  \
	GENERATOR_FUNC(PS_WANDER,              0x1D)  \
	GENERATOR_FUNC(PS_PERSUADED,           0x1E)  \
	GENERATOR_FUNC(PS_RUNAWAY,             0x1F)  \
	GENERATOR_FUNC(PS_FOLLOW_AND_ATTACK,   0x20)  \
	GENERATOR_FUNC(PS_DROWN,               0x21)  \
	GENERATOR_FUNC(PS_GIVE_WARNING,        0x22)  \
	GENERATOR_FUNC(PS_ASHES,               0x23)  \
	GENERATOR_FUNC(PS_CHECK_CROSS_ROAD,    0x24)  \
	GENERATOR_FUNC(PS_CROSS_ROAD,          0x25)  \
	GENERATOR_FUNC(PS_WAIT_TO_CROSS_ROAD,  0x26)  \
	GENERATOR_FUNC(PS_WALK_OFF_ROAD,       0x27)  \
	GENERATOR_FUNC(PS_WAIT_FOR_TRIGGER,    0x28)  \
	GENERATOR_FUNC(PS_WAIT_FOR_TRAIN,      0x29)  \
	GENERATOR_FUNC(PS_ALLOW_PASSENGERS,    0x2A)  \
	GENERATOR_FUNC(PS_USE_WEAPON,          0x2B)  \
	GENERATOR_FUNC(PS_BEING_PERSUADED,     0x2C)  \
	GENERATOR_FUNC(PS_TOTAL_STATES,        0x2D)

typedef enum {
	PERSON_STATE_VALUES(GENERATE_ENUM_LINES)
} PersonState;

const char* person_state_to_str(const PersonState value);


#define PERSON_UNIQUE_FLAGS(GENERATOR_FUNC)  \
	GENERATOR_FUNC(PU_NONE,     0x00)        \
	GENERATOR_FUNC(PU_CIVILIAN, 0x01)        \
	GENERATOR_FUNC(PU_AGENT,    0x02)        \
	GENERATOR_FUNC(PU_POLICE,   0x04)        \
	GENERATOR_FUNC(PU_GUARD,    0x08)        \
	GENERATOR_FUNC(PU_CRIMINAL, 0x10)

typedef enum {
	PERSON_UNIQUE_FLAGS(GENERATE_ENUM_LINES)
} PersonUnique;

const char* person_unique_to_str(const PersonUnique value);


/******************************************************************************
 *                                                                            *
 *  Vehicle                                                                   *
 *                                                                            *
 ******************************************************************************/

#define VEHICLE_STATE_VALUES(GENERATOR_FUNC)       \
	GENERATOR_FUNC(VS_NONE,                  0x0)  \
	GENERATOR_FUNC(VS_APC,                   0x1)  \
	GENERATOR_FUNC(VS_APC_MOVING,            0x2)  \
	GENERATOR_FUNC(VS_APC_ON_FIRE,           0x3)  \
	GENERATOR_FUNC(VS_APC_DESTROYED,         0x4)  \
	GENERATOR_FUNC(VS_TRAIN,                 0x5)  \
	GENERATOR_FUNC(VS_TRAIN_MOVING,          0x6)  \
	GENERATOR_FUNC(VS_TRAIN_ON_FIRE,         0x7)  \
	GENERATOR_FUNC(VS_TRAIN_DESTROYED,       0x8)  \
	GENERATOR_FUNC(VS_CARRIAGE,              0x9)  \
	GENERATOR_FUNC(VS_CARRIAGE_MOVING,       0xA)  \
	GENERATOR_FUNC(VS_CARRIAGE_ON_FIRE,      0xB)  \
	GENERATOR_FUNC(VS_CARRIAGE_DESTROYED,    0xC)  \
	GENERATOR_FUNC(VS_CIVILCAR,              0xD)  \
	GENERATOR_FUNC(VS_CIVILCAR_MOVING,       0xE)  \
	GENERATOR_FUNC(VS_CIVILCAR_ON_FIRE,      0xF)  \
	GENERATOR_FUNC(VS_CIVILCAR_DESTROYED,   0x10)  \
	GENERATOR_FUNC(VS_FIREENGINE,           0x11)  \
	GENERATOR_FUNC(VS_FIREENGINE_MOVING,    0x12)  \
	GENERATOR_FUNC(VS_FIREENGINE_ON_FIRE,   0x13)  \
	GENERATOR_FUNC(VS_FIREENGINE_DESTROYED, 0x14)  \
	GENERATOR_FUNC(VS_UNKNOWN_15,           0x15)  \
	GENERATOR_FUNC(VS_UNKNOWN_16,           0x16)  \
	GENERATOR_FUNC(VS_UNKNOWN_17,           0x17)  \
	GENERATOR_FUNC(VS_UNKNOWN_18,           0x18)  \
	GENERATOR_FUNC(VS_UNKNOWN_19,           0x19)  \
	GENERATOR_FUNC(VS_UNKNOWN_1A,           0x1A)  \
	GENERATOR_FUNC(VS_UNKNOWN_1B,           0x1B)  \
	GENERATOR_FUNC(VS_INDUSTRIAL,           0x1C)  \
	GENERATOR_FUNC(VS_INDUSTRIAL_MOVING,    0x1D)  \
	GENERATOR_FUNC(VS_INDUSTRIAL_ON_FIRE,   0x1E)  \
	GENERATOR_FUNC(VS_INDUSTRIAL_DESTROYED, 0x1F)  \
	GENERATOR_FUNC(VS_UNKNOWN_20,           0x20)  \
	GENERATOR_FUNC(VS_UNKNOWN_21,           0x21)  \
	GENERATOR_FUNC(VS_UNKNOWN_22,           0x22)  \
	GENERATOR_FUNC(VS_UNKNOWN_23,           0x23)  \
	GENERATOR_FUNC(VS_POLICECAR,            0x24)  \
	GENERATOR_FUNC(VS_POLICECAR_MOVING,     0x25)  \
	GENERATOR_FUNC(VS_POLICECAR_ON_FIRE,    0x26)  \
	GENERATOR_FUNC(VS_POLICECAR_DESTROYED,  0x27)  \
	GENERATOR_FUNC(VS_AMBULANCE,            0x28)  \
	GENERATOR_FUNC(VS_AMBULANCE_MOVING,     0x29)  \
	GENERATOR_FUNC(VS_AMBULANCE_ON_FIRE,    0x2A)  \
	GENERATOR_FUNC(VS_AMBULANCE_DESTROYED,  0x2B)  \
	GENERATOR_FUNC(VS_STATES_COUNT,         0x2C)

typedef enum {
	VEHICLE_STATE_VALUES(GENERATE_ENUM_LINES)
} VehicleState;

const char* vehicle_state_to_str(const VehicleState value);


/******************************************************************************
 *                                                                            *
 *  Weapon                                                                    *
 *                                                                            *
 ******************************************************************************/

#define WEAPON_STATE_VALUES(GENERATOR_FUNC)  \
	GENERATOR_FUNC(WS_NONE,          0x00)   \
	GENERATOR_FUNC(WS_PERSUADERTRON, 0x01)   \
	GENERATOR_FUNC(WS_PISTOL,        0x02)   \
	GENERATOR_FUNC(WS_GAUSS_GUN,     0x03)   \
	GENERATOR_FUNC(WS_SHOTGUN,       0x04)   \
	GENERATOR_FUNC(WS_UZI,           0x05)   \
	GENERATOR_FUNC(WS_MINIGUN,       0x06)   \
	GENERATOR_FUNC(WS_LASER,         0x07)   \
	GENERATOR_FUNC(WS_FLAMER,        0x08)   \
	GENERATOR_FUNC(WS_LONG_RANGE,    0x09)   \
	GENERATOR_FUNC(WS_SCANNER,       0x0A)   \
	GENERATOR_FUNC(WS_MEDIKIT,       0x0B)   \
	GENERATOR_FUNC(WS_TIME_BOMB,     0x0C)   \
	GENERATOR_FUNC(WS_ACCESS_CARD,   0x0D)   \
	GENERATOR_FUNC(WS_UNUSED_14,     0x0E)   \
	GENERATOR_FUNC(WS_UNUSED_15,     0x0F)   \
	GENERATOR_FUNC(WS_AUTO_MAPPER,   0x10)   \
	GENERATOR_FUNC(WS_ENERGY_SHIELD, 0x11)   \
	GENERATOR_FUNC(WS_UNUSED_18,     0x12)   \
	GENERATOR_FUNC(WS_UNUSED_19,     0x13)

typedef enum {
	WEAPON_STATE_VALUES(GENERATE_ENUM_LINES)
} WeaponState;

const char* weapon_state_to_str(const WeaponState value);


/******************************************************************************
 *                                                                            *
 *  Command                                                                   *
 *                                                                            *
 ******************************************************************************/

#define COMMAND_STATE_VALUES(GENERATOR_FUNC)   \
	GENERATOR_FUNC(CS_NONE,             0x00)  \
	GENERATOR_FUNC(CS_GOTO_POINT,       0x01)  \
	GENERATOR_FUNC(CS_USE_VEHICLE,      0x02)  \
	GENERATOR_FUNC(CS_LEAVE_VEHICLE,    0x03)  \
	GENERATOR_FUNC(CS_WAIT_FOR_MODEL,   0x04)  \
	GENERATOR_FUNC(CS_WAIT_FOR_TIME,    0x05)  \
	GENERATOR_FUNC(CS_GOTO_STRUCTURE,   0x06)  \
	GENERATOR_FUNC(CS_FAIL_LEVEL,       0x07)  \
	GENERATOR_FUNC(CS_WAIT_FOR_TRIGGER, 0x08)  \
	GENERATOR_FUNC(CS_END_COMMANDS,     0x09)  \
	GENERATOR_FUNC(CS_WAIT_PASSENGERS,  0x0A)  \
	GENERATOR_FUNC(CS_COMPLETE_LEVEL,   0x0B)  \
	GENERATOR_FUNC(CS_TOTAL_COMMANDS,   0x0C)

typedef enum {
	COMMAND_STATE_VALUES(GENERATE_ENUM_LINES)
} CommandState;

const char* command_state_to_str(const CommandState value);


#endif // GDENUMS_H
