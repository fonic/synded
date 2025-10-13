#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <stdint.h>
#include <stddef.h>


/*******************************************************************************
 *                                                                             *
 *  Defines (Dimensions, Array Lengths, Offsets)                               *
 *                                                                             *
 ******************************************************************************/

#define TILES_COUNT_X                     128    // Called MAP_XSIZE/MAP_YSIZE in RGAME.C (see function move_mapwho)
#define TILES_COUNT_Y                     128

#define MIN_TILE_X                          1    // Minimum allowed tile for positioning (see function move_mapwho in RGAME.C)
#define MIN_TILE_Y                          1

#define MAX_TILE_X                        126    // Maximum allowed tile for positioning (see function move_mapwho in RGAME.C)
#define MAX_TILE_Y                        126

#define POS_PER_TILE                      256    // Each tile consists of 256 sub-positions
                                                 // (positions are 16 bit -> highest 8 bit == tile, lowest 8 bit == subpos)

#define MAX_ZPOS                         4095    // Highest possible Z position (see function move_mapwho in RGAME.C)

#define PEOPLE_COUNT                      256
#define VEHICLES_COUNT                     64
#define OBJECTS_COUNT                     400
#define WEAPONS_COUNT                     512
#define EFFECTS_COUNT                     256
#define COMMANDS_COUNT                   2048
#define WORLDS_COUNT                       32
#define OBJECTIVES_COUNT                    8
#define CPOBJECTIVES_COUNT                128

#define RELATIVE_OFFSET_BASE          0x08006    // Location of 'RelOfsBase' member in GameData struct (right above
                                                 // People array); relative offsets are relative to THIS global offset

#define PEOPLE_GLOBAL_OFFSET          0x08008    // 0x00000 == start of GameData struct = start of GAMExx.DAT contents
#define VEHICLES_GLOBAL_OFFSET        0x0dc08
#define OBJECTS_GLOBAL_OFFSET         0x0e688
#define WEAPONS_GLOBAL_OFFSET         0x11568
#define EFFECTS_GLOBAL_OFFSET         0x15d68
#define COMMANDS_GLOBAL_OFFSET        0x17b68
#define WORLDS_GLOBAL_OFFSET          0x1bb68
#define OBJECTIVES_GLOBAL_OFFSET      0x1bd32
#define CPOBJECTIVES_GLOBAL_OFFSET    0x1bdaa

#define PEOPLE_RELATIVE_OFFSET        0x00002    // 0x00000 == location of 'RelOfsBase' member in GameData struct (right
#define VEHICLES_RELATIVE_OFFSET      0x05c02    // above People array); relative offsets are important as THESE are
#define OBJECTS_RELATIVE_OFFSET       0x06682    // used within game data to reference other things, e.g. to associate
#define WEAPONS_RELATIVE_OFFSET       0x09562    // a Weapon with a Person (via Person.ChildWeapon)
#define EFFECTS_RELATIVE_OFFSET       0x0dd62
#define COMMANDS_RELATIVE_OFFSET      0x0fb62
#define WORLDS_RELATIVE_OFFSET        0x13b62
#define OBJECTIVES_RELATIVE_OFFSET    0x13d2c
#define CPOBJECTIVES_RELATIVE_OFFSET  0x13da4


/*******************************************************************************
 *                                                                             *
 *  Helper Macros                                                              *
 *                                                                             *
 ******************************************************************************/

#define OFS_GLOBAL_TO_RELATIVE(offset_global) offset_global - RELATIVE_OFFSET_BASE        // Offset global to relative conversion
#define OFS_RELATIVE_TO_GLOBAL(offset_relative) RELATIVE_OFFSET_BASE + offset_relative    // Offset relative to global conversion

#define POS_TO_MAPWHO_OFS(xpos, ypos) (ypos >> 8) * TILES_COUNT_X + (xpos >> 8)           // Position to offset within MapWho array conversion

#define GET_THING_FOR_RELOFS(gamedata, relofs) (Thing*)((size_t)(gamedata) + offsetof(GameData, RelOfsBase) + relofs)               // Get Thing from GameData struct based on relative offset
#define GET_RELOFS_FOR_THING(gamedata, thing)  (uint16_t)((size_t)(thing) - (size_t)(gamedata) - offsetof(GameData, RelOfsBase))    // Get relative offset of Thing in GameData struct (CAUTION:
                                                                                                                                    // only valid for Things that are actually part of the specified
                                                                                                                                    // struct)


/*******************************************************************************
 *                                                                             *
 *  MapWho Struct (32768 bytes)                                                *
 *  N x M tile map of references (relative offsets) to People, Vehicles,       *
 *  Objects, Weapons and Effects                                               *
 *  (currently not in use, integrated members into GameData struct instead)    *
 *                                                                             *
 ******************************************************************************/

/*typedef struct  {
	uint16_t  ObjOfs[TILES_COUNT_X * TILES_COUNT_Y];
} MapWho;*/


/*******************************************************************************
 *                                                                             *
 *  Thing Struct (28 bytes)                                                    *
 *  Represents the COMMON attributes of in-mission things (People, Vehicles,   *
 *  Objects, Weapons and Effects). Used as a 'base class' for struct casting.  *
 *  NOTE: RGAME.C calls this struct 'Global'                                   *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;
} Thing;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  Person Struct (92 bytes)                                                   *
 *  Represents in-mission people (agents, civilians, police, guards, etc.)     *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Until here same as Thing

	uint16_t  Unique;                  // Attributes unique to Person; not sure yet about uint16_t here (before, there was 'uint8_t HugDistance1' following)
	uint16_t  HugDistance;
	uint16_t  Persuaded;
	uint16_t  ChildHeld;
	uint16_t  ParentHeld;
	uint16_t  Command;
	uint16_t  StartCommand;
	uint16_t  Target;
	uint16_t  Data;
	int16_t   GotoX;
	int16_t   GotoY;
	int16_t   GotoZ;
	int16_t   LastXpos;
	int16_t   LastYpos;
	uint16_t  HugGotoZ;
	uint16_t  ChildWeapon;
	uint16_t  Equipment;
	uint16_t  ParentRank;
	uint16_t  RankPosition;
	uint16_t  Count;
	uint16_t  WeaponHolding;
	uint8_t   WeaponInUse;
	uint8_t   Level1Base;
	uint8_t   Level1Balance;
	uint8_t   Level1True;
	uint8_t   Level1Fixed;
	uint8_t   Level2Base;
	uint8_t   Level2Balance;
	uint8_t   Level2True;
	uint8_t   Level2Fixed;
	uint8_t   Level3Base;
	uint8_t   Level3Balance;
	uint8_t   Level3True;
	uint8_t   Level3Fixed;
	uint8_t   LevelRecovery;
	uint8_t   Speed;
	uint8_t   MaxSpeed;
	uint8_t   BaseSpeed;
	uint8_t   OldState;
	uint8_t   NewState;
	uint8_t   HugChangeDir;
	uint8_t   HugStartAngle;
	uint8_t   HitAngle;
} Person;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  Vehicle Struct (42 bytes)                                                  *
 *  Represents in-mission vehicles (black car, police car, ambulance, etc.)    *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Until here same as Thing

	uint16_t  ChildHeld;               // Attributes unique to Vehicle
	uint16_t  ParentHeld;
	uint16_t  LinkTo;
	int16_t   LinkX;
	int16_t   LinkY;
	int16_t   LinkZ;
	uint8_t   MaxSpeed;
	uint8_t   TravelAngle;
} Vehicle;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  Object Struct (30 bytes)                                                   *
 *  Represents in-mission objects (doors, trash cans, trees, etc.)             *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Until here same as Thing

	uint8_t   Unknown[2];              // Attributes unique to Object
} Object;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  Weapon Struct (36 bytes)                                                   *
 *  Represents in-mission weapons (minigun, time bomb, etc.; both visible,     *
 *  i.e. lying on the ground AND invisible, i.e. carried by a Person)          *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Until here same as Thing

	uint16_t  ChildWeapon;             // Attributes unique to Weapon; from RGAME.C (unverified)
	uint16_t  ParentWeapon;
	uint16_t  WhoOwnsWeapon;
	uint16_t  RepairCount;
} Weapon;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  Effect Struct (30 bytes)                                                   *
 *  Represents in-mission effects (fire, explosions, sounds, etc.)             *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	int16_t   Xpos;
	int16_t   Ypos;
	int16_t   Zpos;
	uint16_t  Status;
	uint16_t  Affect;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Until here same as Thing

	uint16_t  Owner;                   // Attributes unique to Weapon; from FreeSynd leveldata.h (unverified)
} Effect;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  Command Struct (8 bytes)                                                   *
 *  Represents in-mission commands for NPCs (e.g. go to a vehicle, use that    *
 *  vehicle to drive to a certain location, trigger mission failure when       *
 *  location is reached in GAME01.DAT)                                         *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Next;                    // From RGAME.C (unverified)
	uint16_t  Data;
	//int16_t   GotoX;
	//int16_t   GotoY;
	//int16_t   GotoZ;
	uint8_t   GotoX;                   // These reference TILES of HALF SIZE, i.e. to convert
	uint8_t   GotoY;                   // a position to this use: GotoX = (Xpos >> 8) * 2
	uint8_t   GotoZ;
	uint8_t   State;
} Command;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  World Struct (14 bytes)                                                    *
 *  Not entirely sure what this is used for (if at all; seems like this was    *
 *  a planned feature that never got properly implemented)                     *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  WindXSpeed;              // From RGAME.C (unverified); unsure about sizes / order
	uint16_t  WindYSpeed;
	uint16_t  Population;
	uint8_t   Temperature;
	uint8_t   WindSpeed;
	uint8_t   WindAngle;
	uint8_t   Industry;
	uint8_t   Crime;
	uint8_t   Gravity;
	uint8_t   Density;
	uint8_t   Unknown;
} World;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  MapInfo Struct (10 bytes)                                                  *
 *  (currently not in use, integrated members into GameData struct instead)    *
 *                                                                             *
 ******************************************************************************/

/*#pragma pack(push,1)
typedef struct {
	uint16_t  MapNumber;
	uint16_t  LoBoundaryx;
	uint16_t  LoBoundaryy;
	uint16_t  HiBoundaryx;
	uint16_t  HiBoundaryy;
} MapInfo;
#pragma pack(pop)*/


/*******************************************************************************
 *                                                                             *
 *  Objective Struct (14 bytes)                                                *
 *  Represents mission objectives the human player has to accomplish           *
 *  (e.g. kill a person, use a car, drive car to a location to evacuate)       *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint32_t  Status;                  // From RGAME.C (unverified); sizes from FreeSynd leveldata.h + Mefistotelis .xml
	uint16_t  Objective;
	uint16_t  Data;
	int16_t   Xpos;                    // Changed these from uint16_t to int16_t as well
	int16_t   Ypos;                    // (while changing position types for Things, but not sure HERE)
	int16_t   Zpos;
} Objective;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  CPInfo Struct (8 bytes)                                                    *
 *  (currently not in use, integrated members into GameData struct instead)    *
 *                                                                             *
 ******************************************************************************/

/*#pragma pack(push,1)
typedef struct {
	uint8_t   CPCount;                 // All of these are not entirely sure yet!
	uint8_t   CPTeamSize;
	uint8_t   CPProcInt;
	uint8_t   CPLvlInit;
	uint8_t   CPIsBombTeam;
	uint8_t   CPIsPersTeam;
	uint8_t   CPFlags;
	uint8_t   CPWeapon;
} CPInfo;
#pragma pack(pop)*/


/*******************************************************************************
 *                                                                             *
 *  CPObjective Struct (15 bytes)                                              *
 *  Represents mission objectives the computer players have to accomplish      *
 *  (largely unknown for now, likely similar to how Commands for NPCs work)    *
 *                                                                             *
 ******************************************************************************/

#pragma pack(push,1)
typedef struct {
	uint16_t  Child;                   // From RGAME.C (unverified); sizes from Mefistotelis .xml
	uint16_t  Parent;
	uint8_t   UseCount;
	uint8_t   Player;
	uint8_t   Flags;
	uint8_t   ActionType;
	uint8_t   Action;
	int16_t   X;
	int16_t   Y;
	int16_t   Z;
} CPObjective;
#pragma pack(pop)


/*******************************************************************************
 *                                                                             *
 *  GameData Struct (116.010 byte)                                             *
 *  Represents everything that appears in and controls a mission               *
 *  (covers the entirety of contents of GAMExx.DAT files)                      *
 *                                                                             *
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
	/*      0 0x00000 */  uint16_t     Seed;
	/*      2 0x00002 */  uint16_t     PersonCount;                              // Not sure!
	/*      4 0x00004 */  uint16_t     Timer;
	/*      6 0x00006 */  //MapWho     MapWho;                                   // Could use this struct instead of separate member below
	/*      6 0x00006 */  //uint16_t   MapWho[TILES_COUNT_Y][TILES_COUNT_X];     // Would this make more sense / make things easier?
	/*      6 0x00006 */  uint16_t     MapWho[TILES_COUNT_X * TILES_COUNT_Y];
	/*  32774 0x08006 */  uint16_t     RelOfsBase;                               // Name is not final, could also be SSHeader[0]/SSHeader[1]
	/*  32776 0x08008 */  Person       People[PEOPLE_COUNT];
	/*  56328 0x0dc08 */  Vehicle      Vehicles[VEHICLES_COUNT];
	/*  59016 0x0e688 */  Object       Objects[OBJECTS_COUNT];
	/*  71016 0x11568 */  Weapon       Weapons[WEAPONS_COUNT];
	/*  89448 0x15d68 */  Effect       Effects[EFFECTS_COUNT];
	/*  97128 0x17b68 */  Command      Commands[COMMANDS_COUNT];
	/* 113512 0x1bb68 */  World        Worlds[WORLDS_COUNT];
	/* 113960 0x1bd28 */  //MapInfo    MapInfo;                                  // Could use this struct instead of separate members below (until Objectives)
	/* 113960 0x1bd28 */  uint16_t     MapNumber;
	/* 113962 0x1bd2a */  uint16_t     LoBoundaryx;                              // These seem use TILES of HALF SIZE (i.e. range 0-255)
	/* 113964 0x1bd2c */  uint16_t     LoBoundaryy;
	/* 113966 0x1bd2e */  uint16_t     HiBoundaryx;
	/* 113968 0x1bd30 */  uint16_t     HiBoundaryy;
	/* 113970 0x1bd32 */  Objective    Objectives[OBJECTIVES_COUNT];
	/* 114082 0x1bda2 */  //CPInfo     CPInfo;                                   // Could use this struct instead of separate members below (until CPObjectives)
	/* 114082 0x1bda2 */  uint8_t      CPCount;                                  // All of these are not entirely sure yet!
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
