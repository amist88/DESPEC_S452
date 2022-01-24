#include "PLASTIC_TWINPEAKS_Detector_System.h"
//Set for twin peaks 25.02.21 AKM
using namespace std;

//---------------------------------------------------------------

PLASTIC_TWINPEAKS_Detector_System::PLASTIC_TWINPEAKS_Detector_System(){

    //calibration enabled?
    get_Calib_type();
    cal_count = 0;

    Calibration_Done = false;
  
    PLASTIC_TAMEX_Calibration = new PLASTIC_TAMEX_Calibrator(CALIBRATE);

    // different codes for PLASTIC_TWINPEAKS MBS words
    add = 2781;
    aa = 170;
    six_eight = 104;
    six_f = 6;
    trailer_code = 187;
    error_code = 238;
    tamex_identifier = 52;

    iterator = new int[200];
    for(int i = 0;i < 200;++i) iterator[i] = 0;

    tamex_iter = 0;
    lead_arr = new int*[200];
    leading_hits = new int*[200];
    trailing_hits = new int*[200];

    coarse_T = new double[200];
    fine_T = new double[200];
    ch_ID = new unsigned int[200];

    edge_coarse = new double*[200];
    edge_fine = new double*[200];
    ch_ID_edge = new unsigned int*[200];
    
//     edge_coarse_slow = new double*[200];
//     edge_fine_slow = new double*[200];
//     ch_ID_edge_slow = new unsigned int*[200];
    
    for(int o = 0;o < 200;++o){
        edge_coarse[o] = new double[200];
        edge_fine[o] = new double[200];
        ch_ID_edge[o] = new unsigned int[200];
        
//         edge_coarse_slow[o] = new double[200];
//         edge_fine_slow[o] = new double[200];
//         ch_ID_edge_slow[o] = new unsigned int[200];
        
        lead_arr[o] = new int[200];
        leading_hits[o] = new int[200];
        trailing_hits[o] = new int[200];
    }
}

//---------------------------------------------------------------

PLASTIC_TWINPEAKS_Detector_System::~PLASTIC_TWINPEAKS_Detector_System(){
    for(int i = 0;i < 200;++i){
        delete[] edge_coarse[i];
        delete[] edge_fine[i];
        delete[] ch_ID_edge[i];
        
//         delete[] edge_coarse_slow[i];
//         delete[] edge_fine_slow[i];
//         delete[] ch_ID_edge_slow[i];
        
        delete[] lead_arr[i];
        delete[] leading_hits[i];
        delete[] trailing_hits[i];
    }
    delete[] edge_coarse;
    delete[] edge_fine;
    delete[] ch_ID_edge;

//     delete[] edge_coarse_slow;
//     delete[] edge_fine_slow;
//     delete[] ch_ID_edge_slow;
    delete[] coarse_T;
    delete[] fine_T;
    delete[] ch_ID;

    delete PLASTIC_TAMEX_Calibration;
}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::get_Event_data(Raw_Event* RAW){
    RAW->set_DATA_PLASTIC_TWINPEAKS(iterator,edge_coarse,edge_fine,ch_ID_edge,coarse_T,fine_T,tamex_iter,lead_arr);


}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::Process_MBS(int* pdata){

   this->pdata = pdata;
   
  // printf(" pdata 0x%08x\n", (unsigned int*) pdata); 

    //reset old iterator array and old TAMEX data
    for(int i = 0;i < tamex_iter;i++) iterator[i] = 0;
    reset_edges();
    tamex_end = false;
    tamex_iter = 0;

    //loop over the complete TAMEX data of the subevent
    while(!tamex_end){
        Process_TAMEX();
        if(!tamex_end) tamex_iter++;
        this->pdata++;
    }
  //  cout<<"tamex_iter " <<tamex_iter << endl;

    //true -> do "online" calibration and exit program
    if(CALIBRATE) calibrate_ONLINE();
    //false -> do normal "offline" calibration
    else calibrate_OFFLINE();
}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::Process_TAMEX(){

    //reset iterator[tamex_iter]
    iterator[tamex_iter] = 0;
    no_edges[tamex_iter] = false;

    written = false;

    //check for trigger window (beginning of TAMEX MBS)
    if(tamex_iter == 0){
        TRIGGER_WINDOW* window = (TRIGGER_WINDOW*) pdata;
        Pre_Trigger_Window = window->PRE_TRIGG;
        Post_Trigger_Window = window->POST_TRIGG;
         
        //move to next word
        pdata++;
        //skip padding in stream
        skip_padding();
      //  printf(" head 0x%08x\n", (unsigned int*) pdata); 
    }
    //get tamex_id, sfp_id and trigger type
    TAMEX_CHANNEL_HEADER* head = (TAMEX_CHANNEL_HEADER*) pdata;
    
    //check if end of TAMEX MBS reached
    bool ongoing = (head->identify == tamex_identifier) && (head->identify_2 == 0) && (head->sfp_id == 1 || head->sfp_id == 0);

    if(!ongoing){
        tamex_end = true;
        return;
    }
    if(tamex_iter > 0){
        if(head->Tamex_id <= tamex_id[tamex_iter-1]){
            tamex_end = true;
            return;
        }
    }

    sfp_id[tamex_iter] = head->sfp_id;
    trigger_type[tamex_iter] = head->trigger_t;
    tamex_id[tamex_iter] = head->Tamex_id;
      //next word
    pdata++;
    //get amount of fired tdcs (without last trailing words)
    TAMEX_FIRED* fire = (TAMEX_FIRED*) pdata;
    am_fired[tamex_iter] = (fire->am_fired)/4 - 2;

    if(am_fired[tamex_iter] < 0){
        cerr << "NEGATIVE TAMEX FIRED AMOUNT ENCOUNTERED IN bPLAST " << endl;
       // exit(0);
    }


    //next word
    pdata++;
    
    //begin of data header
    TAMEX_BEGIN* begin = (TAMEX_BEGIN*) pdata;
    if(begin->aa != aa){
        cerr << "error in TAMEX format! 0xaa...... word not found after fired amount!" << endl;
        cerr << "TAMEX WORD: " << hex << *pdata << endl;
     //   exit(0);
    }

    //next word
    pdata++;
    //get trigger
    get_trigger();
    //move on to leading and trailing edges
    if(am_fired[tamex_iter] > 3) get_edges();
    else no_edges[tamex_iter] = true;

    //check errors
    //if(!no_edges[tamex_iter]) pdata++;
   // check_error();
    //checking trailer
    check_trailer();
}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::skip_padding(){
    //skip padding by checking words for add
    bool still_padding = true;
    while(still_padding){
        PADDING* padding = (PADDING*) pdata;
        if(padding->add == add) pdata++;
        else still_padding = false;
    }
}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::get_trigger(){
    //check place holder in stream
    PLACE_HOLDER* hold = (PLACE_HOLDER*) pdata;

//     if(hold->six_eight != six_f){
//         cerr << dec << hold->six_eight << endl;
//         cerr << "PLACE_HOLDER error (trigger) in TAMEX!" << endl;
//         exit(0);
//     }

    //next word
    pdata++;

    //extract data
    TAMEX_DATA* data = (TAMEX_DATA*) pdata;
    coarse_T[tamex_iter] = (double) data->coarse_T;
    fine_T[tamex_iter] = (double) data->fine_T;
    ch_ID[tamex_iter] = data->ch_ID;
//cout<<"TRIGGER fine_T[tamex_iter] " << fine_T[tamex_iter]<< " tamex_iter " << tamex_iter << " ch_ID[tamex_iter]  "" coarse_T[tamex_iter] " <<coarse_T[tamex_iter] <<ch_ID[tamex_iter]  <<endl;
 
    //next word
    pdata++;
}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::reset_edges(){
    for(int i = 0;i < 9;++i){
        for(int j = 0;j < 200;++j){
            leading_hits[i][j] = 0;
            trailing_hits[i][j] = 0;
            edge_coarse[i][j] = 131313;
            edge_fine[i][j] = 131313;
            ch_ID_edge[i][j] = 131313;
//             edge_coarse_slow[i][j] = 131313;
//             edge_fine_slow[i][j] = 131313;
//             ch_ID_edge_slow[i][j] = 131313;
        }
    }
}


//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::get_edges(){
    //set iterator[tamex_iter] of edges to 0
    iterator[tamex_iter] = 0;

    //loop over remaining words (getting leading and trailing edge data)
    written = false;

    while(no_error_reached()){
        
        //check place holder in stream
        PLACE_HOLDER* hold = (PLACE_HOLDER*) pdata;
// // 
        if(hold->six_eight == six_f ){
           // cerr << "***Only single channel fired!***" << endl;
            pdata++;
            continue;
        }
//       //  pdata++;
     if(hold->six_eight != six_f) written = false;

//         if(hold->six_eight != six_f){
//             cerr << dec << hold->six_eight << endl;
//             cerr << "PLACE_HOLDER error (edges) in TAMEX!" << endl;
//             //exit(0);
//            // return(0);
//             break;
//         }

        //next word
      

        //extract data
        TAMEX_DATA* data = (TAMEX_DATA*) pdata;
      //  printf(" pdata 0x%08x\n", (unsigned int*) pdata); 
//         cout<<"LEADING PDATA " << ((*pdata & 0x800) >> 11) << endl;
       
       // cout<<"data->leading_E " <<data->leading_E << "  data->coarse_T "<<(double) data->coarse_T<<" data->ch_ID "<<data->ch_ID << endl;
       
//         cout<<"FAST EDGE " << data->leading_E << endl;
//         leading_edge
            if(data->leading_E ==1){
            leading_hit=data->leading_E;
            edge_coarse[tamex_iter][iterator[tamex_iter]] = (double) data->coarse_T;
            edge_fine[tamex_iter][iterator[tamex_iter]] = (double) data->fine_T;
            ch_ID_edge[tamex_iter][iterator[tamex_iter]] = data->ch_ID;
            lead_arr[tamex_iter][iterator[tamex_iter]] = (data->ch_ID % 2);
     
     //    cout << "LEAD EDGE " <<" leading_hit "<<leading_hit<< edge_coarse[tamex_iter][iterator[tamex_iter]] << " fine " << edge_fine[tamex_iter][iterator[tamex_iter]]<< " Chan " << ch_ID_edge[tamex_iter][iterator[tamex_iter]] <<" tamex_iter " <<tamex_iter << " iterator[tamex_iter] " <<iterator[tamex_iter] <<  endl; 
        }
        
//   if(data->leading_E ==1)  ch_ID_edge_lead[tamex_iter][iterator[tamex_iter]]=data->ch_ID;
//   if(data->leading_E ==0)ch_ID_edge_trail[tamex_iter][iterator[tamex_iter]]=data->ch_ID;
  // cout<<"ch_ID_edge_trail[tamex_iter][iterator[tamex_iter]] " <<ch_ID_edge_trail[tamex_iter][iterator[tamex_iter]] << " ch_ID_edge_lead[tamex_iter][iterator[tamex_iter]] " <<ch_ID_edge_lead[tamex_iter][iterator[tamex_iter]] << endl;
      //   if(data->leading_E ==0 && ch_ID_edge_lead[tamex_iter][iterator[tamex_iter]]==ch_ID_edge_trail[tamex_iter][iterator[tamex_iter]]){
  if(data->leading_E ==0 ){
             
             leading_hit=data->leading_E;
              //cout<<"TRAIL EDGE " << data->leading_E << endl;
        edge_coarse[tamex_iter][iterator[tamex_iter]] = (double) data->coarse_T;
        edge_fine[tamex_iter][iterator[tamex_iter]] = (double) data->fine_T;
        ch_ID_edge[tamex_iter][iterator[tamex_iter]] = data->ch_ID+MAX_CHA_INPUT;
        
            //  cout << "TRAIL EDGE " <<" leading_hit "<<leading_hit<< edge_coarse[tamex_iter][iterator[tamex_iter]] << " fine " << edge_fine[tamex_iter][iterator[tamex_iter]]<< " Chan " << ch_ID_edge[tamex_iter][iterator[tamex_iter]] <<" tamex_iter " <<tamex_iter << " iterator[tamex_iter] " <<iterator[tamex_iter] <<  endl; 
        }
//        cout << "coarse " << edge_coarse[tamex_iter][iterator[tamex_iter]] << " fine " << edge_fine[tamex_iter][iterator[tamex_iter]]<< " Chan " << ch_ID_edge[tamex_iter][iterator[tamex_iter]] <<"  lead_arr[tamex_iter][iterator[tamex_iter]] " << lead_arr[tamex_iter][iterator[tamex_iter]] <<  endl;  
         
        iterator[tamex_iter]++;

        written = true;

        //next word
        pdata++; 
        //pdata++; 
       
    }
}

//---------------------------------------------------------------

bool PLASTIC_TWINPEAKS_Detector_System::no_error_reached(){
    TAMEX_ERROR* error = (TAMEX_ERROR*) pdata;
    return error->error != error_code;
}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::check_error(){
    //next word
    //pdata++;

    TAMEX_ERROR* error = (TAMEX_ERROR*) pdata;

    if(error->error != error_code){
        cerr << "wrong error header in bplast TAMEX @ word " << hex << *pdata << endl;
        exit(0);
    }
    if(error->err_code != 0){
        cerr << "Error (not known) in bplast TAMEX occured -> TAMEX WORD: " << hex << *pdata << endl;
        exit(0);
    }
}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::check_trailer(){
    //next word
    pdata++;

    TAMEX_TRAILER* trailer = (TAMEX_TRAILER*) pdata;

    if(trailer->trailer != trailer_code){
     //   cerr << "Unknown TAMEX trailer format!" << endl;
     //   exit(0);
    }
    //else Trailer_Reached = true;

}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::calibrate_ONLINE(){

    //send data to ROOT histograms in Calibrator object
    PLASTIC_TAMEX_Calibration->get_data(edge_fine,ch_ID_edge,tamex_iter,iterator);
   // cout<<"3 " << endl;
    double max_count = 1000000.;
    cal_count++;
    if(cal_count % 1000 == 0){
        cout << dec << "=========================\n";
        cout << cal_count << " " << cal_count/max_count*100. << "%" << endl;
        cout << dec << "=========================" << endl;
    }
    Calibration_Done = false;

    //if critical amount of calibration data reached
    //=> do ONLINE calibration and quit program
    if(cal_count > max_count){
        PLASTIC_TAMEX_Calibration->ONLINE_CALIBRATION();
        Calibration_Done = true;

    }
}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::calibrate_OFFLINE(){
;
    int channel_ID_tmp = 0;
    for(int i = 0;i < 9;++i){
        for(int j = 0;j < iterator[i];++j){
            channel_ID_tmp = (int) ch_ID_edge[i][j];
            if(edge_coarse[i][j] != 131313) edge_fine[i][j] = PLASTIC_TAMEX_Calibration->get_Calibration_val(edge_fine[i][j],i,channel_ID_tmp);
            else edge_fine[i][j] = 131313;
            
            
 
        }
    }
}

//---------------------------------------------------------------

int* PLASTIC_TWINPEAKS_Detector_System::get_pdata(){return pdata;}

//---------------------------------------------------------------

bool PLASTIC_TWINPEAKS_Detector_System::calibration_done(){return Calibration_Done;}

//---------------------------------------------------------------

void PLASTIC_TWINPEAKS_Detector_System::get_Calib_type(){
    ifstream data("Configuration_Files/bPlast/PLASTIC_TAMEX_CALIB_FILE.txt");
    if(data.fail()){
        cerr << "Could not find Calibration type file for PLASTIC_TWINPEAKS" << endl;
        exit(0);
    }
    string line;
    const char* format = "%s %d";
    char s[100];
    int val;
    CALIBRATE = false;
    bool FORCE = false;

    while(data.good()){
        getline(data,line,'\n');
        if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&s,&val);
        if(string(s) == string("ONLINE")) CALIBRATE = (val == 1);
        if(string(s) == string("FORCE")) FORCE = (val == 1);
    }
    data.close();

    //only FORCE possible, if ONLINE active
    FORCE = (CALIBRATE) ? FORCE : false;

    //if FORCE == false -> rewrite config file to OFFLINE mode
    if(!FORCE){
        ofstream out("Configuration_Files/bPlast/PLASTIC_TAMEX_CALIB_FILE.txt");
        out << "#PLASTIC_TWINPEAKS calibration type file" << endl;
        out << "#The file will be changed to OFFLINE after its been read" << endl;
        out << "#-> to force multiple ONLINE calibrations, set FORCE to 1" << endl;
        out << "#ONLINE Calibration and FORCE (1 = yes, 0 = no)" << endl;
        out << "ONLINE\t\t0" << endl;
        out << "FORCE\t\t0" << endl;
        out.close();
    }
    else{
        cout << endl;
        cout << "######################################################################" << endl;
        cout << "!!! ONLINE ANALYSIS IN FORCED MODE" << endl;
        cout << "!!! TO DISABLE, CHECK PLASTIC_TAMEX_CALIB_FILE IN Configuration_Files" << endl;
        cout << "######################################################################" << endl;
        cout << endl;
    }

}

//---------------------------------------------------------------
