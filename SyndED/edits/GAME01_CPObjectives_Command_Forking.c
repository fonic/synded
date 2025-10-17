		// Define agents for computer player right after agents for human player
		uint16_t xpos = gamedata.People[12].Xpos + 500;  // Position of Guard near road
		uint16_t ypos = gamedata.People[12].Ypos - 500;
		uint16_t zpos = gamedata.People[12].Zpos;
		for (size_t p = 8; p < 16; p++) {
			memset(&gamedata.People[p], 0, sizeof(gamedata.People[p]));
			gamedata.People[p].Xpos = xpos;
			gamedata.People[p].Ypos = ypos;
			gamedata.People[p].Zpos = zpos;
			gamedata.People[p].Status = TS_MAPWHO;
			gamedata.People[p].BaseFrame = PB_AGENT;
			gamedata.People[p].Life = 8;
			gamedata.People[p].Model = TM_PERSON;
			gamedata.People[p].Angle = TA_SOUTHEAST;
			gamedata.People[p].Unique = PU_AGENT;
			gamedata.People[p].State = gamedata.People[p].OldState = gamedata.People[p].NewState = PS_NONE;
			ypos -= 250;
		}

		// CP Config
		gamedata.CPCount      = 2;
		gamedata.CPTeamSize   = 8;
		gamedata.CPProcInt    = 0;
		gamedata.CPLvlInit    = 0;
		gamedata.CPIsBombTeam = 1;
		gamedata.CPIsPersTeam = 1;
		gamedata.CPFlags      = 0;
		gamedata.CPWeapon     = 0;

		// CP Objectives 0-2
		gamedata.CPObjectives[0].Player = 255;  // Hunt and kill human player (endless loop)
		gamedata.CPObjectives[0].Parent = 0;
		gamedata.CPObjectives[0].Child = 0;
		gamedata.CPObjectives[0].ActionType = CPOAT_KILL_HUMAN_PLAYER;
		gamedata.CPObjectives[0].Action = CPOA_NONE;
		gamedata.CPObjectives[0].Flags = 0;
		gamedata.CPObjectives[0].X = 0;
		gamedata.CPObjectives[0].Y = 0;
		gamedata.CPObjectives[0].Z = 0;

		gamedata.CPObjectives[1].Player = 255;  // Wait a bit, continue with next objective
		gamedata.CPObjectives[1].Parent = 0;
		gamedata.CPObjectives[1].Child = 2;
		gamedata.CPObjectives[1].ActionType = CPOAT_WAIT_TIME;
		gamedata.CPObjectives[1].Action = CPOA_NONE;
		gamedata.CPObjectives[1].Flags = 0;
		gamedata.CPObjectives[1].X = 100;
		gamedata.CPObjectives[1].Y = 0;
		gamedata.CPObjectives[1].Z = 0;

		gamedata.CPObjectives[2].Player = 255;  // Fork CPObjectives execution flow for each agent (see below)
		gamedata.CPObjectives[2].Parent = 1;
		gamedata.CPObjectives[2].Child = 0;
		gamedata.CPObjectives[2].ActionType = CPOAT_FORK_CPOBJ_FLOW;
		gamedata.CPObjectives[2].Action = CPOA_NONE;
		gamedata.CPObjectives[2].Flags = 0;
		gamedata.CPObjectives[2].X = 0;
		gamedata.CPObjectives[2].Y = 0;
		gamedata.CPObjectives[2].Z = 0;

		// CP Objectives for each of the eight computer player agents individually
		size_t spo = 3;                               // Right after CPObjectives 0-2 defined above
		for (size_t p = 8; p < 16; p++) {
			gamedata.CPObjectives[spo].Player = 255;  // Step forward, continue with next objective
			gamedata.CPObjectives[spo].Parent = 0;
			gamedata.CPObjectives[spo].Child = spo+1;
			gamedata.CPObjectives[spo].ActionType = CPOAT_MOVE;
			gamedata.CPObjectives[spo].Action = CPOA_GOTO_POSITION;
			gamedata.CPObjectives[spo].Flags = 0;
			gamedata.CPObjectives[spo].X = gamedata.People[p].Xpos + 500;
			gamedata.CPObjectives[spo].Y = gamedata.People[p].Ypos;
			gamedata.CPObjectives[spo].Z = gamedata.People[p].Zpos;
			spo++;

			gamedata.CPObjectives[spo].Player = 255;  // Wait a bit, continue with next objective
			gamedata.CPObjectives[spo].Parent = spo-1;
			gamedata.CPObjectives[spo].Child = spo+1;
			gamedata.CPObjectives[spo].ActionType = CPOAT_WAIT_TIME;
			gamedata.CPObjectives[spo].Action = CPOA_NONE;
			gamedata.CPObjectives[spo].Flags = 0;
			gamedata.CPObjectives[spo].X = 50;
			gamedata.CPObjectives[spo].Y = 0;
			gamedata.CPObjectives[spo].Z = 0;
			spo++;

			gamedata.CPObjectives[spo].Player = 255;  // Step back, stay put (endless loop)
			gamedata.CPObjectives[spo].Parent = spo-1;
			gamedata.CPObjectives[spo].Child = spo;
			gamedata.CPObjectives[spo].ActionType = CPOAT_MOVE;
			gamedata.CPObjectives[spo].Action = CPOA_GOTO_POSITION;
			gamedata.CPObjectives[spo].Flags = 0;
			gamedata.CPObjectives[spo].X = gamedata.People[p].Xpos;
			gamedata.CPObjectives[spo].Y = gamedata.People[p].Ypos;
			gamedata.CPObjectives[spo].Z = gamedata.People[p].Zpos;
			spo++;
		}

		// Rebuild MapWho to account for added things
		rebuild_mapwho(&gamedata);
