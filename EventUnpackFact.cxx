
// EVENT UNPACK FACTORY - implementation
// management of UNPACK step

#include "EventUnpackFact.h"

//***********************************************************
// Constructor

EventUnpackFact::EventUnpackFact(const Text_t * name)
: TGo4EventServerFactory(name)
{
}

//***********************************************************
// Default constructor

EventUnpackFact::EventUnpackFact() 
: TGo4EventServerFactory("DESPEC Event Factory")
{ 
}

//***********************************************************
// Default destructor

EventUnpackFact::~EventUnpackFact() 
{ 
}
//***********************************************************

//-----------------------------------------------------------

TGo4EventProcessor * EventUnpackFact::CreateEventProcessor(TGo4EventProcessorParameter* par)
{ 
   EventUnpackProc* proc = new EventUnpackProc("EventUnpackProc");
   return proc;
}

//-----------------------------------------------------------

TGo4EventElement * EventUnpackFact::CreateOutputEvent()
{ // name is given in EventUnpackStore
   EventUnpackStore * event = new EventUnpackStore();
   SetOutputEvent(event); // important for some event store implementations
   
   return event;
}

//-----------------------------------------------------------
ClassImp(EventUnpackFact)

