#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wtypes.h>

#include "bulcommn.h"
#include "keycodes.h"

// Data types
//map size is [128][96][12]

typedef struct {
        unsigned char unkn10[8];
       } LEVELDATA_UNKN01;

typedef struct {
        unsigned char unkn10[256];
       } LEVELDATA_UNKN02;

//This structure contains all people in the game, including agents
//This struct size is 92.
typedef struct {
        unsigned char unkn2[4];
        unsigned char mapposx[2];
        unsigned char mapposy[2];
        unsigned char mapposz[2];
        unsigned char unkn3;//this bit may be connected with minimap in bottom left
        unsigned char unkn4;//this bit is connected with control
        unsigned char unkn5[2];//nothing changes when this changes
        unsigned char vistype[2];//visual object type;must correspond to right type
        unsigned char currvistype[2];//actual character picture; game changes this automaticaly after any command
        unsigned char unkn6;//shoot distance? if this is large, computer just follows me and won't shoot until I come closer
        unsigned char unkn7[6];//??
        unsigned char objtype;//object type on minimap and for computer?; 1-human, 2-car
        unsigned char unkn8[4];//??
        unsigned char unkn9[8];//somewhere here is written to who the agent belongs
        unsigned char unkn10[4];
        unsigned char unkn11[4];
        //Half of structure - 46 bytes
        unsigned char unkn12[12];
        unsigned char unkn13[13];
        //IPA levels: white bar level,set level,exhaused level and forced level
        unsigned char adrenalevels[4];
        unsigned char intelilevels[4];
        unsigned char perceplevels[4];
        unsigned char unkn14;//This value is different for most objects
        unsigned char unkn101[8];//??
       } LEVELDATA_UNKN03;

//This structure contains all cars in the game, including destroyed
//This struct size is 42.
typedef struct {
        unsigned char unkn2[4];
        unsigned char mapposx[2];
        unsigned char mapposy[2];
        unsigned char mapposz[2];
        unsigned char unkn3;//if not set to 4, there is no car
        unsigned char unkn4[5];//somewhere here is damage made to car (filled with 122, one shot destroys car)
        unsigned char currvistype;//actual car picture; changed automatically when car is moving
        unsigned char unkn6;//car is not exist when not set to 6
        unsigned char unkn7[3];//???
        //Half of structure - 21 bytes
        unsigned char unkn8[3];//usually zeroes
        unsigned char status;//Car status;2-can enter into car
        unsigned char type;//Car type;13-standard
        unsigned char unkn10[4];//direction the car is turned; setting all to 122 makes you die when exiting car (?)
        unsigned char unkn11[2];//??
        unsigned char unkn12[2];//if both set to 122, there is no car
        unsigned char unkn16[6];//usually zeroes
        unsigned char speed;//changing this to 0 make car unable to move. The bigger, the faster car is.
        unsigned char unkn20;//??
       } LEVELDATA_UNKN04;

typedef struct {
        unsigned char unkn10[30];
       } LEVELDATA_UNKN05;

typedef struct {
        unsigned char unkn10[36];
       } LEVELDATA_UNKN06;

typedef struct {
        unsigned char unkn10[12];
       } LEVELDATA_UNKN07;

typedef struct {
        unsigned char unkn10[8];
       } LEVELDATA_UNKN08;

typedef struct {
        unsigned char unkn10[437];
       } LEVELDATA_UNKN09;

typedef struct {
        unsigned char unkn10[14];
       } LEVELDATA_UNKN10;
//Agents table?
typedef struct {
        unsigned char unkn10[15];
       } LEVELDATA_UNKN11;

typedef struct {
        LEVELDATA_UNKN01 u01;
        LEVELDATA_UNKN02 u02[128];
        LEVELDATA_UNKN03 u03[256]; // people
        LEVELDATA_UNKN04 u04[64];  // vehicles
        LEVELDATA_UNKN05 u05[400];
        LEVELDATA_UNKN06 u06[725];
        LEVELDATA_UNKN07 u07;
        LEVELDATA_UNKN08 u08[2048];
        LEVELDATA_UNKN09 u09;
        LEVELDATA_UNKN10 u10[9];
        LEVELDATA_UNKN11 u11[129];
       } LEVELDATA;

char *getCarType(int typenum)
{
    switch (typenum)
    {
    case  0:
    case  1:return "invalid";
    case  2:return "army car";
    case  3:return "burning army car";
    case  4:return "damaged army car";
    case  5:
    case  6:return "train head";
    case  7:return "burning train head";
    case  8:return "damaged train head";
    case  9:
    case 10:return "train section";
    case 11:return "burning train section";
    case 12:return "damaged train section";
    case 13:
    case 14:return "standard black car";
    case 15:return "burning black car";
    case 16:return "damaged black car";
    case 17:return "on signal fire car";
    default:return "unknown";
    }
}

int getUsrUValue(int minVal,int maxVal,int *newval)
{
         (*newval)=min(-1,minVal-1);
         printf("Enter new value (%d..%d):",minVal,maxVal);
         char buf[255];
         scanf("%s",buf);
         sscanf(buf,"%i",newval);
         if (((*newval)>=minVal) && ((*newval)<=maxVal))
         {
            printf("\nValue %d accepted.\n",*newval);
            return 1;
         }
         else
            printf("\nValue %d out of range, ignored.\n",*newval);
         return 0;
}

int getUsrFValue(float minVal,float maxVal,float *newval)
{
         (*newval)=min(-1.0,minVal-1.0);
         printf("Enter new value (%f..%f):",minVal,maxVal);
         char buf[255];
         scanf("%s",buf);
         sscanf(buf,"%f",newval);
         if (((*newval)>=minVal) && ((*newval)<=maxVal))
         {
            printf("\nValue %f saved.\n",*newval);
            return 1;
         }
         else
            printf("\nValue %f out of range, ignored.\n",*newval);
         return 0;
}

int getUsr8bitUValueTo(int minVal,int maxVal,unsigned char *dest_ptr)
{
    int newval;
    if (!getUsrUValue(minVal,maxVal,&newval))
        return 0;
    (*dest_ptr)=(unsigned char)(newval&255);
}

int getUsr16bitUValueTo(int minVal,int maxVal,unsigned char *dest_ptr)
{
    int newval;
    if (!getUsrUValue(minVal,maxVal,&newval))
        return 0;
    write_short_le_buf(dest_ptr,newval&65535);
}

int saveStructureToFile(char *samplename,char *src_ptr,unsigned long length)
{
         printf("\nEnter destination file name, ie \"%s\":",samplename);
         char newname[255];
         int i;
         for (i=0;i<255;i++)
             newname[i]=0;
//!!!!         scanf("%s",newname);
         if ((strlen(newname)<1)||(newname[0]<'!')) strcpy(newname,samplename);
         FILE *expfp=fopen(newname,"wb");
         if (expfp==NULL)
         {
            printf("\nOperation skipped - file creation error.\n");
            return 1;
         }
         fwrite (src_ptr, length, 1, expfp);
         fclose(expfp);
         printf("\nStructure saved as \"%s\".\n",newname);
         return 0;
}

int loadStructureFromFile(char *samplename,char *dest_ptr,unsigned long length)
{
         printf("\nEnter source file name, ie \"%s\":",samplename);
         char newname[255];
         int i;
         for (i=0;i<255;i++)
             newname[i]=0;
//!!!!         scanf("%s",newname);
         if ((strlen(newname)<1)||(newname[0]<'!')) strcpy(newname,samplename);
         FILE *impfp=fopen(newname,"rb");
         if (impfp==NULL)
         {
            printf("\nOperation skipped - file opening error.\n");
            return 1;
         }
         fread (dest_ptr, length, 1, impfp);
         fclose(impfp);
         printf("\nStructure loaded from \"%s\".\n",newname);
         return 0;
}

int editGlobalLevelParams(LEVELDATA *level)
{
  while (1)
  {
    printf("\n\nSyndicate level file format decoder:\n");
    printf("1 - save\n");
    printf("2 - load\n");
    printf("Esc - %s\n","Exit");
    printf("\nSelect what to edit:");
    int funcnum;
    char usr_answer;
    do
    {
        usr_answer=getch();
        if ((usr_answer<'1')||(usr_answer>'9'))
            funcnum=-1;
        else
            funcnum=usr_answer-'0';
    }
    while ((usr_answer!=VK_ESCAPE)&&((funcnum<0)));
    if (usr_answer==VK_ESCAPE)
    {
        printf("\n\nExiting - have a nice play!\n");
        return 0;
    }
    printf("%d\n",funcnum);
    switch (funcnum)
    {
    case 1:
        printf("Saving files...\n");
        saveStructureToFile("expr01.dat",(unsigned char *)&level->u01,sizeof(level->u01));
        saveStructureToFile("expr02.dat",(unsigned char *)&level->u02,sizeof(level->u02));
        saveStructureToFile("expr03.dat",(unsigned char *)&level->u03,sizeof(level->u03));
        saveStructureToFile("expr04.dat",(unsigned char *)&level->u04,sizeof(level->u04));
        saveStructureToFile("expr05.dat",(unsigned char *)&level->u05,sizeof(level->u05));
        saveStructureToFile("expr06.dat",(unsigned char *)&level->u06,sizeof(level->u06));
        saveStructureToFile("expr07.dat",(unsigned char *)&level->u07,sizeof(level->u07));
        saveStructureToFile("expr08.dat",(unsigned char *)&level->u08,sizeof(level->u08));
        saveStructureToFile("expr09.dat",(unsigned char *)&level->u09,sizeof(level->u09));
        saveStructureToFile("expr10.dat",(unsigned char *)&level->u10,sizeof(level->u10));
        saveStructureToFile("expr11.dat",(unsigned char *)&level->u11,sizeof(level->u11));
        break;
    case 2:
        printf("Loading files...\n");
        loadStructureFromFile("expr01.dat",(unsigned char *)&level->u01,sizeof(level->u01));
        loadStructureFromFile("expr02.dat",(unsigned char *)&level->u02,sizeof(level->u02));
        loadStructureFromFile("expr03.dat",(unsigned char *)&level->u03,sizeof(level->u03));
        loadStructureFromFile("expr04.dat",(unsigned char *)&level->u04,sizeof(level->u04));
        loadStructureFromFile("expr05.dat",(unsigned char *)&level->u05,sizeof(level->u05));
        loadStructureFromFile("expr06.dat",(unsigned char *)&level->u06,sizeof(level->u06));
        loadStructureFromFile("expr07.dat",(unsigned char *)&level->u07,sizeof(level->u07));
        loadStructureFromFile("expr08.dat",(unsigned char *)&level->u08,sizeof(level->u08));
        loadStructureFromFile("expr09.dat",(unsigned char *)&level->u09,sizeof(level->u09));
        loadStructureFromFile("expr10.dat",(unsigned char *)&level->u10,sizeof(level->u10));
        loadStructureFromFile("expr11.dat",(unsigned char *)&level->u11,sizeof(level->u11));
        break;
    default:
        printf("\nUnknown function. Select one of known functions!\n");
        break;
    }
  }
}

int main(int argc, char *argv[])
{
    printf("\nBullfrog Syndicate level files decoder");
    printf("\n    written by Tomasz Lis, 2006");
    printf("\n-------------------------------\n");
    if (argc<1)
    {
        printf("Not enought parameters.\n");
        printf("Usage:\n");
        printf("  synleved <levfile>\n");
    	return 1;
    }
    FILE *levfp;
    char levfname[255];
    sprintf(levfname,"%s",argv[1]);
    levfp = fopen (levfname, "rb");
    if (!levfp)
    {
        printf("\nCannot open level file!\n");
        return 1;
    }
    printf("Reading level file...");
    LEVELDATA level;
    fread (&level, sizeof(LEVELDATA), 1, levfp);
    printf("done.\n");
    fclose(levfp);

    printf("%d. DO THING\n",1);
    printf("Esc - %s\n","Exit");
    printf("\nEnter player number:");
    char usr_answer;
    int plnum;
    do
    {
        usr_answer=getch();
        if ((usr_answer<'1')||(usr_answer>('2')))
            plnum=-1;
        else
            plnum=usr_answer-'1';
    }
    while ((usr_answer!=VK_ESCAPE)&&((plnum<0)));
    int result;
    if (usr_answer==VK_ESCAPE)
    {
        printf("\n\nExiting without saving - have a nice play!\n");
        return 0;
    }
    printf("%d\n",plnum+1);
    if (plnum==0)
    {
       result=editGlobalLevelParams(&level);
    }

    levfp = fopen (levfname, "wb");
	fwrite (&level, sizeof(LEVELDATA), 1, levfp);
    fclose(levfp);

    printf("\nSavegame file has been rewritten. Execution complete.\n");
    system("PAUSE");
    return result;


}

