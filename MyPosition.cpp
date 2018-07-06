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

class MyPosition : public bz_Plugin, bz_CustomSlashCommandHandler
{
public:
  virtual const char* Name() { return "MyPosition"; }
  virtual void Init(const char* /*config*/);
  virtual void Event(bz_EventData * /* eventData */) { return; }
  virtual void Cleanup(void);
  virtual bool SlashCommand(int playerID, bz_ApiString command, bz_ApiString message, bz_APIStringList* params);
};

BZ_PLUGIN(MyPosition)

void MyPosition::Init(const char*config) {
  bz_registerCustomSlashCommand ( "mypos", this );
}

void MyPosition::Cleanup(void) {
  bz_removeCustomSlashCommand ( "mypos" );
  Flush();
}

bool MyPosition::SlashCommand(int playerID, bz_ApiString command, bz_ApiString message, bz_APIStringList* params) {
  if (!strcmp("mypos", command.c_str())) {
    bz_BasePlayerRecord *pr = bz_getPlayerByIndex(playerID);
    if (pr) {
      if (pr->team != eObservers) {
        float pos0 = pr->lastKnownState.pos[0];
        float pos1 = pr->lastKnownState.pos[1];
        float pos2 = pr->lastKnownState.pos[2];
        //float rotation = pr->lastKnownState.rotation;

        //bz_sendTextMessagef(BZ_SERVER, playerID, "X Position: %f, Y Position: %f, Z Position: %f, Rotation: %f", pos0, pos1, pos2, rotation);
        bz_sendTextMessagef(BZ_SERVER, playerID, "X Position: %f, Y Position: %f, Z Position: %f", pos0, pos1, pos2);
        }
      }
    bz_freePlayerRecord(pr);
  }
  return true;
}

// Local Variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
