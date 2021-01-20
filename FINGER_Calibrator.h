#ifndef FINGER_CALIBRATOR_H
#define FINGER_CALIBRATOR_H

typedef unsigned long ULong;
typedef unsigned int UInt;

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>


#include <TFile.h>
#include <TH1.h>

class FINGER_Calibrator{

private:

    bool ONLINE;

	int am_fired,iter;
    int nbins;

    double min_val,max_val;

    bool** fired;
    bool** wired_tamex_ch;
    
    double* bins_x_arr;
    double*** Cal_arr;

    TH1D*** Fine_Hist;

	void load_Calibration_Files();



public:
	FINGER_Calibrator(bool);
	~FINGER_Calibrator();

    void get_data(double**,UInt**,int,int*, UInt**);

    void ONLINE_CALIBRATION();
    double get_Calibration_val(double,int,int);

};

#endif
