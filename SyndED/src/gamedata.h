/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - Game Data Structs, Defines, Macros                     *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/23/25                                                 *
 *                                                                            *
 ******************************************************************************/

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdint.h>  // int16_t, uint16_t, ...
#include <stddef.h>  // size_t


/******************************************************************************
 *                                                                            *
 *  Defines (Dimensions, Array Lengths, Offsets)                              *
 *                                                                            *
 ******************************************************************************/

#define TILES_COUNT_X                     128    // Called MAP_XSIZE/MAP_YSIZE in RGAME.C (see function move_mapwho)
#define TILES_COUNT_Y                     128

#define MIN_TILE_X                          1    // Minimum allowed tile for positioning (see function move_mapwho in RGAME.C)
#define MIN_TILE_Y                          1

#define MAX_TILE_X                        126    // Maximum allowed tile for positioning (see function move_mapwho in RGAME.C)
#define MAX_TILE_Y                        126

#define POS_PER_TILE                      256    // Each tile consists of 256 sub-positions
                                                 // (positions are 16 bit -> highest 8 bit == tile, lowest 8 bit == sub-pos)

#define MAX_ZPOS                         4095    // Highest possible Z position (see function move_mapwho in RGAME.C)

#define PEOPLE_COUNT                      256    // Lengths of arrays in GameData struct
#define VEHICLES_COUNT                     64
#define OBJECTS_COUNT                     400
#define WEAPONS_COUNT                     512
#define EFFECTS_COUNT                     256
#define COMMANDS_COUNT                   2048
#define WORLDS_COUNT                       32
#define OBJECTIVES_COUNT                    8
#define CPOBJECTIVES_COUNT                128

/*
#define RELATIVE_OFFSET_BASE          0x08006    // Location of 'RelOfsBase' member in GameData struct (right above
                                                 // People array); relative offsets are relative to THIS global offset

#define PEOPLE_GLOBAL_OFFSET          0x08008    // Global offset 0x00000 == start of GameData struct = start of GAMExx.DAT
#define VEHICLES_GLOBAL_OFFSET        0x0dc08    // contents
#define OBJECTS_GLOBAL_OFFSET         0x0e688
#define WEAPONS_GLOBAL_OFFSET         0x11568
#define EFFECTS_GLOBAL_OFFSET         0x15d68
#define COMMANDS_GLOBAL_OFFSET        0x17b68
#define WORLDS_GLOBAL_OFFSET          0x1bb68
#define OBJECTIVES_GLOBAL_OFFSET      0x1bd32
#define CPOBJECTIVES_GLOBAL_OFFSET    0x1bdaa

#define PEOPLE_RELATIVE_OFFSET        0x00002    // Relative offset 0x00000 == location of 'RelOfsBase' member in GameData
#define VEHICLES_RELATIVE_OFFSET      0x05c02    // struct (right above People array); relative offsets are important due to
#define OBJECTS_RELATIVE_OFFSET       0x06682    // being used within game data to reference other things, e.g. to associate
#define WEAPONS_RELATIVE_OFFSET       0x09562    // a Weapon with a Person (via Person.ChildWeapon)
#define EFFECTS_RELATIVE_OFFSET       0x0dd62
#define COMMANDS_RELATIVE_OFFSET      0x0fb62
#define WORLDS_RELATIVE_OFFSET        0x13b62
#define OBJECTIVES_RELATIVE_OFFSET    0x13d2c
#define CPOBJECTIVES_RELATIVE_OFFSET  0x13da4
*/

#define RELATIVE_OFFSET_BASE          offsetof(GameData, RelOfsBase)                                       // Location of 'RelOfsBase' member in GameData struct (right above
                                                                                                           // People array); relative offsets are relative to THIS global offset

#define PEOPLE_GLOBAL_OFFSET          offsetof(GameData, People)                                           // Global offset 0x00000 == start of GameData struct == start of GAMExx.DAT
#define VEHICLES_GLOBAL_OFFSET        offsetof(GameData, Vehicles)                                         // file contents
#define OBJECTS_GLOBAL_OFFSET         offsetof(GameData, Objects)
#define WEAPONS_GLOBAL_OFFSET         offsetof(GameData, Weapons)
#define EFFECTS_GLOBAL_OFFSET         offsetof(GameData, Effects)
#define COMMANDS_GLOBAL_OFFSET        offsetof(GameData, Commands)
#define WORLDS_GLOBAL_OFFSET          offsetof(GameData, Worlds)
#define OBJECTIVES_GLOBAL_OFFSET      offsetof(GameData, Objectives)
#define CPOBJECTIVES_GLOBAL_OFFSET    offsetof(GameData, CPObjectives)

#define PEOPLE_RELATIVE_OFFSET        offsetof(GameData, People) - offsetof(GameData, RelOfsBase)          // Relative offset 0x00000 == location of 'RelOfsBase' member in GameData
#define VEHICLES_RELATIVE_OFFSET      offsetof(GameData, Vehicles) - offsetof(GameData, RelOfsBase)        // struct; relative offsets are important due to being used as references
#define OBJECTS_RELATIVE_OFFSET       offsetof(GameData, Objects) - offsetof(GameData, RelOfsBase)         // within game data, e.g. to associate a Weapon with a Person (via Person.
#define WEAPONS_RELATIVE_OFFSET       offsetof(GameData, Weapons) - offsetof(GameData, RelOfsBase)         // ChildWeapon)
#define EFFECTS_RELATIVE_OFFSET       offsetof(GameData, Effects) - offsetof(GameData, RelOfsBase)
#define COMMANDS_RELATIVE_OFFSET      offsetof(GameData, Commands) - offsetof(GameData, RelOfsBase)
#define WORLDS_RELATIVE_OFFSET        offsetof(GameData, Worlds) - offsetof(GameData, RelOfsBase)
#define OBJECTIVES_RELATIVE_OFFSET    offsetof(GameData, Objectives) - offsetof(GameData, RelOfsBase)
#define CPOBJECTIVES_RELATIVE_OFFSET  offsetof(GameData, CPObjectives) - offsetof(GameData, RelOfsBase)


/******************************************************************************
 *                                                                            *
 *  Helper Macros                                                             *
 *                                                                            *
 ******************************************************************************/

//#define POS_TO_TILE(pos) (pos >> 8)                                                                      // Position to tile conversion
#define POS_TO_TILE(pos) (pos / POS_PER_TILE)                                                              // Position to tile conversion

//#define POS_TO_CMDGOTO(pos) ((pos >> 8) * 2)                                                             // Position to Command goto conversion
#define POS_TO_CMDGOTO(pos) ((pos / POS_PER_TILE) * 2)                                                     // Position to Command goto conversion

//#define POS_TO_MAPWHO_OFS(xpos, ypos) (ypos >> 8) * TILES_COUNT_X + (xpos >> 8)                          // Position to offset within MapWho array conversion
#define POS_TO_MAPWHO_OFS(xpos, ypos) (ypos / POS_PER_TILE) * TILES_COUNT_X + (xpos / POS_PER_TILE)        // Position to offset within MapWho array conversion

#define OFS_GLOBAL_TO_RELATIVE(offset_global) (offset_global - RELATIVE_OFFSET_BASE)                       // Offset global to relative conversion
#define OFS_RELATIVE_TO_GLOBAL(offset_relative) (RELATIVE_OFFSET_BASE + offset_relative)                   // Offset relative to global conversion

#define GET_THING_FOR_RELOFS(gamedata, relofs) (Thing*)((size_t)(gamedata) + offsetof(GameData, RelOfsBase) + relofs)               // Get Thing from GameData struct based on relative offset
#define GET_RELOFS_FOR_THING(gamedata, thing)  (uint16_t)((size_t)(thing) - (size_t)(gamedata) - offsetof(GameData, RelOfsBase))    // Get relative offset of Thing in GameData struct (CAUTION:
                                                                                                                                    // result is only valid for Things that are actually part of
                                                                                                                                    // the specified GameData struct)


/******************************************************************************
 *                                                                            *
 *  MapWho Struct (32768 bytes)                                               *
 *  N x M tile map of references (relative offsets) to People, Vehicles,      *
 *  Objects, Weapons and Effects                                              *
 *  (currently not in use, integrated members into GameData struct instead)   *
 *                                                                            *
 ******************************************************************************/

/*typedef struct  {
	uint16_t  ObjOfs[TILES_COUNT_X * TILES_COUNT_Y];
} MapWho;*/


/******************************************************************************
 *                                                                            *
 *  Thing Struct (28 bytes)                                                   *
 *  Represents the COMMON attributes of in-mission things (People, Vehicles,  *
 *  Objects, Weapons and Effects). Used as a 'base class' for struct casting. *
 *  (NOTE: RGAME.C calls this struct 'Global')                                *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;            // Next thing in MapWho linked list (0 == end of list)
	uint16_t  Parent;           // Previous thing in MapWho linked list (0 == start of list)
	int16_t   Xpos;             // Position on map, X axis
	int16_t   Ypos;             // Position on map, Y axis
	int16_t   Zpos;             // Position on map, Z axis
	uint16_t  Status;           // Flags, largely unknown except for TS_MAPWHO and TS_NODRAW
	uint16_t  Affect;           // Flags, meaning depends on thing type (see Model below)
	uint16_t  BaseFrame;        // Sometimes defines visual appearance (e.g. for Person, but NOT for Vehicle)
	uint16_t  Frame;            // Likely current frame of animation
	uint16_t  OldFrame;         // Likely previous frame of animation
	uint16_t  Life;             // Value, meaning depends on thing type (see Model below)
	uint16_t  WhoShotMe;        // Reference to who/what last hurt thing (likely used for retaliation logic of computer-controlled people)
	uint8_t   Model;            // Thing type (Person, Vehicle, Effect, Weapon, Object)
	uint8_t   State;            // Current state within state machine, meaning depends on thing type (e.g. for Person: PS_WANDER, PS_ON_FIRE)
	uint8_t   Angle;            // Orientation on map (on X and Y axis)
	uint8_t   ZAngle;           // Unknown (seems to be rarely used; rotations on Z axis do not actually occur in-game)
} Thing;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  Person Struct (92 bytes)                                                  *
 *  Represents in-mission people (agents, civilians, police, guards, etc.)    *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;            // For attributes without comment, refer to comments for struct Thing
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;           // Unknown (seems to duplicate some State stuff, e.g. PA_HIT_BY_FIRE vs. PS_HIT_BY_FIRE)
	uint16_t  BaseFrame;        // Defines visual appearance (e.g. agent, blonde woman, man in suit)
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;             // Health, i.e. how much damage can be tolerated before dying (value seems to have NO relevance for agents)
	uint16_t  WhoShotMe;        // Reference to who/what last hurt person (likely used for retaliation logic of computer-controlled agents/NPCs)
	uint8_t   Model;            // Set to TM_PERSON
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;           // Until here same as Thing, attributes below are unique to Person (see assignments following GPerson in RGAME.C)

	uint16_t  Unique;           // Defines general character/behavior (e.g. civilian, guard, agent); NOT to be confused with visual appearance, which is defined by BaseFrame
	uint16_t  HugDistance;      // Unknown (very random values that are NOT relofs references; naming/sizing might be wrong)
	uint16_t  Persuaded;        // Reference to person that acted as persuader (usually human player agents)
	uint16_t  ChildHeld;        // Reference to next person in linked list of vehicle passengers (0 == end of list)
	uint16_t  ParentHeld;       // Reference to previous person in linked list of vehicle passengers (values >= 23554: reference to vehicle that people are passengers of, person is head of linked list)
	uint16_t  Command;          // Reference to currently executed command of command chain
	uint16_t  StartCommand;     // Reference to initial command of command chain to be executed
	uint16_t  Target;           // Reference to current target that is hunted/attacked
	uint16_t  Data;             // Unknown (seems to be used for several different purposes, e.g. reference to other things -or- values for guards)
	int16_t   GotoX;            // Goto position on map, X axis
	int16_t   GotoY;            // Goto position on map, Y axis
	int16_t   GotoZ;            // Goto position on map, Z axis
	int16_t   LastXpos;         // Previous position on map, X axis
	int16_t   LastYpos;         // Previous position on map, Y axis
	uint16_t  HugGotoZ;         // Unknown (seems to be rarely used if ever)
	uint16_t  ChildWeapon;      // Reference to weapon(s) carried by person (i.e. start of linked list)
	uint16_t  Equipment;        // Likely flags for body mods configuration (seems to be only used for agents)
	uint16_t  ParentRank;       // Unknown (always 0 in dumps; might be related to multiplayer?)
	uint16_t  RankPosition;     // Unknown (always 0 in dumps; might be related to multiplayer?)
	uint16_t  Count;            // Unknown (non-zero in dumps; count for WHAT?)
	uint16_t  WeaponHolding;    // Reference to currently selected weapon (out of the inventory of weapons carried)
	uint8_t   WeaponInUse;      // Reference to currently used (as in fired) weapon
	uint8_t   Level1Base;       // Adrenaline (red) base level (value for / location of color bar shade; 0 == left, 128 == center, 255 == right)
	uint8_t   Level1Balance;    // Adrenaline (red) balance level (value for / location of vertical white line; 0 == left, 128 == center, 255 == right)
	uint8_t   Level1True;       // Adrenaline (red) true level (value for / location of color bar; 0 == left, 128 == center, 255 == right)
	uint8_t   Level1Fixed;      // Adrenaline (red) fixed level (always 0 for agents, but non-zero for NPCs -> NPCs likely use fixed values instead of dynamic level management)
	uint8_t   Level2Base;       // Intelligence (green) levels (works like Adrenaline above)
	uint8_t   Level2Balance;
	uint8_t   Level2True;
	uint8_t   Level2Fixed;
	uint8_t   Level3Base;       // Perception (blue) levels (works like Adrenaline above)
	uint8_t   Level3Balance;
	uint8_t   Level3True;
	uint8_t   Level3Fixed;
	uint8_t   LevelRecovery;    // Unknown (very random values that are NOT relofs references; name might be wrong)
	uint8_t   Speed;            // Current speed / velocity / rate of movement
	uint8_t   MaxSpeed;         // Maximum speed
	uint8_t   BaseSpeed;        // Base speed
	uint8_t   NewState;         // Next state within state machine
	uint8_t   OldState;         // Previous state within state machine
	uint8_t   HugChangeDir;     // Unknown (likely related to HugStartAngle + HitAngle)
	uint8_t   HugStartAngle;    // Unknown (likely angle/orientation that is used when "hugging" along a wall)
	uint8_t   HitAngle;         // Unknown (likely related to HugChangeDir + HugStartAngle)
} Person;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  Vehicle Struct (42 bytes)                                                 *
 *  Represents in-mission vehicles (black car, police car, ambulance, etc.)   *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;            // For attributes without comment, refer to comments for struct Thing
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;           // Unknown
	uint16_t  BaseFrame;        // Usually set to 0 (does NOT define visual appearance like it does for Person; see State for that)
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;             // Health, i.e. how much damage can be tolerated before breaking
	uint16_t  WhoShotMe;
	uint8_t   Model;            // Set to TM_VEHICLE
	uint8_t   State;            // Defines visual appearance (e.g. police car, APC) as well as current state in state machine (e.g. moving, on fire, destroyed)
	uint8_t   Angle;
	uint8_t   ZAngle;           // Until here same as Thing, attributes below are unique to Vehicle (see assignments following GVehicle in RGAME.C)

	uint16_t  ChildHeld;        // Reference to next person in passengers linked list (0 == end of list / no passengers)
	uint16_t  ParentHeld;       // Not sure if this can actually be anything but 0 for vehicles (TODO: check trains)
	uint16_t  LinkTo;           // Reference to connected/linked vehicle (used to connect/link multiple vehicles, e.g. carriage to train head; connected/linked vehicles move as a group)
	int16_t   LinkX;            // Position offset relative to connected/linked vehicle (see LinkTo), X axis
	int16_t   LinkY;            // Position offset relative to connected/linked vehicle (see LinkTo), Y axis
	int16_t   LinkZ;            // Position offset relative to connected/linked vehicle (see LinkTo), Z axis
	uint8_t   MaxSpeed;         // Maximum speed / velocity / rate of movement
	uint8_t   TravelAngle;      // Unknown (especially regarding difference between this and to Angle)
} Vehicle;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  Object Struct (30 bytes)                                                  *
 *  Represents in-mission objects (doors, trash cans, trees, etc.)            *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;            // For attributes without comment, refer to comments for struct Thing
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;
	uint16_t  BaseFrame;        // Unknown (sometimes 0, sometimes not)
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;             // Unknown (almost always non-zero)
	uint16_t  WhoShotMe;
	uint8_t   Model;            // Set to TM_OBJECT
	uint8_t   State;            // Unknown (might be appearance + state like for vehicles?)
	uint8_t   Angle;
	uint8_t   ZAngle;           // Until here same as Thing, attributes below are unique to Object (see assignments following GObject in RGAME.C)

	uint16_t  Connected;        // Unknown (always 0, likely unused or very rarely used; name from RGAME.C)
} Object;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  Weapon Struct (36 bytes)                                                  *
 *  Represents in-mission weapons (minigun, time bomb, etc.; both visible,    *
 *  i.e. lying on the ground AND invisible, i.e. carried by a Person)         *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;            // For attributes without comment, refer to comments for struct Thing
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;           // Set to 0
	uint16_t  BaseFrame;        // Set to 0
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;             // Amount of ammunition left in weapon (TODO: also timer for time bombs?)
	uint16_t  WhoShotMe;
	uint8_t   Model;            // Set to TM_WEAPON (exploded time bombs get set to TM_NONE)
	uint8_t   State;            // Type of weapon (e.g. WS_MINIGUN)
	uint8_t   Angle;
	uint8_t   ZAngle;           // Until here same as Thing, attributes below are unique to Weapon (see assignments following GWeapon in RGAME.C)

	uint16_t  ChildWeapon;      // Reference to next weapon in linked list of weapons carried by person (0 == end of list)
	uint16_t  ParentWeapon;     // Reference to previous weapon in linked list of weapons carried by person (values < 38242: reference to person that carries weapon(s), weapon is head of linked list)
	uint16_t  WhoOwnsWeapon;    // Reference to person that owns (i.e. carries) the weapon (0 == no owner, e.g. when weapon lies on ground)
	uint16_t  RepairCount;      // Unknown (0 for weapons belonging to agents, other values for weapons belonging to NPCs, but NOT relofs references)
} Weapon;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  Effect Struct (30 bytes)                                                  *
 *  Represents in-mission effects (fire, explosions, sounds, number above     *
 *  human player agents, etc.)                                                *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;            // For attributes without comment, refer to comments for struct Thing
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;           // Unknown (seems to be always 0)
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;             // Unknown (might be time value for how long effect lasts)
	uint16_t  WhoShotMe;
	uint8_t   Model;            // Set to TM_EFFECT
	uint8_t   State;            // Unknown (seems to be always non-zero)
	uint8_t   Angle;
	uint8_t   ZAngle;           // Until here same as Thing, attributes below are unique to Effect (see assignments following GEffect in RGAME.C)

	uint16_t  WhoShot;          // Reference to thing that caused the effect (name from RGAME.C)
} Effect;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  Command Struct (8 bytes)                                                  *
 *  Represents in-mission commands for NPCs (e.g. go to a vehicle, use that   *
 *  vehicle to drive to a certain location, trigger mission failure when      *
 *  location is reached in GAME01.DAT)                                        *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Next;             // Reference to next command of command chain (offset relative to start of Commands; 0 == end of command chain)
	uint16_t  Data;             // Reference to thing relevant for command (e.g. vehicle person shall enter)
	uint8_t   GotoX;            // Goto location for command, X axis (CAUTION: references TILES of HALF SIZE, i.e. 0-255; to convert position to goto: Goto = (pos >> 8) * 2 -or- Goto = POS_TO_CMDGOTO(pos))
	uint8_t   GotoY;            // Goto location for command, Y axis
	uint8_t   GotoZ;            // Goto location for command, Z axis
	uint8_t   State;            // Type of command (e.g. CS_GOTO_POINT)
} Command;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  World Struct (14 bytes)                                                   *
 *  Not entirely sure what this is used for (if at all; seems like this was   *
 *  a planned feature that never got properly implemented)                    *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  WindXSpeed;       // From RGAME.C (unverified); unsure about sizes/order; only 1 world seems to be populated
	uint16_t  WindYSpeed;       // in games; this might just be a leftover of some planned, but never implemented feature
	uint16_t  Population;
	uint8_t   Temperature;
	uint8_t   WindSpeed;
	uint8_t   WindAngle;
	uint8_t   Industry;
	uint8_t   Crime;
	uint8_t   Gravity;          // TODO: test if settings this has any effect on people falling from platforms when being shot
	uint8_t   Density;
	uint8_t   Unknown;          // Unknown (not sure about this, could simply be that one if the preceding members is 16 bit instead of 8 bit)
} World;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  MapInfo Struct (10 bytes)                                                 *
 *  Map settings/configuration (number of map game is meant for, boundaries   *
 *  for map viewing/scrolling)                                                *
 *  (currently not in use, integrated members into GameData struct instead)   *
 *                                                                            *
 ******************************************************************************/

/*#pragma pack(push,1)
typedef struct {
	uint16_t  MapNumber;        // Number of map associated with game (tell game engine which MAPxx.DAT file to load)
	uint16_t  LoBoundaryx;      // Lower boundary of user-scrollable area, X axis (CAUTION: uses TILES of HALF SIZE, i.e. 0-255)
	uint16_t  LoBoundaryy;      // Lower boundary of user-scrollable area, Y axis
	uint16_t  HiBoundaryx;      // Upper boundary of user-scrollable area, X axis
	uint16_t  HiBoundaryy;      // Upper boundary of user-scrollable area, Y axis
} MapInfo;
#pragma pack(pop)*/


/******************************************************************************
 *                                                                            *
 *  Objective Struct (14 bytes)                                               *
 *  Represents mission objectives the human player has to accomplish          *
 *  (e.g. kill a person, use a car, go to a location to evacuate)             *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint32_t  Status;           // 0 if objective has yet to be accomplished, 1 if objective has been accomplished
	uint16_t  Type;             // Type of objective (e.g. OT_PROTECT_PERSON, OT_EVACUATE_TO_POS)
	uint16_t  Data;             // Reference to thing relevant for objective (e.g. person that must be persuaded)
	int16_t   Xpos;             // Position relevant for objective, X axis (e.g. location to evacuate to)
	int16_t   Ypos;             // Position relevant for objective, Y axis
	int16_t   Zpos;             // Position relevant for objective, Z axis
} Objective;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  CPInfo Struct (8 bytes)                                                   *
 *  Computer player settings/configuration (number of computer players,       *
 *  aggressiveness, body mods level of enemy agents, weapons carried by       *
 *  agents, etc.)                                                             *
 *  (currently not in use, integrated members into GameData struct instead)   *
 *                                                                            *
 ******************************************************************************/

/*#pragma pack(push,1)
typedef struct {
	uint8_t   CPCount;          // Number of computer players + 1 (unsure why +1, wrong values result in buggy behavior; maximum is 8, i.e. 7 computer players)
	uint8_t   CPTeamSize;       // Number of agents per computer player (1-8; CAUTION: layout/order of enemy agents in People array has to be tailored to match this value)
	uint8_t   CPProcInt;        // Computer player aggressiveness (0-16; reaction time + fire rate; lower value == higher aggressiveness)
	uint8_t   CPLvlInit;        // Level of body mods (for all body parts) for computer player agents (0-3)
	uint8_t   CPIsBombTeam;     // Specifies if computer player agents carry time bombs (in addition to regular firearm and persuadertrons)
	uint8_t   CPIsPersTeam;     // Specifies if agents carry persuadertrons (in addition to regular firearm and time bombs)
	uint8_t   CPFlags;          // Flags, unknown (it would seem 4 is REQUIRED to enable computer player infighting)
	uint8_t   CPWeapon;         // Specifies firearm agents carry (e.g. WS_PISTOL; if set to 0, firearm is based on human player RESEARCH progress: Shotgun, Uzi or Minigun)
} CPInfo;
#pragma pack(pop)*/


/******************************************************************************
 *                                                                            *
 *  CPObjective Struct (15 bytes)                                             *
 *  Represents mission objectives the computer players have to accomplish     *
 *  (very similar to how Commands for NPCs work, but tailored to command      *
 *  groups of agents; NOTE: CPObjectives is a bit misleading, CPCommands      *
 *  would actually be more fitting)                                           *
 *                                                                            *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;            // Index of next objective of objective chain (0 == end of objective chain)
	uint16_t  Parent;           // Index of previous objective of objective chain (0 == start of objective chain)
	uint8_t   UseCount;         // Unknown (likely counter for how often objective was used by / applied to computer player)
	uint8_t   Player;           // Number of player objective is meant for (1-7; 255 == any computer player)
	uint8_t   Flags;            // Unknown (mostly 0, but also spotted value 16)
	uint8_t   ActionType;       // Specifies action to be performed by computer player (e.g. CPOAT_ATTACK_PLAYER; can act as a category for Action, e.g. CPOAT_MOVE)
	uint8_t   Action;           // Specified sub-action to be performed by computer player (e.g. ActionType == CPOAT_MOVE + Action == CPOA_GOTO_PERSON)
	int16_t   X;                // Parameter X for action/sub-action (e.g. reference to thing, timer value, X position)
	int16_t   Y;                // Parameter Y for action/sub-action
	int16_t   Z;                // Parameter Z for action/sub-action
} CPObjective;
#pragma pack(pop)


/******************************************************************************
 *                                                                            *
 *  GameData Struct (116.010 byte)                                            *
 *  Represents everything that appears in and controls a mission              *
 *  (covers the entirety of contents of GAMExx.DAT files)                     *
 *                                                                            *
 ******************************************************************************/

// Yet to be identified within GameData struct (from RGAME.C; commented out == identified):
/*
	MapX
	MapY
	MoveActive
	ScreenMode
	Version
	//Seed
	//PersonCount
	//Timer
	Header[0]
	Header[1]
	//MapNumber
	//LoBoundaryx
	//LoBoundaryy
	//HiBoundaryx
	//HiBoundaryy
	//CPLvlInit
	StructEnd
*/

typedef struct {
	/*      0 0x00000 */  uint16_t     Seed;                                     // Unknown (likely seed value for RNG)
	/*      2 0x00002 */  uint16_t     PersonCount;                              // Unknown (most likely named wrong, does not actually seem to reflect number of peoples)
	/*      4 0x00004 */  uint16_t     Timer;                                    // Unknown (might be time allowed for mission to be completed, i.e. timeout-based failure)
	/*      6 0x00006 */  //MapWho     MapWho;                                   // Could use this struct instead of separate member below
	/*      6 0x00006 */  //uint16_t   MapWho[TILES_COUNT_Y][TILES_COUNT_X];     // Would defining it like this make more sense / make things easier?
	/*      6 0x00006 */  uint16_t     MapWho[TILES_COUNT_X * TILES_COUNT_Y];
	/*  32774 0x08006 */  uint16_t     RelOfsBase;                               // Base for relative offsets of things (name was chosen to fit purpose; this might be SSHeader[0]/SSHeader[1] of RGAME.C)
	/*  32776 0x08008 */  Person       People[PEOPLE_COUNT];
	/*  56328 0x0dc08 */  Vehicle      Vehicles[VEHICLES_COUNT];
	/*  59016 0x0e688 */  Object       Objects[OBJECTS_COUNT];
	/*  71016 0x11568 */  Weapon       Weapons[WEAPONS_COUNT];
	/*  89448 0x15d68 */  Effect       Effects[EFFECTS_COUNT];
	/*  97128 0x17b68 */  Command      Commands[COMMANDS_COUNT];
	/* 113512 0x1bb68 */  World        Worlds[WORLDS_COUNT];
	/* 113960 0x1bd28 */  //MapInfo    MapInfo;                                  // Could use this struct instead of separate members below (until Objectives)
	/* 113960 0x1bd28 */  uint16_t     MapNumber;                                // See struct MapInfo for meanings/explanations
	/* 113962 0x1bd2a */  uint16_t     LoBoundaryx;
	/* 113964 0x1bd2c */  uint16_t     LoBoundaryy;
	/* 113966 0x1bd2e */  uint16_t     HiBoundaryx;
	/* 113968 0x1bd30 */  uint16_t     HiBoundaryy;
	/* 113970 0x1bd32 */  Objective    Objectives[OBJECTIVES_COUNT];
	/* 114082 0x1bda2 */  //CPInfo     CPInfo;                                   // Could use this struct instead of separate members below (until CPObjectives)
	/* 114082 0x1bda2 */  uint8_t      CPCount;                                  // See struct CPInfo for meanings/explanations
	/* 114083 0x1bda3 */  uint8_t      CPTeamSize;
	/* 114084 0x1bda4 */  uint8_t      CPProcInt;
	/* 114085 0x1bda5 */  uint8_t      CPLvlInit;
	/* 114086 0x1bda6 */  uint8_t      CPIsBombTeam;
	/* 114087 0x1bda7 */  uint8_t      CPIsPersTeam;
	/* 114088 0x1bda8 */  uint8_t      CPFlags;
	/* 114089 0x1bda9 */  uint8_t      CPWeapon;
	/* 114090 0x1bdaa */  CPObjective  CPObjectives[CPOBJECTIVES_COUNT];
	/* 116010 0x1c52a */  // [ End of struct ]
} GameData;


#endif // GAMEDATA_H
