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

// Kamikaze.cpp : Defines the entry point for the DLL application.

#include "bzfsAPI.h"
bool KamikazePlayer[256] = { 0 };

class Kamikaze : public bz_Plugin, bz_CustomSlashCommandHandler
{
public:
  virtual const char* Name() { return "Kamikaze"; }
  virtual void Init(const char* config);
  virtual void Event(bz_EventData *eventData);
  virtual void Cleanup(void);
  virtual bool SlashCommand(int playerID, bz_ApiString command, bz_ApiString message, bz_APIStringList* params);
};

BZ_PLUGIN(Kamikaze)

void Kamikaze::Init(const char* /*commandLine*/)
{
  bz_debugMessage(4, "Kamikaze plugin loaded");

  // Register our events
  bz_registerCustomSlashCommand("sk", this);
  Register(bz_eShotFiredEvent);
}

void Kamikaze::Event(bz_EventData *eventData)
{
    if (eventData->eventType != bz_eShotFiredEvent)
      return;

    bz_ShotFiredEventData_V1 *shotData = (bz_ShotFiredEventData_V1*)eventData;

  if (KamikazePlayer[shotData->playerID] == 1)
  {
    // Fire a shockwave where the player fired their weapon
    float vector[3] = { 0, 0, 0 };
    bz_fireServerShot("SW", shotData->pos, vector);
    KamikazePlayer[shotData->playerID] = 0;
  }
}

bool Kamikaze::SlashCommand(int playerID, bz_ApiString command, bz_ApiString message, bz_APIStringList* params)
{
  if (command == "sk")
  {
    KamikazePlayer[playerID] = 1; //activate kamikaze
    bz_sendTextMessage(BZ_SERVER, playerID, "Next shot triggers kamikaze");
  }
  return true;
}

void Kamikaze::Cleanup(void)
{
  bz_removeCustomSlashCommand("sk");
  Flush();
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
