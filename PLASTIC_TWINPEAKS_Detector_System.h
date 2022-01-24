#ifndef PLASTIC_TWINPEAKS_DETECTOR_SYSTEM_H
#define PLASTIC_TWINPEAKS_DETECTOR_SYSTEM_H

#include <iostream>
#include <string>

#include "Detector_System.cxx"
#include "PLASTIC_TAMEX_Calibrator.h"
#include "Raw_Event.h"

#include "TAMEX.h"
#define MAX_CHA_INPUT 33                // A) maximum physical input channels per module. must be modulo 4


typedef unsigned long long ULong64_t;
typedef unsigned long ULong;

class PLASTIC_TWINPEAKS_Detector_System : public Detector_System{


private:

    PLASTIC_TAMEX_Calibrator* PLASTIC_TAMEX_Calibration; 

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

    Bool_t leading_hit;
    double** edge_coarse;
    double** edge_fine;
    unsigned int** ch_ID_edge;
    
    unsigned int ch_ID_edge_lead[100][100];
    unsigned int ch_ID_edge_trail[100][100];
    
//     double** edge_coarse_slow;
//     double** edge_fine_slow;
//     unsigned int** ch_ID_edge_slow;

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
    PLASTIC_TWINPEAKS_Detector_System();
    ~PLASTIC_TWINPEAKS_Detector_System();

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
    
    unsigned int epoch_data;
    
    bool do_gain_matching(int ts_ns) {return 1;};
    unsigned long next_ts_for_update() {return 1;}

};



#endif
