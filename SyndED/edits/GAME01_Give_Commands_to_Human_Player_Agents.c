		// [TESTING] Command your own agents to be useful on their own
		gamedata.LoBoundaryx = 0;
		gamedata.LoBoundaryy = 0;
		gamedata.HiBoundaryx = 255;
		gamedata.HiBoundaryy = 255;
		Command command; memset(&command, 0, sizeof(Command)); size_t command_slot = 63;
		for (size_t i = 0; i <= 7; i++) {
			gamedata.People[i].NewState = PS_NEXT_COMMAND;
			gamedata.People[i].StartCommand = gamedata.People[i].Command = sizeof(Command) * command_slot;
		}
		command.Next = sizeof(Command) * (command_slot+1);
		command.GotoX = POS_TO_CMDGOTO(gamedata.People[0].Xpos) - 28;  // Go to 28 half-sized tiles north-west of starting point
		command.GotoY = POS_TO_CMDGOTO(gamedata.People[0].Ypos);       // (more or less the center of the court after bridge)
		command.State = CS_GOTO_POINT;
		gamedata.Commands[command_slot++] = command;
		for (size_t i = 0; i < PEOPLE_COUNT; i++) {
			if (gamedata.People[i].Unique != PU_GUARD)
				continue;
			command.Next = sizeof(Command) * (command_slot+1);
			command.GotoX = POS_TO_CMDGOTO(gamedata.People[i].Xpos);   // Hunt down guards
			command.GotoY = POS_TO_CMDGOTO(gamedata.People[i].Ypos);
			command.State = CS_GOTO_POINT;
			gamedata.Commands[command_slot++] = command;
		}
		//memset(&command, 0, sizeof(Command));                        // End of command list
		//command.State = CS_END_COMMANDS;
		//gamedata.Commands[command_slot++] = command;
		gamedata.Commands[command_slot-1].Next = 456;                  // Let's get that shiny black car (pre-existing command)
