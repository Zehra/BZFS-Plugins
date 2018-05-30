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
  switch (eventData->eventType)
  {
  case bz_eAllowFlagGrab:
  {
    bz_AllowFlagGrabData_V1* flagData = (bz_AllowFlagGrabData_V1*)eventData;
    if (bz_getPlayerWins(flagData->playerID) > bz_getPlayerLosses(flagData->playerID)) { flagData->allow = false; }
  }
  break;
  }
}
