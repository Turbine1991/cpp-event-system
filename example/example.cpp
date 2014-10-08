#include <iostream>
#include "../Events.h"

using namespace std;

bool CanPrint1(int a);
bool CanPrint2(int a);

int main()
{
   ///Declare & Initialise
   Events events;
   Events::event_t& event = events.create("CAN_CLIENT_CONNECT", Events::CAN_CLIENT_CONNECT);

   ///Methods
   events.exists("CAN_CLIENT_CONNECT");
   events.get(Events::CAN_CLIENT_CONNECT);

   event.add("test1", (void*)CanPrint1);
   event.add("test2", (void*)CanPrint2);

   if (event.call(5))
     cout << "Can Print" << endl;

   event.remove("test2");
   event.exists("test3");
   event.clear();
   event.disabled = false;
   event.replace("test1", (void*)CanPrint2);

   return EXIT_SUCCESS;
}

bool CanPrint1(int a)
{
  cout << "Test 1 " << a << endl;
  return true;
}

bool CanPrint2(int a)
{
  cout << "Test 2 " << a << endl;
  return true;
}
