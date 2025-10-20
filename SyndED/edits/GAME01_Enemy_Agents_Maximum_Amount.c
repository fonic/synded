
		// Move human-player agents closer to the action
		uint16_t xpos = gamedata.People[0].Xpos - 1000;  // First human player agent
		uint16_t ypos = gamedata.People[0].Ypos + 1000;
		uint16_t zpos = gamedata.People[0].Zpos;
		for (size_t i = 0; i < 8; i++) {
			gamedata.People[i].Xpos = xpos;
			gamedata.People[i].Ypos = ypos;
			gamedata.People[i].Zpos = zpos;
			ypos -= 125;
		}

		// Define agents for computer player right after agents for human player
		size_t ps = 8;
		xpos = gamedata.People[12].Xpos + 400;  // Position of Guard near road
		ypos = gamedata.People[12].Ypos - 250;
		zpos = gamedata.People[12].Zpos;
		for (size_t i = 0; i < 28; i++) {       // 28 * 2 = 56 agents total -> largest "army" size possible
			memset(&gamedata.People[ps], 0, sizeof(gamedata.People[ps]));  // Spawn 2 consecutive agents
			gamedata.People[ps].Xpos = xpos;
			gamedata.People[ps].Ypos = ypos;
			gamedata.People[ps].Zpos = zpos;
			gamedata.People[ps].Status = TS_MAPWHO;
			gamedata.People[ps].BaseFrame = PB_AGENT;
			gamedata.People[ps].Life = 16;      // Setting does NOT seem to affect health of computer player agents
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
			gamedata.People[ps].Life = 16;
			gamedata.People[ps].Model = TM_PERSON;
			gamedata.People[ps].Angle = TA_SOUTHEAST;
			gamedata.People[ps].Unique = PU_AGENT;
			gamedata.People[ps].State = gamedata.People[ps].OldState = gamedata.People[ps].NewState = PS_NONE;
			ps++;
			ypos -= 125;
			if ((i+1) % 4 == 0)  // Nicely group enemy agents
				ypos -= 125;
		}

		// CP Config
		gamedata.CPCount      = 8;  // Needs to be set to # of computer player + 1 (unsure why; wrong values cause buggy behavior)
		gamedata.CPTeamSize   = 8;  // If there is more than ONE computer player, only 8 works reliably (lower values cause buggy behavior)
		gamedata.CPProcInt    = 0;  // Tunes general aggressiveness (reaction time + fire rate; lower value == higher aggressiveness)
		gamedata.CPLvlInit    = 2;  // Sets level of body mods (for all body parts)
		gamedata.CPIsBombTeam = 0;  // Specifies if agents carry time bombs (in addition to regular firearm)
		gamedata.CPIsPersTeam = 0;  // Specifies if agents carry persuadertrons (in addition to regular firearm)
		gamedata.CPFlags      = 0;  // Largely unknown, but it would seem 4 is REQUIRED to enable computer player infighting (*)
		gamedata.CPWeapon     = 0;  // Specifies firearm agents carry (e.g. WS_PISTOL; if set to 0, firearm is based on human player research
		                            // status: Shotgun, Uzi or Minigun)

		                            // (*) Value/flag 4 leads to "Yukon-style shoot when approaching target" behavior
		                            // (which, when computer players hunt for the human player, can lead to infighting
		                            // as agents seem to retaliate after being hit);
		                            // Even if computer players are instructed to attack other computer players (via
		                            // CPObjectives), this flag seems to be REQUIRED for actual infighting to occur
		                            // (without it, agents will just walk to their target and be "friendly" with it)

		// CP Objectives
		memset(&gamedata.CPObjectives[0], 0, sizeof(gamedata.CPObjectives[0]));

		gamedata.CPObjectives[1].Player = 255;  // Wait a bit
		gamedata.CPObjectives[1].Parent = 0;
		gamedata.CPObjectives[1].Child = 2;
		gamedata.CPObjectives[1].ActionType = CPOAT_WAIT_TIME;
		gamedata.CPObjectives[1].Action = CPOA_NONE;
		gamedata.CPObjectives[1].Flags = 0;
		gamedata.CPObjectives[1].X = 50;
		gamedata.CPObjectives[1].Y = 0;
		gamedata.CPObjectives[1].Z = 0;

		gamedata.CPObjectives[2].Player = 255;  // Attack human player
		gamedata.CPObjectives[2].Parent = 1;
		gamedata.CPObjectives[2].Child = 2;
		gamedata.CPObjectives[2].ActionType = CPOAT_ATTACK_PLAYER;
		gamedata.CPObjectives[2].Action = CPOA_NONE;
		gamedata.CPObjectives[2].Flags = 0;
		gamedata.CPObjectives[2].X = 0;
		gamedata.CPObjectives[2].Y = 0;
		gamedata.CPObjectives[2].Z = 0;

		// Rebuild MapWho to account for added things (important!)
		rebuild_mapwho(&gamedata);
