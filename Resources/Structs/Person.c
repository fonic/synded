
// FreeSynd - leveldata.h

    /*!
	 * This structure contains all people in the game, including agents
	 * This struct size is 92.
	 * most 2 byte variable have little-endianess byte order(LE)
	 */
	struct People {
		// (LE data)'offset + 32774' gives the offset in this
		// file of the next object
		uint8 offset_next[2];
		// (LE data)'offset + 32774' gives the offset in this
		// file of the previous object (sometimes weapon, or
		// the next target for example ???)
		uint8 offset_prev[2];
		// [0] - offset, [1] - tile
		uint8 mapposx[2];
		uint8 mapposy[2];
		// to convert to our system use as uint16(LE)
		// tile = (uint16)/128, offz =(uint16)%128 or offz = mapposz[0] & 0x1F
		uint8 mapposz[2];
		/*!
		 * This field gives information on the ped location. Values are:
		 * 0x04 - ped on map
		 * 0x05 - ped not on map(driving)
		 * 0x0D - they are not visible/present on original map(on water located), purpose?
		 * 0x0C - located level above possible walking surface, purpose?
		 * 0x0D and 0x0C are excluded from being loaded
		 */
		uint8 location;
		/*!
		 * This field gives information on the ped's state. Values are:
		 * 0x0 - standing
		 * 0x10 - walking
		 * 0x11 - dead
		 */
		uint8 state;
		uint8 unkn3[2];         // nothing changes when this changes
		uint8 index_base_anim[2];  //index in (HSTA-0.ANI)
		uint8 index_current_frame[2];   //index in (HFRA-0.ANI)
		uint8 index_current_anim[2]; // index in (HSTA-0.ANI)
		uint8 health[2];
		uint8 offset_last_enemy[2];
		//0x01 ped; 0x02 vehicle; 0x04 weapon;
		//0x05 object; allow to display a target, a pickup, and for minimap
		uint8 type;
		uint8 status; // this can be sub type(?)
		//from 0xF0 to 0x10 : south = 0
		//from 0x10 to 0x30 : south-east = 1
		//from 0x30 to 0x50 : east = 2
		//from 0x50 to 0x70 : east-north = 3
		//from 0x70 to 0x90 : north = 4
		//from 0x90 to 0xB0 : north-west = 5
		//from 0xB0 to 0xD0 : west = 6
		//from 0xD0 to 0xF0 : west-south = 7
		// surface is mapped not to 360 degrees/surface, but 256 degrees/surface
		uint8 orientation;
		uint8 unkn4;
		// when 01 pedestrian, 02 agent, 04 police, 08 guard, 16 criminal
		uint8 type_ped;
		uint8 unkn5[3];
		uint8 offset_of_persuader[2];
		uint8 unkn6[2];
		uint8 offset_of_vehicle[2];
		// currently executed scenario
		uint8 offset_scenario_curr[2];
		// starting point for current scenario
		uint8 offset_scenario_start[2];
		uint8 unkn7[2];
		uint8 offset_of_vehicle_2[2]; // ??
		uint8 goto_mapposx[2];
		uint8 goto_mapposy[2];
		uint8 goto_mapposz[2];
		uint8 unkn8[6];
		uint8 offset_equipment[2];
		//bitmask, 0b - gender, 1-2b - leg, 3-4b - arm, 5-6b - chest
		// 7-8b - heart, 9-10b - eye, 11-12b - brain, 13-15b - unknown
		uint8 mods_info[2];
		uint8 unkn9[6];
		uint8 offset_cur_weapon[2];
		// IPA levels: white bar level,set level,exhaused level and forced level
		uint8 unkn10;
		uint8 adrena_amount;
		uint8 adrena_dependency;
		uint8 adrena_effect;
		uint8 unkn11;
		uint8 inteli_amount;
		uint8 inteli_dependency;
		uint8 inteli_effect;
		uint8 unkn12;
		uint8 percep_amount;
		uint8 percep_dependency;
		uint8 percep_effect;
		uint8 unkn13;
		uint8 unkn14[9];
	};


// RGAME.C

	// Names: SSPeople, Person, GPerson

	tperson->Unique					=	1;
	tperson->HugDistance			=	0;
	tperson->Persuaded				=	0;
	tperson->ChildHeld				=	0;
	tperson->ParentHeld				=	GET_MODEL_OFFSET((struct Global *)tvehicle);
	tperson->Command				=	GET_COMMAND_OFFSET((struct Command *)&new_save_struct.SSCommands[commands]);
	tperson->StartCommand			=	GET_COMMAND_OFFSET((struct Command *)&new_save_struct.SSCommands[commands]);
	tperson->Target					=	0;
	tperson->Data					=	GET_MODEL_OFFSET((struct Global *)tvehicle);
	tperson->GotoX					=	14400;
	tperson->GotoY					=	10304;
	tperson->GotoZ					=	256;
	tperson->LastXpos				=	tvehicle->GVehicle.Xpos;
	tperson->LastYpos				=	tvehicle->GVehicle.Ypos;
	tperson->HugGotoZ				=	0;
	tperson->ChildWeapon			=	0;
	tperson->Equipment				=	0;
	tperson->ParentRank				=	0;
	tperson->RankPosition			=	0;
	tperson->Count					=	0;
	tperson->WeaponHolding			=	0;
	tperson->WeaponInUse			=	0;
	tperson->Level1Base				=	0x80;
	tperson->Level1Balance			=	0x80;
	tperson->Level1True				=	0x80;
	tperson->Level1Fixed			=	0;
	tperson->Level2Base				=	0x80;
	tperson->Level2Balance			=	0x80;
	tperson->Level2True				=	0x80;
	tperson->Level2Fixed			=	0;
	tperson->Level3Base				=	0x80;
	tperson->Level3Balance			=	0x80;
	tperson->Level3True				=	0x80;
	tperson->Level3Fixed			=	0;
	tperson->LevelRecovery			=	5;
	tperson->Speed					=	tvehicle->MaxSpeed;
	tperson->MaxSpeed				=	tvehicle->MaxSpeed;
	tperson->BaseSpeed				=	0x20;
	tperson->OldState				=	0;
	tperson->NewState				=	S_PERSON_WANDER;
	tperson->HugChangeDir			=	0;
	tperson->HugStartAngle			=	0;
	tperson->HitAngle				=	0;
