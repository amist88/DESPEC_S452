#include "FATIMA_Energy_Calibration.h"

#include <cstdlib>


using namespace std;

//----------------------------------------------------------

FATIMA_Energy_Calibration::FATIMA_Energy_Calibration(){
    load_Calibration_File();
}

//----------------------------------------------------------

FATIMA_Energy_Calibration::~FATIMA_Energy_Calibration(){}

//----------------------------------------------------------

void FATIMA_Energy_Calibration::load_Calibration_File(){
    
    const char* format = "%d %lf %lf %lf %lf %lf";


    ifstream calib_file("Configuration_Files/FATIMA/FATIMA_Energy_Calibration.txt");

    if(calib_file.fail()){
        cerr << "Could not find Fatima Energy Calibration file" << endl;
        exit(0);
    }
    string line;

    double tmp_coeffs[5] = {0,0,0,0,0};

    int det_id = 0;

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

double FATIMA_Energy_Calibration::Calibrate(double E,int det_id){
    //calibrate using Horner's method (https://en.wikipedia.org/wiki/Horner%27s_method)
    double Energy_c = calib_coeffs[det_id][0];
    for(int i = 1;i < 5;++i) Energy_c = Energy_c*E + calib_coeffs[det_id][i];
    
    Energy_c += (static_cast<double>(rand())/static_cast<double>(RAND_MAX+0.5));
    return Energy_c;
}

//----------------------------------------------------------
