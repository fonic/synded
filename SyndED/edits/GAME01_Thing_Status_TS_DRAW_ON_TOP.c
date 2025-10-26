
		// Get agent 1 close to the action
		gamedata.People[0].Xpos = gamedata.People[12].Xpos + 1000;
		gamedata.People[0].Ypos = gamedata.People[12].Ypos - 1250;
		gamedata.People[0].Zpos = gamedata.People[12].Zpos;

		// Get position of guard near road
		int16_t xpos = gamedata.People[12].Xpos + 500;
		int16_t ypos = gamedata.People[12].Ypos - 500;
		int16_t zpos = gamedata.People[12].Zpos;
		memset(&gamedata.People[12], 0, sizeof(gamedata.People[12]));  // Erase guard

		// Add women with certain flags set
		size_t slot = 20;
		for (size_t i = 1; i < 16; i++) {
			memset(&gamedata.People[slot], 0, sizeof(gamedata.People[slot]));
			gamedata.People[slot].Xpos = xpos;
			gamedata.People[slot].Ypos = ypos;
			gamedata.People[slot].Zpos = zpos;
			gamedata.People[slot].Status = TS_MAPWHO | TS_DRAW_ON_TOP;
			gamedata.People[slot].Angle = TA_SOUTHEAST;
			gamedata.People[slot].Model = TM_PERSON;
			gamedata.People[slot].Unique = PU_CIVILIAN;
			gamedata.People[slot].Life = 8;
			gamedata.People[slot].BaseSpeed = gamedata.People[slot].MaxSpeed = 4;
			gamedata.People[slot].State = PS_WANDER;
			gamedata.People[slot].BaseFrame = PB_WOMAN_BLONDE;
			gamedata.People[slot].Frame = gamedata.People[slot].OldFrame = 0;
			ypos -= 225; slot++;
		}

		// Rebuild MapWho to account for added things (important!)
		rebuild_mapwho(&gamedata);
