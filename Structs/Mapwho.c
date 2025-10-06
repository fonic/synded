
// FreeSynd - leveldata.h

	/*!
	* The objs field is an array that represent the tiles of the map
	* (every map are 128x128 tiles). The values plus 32774 give an offset
	* in this file that is the entity placed on this tile.
	* The resulting offset can be 98309 max and only peds, vehicle, objects
	* and weapons can be indexed.
	* Was not able to verify correctness
	* total: 32768 bytes
	*/
	struct Map {//
		//! 128*128 offsets size 2 bytes(LE)
		uint8 objs[32768];
	};


// RGAME.C

	for(counter=0;counter<(128*128);counter++)
	{
		new_save_struct.SSMapwho[counter]=save_struct.SSMapwho[counter];
	}

	void	move_off_mapwho(struct Global *tglobal)
	{

		UWORD   *mappos;
		struct 	Global 	*parent;
		struct 	Global 	*child;

		if (tglobal->Status & STATUS_MAPWHO)
		{
			mappos=&_mapwho[GET_MAPWHO_OFFSET(tglobal->Xpos,tglobal->Ypos)];
			if (tglobal->Parent)
			{
				parent=GET_GLOBAL_PTR(tglobal->Parent);
				parent->Child=tglobal->Child;
			}
			else
				*mappos=tglobal->Child;
			if (tglobal->Child)
			{
				child=GET_GLOBAL_PTR(tglobal->Child);
				child->Parent=tglobal->Parent;
			}
			tglobal->Status&=(~STATUS_MAPWHO);
		}
		return;
	}
