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
