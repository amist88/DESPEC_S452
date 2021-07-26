#ifndef FATIMA_TIME_CALIB_H
#define FATIMA_TIME_CALIB_H

#include <string>
#include <fstream>
#include <iostream>

class FATIMA_Time_Calibration{

private:

    double calib_coeffs[100];
    double calib_coeffs_QDC[100];

    void load_Calibration_File();


public:
    FATIMA_Time_Calibration();
    ~FATIMA_Time_Calibration();
    
    double Calibrate_TDC(unsigned long,int);
    double Calibrate_QDC(double,int);
};



#endif
