/******************************************************************************
 *                                                                            *
 *  Syndicate Editor - MapWho Management                                      *
 *                                                                            *
 *  Created by Fonic <https://github.com/fonic>                               *
 *  Date: 10/08/25 - 10/14/25                                                 *
 *                                                                            *
 ******************************************************************************/

#include "mapwho.h"   // related header

#include <string.h>   // memset

#include "gdenums.h"  // TS_MAPWHO

// Based on function move_mapwho() in RGAME.C (but modified to fit our use case)
bool add_thing_to_mapwho(GameData *gamedata, Thing *thing) {
	int16_t   xtile, ytile;
	uint16_t *mw;
	Thing    *child;
	uint16_t  relofs;

	if (thing->Status & TS_MAPWHO) {                              // Thing already is on MapWho, thus don't add it (function move_
		return false;                                             // thing_within_mapwho must be used instead to move thing within mapwho)
	}

	xtile = (thing->Xpos >> 8);                                   // Position to tile (positions are 16 bit -> highest 8 bit == tile,
	ytile = (thing->Ypos >> 8);                                   // lowest 8 bit == sub-position within tile)

	/*                                                            // Original from RGAME.C, replaced by modified variant below
	if (xtile < MIN_TILE_X)                                       // Below lowest possible tile? -> wrap position around to highest possible tile
		thing->Xpos = MAX_TILE_X * POS_PER_TILE;
	if (ytile < MIN_TILE_Y)
		thing->Ypos = MAX_TILE_Y * POS_PER_TILE;

	if (xtile > MAX_TILE_X)                                       // Above highest possible tile? -> wrap position around to lowest possible tile
		thing->Xpos = MIN_TILE_X * POS_PER_TILE;                  // CAUTION: this was (MIN_TILE_X+1) in RGAME.C (not sure why though)
	if (ytile > MAX_TILE_Y)
		thing->Ypos = MIN_TILE_Y * POS_PER_TILE;                  // CAUTION: this was (MIN_TILE_Y+1) in RGAME.C (not sure why though)
	*/

	if (xtile < MIN_TILE_X)                                       // Below lowest possible tile? -> readjust position to lowest possible tile
		thing->Xpos = MIN_TILE_X * POS_PER_TILE;
	if (ytile < MIN_TILE_Y)
		thing->Ypos = MIN_TILE_Y * POS_PER_TILE;

	if (xtile > MAX_TILE_X)                                       // Above highest possible tile? -> readjust position to highest possible tile
		thing->Xpos = MAX_TILE_X * POS_PER_TILE;
	if (ytile > MAX_TILE_Y)
		thing->Ypos = MAX_TILE_Y * POS_PER_TILE;

	thing->Zpos &= MAX_ZPOS;                                      // Limit Z position to highest possible value (cutoff)

	mw = &gamedata->MapWho[POS_TO_MAPWHO_OFS(thing->Xpos, thing->Ypos)];    // Reference to head of linked list in mapwho (at position of thing)

	relofs = GET_RELOFS_FOR_THING(gamedata, thing);
	thing->Parent = 0;                                            // Thing becomes new head of linked list (i.e. no parent)
	thing->Child = *(mw);                                         // Child points to what was previously stored in mapwho (i.e. FORMER head of linked list -or- 0)
	if (thing->Child != 0) {                                      // If child actually exists (see if above) ...
		child = GET_THING_FOR_RELOFS(gamedata, thing->Child);
		child->Parent = relofs;                                   // ... its parent is now thing (i.e. it gets demoted from head of linked list to 2nd in linked list)
	}
	*(mw) = relofs;                                               // Thing is now new head of linked list, thus store its relofs in mapwho

	return true;
}

// Based on function move_off_mapwho() in RGAME.C (but modified to fit our use case)
void remove_thing_from_mapwho(GameData *gamedata, Thing *thing) {
	uint16_t *mw;
	Thing    *parent;
	Thing    *child;

	if (!(thing->Status & TS_MAPWHO)) {                           // If thing is currently NOT on mapwho, there is nothing to do
		return;
	}

	mw = &gamedata->MapWho[POS_TO_MAPWHO_OFS(thing->Xpos, thing->Ypos)];  // Reference to head of linked list in mapwho

	if (thing->Parent != 0) {                                     // Remove thing from linked list (parent side)
		parent = GET_THING_FOR_RELOFS(gamedata, thing->Parent);
		parent->Child = thing->Child;
		thing->Parent = 0;                                        // Was MISSING in original code, but seems like a good idea
	} else {
		*(mw) = thing->Child;                                     // Thing was head of linked list -> child becomes new head
	}

	if (thing->Child != 0) {                                      // Remove thing from linked list (child side)
		child = GET_THING_FOR_RELOFS(gamedata, thing->Child);
		child->Parent = thing->Parent;
		thing->Child = 0;                                         // Was MISSING in original code, but seems like a good idea
	}

	thing->Status &= (~TS_MAPWHO);                                // Clear flag -> thing is no longer on mapwho
}

// Based on function move_mapwho() in RGAME.C (but modified to fit our use case)
bool move_thing_within_mapwho(GameData *gamedata, Thing *thing, int16_t new_xpos, int16_t new_ypos, int16_t new_zpos) {
	int16_t   xtile, ytile;
	uint16_t *mwold, *mwnew;
	Thing    *child;
	Thing    *parent;
	uint16_t  relofs;

	if (!(thing->Status & TS_MAPWHO)) {                           // If thing is currently not on mapwho, thus don't move it (function
		return false;                                             // add_thing_to_mapwho must be used instead to add thing to mapwho)
	}

	xtile = (new_xpos >> 8);                                      // Position to tile (positions are 16 bit -> highest 8 bit == tile,
	ytile = (new_ypos >> 8);                                      // lowest 8 bit == sub-position within tile)

	/*                                                            // Original from RGAME.C, replaced by modified variant below
	if (xtile < MIN_TILE_X)                                       // Below lowest possible tile? -> wrap position around to highest possible tile
		thing->Xpos = MAX_TILE_X * POS_PER_TILE;
	if (ytile < MIN_TILE_Y)
		thing->Ypos = MAX_TILE_Y * POS_PER_TILE;

	if (xtile > MAX_TILE_X)                                       // Above highest possible tile? -> wrap position around to lowest possible tile
		thing->Xpos = MIN_TILE_X * POS_PER_TILE;                  // CAUTION: this was (MIN_TILE_X+1) in RGAME.C (not sure why though)
	if (ytile > MAX_TILE_Y)
		thing->Ypos = MIN_TILE_Y * POS_PER_TILE;                  // CAUTION: this was (MIN_TILE_Y+1) in RGAME.C (not sure why though)
	*/

	if (xtile < MIN_TILE_X)                                       // Below lowest possible tile? -> readjust position to lowest possible tile
		thing->Xpos = MIN_TILE_X * POS_PER_TILE;
	if (ytile < MIN_TILE_Y)
		thing->Ypos = MIN_TILE_Y * POS_PER_TILE;

	if (xtile > MAX_TILE_X)                                       // Above highest possible tile? -> readjust position to highest possible tile
		thing->Xpos = MAX_TILE_X * POS_PER_TILE;
	if (ytile > MAX_TILE_Y)
		thing->Ypos = MAX_TILE_Y * POS_PER_TILE;

	new_zpos &= MAX_ZPOS;                                         // Limit Z position to highest possible value (cutoff)

	mwold = &gamedata->MapWho[POS_TO_MAPWHO_OFS(thing->Xpos, thing->Ypos)];  // Reference to head of linked list in mapwho (at old position)
	mwnew = &gamedata->MapWho[POS_TO_MAPWHO_OFS(new_xpos, new_ypos)];        // Reference to head of linked list in mapwho (at new position)

	if (mwnew != mwold) {                                         // Does the thing actually move within mapwho (i.e. across tile boundaries)?

		if (thing->Parent != 0) {                                 // Remove thing from linked list (parent side)
			parent = GET_THING_FOR_RELOFS(gamedata, thing->Parent);
			parent->Child = thing->Child;
		} else {
			*(mwold) = thing->Child;                              // Thing was head of linked list -> child becomes new head
		}
		if (thing->Child != 0) {                                  // Remove thing from linked list (child side)
			child = GET_THING_FOR_RELOFS(gamedata, thing->Child);
			child->Parent = thing->Parent;
		}

		relofs = GET_RELOFS_FOR_THING(gamedata, thing);
		thing->Parent = 0;                                        // Thing becomes new head of linked list (i.e. no parent)
		thing->Child = *(mwnew);                                  // Child points to what was previously stored in mapwho (i.e. FORMER head of linked list -or- 0)
		if (thing->Child != 0) {                                  // If child actually exists (see if above) ...
			child = GET_THING_FOR_RELOFS(gamedata, thing->Child);
			child->Parent = relofs;                               // ... its parent is now thing (i.e. it gets demoted from head of linked list to 2nd in linked list)
		}
		*(mwnew) = relofs;                                        // Thing is now new head of linked list, thus store its relofs in mapwho

	}

	thing->Xpos = new_xpos;                                       // Apply new position to thing (always needs to be done, even
	thing->Ypos = new_ypos;                                       // if tile boundaries were NOT crossed by move)
	thing->Zpos = new_zpos;

	return true;
}

bool verify_mapwho(const GameData *gamedata) {
	/*
	 * Algorithm:
	 *
	 * 1. Process all entries in MapWho:
	 *    - Each Thing can only appear ONCE within MapWho
	 *    - Each Thing in MapWho must have Parent == 0 (i.e. must be HEAD of linked list)
	 *    - Each Thing in MapWho must have flag STATUS_MAPWHO set (i.e. thing->Status & STATUS_MAPWHO)
	 *    - Recursion: each child of a Thing must have flag STATUS_MAPWHO set (same for each Thing until end of linked list)
	 *      (CAUTION: also detect recursion loops, i.e. break if relofs of starting point appears again)
	 *
	 * 2. Process all Things (across People, Vehicles, Objects, Weapons and Effects):
	 *    - If Thing has flag STATUS_MAPWHO set -AND- has Parent == 0 (i.e. is HEAD of linked list),
	 *      it MUST appear / have an entry in MapWho (and exactly 1, not multiple!)
	 *    - If Thing has NOT flag STATUS_MAPWHO set, it must NOT appear / have an entry in MapWho
	 *      -AND- should not appear in any linked list (PROBLEM: move_thing_off_mapwho does NOT reset
	 *      thing.Parent/thing.Child, thus there will be stale references)
	 *    - Recursion: if a Thing has flag STATUS_MAPWHO set, all its children must have flag set as well (until end of linked list)
	 *      (CAUTION: also detect recursion loops, i.e. break if relofs of starting point appears again)
	 *
	 */
	(void)(gamedata);
	return true;
}

void rebuild_mapwho(GameData *gamedata) {
	/*
	 * Algorithm:
	 *
	 * 1. Clear mapwho (i.e. memset to 0)
	 *
	 * 2. Iterate over all things (i.e. iterate over game data arrays one after the other and cast items to Thing)
	 *
	 * 3. For each thing:
	 *
	 *    If thing has flag TS_MAPWHO/STATUS_MAPWHO set (i.e. belongs on mapwho):
	 *    Determine offset/entry within mapwho, add thing as new head to mapwho and shift existing head to 2nd position
	 *    (-or- simply use add_thing_to_mapwho(), cause that's what it does + adjusts out of bounds positions)
	 *
	 *    If thing has flag TS_MAPWHO/STATUS_MAPWHO NOT set (i.e. does not belong on mapwho):
	 *    Set thing.Child = thing.Parent = 0
	 *    (NOTE: original sources don't do that, but it should be cleaner to remove stale references)
	 *
	 */

	// Clear mapwho completely (i.e. set each entry to 0)
	memset(&gamedata->MapWho, 0, sizeof(gamedata->MapWho));

	// Iterate over all things that may be referenced in mapwho
	// (i.e. People, Vehicles, Objects, Weapons, Effects)
	for (size_t i = 0; i < PEOPLE_COUNT; i++) {
		Thing *thing = (Thing*)(&gamedata->People[i]);
		if (thing->Status & TS_MAPWHO) {
			thing->Status &= (~TS_MAPWHO);                        // Temporarily clear flag TS_MAPWHO to bypass check in add_thing_to_mapwho()
			add_thing_to_mapwho(gamedata, thing);                 // Thing belongs on mapwho, thus add it
			thing->Status |= TS_MAPWHO;                           // Re-set previously cleared flag
		} else {
			thing->Parent = thing->Child = 0;                     // Things does NOT belong on mapwho, thus clear (stale) references
		}
	}
	for (size_t i = 0; i < VEHICLES_COUNT; i++) {                 // Same as above for all other thing categories
		Thing *thing = (Thing*)(&gamedata->Vehicles[i]);
		if (thing->Status & TS_MAPWHO) {
			thing->Status &= (~TS_MAPWHO);
			add_thing_to_mapwho(gamedata, thing);
			thing->Status |= TS_MAPWHO;
		} else {
			thing->Parent = thing->Child = 0;
		}
	}
	for (size_t i = 0; i < OBJECTS_COUNT; i++) {
		Thing *thing = (Thing*)(&gamedata->Objects[i]);
		if (thing->Status & TS_MAPWHO) {
			thing->Status &= (~TS_MAPWHO);
			add_thing_to_mapwho(gamedata, thing);
			thing->Status |= TS_MAPWHO;
		} else {
			thing->Parent = thing->Child = 0;
		}
	}
	for (size_t i = 0; i < WEAPONS_COUNT; i++) {
		Thing *thing = (Thing*)(&gamedata->Weapons[i]);
		if (thing->Status & TS_MAPWHO) {
			thing->Status &= (~TS_MAPWHO);
			add_thing_to_mapwho(gamedata, thing);
			thing->Status |= TS_MAPWHO;
		} else {
			thing->Parent = thing->Child = 0;
		}
	}
	for (size_t i = 0; i < EFFECTS_COUNT; i++) {
		Thing *thing = (Thing*)(&gamedata->Effects[i]);
		if (thing->Status & TS_MAPWHO) {
			thing->Status &= (~TS_MAPWHO);
			add_thing_to_mapwho(gamedata, thing);
			thing->Status |= TS_MAPWHO;
		} else {
			thing->Parent = thing->Child = 0;
		}
	}
}
