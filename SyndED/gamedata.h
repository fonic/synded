#ifndef GAMEDATA_H
#define GAMEDATA_H


#define TILES_COUNT_X                     128
#define TILES_COUNT_Y                     128

#define PEOPLE_COUNT                      256
#define VEHICLES_COUNT                     64
#define OBJECTS_COUNT                     400
#define WEAPONS_COUNT                     512
#define EFFECTS_COUNT                     256
#define COMMANDS_COUNT                   2048
#define WORLDS_COUNT                       32
#define OBJECTIVES_COUNT                    8
#define CPOBJECTIVES_COUNT                128

#define RELATIVE_OFFSET_BASE          0x08006     // Location of 'Unknown' member in GameData struct (right above
                                                  // People array); relative offsets are relative to THIS global offset

#define PEOPLE_GLOBAL_OFFSET          0x08008     // 0x00000 == start of GameData struct = start of GAMExx.DAT contents
#define VEHICLES_GLOBAL_OFFSET        0x0dc08
#define OBJECTS_GLOBAL_OFFSET         0x0e688
#define WEAPONS_GLOBAL_OFFSET         0x11568
#define EFFECTS_GLOBAL_OFFSET         0x15d68
#define COMMANDS_GLOBAL_OFFSET        0x17b68
#define WORLDS_GLOBAL_OFFSET          0x1bb68
#define OBJECTIVES_GLOBAL_OFFSET      0x1bd32
#define CPOBJECTIVES_GLOBAL_OFFSET    0x1bdaa

#define PEOPLE_RELATIVE_OFFSET        0x00002     // 0x00000 == location of 'Unknown' member in GameData struct (right
#define VEHICLES_RELATIVE_OFFSET      0x05c02     // above People array); relative offsets are important as THESE are
#define OBJECTS_RELATIVE_OFFSET       0x06682     // used within game data to reference other things, e.g. to associate
#define WEAPONS_RELATIVE_OFFSET       0x09562     // a Weapon with a Person (via Person.ChildWeapon)
#define EFFECTS_RELATIVE_OFFSET       0x0dd62
#define COMMANDS_RELATIVE_OFFSET      0x0fb62
#define WORLDS_RELATIVE_OFFSET        0x13b62
#define OBJECTIVES_RELATIVE_OFFSET    0x13d2c
#define CPOBJECTIVES_RELATIVE_OFFSET  0x13da4

#define OFFSET_GLOBAL_TO_RELATIVE(offset_global) offset_global - RELATIVE_OFFSET_BASE        // Offset global to relative conversion
#define OFFSET_RELATIVE_TO_GLOBAL(offset_relative) RELATIVE_OFFSET_BASE + offset_relative    // Offset relative to global conversion

#define POSITION_TO_MAPWHO_OFFSET(xpos, ypos) (ypos >> 8) * TILES_COUNT_X + (xpos >> 8)      // Position to offset within MapWho array conversion


/*typedef struct  {                                     // Map struct (32768 bytes)
	uint16_t  ObjOfs[TILES_COUNT_X * TILES_COUNT_Y];    // N x M tile map of references to People, Vehicles, Objects,
} MapWho;*/                                             // -> struct currently not in use, integrated sole member
                                                        //    into GameData struct


#pragma pack(push,1)
typedef struct {                       // Person struct (92 bytes)
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
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
	uint8_t   ZAngle;                  // Until here same for: Person, Vehicle, Object, Weapon, Effect

	uint16_t  Unique;                  // Not sure yet about uint16_t (before, there was 'uint8_t HugDistance1' following)
                                       // Attributes unique to Person
	uint16_t  HugDistance;

	uint16_t  Persuaded;

	uint16_t  ChildHeld;
	uint16_t  ParentHeld;

	uint16_t  Command;
	uint16_t  StartCommand;
	uint16_t  Target;
	uint16_t  Data;

	uint16_t  GotoX;
	uint16_t  GotoY;
	uint16_t  GotoZ;

	uint16_t  LastXpos;
	uint16_t  LastYpos;
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


#pragma pack(push,1)
typedef struct {                       // Vehicle struct (42 bytes)
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
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
	uint8_t   ZAngle;                  // Until here same as Person

	uint16_t  ChildHeld;               // Attributes unique to Vehicle
	uint16_t  ParentHeld;
	uint16_t  LinkTo;
	uint16_t  LinkX;
	uint16_t  LinkY;
	uint16_t  LinkZ;
	uint8_t   MaxSpeed;
	uint8_t   TravelAngle;
} Vehicle;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct {                       // Object struct (30 bytes)
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
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
	uint8_t   ZAngle;                  // Until here same as Person

	uint8_t   Unknown[2];              // Attributes unique to Object
} Object;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct {                       // Weapon struct (36 bytes)
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
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
	uint8_t   ZAngle;                  // Until here same as Person

	uint16_t  ChildWeapon;             // Attributes unique to Weapon; from RGAME.C (unverified)
	uint16_t  ParentWeapon;
	uint16_t  WhoOwnsWeapon;
	uint16_t  RepairCount;
} Weapon;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct {                       // Effect struct (30 bytes)
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
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
	uint8_t   ZAngle;                  // Until here same as Person

	uint16_t  Owner;                   // Attributes unique to Weapon; from FreeSynd leveldata.h (unverified)
} Effect;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct {                       // Command struct (8 bytes)
	uint16_t  Next;                    // From RGAME.C (unverified)
	uint16_t  Data;
	//uint16_t  GotoX;
	//uint16_t  GotoY;
	//uint16_t  GotoZ;
	uint8_t   GotoX;                   // These seem to reference TILES (0-128), not POSITIONS (like in other
	uint8_t   GotoY;                   // structs), according to FreeSynd leveldata.h
	uint8_t   GotoZ;
	uint8_t   State;
} Command;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct {                       // World struct (14 bytes)
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


/*#pragma pack(push,1)
typedef struct {                       // MapInfo struct (10 bytes)
	uint16_t  MapNumber;
	uint16_t  LoBoundaryx;
	uint16_t  LoBoundaryy;
	uint16_t  HiBoundaryx;
	uint16_t  HiBoundaryy;             // -> struct currently not in use, using separate members
} MapInfo;                             //    instead (like in RGAME.C)
#pragma pack(pop)*/


#pragma pack(push,1)
typedef struct {                       // Objective struct (14 bytes)
	uint32_t  Status;                  // From RGAME.C (unverified); sizes from FreeSynd leveldata.h + Mefistotelis .xml
	uint16_t  Objective;
	uint16_t  Data;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
} Objective;
#pragma pack(pop)


/*#pragma pack(push,1)
typedef struct {                       // CPInfo struct (10 bytes)
	uint8_t   CPCount;                 // All of these are not entirely sure yet!
	uint8_t   CPTeamSize;
	uint8_t   CPProcInt;
	uint8_t   CPLvlInit;
	uint8_t   CPIsBombTeam;
	uint8_t   CPIsPersTeam;
	uint8_t   CPFlags;
	uint8_t   CPWeapon;
	uint16_t  HiBoundaryy;             // -> struct currently not in use, using separate members
} CPInfo;                              //    instead (like in RGAME.C)
#pragma pack(pop)*/


#pragma pack(push,1)
typedef struct {                       // CPObjective struct (15 bytes)
	uint16_t  Child;                   // From RGAME.C (unverified); sizes from Mefistotelis .xml
	uint16_t  Parent;
	uint8_t   UseCount;
	uint8_t   Player;
	uint8_t   Flags;
	uint8_t   ActionType;
	uint8_t   Action;
	uint16_t  X;
	uint16_t  Y;
	uint16_t  Z;
} CPObjective;
#pragma pack(pop)


typedef struct {                                                                 // Game data struct (116.010 bytes -> covers entirety of contents of GAMExx.DAT file)
	/*      0 0x00000 */  uint16_t     Seed;
	/*      2 0x00002 */  uint16_t     PersonCount;                              // Not sure!
	/*      4 0x00004 */  uint16_t     Timer;
	/*      6 0x00006 */  //MapWho       MapWho;                                 // Could use this struct instead of separate member below
	/*      6 0x00006 */  //uint16_t     MapWho[TILES_COUNT_Y][TILES_COUNT_X];   // Would this make more sense / make things easier?
	/*      6 0x00006 */  uint16_t     MapWho[TILES_COUNT_X * TILES_COUNT_Y];
	/*  32774 0x08006 */  uint16_t     Unknown;                                  // What is this? -> likely SSHeader[0]/SSHeader[1]
	/*  32776 0x08008 */  Person       People[PEOPLE_COUNT];
	/*  56328 0x0dc08 */  Vehicle      Vehicles[VEHICLES_COUNT];
	/*  59016 0x0e688 */  Object       Objects[OBJECTS_COUNT];
	/*  71016 0x11568 */  Weapon       Weapons[WEAPONS_COUNT];
	/*  89448 0x15d68 */  Effect       Effects[EFFECTS_COUNT];
	/*  97128 0x17b68 */  Command      Commands[COMMANDS_COUNT];
	/* 113512 0x1bb68 */  World        Worlds[WORLDS_COUNT];
	/* 113960 0x1bd28 */  //MapInfo      MapInfo;                                // Could use this struct instead of separate members below (until Objectives)
	/* 113960 0x1bd28 */  uint16_t     MapNumber;
	/* 113962 0x1bd2a */  uint16_t     LoBoundaryx;
	/* 113964 0x1bd2c */  uint16_t     LoBoundaryy;
	/* 113966 0x1bd2e */  uint16_t     HiBoundaryx;
	/* 113968 0x1bd30 */  uint16_t     HiBoundaryy;
	/* 113970 0x1bd32 */  Objective    Objectives[OBJECTIVES_COUNT];
	/* 114082 0x1bda2 */  //CPInfo       CPInfo;                                 // Could use this struct instead of separate members below (until CPObjectives)
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


#endif // GAMEDATA_H
