/*
 *  Copyright (C) 2018 Zehra
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option) any
 * later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this library; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#include "bzfsAPI.h"
#include <map>

class NoRogueCTF : public bz_Plugin
{
public:
	virtual const char* Name() { return "NoRogueCTF"; }
	virtual void Init(const char* config);

	virtual void Event(bz_EventData *eventData);
};

BZ_PLUGIN(NoRogueCTF)

void NoRogueCTF::Init(const char* /*commandLine*/)
{
	Register(bz_eAllowFlagGrab);
}


void NoRogueCTF::Event(bz_EventData *eventData)
{
	if (eventData->eventType == bz_eAllowFlagGrab)
	{
		bz_AllowFlagGrabData_V1* data = (bz_AllowFlagGrabData_V1*)eventData;

		// Fetch the player record to check if they are a global user
		bz_BasePlayerRecord *player = bz_getPlayerByIndex(data->playerID);

		// Put the flag name into an easy-to-test variable type.
		bz_ApiString flagAbbrev = bz_getFlagName(data->flagID);

		// check teams and disallow team flags for them
		if (bz_getPlayerTeam(player->playerID) == eRogueTeam && (flagAbbrev == "R*" || flagAbbrev == "G*" || flagAbbrev == "B*" || flagAbbrev == "P*"))
		{
			data->allow = false;
		}

		// Free the player record
		bz_freePlayerRecord(player);
	}
	return;
}
