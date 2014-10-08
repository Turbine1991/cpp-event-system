/*
   Index expandable vector array.

   Elements are stored contiguously like a vector, placing new elements determines whether or not
   it should expand to accomodate the new element's index value. Useful when avoiding the overhead of
   std list and set.
*/

#pragma once

#include <vector>
#include <algorithm>

template <typename T>
   class PlaceableVector
{
public:
   typedef std::vector<T> vector_t;
   typedef T item_t;
   typedef size_t index_t;
   typedef typename vector_t::iterator iterator;

   PlaceableVector()
   {

   }

   item_t& at(index_t index)
   {
      return contents.at(index);
   }

   item_t& operator[](index_t index)
   {
      return contents[index];
   }

   void place(index_t index, item_t item)
   {
      if (index == contents.size())
      {
         contents.push_back(item);
         return;
      }

      if (index > contents.size())
         contents.resize(index + 1);

      contents.at(index) = item;
   }

   index_t place_back(item_t item)
   {
      contents.push_back(item);
      return contents.size() - 1;
   }

   template <typename... Args>
      void emplace(index_t index, Args... args)
   {
      emplace(contents.front() + index, args...);
   }

   template <typename... Args>
      index_t emplace_back(Args... args)
   {
      emplace(args...);
      return contents.size() - 1;
   }

   iterator begin()
   {
      return contents.begin();
   }

   iterator end()
   {
      return contents.end();
   }

   size_t size()
   {
      return contents.size();
   }

   bool in_bounds(index_t index)
   {
      return index > 0 && index < size();
   }

   void erase(typename vector_t::iterator it)
   {
      contents.erase(it);
   }

private:
   vector_t contents;
};
