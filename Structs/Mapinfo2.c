
// FreeSynd - leveldata.h

	// Not defined; might be part of MapInfos struct (could start EARLIER):
	struct LevelDataAll {
		...
		/* 113512 */ Unkn09 u09;         // <- missing data might be here
		/* 113960 */ MapInfos mapinfos;
		...
	};


// RGAME.C

	// Names: none (no separate struct, part of main struct)

	new_save_struct.SSMapX=save_struct.SSMapX;
	new_save_struct.SSMapY=save_struct.SSMapY;

	new_save_struct.SSMoveActive=save_struct.SSMoveActive;
	new_save_struct.SSScreenMode=save_struct.SSScreenMode;
	new_save_struct.SSVersion=save_struct.SSVersion;
	new_save_struct.SSSeed=save_struct.SSSeed;
	new_save_struct.SSPersonCount=save_struct.SSPersonCount;
	new_save_struct.SSTimer=save_struct.SSTimer;
