#ifndef FATIMA_ENERGY_CALIB_H
#define FATIMA_ENERGY_CALIB_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple> //added for gain matching list
typedef std::tuple<int, int, std::string> gmentry;
class FATIMA_Energy_Calibration{

private:

    double calib_coeffs[100][5];
    double original_calib_coeffs[100][5];

   // std::string filename;

    void load_Calibration_File();

    //gain matching stuff:
    double gm_coeffs[100][2];
    bool do_gm;
    bool have_gm_list;
    int current_gmlist_pos;
    std::vector<gmentry> gm_list;
    void load_GainMatching_List();
    void load_GainMatching_File(gmentry gm);
public:
    FATIMA_Energy_Calibration();
    ~FATIMA_Energy_Calibration();
    
    double Calibrate(double,int);
     //gain matching stuff:
    void   ResetGainMatching();
    unsigned long   next_ts_for_update;
    long   last_ts_in_list;
    void   UpdateGainMatching(int ts_minutes);
};



#endif
