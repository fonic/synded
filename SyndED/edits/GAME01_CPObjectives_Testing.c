
		// [TESTING] Modify CPObjectives

		gamedata.LoBoundaryx = 0;
		gamedata.LoBoundaryy = 0;
		gamedata.HiBoundaryx = 255;
		gamedata.HiBoundaryy = 255;

		gamedata.CPCount      = 5; // n CP players (1 is either humans player -or- CP player for Guards/Police/Civilians)
		gamedata.CPTeamSize   = 8; // m agents per CP player
		gamedata.CPProcInt    = 0; // Unknown
		gamedata.CPLvlInit    = 0; // Level of body mods
		gamedata.CPIsBombTeam = 1; // Do Agents carry Time Bombs?
		gamedata.CPIsPersTeam = 1; // Do Agents carry Persuadertrons?
		gamedata.CPFlags      = 0; // Unknown
		gamedata.CPWeapon     = 0; // Likely primary weapon

		/*for (size_t i = 0; i < CPOBJECTIVES_COUNT; i++) {  // not sure yet if this actually does something
			gamedata.CPObjectives[i].Flags = 64;
		}*/

		gamedata.CPObjectives[0].Player = 255;  // player == 255 -> all agents of a computer player execute
		gamedata.CPObjectives[0].Parent = 0;    // the command once ONE of the agents reaches the command
		gamedata.CPObjectives[0].Child = 0;
		gamedata.CPObjectives[0].ActionType = CPOAT_KILL_HUMAN_PLAYER;
		gamedata.CPObjectives[0].Action = CPOA_NONE;
		gamedata.CPObjectives[0].Flags = 0;
		gamedata.CPObjectives[0].X = 0;
		gamedata.CPObjectives[0].Y = 0;
		gamedata.CPObjectives[0].Z = 0;

		/*CPObjective cpobjective; memset(&cpobjective, 0, sizeof(cpobjective));  // clear out objective 0
		gamedata.CPObjectives[0] = cpobjective;*/

		/*Person person; memset(&person, 0, sizeof(person));  // erase unused human player agents 4-8
		gamedata.People[4] = gamedata.People[5] = gamedata.People[6] = gamedata.People[7] = person;*/


		size_t objective_slot; uint16_t playnum;

		// CP Player 1 (blue hats)
		objective_slot = 3; playnum = 1;
		gamedata.CPObjectives[objective_slot+0].Player = playnum;            // wait for some time
		gamedata.CPObjectives[objective_slot+0].Parent = 0;
		gamedata.CPObjectives[objective_slot+0].Child = objective_slot+1;
		gamedata.CPObjectives[objective_slot+0].ActionType = CPOAT_WAIT_TIME;
		gamedata.CPObjectives[objective_slot+0].Action = CPOA_NONE;
		gamedata.CPObjectives[objective_slot+0].Flags = 0;
		gamedata.CPObjectives[objective_slot+0].X = 50;
		gamedata.CPObjectives[objective_slot+0].Y = 0;
		gamedata.CPObjectives[objective_slot+0].Z = 0;

		gamedata.CPObjectives[objective_slot+1].Player = playnum;            // goto position
		gamedata.CPObjectives[objective_slot+1].Parent = objective_slot+0;
		//gamedata.CPObjectives[objective_slot+1].Child = objective_slot+1;  // stop command chain (endless loop)
		gamedata.CPObjectives[objective_slot+1].Child = 0;                   // jump to command at index 0 (default command)
		//gamedata.CPObjectives[objective_slot+1].Child = objective_slot+2;  // next command in chain
		gamedata.CPObjectives[objective_slot+1].ActionType = CPOAT_GOTO;
		gamedata.CPObjectives[objective_slot+1].Action = CPOA_POSITION;
		gamedata.CPObjectives[objective_slot+1].Flags = 0;
		gamedata.CPObjectives[objective_slot+1].X = gamedata.Vehicles[0].Xpos - 0;
		gamedata.CPObjectives[objective_slot+1].Y = gamedata.Vehicles[0].Ypos + 500;
		gamedata.CPObjectives[objective_slot+1].Z = gamedata.Vehicles[0].Zpos;

		/*gamedata.CPObjectives[objective_slot+2].Player = playnum;
		gamedata.CPObjectives[objective_slot+2].Parent = objective_slot+1;
		gamedata.CPObjectives[objective_slot+2].Child = 0;
		gamedata.CPObjectives[objective_slot+2].ActionType = CPOAT_GOTO;
		gamedata.CPObjectives[objective_slot+2].Action = CPOA_UNKNOWN_0C;
		gamedata.CPObjectives[objective_slot+2].Flags = 0;
		gamedata.CPObjectives[objective_slot+2].X = 26332;
		gamedata.CPObjectives[objective_slot+2].Y = 0;
		gamedata.CPObjectives[objective_slot+2].Z = 0;*/


		// CP Player 2 (red hats)
		objective_slot = 9; playnum = 2;
		gamedata.CPObjectives[objective_slot+0].Player = playnum;
		gamedata.CPObjectives[objective_slot+0].Parent = 0;
		gamedata.CPObjectives[objective_slot+0].Child = objective_slot+1;
		gamedata.CPObjectives[objective_slot+0].ActionType = CPOAT_WAIT_TIME;
		gamedata.CPObjectives[objective_slot+0].Action = CPOA_NONE;
		gamedata.CPObjectives[objective_slot+0].Flags = 0;
		gamedata.CPObjectives[objective_slot+0].X = 75;
		gamedata.CPObjectives[objective_slot+0].Y = 0;
		gamedata.CPObjectives[objective_slot+0].Z = 0;

		gamedata.CPObjectives[objective_slot+1].Player = playnum;
		gamedata.CPObjectives[objective_slot+1].Parent = objective_slot+0;
		//gamedata.CPObjectives[objective_slot+1].Child = objective_slot+1;
		//gamedata.CPObjectives[objective_slot+1].Child = 0;
		gamedata.CPObjectives[objective_slot+1].Child = objective_slot+2;
		gamedata.CPObjectives[objective_slot+1].ActionType = CPOAT_GOTO;
		gamedata.CPObjectives[objective_slot+1].Action = CPOA_POSITION;
		gamedata.CPObjectives[objective_slot+1].Flags = 0;
		gamedata.CPObjectives[objective_slot+1].X = gamedata.Vehicles[0].Xpos - 500;
		gamedata.CPObjectives[objective_slot+1].Y = gamedata.Vehicles[0].Ypos + 500;
		gamedata.CPObjectives[objective_slot+1].Z = gamedata.Vehicles[0].Zpos;

		gamedata.CPObjectives[objective_slot+2].Player = playnum;
		gamedata.CPObjectives[objective_slot+2].Parent = objective_slot+1;
		gamedata.CPObjectives[objective_slot+2].Child = 0;
		gamedata.CPObjectives[objective_slot+2].ActionType = CPOAT_DESTROY_VEHICLE;
		gamedata.CPObjectives[objective_slot+2].Action = 0;
		gamedata.CPObjectives[objective_slot+2].Flags = 0;
		gamedata.CPObjectives[objective_slot+2].X = GET_RELOFS_FOR_THING(&gamedata, &gamedata.Vehicles[0]);
		gamedata.CPObjectives[objective_slot+2].Y = 0;
		gamedata.CPObjectives[objective_slot+2].Z = 0;


		// CP Player 3 (green hats)
		objective_slot = 15; playnum = 3;
		gamedata.CPObjectives[objective_slot+0].Player = playnum;
		gamedata.CPObjectives[objective_slot+0].Parent = 0;
		gamedata.CPObjectives[objective_slot+0].Child = objective_slot+1;
		gamedata.CPObjectives[objective_slot+0].ActionType = CPOAT_WAIT_TIME;
		gamedata.CPObjectives[objective_slot+0].Action = CPOA_NONE;
		gamedata.CPObjectives[objective_slot+0].Flags = 0;
		gamedata.CPObjectives[objective_slot+0].X = 100;
		gamedata.CPObjectives[objective_slot+0].Y = 0;
		gamedata.CPObjectives[objective_slot+0].Z = 0;

		gamedata.CPObjectives[objective_slot+1].Player = playnum;
		gamedata.CPObjectives[objective_slot+1].Parent = objective_slot+0;
		//gamedata.CPObjectives[objective_slot+1].Child = objective_slot+1;
		//gamedata.CPObjectives[objective_slot+1].Child = 0;
		gamedata.CPObjectives[objective_slot+1].Child = objective_slot+2;
		gamedata.CPObjectives[objective_slot+1].ActionType = CPOAT_GOTO;
		gamedata.CPObjectives[objective_slot+1].Action = CPOA_POSITION;
		gamedata.CPObjectives[objective_slot+1].Flags = 0;
		gamedata.CPObjectives[objective_slot+1].X = gamedata.Vehicles[0].Xpos - 1000;
		gamedata.CPObjectives[objective_slot+1].Y = gamedata.Vehicles[0].Ypos + 500;
		gamedata.CPObjectives[objective_slot+1].Z = gamedata.Vehicles[0].Zpos;

		gamedata.Objectives[0].Data = 3682;                   // Assassination target for human player == blonde woman
		gamedata.Objectives[0].Type = OT_ASSASSINATE_PERSON;  // (to demonstrate agent CPObjective right below)

		gamedata.CPObjectives[objective_slot+2].Player = playnum;
		gamedata.CPObjectives[objective_slot+2].Parent = objective_slot+1;
		//gamedata.CPObjectives[objective_slot+2].Child = 0;
		gamedata.CPObjectives[objective_slot+2].Child = objective_slot+3;
		gamedata.CPObjectives[objective_slot+2].ActionType = CPOAT_KILL_ASSTRGT;  // Kill assassination target specified by gamedata.Objective[0] using weapon (i.e. shoot)
		gamedata.CPObjectives[objective_slot+2].Action = 0;                       // Action/X/Y/Z likely ignored (not sure)
		gamedata.CPObjectives[objective_slot+2].Flags = 0;
		gamedata.CPObjectives[objective_slot+2].X = 0;
		gamedata.CPObjectives[objective_slot+2].Y = 0;
		gamedata.CPObjectives[objective_slot+2].Z = 0;

		gamedata.CPObjectives[objective_slot+3].Player = playnum;
		gamedata.CPObjectives[objective_slot+3].Parent = objective_slot+2;
		gamedata.CPObjectives[objective_slot+3].Child = 0;
		gamedata.CPObjectives[objective_slot+3].ActionType = CPOAT_DROP_TIME_BOMB;  // Seems to be "drop time bomb" (only works for time bomb, nothing else is ever dropped)
		gamedata.CPObjectives[objective_slot+3].Action = 0;                         // does not seem to matter, also works when set to 0
		gamedata.CPObjectives[objective_slot+3].Flags = 0;
		gamedata.CPObjectives[objective_slot+3].X = 0;
		gamedata.CPObjectives[objective_slot+3].Y = 0;
		gamedata.CPObjectives[objective_slot+3].Z = 0;


		// CP Player 4 (yellow hats)
		objective_slot = 21; playnum = 4;
		gamedata.CPObjectives[objective_slot+0].Player = playnum;
		gamedata.CPObjectives[objective_slot+0].Parent = 0;
		gamedata.CPObjectives[objective_slot+0].Child = objective_slot+1;
		gamedata.CPObjectives[objective_slot+0].ActionType = CPOAT_WAIT_TIME;
		gamedata.CPObjectives[objective_slot+0].Action = CPOA_NONE;
		gamedata.CPObjectives[objective_slot+0].Flags = 0;
		gamedata.CPObjectives[objective_slot+0].X = 100;
		gamedata.CPObjectives[objective_slot+0].Y = 0;
		gamedata.CPObjectives[objective_slot+0].Z = 0;

		gamedata.CPObjectives[objective_slot+1].Player = playnum;
		gamedata.CPObjectives[objective_slot+1].Parent = objective_slot+0;
		gamedata.CPObjectives[objective_slot+1].Child = objective_slot+1;
		//gamedata.CPObjectives[objective_slot+0].Child = 0;
		gamedata.CPObjectives[objective_slot+1].ActionType = CPOAT_GOTO;
		gamedata.CPObjectives[objective_slot+1].Action = CPOA_POSITION;
		gamedata.CPObjectives[objective_slot+1].Flags = 0;
		gamedata.CPObjectives[objective_slot+1].X = gamedata.Vehicles[0].Xpos - 1500;
		gamedata.CPObjectives[objective_slot+1].Y = gamedata.Vehicles[0].Ypos + 500;
		gamedata.CPObjectives[objective_slot+1].Z = gamedata.Vehicles[0].Zpos;

		/*gamedata.CPObjectives[objective_slot+2].Player = playnum;
		gamedata.CPObjectives[objective_slot+2].Parent = objective_slot+1;
		gamedata.CPObjectives[objective_slot+2].Child = 0;
		gamedata.CPObjectives[objective_slot+2].ActionType = CPOAT_KILL_PERSON;
		gamedata.CPObjectives[objective_slot+2].Action = CPOA_NONE;
		gamedata.CPObjectives[objective_slot+2].Flags = 0;
		gamedata.CPObjectives[objective_slot+2].X = 738;
		gamedata.CPObjectives[objective_slot+2].Y = 0;
		gamedata.CPObjectives[objective_slot+2].Z = 0;*/


		size_t person_slot = 8; // Agents have to be placed here to work correctly!
		                        // (or at least to be colored correctly)

		uint16_t xpos = gamedata.People[12].Xpos + 500;  // Position of Guard near road
		uint16_t ypos = gamedata.People[12].Ypos - 500;  // (guard will get overwritten by agent spawning below)
		uint16_t zpos = gamedata.People[12].Zpos;
		for (size_t i = 0; i < 16; i++) {  // Spawn agents for computer player
			memset(&gamedata.People[person_slot], 0, sizeof(gamedata.People[person_slot]));
			gamedata.People[person_slot].Xpos = xpos;
			gamedata.People[person_slot].Ypos = ypos;
			gamedata.People[person_slot].Zpos = zpos;
			gamedata.People[person_slot].Status = TS_MAPWHO;
			gamedata.People[person_slot].BaseFrame = PB_AGENT;
			gamedata.People[person_slot].Life = 8;
			gamedata.People[person_slot].Model = TM_PERSON;
			gamedata.People[person_slot].Angle = TA_SOUTHEAST;
			gamedata.People[person_slot].Unique = PU_AGENT;
			gamedata.People[person_slot].State = gamedata.People[person_slot].OldState = gamedata.People[person_slot].NewState = PS_NONE;
			person_slot++;
			memset(&gamedata.People[person_slot], 0, sizeof(gamedata.People[person_slot]));
			gamedata.People[person_slot].Xpos = xpos + 250;
			gamedata.People[person_slot].Ypos = ypos;
			gamedata.People[person_slot].Zpos = zpos;
			gamedata.People[person_slot].Status = TS_MAPWHO;
			gamedata.People[person_slot].BaseFrame = PB_AGENT;
			gamedata.People[person_slot].Life = 8;
			gamedata.People[person_slot].Model = TM_PERSON;
			gamedata.People[person_slot].Angle = TA_SOUTHEAST;
			gamedata.People[person_slot].Unique = PU_AGENT;
			gamedata.People[person_slot].State = gamedata.People[person_slot].OldState = gamedata.People[person_slot].NewState = PS_NONE;
			person_slot++;
			ypos -= 250;
		}

		gamedata.People[person_slot].Xpos = gamedata.Vehicles[0].Xpos + 3500;  // blonde woman in standing in front of door near river
		gamedata.People[person_slot].Ypos = gamedata.Vehicles[0].Ypos + 4250;
		gamedata.People[person_slot].Zpos = gamedata.Vehicles[0].Zpos;
		gamedata.People[person_slot].Status = TS_MAPWHO;
		gamedata.People[person_slot].BaseFrame = PB_WOMAN_BLONDE;
		gamedata.People[person_slot].Life = 8;
		gamedata.People[person_slot].Model = TM_PERSON;
		gamedata.People[person_slot].Angle = TA_SOUTHEAST;
		gamedata.People[person_slot].Unique = PU_CIVILIAN;
		gamedata.People[person_slot].State = gamedata.People[person_slot].OldState = gamedata.People[person_slot].NewState = PS_NONE;

		// Rebuild MapWho (important!)
		rebuild_mapwho(&gamedata);
