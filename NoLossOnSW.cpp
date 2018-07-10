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

class NoLossOnSW : public bz_Plugin
{
public:
  virtual const char* Name() { return "NoLossOnSW"; }
  virtual void Init(const char* /*config*/);
  virtual void Event(bz_EventData *eventData);
  virtual void Cleanup(void);
};

BZ_PLUGIN(NoLossOnSW)

void NoLossOnSW::Init(const char*config) {
  Register(bz_ePlayerDieEvent);
}

void NoLossOnSW::Cleanup(void) {
  Flush();
}

void NoLossOnSW::Event(bz_EventData *eventData) {
  if (eventData->eventType == bz_ePlayerDieEvent) {
    bz_PlayerDieEventData_V2 *deathData = (bz_PlayerDieEventData_V2*)eventData;
    if (deathData->flagKilledWith == "SW") {
      bz_incrementPlayerLosses(deathData->playerID, -1);
    }
  }
}

// Local Variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
