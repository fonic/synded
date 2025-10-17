		// [TESTING] Macros GET_RELOFS_FOR_THING + GET_THING_FOR_RELOFS
		printf("Relative offset of gamedata.People[12]:   %u\n", GET_RELOFS_FOR_THING(&gamedata, &gamedata.People[12]));
		printf("Relative offset of gamedata.Vehicles[20]: %u\n", GET_RELOFS_FOR_THING(&gamedata, &gamedata.Vehicles[20]));
		Thing *t = GET_THING_FOR_RELOFS(&gamedata, 1106);   // Retrieved thing must match gamedata.People[12]
		printf("Thing.RelOfs:  %u, Thing.Xpos:  %u, Thing.Ypos:  %u\n", 1106, t->Xpos, t->Ypos);
		printf("Person.RelOfs: %u, Person.Xpos: %u, Person.Ypos: %u\n", (uint16_t)(PEOPLE_RELATIVE_OFFSET + sizeof(Person) * 12), gamedata.People[12].Xpos, gamedata.People[12].Ypos);
		Thing *t2 = GET_THING_FOR_RELOFS(&gamedata, 24394); // Retrieved thing must match gamedata.Vehicles[20]
		printf("Thing.RelOfs:   %u, Thing.Xpos:   %u, Thing.Ypos:   %u\n", 24394, t2->Xpos, t2->Ypos);
		printf("Vehicle.RelOfs: %u, Vehicle.Xpos: %u, Vehicle.Ypos: %u\n", (uint16_t)(VEHICLES_RELATIVE_OFFSET + sizeof(Vehicle) * 20), gamedata.Vehicles[20].Xpos, gamedata.Vehicles[20].Ypos);
