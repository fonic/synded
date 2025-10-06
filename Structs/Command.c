
// FreeSynd - leveldata.h

    /*!
	 * total: 8 bytes
	 */
	struct Scenarios {
		// first scenario should be skipped, type 0x00
		uint8 next[2];
		uint8 offset_object[2];
		// tile_x_ = tilex >> 1
		// off_x_ = (tilex & 0x01) << 7
		uint8 tilex;
		// tile_y_ = tiley >> 1
		// off_y_ = (tiley & 0x01) << 7
		uint8 tiley;
		// tile_z_ = tilez
		uint8 tilez;
		/*!
		 * Gives the type of scenario. Values are:
		 * 0x00 - unset scenario type, is found at start of array and end;
		 * 0x01 - walking/driving to pos, x,y defined, no object offset;
		 * 0x02 - vehicle to use and goto
		 * 0x03 - ?(south africa)
		 * 0x05 - ?(kenya)
		 * 0x06 - (kenya) - ped offset when in vehicle, and? (TODO)
		 * 0x07 - assasinate target escaped, mission failed
		 * 0x08 - walking to pos, triggers on our agents in range, x,y defined
		 * 0x09 - repeat from start, actually this might be end of script
		 * 0x0A - train stops and waits
		 * 0x0B - protected target reached destination(kenya) (TODO properly)
		 */
		uint8 type;
	};


// RGAME.C

	// Names: SSCommands, Command

	new_save_struct.SSCommands[commands].Next = GET_COMMAND_OFFSET((struct Command *)&new_save_struct.SSCommands[commands+1]);
	new_save_struct.SSCommands[commands].Data = GET_MODEL_OFFSET((struct Global *)tvehicle);
	new_save_struct.SSCommands[commands].GotoX =0;
	new_save_struct.SSCommands[commands].GotoY =0;
	new_save_struct.SSCommands[commands].GotoZ =0;
	new_save_struct.SSCommands[commands].State =2;

	new_save_struct.SSCommands[commands+1].Next =0;
	new_save_struct.SSCommands[commands+1].Data =0;
	new_save_struct.SSCommands[commands+1].GotoX =0x70;
	new_save_struct.SSCommands[commands+1].GotoY =0x50;
	new_save_struct.SSCommands[commands+1].GotoZ =0x2;
	new_save_struct.SSCommands[commands+1].State =1;
