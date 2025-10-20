
		// Move human-player agents closer to the action
		uint16_t xpos = gamedata.People[8].Xpos - 175;   // Position of Soldier in building
		uint16_t ypos = gamedata.People[8].Ypos + 1000;
		uint16_t zpos = gamedata.People[8].Zpos;
		for (size_t i = 0; i < 8; i++) {
			gamedata.People[i].Xpos = xpos;
			gamedata.People[i].Ypos = ypos;
			gamedata.People[i].Zpos = zpos;
			xpos += 200;
		}

		// Define agents for computer player right after agents for human player
		size_t ps = 8;
		xpos = gamedata.People[12].Xpos + 400;  // Position of Guard near road
		ypos = gamedata.People[12].Ypos - 1500;
		zpos = gamedata.People[12].Zpos;
		for (size_t i = 0; i < 4; i++) {
			memset(&gamedata.People[ps], 0, sizeof(gamedata.People[ps]));  // Spawn 4 consecutive agents
			gamedata.People[ps].Xpos = xpos;
			gamedata.People[ps].Ypos = ypos;
			gamedata.People[ps].Zpos = zpos;
			gamedata.People[ps].Status = TS_MAPWHO;
			gamedata.People[ps].BaseFrame = PB_AGENT;
			gamedata.People[ps].Life = 16;     // Setting does NOT seem to affect health of computer player agents
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
			memset(&gamedata.People[ps], 0, sizeof(gamedata.People[ps]));
			gamedata.People[ps].Xpos = xpos;
			gamedata.People[ps].Ypos = ypos;
			gamedata.People[ps].Zpos = zpos;
			gamedata.People[ps].Status = TS_MAPWHO;
			gamedata.People[ps].BaseFrame = PB_AGENT;
			gamedata.People[ps].Life = 16;     // Setting does NOT seem to affect health of computer player agents
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
			ypos -= 500;
			memset(&gamedata.People[ps], 0, sizeof(gamedata.People[ps]));      // Leave 4 People table slots unoccupied
			memset(&gamedata.People[ps+1], 0, sizeof(gamedata.People[ps+1]));  // (necessary workaround for teams smaller than 8)
			memset(&gamedata.People[ps+2], 0, sizeof(gamedata.People[ps+2]));
			memset(&gamedata.People[ps+3], 0, sizeof(gamedata.People[ps+3]));
			ps += 4;
		}

		// CP Config
		gamedata.CPCount      = 5;  // Needs to be set to # of computer player + 1 (unsure why; wrong values cause buggy behavior)
		gamedata.CPTeamSize   = 4;  // Values lower than 8 requires some additional effort (see memset block above)
		gamedata.CPProcInt    = 8;  // Tunes general aggressiveness (reaction time + fire rate; lower value == higher aggressiveness)
		gamedata.CPLvlInit    = 1;  // Sets level of body mods (for all body parts)
		gamedata.CPIsBombTeam = 0;  // Specifies if agents carry time bombs (in addition to regular firearm)
		gamedata.CPIsPersTeam = 0;  // Specifies if agents carry persuadertrons (in addition to regular firearm)
		gamedata.CPFlags      = 4;  // Largely unknown, but it would seem 4 is REQUIRED to enable computer player infighting (*)
		gamedata.CPWeapon     = 0;  // Specifies firearm agents carry (e.g. WS_PISTOL; if set to 0, firearm is based on human player research
		                            // status: Shotgun, Uzi or Minigun)

		                            // (*) Value/flag 4 leads to "Yukon-style shoot when approaching target" behavior
		                            // (which, when computer players hunt for the human player, can lead to infighting
		                            // as agents seem to retaliate after being hit);
		                            // Even if computer players are instructed to attack other computer players (via
		                            // CPObjectives), this flag seems to be REQUIRED for actual infighting to occur
		                            // (without it, agents will just walk to their target and be "friendly" with it)

		// CP Objectives
		gamedata.CPObjectives[0].Player = 1;  // Computer Player 1 ...
		gamedata.CPObjectives[0].Parent = 0;
		gamedata.CPObjectives[0].Child = 0;
		gamedata.CPObjectives[0].ActionType = CPOAT_MOVE;
		gamedata.CPObjectives[0].Action = CPOA_GOTO_PERSON;
		gamedata.CPObjectives[0].Flags = 0;
		gamedata.CPObjectives[0].X = GET_RELOFS_FOR_THING(&gamedata, &gamedata.People[3]);
		gamedata.CPObjectives[0].Y = 0;       // ... walks to human player agent 4
		gamedata.CPObjectives[0].Z = 0;

		gamedata.CPObjectives[1].Player = 2;  // Computer Player 2 ...
		gamedata.CPObjectives[1].Parent = 0;
		gamedata.CPObjectives[1].Child = 0;
		gamedata.CPObjectives[1].ActionType = CPOAT_MOVE;
		gamedata.CPObjectives[1].Action = CPOA_GOTO_PERSON;
		gamedata.CPObjectives[1].Flags = 0;
		gamedata.CPObjectives[1].X = GET_RELOFS_FOR_THING(&gamedata, &gamedata.People[2]);
		gamedata.CPObjectives[1].Y = 0;       // ... walks to human player agent 3
		gamedata.CPObjectives[1].Z = 0;

		gamedata.CPObjectives[2].Player = 3;  // Computer Player 3 ...
		gamedata.CPObjectives[2].Parent = 0;
		gamedata.CPObjectives[2].Child = 0;
		gamedata.CPObjectives[2].ActionType = CPOAT_MOVE;
		gamedata.CPObjectives[2].Action = CPOA_GOTO_PERSON;
		gamedata.CPObjectives[2].Flags = 0;
		gamedata.CPObjectives[2].X = GET_RELOFS_FOR_THING(&gamedata, &gamedata.People[1]);
		gamedata.CPObjectives[2].Y = 0;       // ... walks to human player agent 2
		gamedata.CPObjectives[2].Z = 0;

		gamedata.CPObjectives[3].Player = 4;  // Computer Player 4 ...
		gamedata.CPObjectives[3].Parent = 0;
		gamedata.CPObjectives[3].Child = 0;
		gamedata.CPObjectives[3].ActionType = CPOAT_MOVE;
		gamedata.CPObjectives[3].Action = CPOA_GOTO_PERSON;
		gamedata.CPObjectives[3].Flags = 0;
		gamedata.CPObjectives[3].X = GET_RELOFS_FOR_THING(&gamedata, &gamedata.People[0]);
		gamedata.CPObjectives[3].Y = 0;       // ... walks to human player agent 1
		gamedata.CPObjectives[3].Z = 0;

		// Rebuild MapWho to account for added things (important!)
		rebuild_mapwho(&gamedata);
