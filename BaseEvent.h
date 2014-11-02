/*
   Generic function delegate handling with associative names (and aliases), management of unique event calls and deduction of return and parameter types when called.

   An event may be disabled or re-enabled by modifying the disabled attribute.
*/

#pragma once

#include <unordered_map>
#include <string>
#include <list>
#include "InterfaceEvent.h"

class BaseEvent: public InterfaceEvent
{
public:
   typedef std::list<name_t> names_t;
   typedef std::string action_name_t;
   typedef std::unordered_map<action_name_t, void*> functs_t;

   bool disabled;

   BaseEvent(name_t name = "");
   name_t getName();
   bool hasName(name_t name);
   const names_t& getNames();
   void add(action_name_t actionName, void* funct, bool append = true);
   void replace(action_name_t actionName, void* funct);
   bool exists(action_name_t actionName);
   bool remove(action_name_t actionName);
   void clear();
   virtual bool canCall();

   template <typename... Args>
      void addAlias(Args... args);

protected:
   functs_t functs;

private:
   names_t names;
};

///Public
template <typename... Args>
   void BaseEvent::addAlias(Args... args)
{
   names.insert(names.end(), {args...});
}
