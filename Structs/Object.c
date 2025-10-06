
// FreeSynd - leveldata.h

	/*!
	*
	* total: 30 bytes
	*/
	struct Statics {
		uint8 offset_next[2];
		uint8 offset_prev[2];
		uint8 mapposx[2];
		uint8 mapposy[2];
		uint8 mapposz[2];
		// 0x04 - on map;
		// 0x06 - on map, but why not 0x04?
		// 0x07 - on map, objects visibility is dependent on
		// orientation 0x40, 0x80 are drawn
		uint8 desc;
		uint8 unkn11;
		uint8 unkn12;
		uint8 unkn13;
		uint8 index_base_anim[2];
		uint8 index_current_frame[2];
		uint8 index_current_anim[2];
		uint8 unkn20[4];
		uint8 type;
		// more info mapobject.cpp
		uint8 sub_type;
		uint8 orientation;
		uint8 unkn27[3];
	};


// RGAME.C

	// Names: SSObjects, Object, GObject

	for(counter=0;counter<400;counter++)
	{
		new_save_struct.SSObjects[counter].GObject=save_struct.SSObjects[counter].GObject;
		new_save_struct.SSObjects[counter].Connected=save_struct.SSObjects[counter].Connected;
	}

	case	OBJECT:
	{
		struct	Object			*temp_SSObjects;

		temp_SSObjects = (struct Object *)NEWSTRUCT(new_save_struct.SSMapwho[counter]);
		tmp=temp_SSObjects->GObject.Child;
		temp_SSObjects->GObject.Child=adjustglobal(tmp);
		tmp=temp_SSObjects->GObject.Parent;
		temp_SSObjects->GObject.Parent=adjustglobal(tmp);
		tmp=temp_SSObjects->GObject.WhoShotMe;
		temp_SSObjects->GObject.WhoShotMe=adjustglobal(tmp);

		//			tmp=temp_SSObjects->Connected;
		//			temp_SSObjects->Connected=adjustglobal(tmp);
		break;
	}

