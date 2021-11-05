//Changes, 24.07.18 MR long time ago and again

//b) changed allocation file name from allocation.txt to
//   FATIMA_allocation.txt


#include "FATIMA_Detector_System.h"

#include <cstdlib>

using namespace std;

//---------------------------------------------------------------

FATIMA_Detector_System::FATIMA_Detector_System(){

 
     
    FAT_evt = 0;
    unknown_header_counter = 0;
    //set amount of QDCs and TDCs
    max_am_dets = 60;
    maxScalers = 32;

    fired_QDC_amount = 0;

    QLong = new double[max_am_dets];
    QLong_Raw = new double[max_am_dets];
    QShort_Raw = new double[max_am_dets];

    QDC_Time_Coarse = new ULong64_t[max_am_dets];
    QDC_Time_Fine = new double[max_am_dets];

    TDC_Time_raw = new ULong64_t[max_am_dets];
    TDC_Time_ns  = new double[max_am_dets];

    det_ids_QDC = new int[max_am_dets];
    det_ids_TDC = new int[max_am_dets];
    
    Scaler_Data = new double[maxScalers];
    
    for(int i=0; i<maxScalers; i++){
     Scaler_Data[i] = 0;
    }

    for(int i = 0;i < max_am_dets;++i){
        QLong[i] = 0;
        //QShort[i] = 0;
        QDC_Time_Coarse[i] = 0;
        QDC_Time_Fine[i] = 0;
        TDC_Time_raw[i] = 0;
        TDC_Time_ns[i] = 0;
        det_ids_QDC[i] = 0;
        det_ids_TDC[i] = 0;
    }

    det_ID_QDC = new int*[100];
    det_ID_TDC = new int*[100];
    for(int i = 0;i < 100;++i){
        det_ID_QDC[i] = new int[100];
        det_ID_TDC[i] = new int[100];
        for(int j = 0;j < 100;++j){
            det_ID_QDC[i][j] = -1;
            det_ID_TDC[i][j] = -1;
        }

    }
  //  FAT_positions = new double*[36];
  //  source_position_correction = new double[36];
//     for(int i = 0; i < 36; i++){
//    // FAT_positions[i] = new double[3];
//    // source_position_correction[i] = -1;
// 
//     for (int j = 0; j < 3; j++) FAT_positions[i][j] = -1;
//     
//     }

    FATIMA_T_CALIB = new FATIMA_Time_Calibration();
    FATIMA_E_CALIB = new FATIMA_Energy_Calibration();

    load_board_channel_file();
    //FATIMA_VME_Setup_File("Configuration_Files/FATIMA/FATIMA_VME_Setup_File.txt");
  
    
    //load_pos_correction();
    
}

//---------------------------------------------------------------

FATIMA_Detector_System::~FATIMA_Detector_System(){
    for(int i = 0;i < 100;++i){
        delete[] det_ID_QDC[i];
        delete[] det_ID_TDC[i];
    }

    delete[] det_ID_TDC;
    delete[] det_ID_QDC;

    delete[] det_ids_QDC;
    delete[] det_ids_TDC;

    delete[] QLong_Raw;
    delete[] QShort_Raw;
    delete[] QLong;
    delete[] QDC_Time_Coarse;
    delete[] QDC_Time_Fine;
    delete[] TDC_Time_raw;
    delete[] TDC_Time_ns;
    delete FATIMA_T_CALIB;
    delete FATIMA_E_CALIB;
    
    delete[]Scaler_Data;
}

//---------------------------------------------------------------


void FATIMA_Detector_System::load_board_channel_file(){

    const char* format = "%d %d %d %d %d %d";

    ifstream file("Configuration_Files/FATIMA/FATIMA_VME_allocation.txt");

    if(file.fail()){
        cerr << "Could not find QDC_FATIMA Board_Channel to DetNum File!" << endl;
      //  exit(0);
    }

    string line;
    int detector_number, board_id, channel_num, board_id_TDC, TDC_ch, enabled;

    while(file.good()){
        getline(file,line,'\n');
        if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&detector_number,&board_id,
                    &channel_num,&board_id_TDC,&TDC_ch,&enabled);
        if (enabled == 1) {
            det_ID_QDC[board_id][channel_num] = detector_number;
         
            det_ID_TDC[board_id_TDC][TDC_ch] = detector_number;
        }
    }
}

//---------------------------------------------------------------

// void FATIMA_Detector_System::load_det_angles(){
// 
//     const char* format = "%d %lf %lf %lf";
// 
//     ifstream file("Configuration_Files/FATIMA/FATIMA_Detector_Positions.txt");
// 
//     if(file.fail()){
//         cerr << "Could not find FATIMA Detector Positions File!" << endl;
//       //  exit(0);
//     }
// 
//     string line;
//     int pos_num;
//     double r, theta, phi;
// 
//     while(file.good()){
//         getline(file,line,'\n');
//         if(line[0] == '#') continue;
//         sscanf(line.c_str(),format, &pos_num, &r, &theta, &phi);
//         
//         FAT_positions[pos_num][0] = r;
//         FAT_positions[pos_num][1] = theta;
//         FAT_positions[pos_num][2] = phi;
//     }
// }

//---------------------------------------------------------------

// void FATIMA_Detector_System::load_pos_correction(){
// 
//     const char* format = "%lf %lf %lf";
// 
//     ifstream file("Configuration_Files/FATIMA/FATIMA_Source_Position.txt");
// 
//     if(file.fail()){
//         cerr << "Could not find FATIMA Source Position File!" << endl;
//       //  exit(0);
//     }
// 
//     string line;
//     int pos_num;
//     double r, theta, phi;
//     
// 
//     while(file.good()){
//         getline(file,line,'\n');
//         if(line[0] == '#') continue;
//         sscanf(line.c_str(),format, &r, &theta, &phi);
//     
//     
//     }
//     
//     for(int i = 0; i < 36; ++i){
//     
//     source_position_correction[i] = distance_between_detectors(r, theta, phi, FAT_positions[i][0], FAT_positions[i][1], FAT_positions[i][2]);
// 
//     double average_distance = distance_between_detectors(0.0, 0.0, 0.0, FAT_positions[i][0], FAT_positions[i][1], FAT_positions[i][2]);
// 
//     source_position_correction[i] = (average_distance - source_position_correction[i])/300.0;
//     
//     }
// }
//---------------------------------------------------------------

void FATIMA_Detector_System::get_Event_data(Raw_Event* RAW){

    bool called = false;
    int a = 0;
    for(int i = 0;i < fired_TDC_amount;++i){
        a = det_ids_TDC[i];
        if(a == 50 || a == 51) called = true;
        if(called) break;
      
    }
                    
    RAW->set_DATA_FATIMA(fired_QDC_amount,fired_TDC_amount,
                        QLong_Raw,QShort_Raw,QLong,
                        TDC_Time_raw, TDC_Time_ns, QDC_Time_Coarse,QDC_Time_Fine,
                        det_ids_QDC,det_ids_TDC);
    
    //RAW->set_DATA_SCALER(Scaler_iterator, Scaler_Data);
                        
    //QDC_TDC->get_Detector_Data(RAW);
}

//---------------------------------------------------------------

void FATIMA_Detector_System::Process_MBS(int* pdata){
    //printf("  FATIMA process MBS\n");
    reset_fired_channels();
    this->pdata = pdata;
    /*
    for (int i=0; i<20; i++) {
      printf("0x%08x ", *this->pdata);
      this->pdata++;
      printf("0x%08x ", *this->pdata);
      this->pdata++;
      printf("0x%08x ", *this->pdata);
      this->pdata++;
      printf("0x%08x\n", *this->pdata);
      this->pdata++;
    }
    return;
    */
    //readout sequence is SCALER-QDC-TDC!!
    //readout scalers//////////////////////
    unsigned int sc_geo = 15;
    if(SCALER_MODULE_ON) {
      if(Check_SCALER_DATA(this->pdata, sc_geo) < 1) {
        this->pdata = pdata;
      }
    }
    //printf("Next header: %08x\n", *this->pdata);
    //readout QDC//////////////////////////
    int nqdc = 0;
    //printf("Reading QDC data:\n");
    //while(true) {
    for (int qdcboards=0; qdcboards<5; qdcboards++) {
      QDC_Header* QDChead  = (QDC_Header*) this->pdata;
      //QDC channel empty (check a -> always with QDC, length-> am_channels called (len-4))
      //printf("  checking header 0x%08x\n", *this->pdata);
      if(QDChead->check_a == 10 && QDChead->length == 4) {
        for(int i = 0;i < 4;++i) {
          this->pdata++;
        }
        nqdc++;
        //printf("  empty QDC %2d\n", nqdc);
      } else if(QDChead->check_a == 10){//QDC channel filled 
        //printf("   found header with data 0x%08x\n", this->pdata);
        if(!Check_QDC_DATA()) {
          printf("  WARNING: FATIMA QDC readout error\n");
        }
        nqdc++;
        //printf("  data QDC %2d\n", nqdc);
      /*
      } else if((*this->pdata & 0xF8000000) == 0x40000000
                || *this->pdata == 0x06000000) {
        //Found first TDC.
        //printf("  Found TDC!\n");
        if(nqdc == 0) {
          printf("  WARNING: FATIMA TDC data found before any QDC data. Readout order is SCALER-QDC-TDC\n");
        }
        break;
      */
      } else {
        printf("  WARNING: FATIMA QDC readout encountered unknown header\n");
        break;
      }
    }
    //readout TDC////////////////////////
    //printf("Reading TDC data:\n");
    TDC_Check* TDChead = (TDC_Check*) this->pdata;
    num_TDC_modules = 0;
    for (int i=0; i<FAT_TDC_NUMBER; i++) {
      if(Check_TDC_DATA()) {
        num_TDC_modules++;
        //printf("Found TDC%d\n", num_TDC_modules);
      }else{
        printf("WARNING: FATIMA TDC readout error\n");
      }
    }
    if (num_TDC_modules != FAT_TDC_NUMBER) {
        printf("WARNING: FATIMA TDC readout error. Only found %d of %d TDCs.\n", num_TDC_modules, FAT_TDC_NUMBER);
    } else {
       //printf("ALL FINE reading FATIMA!\n==================\n");
    }
    return;
}

//---------------------------------------------------------------

void FATIMA_Detector_System::reset_fired_channels(){
    fired_QDC_amount = 0;
    fired_TDC_amount = 0;
    for(int i = 0;i < max_am_dets;++i){
        QLong[i] = -1;
        QDC_Time_Coarse[i] = 0;
        QDC_Time_Fine[i] = 0;
        TDC_Time_raw[i] = 0;
        TDC_Time_ns[i] = 0;
    }
    Scaler_iterator = 0;
    memset(Scaler_Data, 0, sizeof(double)*maxScalers);
}


//---------------------------------------------------------------

int FATIMA_Detector_System::Check_QDC_DATA(){
    this->pdata++; // Moves to 2nd header value //
    QDC_Header_2 *QDChead_2 = (QDC_Header_2*) this->pdata;
    int board_ID = QDChead_2->geo; // Gets Geographical Address //
    int num_Channels = QDChead_2->channels; // Gets Channels fired 0011 means 1&2 fired //
    int num_channels_fired = 0;
    if(board_ID!=13){
      // Loop retrieves channels fired from integer value //
      for(int j = 7; j >= 0; j--){
        if(num_Channels >= pow(2, j)){
            //fill Fired_Channel array with corresponding ids
            if(wired_QDC(board_ID,j)){
                Fired_QDC_Channels[num_channels_fired][0] = board_ID; 
                Fired_QDC_Channels[num_channels_fired][1] = j;
                num_channels_fired++;
            }
            else{
                Fired_QDC_Channels[num_channels_fired][0] = board_ID; 
                Fired_QDC_Channels[num_channels_fired][1] = -1;
                num_channels_fired++;
            }
            num_Channels -= pow(2, j);
        }
      }

      this->pdata += 2; // Moves from 2nd to 4th header value //
    
      //int size = 0;
      int active_Channel = 0;
      int active_board = 0;
      int active_det = 0;
      double fine_time = 0;

      for(int i = (num_channels_fired - 1); i >= 0; --i){
    
        this->pdata++; // Moves to 1st data value

        QDC_Format_Size* fs = (QDC_Format_Size*) this->pdata;
    
    
        if (Fired_QDC_Channels[i][1] == -1){ /*this->pdata += 6;*/
	       cout<<"Warning, Fatima channel ID = -1!! "<<endl;
          return 0;
        }else{
            //set active board_ID and channel #
            active_board = Fired_QDC_Channels[i][0];
            active_Channel = Fired_QDC_Channels[i][1];
            active_det = det_ID_QDC[active_board][active_Channel];
            //cout<<"Channel Number = "<<active_det<<endl;
            det_ids_QDC[fired_QDC_amount] = active_det;
            this->pdata += 3; //Moves to QDC time data
            QDC_Time* t = (QDC_Time*) pdata;
            QDC_Time_Coarse[fired_QDC_amount] = t->trigger_tag;
         //  if(dist_corr_used) QDC_Time_Coarse[fired_QDC_amount] += source_position_correction[active_det];
            this->pdata++; // Moves to Extras
            QDC_Extras* e = (QDC_Extras*) this->pdata;    
            ULong64_t tmp_ext_trig = e->ext_trig;
            fine_time = (((t->trigger_tag) + (tmp_ext_trig << 32)));
            //possibly this should be -= have to verify...
            fine_time += ((double)(e->fine_time)/1024.);
           // if(dist_corr_used) fine_time += source_position_correction[active_det];        
            QDC_Time_Fine[fired_QDC_amount] = fine_time;
            this->pdata++; // Moves to 6th data value87454dda
            QDC_Data* d = (QDC_Data*) this->pdata;
            QLong_Raw[fired_QDC_amount] = d->QL; // Gets Q Long data //
            QShort_Raw[fired_QDC_amount] = d->QS; // Gets Q Short data //
            //printf("Det%02d  E (chn) %8.2lf ", det_ids_QDC[fired_QDC_amount],
            //                                  QLong_Raw[fired_QDC_amount]);
//             if (gain_match_used) {
//                 Gain_Match_QDC(fired_QDC_amount);
//             //  printf("E (gm) %8.2lf ", QLong[fired_QDC_amount]);
//             }
            Calibrate_QDC(fired_QDC_amount);
            //printf("E (gm) %8.2lf\n", QLong[fired_QDC_amount]);
            fired_QDC_amount++;
        }
      }
      this->pdata++;
      return 1;
   }//END if ID != 13
   else {
     printf("WARNING: FATIMA QDC readout, unknown ID 13\n");
     this->pdata++;
     return 0;
   }
}


//---------------------------------------------------------------

int FATIMA_Detector_System::Check_TDC_DATA(){
    
    bool trail = false;

    int check = 0;
    int tdc_board_ID = 0;
    int TDC_ch = 0;
    int active_det = 0;
    no_data = true;
    
    // unused // int TDC_loop = 0;
    
    int loop_counter = 0;
    while(!trail){
        loop_counter++;
        //pdata++;
            
        TDC_Check* p = (TDC_Check*) pdata;
        check = p->type;
          
         // Global Header Condition //
        if (*pdata == 0x06000000) {
          //printf("  TDC empty\n");
          pdata++;
          return 1; //empty TDC
        }
        else if( check == 8 ){
            TDC_Glob_Header* gh = (TDC_Glob_Header*) pdata;
            tdc_board_ID = gh->geo;
            pdata++;
            //printf("TDC header found 0x%08d\n", *pdata); 
        }

        // TDC Header Condition //
        else if( check == 1 ) {
          pdata++;
        }
        // TDC Measurement Condition //
        else if( check == 0 ){
            TDC_Measurement* m = (TDC_Measurement*) pdata;
            TDC_ch = m->channel;
            if(!wired_TDC(tdc_board_ID,TDC_ch)){
                no_data = true;
            }
            else{
                active_det = det_ID_TDC[tdc_board_ID][TDC_ch];
                det_ids_TDC[fired_TDC_amount] = active_det;
                TDC_Time_raw[fired_TDC_amount] = (ULong64_t) (m->measurement);
                Calibrate_TDC(fired_TDC_amount);
                Calibrate_TDC(fired_TDC_amount);
                fired_TDC_amount++;
                no_data = false;
            }
            pdata++;
        }
        // TDC Trailer Condition // 
        else if ( check == 16 ) {
          //printf("Trailer found\n");
          pdata++;
          return 1;
        }else{
          printf("WARNING: FATIMA TDC WRONG: header is 0x%08d\n", *pdata);
          pdata++;
        }
        if(loop_counter > 100){
            cerr << "WARNING: FATIMA TDC loop not reaching trailer! pdata iteration problem possible" << endl;
            pdata++;
            return 0;
        }
    }
    printf("ERROR: FATIMA: should never get here!\n");
    return 0; 
}

int FATIMA_Detector_System::Check_SCALER_DATA(int* pheader,  unsigned int geoadd) {
      unsigned int sc_header = *pheader;
      int nwords = 0;
      //printf("Checking the scaler data 0x%08x, 0x%08x, %d:\n", sc_header, geoadd, (sc_header&0xF8000000)>>27);
      if((sc_header & 0xF8000000)>>27 == geoadd){
        //printf("we have a scaler 0x%08x\n", sc_header);
        nwords = (sc_header & 0x1F00) >> 8;
        for (int i=0; i<nwords; i++) {
          this->pdata++;
          //printf("0x%08x\n", *this->pdata);
          Scaler_Data[Scaler_iterator] = *this->pdata;
          Scaler_iterator++; 
        }
        this->pdata++;
        //printf("scalertrailer 0x%08x\n", *this->pdata);
        if(*this->pdata != (int) (geoadd<<27) + 0x400000) {
          //printf("Nice, correct trailer word\n");
        }else{
          printf("WARNING: FATIMA SCALER readout, trailer not found");
        }
        this->pdata++;
        return 1;
      }else if (sc_header == 0x06000000) {
        //Filler word, no scaler data
        this->pdata++;
        return 1; 
      }else{
        printf("WARNING: FATIMA SCALER enabled but not found.\n");
        printf("         Readout sequence is SCALER-QDC-TDC.\n");
        return 0;
      }

}

//---------------------------------------------------------------

//bool FATIMA_Detector_System::check_additional(int active){return (active == 51);}

//---------------------------------------------------------------

bool FATIMA_Detector_System::wired_QDC(int board_id,int ch_num){
    return det_ID_QDC[board_id][ch_num] != -1;
}

//---------------------------------------------------------------

bool FATIMA_Detector_System::wired_TDC(int board_id,int ch_num){
    return det_ID_TDC[board_id][ch_num] != -1;

}

//---------------------------------------------------------------

//det_ids_TDC/det_ids_QDC has to
//be set correctly before calling these cal / gm functions
void FATIMA_Detector_System::Calibrate_QDC(int id){
    
   // if (gain_match_used){
        QLong[id] = FATIMA_E_CALIB->Calibrate(QLong_Raw[id], det_ids_QDC[id]);
      // cout<<" 1QLong[id] " << QLong[id] << " QLong_Raw[id] " <<QLong_Raw[id] << endl;
   // }
  // else{
     //   QLong[id] = QLong_Raw[id];
      //  cout<<" 2QLong[id] " << QLong[id] << " QLong_Raw[id] " <<QLong_Raw[id] << endl;
  // }
    QDC_Time_Coarse[id] = FATIMA_T_CALIB->Calibrate_QDC(QDC_Time_Coarse[id], det_ids_TDC[id]);
    QDC_Time_Fine[id] = FATIMA_T_CALIB->Calibrate_QDC(QDC_Time_Fine[id], det_ids_TDC[id]);

}

//---------------------------------------------------------------
/*
void FATIMA_Detector_System::Gain_Match_QDC(int id){
    QLong[id] = FATIMA_GAIN_MATCH->Gain_Match(QLong_Raw[id],det_ids_QDC[id]);
}*/

//---------------------------------------------------------------
void FATIMA_Detector_System::Calibrate_TDC(int id){
    TDC_Time_ns[id] = FATIMA_T_CALIB->Calibrate_TDC(TDC_Time_raw[id],det_ids_TDC[id]);
}

Int_t FATIMA_Detector_System::getbits(Int_t value, int nword, int start, int length){
    
  UInt_t buf = (UInt_t) value;
  buf = buf >> ((nword-1)*16 + start - 1);
  buf = buf & ((1 << length) - 1);
  return buf;
  
}

//---------------------------------------------------------------

int* FATIMA_Detector_System::get_pdata(){return pdata;}

//---------------------------------------------------------------

// void FATIMA_Detector_System::FATIMA_VME_Setup_File(string config_filename){
//     
//     ifstream file(config_filename);
// 
//     if(file.fail()){
//         cerr << "Could not find File for setup parameters!" << endl;
//        // exit(0);
//     }
// 
//     string line;
//     
//    file.ignore(256,':');
//    file >> gain_match_used;//dummy_var;
// 
//     file.ignore(256,':');
//     file >> num_TDC_modules_fixed;//dummy_var; 
//     
//     file.ignore(256,':');
//     file >> Scaler_Module;//dummy_var; 
// 
// };

//---------------------------------------------------------------

// double FATIMA_Detector_System::distance_between_detectors(double _r, double _theta, double _phi, double r_, double theta_, double phi_){
// 
//     _theta = _theta * M_PI/180.0; 
//     theta_ = theta_ * M_PI/180.0; 
// 
//     _phi = _phi * M_PI/180.0; 
//     phi_ = phi_ * M_PI/180.0; 
// 
//     double dist = sqrt(_r*_r + r_*r_ - 2.0*_r*r_*(sin(_theta)*sin(theta_)*cos(_phi - phi_) + cos(_theta)*cos(theta_)));
//     
//     return dist;
// 
// 
// }
//---------------------------------------------------------------

