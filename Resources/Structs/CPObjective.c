
// FreeSynd - leveldata.h

	// Not defined; might be part of Unkn11

	struct Unkn11 {
		uint8 unkn10[1952];
	};

	struct LevelDataAll {
		...
		/* 113960 */ MapInfos mapinfos;
		/* 113974 */ Objectives objectives[6];
		/* 114058 */ Unkn11 u11;                // SSCPObjectives[128] (?)
	};


// RGAME.C

	// Names: SSCPObjectives

	for(counter=0;counter<128;counter++)
	{
		new_save_struct.SSCPObjectives[counter].Child=save_struct.SSCPObjectives[counter].Child;
		new_save_struct.SSCPObjectives[counter].Parent=save_struct.SSCPObjectives[counter].Parent;
		new_save_struct.SSCPObjectives[counter].UseCount=save_struct.SSCPObjectives[counter].UseCount;
		new_save_struct.SSCPObjectives[counter].Player=save_struct.SSCPObjectives[counter].Player;
		new_save_struct.SSCPObjectives[counter].Flags=save_struct.SSCPObjectives[counter].Flags;
		new_save_struct.SSCPObjectives[counter].ActionType=save_struct.SSCPObjectives[counter].ActionType;
		new_save_struct.SSCPObjectives[counter].Action=save_struct.SSCPObjectives[counter].Action;
		new_save_struct.SSCPObjectives[counter].X=save_struct.SSCPObjectives[counter].X;
		new_save_struct.SSCPObjectives[counter].Y=save_struct.SSCPObjectives[counter].Y;
		new_save_struct.SSCPObjectives[counter].Z=save_struct.SSCPObjectives[counter].Z;
	}

	case	11:		// Western Australia
		new_save_struct.SSCPObjectives[0].Player=0xFF;
		new_save_struct.SSCPObjectives[0].ActionType=3;
		new_save_struct.SSCPObjectives[1].Player=0xFF;
		new_save_struct.SSCPObjectives[1].ActionType=3;
		new_save_struct.SSCPObjectives[2].Player=0xFF;
		new_save_struct.SSCPObjectives[2].ActionType=3;
		new_save_struct.SSCPObjectives[3].Player=0xFF;
		new_save_struct.SSCPObjectives[3].ActionType=3;
