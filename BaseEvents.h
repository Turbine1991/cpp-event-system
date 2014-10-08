/*
   Event System - 1.00
   You are free to use this however you wish.

   If you find a bug, please attept to debug the cause.
   Post your environment details and the cause or fix in the issues section of GitHub.

   Written by Turbine.

   Website:
   https://github.com/Turbine1991/cpp-event-system

   Provides a base for the creation, association and retrieving of events.
*/

#pragma once

#include <assert.h>
#include <stdint.h>
#include "PlaceableVector.h"

template <typename T>
   class BaseEvents
{
public:
   typedef uint16_t event_id_t;
   typedef T event_t;
   typedef PlaceableVector<event_t*> all_t;
   typedef typename event_t::name_t event_name_t;

   BaseEvents();
   ~BaseEvents();
   template <typename... Args>
      event_t& create(event_name_t name, event_id_t eventId, Args... args);
   event_t& get(event_id_t eventId);
   event_t& get(event_name_t eventName);
   bool exists(event_id_t eventId);
   bool exists(event_name_t eventName);
   all_t& getAll();

protected:
   template <typename U>
      typename U::iterator find(U& data, event_name_t eventName);
   typename all_t::iterator find(event_name_t eventName);
   bool exists(typename all_t::iterator it);
   void place(event_t* event, event_id_t eventId = 0);

private:
   all_t all;
};

///Public
template <typename T>
   BaseEvents<T>::BaseEvents()
{
   all.place_back(NULL); //Reserve 0
}

template <typename T>
   BaseEvents<T>::~BaseEvents()
{
   for (auto it = all.begin(); it != all.end(); it++)
   {
      delete *it;
   }
}


template <typename T>
   template <typename... Args>
      typename BaseEvents<T>::event_t& BaseEvents<T>::create(event_name_t eventName, event_id_t eventId, Args... args)
{
   assert(!exists(eventName));

   event_t* event = new event_t(eventName, args...);
   place(event, eventId);

   return *event;
}

template <typename T>
   typename BaseEvents<T>::event_t& BaseEvents<T>::get(event_id_t eventId)
{
   event_t* event = all.at(eventId);
   assert(eventId != 0 && event != NULL);
   return *event;
}

template <typename T>
   typename BaseEvents<T>::event_t& BaseEvents<T>::get(event_name_t eventName)
{
   typename all_t::iterator it = find(eventName);
   assert(exists(it));
   return **it;
}

template <typename T>
   bool BaseEvents<T>::exists(event_id_t eventId)
{
   if (!all.in_bounds(eventId))
      return false;

   return all.at(eventId) != NULL;
}

template <typename T>
   bool BaseEvents<T>::exists(event_name_t eventName)
{
   return exists(find(eventName));
}

///Protected
template <typename T>
   template <typename U>
      typename U::iterator BaseEvents<T>::find(U& data, event_name_t eventName)
{
   return std::find_if(data.begin(), data.end(), [eventName] (event_t* event)
   {
      if (event == NULL)
         return false;

      return event->hasEventName(eventName);
   });
}

template <typename T>
   typename BaseEvents<T>::all_t::iterator BaseEvents<T>::find(event_name_t eventName)
{
   return find(all, eventName);
}

template <typename T>
   bool BaseEvents<T>::exists(typename all_t::iterator it)
{
   return it != all.end();
}

template <typename T>
   typename BaseEvents<T>::all_t& BaseEvents<T>::getAll()
{
   return all;
}

template <typename T>
   void BaseEvents<T>::place(event_t* event, event_id_t eventId)
{
   assert(event != NULL);

   if (eventId == 0)
      all.place_back(event);
   else
      all.place(eventId, event);
}
