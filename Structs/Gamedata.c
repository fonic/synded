
// FreeSynd - leveldata.h

	/*!
	* This is the main structure.
	*/
	struct LevelDataAll {
		/*      0 */ Unkn01 u01;
		/*      6 */ Map map;
		/*  32774 0x0*/ uint8 offset_ref[2];
		/*  32776 0x02*/ People people[256];
		/*  56328 0x5C02*/ Cars cars[64];
		/*  59016 0x6682*/ Statics statics[400];
		/*  71016 0x9562*/ Weapons weapons[512];
		/*  89448 0xDD62*/ Sfx sfx[256];
		/*  97128 0xFB62*/ LevelData::Scenarios scenarios[2048];
		/* 113512 */ Unkn09 u09;
		/* 113960 */ MapInfos mapinfos;
		/* 113974 */ Objectives objectives[6];
		/* 114058 */ Unkn11 u11;
	};


// RGAME.C

	void	copyStuff()
	{
		UWORD	counter=0;
		ULONG	tmp;
		SLONG rett;

		new_save_struct.SSMapX=save_struct.SSMapX;
		new_save_struct.SSMapY=save_struct.SSMapY;
		for(counter=0;counter<256;counter++)
			new_save_struct.SSUserString[counter]=0;
		for(counter=0;counter<256;counter++)
			new_save_struct.SSUserString[counter]=save_struct.SSUserString[counter];
		new_save_struct.SSMoveActive=save_struct.SSMoveActive;
		new_save_struct.SSScreenMode=save_struct.SSScreenMode;
		new_save_struct.SSVersion=save_struct.SSVersion;
		new_save_struct.SSSeed=save_struct.SSSeed;
		new_save_struct.SSPersonCount=save_struct.SSPersonCount;
		new_save_struct.SSTimer=save_struct.SSTimer;

		new_save_struct.SSHeader[0]=save_struct.SSHeader[0];
		new_save_struct.SSHeader[1]=save_struct.SSHeader[1];
		for(counter=0;counter<256;counter++)
			new_save_struct.SSPeople[counter]=save_struct.SSPeople[counter];
		for(counter=0;counter<512;counter++)
			new_save_struct.SSWeapons[counter]=save_struct.SSWeapons[counter];
		for(counter=0;counter<(256*8);counter++)
			new_save_struct.SSCommands[counter]=save_struct.SSCommands[counter];
		new_save_struct.SSMapNumber=save_struct.SSMapNumber;
		new_save_struct.SSLoBoundaryx=save_struct.SSLoBoundaryx;
		new_save_struct.SSLoBoundaryy=save_struct.SSLoBoundaryy;
		new_save_struct.SSHiBoundaryx=save_struct.SSHiBoundaryx;
		new_save_struct.SSHiBoundaryy=save_struct.SSHiBoundaryy;
		new_save_struct.SSCPLvlInit=save_struct.SSCPLvlInit;
		new_save_struct.SSStructEnd=save_struct.SSStructEnd;

		for(counter=0;counter<NO_VEHICLES;counter++)
		{
			new_save_struct.SSVehicles[counter].GVehicle=save_struct.SSVehicles[counter].GVehicle;
			new_save_struct.SSVehicles[counter].ChildHeld=save_struct.SSVehicles[counter].ChildHeld;
			new_save_struct.SSVehicles[counter].ParentHeld=save_struct.SSVehicles[counter].ParentHeld;
			new_save_struct.SSVehicles[counter].LinkTo=save_struct.SSVehicles[counter].LinkTo;
			new_save_struct.SSVehicles[counter].LinkX=save_struct.SSVehicles[counter].LinkX;
			new_save_struct.SSVehicles[counter].LinkY=save_struct.SSVehicles[counter].LinkY;
			new_save_struct.SSVehicles[counter].LinkZ=save_struct.SSVehicles[counter].LinkZ;
			new_save_struct.SSVehicles[counter].MaxSpeed=save_struct.SSVehicles[counter].MaxSpeed;
			new_save_struct.SSVehicles[counter].TravelAngle=save_struct.SSVehicles[counter].TravelAngle;
		}

		for(counter=0;counter<400;counter++)
		{
			new_save_struct.SSObjects[counter].GObject=save_struct.SSObjects[counter].GObject;
			new_save_struct.SSObjects[counter].Connected=save_struct.SSObjects[counter].Connected;
		}

		for(counter=0;counter<256;counter++)
		{
			new_save_struct.SSEffects[counter].GEffect=save_struct.SSEffects[counter].GEffect;
			new_save_struct.SSEffects[counter].WhoShot=save_struct.SSEffects[counter].WhoShot;
		}

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

		for(counter=0;counter<8;counter++)
		{
			new_save_struct.SSObjectives[counter].Status=save_struct.SSObjectives[counter].Status;
			new_save_struct.SSObjectives[counter].Objective=save_struct.SSObjectives[counter].Objective;
			new_save_struct.SSObjectives[counter].Data=save_struct.SSObjectives[counter].Data;
			new_save_struct.SSObjectives[counter].Xpos=save_struct.SSObjectives[counter].Xpos;
			new_save_struct.SSObjectives[counter].Ypos=save_struct.SSObjectives[counter].Ypos;
			new_save_struct.SSObjectives[counter].Zpos=save_struct.SSObjectives[counter].Zpos;
		}

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

		for(counter=0;counter<(128*128);counter++)
		{
			new_save_struct.SSMapwho[counter]=save_struct.SSMapwho[counter];
		}
	}
