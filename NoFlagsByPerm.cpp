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

class NoFlagsByPerm : public bz_Plugin
{
public:
  virtual const char* Name() { return "NoFlagsByPerm"; }
  virtual void Init(const char* /*config*/);
  virtual void Event(bz_EventData *eventData);
  virtual void Cleanup(void);
};

BZ_PLUGIN(NoFlagsByPerm)

void NoFlagsByPerm::Init(const char*config)
{
  Register(bz_eAllowFlagGrab);
  bz_debugMessage(1, "NoFlagsByPerm Plug-in loaded");
}

void NoFlagsByPerm::Cleanup(void)
{
  Flush(); // Cleanup of all events
  bz_debugMessage(1, "NoFlagsByPerm Plug-in unloaded");
}

void NoFlagsByPerm::Event(bz_EventData *eventData)
{
  switch (eventData->eventType)
  {
  case bz_eAllowFlagGrab:
  {
    bz_AllowFlagGrabData_V1* flagData = (bz_AllowFlagGrabData_V1*)eventData;
    if (bz_hasPerm(flagData->playerID, "FLAGLESS") && !bz_hasPerm(flagData->playerID, "FLAGS"))
    {
      flagData->allow = false;
    }
  }
  break;
  }
}
