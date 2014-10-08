#include <assert.h>
#include <algorithm>
#include "BaseEvent.h"

using namespace std;

///Public
BaseEvent::BaseEvent(name_t eventName): disabled(false)
{
   names.push_back(eventName);
}

BaseEvent::name_t BaseEvent::getEventName()
{
   return names.front();
}

bool BaseEvent::hasEventName(name_t eventName)
{
   return std::find(names.begin(), names.end(), eventName) != names.end();
}

const BaseEvent::names_t& BaseEvent::getEventNames()
{
   return names;
}

void BaseEvent::add(unique_name_t uniqueName, void* funct, bool append)
{
   assert(funct != NULL);

   if (!append)
      clear();

   functs.insert(std::make_pair(uniqueName, funct));
}

void BaseEvent::replace(unique_name_t uniqueName, void* funct)
{
   assert(funct != NULL);

   if (exists(uniqueName))
      functs[uniqueName] = funct;
}

bool BaseEvent::exists(unique_name_t uniqueName)
{
   return functs.find(uniqueName) != functs.end();
}

bool BaseEvent::remove(unique_name_t uniqueName)
{
   functs_t::iterator it = functs.find(uniqueName);
   if (it == functs.end())
      return false;

   functs.erase(it);

   return true;
}

void BaseEvent::clear()
{
   functs.clear();
}

bool BaseEvent::canCall()
{
   return !disabled;
}
