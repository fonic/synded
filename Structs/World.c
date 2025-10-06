
// FreeSynd - leveldata.h

	// Not defined; might be part of Unkn09

	struct Unkn09{
		uint8 unkn10[448];
	};

	struct LevelDataAll {
		...
		/*  97128 0xFB62*/ LevelData::Scenarios scenarios[2048];
        /* 113512 */ Unkn09 u09;         // SSWorlds[32] (?)
		/* 113960 */ MapInfos mapinfos;
		...
	};


// RGAME.C

	// Names: SSWorlds

	for(counter=0;counter<32;counter++)
	{
		new_save_struct.SSWorlds[counter].WindXSpeed=save_struct.SSWorlds[counter].WindXSpeed;
		new_save_struct.SSWorlds[counter].WindYSpeed=save_struct.SSWorlds[counter].WindYSpeed;
		new_save_struct.SSWorlds[counter].Population=save_struct.SSWorlds[counter].Population;
		new_save_struct.SSWorlds[counter].Temperature=save_struct.SSWorlds[counter].Temperature;
		new_save_struct.SSWorlds[counter].WindSpeed=save_struct.SSWorlds[counter].WindSpeed;
		new_save_struct.SSWorlds[counter].WindAngle=save_struct.SSWorlds[counter].WindAngle;
		new_save_struct.SSWorlds[counter].Industry=save_struct.SSWorlds[counter].Industry;
		new_save_struct.SSWorlds[counter].Crime=save_struct.SSWorlds[counter].Crime;
		new_save_struct.SSWorlds[counter].Gravity=save_struct.SSWorlds[counter].Gravity;
		new_save_struct.SSWorlds[counter].Density=save_struct.SSWorlds[counter].Density;
	}
