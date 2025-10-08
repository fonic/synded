#ifndef GAMEDATA_H
#define GAMEDATA_H


// Forward declarations
typedef struct Person;
typedef struct Vehicle;
typedef struct Object;
typedef struct Weapon;
typedef struct Effect;
typedef struct Command;
typedef struct World;
typedef struct MapInfo;
typedef struct Objective;
typedef struct CPObjective;


// Game data struct (covers entirety of content of GAMExx.DAT file)
struct GameData {
	/*      0 */  uint8_t    Unknown1[6];
	/*      6 */  Map        Map;
	/*  32774 */  uint8_t    Offset_ref[2];     // What is this? -> check FreeSynd sources
	/*  32776 */  Person     People[256];
	/*  56328 */  Vehicle    Vehicles[64];
	/*  59016 */  Object     Objects[400];
	/*  71016 */  Weapon     Weapons[512];
	/*  89448 */  Effect     Effects[256];
	/*  97128 */  Command    Commands[2048];
	/* 113512 */  uint8_t    Unknown2[448];     // World[32] * 14 bytes = 448 bytes (?)
	/* 113960 */  MapInfo    MapInfos;          // Might start EARLIER (to include additional members used in RGAME.C: SSMapX, SSMapY, SSMoveActive, SSScreenMode, SSVersion, SSSeed, SSPersonCount, SSTimer)
	/* 113974 */  Objective  Objectives[6];     // Should be [8] according to RGAME.C (?)
	/* 114058 */  uint8_t    Unknown3[1952];    // CPObjective[128] * 15 bytes = 1920 bytes (?)
};


// Person struct (item of People array)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown1;
	uint8_t   Unknown2;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Until here same for: Person, Vehicle, Object, Weapon, Effect

	uint16_t  Unique;                  // Unique stuff starts here (no pun intended)

	uint8_t   Hugdistance1;
	uint16_t  Hugdistance2;

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


// Vehicle struct (item of Vehicles array)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown1;
	uint8_t   Unknown2;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Same as person until here

	uint16_t  ChildHeld;               // Unique stuff starts here; from RGAME.C (unverified)
	uint16_t  ParentHeld;
	uint16_t  LinkTo;
	uint16_t  LinkX;
	uint16_t  LinkY;
	uint16_t  LinkZ;
	uint8_t   MaxSpeed;
	uint8_t   TravelAngle;
} Vehicle;


// Object struct (item of Objects array)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown1;
	uint8_t   Unknown2;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Same as person until here; no unique stuff
} Object;


// Weapon struct (item of Weapons array)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown1;
	uint8_t   Unknown2;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Same as person until here

	uint16_t  ChildWeapon;             // Unique stuff starts here; from RGAME.C (unverified)
	uint16_t  ParentWeapon;
	uint16_t  WhoOwnsWeapon;
	uint8_t   RepairCount;
} Weapon;


// Effect struct (item of Effects array)
typedef struct {
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown1;
	uint8_t   Unknown2;
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Same as person until here

	uint16_t  Owner;                   // From FreeSynd leveldata.h (unverified)
} Effect;


// Command struct (item of Commands array)
typedef struct {
	uint16_t  Next;                    // From RGAME.C (unverified)
	uint16_t  Data;
	uint16_t  GotoX;
	uint16_t  GotoY;
	uint16_t  GotoZ;
	uint8_t   State;
} Command;


// World struct (item of Worlds array)
typedef struct {
	uint16_t  WindXSpeed;              // From RGAME.C (unverified); very unsure about sizing of members!
	uint16_t  WindYSpeed;
	uint16_t  Population;
	uint8_t   Temperature;
	uint8_t   WindSpeed;
	uint8_t   WindAngle;
	uint8_t   Industry;
	uint8_t   Crime;
	uint8_t   Gravity;
	uint8_t   Density;
} World;


// MapInfo struct (single item, no array)
typedef struct {
	// tbd
} MapInfo;


// Objective struct (item of Objectives array)
typedef struct {
	// tbd
} Objective;


// CPObjective struct (item of CPObjectives array)
typedef struct {
	// tbd
} CPObjective;


#endif // GAMEDATA_H
