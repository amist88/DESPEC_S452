
#ifndef Germanium_ENERGY_CALIB_H
#define Germanium_ENERGY_CALIB_H

#include <string>
#include <fstream>
#include <iostream>

class Germanium_Energy_Calibration{

private:

    double calib_coeffs[100][36];

    std::string filename;

    void load_Calibration_File();


public:
    Germanium_Energy_Calibration();
    ~Germanium_Energy_Calibration();
    
    double Calibrate_FEBEX_E(double,int);
};



#endif
