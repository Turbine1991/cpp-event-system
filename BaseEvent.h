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
   typedef std::string unique_name_t;
   typedef std::unordered_map<unique_name_t, void*> functs_t;

   bool disabled;

   BaseEvent(name_t eventName = "");
   name_t getName();
   bool hasName(name_t eventName);
   const names_t& getNames();
   void add(unique_name_t uniqueName, void* funct, bool append = true);
   void replace(unique_name_t uniqueName, void* funct);
   bool exists(unique_name_t uniqueName);
   bool remove(unique_name_t uniqueName);
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
