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
