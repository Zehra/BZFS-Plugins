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

class PlaceHolder : public bz_Plugin
{
public:
  virtual const char* Name() { return "PlaceHolder"; }
  virtual void Init(const char* config);
  virtual void Event(bz_EventData * /* eventData */) { return; }
  virtual void Cleanup(void);
};

void PlaceHolder::Cleanup(void)
{
  Flush();
  bz_debugMessage(4, "PlaceHolder plugin unloaded");
}

BZ_PLUGIN(PlaceHolder)

void PlaceHolder::Init(const char* /*commandLine*/)
{
  bz_debugMessage(4, "PlaceHolder plugin loaded");
  bz_RegisterCustomFlag("PH", "Place Holder", "A flag which takes the place of others, but this one is bad.", 0, eBadFlag);
}

// Local Variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
