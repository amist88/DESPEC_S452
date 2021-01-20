
// DESPEC EVENT UNPACK FACTORY - definition
// management of UNPACK step

#ifndef EVENTUNPACKFACT_H
#define EVENTUNPACKFACT_H

#include "Go4EventServer/Go4EventServer.h"
#include "EventUnpackStore.h"
#include "EventUnpackProc.h"
#include "Go4EventServer/TGo4EventServerFactory.h"

class EventUnpackStore;

class EventUnpackFact : public TGo4EventServerFactory {
   public:
      virtual TGo4EventElement   * CreateOutputEvent();
      virtual TGo4EventProcessor * CreateEventProcessor(TGo4EventProcessorParameter* par);
      EventUnpackFact();
      EventUnpackFact(const Text_t * name);
      virtual ~EventUnpackFact();

ClassDef(EventUnpackFact,1)     
};
#endif 

