#ifndef AIDA_DETECTOR_SYSTEM_H
#define AIDA_DETECTOR_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include <stdlib.h>
#include <cstdlib>

#include "TROOT.h"
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include "TCutG.h"
#include "TArc.h"
#include "TTree.h"
#include "TH1.h"
#include "AIDA_Headers.h"
#include "AIDA_Event.h"
#include "AIDA_Data_Types.h"
#include "TGo4MbsEvent.h"
#include "EventUnpackStore.h"
#include "AIDA_Decay_Event_Store.h"
#include "TGo4Analysis.h"

#include "Detector_System.cxx"



typedef unsigned long long ULong64_t;

class AIDA_Detector_System : public Detector_System
{
private:

  int Hits;
  double* Energy;
  int* FEE_ID;
  int* Ch_ID;
  ULong64_t* Time;
  ULong64_t* FastTime;
  bool* HighE_veto;
  int* Side;
  int* Strip;
  int* EvtID;
  int* AdcData;
  std::vector<AidaScaler> ScalerData;

  Int_t* pdata;
  Int_t* pdata_start;
  Int_t lwords;
  Int_t sub_evt_length;

  std::vector<std::array<int, 64>> adcOffsets;
  std::vector<int> adcTimeOffsets;
  std::vector<uint64_t> oldtime_d;
  std::vector<uint64_t> upperTime48_d;
  std::vector<uint64_t> upperTime63_d;
  std::vector<std::array<uint64_t, 64>> discriminatorTimes;
  std::vector<uint64_t> scaler;

  Int_t* pMbsData;
  Int_t* pMbsEnd;


  uint64_t oldtime;
  uint64_t upperTime48;
  uint64_t upperTime63;

  UnpackProcStats stats;
  std::vector<UnpackProcStats> stats_d;
  std::vector<uint64_t> pauseTimes;
  int pausedCounter;
  uint64_t totalPauseTime;
  uint64_t GetTime(uint64_t lowTS);
  uint64_t GetTime_d(int fee, uint64_t lowTS);

  bool BuildAIDAEvent(TGo4MbsSubEvent* psubevt, Int_t word1, Int_t word2);
  bool BuildAIDAADCEvent(TGo4MbsSubEvent* psubevt, Int_t word1, Int_t word2);
  bool BuildAIDAInfoEvent(TGo4MbsSubEvent* psubevt, Int_t word1, Int_t word2);

public:
  AIDA_Detector_System();
  ~AIDA_Detector_System();

  ///Nic additions

  void CorrectMultiplexer(ADCDataItem&);
  virtual void PrintStatistics();

  void Process_MBS(TGo4MbsSubEvent* psubevt);

    
  const char* get_filename();
  bool get_newfile();
  void Process_MBS(int*){};
  void get_Event_data(Raw_Event*);
  int* get_pdata();

  void write(){return;};
  bool calibration_done(){return false;}

  void set_Gain_Match_Filename(std::string){return;};
  
    bool do_gain_matching(int ts_ns) {return 1;};
    unsigned long next_ts_for_update() {return 1;}
};



#endif
