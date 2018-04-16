#include "bzfsAPI.h"
#include "plugin_utils.h"

class RaceMode : public bz_Plugin, bz_CustomSlashCommandHandler
{
public:
	virtual const char* Name() { return "RaceMode"; }
	virtual void Init(const char* config);
	virtual void Cleanup(void);
	virtual bool SlashCommand(int playerID, bz_ApiString command, bz_ApiString message, bz_APIStringList* params);
	virtual void Event(bz_EventData *eventData);
	bool  RaceModeActive = false;
};

BZ_PLUGIN(RaceMode)

void RaceMode::Init(const char* /*commandLine*/)
{
	bz_registerCustomSlashCommand("startrace", this);
	bz_registerCustomSlashCommand("stoprace", this);
	Register(bz_eSlashCommandEvent);
	Register(bz_eCaptureEvent);
	bz_debugMessage(4, "RaceMode plugin loaded");
}


void RaceMode::Cleanup(void)
{
	Flush();
	bz_removeCustomSlashCommand("startrace");
	bz_removeCustomSlashCommand("stoprace");
	bz_debugMessage(4, "RaceMode plugin unloaded");
}

bool RaceMode::SlashCommand(int playerID, bz_ApiString command, bz_ApiString message, bz_APIStringList* params)
{
	if ((command == "startrace") && !bz_hasPerm(playerID, "RACEMOD"))
	{
		bz_sendTextMessagef(BZ_SERVER, playerID, "You do not have permission to start a race");
		return true;
	}
	else if ((command == "startrace") && bz_hasPerm(playerID, "RACEMOD"))
	{
		RaceModeActive = true;
		bz_sendTextMessagef(BZ_SERVER, playerID, "RaceMode has been activated");
		bz_sendTextMessagef(BZ_SERVER, BZ_ALLUSERS, "The race has started.");
		return true;
	}
	if ((command == "stoprace") && !bz_hasPerm(playerID, "RACEMOD"))
	{
		bz_sendTextMessagef(BZ_SERVER, playerID, "You do not have permission to stop a race");
		return true;
	}
	else if ((command == "stoprace") && bz_hasPerm(playerID, "RACEMOD"))
	{
		RaceModeActive = false;
		bz_sendTextMessagef(BZ_SERVER, playerID, "RaceMode has been turned off");
		bz_sendTextMessagef(BZ_SERVER, BZ_ALLUSERS, "The race has been stopped");
		return true;
	}
	return false;
}

void RaceMode::Event(bz_EventData *eventData)
{
	switch (eventData->eventType)
	{
	case bz_eCaptureEvent: // This event is called each time a team's flag has been captured
	{
		bz_CTFCaptureEventData_V1* captureData = (bz_CTFCaptureEventData_V1*)eventData;
		{
			if (captureData->teamCapping == eRedTeam && (RaceModeActive == true))
			{
				bz_sendTextMessage(BZ_SERVER, BZ_ALLUSERS, "Red team wins");
				bz_gameOver(captureData->playerCapping, captureData->teamCapping);
			}
			else if (captureData->teamCapping == eGreenTeam && (RaceModeActive == true))
			{
				bz_sendTextMessage(BZ_SERVER, BZ_ALLUSERS, "Green team wins");
				bz_gameOver(captureData->playerCapping, captureData->teamCapping);
			}
			else if (captureData->teamCapping == eBlueTeam && (RaceModeActive == true))
			{
				bz_sendTextMessage(BZ_SERVER, BZ_ALLUSERS, "Blue team wins");
				bz_gameOver(captureData->playerCapping, captureData->teamCapping);
			}
			else if (captureData->teamCapping == ePurpleTeam && (RaceModeActive == true))
			{
				bz_sendTextMessage(BZ_SERVER, BZ_ALLUSERS, "Purple team wins");
				bz_gameOver(captureData->playerCapping, captureData->teamCapping);
			}
			else

				return;
		}
	}
	break;
	default: break;
	}
}
