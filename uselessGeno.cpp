// uselessGeno.cpp : uselessGeno plug-in

#include "bzfsAPI.h"
#define genoType "US"
//^ If another flag is wished to be used, we simply change this and rename plug-in.

class uselessGeno : public bz_Plugin
{
public:
  virtual const char* Name() { return "uselessGeno"; }
  virtual void Init(const char* /*config*/);
  virtual void Event(bz_EventData *eventData);
  virtual void Cleanup(void);
  // Setting defaults.
  bool rogueGeno = false;
  bool genoOnce = false;
  bool teamSafety = false;
};

BZ_PLUGIN(uselessGeno)

void uselessGeno::Init(const char* commandLine) {
  char active = '1';
  char cmdInfo[7] = { "" }; //Blank array
  strcpy(cmdInfo, commandLine);

  if (cmdInfo[0] == active) {
    rogueGeno = true;
  }
  else {
    rogueGeno = false;
  }

  if (cmdInfo[1] == active) {
    genoOnce = true;
  }
  else {
    genoOnce = false;
  }

  if (cmdInfo[2] == active) {
    teamSafety = true;
  }
  else {
    teamSafety = false;
  }

  if (rogueGeno == false) {
    bz_debugMessage(0, "Rogue Geno off");
  }
  else {
    bz_debugMessage(0, "Rogue Geno on");
  }

  if (genoOnce == false) {
    bz_debugMessage(0, "Geno once off");
  }
  else {
    bz_debugMessage(0, "Geno once on");
  }

  if (teamSafety == true) {
    bz_debugMessage(0, "team safety on");
  }
  else {
    bz_debugMessage(0, "team safety off");
  }

  Register(bz_eFlagGrabbedEvent);
  Register(bz_ePlayerDieEvent);
}

void uselessGeno::Cleanup(void) {
  Flush();
}

void uselessGeno::Event(bz_EventData *eventData) {

  if (eventData->eventType == bz_ePlayerDieEvent) {
    bz_PlayerDieEventData_V1 *deathData = (bz_PlayerDieEventData_V1*)eventData;
    if ((deathData->flagKilledWith == genoType) && (deathData->playerID != deathData->killerID)) {
      if (((bz_getPlayerTeam(deathData->killerID) != eRogueTeam) && (bz_getPlayerTeam(deathData->playerID) == eRogueTeam) && (teamSafety == true) && (rogueGeno == true)) || ((bz_getPlayerTeam(deathData->killerID) == eRogueTeam) && (bz_getPlayerTeam(deathData->playerID) == eRogueTeam) && (teamSafety == false) && (rogueGeno == true)) || (bz_getPlayerTeam(deathData->killerID) != bz_getPlayerTeam(deathData->playerID)) || teamSafety == false && (bz_getPlayerTeam(deathData->killerID) == bz_getPlayerTeam(deathData->playerID))) {
        // ((bz_getPlayerTeam(deathData->killerID) != eRogueTeam) && (bz_getPlayerTeam(deathData->playerID) == eRogueTeam) && (teamSafety == true) && (rogueGeno == true))
        // ((bz_getPlayerTeam(deathData->killerID) == eRogueTeam) && (bz_getPlayerTeam(deathData->playerID) == eRogueTeam) && (teamSafety == false) && (rogueGeno == true))
          bz_APIIntList *player_list = bz_newIntList();
          bz_getPlayerIndexList(player_list);

          for (unsigned int i = 0; i < player_list->size(); i++) {
            if (bz_getPlayerTeam(player_list->get(i)) == bz_getPlayerTeam(deathData->playerID)) {
              bz_killPlayer((player_list->get(i)), false, deathData->killerID, genoType);
            }
          }
          bz_deleteIntList(player_list);

          if (genoOnce == true) { // Check and remove flag, if geno once is true
            bz_removePlayerFlag(deathData->killerID);
          }
      }
    }
  }

  if (eventData->eventType == bz_eFlagGrabbedEvent) {
    bz_FlagGrabbedEventData_V1 *flagGrab = (bz_FlagGrabbedEventData_V1*)eventData;
    if (strcmp(genoType, flagGrab->flagType) == 0) { // See if they grab 'genoType' (Useless flag).
      bz_sendTextMessage(BZ_SERVER, flagGrab->playerID, "You have grabbed Useless Geno"); // Notify player on grab
    }
  }
}
