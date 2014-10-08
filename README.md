cpp-event-system
================

GCC supported C++ extensible hook system. Providing an implementation for generic delegates and the handling of these as associative events. Designed as a C++ equivalent to the hook functionality found in Garry's Mod.

Why use an event/hook system? It decouples and simplifies code complexity while promoting modular characteristics. Another defining benefit is enabling developers the ability to provide version redundant compatibility. Any event may be overwritten, replaced, disabled, aliased and invoked.

##Methods

###Events
Statement     | Return Type
------------- | -------------
events.create(eventName, eventId = 0)|Event&
events.get(eventName or eventId)|Event&
events.exists(eventName or eventId)|bool

###Event
Statement     | Return Type
------------- | -------------
event(name = "")|constructor
event.hasName(name_t name)|bool
event.getNames()|const list<name_t>&
event.add(name, funct, append = true)|void
event.replace(name, funct)|void
event.exists(name)|bool
event.remove(name)|bool
event.clear(eventName or eventId)|void

##Example
```
#include <iostream>
#include "Events.h"

using namespace std;
```
...
```
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
```
...
```
Events::event_t& event = Events.create("CAN_CLIENT_CONNECT", Events::CAN_CLIENT_CONNECT);
Events.exists("CAN_CLIENT_CONNECT");
Events.get(Events::CAN_CLIENT_CONNECT);

event.add("test1", (void*)CanPrint1);
event.add("test2", (void*)CanPrint2);

if (event.call(5))
  cout << "Can Print" << endl;

event.remove("test2");
event.exists("test3");
event.clear();
event.disabled = false;
event.replace("test1", Test2);*
```

##More
Please see the example .cpp file and Code::Blocks .cbp project for a compilable GCC and VSC++ example. Additionally includes enabling wide char support and iterating through contents.
