#include "AIDA_Event.h"



// AIDA_Event::AIDA_Event(int* positions_tmp,int length,Raw_Event* RAW) : Events(positions_tmp,length){
//     set_DATA(RAW);
//    
// }

void AIDA_Event::Clear(Option_t *t)
{
   EventAida.Zero();

//    ID = 0;
//    ID = 0;
//   HighEnergy = false;
//   Module = 0;
//   ADC = 0;
//   Channel = 0;
//   Data = 0;
//   Time = 0;
//   DSSD = 0;
//   Side = 0;
//   Strip = 0;
//   Intensity = 0;
//   Energy = 0;
}
//---------------------------------------------------------------

// AIDA_Event::~AIDA_Event() {
// 
// }

//---------------------------------------------------------------

// inline void AIDA_Event::set_DATA(Raw_Event* RAW){
//     AIDA_DataStruct* EventAida=RAW->PassAIDA();
// }

