#include "Germanium_Energy_Calibration.h"

#include <cstdlib>


using namespace std;

//----------------------------------------------------------

Germanium_Energy_Calibration::Germanium_Energy_Calibration(){
    load_Calibration_File();
}

//----------------------------------------------------------

Germanium_Energy_Calibration::~Germanium_Energy_Calibration(){}

//----------------------------------------------------------

void Germanium_Energy_Calibration::load_Calibration_File(){
    
    const char* format = "%d %lf %lf %lf %lf %lf";


    ifstream calib_file("Configuration_Files/Germanium/Germanium_Energy_Calibration.txt");

    if(calib_file.fail()){
        cerr << "Could not find Germanium Energy Calibration file" << endl;
        exit(0);
    }
    string line;

    double tmp_coeffs[5];

    int det_id;

    while(calib_file.good()){
        getline(calib_file,line,'\n');
        if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&det_id,&tmp_coeffs[0]
                                  ,&tmp_coeffs[1],&tmp_coeffs[2]
                                  ,&tmp_coeffs[3],&tmp_coeffs[4]);

        for(int i = 0;i < 5;++i) calib_coeffs[det_id][i] = tmp_coeffs[i];
    }
}

//----------------------------------------------------------

double Germanium_Energy_Calibration::Calibrate_FEBEX_E(double E,int det_id){
    
    //calibrate using Horner's method (https://en.wikipedia.org/wiki/Horner%27s_method)
    double Energy_c = calib_coeffs[det_id][0];
    for(int i = 1;i < 5;++i) Energy_c = Energy_c*E + calib_coeffs[det_id][i];
    return Energy_c;
}

//----------------------------------------------------------

