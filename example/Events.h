#pragma once

#include "../BaseEvents.h"
#include "Event.h"

class Events: public BaseEvents <Event<bool>>
{
public:
   enum event_e { RESERVED, CAN_CLIENT_CONNECT };
};
