
// FreeSynd - leveldata.h

	/*!
	* total: 14 bytes
	*/
	struct MapInfos {
		uint8 map[2];
		uint8 min_x[2];
		uint8 min_y[2];
		uint8 max_x[2];
		uint8 max_y[2];
		//status flag is set to 1 if the mission has been successfully completed
		uint8 status;
		uint8 unkn1[3];
	};


// RGAME.C

	// Names: none (no separate struct, part of main struct)

	new_save_struct.SSMapNumber=save_struct.SSMapNumber;
	new_save_struct.SSLoBoundaryx=save_struct.SSLoBoundaryx;
	new_save_struct.SSLoBoundaryy=save_struct.SSLoBoundaryy;
	new_save_struct.SSHiBoundaryx=save_struct.SSHiBoundaryx;
	new_save_struct.SSHiBoundaryy=save_struct.SSHiBoundaryy;
	new_save_struct.SSCPLvlInit=save_struct.SSCPLvlInit;
	new_save_struct.SSStructEnd=save_struct.SSStructEnd;
