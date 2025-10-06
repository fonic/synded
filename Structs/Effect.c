
// FreeSynd - leveldata.h

	/*!
	* total: 30 bytes
	*/
	struct Sfx {
		uint8 offset_next[2];
		uint8 offset_prev[2];
		uint8 mapposx[2];
		uint8 mapposy[2];
		uint8 mapposz[2];
		uint8 unkn1[4];
		uint8 index_base_anim[2];
		uint8 index_current_frame[2];
		uint8 index_current_anim[2];
		uint8 unkn2[8];
		uint8 offset_owner[2];
	};


// RGAME.C

	// Names: SSEffects, Effect, GEffect

	for(counter=0;counter<256;counter++)
	{
		new_save_struct.SSEffects[counter].GEffect=save_struct.SSEffects[counter].GEffect;
		new_save_struct.SSEffects[counter].WhoShot=save_struct.SSEffects[counter].WhoShot;
	}

	case	EFFECT:
	{
		struct	Effect			*temp_SSEffects;

		temp_SSEffects = (struct Effect *)NEWSTRUCT(new_save_struct.SSMapwho[counter]);
		tmp=temp_SSEffects->GEffect.Child;
		temp_SSEffects->GEffect.Child=adjustglobal(tmp);
		tmp=temp_SSEffects->GEffect.Parent;
		temp_SSEffects->GEffect.Parent=adjustglobal(tmp);
		tmp=temp_SSEffects->GEffect.WhoShotMe;
		temp_SSEffects->GEffect.WhoShotMe=adjustglobal(tmp);

		tmp=temp_SSEffects->WhoShot;
		temp_SSEffects->WhoShot=adjustglobal(tmp);
		break;
	}
