
#ifndef DETECTOR_SYSTEM_H
#define DETECTOR_SYSTEM_H 

#include "Raw_Event.h"


#include <string>

// Go4 Includes //
#include "TGo4UserException.h"
#include "TGo4Picture.h"
#include "TGo4MbsEvent.h"

#include "TFRSParameter.h"
#include "TGo4EventProcessor.h"


class Detector_System{

public:

    virtual ~Detector_System(){};

    virtual void Process_MBS(int*) = 0;
    
    virtual void Process_MBS(TGo4MbsSubEvent*) = 0;

    virtual void get_Event_data(Raw_Event*) = 0;
    
  //  virtual void get_parameters(TGo4EventProcessor*) =0;

//    virtual void get_Event_data(Data_Stream*) = 0;


    virtual int* get_pdata() = 0;


	virtual bool calibration_done() = 0;

	//virtual void write() = 0;
	
	 virtual bool do_gain_matching(int ts_ns) = 0;
   virtual unsigned long next_ts_for_update() = 0;
	///virtual void set_Gain_Match_Filename(std::string) = 0;
};

#endif
