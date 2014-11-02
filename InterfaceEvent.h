#pragma once

#include <string>

class InterfaceEvent
{
public:
   typedef std::string name_t;

   virtual name_t getEventName() = 0;
   virtual bool hasEventName(name_t eventName) = 0;
};

