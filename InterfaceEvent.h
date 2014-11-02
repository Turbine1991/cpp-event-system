#pragma once

#include <string>

class InterfaceEvent
{
public:
   typedef std::string name_t;

   virtual name_t getName() = 0;
   virtual bool hasName(name_t name) = 0;
};

