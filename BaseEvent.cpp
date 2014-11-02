#include <assert.h>
#include <algorithm>
#include "BaseEvent.h"

using namespace std;

///Public
BaseEvent::BaseEvent(name_t name): disabled(false)
{
   names.push_back(name);
}

BaseEvent::name_t BaseEvent::getName()
{
   return names.front();
}

bool BaseEvent::hasName(name_t name)
{
   return std::find(names.begin(), names.end(), name) != names.end();
}

const BaseEvent::names_t& BaseEvent::getNames()
{
   return names;
}

void BaseEvent::add(action_name_t actionName, void* funct, bool append)
{
   assert(funct != NULL);

   if (!append)
      clear();

   functs.insert(std::make_pair(actionName, funct));
}

void BaseEvent::replace(action_name_t actionName, void* funct)
{
   assert(funct != NULL);

   if (exists(actionName))
      functs[actionName] = funct;
}

bool BaseEvent::exists(action_name_t actionName)
{
   return functs.find(actionName) != functs.end();
}

bool BaseEvent::remove(action_name_t actionName)
{
   functs_t::iterator it = functs.find(actionName);
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
