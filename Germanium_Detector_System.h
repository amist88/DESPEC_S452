#ifndef Germanium_DETECTOR_SYSTEM_H
#define Germanium_DETECTOR_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>


#include "Germanium_Energy_Calibration.h"
#include "Germanium_Time_Calibration.h"

#include "FEBEX.h"

#include "Detector_System.cxx"

typedef unsigned long long ULong64_t;

class Germanium_Detector_System : public Detector_System{


private:
    int max_am_dets;
    
    int board_id;
    int num_channels;
    
    int* pdata;

    ULong64_t tmp_Sum_Time;
    int tmp_Pileup;
    int tmp_Hit_Pattern;
    
    int* det_ids;
    int* crystal_ids;
    ULong64_t* Sum_Time;
    int* Hit_Pattern;
    ULong64_t* Chan_Time;
    double* Chan_Energy;
    ULong64_t* Chan_CF;
    bool* Overflow;
    bool* Pileup;
    

    std::map<std::pair<int,int>, std::pair<int,int>> Germanium_map;
    
    int num_channels_fired = 0;

    int pileup_flags[16];
    int Ge_channels[16];
    int fired_FEBEX_amount;
    void load_board_channel_file();
    void reset_fired_channels();
    void Calibrate_FEBEX(int);

    Germanium_Time_Calibration* Germanium_T_CALIB;
    Germanium_Energy_Calibration* Germanium_E_CALIB;


public:
    Germanium_Detector_System();
    ~Germanium_Detector_System();
    
    void Process_MBS(TGo4MbsSubEvent* psubevt){};

    void Process_MBS(int*);
    void get_Event_data(Raw_Event*);
    int* get_pdata();


    // Useless but needed for Detector_System
    bool calibration_done(){return false;}
    void write(){return;};
    void set_Gain_Match_Filename(std::string){return;};
    bool do_gain_matching(int ts_ns) {return 1;};
    unsigned long next_ts_for_update() {return 1;};

};



#endif
