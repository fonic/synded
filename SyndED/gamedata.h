#ifndef GAMEDATA_H
#define GAMEDATA_H


typedef struct  {                      // Map struct (128*128 tile map of references to People, Vehicles, Objects, etc.)
	uint16_t  ObjRef[128*128];
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

	uint8_t  Unique;                  // Unique stuff starts here (no pun intended)

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


typedef struct {                       // World struct (item of Worlds array) | 12 bytes (could also be 14 bytes, but NOT more)
	uint8_t   WindXSpeed;              // From RGAME.C (unverified); very unsure about sizing of members!
	uint8_t   WindYSpeed;
	uint16_t  Population;
	uint8_t   Temperature;
	uint8_t   WindSpeed;
	uint8_t   WindAngle;
	uint8_t   Industry;
	uint8_t   Crime;
	uint8_t   Gravity;
	uint8_t   Density;
} World;


typedef struct {                        // MapInfo struct (single item, no array) | 14 bytes
	uint16_t  MapNumber;                // From RGAME.C (unverified); sizes verified by FreeSynd leveldata.h
	uint16_t  LoBoundaryx;
	uint16_t  LoBoundaryy;
	uint16_t  HiBoundaryx;
	uint16_t  HiBoundaryy;
	uint16_t  SSCPLvlInit;
	uint16_t  SSStructEnd;
} MapInfo;


typedef struct {                       // Objective struct (item of Objectives array) | 14 bytes
	uint16_t  Objective;               // From RGAME.C (unverified); sizes verified by FreeSynd leveldata.h
	uint16_t  Data;
	uint16_t  Xpos;
	uint16_t  Ypos;
	uint16_t  Zpos;
	uint8_t   Status;                  // Unsure, might be uint16_t
	uint8_t   Unknown[3];
} Objective;


typedef struct {                       // CPObjective struct (item of CPObjectives array) | 12 bytes (could also be 14 bytes, but NOT more)
	uint16_t  Child;                   // From RGAME.C (unverified); sizes from Mefistotelis .xml
	uint16_t  Parent;
	uint8_t   UseCount;
	uint8_t   Player;
	uint8_t   Flags;
	uint8_t   ActionType;
	uint8_t   Action;
	//uint16_t  X;                     // Is this referencing POSITIONS ...
	//uint16_t  Y;
	//uint16_t  Z;
	uint8_t   X;                       // ... or TILES, similar to struct Command?
	uint8_t   Y;
	uint8_t   Z;
} CPObjective;


typedef struct {                                     // Game data struct (covers entirety of content of GAMExx.DAT file)
	/*      0 */  uint8_t      Unknown_1[6];         // What is this? (two bytes might be header according to RGAME.C)
	/*      6 */  MapWho       MapWho;
	/*  32774 */  uint8_t      Offset_ref[2];        // What is this? -> check FreeSynd sources
	/*  32776 */  Person       People[256];
	/*  56328 */  Vehicle      Vehicles[64];
	/*  59016 */  Object       Objects[400];
	/*  71016 */  Weapon       Weapons[512];
	/*  89448 */  Effect       Effects[256];
	/*  97128 */  Command      Commands[2048];
	/* 113512 */  World        Worlds[32];           // Was unknown before, guessing this is: World[32] * 12 bytes = 384 bytes
	/* 113896 */  uint8_t      Unknown_2[64];        // Likely either MapInfos or Worlds (if sized 14 bytes per item)
	/* 113960 */  MapInfo      MapInfos;             // Might start EARLIER (to include additional members used in RGAME.C: SSMapX, SSMapY, SSMoveActive, SSScreenMode, SSVersion, SSSeed, SSPersonCount, SSTimer)
	/* 113974 */  Objective    Objectives[8];        // Array size is 8 according to RGAME.C, but 6 according to FreeSynd leveldata.h
	/* 114086 */  CPObjective  CPObjectives[128];    // Could be: CPObjective[128] * 12 bytes = 1536 bytes (?) Max. would be 1924 bytes
	/* 115622 */  uint8_t      Unknown_3[388];       // What is this?
} GameData;


#endif // GAMEDATA_H
