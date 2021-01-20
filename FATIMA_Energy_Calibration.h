#ifndef FATIMA_ENERGY_CALIB_H
#define FATIMA_ENERGY_CALIB_H

#include <string>
#include <fstream>
#include <iostream>

class FATIMA_Energy_Calibration{

private:

    double calib_coeffs[100][5];

    std::string filename;

    void load_Calibration_File();


public:
    FATIMA_Energy_Calibration();
    ~FATIMA_Energy_Calibration();
    
    double Calibrate(double,int);
};



#endif
