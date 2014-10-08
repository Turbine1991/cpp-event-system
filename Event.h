/*
   Derivable event object for use in a derived "events" class.

   Upon creation is associated with a event identifier.
*/

#pragma once

#include "BaseEvent.h"

template <typename T = void>
   class Event: public BaseEvent
{
public:
   typedef T return_t;

   Event(name_t name = "");
   template <typename... Args>
      return_t call(Args... args);
};

///Public
template <typename T>
   Event<T>::Event(name_t name): BaseEvent(name)
{

}

template <>
   template <typename... Args>
      typename Event<bool>::return_t Event<bool>::call(Args... args)
{
   typedef return_t (*funct_t)(Args...);

   if (!canCall())
      return false;

   funct_t funct;
   for(functs_t::value_type& pair: functs)
   {
      funct = (funct_t)pair.second;
      if (!funct(args...)) //Block
         return false;
   }

   return true;
}

template <typename T>
   template <typename... Args>
      typename Event<T>::return_t Event<T>::call(Args... args)
{
   typedef return_t (*funct_t)(Args...);

   if (disabled)
      return;

   funct_t funct;
   for(functs_t::value_type& pair: functs)
   {
      funct = (funct_t)pair.second;
      funct(args...);
   }
}
