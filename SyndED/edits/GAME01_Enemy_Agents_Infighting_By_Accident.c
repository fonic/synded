
		// [TESTING] Computer player infighting

		// Move human-player agents to a more suitable spot
		{
			uint16_t xpos = gamedata.People[8].Xpos - 75;  // Position of Soldier in building
			uint16_t ypos = gamedata.People[8].Ypos - 125;
			uint16_t zpos = gamedata.People[8].Zpos;
			for (size_t i = 0; i < 8; i++) {
				gamedata.People[i].Xpos = xpos;
				gamedata.People[i].Ypos = ypos;
				gamedata.People[i].Zpos = zpos;
				xpos += 50;
			}
		}

		// Define agents for computer player right after agents for human player
		size_t ps = 8;
		uint16_t xpos = gamedata.People[12].Xpos + 500;  // Position of Guard near road
		uint16_t ypos = gamedata.People[12].Ypos - 500;
		uint16_t zpos = gamedata.People[12].Zpos;
		for (size_t i = 0; i < 16; i++) {
			memset(&gamedata.People[ps], 0, sizeof(gamedata.People[ps]));
			gamedata.People[ps].Xpos = xpos;
			gamedata.People[ps].Ypos = ypos;
			gamedata.People[ps].Zpos = zpos;
			gamedata.People[ps].Status = TS_MAPWHO;
			gamedata.People[ps].BaseFrame = PB_AGENT;
			gamedata.People[ps].Life = 8;
			gamedata.People[ps].Model = TM_PERSON;
			gamedata.People[ps].Angle = TA_SOUTHEAST;
			gamedata.People[ps].Unique = PU_AGENT;
			gamedata.People[ps].State = gamedata.People[ps].OldState = gamedata.People[ps].NewState = PS_NONE;
			ps++;
			memset(&gamedata.People[ps], 0, sizeof(gamedata.People[ps]));
			gamedata.People[ps].Xpos = xpos + 125;
			gamedata.People[ps].Ypos = ypos;
			gamedata.People[ps].Zpos = zpos;
			gamedata.People[ps].Status = TS_MAPWHO;
			gamedata.People[ps].BaseFrame = PB_AGENT;
			gamedata.People[ps].Life = 8;
			gamedata.People[ps].Model = TM_PERSON;
			gamedata.People[ps].Angle = TA_SOUTHEAST;
			gamedata.People[ps].Unique = PU_AGENT;
			gamedata.People[ps].State = gamedata.People[ps].OldState = gamedata.People[ps].NewState = PS_NONE;
			ps++;
			ypos -= 125;
			if ( (i+1) % 4 == 0 )
				ypos -= 125;
		}

		// NOTE:
		// Everything below was tailored to resemble the Yukon mission (which
		// features infighting), but in the end it turned out that CPFlags = 4
		// is all that's really needed for infighting to occur

		// CP Config
		gamedata.CPCount      = 5;
		gamedata.CPTeamSize   = 8;
		gamedata.CPProcInt    = 8;
		gamedata.CPLvlInit    = 0;
		gamedata.CPIsBombTeam = 0;
		gamedata.CPIsPersTeam = 0;
		gamedata.CPFlags      = 23;  // Flag 4 enables infighting
		gamedata.CPWeapon     = 0;

		// CP Objectives
		gamedata.CPObjectives[0].Player = 255;
		gamedata.CPObjectives[0].Parent = 0;
		gamedata.CPObjectives[0].Child = 0;
		gamedata.CPObjectives[0].ActionType = CPOAT_KILL_HUMAN_PLAYER;
		gamedata.CPObjectives[0].Action = CPOA_NONE;
		gamedata.CPObjectives[0].Flags = 0;
		gamedata.CPObjectives[0].X = 0;
		gamedata.CPObjectives[0].Y = 0;
		gamedata.CPObjectives[0].Z = 0;

		gamedata.CPObjectives[1].Player = 255;
		gamedata.CPObjectives[1].Parent = 0;
		gamedata.CPObjectives[1].Child = 2;
		gamedata.CPObjectives[1].ActionType = CPOAT_WAIT_TIME;
		gamedata.CPObjectives[1].Action = CPOA_NONE;
		gamedata.CPObjectives[1].Flags = 0;
		gamedata.CPObjectives[1].X = 50;
		gamedata.CPObjectives[1].Y = 0;
		gamedata.CPObjectives[1].Z = 0;

		gamedata.CPObjectives[2].Player = 255;
		gamedata.CPObjectives[2].Parent = 1;
		gamedata.CPObjectives[2].Child = 0;
		gamedata.CPObjectives[2].ActionType = CPOAT_KILL_HUMAN_PLAYER;
		gamedata.CPObjectives[2].Action = CPOA_NONE;
		gamedata.CPObjectives[2].Flags = 0;
		gamedata.CPObjectives[2].X = 0;
		gamedata.CPObjectives[2].Y = 0;
		gamedata.CPObjectives[2].Z = 0;

		gamedata.CPObjectives[3].Player = 0;
		gamedata.CPObjectives[3].Parent = 0;
		gamedata.CPObjectives[3].Child = 0;
		gamedata.CPObjectives[3].ActionType = CPOAT_NONE;
		gamedata.CPObjectives[3].Action = CPOA_NONE;
		gamedata.CPObjectives[3].Flags = 64;
		gamedata.CPObjectives[3].X = 0;
		gamedata.CPObjectives[3].Y = 0;
		gamedata.CPObjectives[3].Z = 0;

		gamedata.CPObjectives[4].Player = 0;
		gamedata.CPObjectives[4].Parent = 0;
		gamedata.CPObjectives[4].Child = 0;
		gamedata.CPObjectives[4].ActionType = CPOAT_NONE;
		gamedata.CPObjectives[4].Action = CPOA_NONE;
		gamedata.CPObjectives[4].Flags = 64;
		gamedata.CPObjectives[4].X = 0;
		gamedata.CPObjectives[4].Y = 0;
		gamedata.CPObjectives[4].Z = 0;

		// Rebuild MapWho to account for added things (important!)
		rebuild_mapwho(&gamedata);
