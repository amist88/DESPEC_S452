#ifndef FATIMA_DETECTOR_SYSTEM_H
#define FATIMA_DETECTOR_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
#include "TGo4Analysis.h"
#include <TFile.h>
#include <TH1.h>
#include "FATIMA_Energy_Calibration.h"
#include "FATIMA_Time_Calibration.h"

#include "QDC_751.h"
#include "TDC_1290.h"
#include "Detector_System.cxx"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

typedef unsigned long long ULong64_t;

class FATIMA_Detector_System : public Detector_System{

    
    
private:

   
	int max_am_dets;
	int FAT_evt;
	
	int unknown_header_counter;

	int* pdata;
    
    int Scaler_iterator;
    double* Scaler_Data;
    int maxScalers;
	
    //These are indexed by fired_QDC_amount
    int fired_QDC_amount;
    int* det_ids_QDC;
    double* QLong;
    double* QLong_Raw;
    double* QShort_Raw;
    ULong64_t* QDC_Time_Coarse;
    double* QDC_Time_Fine;
    
    //These are indexed by fired_TDC_amount
    int fired_TDC_amount;
    int* det_ids_TDC;
    ULong64_t* TDC_Time_raw;        //This is the raw TDC time
    double* TDC_Time_ns;        //This is the raw TDC time


    //These are used for mapping mod,chn to detector
    int** det_ID_QDC;
    int** det_ID_TDC;
    double** FAT_positions;
    
    double* source_position_correction;

    bool exiter;
    bool no_data;
    bool QDC_DATA;
    
	//These are indexed by fired_QDC_amount
    //for vectors 
// 	int fired_QDC_amount;
// 	std::vector<int> det_ids_QDC;
// 	std::vector<double> QLong;
// 	std::vector<double> QLong_Raw;
// 	std::vector<double> QShort_Raw;
// 	std::vector<ULong64_t> QDC_Time_Coarse;
// 	std::vector<double> QDC_Time_Fine;
// 	
// 	//These are indexed by fired_TDC_amount
// 	int fired_TDC_amount;
// 	std::vector<int> det_ids_TDC;
// 	std::vector<ULong64_t> TDC_Time_raw;		//This is the raw TDC time
// 	std::vector<double> TDC_Time_ns;		//This is the raw TDC time
// 
// 
// 	//These are used for mapping mod,chn to detector
// 	std::vector<std::vector<int> > det_ID_QDC;
// 	std::vector<std::vector<int> > det_ID_TDC;
// 	std::vector<std::vector<double> > FAT_positions;
// 	
// 	std::vector<double> source_position_correction;
// 
// 	bool exiter;
// 	bool no_data;
// 	bool QDC_DATA;
// 	std::string gain_match_filename;
	
	//bool dist_corr_used;
    bool gain_match_used;
	int num_TDC_modules = 0;  //Set in the constructor
	int num_TDC_modules_fixed = 0;  //Set in the constructor
	bool Scaler_Module;
    bool Scaler_module;
	    //This is used during individual module unpacking
	int Fired_QDC_Channels[100][2];
    
	void load_board_channel_file();
	//void load_det_angles();
	//void load_pos_correction();

	void reset_fired_channels();
	int  Check_QDC_DATA();                     //returns 1 if ok
	int  Check_TDC_DATA();                     //returns number of TDCs found
   int  Check_SCALER_DATA(int* pheader, unsigned int sc_geoadd);     //returns 1 if ok
	void Calibrate_QDC(int);
	void Calibrate_TDC(int);
	
	//void FATIMA_VME_Setup_File(std::string);
	
	
	//double distance_between_detectors(double, double, double, double, double, double);


	//This could be used to activate deactivate individual
	//detectors
	bool wired_QDC(int,int);
	bool wired_TDC(int,int);

	//??
   // bool check_additional(int);

    FATIMA_Time_Calibration* FATIMA_T_CALIB;
    FATIMA_Energy_Calibration* FATIMA_E_CALIB;

    //tmp root things
 //   TH1D** Det_Hist;

public:
	FATIMA_Detector_System();
	~FATIMA_Detector_System();
	
	void Process_MBS(TGo4MbsSubEvent* psubevt){};
	
	void Process_MBS(int*);
	void get_Event_data(Raw_Event*);
	int* get_pdata();
    
    unsigned long** tmp_get_coarse_T(){return NULL;};
    int tmp_get_am_hits(){return 0;};

    unsigned int** tmp_get_chID(){return NULL;};

    int* tmp_get_iterator(){return NULL;};

    bool calibration_done(){return false;};
    
    Int_t getbits(Int_t, int, int, int);
    //bool do_gain_matching(){return gain_match_used;};
		bool do_gain_matching(int ts_ns) {FATIMA_E_CALIB->UpdateGainMatching(ts_ns); return 1;};
    unsigned long next_ts_for_update() {return FATIMA_E_CALIB->next_ts_for_update;};

    //bool do_gain_matching(){return gain_match_used;};

   // void write();
    //void set_Gain_Match_Filename(std::string);

};



#endif
