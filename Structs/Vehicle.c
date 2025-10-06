
// FreeSynd - leveldata.h

    /*!
	 * This structure contains all cars in the game, including destroyed
	 * This struct size is 42.
	 */
	struct Cars {
		uint8 offset_next[2];
		uint8 offset_prev[2];
		uint8 mapposx[2];
		uint8 mapposy[2];
		uint8 mapposz[2];
		// 0x04 on map(visible)
		// 0x05 not on map(hidden)
		uint8 desc;
		uint8 unkn1;
		uint8 unkn2;
		uint8 unkn3;
		uint8 index_base_anim[2];
		uint8 index_current_frame[2];
		uint8 index_current_anim[2];
		uint8 health[2];
		uint8 offset_last_enemy[2];
		uint8 type; // 0x02
		uint8 sub_type;
		uint8 orientation;
		uint8 unkn4;
		uint8 offset_of_driver; //driver
		uint8 unkn5[11];
		uint8 speed;
		uint8 unkn6;
	};


// RGAME.C

	// Names: SSVehicles, Vehicle, GVehicle

	tvehicle->GVehicle.Child		=	0;
	tvehicle->GVehicle.Parent		=	GET_MODEL_OFFSET((struct Global *)tperson);
//	tvehicle->GVehicle.Xpos			=;
//	tvehicle->GVehicle.Ypos			=;
//	tvehicle->GVehicle.Zpos			=;
	tvehicle->GVehicle.Status		=	4;
	tvehicle->GVehicle.Affect		=	0;
//	tvehicle->GVehicle.BaseFrame	=;
//	tvehicle->GVehicle.Frame		=;
//	tvehicle->GVehicle.OldFrame		=;
//	tvehicle->GVehicle.Life			=;
	tvehicle->GVehicle.WhoShotMe	=	0;
	tvehicle->GVehicle.Model		=	2;
	tvehicle->GVehicle.State		=	0xD;
//	tvehicle->GVehicle.Angle		=;
//	tvehicle->GVehicle.ZAngle		=;
	tvehicle->ChildHeld				=	GET_MODEL_OFFSET((struct Global *)tperson);
	tvehicle->ParentHeld			=	0;
	tvehicle->LinkTo				=	0;
	tvehicle->LinkX					=	0;
	tvehicle->LinkY					=	0;
	tvehicle->LinkZ					=	0;
//	tvehicle->MaxSpeed				=;
//	tvehicle->TravelAngle			=;
