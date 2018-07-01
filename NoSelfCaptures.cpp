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

// NoSelfCaptures.cpp : This plug-in prevents self-captures in CTF maps.

#include "bzfsAPI.h"

class NoSelfCaptures : public bz_Plugin
{
  virtual const char* Name() { return "NoSelfCaptures"; }
  virtual void Init(const char* /*config*/);
  virtual void Event(bz_EventData *eventData);
  virtual void Cleanup(void);
public:
};

BZ_PLUGIN(NoSelfCaptures)

void NoSelfCaptures::Init(const char*config)
{
  Register(bz_eAllowCTFCaptureEvent);
}

void NoSelfCaptures::Cleanup(void)
{
  Flush();
}

void NoSelfCaptures::Event(bz_EventData *eventData)
{
  switch (eventData->eventType)
  {
    case bz_eAllowCTFCaptureEvent:
    {
      bz_AllowCTFCaptureEventData_V1 *capData = (bz_AllowCTFCaptureEventData_V1*)eventData;
      if (bz_getPlayerTeam(capData->playerCapping) == capData->teamCapped)
      {
        capData->allow = false;
      }
      else capData->allow = true;
    }break;
  }
}
