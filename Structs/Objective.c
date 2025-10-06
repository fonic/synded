
// FreeSynd - leveldata.h

    /*!
	 * total: 14 bytes
	 */
	struct Objectives {
		/* only max 5 objectives are non-zero, we will read 6
		 * 0x00 action for non-agent(?) ;0x01 persuade; 0x02 assassinate;
		 * 0x03 protect; 0x05 equipment aquisition; 0x0a combat sweep (police);
		 * 0x0b combat sweep; 0x0e destroy vehicle; 0x0f use vehicle;
		 * 0x10 evacuate
		 * more info in mission.cpp : loadLevel()
		 */
		uint8 type[2];
		// 'offset + 32774' gives the offset in this file of the first objective
		uint8 offset[2];
		uint8 mapposx[2];
		uint8 mapposy[2];
		uint8 mapposz[2];
		/* If "protect", the next objective are the goals and their type is zero.
		 * The list finish with zero and the offset of the protected item ?
		 * The status flag is set to 1 if the objective has to be completed
		 */
		uint8 status;
		uint8 unkn1[3];
	};


// RGAME.C

	// Names: SSObjectives

	new_save_struct.SSObjectives[1].Data = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSPeople[109]);
	new_save_struct.SSObjectives[1].Status	= 0;
	new_save_struct.SSObjectives[1].Objective	= 0x1;	// Persuade
	new_save_struct.SSObjectives[1].Xpos	= 0;
	new_save_struct.SSObjectives[1].Ypos	= 0;
	new_save_struct.SSObjectives[1].Zpos	= 0;

	new_save_struct.SSObjectives[2].Status = OBJ_STATUS_DONE;
	new_save_struct.SSObjectives[2].Objective = 0;
	new_save_struct.SSObjectives[2].Data = 0;
	new_save_struct.SSObjectives[2].Xpos = 0;
	new_save_struct.SSObjectives[2].Ypos = 0;
	new_save_struct.SSObjectives[2].Zpos = 0;

	new_save_struct.SSObjectives[3].Status = OBJ_STATUS_DONE;
	new_save_struct.SSObjectives[4].Status = OBJ_STATUS_DONE;
	new_save_struct.SSObjectives[5].Status = OBJ_STATUS_DONE;
	new_save_struct.SSObjectives[6].Status = OBJ_STATUS_DONE;
	new_save_struct.SSObjectives[7].Status = OBJ_STATUS_DONE;
