#ifndef GDENUMS_H
#define GDENUMS_H


/*******************************************************************************
 *                                                                             *
 *  Enum generator macros are based on this approach                           *
 *  (but customized to support non-consecutive enums):                         *
 *  https://stackoverflow.com/a/10966395/1976617                               *
 *                                                                             *
 *  Usage:                                                                     *
 *  1) Copy entire commented block from '#define' until '#undef'               *
 *  2) Replace 'STRUCT_MEMBER' with '<STRUCT-NAME>_<MEMBER-NAME>'              *
 *  3) Replace 'StructMember'  with '<Struct-Name><Member-Name>'               *
 *  4) Replace 'struct_member' with '<struct-name>_<member-name>'              *
 *  5) Replace value list below '#define STRUCT_MEMBER(GENERATOR_FUNC)'        *
 *     using format 'GENERATOR_FUNC( <PREFIX>_NAME, <VALUE> )', with           *
 *     <PREFIX> being a unique identifier (e.g. first letter of struct         *
 *     name + first letter of member name)                                     *
 *                                                                             *
 ******************************************************************************/

#define GENERATE_ENUM_LINES(NAME, VALUE) NAME = VALUE,

#define GENERATE_SWITCH_CASE(ENUM_MACRO)  \
	switch (value) {                      \
		ENUM_MACRO(GENERATE_CASE_LINES)   \
		default: return "UNDEFINED";      \
	}

#define GENERATE_CASE_LINES(STRING, VALUE)  \
	case VALUE: return #STRING;


/*
#define STRUCT_MEMBER(GENERATOR_FUNC)   \
	GENERATOR_FUNC(SM_NONE,      0x00)  \
	GENERATOR_FUNC(SM_SOMETHING, 0x01)  \
	GENERATOR_FUNC(SM_SOMETHING, 0x02)  \
	GENERATOR_FUNC(SM_SOMETHING, 0x04)  \
	GENERATOR_FUNC(SM_SOMETHING, 0x10)

enum StructMember {
	STRUCT_MEMBER(GENERATE_ENUM_LINES)
};

static const char* struct_member_to_str(const enum StructMember value) {
	GENERATE_SWITCH_CASE(STRUCT_MEMBER)
}
#undef STRUCT_MEMBER
*/


/*******************************************************************************
 *  Thing (i.e. universal for Person, Vehicle, Object, Weapon, Effect)         *
 ******************************************************************************/

#define THING_STATUS(GENERATOR_FUNC)     \
	GENERATOR_FUNC(TS_NONE,       0x00)  \
	GENERATOR_FUNC(TS_UNKNOWN_1,  0x01)  \
	GENERATOR_FUNC(TS_UNKNOWN_2,  0x02)  \
	GENERATOR_FUNC(TS_INMAPWHO,   0x04)  \
	GENERATOR_FUNC(TS_UNKNOWN_8,  0x08)  \
	GENERATOR_FUNC(TS_UNKNOWN_10, 0x10)

enum ThingStatus {
	THING_STATUS(GENERATE_ENUM_LINES)
};

static const char* thing_status_to_str(const enum ThingStatus value) {
	GENERATE_SWITCH_CASE(THING_STATUS)
}
#undef THING_STATUS


#define THING_MODEL(GENERATOR_FUNC)    \
	GENERATOR_FUNC(TM_NONE,     0x00)  \
	GENERATOR_FUNC(TM_PERSON,   0x01)  \
	GENERATOR_FUNC(TM_VEHICLE,  0x02)  \
	GENERATOR_FUNC(TM_EFFECT,   0x03)  \
	GENERATOR_FUNC(TM_WEAPON,   0x04)  \
	GENERATOR_FUNC(TM_OBJECT,   0x05)

enum ThingModel {
	THING_MODEL(GENERATE_ENUM_LINES)
};

static const char* thing_model_to_str(const enum ThingModel value) {
	GENERATE_SWITCH_CASE(THING_MODEL)
}
#undef THING_MODEL


/*******************************************************************************
 *  Person                                                                     *
 ******************************************************************************/

#define PERSON_AFFECT(GENERATOR_FUNC)           \
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

enum PersonAffect {
	PERSON_AFFECT(GENERATE_ENUM_LINES)
};

static const char* person_affect_to_str(const enum PersonAffect value) {
	GENERATE_SWITCH_CASE(PERSON_AFFECT)
}
#undef PERSON_AFFECT


#define PERSON_BASEFRAME(GENERATOR_FUNC)    \
	GENERATOR_FUNC(PB_NONE,             0)  \
	GENERATOR_FUNC(PB_AGENT,            1)  \
	GENERATOR_FUNC(PB_WOMAN_BLONDE,   626)  \
	GENERATOR_FUNC(PB_POLICE,         833)  \
	GENERATOR_FUNC(PB_WOMAN_REDHEAD, 1123)  \
	GENERATOR_FUNC(PB_MAN_SUIT,      1330)  \
	GENERATOR_FUNC(PB_SOLDIER,       1537)  \
	GENERATOR_FUNC(PB_MAN_JACKET,    1744)

enum PersonBaseframe {
	PERSON_BASEFRAME(GENERATE_ENUM_LINES)
};

static const char* person_baseframe_to_str(const enum PersonBaseframe value) {
	GENERATE_SWITCH_CASE(PERSON_BASEFRAME)
}
#undef PERSON_BASEFRAME


#define PERSON_STATE(GENERATOR_FUNC)             \
	GENERATOR_FUNC(PS_NONE,                0x0)  \
	GENERATOR_FUNC(PS_NEXT_COMMAND,        0x1)  \
	GENERATOR_FUNC(PS_GOTO_POINT2,         0x2)  \
	GENERATOR_FUNC(PS_GOTO_POINT3,         0x3)  \
	GENERATOR_FUNC(PS_GOTO_STRUCTURE4,     0x4)  \
	GENERATOR_FUNC(PS_GOTO_STRUCTURE5,     0x5)  \
	GENERATOR_FUNC(PS_MOVE_INTO_VEHICLE,   0x6)  \
	GENERATOR_FUNC(PS_MOVE_OUT_OF_VEHICLE, 0x7)  \
	GENERATOR_FUNC(PS_PASSENGER,           0x8)  \
	GENERATOR_FUNC(PS_PICKUP_WEAPON,       0x9)  \
	GENERATOR_FUNC(PS_DROP_WEAPON,         0xA)  \
	GENERATOR_FUNC(PS_SELECT_WEAPON,       0xB)  \
	GENERATOR_FUNC(PS_WAIT_FOR_MODEL,      0xC)  \
	GENERATOR_FUNC(PS_WAIT_FOR_TIME,       0xD)  \
	GENERATOR_FUNC(PS_HUG_RIGHT,           0xE)  \
	GENERATOR_FUNC(PS_HUG_LEFT,            0xF)  \
	GENERATOR_FUNC(PS_WAITING_TO_MOVE,    0x10)  \
	GENERATOR_FUNC(PS_HIT_BY_LASER,       0x11)  \
	GENERATOR_FUNC(PS_HIT_BY_BULLET,      0x12)  \
	GENERATOR_FUNC(PS_HIT_BY_VEHICLE,     0x13)  \
	GENERATOR_FUNC(PS_HIT_BY_FIRE,        0x14)  \
	GENERATOR_FUNC(PS_HIT_BY_EXPLOSION,   0x15)  \
	GENERATOR_FUNC(PS_FLY_BACK,           0x16)  \
	GENERATOR_FUNC(PS_ON_FIRE,            0x17)  \
	GENERATOR_FUNC(PS_DYING,              0x18)  \
	GENERATOR_FUNC(PS_DYING_ON_FIRE,      0x19)  \
	GENERATOR_FUNC(PS_DEAD,               0x1A)  \
	GENERATOR_FUNC(PS_DEAD_ON_FIRE,       0x1B)  \
	GENERATOR_FUNC(PS_GUARD_AREA,         0x1C)  \
	GENERATOR_FUNC(PS_WANDER,             0x1D)  \
	GENERATOR_FUNC(PS_PERSUADED,          0x1E)  \
	GENERATOR_FUNC(PS_RUNAWAY,            0x1F)  \
	GENERATOR_FUNC(PS_FOLLOW_AND_ATTACK,  0x20)  \
	GENERATOR_FUNC(PS_DROWN,              0x21)  \
	GENERATOR_FUNC(PS_GIVE_WARNING,       0x22)  \
	GENERATOR_FUNC(PS_ASHES,              0x23)  \
	GENERATOR_FUNC(PS_CHECK_CROSS_ROAD,   0x24)  \
	GENERATOR_FUNC(PS_CROSS_ROAD,         0x25)  \
	GENERATOR_FUNC(PS_WAIT_TO_CROSS_ROAD, 0x26)  \
	GENERATOR_FUNC(PS_WALK_OFF_ROAD,      0x27)  \
	GENERATOR_FUNC(PS_WAIT_FOR_TRIGGER,   0x28)  \
	GENERATOR_FUNC(PS_WAIT_FOR_TRAIN,     0x29)  \
	GENERATOR_FUNC(PS_ALLOW_PASSENGERS,   0x2A)  \
	GENERATOR_FUNC(PS_USE_WEAPON,         0x2B)  \
	GENERATOR_FUNC(PS_BEING_PERSUADED,    0x2C)  \
	GENERATOR_FUNC(PS_TOTAL_STATES,       0x2D)

enum PersonState {
	PERSON_STATE(GENERATE_ENUM_LINES)
};

static const char* person_state_to_str(const enum PersonState value) {
	GENERATE_SWITCH_CASE(PERSON_STATE)
}
#undef PERSON_STATE


#define PERSON_UNIQUE(GENERATOR_FUNC)  \
	GENERATOR_FUNC(PU_NONE,     0x00)  \
	GENERATOR_FUNC(PU_CIVILIAN, 0x01)  \
	GENERATOR_FUNC(PU_AGENT,    0x02)  \
	GENERATOR_FUNC(PU_POLICE,   0x04)  \
	GENERATOR_FUNC(PU_GUARD,    0x08)  \
	GENERATOR_FUNC(PU_CRIMINAL, 0x10)

enum PersonUnique {
	PERSON_UNIQUE(GENERATE_ENUM_LINES)
};

static const char* person_unique_to_str(const enum PersonUnique value) {
	GENERATE_SWITCH_CASE(PERSON_UNIQUE)
}
#undef PERSON_UNIQUE


/*******************************************************************************
 *  Weapon                                                                     *
 ******************************************************************************/

#define WEAPON_STATE(GENERATOR_FUNC)         \
	GENERATOR_FUNC(WS_NONE,           0x00)  \
	GENERATOR_FUNC(WS_PERSUADERTRON,  0x01)  \
	GENERATOR_FUNC(WS_PISTOL,         0x02)  \
	GENERATOR_FUNC(WS_GAUSS_GUN,      0x03)  \
	GENERATOR_FUNC(WS_SHOTGUN,        0x04)  \
	GENERATOR_FUNC(WS_UZI,            0x05)  \
	GENERATOR_FUNC(WS_MINIGUN,        0x06)  \
	GENERATOR_FUNC(WS_LASER,          0x07)  \
	GENERATOR_FUNC(WS_FLAMER,         0x08)  \
	GENERATOR_FUNC(WS_LONG_RANGE,     0x09)  \
	GENERATOR_FUNC(WS_SCANNER,        0x0A)  \
	GENERATOR_FUNC(WS_MEDIKIT,        0x0B)  \
	GENERATOR_FUNC(WS_TIME_BOMB,      0x0C)  \
	GENERATOR_FUNC(WS_ACCESS_CARD,    0x0D)  \
	GENERATOR_FUNC(WS_UNUSED_14,      0x0E)  \
	GENERATOR_FUNC(WS_UNUSED_15,      0x0F)  \
	GENERATOR_FUNC(WS_AUTO_MAPPER,    0x10)  \
	GENERATOR_FUNC(WS_ENERGY_SHIELD,  0x11)  \
	GENERATOR_FUNC(WS_UNUSED_18,      0x12)  \
	GENERATOR_FUNC(WS_UNUSED_19,      0x13)

enum WeaponState {
	WEAPON_STATE(GENERATE_ENUM_LINES)
};

static const char* weapon_state_to_str(const enum WeaponState value) {
	GENERATE_SWITCH_CASE(WEAPON_STATE)
}
#undef WEAPON_STATE


/*******************************************************************************
 *  Command                                                                    *
 ******************************************************************************/

#define COMMAND_STATE(GENERATOR_FUNC)          \
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

enum CommandState {
	COMMAND_STATE(GENERATE_ENUM_LINES)
};

static const char* command_state_to_str(const enum CommandState value) {
	GENERATE_SWITCH_CASE(COMMAND_STATE)
}
#undef COMMAND_STATE


#endif // GDENUMS_H
