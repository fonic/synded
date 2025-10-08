#include	<exec/types.h>
#include <stddef.h>
#include <stdio.h>
#include "syndicat.h"
#include	"macros.h"

typedef	WORD	SWORD;
typedef	LONG	SLONG;
typedef	BYTE	SBYTE;
#include	"libstruc.h"

#define	MS_MAX_ALTERABLE_CARS	16

#define	OLDOFF(m)	(offsetof(struct SaveStruct, m) - offsetof(struct SaveStruct, SSHeader))
#define	NEWOFF(m)	(offsetof(struct NewSaveStruct, m) - offsetof(struct NewSaveStruct, SSHeader))
#define	NEWSTRUCT(m)	((ULONG)new_save_struct.SSHeader + m)
enum	{UNKNOWN, VEHICLE, OBJECT, WEAPON, EFFECT, COMMAND, PEOPLE};

__far struct	SaveStruct		save_struct;
__far struct	NewSaveStruct	new_save_struct;

UWORD	lo_boundaryx;
UWORD lo_boundaryy;
UWORD hi_boundaryx;
UWORD hi_boundaryy;

UBYTE	iAm(UWORD offset)
{
	if(offset>0)
	{
		int	lo,hi;

	// Correct Vehicles
		lo = NEWOFF(SSVehicles);
		hi = NEWOFF(SSObjects);
		if((offset >= lo) && (offset < hi))
			return(VEHICLE);
	// Correct Objects
		lo = NEWOFF(SSObjects);
		hi = NEWOFF(SSWeapons);
		if((offset >= lo) && (offset < hi))
			return(OBJECT);
	// Correct Weapons
		// if within weapons range
		lo = NEWOFF(SSWeapons);
		hi = NEWOFF(SSEffects);
		if((offset >= lo) && (offset < hi))
			return(WEAPON);
	// Correct Effects
		lo = NEWOFF(SSEffects);
		hi = NEWOFF(SSCommands);
		if((offset >= lo) && (offset < hi))
			return(EFFECT);
	// Correct Commands
		lo = NEWOFF(SSCommands);
		hi = NEWOFF(SSWorlds);
		if((offset >= lo) && (offset < hi))
			return(COMMAND);
	}
	return(UNKNOWN);
}

UWORD	adjustglobal(UWORD	offset)
{
	ULONG	lo=0,hi=0;
	ULONG tempcounter;
	UWORD tempmapwho;
	UBYTE done=0;


	if(offset>0)
	{

	// Correct Vehicles
		if(done==0)
		{
			lo = OLDOFF(SSVehicles);
			hi = OLDOFF(SSObjects);
			if((offset >= lo) && (offset < hi))
			{
				offset += (offset - lo)/sizeof(struct OldVehicle)*2;
				done=1;
			}
		}


	// Correct Objects
		if(done==0)
		{
			lo = OLDOFF(SSObjects);
			hi = OLDOFF(SSWeapons);
			if((offset >= lo) && (offset < hi))
			{
				offset += (offset - lo)/sizeof(struct OldObject)*2;
				offset+=(2 * (NO_VEHICLES));
				done=1;
			}
		}

	// Correct Weapons
		// if within weapons range
		if(done==0)
		{
			lo = OLDOFF(SSWeapons);
			hi = OLDOFF(SSEffects);
			if((offset >= lo) && (offset < hi))
			{
				offset+=(2 * (NO_VEHICLES));
				offset+=(2 * (NO_OBJECTS));
				done=1;
			}
		}

	// Correct Effects
		if(done==0)
		{
			lo = OLDOFF(SSEffects);
			hi = OLDOFF(SSCommands);
			if((offset >= lo) && (offset < hi))
			{
				offset += (offset - lo)/sizeof(struct OldEffect)*2;
				offset+=(2 * (NO_VEHICLES));
				offset+=(2 * (NO_OBJECTS));
				done=1;
			}
		}

	// Correct Commands
		if(done==0)
		{
			lo = OLDOFF(SSCommands);
			hi = OLDOFF(SSWorlds);
			if((offset >= lo) && (offset < hi))
			{
				offset+=(2 * (NO_VEHICLES));
				offset+=(2 * (NO_OBJECTS));
				offset+=(2 * (NO_EFFECTS));
				done=1;
			}
		}
	}

	return(offset);
}

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

void	adjustMapWho()
{
	int	counter;

	for(counter=0;counter<(128*128);counter++)
	{
		if (new_save_struct.SSMapwho[counter]>0)
		{
			new_save_struct.SSMapwho[counter] = adjustglobal(new_save_struct.SSMapwho[counter]);
		}
	}
}

void	adjustEverything()
{
	int counter;
	UWORD	tmp;

	for(counter=0;counter<(128*128);counter++)
	{
	// Calculate new offsets
		ULONG tempcounter;

		switch (iAm(new_save_struct.SSMapwho[counter]))
		{
			case	VEHICLE:
			{
				struct	Vehicle			*temp_SSVehicles;

				temp_SSVehicles = (struct Vehicle *)NEWSTRUCT(new_save_struct.SSMapwho[counter]);
				tmp=temp_SSVehicles->GVehicle.Child;
				temp_SSVehicles->GVehicle.Child=adjustglobal(tmp);
				tmp=temp_SSVehicles->GVehicle.Parent;
				temp_SSVehicles->GVehicle.Parent=adjustglobal(tmp);
				tmp=temp_SSVehicles->GVehicle.WhoShotMe;
				temp_SSVehicles->GVehicle.WhoShotMe=adjustglobal(tmp);

				tmp=temp_SSVehicles->ChildHeld;
				temp_SSVehicles->ChildHeld=adjustglobal(tmp);
				tmp=temp_SSVehicles->ParentHeld;
				temp_SSVehicles->ParentHeld=adjustglobal(tmp);
				tmp=temp_SSVehicles->LinkTo;
				break;
			}
			case	PEOPLE:
			{
				struct	Person			*temp_SSPeople;

				temp_SSPeople = (struct Person *)NEWSTRUCT(new_save_struct.SSMapwho[counter]);
				tmp=temp_SSPeople->GPerson.Child;
				temp_SSPeople->GPerson.Child=adjustglobal(tmp);
				tmp=temp_SSPeople->GPerson.Parent;
				temp_SSPeople->GPerson.Parent=adjustglobal(tmp);
				tmp=temp_SSPeople->GPerson.WhoShotMe;
				temp_SSPeople->GPerson.WhoShotMe=adjustglobal(tmp);


	//			tmp=temp_SSPeople->Unique;
	//			temp_SSPeople->Unique=adjustglobal(tmp);

				tmp=temp_SSPeople->Persuaded;
				temp_SSPeople->Persuaded=adjustglobal(tmp);

				tmp=temp_SSPeople->ChildHeld;
				temp_SSPeople->ChildHeld=adjustglobal(tmp);
				tmp=temp_SSPeople->ParentHeld;
				temp_SSPeople->ParentHeld=adjustglobal(tmp);

				tmp=temp_SSPeople->Command;
				temp_SSPeople->Command=adjustglobal(tmp);
				tmp=temp_SSPeople->StartCommand;
				temp_SSPeople->StartCommand=adjustglobal(tmp);

				tmp=temp_SSPeople->Target;
				temp_SSPeople->Target=adjustglobal(tmp);
				tmp=temp_SSPeople->Data;
				temp_SSPeople->Data=adjustglobal(tmp);

				tmp=temp_SSPeople->ChildWeapon;
				temp_SSPeople->ChildWeapon=adjustglobal(tmp);
	//			tmp=temp_SSPeople->Equipment;
	//			temp_SSPeople->Equipment=adjustglobal(tmp);

	//			tmp=temp_SSPeople->ParentRank;
	//			temp_SSPeople->ParentRank=adjustglobal(tmp);
	//			tmp=temp_SSPeople->RankPosition;
	//			temp_SSPeople->RankPosition=adjustglobal(tmp);

				tmp=temp_SSPeople->WeaponHolding;
				temp_SSPeople->WeaponHolding=adjustglobal(tmp);
				break;
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
			case	WEAPON:
			{
				struct	Weapon			*temp_SSWeapons;

				temp_SSWeapons = (struct Weapon *)NEWSTRUCT(new_save_struct.SSMapwho[counter]);
				tmp=temp_SSWeapons->GWeapon.Child;
				temp_SSWeapons->GWeapon.Child=adjustglobal(tmp);
				tmp=temp_SSWeapons->GWeapon.Parent;
				temp_SSWeapons->GWeapon.Parent=adjustglobal(tmp);
				tmp=temp_SSWeapons->GWeapon.WhoShotMe;
				temp_SSWeapons->GWeapon.WhoShotMe=adjustglobal(tmp);

				tmp=temp_SSWeapons->ChildWeapon;
				temp_SSWeapons->ChildWeapon=adjustglobal(tmp);
				tmp=temp_SSWeapons->ParentWeapon;
				temp_SSWeapons->ParentWeapon=adjustglobal(tmp);
				tmp=temp_SSWeapons->WhoOwnsWeapon;
				temp_SSWeapons->WhoOwnsWeapon=adjustglobal(tmp);
				break;
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
			case	COMMAND:
			{
				struct	Command			*temp_SSCommands;

				temp_SSCommands = (struct Command *)NEWSTRUCT(new_save_struct.SSMapwho[counter]);
				tmp=temp_SSCommands->Next;
				temp_SSCommands->Next=adjustglobal(tmp);
				tmp=temp_SSCommands->Data;
				temp_SSCommands->Data=adjustglobal(tmp);
			}
		}
	}
	for(counter=0;counter<128;counter++)
	{
		tmp = new_save_struct.SSCPObjectives[counter].Child;
		new_save_struct.SSCPObjectives[counter].Child=adjustglobal(tmp);
		tmp = new_save_struct.SSCPObjectives[counter].Parent;
		new_save_struct.SSCPObjectives[counter].Parent=adjustglobal(tmp);
	}
	for(counter=0;counter<8;counter++)
	{
		tmp = new_save_struct.SSObjectives[counter].Objective;
		new_save_struct.SSObjectives[counter].Objective=adjustglobal(tmp);
		tmp = new_save_struct.SSObjectives[counter].Data;
		new_save_struct.SSObjectives[counter].Data=adjustglobal(tmp);
	}
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

void	move_mapwho(struct Global *tglobal,SWORD xpos,SWORD ypos,SWORD zpos)
{
	SWORD	wx,wy;
	struct 	Global 	*child;
	struct 	Global 	*parent;
	UWORD	*pnew;
	UWORD	*pold;
	UWORD	offset;


	wx=(xpos>>8);
	wy=(ypos>>8);

	if (wx<1)
		xpos=(MAP_XSIZE-2)*256;
	if (wy<1)
		ypos=(MAP_YSIZE-2)*256;
	if (wx>=(MAP_XSIZE-1))
		xpos=2*256;
	if (wy>=(MAP_YSIZE-1))
		ypos=2*256;

	zpos&=(4096-1);


	pnew=&_mapwho[GET_MAPWHO_OFFSET(xpos,ypos)];
	pold=&_mapwho[GET_MAPWHO_OFFSET(tglobal->Xpos,tglobal->Ypos)];
	if(pnew!=pold)
	{
		if (tglobal->Status & STATUS_MAPWHO) // if i am on the mapwho delete ans:myself off
		{
			if (tglobal->Parent)
			{
				parent=GET_GLOBAL_PTR(tglobal->Parent);
				parent->Child=tglobal->Child;
			}
			else
				*pold=tglobal->Child;
			if (tglobal->Child)
			{
				child=GET_GLOBAL_PTR(tglobal->Child);
				child->Parent=tglobal->Parent;
			}
			tglobal->Status&=(~STATUS_MAPWHO);
		}
		if (!(tglobal->Status & STATUS_MAPWHO)) // if i am not on the mapwho ans:mark it
		{
			offset=GET_MODEL_OFFSET(tglobal);
			tglobal->Parent=0;
			if(tglobal->Child=*pnew)
			{
				child=GET_GLOBAL_PTR(tglobal->Child);
				child->Parent=offset;
			}
			*pnew=offset;
			tglobal->Status|=STATUS_MAPWHO;
		}
	}

	tglobal->Xpos=xpos;
	tglobal->Ypos=ypos;
	tglobal->Zpos=zpos;
	return;
}

void	ms_remove_model(struct Global *tglobal)
{
	move_off_mapwho(tglobal);
	tglobal->Model=0;
	tglobal->Frame=0;
}

void	remove_police(void)
{

	struct 	Person 	*tperson;
	struct 	Weapon 	*tweapon;
	UWORD	count;
	UWORD	flag;

	count=0;
	flag=0;
	for(tperson=_People;tperson<(struct Person *)&_EndPeople;tperson++)
	{
		if(tperson->GPerson.Model)
		{
			if((tperson->Unique & UNIQUE_POLICE) || (tperson->Unique & UNIQUE_GUARD))
			{
				ms_remove_model((struct Global *)tperson);
			}
		}
	}

}

void	ms_empty_cars(UWORD	start,UWORD	end)
{
	UWORD	counter;
	for(counter=start;counter<=end;counter++)
	{
		if(new_save_struct.SSVehicles[counter].GVehicle.State != S_VEHICLE_TRAIN &&
			new_save_struct.SSVehicles[counter].GVehicle.State != S_VEHICLE_TRAIN_MOVING)
		{
	//		kprintf("Emptying car %d \n",counter);
			new_save_struct.SSVehicles[counter].ChildHeld=0;
			new_save_struct.SSVehicles[counter].ParentHeld=0;
			new_save_struct.SSVehicles[counter].GVehicle.Child=0;
			new_save_struct.SSVehicles[counter].GVehicle.Parent=0;
		}
	}
}

void	debug_blank_weapons(UBYTE	person_no)
{
	new_save_struct.SSPeople[person_no].GPerson.Child=0;
	new_save_struct.SSPeople[person_no].GPerson.Parent=0;
	new_save_struct.SSPeople[person_no].ChildWeapon=0;

}

void	ms_fill_cars(struct Person *tperson,struct Vehicle *tvehicle,UWORD	commands)
{
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


	tperson->GPerson.Child			=	GET_MODEL_OFFSET((struct Global *)tvehicle);
	tperson->GPerson.Parent			=	0;
	tperson->GPerson.Xpos			=	tvehicle->GVehicle.Xpos;
	tperson->GPerson.Ypos			=	tvehicle->GVehicle.Ypos;
	tperson->GPerson.Zpos			=	tvehicle->GVehicle.Zpos;
	tperson->GPerson.Status			=	5;
	tperson->GPerson.Affect			=	0;
	tperson->GPerson.BaseFrame		=	0x272;
	tperson->GPerson.Frame			=	0x1D9;
	tperson->GPerson.OldFrame		=	0x27B;
	tperson->GPerson.Life			=	0;
	tperson->GPerson.WhoShotMe		=	0;
	tperson->GPerson.Model			=	1;
	tperson->GPerson.State			=	3;
	tperson->GPerson.Angle			=	0x22;
	tperson->GPerson.ZAngle			=	0;

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


}

void	move_on_mapwho(struct Global *tglobal,UWORD xpos,UWORD ypos,UWORD zpos)
{
	UWORD   *tmapwho;
	struct 	Global 	*child;
	UWORD	offset;

	if (!(tglobal->Status & STATUS_MAPWHO))
	{
		tmapwho=&_mapwho[GET_MAPWHO_OFFSET(xpos,ypos)];
		offset=GET_MODEL_OFFSET(tglobal);
		tglobal->Parent=0;
		if(tglobal->Child=*tmapwho)
		{
			child=GET_GLOBAL_PTR(tglobal->Child);
			child->Parent=offset;
		}
		*tmapwho=offset;
		tglobal->Status|=STATUS_MAPWHO;
	}
	tglobal->Xpos=xpos;
	tglobal->Ypos=ypos;
	tglobal->Zpos=zpos;
	return;
}

void	map_patch(void)
{


#define	S_VEHICLE_TRAIN					5
#define	S_VEHICLE_TRAIN_MOVING			6
#define	S_VEHICLE_TRAIN_ON_FIRE			7
#define	S_VEHICLE_TRAIN_DESTROYED		8
#define	S_VEHICLE_CARRIAGE				9
#define	S_VEHICLE_CARRIAGE_MOVING		10
#define	S_VEHICLE_CARRIAGE_ON_FIRE		11
#define	S_VEHICLE_CARRIAGE_DESTROYED	12


		struct 	Weapon 	*tweapon;
		struct 	Vehicle *tvehicle;
		UWORD	child,parent;

		child=0;
		parent=0;



//MS TEMP
//		ms_empty_cars(0,11);


	//	kprintf("Vehicle [0] X %ld Y %ld Z %ld \n",new_save_struct.SSVehicles[0].GVehicle.Xpos,new_save_struct.SSVehicles[0].GVehicle.Ypos,new_save_struct.SSVehicles[0].GVehicle.Zpos);
	//	kprintf("Vehicle [1] X %ld Y %ld Z %ld \n",new_save_struct.SSVehicles[1].GVehicle.Xpos,new_save_struct.SSVehicles[1].GVehicle.Ypos,new_save_struct.SSVehicles[1].GVehicle.Zpos);
	//	kprintf("Vehicle [2] X %ld Y %ld Z %ld \n",new_save_struct.SSVehicles[2].GVehicle.Xpos,new_save_struct.SSVehicles[2].GVehicle.Ypos,new_save_struct.SSVehicles[2].GVehicle.Zpos);

//MS DEBUG 8/3/95

	for(tvehicle=_Vehicles;tvehicle<_EndVehicles;tvehicle++)
		{
			if(tvehicle->GVehicle.Model)
			{
				if(tvehicle->GVehicle.State)
				{
					switch(tvehicle->GVehicle.State)
					{
						case	S_VEHICLE_TRAIN:
						case	S_VEHICLE_TRAIN_MOVING:
						case	S_VEHICLE_TRAIN_ON_FIRE:
						case	S_VEHICLE_TRAIN_DESTROYED:
						//	kprintf("TRAIN ");
						//	if(tvehicle->LinkTo)
						//		kprintf("with a linkto\n");
						//	else
						//		kprintf("without a linkto\n");

					//MS DEBUG 2/3/95	Train fix
							new_save_struct.SSVehicles[1].LinkTo = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSVehicles[0]);
							new_save_struct.SSVehicles[2].LinkTo = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSVehicles[1]);
							new_save_struct.SSVehicles[3].LinkTo = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSVehicles[2]);
							new_save_struct.SSVehicles[4].LinkTo = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSVehicles[3]);
							new_save_struct.SSVehicles[5].LinkTo = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSVehicles[4]);
							new_save_struct.SSVehicles[6].LinkTo = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSVehicles[5]);

							break;
						case	S_VEHICLE_CARRIAGE:
						case	S_VEHICLE_CARRIAGE_MOVING:
						case	S_VEHICLE_CARRIAGE_ON_FIRE:
						case	S_VEHICLE_CARRIAGE_DESTROYED:
						//	kprintf("CARRIAGE ");
						//	if(tvehicle->LinkTo)
						//		kprintf("with a linkto\n");
						//	else
						//		kprintf("without a linkto\n");
							break;
					//	default:
					//		kprintf("No vehicle match\n");
					//		break;
					}
			//		kprintf("LinktoX %d LinktoY %d LinktoZ %d\n \n",tvehicle->LinkX,tvehicle->LinkY,tvehicle->LinkZ);
				}
			}
		}





	// take weapons patch

	if(new_save_struct.SSObjectives[0].Objective==OBJECTIVE_TAKE_WEAPON)
	{
		struct 	Weapon 	*tweapon;

	//	kprintf("WEAPON MISSION\n");
		tweapon=GET_WEAPON_PTR(new_save_struct.SSObjectives[0].Data);
		tweapon->GWeapon.Status |= STATUS_DRAW;
		tweapon->GWeapon.Status &=(~STATUS_DRAW);
		move_on_mapwho(GET_GLOBAL_PTR(new_save_struct.SSObjectives[0].Data),tweapon->GWeapon.Xpos,tweapon->GWeapon.Ypos,tweapon->GWeapon.Zpos);
	//	kprintf("WEAPON SET\n");
	}

	{
		UWORD	counter,person_counter,command_counter;
		struct	Vehicle *tvehicle;

		counter=0;
		person_counter=0;
		command_counter=(NO_PEOPLE*8)-(MS_MAX_ALTERABLE_CARS*2);
		for(tvehicle=_Vehicles;tvehicle<(struct Vehicle *)_EndVehicles;tvehicle++)
		{
			if(	(new_save_struct.SSVehicles[counter].GVehicle.State != S_VEHICLE_TRAIN) &&
				(new_save_struct.SSVehicles[counter].GVehicle.State != S_VEHICLE_TRAIN_MOVING) &&
				(new_save_struct.SSVehicles[counter].GVehicle.State != S_VEHICLE_CARRIAGE) &&
				(new_save_struct.SSVehicles[counter].GVehicle.State != S_VEHICLE_CARRIAGE_MOVING)
				)
			{
			//	kprintf("ALTERING CAR %d\n",counter);
				if(new_save_struct.SSVehicles[0+counter].ChildHeld)
				{
			//		kprintf("FILLING\n");
					ms_fill_cars((struct Person *)&new_save_struct.SSPeople[(256-MS_MAX_ALTERABLE_CARS)+person_counter],(struct Vehicle *)&new_save_struct.SSVehicles[0+counter],command_counter);
					command_counter+=2;
					person_counter++;
				}
				else
				{
			//		kprintf("EMPTYING\n");
					ms_empty_cars(counter,counter+1);
				}
			}
			counter++;
		}
	}



	switch(_map_number)
	{
		case	1:		// western europe
			lo_boundaryx = 69;
			lo_boundaryy = 32;
			hi_boundaryx = 152;
			hi_boundaryy = 92;
			break;
		case	2:		// Far East
			lo_boundaryx = 18;
			lo_boundaryy = 18;
			hi_boundaryx = 204;
			hi_boundaryy = 150;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			remove_police();
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[60]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[54]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[63]);
/*
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[198]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[134]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[150]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[123]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[89]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[163]);
*/
//MS DEBUG	3/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[1]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[2]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[3]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[4]);
//MS DEBUG 6/4/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[12]);


			break;
		case	3:		// mongolia
			lo_boundaryx = 18;
			lo_boundaryy = 22;
			hi_boundaryx = 186;
			hi_boundaryy = 150;
			new_save_struct.SSPeople[68].GPerson.Model=0;
			new_save_struct.SSPeople[68].GPerson.Status=0;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[1]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[2]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[3]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[4]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[5]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[6]);
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[61]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[43]);
//MS DEBUG 1/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[48]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[42]);
			break;
		case	4:		//iran
			lo_boundaryx = 30;
			lo_boundaryy = 18;
			hi_boundaryx = 183;
			hi_boundaryy = 145;
//MS DEBUG 16/3/95

			ms_remove_model((struct Global *)&new_save_struct.SSPeople[24]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[25]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[26]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[28]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[29]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[30]);
//MS DEBUG 30/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[27]);
//MS DEBUG 30/3/95
//			_mapwho[35+58*MAP_XSIZE]=0;

			break;
		case	5:		// california
			lo_boundaryx = 6;
			lo_boundaryy = 18;
			hi_boundaryx = 184;
			hi_boundaryy = 150;
			//ms_empty_cars(0,9);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[1]);
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[59]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[58]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[84]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[72]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[83]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[40]);
//MS DEBUG 1/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[84]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[72]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[83]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[40]);
//MS DEBUG 6/4/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[47]);
			break;
		case	6:		// iraq
/*
			lo_boundaryx = 18;
			lo_boundaryy = 18;
			hi_boundaryx = 204;
			hi_boundaryy = 150;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[1]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[2]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[3]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[4]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[5]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[6]);
*/

			break;
		case	7:		// india
			lo_boundaryx = 46;
			lo_boundaryy = 24;
			hi_boundaryx = 156;
			hi_boundaryy = 150;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[62]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[30]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[26]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[22]);
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[49]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[28]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[151]);
//MS DEBUG 1/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[25]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[151]);
//MS DEBUG 14/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[10]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[31]);


			break;
		case	8:		// north east territories
			lo_boundaryx = 38;
			lo_boundaryy = 19;
			hi_boundaryx = 164;
			hi_boundaryy = 159;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[25]);

			ms_remove_model((struct Global *)&new_save_struct.SSPeople[14]); // agent wi flamer
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[63]);

		//	remove_police();
			ms_empty_cars(0,9);	// rider wi no car
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[1]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[6]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[4]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[5]);
//MS DEBUG 30/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[70]);
//MS DEBUG 6/4/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[75]);

			break;
		case	10:		// east europe
			lo_boundaryx = 29;
			lo_boundaryy = 32;
			hi_boundaryx = 130;
			hi_boundaryy = 136;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[28]);
			break;
		case	11:		// Western Australia
			lo_boundaryx = 66;
			lo_boundaryy = 18;
			hi_boundaryx = 204;
			hi_boundaryy = 150;
			new_save_struct.SSCPObjectives[0].Player=0xFF;
			new_save_struct.SSCPObjectives[0].ActionType=3;
			new_save_struct.SSCPObjectives[1].Player=0xFF;
			new_save_struct.SSCPObjectives[1].ActionType=3;
			new_save_struct.SSCPObjectives[2].Player=0xFF;
			new_save_struct.SSCPObjectives[2].ActionType=3;
			new_save_struct.SSCPObjectives[3].Player=0xFF;
			new_save_struct.SSCPObjectives[3].ActionType=3;

			new_save_struct.SSVehicles[0].GVehicle.Status=4;
			new_save_struct.SSVehicles[0].GVehicle.Affect=0;
			new_save_struct.SSVehicles[0].GVehicle.BaseFrame=0;
			new_save_struct.SSVehicles[0].GVehicle.Frame=0x696;
			new_save_struct.SSVehicles[0].GVehicle.OldFrame=0x1C4;
			new_save_struct.SSVehicles[0].GVehicle.Model=2;
			new_save_struct.SSVehicles[0].GVehicle.State=0xD;
			new_save_struct.SSVehicles[0].GVehicle.Angle=0xC0;


			remove_police();

			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[3]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[238]);

//MS DEBUG - Agent 1 being repositioned too far off map ..
/*
			new_save_struct.SSPeople[0].GPerson.Parent=0;
			new_save_struct.SSPeople[0].GPerson.Child=0;
			new_save_struct.SSPeople[0].GPerson.Xpos=new_save_struct.SSPeople[1].GPerson.Xpos;
			new_save_struct.SSPeople[0].GPerson.Ypos=new_save_struct.SSPeople[1].GPerson.Ypos+100;
			new_save_struct.SSPeople[0].GPerson.Zpos=new_save_struct.SSPeople[1].GPerson.Zpos;
			move_mapwho((struct Global *)&new_save_struct.SSPeople[0],new_save_struct.SSPeople[0].GPerson.Xpos,new_save_struct.SSPeople[0].GPerson.Ypos,new_save_struct.SSPeople[0].GPerson.Zpos);
			move_weapons();
*/
			new_save_struct.SSPeople[3].GPerson.Parent=0;
			new_save_struct.SSPeople[3].GPerson.Child=0;
			new_save_struct.SSPeople[3].GPerson.Ypos-=1200;
			new_save_struct.SSPeople[2].GPerson.Parent=0;
			new_save_struct.SSPeople[2].GPerson.Child=0;
			new_save_struct.SSPeople[2].GPerson.Ypos-=800;
			new_save_struct.SSPeople[0].GPerson.Parent=0;
			new_save_struct.SSPeople[0].GPerson.Child=0;
			new_save_struct.SSPeople[0].GPerson.Xpos=new_save_struct.SSPeople[1].GPerson.Xpos;
			new_save_struct.SSPeople[0].GPerson.Ypos=new_save_struct.SSPeople[1].GPerson.Ypos;
			new_save_struct.SSPeople[0].GPerson.Zpos=new_save_struct.SSPeople[1].GPerson.Zpos;
			new_save_struct.SSPeople[1].GPerson.Parent=0;
			new_save_struct.SSPeople[1].GPerson.Child=0;
			new_save_struct.SSPeople[1].GPerson.Ypos-=400;
			move_mapwho((struct Global *)&new_save_struct.SSPeople[0],new_save_struct.SSPeople[0].GPerson.Xpos,new_save_struct.SSPeople[0].GPerson.Ypos,new_save_struct.SSPeople[0].GPerson.Zpos);
			move_mapwho((struct Global *)&new_save_struct.SSPeople[1],new_save_struct.SSPeople[1].GPerson.Xpos,new_save_struct.SSPeople[1].GPerson.Ypos,new_save_struct.SSPeople[1].GPerson.Zpos);
			move_mapwho((struct Global *)&new_save_struct.SSPeople[2],new_save_struct.SSPeople[2].GPerson.Xpos,new_save_struct.SSPeople[2].GPerson.Ypos,new_save_struct.SSPeople[2].GPerson.Zpos);
			move_mapwho((struct Global *)&new_save_struct.SSPeople[3],new_save_struct.SSPeople[3].GPerson.Xpos,new_save_struct.SSPeople[3].GPerson.Ypos,new_save_struct.SSPeople[3].GPerson.Zpos);

			//move_weapons();


//MS DEBUG - Agent 3 adren level drops
			new_save_struct.SSPeople[2].Level1Base=new_save_struct.SSPeople[1].Level1Base;
			new_save_struct.SSPeople[2].Level1Balance=new_save_struct.SSPeople[1].Level1Balance;
			new_save_struct.SSPeople[2].Level1True=new_save_struct.SSPeople[1].Level1True;
			new_save_struct.SSPeople[2].Level1Fixed=new_save_struct.SSPeople[1].Level1Fixed;


			break;
		case	12:		// kamchatka
			lo_boundaryx = 18;
			lo_boundaryy = 22;
			hi_boundaryx = 144;
			hi_boundaryy = 152;
			break;

		case	13:		// mozambique
			lo_boundaryx = 60;
			lo_boundaryy = 22;
			hi_boundaryx = 114;
			hi_boundaryy = 150;
	//		new_save_struct.SSWeapons[0].GWeapon.Child=0;
	//		new_save_struct.SSWeapons[0].GWeapon.Parent=0;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[26]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[10]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[12]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[27]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[20]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[19]);

			//MOZAMBIQUE TARGET WEAPON = Xpos 14484 Ypos 3436 Zpos 1024

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

			new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Status&=~STATUS_MAPWHO;
			move_on_mapwho((struct Global *)&new_save_struct.SSWeapons[NO_WEAPONS-1],new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Xpos,new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Ypos,new_save_struct.SSWeapons[NO_WEAPONS-1].GWeapon.Zpos);

			new_save_struct.SSObjectives[0].Data = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSWeapons[NO_WEAPONS-1]);

	//		move_off_mapwho((struct Global *)&new_save_struct.SSWeapons[32]);
	//		move_off_mapwho((struct Global *)&new_save_struct.SSWeapons[13]);
/*
			{
				struct	Weapon	*tweapon;

				tweapon = GET_WEAPON_PTR(new_save_struct.SSObjectives[0].Data);
				kprintf("MOZAMBIQUE TARGET WEAPON = ");
				kprintf("Xpos %ld Ypos %ld Zpos %ld \n",tweapon->GWeapon.Xpos,tweapon->GWeapon.Ypos,tweapon->GWeapon.Zpos);
			}
*/

//MS DEBUG 2/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[13]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[14]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[39]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[47]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[48]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[49]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[50]);
//MS DEBUG 16/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[42]);
//MS DEBUG 29/3/95
			debug_blank_weapons(29);
			debug_blank_weapons(30);
//MS DEBUG 31/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[51]);
			break;
		case	18:		// central europe
			lo_boundaryx = 66;
			lo_boundaryy = 18;
			hi_boundaryx = 163;
			hi_boundaryy = 133;
			//ms_empty_cars(0,4);
			break;
		case	19:		// greenland
			lo_boundaryx = 39;
			lo_boundaryy = 18;
			hi_boundaryx = 166;
			hi_boundaryy = 131;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[53]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[43]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[44]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[45]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[47]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[46]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[51]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[65]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[42]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[57]);
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[56]);
			ms_empty_cars(0,3);
//MS DEBUG 2/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[1]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[2]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[3]);
//MS DEBUG 13/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[63]);
			new_save_struct.SSPeople[66].GPerson.Life=-16;
			new_save_struct.SSPeople[66].GPerson.Status|=(STATUS_CONTROL | STATUS_DEAD);

//MS DEBUG 13/3/95 - stop people in car at end
			new_save_struct.SSVehicles[1].GVehicle.Status|=(STATUS_CONTROL | STATUS_DEAD);
			new_save_struct.SSVehicles[2].GVehicle.Status|=(STATUS_CONTROL | STATUS_DEAD);
			new_save_struct.SSVehicles[3].GVehicle.Status|=(STATUS_CONTROL | STATUS_DEAD);
			new_save_struct.SSPeople[69].GPerson.Life=-16;
			new_save_struct.SSPeople[69].GPerson.Status|=(STATUS_CONTROL | STATUS_DEAD);
			new_save_struct.SSPeople[75].GPerson.Life=-16;
			new_save_struct.SSPeople[75].GPerson.Status|=(STATUS_CONTROL | STATUS_DEAD);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[69]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[75]);
			break;
		case	20:		// peru
			lo_boundaryx = 18;
			lo_boundaryy = 30;
			hi_boundaryx = 186;
			hi_boundaryy = 127;
			new_save_struct.SSPeople[8].GPerson.BaseFrame=0;
			new_save_struct.SSPeople[8].GPerson.Frame=0;
			new_save_struct.SSPeople[8].GPerson.OldFrame=0;


			//ms_empty_cars(7,8);
			new_save_struct.SSVehicles[8].GVehicle.Xpos=8440;
			new_save_struct.SSVehicles[8].GVehicle.Ypos=18624;
			new_save_struct.SSVehicles[8].GVehicle.Zpos=768;
			new_save_struct.SSVehicles[8].GVehicle.Status=4;
			new_save_struct.SSVehicles[8].GVehicle.Affect=0;
			new_save_struct.SSVehicles[8].GVehicle.BaseFrame=0;
			new_save_struct.SSVehicles[8].GVehicle.Frame=0x696;
			new_save_struct.SSVehicles[8].GVehicle.OldFrame=0x1C4;
			new_save_struct.SSVehicles[8].GVehicle.Model=2;
			new_save_struct.SSVehicles[8].GVehicle.State=0xD;
			new_save_struct.SSVehicles[8].GVehicle.Angle=0xC0;
			new_save_struct.SSVehicles[8].GVehicle.ZAngle=0;
			//ms_empty_cars(9,11);

//MS DEBUG 13/3/95
			new_save_struct.SSPeople[9].GPerson.Zpos-=50;
			move_mapwho((struct Global *)&new_save_struct.SSPeople[9],new_save_struct.SSPeople[9].GPerson.Xpos,new_save_struct.SSPeople[9].GPerson.Ypos,new_save_struct.SSPeople[9].GPerson.Zpos);
//MS DEBUG 29/3/95
			debug_blank_weapons(65);
/*
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[22]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[47]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[65]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[69]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[70]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[76]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[94]);
*/
			{
				UBYTE	counter;

				for(counter=0;counter<8;counter++)
				{
					new_save_struct.SSVehicles[counter].GVehicle.Child=0;
					new_save_struct.SSVehicles[counter].GVehicle.Parent=0;
				}
			}
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[75]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[81]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[97]);

			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[11]);

			break;
		case	31:		// venezuela
			lo_boundaryx = 0;
			lo_boundaryy = 18;
			hi_boundaryx = 204;
			hi_boundaryy = 158;
			break;
		case	32:		// scandinavia
			lo_boundaryx = 40;
			lo_boundaryy = 50;
			hi_boundaryx = 142;
			hi_boundaryy = 129;
			break;
		case	34:		// northern territories
			lo_boundaryx = 16;
			lo_boundaryy = 30;
			hi_boundaryx = 183;
			hi_boundaryy = 117;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[29]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[38]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[35]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[125]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[55]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[54]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[32]);  // agent as door
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[43]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[44]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[64]);
//MS DEBUG 1/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[36]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[61]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[48]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[62]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[60]);
//MS DEBUG 16/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[65]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[63]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[66]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[20]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[55]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[18]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[19]);
			break;
		case	35:		// alaska
			lo_boundaryx = 67;
			lo_boundaryy = 47;
			hi_boundaryx = 174;
			hi_boundaryy = 121;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[8]);
			new_save_struct.SSVehicles[2].GVehicle.Status=4;
			new_save_struct.SSVehicles[2].GVehicle.Affect=0;
			new_save_struct.SSVehicles[2].GVehicle.BaseFrame=0;
			new_save_struct.SSVehicles[2].GVehicle.Frame=0x693;
			new_save_struct.SSVehicles[2].GVehicle.OldFrame=0x1BE;
			new_save_struct.SSVehicles[2].GVehicle.Model=2;
			new_save_struct.SSVehicles[2].GVehicle.State=0xD;
			new_save_struct.SSVehicles[2].GVehicle.Angle=0x80;
			new_save_struct.SSVehicles[3].GVehicle.Status=4;
			new_save_struct.SSVehicles[3].GVehicle.Affect=0;
			new_save_struct.SSVehicles[3].GVehicle.BaseFrame=0;
			new_save_struct.SSVehicles[3].GVehicle.Frame=0x693;
			new_save_struct.SSVehicles[3].GVehicle.OldFrame=0x1BE;
			new_save_struct.SSVehicles[3].GVehicle.Model=2;
			new_save_struct.SSVehicles[3].GVehicle.State=0xD;
			new_save_struct.SSVehicles[3].GVehicle.Angle=0x80;
			break;
		case	38:		// urals
			lo_boundaryx = 50;
			lo_boundaryy = 32;
			hi_boundaryx = 186;
			hi_boundaryy = 139;
			new_save_struct.SSCPObjectives[0].Player=0xFF;
			new_save_struct.SSCPObjectives[0].ActionType=3;
			break;
		case	39:		// yukon
			lo_boundaryx = 42;
			lo_boundaryy = 29;
			hi_boundaryx = 155;
			hi_boundaryy = 139;
//MS DEBUG 31/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[80]);  // agent as door
			break;
		case	40:		// new england
			lo_boundaryx = 23;
			lo_boundaryy = 19;
			hi_boundaryx = 147;
			hi_boundaryy = 157;
			break;
		case	41:		// siberia
			lo_boundaryx = 18;
			lo_boundaryy = 22;
			hi_boundaryx = 184;
			hi_boundaryy = 150;
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[83]);  // agent as door
		//	new_save_struct.SSPeople[24].GPerson.Model=0;

/*
			{
				UBYTE	train;

				for(train=0;train<7;train++)
				{
					ms_remove_model((struct Global *)&new_save_struct.SSVehicles[train]);
				}
			}
*/

			ms_remove_model((struct Global *)&new_save_struct.SSPeople[122]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[154]);
/*
			// train waiting ?
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[24]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[25]);
*/
//MS DEBUG 14/3/95
			new_save_struct.SSPeople[24].GPerson.Child=0;
			new_save_struct.SSPeople[25].GPerson.Child=0;
			new_save_struct.SSVehicles[1].GVehicle.Child=0;


			ms_remove_model((struct Global *)&new_save_struct.SSObjects[37]);

			// give PERSON MATCH - SSPEOPLE[ 170 ] a minigun to please E.A.
			//new_save_struct.SSPeople[170].ChildWeapon=0;
			//init_a_players_weapon((struct Person *)&new_save_struct.SSPeople[170],S_WEAPON_MINI_GUN,GET_WEAPONS_AMMO(S_WEAPON_MINI_GUN));

			{
				struct	Global tglobal;

				tglobal = new_save_struct.SSVehicles[6].GVehicle;
				new_save_struct.SSVehicles[6] = new_save_struct.SSVehicles[5];

				new_save_struct.SSVehicles[6].LinkTo = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSVehicles[5]);
		//		new_save_struct.SSVehicles[6].LinkX = 0;
		//		new_save_struct.SSVehicles[6].LinkY = 0;
		//		new_save_struct.SSVehicles[6].LinkZ = 0;

				new_save_struct.SSVehicles[6].GVehicle.Ypos = new_save_struct.SSVehicles[5].GVehicle.Ypos - (new_save_struct.SSVehicles[4].GVehicle.Ypos - new_save_struct.SSVehicles[5].GVehicle.Ypos);

				new_save_struct.SSVehicles[6].GVehicle.Child=0;
				new_save_struct.SSVehicles[6].GVehicle.Parent=0;
				new_save_struct.SSVehicles[6].GVehicle.Status = 4;
				new_save_struct.SSVehicles[6].GVehicle.BaseFrame = 0;
				new_save_struct.SSVehicles[6].GVehicle.Frame = 0;
				new_save_struct.SSVehicles[6].GVehicle.OldFrame = 0;
				new_save_struct.SSVehicles[6].GVehicle.Life = 100;
				new_save_struct.SSVehicles[6].GVehicle.Model = 2;
				new_save_struct.SSVehicles[6].GVehicle.State = 5;
				new_save_struct.SSVehicles[6].GVehicle.Angle = tglobal.Angle;
				new_save_struct.SSVehicles[6].GVehicle.ZAngle = tglobal.ZAngle;
			}
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[6]);

			break;
		case	43:		//	libya
			lo_boundaryx = 20;
			lo_boundaryy = 19;
			hi_boundaryx = 185;
			hi_boundaryy = 150;

			{
				UBYTE	train;

				for(train=0;train<7;train++)
				{
					ms_remove_model((struct Global *)&new_save_struct.SSVehicles[train]);
				}
			}


			break;
		case	50:	//uraguay
			lo_boundaryx = 13;
			lo_boundaryy = 18;
			hi_boundaryx = 204;
			hi_boundaryy = 161;
		//	ms_remove_model((struct Global *)&new_save_struct.SSVehicles[1]);
		//	ms_remove_model((struct Global *)&new_save_struct.SSVehicles[2]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[49]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[74]);

			new_save_struct.SSVehicles[1].GVehicle.Status=4;
			new_save_struct.SSVehicles[1].GVehicle.Affect=0;
			new_save_struct.SSVehicles[1].GVehicle.BaseFrame=0;
			new_save_struct.SSVehicles[1].GVehicle.Frame=0x693;
			new_save_struct.SSVehicles[1].GVehicle.OldFrame=0x1BE;
			new_save_struct.SSVehicles[1].GVehicle.Model=2;
			new_save_struct.SSVehicles[1].GVehicle.State=0xD;
			new_save_struct.SSVehicles[1].GVehicle.Angle=0;
			new_save_struct.SSVehicles[2].GVehicle.Status=4;
			new_save_struct.SSVehicles[2].GVehicle.Affect=0;
			new_save_struct.SSVehicles[2].GVehicle.BaseFrame=0;
			new_save_struct.SSVehicles[2].GVehicle.Frame=0x693;
			new_save_struct.SSVehicles[2].GVehicle.OldFrame=0x1BE;
			new_save_struct.SSVehicles[2].GVehicle.Model=2;
			new_save_struct.SSVehicles[2].GVehicle.State=0xD;
			new_save_struct.SSVehicles[2].GVehicle.Angle=0;

			break;
		case	51:					// Pacific Rim
			lo_boundaryx = 2;
			lo_boundaryy = 25;
			hi_boundaryx = 201;
			hi_boundaryy = 127;
//			ms_empty_cars(0,10);
//			{
//				UBYTE	counter;
//
//				for(counter=0;counter<10;counter++)
//				{
//					ms_remove_model((struct Global *)&new_save_struct.SSVehicles[counter]);
//				}
//			}
			remove_police();

			// Get rid of flashing agent in evac area
/*
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[1]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[59]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[153]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[154]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[169]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[170]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[176]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[177]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[178]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[179]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[180]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[182]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[186]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[192]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[240]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[274]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[275]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[276]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[287]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[288]);
*/
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[175]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[167]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[184]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[188]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[242]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[177]);

			ms_remove_model((struct Global *)&new_save_struct.SSObjects[24]);
//MS DEBUG 30/3/95
			_mapwho[72+65*MAP_XSIZE]=0;
//MS DEBUG 6/4/95
			_mapwho[71+76*MAP_XSIZE]=0;
			_mapwho[56+61*MAP_XSIZE]=0;

			break;
		case	53:		//paraguay
			lo_boundaryx = 2;
			lo_boundaryy = 18;
			hi_boundaryx = 204;
			hi_boundaryy = 106;
//MS DEBUG 4/4/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[59]);
			break;
		case	54:			// china
			lo_boundaryx = 37;
			lo_boundaryy = 34;
			hi_boundaryx = 200;
			hi_boundaryy = 158;
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[60]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[68]);
//MS DEBUG 5/4/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[73]);
			break;
		case	56:			// atlantic accel
			lo_boundaryx = 23;
			lo_boundaryy = 20;
			hi_boundaryx = 176;
			hi_boundaryy = 115;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[65]);
			break;
		case	57:			// arabia
			hi_boundaryx = 204;
			hi_boundaryy = 150;

			remove_police();

			break;
		case	58:		// north west territories
		//	lo_boundaryx = 39;
			lo_boundaryx = 4;
			lo_boundaryy = 18;
			hi_boundaryx = 204;
			hi_boundaryy = 159;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
//MS DEBUG 13/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[14]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[139]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[140]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[148]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[149]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[153]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[157]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[158]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[164]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[165]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[247]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[251]);
			break;
		case	60:		// colorado
			lo_boundaryx = 6;
			lo_boundaryy = 26;
			hi_boundaryx = 204;
			hi_boundaryy = 150;
		//	ms_remove_model((struct Global *)&new_save_struct.SSVehicles[1]);
		//	ms_remove_model((struct Global *)&new_save_struct.SSVehicles[2]);
		//	ms_remove_model((struct Global *)&new_save_struct.SSVehicles[3]);
			new_save_struct.SSObjectives[0].Data = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSPeople[62]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[82]);
//MS DEBUG 1/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[30]);
//MS DEBUG 10/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[162]);
//MS DEBUG 16/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[212]);
			ms_empty_cars(0,7);
//MS DEBUG 21/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);

	//		ms_remove_model((struct Global *)&new_save_struct.SSVehicles[1]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[2]);
	//		ms_remove_model((struct Global *)&new_save_struct.SSVehicles[3]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[4]);

			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[5]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[6]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[7]);

			break;
		case	61:		// sudan
			lo_boundaryx = 59;
			lo_boundaryy = 20;
			hi_boundaryx = 204;
			hi_boundaryy = 150;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[169]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[187]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[44]);
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[36]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[38]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[64]);
//MS DEBUG 1/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[48]);
//MS DEBUG 13/3/95
			remove_police();
//MS DEBUG 13/3/95
			new_save_struct.SSObjectives[1].Data = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSPeople[154]);
//MS DEBUG 30/3/95
			_mapwho[45+52*MAP_XSIZE]=0;
			break;
		case	62:		// Mid West
			lo_boundaryx = 23;
			lo_boundaryy = 19;
			hi_boundaryx = 204;
			hi_boundaryy = 150;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[45]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[54]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[59]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[85]);
			break;
		case	63:		// kazakstan	& kenya
			lo_boundaryx = 16;
			lo_boundaryy = 30;
			hi_boundaryx = 179;
			hi_boundaryy = 150;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			new_save_struct.SSCPObjectives[0].Player=0xFF;
			new_save_struct.SSCPObjectives[0].ActionType=3;
			new_save_struct.SSCPObjectives[1].Player=0xFF;
			new_save_struct.SSCPObjectives[1].ActionType=3;
			new_save_struct.SSCPObjectives[2].Player=0xFF;
			new_save_struct.SSCPObjectives[2].ActionType=3;
			new_save_struct.SSCPObjectives[3].Player=0xFF;
			new_save_struct.SSCPObjectives[3].ActionType=3;
			new_save_struct.SSCPObjectives[4].Player=0xFF;
			new_save_struct.SSCPObjectives[4].ActionType=3;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[45]);

//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[59]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[54]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[47]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[83]);
//MS DEBUG 1/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[75]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[68]);
//MS DEBUG 2/3/95
			remove_police();

			break;
		case	64:		// Mauritania
			lo_boundaryx = 34;
			lo_boundaryy = 19;
			hi_boundaryx = 204;
			hi_boundaryy = 166;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[5]);
		//	ms_remove_model((struct Global *)&new_save_struct.SSPeople[22]);
//MS DEBUG 10/3/95
		//	ms_remove_model((struct Global *)&new_save_struct.SSPeople[33]);
//MS DEBUG 13/3/95	- fix bug 143, object is not a woman
			new_save_struct.SSObjectives[0].Data = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSPeople[98]);
//MS DEBUG 13/3/95
		//	ms_remove_model((struct Global *)&new_save_struct.SSPeople[30]);
		//	ms_remove_model((struct Global *)&new_save_struct.SSPeople[32]);
			{
				struct	Person	tperson1;
				struct	Person	tperson2;

				tperson1 = new_save_struct.SSPeople[30];
				tperson2 = new_save_struct.SSPeople[32];
				remove_police();
				new_save_struct.SSPeople[30] = tperson1;
				new_save_struct.SSPeople[32] = tperson2;

				move_on_mapwho((struct Global *)&new_save_struct.SSPeople[30],new_save_struct.SSPeople[30].GPerson.Xpos,new_save_struct.SSPeople[30].GPerson.Ypos,new_save_struct.SSPeople[30].GPerson.Zpos);
				move_on_mapwho((struct Global *)&new_save_struct.SSPeople[32],new_save_struct.SSPeople[32].GPerson.Xpos,new_save_struct.SSPeople[32].GPerson.Ypos,new_save_struct.SSPeople[32].GPerson.Zpos);
			}

			break;
		case	65:		// new s wales
			lo_boundaryx = 11;
			lo_boundaryy = 19;
			hi_boundaryx = 202;
			hi_boundaryy = 155;
	//		ms_empty_cars(1,6);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[4]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[252]);
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[199]);
//MS DEBUG 7/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[63]);
			ms_remove_model((struct Global *)&new_save_struct.SSObjects[34]);

/*
			{
				UWORD	counter;

				for(counter=0;counter<7;counter++)
				{
					if(new_save_struct.SSVehicles[0+counter].ChildHeld)
						ms_fill_cars((struct Person *)&new_save_struct.SSPeople[250+counter],(struct Vehicle *)&new_save_struct.SSVehicles[0+counter]);
					else
						ms_empty_cars(counter,counter+1);
				}
			}
*/
//MS DEBUG 31/3/95 - rogue policeman
		//	_mapwho[14+85*MAP_XSIZE]=0;
			debug_blank_weapons(158);
			break;
		case	66:		// newfoundland
			lo_boundaryx = 20;
			lo_boundaryy = 23;
			hi_boundaryx = 196;
			hi_boundaryy = 141;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			break;
		case	67:		// argentina
			lo_boundaryx = 1;
			lo_boundaryy = 18;
			hi_boundaryx = 204;
			hi_boundaryy = 162;
			break;
		case	70:		//southern states
			lo_boundaryx = 23;
			lo_boundaryy = 20;
			hi_boundaryx = 189;
			hi_boundaryy = 160;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[30]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[157]);
#ifdef foo
			if(iraq_debug)
			{
				move_off_mapwho((struct Global *)&new_save_struct.SSPeople[0]);
				move_off_mapwho((struct Global *)&new_save_struct.SSPeople[1]);
				move_off_mapwho((struct Global *)&new_save_struct.SSPeople[2]);
				move_off_mapwho((struct Global *)&new_save_struct.SSPeople[3]);
				new_save_struct.SSPeople[0].GPerson.Ypos+=0x10000;
				new_save_struct.SSPeople[1].GPerson.Ypos+=0x10000;
				new_save_struct.SSPeople[2].GPerson.Ypos+=0x10000;
				new_save_struct.SSPeople[3].GPerson.Ypos+=0x10000;
				move_on_mapwho((struct Global *)&new_save_struct.SSPeople[0],new_save_struct.SSPeople[0].GPerson.Xpos,new_save_struct.SSPeople[0].GPerson.Ypos,new_save_struct.SSPeople[0].GPerson.Zpos);
				move_on_mapwho((struct Global *)&new_save_struct.SSPeople[1],new_save_struct.SSPeople[1].GPerson.Xpos,new_save_struct.SSPeople[1].GPerson.Ypos,new_save_struct.SSPeople[1].GPerson.Zpos);
				move_on_mapwho((struct Global *)&new_save_struct.SSPeople[2],new_save_struct.SSPeople[2].GPerson.Xpos,new_save_struct.SSPeople[2].GPerson.Ypos,new_save_struct.SSPeople[2].GPerson.Zpos);
				move_on_mapwho((struct Global *)&new_save_struct.SSPeople[3],new_save_struct.SSPeople[3].GPerson.Xpos,new_save_struct.SSPeople[3].GPerson.Ypos,new_save_struct.SSPeople[3].GPerson.Zpos);

				new_save_struct.SSObjectives[0].Data = GET_MODEL_OFFSET((struct Global *)&new_save_struct.SSPeople[160]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[24]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[74]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[80]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[73]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[71]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[77]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[76]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[70]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[31]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[75]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[25]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[78]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[26]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[79]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[27]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[50]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[39]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[64]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[35]);
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[54]);
//MS DEBUG 1/3/95
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[37]);
			//	remove_police();
			}
			else
#endif
			{
	//MS DEBUG 28/2/95
				ms_remove_model((struct Global *)&new_save_struct.SSPeople[49]);
			}

			break;
		case	71:		// zaire
			lo_boundaryx = 4;
			lo_boundaryy = 26;
			hi_boundaryx = 179;
			hi_boundaryy = 150;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[99]);
//MS DEBUG 29/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[29]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[30]);
			break;
		case	72:		//algeria
			lo_boundaryx = 7;
			lo_boundaryy = 19;
			hi_boundaryx = 204;
			hi_boundaryy = 150;
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[58]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[65]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[59]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[88]);
//MS DEBUG 5/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[55]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[61]);
			break;
		case	80:		// columbia
			lo_boundaryx = 1;
			lo_boundaryy = 18;
			hi_boundaryx = 203;
			hi_boundaryy = 158;
			ms_empty_cars(0,8);

			ms_remove_model((struct Global *)&new_save_struct.SSPeople[193]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[192]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[214]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[228]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[200]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[225]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[217]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[219]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[230]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[127]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[203]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[212]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[208]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[202]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[32]);

			ms_remove_model((struct Global *)&new_save_struct.SSPeople[130]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[201]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[202]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[208]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[32]);

			ms_remove_model((struct Global *)&new_save_struct.SSPeople[194]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[196]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[210]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[229]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[216]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[218]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[211]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[222]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[226]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[215]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[66]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[221]);

			ms_remove_model((struct Global *)&new_save_struct.SSPeople[204]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[207]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[205]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[198]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[197]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[223]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[206]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[199]);



			remove_police();


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

//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[209]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[224]);
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[227]);
//MS DEBUG 6/4/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[19]);
			break;
		case	81:		// nigeria
			lo_boundaryx = 23;
			lo_boundaryy = 20;
			hi_boundaryx = 204;
			hi_boundaryy = 150;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[45]);
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
			//ms_empty_cars(0,7);

//			ms_remove_model((struct Global *)&new_save_struct.SSPeople[35]);
//			ms_remove_model((struct Global *)&new_save_struct.SSPeople[136]);

//MS DEBUG 28/3/95
//			{
//				UWORD	*tmapwho;
//
//				tmapwho=&_mapwho[GET_MAPWHO_OFFSET(new_save_struct.SSPeople[0].GPerson.Xpos,new_save_struct.SSPeople[0].GPerson.Ypos)];
//				*tmapwho=0;
//
				new_save_struct.SSPeople[0].GPerson.Child=0;
				new_save_struct.SSPeople[0].GPerson.Parent=new_save_struct.SSPeople[0].ChildWeapon;
				new_save_struct.SSPeople[0].GPerson.Ypos -= 500;
				move_mapwho((struct Global *)&new_save_struct.SSPeople[0],new_save_struct.SSPeople[0].GPerson.Xpos,new_save_struct.SSPeople[0].GPerson.Ypos,new_save_struct.SSPeople[0].GPerson.Zpos);

				move_off_mapwho((struct Global *)&new_save_struct.SSWeapons[70]);
				move_off_mapwho((struct Global *)&new_save_struct.SSPeople[102]);
				move_off_mapwho((struct Global *)&new_save_struct.SSPeople[35]);

//			}
			break;
		case	82:		// brazil
			lo_boundaryx = 1;
			lo_boundaryy = 19;
			hi_boundaryx = 199;
			hi_boundaryy = 150;
//MS DEBUG 28/2/95
			remove_police();
//MS DEBUG 31/3/95
			_mapwho[34+14*MAP_XSIZE]=0;		// agent echo
			_mapwho[36+14*MAP_XSIZE]=0;		// weapon echo
			break;
		case	90:		// Rockies
			lo_boundaryx = 4;
			lo_boundaryy = 30;
			hi_boundaryx = 204;
			hi_boundaryy = 157;
			new_save_struct.SSPeople[61].ParentHeld=0;
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[8]);
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[38]);
//MS DEBUG 16/3/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[54]);
			break;
		case	91:			// indonesia
			lo_boundaryx -= 8;
			hi_boundaryx = 204;
			hi_boundaryy = 150;
//MS DEBUG 28/2/95
			ms_remove_model((struct Global *)&new_save_struct.SSPeople[59]);
			break;
		case	92:			// mexico
			lo_boundaryx = 0;
			lo_boundaryy = 18;
			hi_boundaryx = 191;
			hi_boundaryy = 161;
			ms_remove_model((struct Global *)&new_save_struct.SSVehicles[0]);
//			ms_lo_mapwho = (_mapwho+2*128);
			break;
		case	93:		// south africa
			lo_boundaryx = 16;
		//	lo_boundaryy = 30;
			lo_boundaryy = 18;
		//	hi_boundaryx = 204;
			hi_boundaryx = 200;
			hi_boundaryy = 160;

//			Cover_Person_X1 = -10;
//			Cover_Person_Y1 = -42;

//			ms_remove_model((struct Global *)&new_save_struct.SSPeople[26]);

			new_save_struct.SSVehicles[0].GVehicle.Status=4;
			new_save_struct.SSVehicles[0].GVehicle.Affect=0;
			new_save_struct.SSVehicles[0].GVehicle.BaseFrame=0;
			new_save_struct.SSVehicles[0].GVehicle.Frame=0x693;
			new_save_struct.SSVehicles[0].GVehicle.OldFrame=0x1BE;
			new_save_struct.SSVehicles[0].GVehicle.Model=2;
			new_save_struct.SSVehicles[0].GVehicle.State=0xD;
			new_save_struct.SSVehicles[0].GVehicle.Angle=0;
			ms_empty_cars(1,3);
			break;
		default:
			hi_boundaryx = 204;
			hi_boundaryy = 150;
			break;
	}
}



main(int argc, char *argv[])
{
	FILE	*handle;

	if (argc < 3)
	{
		printf("Usage: rgame <oldfile> <newfile>\n");
		return;
	}

	if (!(handle = fopen(argv[1], "rb")))
	{
		printf("Can't open %s!\n", argv[1]);
		return;
	}
	fread(&save_struct.SSSeed, sizeof(struct SaveStruct)-offsetof(struct SaveStruct, SSSeed), 1, handle);
	fclose(handle);

	copyStuff();
	adjustMapWho();
	adjustEverything();

	map_patch();

	if (handle = fopen(argv[2], "wb"))
	{
		fwrite(&new_save_struct.SSSeed, sizeof(struct NewSaveStruct)-offsetof(struct NewSaveStruct, SSSeed), 1, handle);
		fclose(handle);
		puts("Done");
	}
}
