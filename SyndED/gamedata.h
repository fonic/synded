#ifndef GAMEDATA_H
#define GAMEDATA_H


typedef struct  {                      // Map struct (128*128 tile map of references to People, Vehicles, Objects, etc.)
	uint16_t  ObjOfs[128*128];
} MapWho;                              // 32768 bytes


typedef struct {                       // Person struct (item of People array) | 92 bytes
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown[2];
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Until here same for: Person, Vehicle, Object, Weapon, Effect

	uint8_t   Unique;                  // Unique stuff starts here (no pun intended)

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


typedef struct {                       // Vehicle struct (item of Vehicles array) | 42 bytes
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown[2];
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


typedef struct {                       // Object struct (item of Objects array) | 28 bytes
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown1[2];
	uint16_t  BaseFrame;
	uint16_t  Frame;
	uint16_t  OldFrame;
	uint16_t  Life;
	uint16_t  WhoShotMe;
	uint8_t   Model;
	uint8_t   State;
	uint8_t   Angle;
	uint8_t   ZAngle;                  // Same as person until here; no unique stuff
	uint8_t   Unknown2[2];
} Object;


typedef struct {                       // Weapon struct (item of Weapons array) | 36 bytes
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown[2];
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


typedef struct {                       // Effect struct (item of Effects array) | 30 bytes
	uint16_t  Child;
	uint16_t  Parent;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;
	uint8_t   Affect;
	uint8_t   Unknown[2];
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


typedef struct {                       // Command struct (item of Commands array) | 8 bytes
	uint16_t  Next;                    // From RGAME.C (unverified)
	uint16_t  Data;
	//uint16_t  GotoX;
	//uint16_t  GotoY;
	//uint16_t  GotoZ;
	uint8_t   GotoX;                   // These seem to reference TILES (0-128), not POSITIONS (like in other structs), according to FreeSynd leveldata.h
	uint8_t   GotoY;
	uint8_t   GotoZ;
	uint8_t   State;
} Command;


typedef struct {                       // World struct (item of Worlds array) | 14 bytes
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


/*typedef struct {                     // MapInfo struct (single item, no array) | 10 bytes
	uint16_t  MapNumber;               // From RGAME.C (unverified)
	uint16_t  LoBoundaryx;
	uint16_t  LoBoundaryy;
	uint16_t  HiBoundaryx;
	uint16_t  HiBoundaryy;
} MapInfo;*/                           // -> no longer in use, deconstructed into separate members (like in RGAME.C)


#pragma pack(1)
typedef struct {                       // Objective struct (item of Objectives array) | 14 bytes
	uint32_t  Status;
	uint16_t  Objective;               // From RGAME.C (unverified); sizes verified by FreeSynd leveldata.h
	uint16_t  Data;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
} Objective;


#pragma pack(1)
typedef struct {                       // CPObjective struct (item of CPObjectives array) | 15 bytes
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


typedef struct {                                     // Game data struct (covers entirety of contents of GAMExx.DAT file)
	/*      0 */  uint16_t     Seed;
	/*      2 */  uint16_t     PersonCount;          // Not sure!
	/*      4 */  uint16_t     Timer;
	/*      6 */  MapWho       MapWho;
	/*  32774 */  uint16_t     Unknown_1;            // What is this? -> likely SSHeader[0]/SSHeader[1]
	/*  32776 */  Person       People[256];
	/*  56328 */  Vehicle      Vehicles[64];
	/*  59016 */  Object       Objects[400];
	/*  71016 */  Weapon       Weapons[512];
	/*  89448 */  Effect       Effects[256];
	/*  97128 */  Command      Commands[2048];
	/* 113512 */  World        Worlds[32];
	/* 113960 */  //MapInfo      MapInfos;
	/* 113960 */  uint16_t     MapNumber;            // Formerly part of struct MapInfos
	/* 113962 */  uint16_t     LoBoundaryx;          // Formerly part of struct MapInfos
	/* 113964 */  uint16_t     LoBoundaryy;          // Formerly part of struct MapInfos
	/* 113966 */  uint16_t     HiBoundaryx;          // Formerly part of struct MapInfos
	/* 113968 */  uint16_t     HiBoundaryy;          // Formerly part of struct MapInfos
	/* 113970 */  Objective    Objectives[8];
	/* 114082 */  uint8_t      Unknown_2;            // What is this?
	/* 114083 */  uint8_t      CPTeamSize;
	/* 114084 */  uint8_t      Unknown_3;            // What is this?
	/* 114085 */  uint8_t      CPLvlInit;
	/* 114086 */  uint8_t      Unknown_4;            // What is this?
	/* 114087 */  uint8_t      Unknown_5;            // What is this?
	/* 114088 */  uint8_t      Unknown_6;            // What is this?
	/* 114089 */  uint8_t      Unknown_7;            // What is this?
	/* 114090 */  CPObjective  CPObjectives[128];
} GameData;


// Yet to be identified within GameData struct (commented out == identified):
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
