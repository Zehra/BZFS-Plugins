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
#include "plugin_utils.h"

class TeamDeathZone : public bz_CustomZoneObject
{
public:
  TeamDeathZone() : bz_CustomZoneObject()
  {
  }

  int team;
};

class TeamDeathZoneSample : public bz_Plugin, bz_CustomMapObjectHandler
{
public:
  virtual const char* Name() { return "TeamDeathZones"; }
  virtual void Init(const char* config);
  virtual void Event(bz_EventData *eventData);
  virtual void Cleanup(void);

  virtual bool MapObject(bz_ApiString object, bz_CustomMapObjectInfo *data);

  std::vector<TeamDeathZone> teamDeathZones;
};

BZ_PLUGIN(TeamDeathZoneSample)

void TeamDeathZoneSample::Init(const char* /*commandLine*/)
{
  Register(bz_ePlayerUpdateEvent);

  bz_registerCustomMapObject("teamdeathzone", this);
}

void TeamDeathZoneSample::Cleanup(void)
{
  Flush();

  bz_removeCustomMapObject("teamdeathzone");
}

bool TeamDeathZoneSample::MapObject(bz_ApiString object, bz_CustomMapObjectInfo *data)
{
  if (object != "TEAMDEATHZONE" || !data)
    return false;

  // The new zone we just found and we'll be storing in our vector of zones
  TeamDeathZone newZone;

  newZone.handleDefaultOptions(data);

  // Loop through the object data
  for (unsigned int i = 0; i < data->data.size(); i++)
  {
    std::string line = data->data.get(i).c_str();

    bz_APIStringList *nubs = bz_newStringList();
    nubs->tokenize(line.c_str(), " ", 0, true);

    if (nubs->size() > 0)
    {
      std::string key = bz_toupper(nubs->get(0).c_str());

      // These are our custom fields in the TeamDeathZone class
      if (key == "TEAM" && nubs->size() > 1)
      {
        newZone.team = (int)atoi(nubs->get(1).c_str());
      }
    }

    bz_deleteStringList(nubs);
  }

  teamDeathZones.push_back(newZone);

  return true;
}

void TeamDeathZoneSample::Event(bz_EventData *eventData)
{
  switch (eventData->eventType)
  {
  case bz_ePlayerUpdateEvent: // This event is called each time a player sends an update to the server
  {
    bz_PlayerUpdateEventData_V1* updateData = (bz_PlayerUpdateEventData_V1*)eventData;

    // Loop through all of our custom zones
    for (unsigned int i = 0; i < teamDeathZones.size(); i++)
    {
      if (teamDeathZones[i].pointInZone(updateData->state.pos))
      {
        // If the player has the flag specified in the zone, send them a message and remove their flag
        if (bz_getPlayerTeam(updateData->playerID) == eRogueTeam && teamDeathZones[i].team == 0)//RogueTeam
        {
          bz_killPlayer(updateData->playerID, false, BZ_SERVER);
        }
        else if (bz_getPlayerTeam(updateData->playerID) == eRedTeam && teamDeathZones[i].team == 1)//RedTeam
        {
          bz_killPlayer(updateData->playerID, false, BZ_SERVER);
        }
        else if (bz_getPlayerTeam(updateData->playerID) == eGreenTeam && teamDeathZones[i].team == 2)//GreenTeam
        {
          bz_killPlayer(updateData->playerID, false, BZ_SERVER);
        }
        else if (bz_getPlayerTeam(updateData->playerID) == eBlueTeam && teamDeathZones[i].team == 3)//BlueTeam
        {
          bz_killPlayer(updateData->playerID, false, BZ_SERVER);
        }
        else if (bz_getPlayerTeam(updateData->playerID) == ePurpleTeam && teamDeathZones[i].team == 4)//PurpleTeam
        {
          bz_killPlayer(updateData->playerID, false, BZ_SERVER);
        }
        else if (bz_getPlayerTeam(updateData->playerID) == eRabbitTeam && teamDeathZones[i].team == 5)//RabbitTeam
        {
          bz_killPlayer(updateData->playerID, false, BZ_SERVER);
        }
        else if (bz_getPlayerTeam(updateData->playerID) == eRabbitTeam && teamDeathZones[i].team == 6)//HunterTeam
        {
          bz_killPlayer(updateData->playerID, false, BZ_SERVER);
        }
      }
    }
  }
  break;

  default: break;
  }
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
