#ifndef FINGER_DETECTOR_SYSTEM_H
#define FINGER_DETECTOR_SYSTEM_H

#include <iostream>
#include <string>

#include "Detector_System.cxx"
#include "FINGER_Calibrator.h"
#include "Raw_Event.h"

#include "TAMEX.h"



typedef unsigned long long ULong64_t;
typedef unsigned long ULong;

class FINGER_Detector_System : public Detector_System{


private:

    FINGER_Calibrator* FINGER_Calibration; 

    bool tamex_end;

    bool no_edges[100];

    bool written;

    bool CALIBRATE,Calibration_Done;
    
    int cal_count;

    int* pdata;

    int unknown;
    int increase;
    int add;
    int aa;
    int six_eight,six_f;
    int error_code;
    int tamex_identifier;

    ULong trailer_code;

    int am_fired[100];
    int sfp_id[100];
    int trigger_type[100];
    int* iterator;
    int tamex_id[100];


    int tamex_iter;

    ULong Pre_Trigger_Window;
    ULong Post_Trigger_Window;

    int** leading_hits;
    int** trailing_hits;

    int** lead_arr;

    double** edge_coarse;
    double** edge_fine;
    unsigned int** ch_ID_edge;
    unsigned int** ch_num;
    double* coarse_T;
    double* fine_T;
    unsigned int* ch_ID;

    void check_error();
    void check_trailer();
    void get_edges();
    void get_trigger();
    void skip_padding();
    void Process_TAMEX();
    void calibrate_ONLINE();
    void calibrate_OFFLINE();

    void get_Calib_type();
    void reset_edges();

    bool no_error_reached();
    

public:
    FINGER_Detector_System();
    ~FINGER_Detector_System();

    //void Process_FRS(TModParameter* , TGo4MbsSubEvent* , TGo4MbsEvent*){};
    void Process_MBS(TGo4MbsSubEvent* psubevt){};

    //functions from abstract class Detector_System
    void Process_MBS(int*);

    void get_Event_data(Raw_Event*);
    //void get_Event_data(Data_Stream*){return;};


    int* get_pdata();

    bool calibration_done();

    void write(){return;};
    void set_Gain_Match_Filename(std::string){return;};
    bool do_gain_matching(int ts_ns) {return 1;};
    unsigned long next_ts_for_update() {return 1;}
};



#endif
