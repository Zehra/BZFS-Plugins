/* Kamikaze.cpp
* Copyright (c) 2018 Zehra
*
* This package is free software;  you can redistribute it and/or
* modify it under the terms of the LGPL 2.1 license.
* https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
*
* THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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
