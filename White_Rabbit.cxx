#include "White_Rabbit.h"

using namespace std;

//---------------------------------------------------------------

White_Rabbit::White_Rabbit(){

    for(int i = 0;i < 7;++i) ID[i] = -1;
    load_config_file();
    pdata = nullptr;
    increase = 5;
}

//---------------------------------------------------------------

// White_Rabbit::White_Rabbit(bool tmp){
//     //second ctor for linked systems (linking of FATIMA and PLASTIC)
//     load_config_file();
// }

//---------------------------------------------------------------

White_Rabbit::~White_Rabbit(){}

//---------------------------------------------------------------

void White_Rabbit::load_config_file(){

    const char* format = "%s %x";

    ifstream config_file("Configuration_Files/DESPEC_General_Setup/White_Rabbit_Map.txt");
    if(config_file.fail()){
        cerr << "Could not find White_rabbit map!" << endl;
        exit(0);
    }

    //load file (and skip header)
    string line;
    char s[100];
    int id = 0;

    while(config_file.good()){
        getline(config_file,line,'\n');
        if(line[0] == '#') continue;
        sscanf(line.c_str(),format,s,&id);
        for(int i = 0;i < 7;++i){
            if(string(s) == names[i]){
                ID[i] = id;

                break;
            }
        }
    }
}

//---------------------------------------------------------------

// NH: Is this gibberish?
// AM: I'm removing it (useful for FRS subsystems?) 
//void White_Rabbit::set_WR_from_MASTER_DET(ULong64_t WR_Time){this->WR_Time = WR_Time;}

//---------------------------------------------------------------

void White_Rabbit::set_triggered_detector(int WR_d){

    //check for id of detector
    for(int i = 0;i < 7;i++){
      // printf("ID0x%02x, WR0x%02x\n", (unsigned int) ID[i], WR_d);
        if(WR_d == ID[i]){
            detector_id = i;
            
            return;

        }
       //else break;
    }
    ///This skips the second FRS white rabbit header
    if(WR_d==0x200)return;
     printf("0x%02x\n", (unsigned int) WR_d);
    //unknown detector id in white rabbit header
   // cerr << hex << "White Rabbit Header 0x"<<WR_d << " not known!" << endl;
    exit(0);
}

//---------------------------------------------------------------

void White_Rabbit::process_White_Rabbit(int* pdata){
    bool found;
    this->pdata = pdata;
    detector_id = -1;

    //check for White Rabbit header in pdata

    // Update by NH to better handle WR timestamps

    // First word is the WR detector ID
    
    int WR_d = *pdata++;
    
     
    //Four words of WR timestamp: lower 16 bits contain timestamp and upper 16 are ID to validate WR
    WR_Data* wr_l = (WR_Data*)pdata++;
    WR_Data* wr_m = (WR_Data*)pdata++;
    WR_Data* wr_h = (WR_Data*)pdata++;
    WR_Data* wr_x = (WR_Data*)pdata++;

    // Check if the WR timestamp contains the valid IDs, if so it's a WR header
    // (The old method looked for specific invalid WR detector IDs, this way is independent of data)
    found = (wr_l->id == WR_TS_ID_L && wr_m->id == WR_TS_ID_M && wr_h->id == WR_TS_ID_H && wr_x->id == WR_TS_ID_X);

    // If a valid WR timestamp is found
    if (found)
    {
      // match the WR detector ID to the internal detector number
      set_triggered_detector(WR_d);

      // Extract the WR timestamp
      WR_Time = ((ULong64_t) wr_l->timestamp)
            + (((ULong64_t) wr_m->timestamp) << 16)
            + (((ULong64_t) wr_h->timestamp) << 32)
            + (((ULong64_t) wr_x->timestamp) << 48);

      // Advance the data pointer to after the WR header
      this->pdata = pdata;
    }
}

//---------------------------------------------------------------

ULong64_t White_Rabbit::get_White_Rabbit(int* pdata){
    this->pdata = pdata;
    process_White_Rabbit(pdata);
    return WR_Time;
  }

//---------------------------------------------------------------

int White_Rabbit::get_Detector_id(){return detector_id;}

//---------------------------------------------------------------

int* White_Rabbit::get_pdata(){return pdata;}

//---------------------------------------------------------------
