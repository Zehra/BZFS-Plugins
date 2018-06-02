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
