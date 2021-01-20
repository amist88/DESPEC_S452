#ifndef AIDA_EVENT_H_
#define AIDA_EVENT_H_

//#include "Events.h"
#include "Raw_Event.h"
#define AIDA_EVENT_ADC 3
#define AIDA_EVENT_INFO 2
#include "AIDA_Decay_Event_Store.h"
#include "TGo4EventElement.h"

class AIDA_Event: public TGo4EventElement {
    private:

    int am_fired;
    double energy_tot;
   // inline void set_DATA(Raw_Event*);
    
    public:
        AIDA_Event() : TGo4EventElement() {}
        AIDA_Event(const char* name): TGo4EventElement(name) {}
        virtual ~AIDA_Event(){};
       
        
        virtual void Clear(Option_t *t="");
        
        AidaEvent EventAida;
      //  AidaEvent Andrew;
//         int ID = 0;
//         bool HighEnergy;
//   int Module;
//   int ADC;
//   int Channel;
//   int Data;
//   int64_t Time;
//   int64_t FastTime; // time of last fast discriminator  for this channel
// 
//   /* Mapped to DSSD */
//   int DSSD;
//   int Side;
//   int Strip;
//   int Intensity; /* ADC Data corrected for polarity */
//   double Energy;
 

 ClassDef(AIDA_Event,1)
};

#endif /* AIDA_EVENT_H_ */
