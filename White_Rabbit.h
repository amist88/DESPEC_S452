#ifndef WHITE_RABBIT_H
#define WHITE_RABBIT_H

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

#include "WR_Structure.h"


//define ULong64_t (used e.g. in Root or Go4)
typedef unsigned long long ULong64_t;

class White_Rabbit{

private:

    const std::string names[7] = {"FRS","AIDA","PLASTIC","FATIMA","FATIMA_TAMEX","GERMANIUM","FINGER"};
    int increase;
    int DETECTORS[7];
    int ID[7];

    int* pdata;

    int detector_id;
    ULong64_t WR_Time;

    void load_config_file();
    int get_Detector_type();

    void set_triggered_detector(int);
    void process_White_Rabbit(int*);



public:
    White_Rabbit();
    White_Rabbit(bool);
    ~White_Rabbit();

    void set_WR_from_MASTER_DET(ULong64_t);

    ULong64_t get_White_Rabbit(int*);
    int get_Detector_id();

    int* get_pdata();

    
};


#endif
