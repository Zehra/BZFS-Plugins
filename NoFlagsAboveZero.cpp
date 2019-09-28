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

class NoFlagsAboveZero : public bz_Plugin
{
public:
  virtual const char* Name() { return "NoFlagsAboveZero"; }
  virtual void Init(const char* /*config*/);
  virtual void Event(bz_EventData *eventData);
  virtual void Cleanup(void);
};

BZ_PLUGIN(NoFlagsAboveZero)

void NoFlagsAboveZero::Init(const char*config)
{
  Register(bz_eAllowFlagGrab);
  bz_debugMessage(1, "NoFlagsAboveZero Plug-in loaded");
}

void NoFlagsAboveZero::Cleanup(void)
{
  Flush(); // Cleanup of all events
  bz_debugMessage(1, "NoFlagsAboveZero Plug-in unloaded");
}

void NoFlagsAboveZero::Event(bz_EventData *eventData)
{
  if (eventData->eventType == bz_eAllowFlagGrab)
  {
    bz_AllowFlagGrabData_V1* flagData = (bz_AllowFlagGrabData_V1*)eventData;
    if (bz_getPlayerWins(flagData->playerID) > bz_getPlayerLosses(flagData->playerID))
      {
        flagData->allow = false; 
      }
  }
}
