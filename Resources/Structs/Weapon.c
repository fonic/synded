
// FreeSynd - leveldata.h

    /*!
	 *
	 * total: 36 bytes
	 */
	struct Weapons {
		uint8 offset_next[2];
		uint8 offset_prev[2];
		uint8 mapposx[2];
		uint8 mapposy[2];
		uint8 mapposz[2];
		// 0x04 on map
		// 0x05 not on map(in inventory)
		uint8 desc;
		uint8 unkn2;
		uint8 unkn3;
		uint8 unkn4;
		uint8 index_base_anim[2];
		uint8 index_current_frame[2];
		uint8 index_current_anim[2];
		uint8 unkn5[4];
		// look peds for more info
		uint8 type; // 0x04
		/* 0x01 persuadertron; 0x02 pistol; 0x03 gauss gun; 0x04 shotgun;
		 * 0x05 uzi; 0x06 minigun; 0x07 laser; 0x08 flamer; 0x09 long range;
		 * 0x0A scanner; 0x0B medikit; 0x0C time bomb; 0x0D access card;
		 * 0x0E invalid; 0x0F invalid; 0x10 invalid; 0x11 energy shield;
		 */
		uint8 sub_type;
		uint8 unkn6[2];
		uint8 offset_next_inventory[2];
		uint8 offset_prev_inventory[2];
		uint8 offset_owner[2];
		uint8 unkn7[2];
	};


// RGAME.C

	// Names: SSWeapons, Weapon, GWeapon

	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Child = 0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Parent = 0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Xpos = 14484;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Ypos = 3436;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Zpos = 1024;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Status = 4;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Affect = 0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.BaseFrame = 0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Frame = 0x8D2;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.OldFrame = 0x171;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Life = 2;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.WhoShotMe = 0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Model = 4;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.State = 3;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Angle = 0xD0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.ZAngle = 0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].ChildWeapon = 0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].ParentWeapon = 0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].WhoOwnsWeapon = 0;
	new_save_struct.SSWeapons[NO_WEAPONS-1].RepairCount = 0;
