#include "FRS_Detector_System.h"

#include "Riostream.h"
#include "TROOT.h"
#include "TH1.h"
#include "TMap.h"
#include "TObject.h"
#include "TString.h"
#include "TObjString.h"

#include <cstdlib>
#include <bitset>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>

// Go4 Includes //
#include "TGo4UserException.h"
#include "TGo4Picture.h"
#include "TGo4MbsEvent.h"
#include "TGo4StepFactory.h"
#include "TGo4Analysis.h"
#include "TGo4AnalysisObjectManager.h"
#include "TGo4WinCond.h"
#include "TGo4PolyCond.h"
#include "TGo4CondArray.h"
#include "TGo4EventProcessor.h"
#include "TGo4Parameter.h"

#include "TFRSParameter.h"

#include "DESPECAnalysis.h"
#include "TH2.h"
#include "TCutG.h"

#include "Gtypes.h"

#include <sys/stat.h>
#include <sys/types.h>
//#include "TFRSVftxSetting.h"


using namespace std;

//---------------------------------------------------------------


FRS_Detector_System::FRS_Detector_System(){


     DESPECAnalysis* an = dynamic_cast<DESPECAnalysis*> (TGo4Analysis::Instance());

  if (an==0) {
    cout << "!!!  Script should be run in FRS analysis" << endl;
    return;
  }

   frs = dynamic_cast<TFRSParameter*> (an->GetParameter("FRSPar"));
  if (frs==0) {
    cout << "!!!  Parameter FRSPar not found" << endl;
    return;
  }

 //  ModSetup = dynamic_cast<TModParameter*>(an->GetParameter("ModPar"));

   mw = dynamic_cast<TMWParameter*> (an->GetParameter("MWPar"));
  if (mw==0) {
    cout << "!!!  Parameter MWPar not found" << endl;
    return;
  }

   music = dynamic_cast<TMUSICParameter*> (an->GetParameter("MUSICPar"));
  if (music==0) {
    cout << "!!!  Parameter MUSICPar not found" << endl;
    return;
  }

  sci = dynamic_cast<TSCIParameter*> (an->GetParameter("SCIPar"));
  if (sci==0) {
    cout << "!!!  Parameter SCIPar not found" << endl;
    return;
  }

   id = dynamic_cast<TIDParameter*> (an->GetParameter("IDPar"));
  if (id==0) {
    cout << "!!!  Parameter IDPar not found" << endl;
    return;
  }

   tpc = dynamic_cast<TTPCParameter*> (an->GetParameter("TPCPar"));
  if (tpc==0) {
    cout << "!!!  Parameter TPCPar not found" << endl;
    return;
  }

   si = dynamic_cast<TSIParameter*> (an->GetParameter("SIPar"));
  if (si==0) {
    cout << "!!!  Parameter SIPar not found" << endl;
    return;
  }

   mrtof = dynamic_cast<TMRTOFMSParameter*> (an->GetParameter("MRTOFMSPar"));
  if (mrtof==0) {
    cout << "!!!  Parameter MR-TOF-MSPar not found" << endl;
    return;
  }

  //TModParameter* ElecMod = dynamic_cast<TModParameter*>(an->GetParameter("ModPar"));
  if(frs == nullptr)
    {
     std::cout<<"E> FRS parameters not set properly, it is nullptr !"<<std::endl;
     std::exit(-1);
    }
    #if CALIBRATION_VFTX
  for(int mod=0; mod<VFTX_N; mod++)
    for(int ch=0; ch<VFTX_MAX_CHN; ch++)
      Vftx_Stat[mod][ch]=0;
#endif

    Text_t hist[256];

    for (int module=0; module<VFTX_N; module++) {
    for(int channel=0; channel<VFTX_MAX_CHN; channel++){
    sprintf(hist,"FRS/VFTX_Unpack/VFTX_%i/FineTime/VFTX%i_FineTime_ch%02d",module,module,channel);
    h1_vftx_ft[module][channel] = new TH1D(hist,hist,1000,0,1000);


        }
    }

      // VFTX parameters
  m_VFTX_Bin2Ps();
//     ///for VFTX calibration
//    min_val=0;
//    max_val=1000;
//    nbins =1000;
//     #if LOAD_CALIBRATION_VFTX
// //
//     load_VFTX_Calibration_Files();
//      #endif
  //  vme2s = new Int_t*[32];           // User TDC (V1290)
    //vme2s_trailing = new Int_t*[32];  // User TDC (V1290)

     //leading_v1290_main     =   new UInt_t*[32];             // Mtof TDC (V1290)
     //trailing_v1290_main   = new UInt_t*[32];   // Mtof TDC (V1290)

    //nhit5 = new Int_t*[32];            // multiplicity (V1290)

    //#if NEW_CALIBRATION_VFTX
  for(int mod=0; mod<VFTX_N; mod++)
    for(int ch=0; ch<VFTX_MAX_CHN; ch++)
      Vftx_Stat[mod][ch]=0;
 // #endif

    for(int i = 0; i < 32; ++i){

//     vme2s[i]        = new Int_t[10];           // User TDC (V1290)
//     vme2s_trailing[i]   = new Int_t[10];  // User TDC (V1290)

//   leading_v1290_main[i]         = new UInt_t[10];           // Mtof TDC (V1290)
  // trailing_v1290_main[i]    = new UInt_t[10];  // Mtof TDC (V1290)

  //  nhit5[i]        = new Int_t[2];       // multiplicity (V1290)
//    nhit_v1290_main[i]    = new Int_t[2];       // multiplicity (V1290)

    }


    vme2scaler = new Int_t[32];         // User Crate Messhute
    vme3scaler = new Int_t[32];         // User Crate Messhute

    //firstTS = new bool[3];

    //previousTimeStamp = new Long64_t[3];

    //currentTimeStamp = 0;

    //EventFlag = 0;

    qlength     = 0;         /* From event header     */
    qtype   = 0;           /*                       */
    qsubtype    = 0;        /*                       */
    qdummy  = 0;          /*                       */
    qtrigger    = 0;        /*                       */
    qevent_nr   = 0;       /*                       */

    for(int i=0; i<16; i++){
     vme_trmu_tdc[i] = 0;
     vme_trmu_adc[i] = 0;
    }

 //   Proc_iterator=0;

    /*******************************************************************/
    /***SORT STUFF***/

    StartOfSpilTime     = 0;
    StartOfSpilTime2    = 0; //does not reset at end of extraction
    PreviousTS      = 0;

    counter = 0;

    // time stamp data
    ts_id = 0;
   // ts_word = new ULong64_t[4]; //for the titris time stammping
    //tsys_word = new Int_t[3]; //for the system time
    timestamp = 0;  // absolute time stamp value
    timespill = 0;  // relative time from start of the spill
    timespill2 = 0;  // relative time from start of the spill does not reset at end extraction
    systemtime_ms = 0;
    systemtime_s = 0;

    pattern = 0;
    trigger = 0;

    // scaler readings
    //sc_long = new UInt_t[64]; //changed from 32 to 64 (10.07.2018)
   // sc_long2 = new UInt_t[32];


    // SEETRAM calib IC energy
    //      Int_t         ic_de;           /*                          */


    // part of MW parameter
//     mw_an = new Int_t[13];       /*  anode time              */
//     mw_xl = new Int_t[13];       /*  Rohdaten                */
//     mw_xr = new Int_t[13];       /*                          */
//     mw_yu = new Int_t[13];       /*                          */
//     mw_yd = new Int_t[13];       /*                          */

    // TPC part //(HAPOL-25/03/06) 6 TPCs each one with 2 delay lines each!!
    //7 TPCs (4 at S2, 2 at S4 and one at S3) 03.07.2018 SB

//     tpc_l = new Int_t*[7];
//     tpc_r = new Int_t*[7];
        tpc_lt= new Int_t**[7];
        tpc_rt= new Int_t**[7];
        tpc_dt= new Int_t**[7];
        tpc_l= new Int_t*[7];
        tpc_r= new Int_t*[7];
        tpc_a= new Int_t*[7];
        
   for(int i=0; i < 7; ++i){
       tpc_lt[i] = new Int_t*[2];
       tpc_rt[i] = new Int_t*[2];
       tpc_dt[i] = new Int_t*[4];
       tpc_l[i] = new Int_t[2];
       tpc_r[i] = new Int_t[2];
       tpc_a[i] = new Int_t[4];
       for(int j=0; j < 2; ++j){
           tpc_lt[i][j] = new Int_t[64];
           tpc_rt[i][j] = new Int_t[64];
       }
        for(int j=0; j < 4; ++j)tpc_dt[i][j] = new Int_t[64];
   }
  //  tpc_timeref = new Int_t*[7];
    // [index][anode_no]
//     tpc_dt = new Int_t*[7];
   // tpc_a = new Int_t*[7];
  //  tpc_timeref = new Int_t[4];


//     for(int i=0; i < 7; ++i){
//
//     tpc_l[i] = new Int_t[2];
//     tpc_r[i] = new Int_t[2];
//
//
// //     tpc_dt[i] = new Int_t[4];
// //     tpc_a[i] = new Int_t[4];
//
//     }


    // SCI part
    de_21l  = 0;         /* dE SCI21 left            */
    de_21r  = 0;         /* de SCI21 right           */
    de_41l  = 0;         /* dE SCI41 left            */
    de_41r  = 0;         /* dE SCI41 right           */
    de_41u  = 0;         /* dE SCI41 up              */
    de_41d  = 0;         /* dE SCI41 down            */
    de_42l  = 0;         /* de SCI42 left            */
    de_42r  = 0;         /* de SCI42 right           */
    de_43l  = 0;         /* de SCI43 left            */
    de_43r  = 0;         /* de SCI43 right           */
    de_81l  = 0;         /* de SCI81 left            */
    de_81r  = 0;         /* de SCI81 right           */
//     de_21ld = 0;         /* dE SCI21 left delayed    */
//     de_21rd = 0;         /* de SCI21 right delayed   */
//     de_v1l  = 0;         /* dE veto1 left            */
//     de_v1r  = 0;         /* de veto1 right           */
//     de_v2l  = 0;         /* dE veto2 left            */
//     de_v2r  = 0;         /* dE veto2 right           */
//     de_v3   = 0;         /* dE veto3                 */


    dt_21l_21r  = 0;     /*                          */
    dt_41l_41r  = 0;     /*                          */
    dt_21l_41l  = 0;     /*                          */
    dt_21r_41r  = 0;     /*                          */
    dt_42l_42r  = 0;     /*                          */
    dt_43l_43r  = 0;     /*                          */
    dt_42l_21l  = 0;     /*                          */
    dt_42r_21r  = 0;     /*                          */
    dt_41u_41d  = 0;     /*                          */
    dt_81l_81r  = 0;     /*                          */
    dt_21l_81l  = 0;     /*                          */
    dt_21r_81r  = 0;     /*                          */

    // User multihit TDC

//     tdc_sc41l = new Int_t[10];
//     tdc_sc41r = new Int_t[10];
//     tdc_sc21l = new Int_t[10];
//     tdc_sc21r = new Int_t[10];
//     tdc_sc42l = new Int_t[10];
//     tdc_sc42r = new Int_t[10];
//     tdc_sc43l = new Int_t[10];
//     tdc_sc43r = new Int_t[10];
//     tdc_sc81l = new Int_t[10];
//     tdc_sc81r = new Int_t[10];
//     tdc_sc31l = new Int_t[10];
//     tdc_sc31r = new Int_t[10];
//     tdc_sc11 = new Int_t[10];
    // MUSIC1 part
    music_e1 = new Int_t[8];     /* Raw energy signals       */
    music_t1 = new Int_t[8];     /* Raw drift time           */
   // music_pres = new Int_t[3];   /* Music Druck              */
   // music_temp = new Int_t[3];   /* Music Temperatur         */

    // MUSIC2 part
    music_e2 = new Int_t[8];     /* Raw energy signals       */
    music_t2 = new Int_t[8];     /* Raw drift time           */

    // MUSIC3 part (OLD MUSIC)
    music_e3 = new Int_t[8];     /* Raw energy signals       */
    music_t3 = new Int_t[8];     /* Raw drift times          */


    /******************************************************************/
    /**CALIBRATION Parameters**/

    // MON data declarations

//    check_first_event        = new int[2];
//     scaler_channel_10khz = 0;//YT 20Jun
//     scaler_time_count        = new Long64_t[2];
//     scaler_spill_count       = new Long64_t[2]; //UInt_t
//     scaler_time_check_last   = new Long64_t[2];//UInt_t
//     scaler_spill_check_last      = new Long64_t[2];//UInt_t
//     check_increase_time      = new Long64_t[64];//UInt_t
//     check_increase_spill     = new Long64_t[64];//UInt_t
//     scaler_increase_event    = new Long64_t[64];//UInt_t
//     scaler_last_event        = new Long64_t[64];

    scaler_ch_1kHz=39; //ch7 of 2nd scaler
    scaler_ch_spillstart=8; //ch8 of 1st scaler
    scaler_check_first_event=1;
    //TGo4WinCond   *cMW_XSUM[13];
    //TGo4WinCond   *cMW_YSUM[13];

    ////condtition for control sum
    //TGo4WinCond *cTPC_CSUM[7][4];
    //TGo4PolyCond *cTPC_XY[7];

   // TGo4WinCond *cTPC_SC_TIMEREF[8];

///All this MON and MW stuff I took out (also in the header) since its not used A.K.M Jan 2022

    //coin  = new Int_t[16];
   // seetram         = 0;

    tmp_nhit_prev=0;
        for(int i=0; i<128; i++){
        nhit_v1190_tpcs2[i]=0;
        for(int j=0; j<64; j++) leading_v1190_tpcs2[i][j]=0;
        }


    focx_s2 = 0;         /*  FRS foci                */
    focy_s2 = 0;         /*                          */
    focx_s4 = 0;         /*                          */
    focy_s4 = 0;         /*                          */
    focx_s8 = 0;         /*  FRS foci                */
    focy_s8 = 0;         /*                          */
    angle_x_s2 = 0;      /*                          */
    angle_y_s2 = 0;      /*                          */
    angle_x_s4 = 0;      /*                          */
    angle_y_s4 = 0;      /*                          */
    angle_x_s8 = 0;      /*                          */
    angle_y_s8 = 0;      /*                          */

  tpc_x_s2_foc_21_22=-999.;
  tpc_y_s2_foc_21_22=-999.;
  tpc_x_s2_foc_23_24=-999.;
  tpc_y_s2_foc_23_24=-999.;
  tpc_x_s2_foc_22_24=-999.;
  tpc_y_s2_foc_22_24=-999.;
  tpc_x_s4=-999.;
  tpc_y_s4=-999.;
  tpc_angle_x_s2_foc_21_22=-999.;
  tpc_angle_y_s2_foc_21_22=-999.;
  tpc_angle_x_s2_foc_23_24=-999.;
  tpc_angle_y_s2_foc_23_24=-999.;
  tpc_angle_x_s2_foc_22_24=-999.;
  tpc_angle_y_s2_foc_22_24=-999.;
  tpc_angle_x_s4=-999.;
  tpc_angle_y_s4=-999.;

  tpc21_22_sc21_x = -999.;      /* SC21                     */
  tpc23_24_sc21_x = -999.;      /* SC21                     */
  tpc22_24_sc21_x = -999.;      /* SC21                     */
  tpc21_22_sc21_y = -999.;      /* SC21                     */
  tpc23_24_sc21_y = -999.;      /* SC21                     */
  tpc22_24_sc21_y = -999.;      /* SC21                     */

  tpc21_22_sc22_x = -999.;      /* SC22                     */
  tpc21_22_sc22_y = -999.;      /* SC22                     */
  tpc23_24_sc22_x = -999.;      /* SC22                     */
  tpc23_24_sc22_y = -999.;      /* SC22                     */
  tpc22_24_sc22_x = -999.;               /* SC22                     */
  tpc22_24_sc22_y = -999.;              /* SC22                     */

  tpc21_22_s2target_x = -999.;      /* S2TARGET                     */
  tpc23_24_s2target_x = -999.;      /* S2TARGET                     */
  tpc22_24_s2target_x = -999.;      /* S2TARGET                     */
  tpc21_22_s2target_y = -999.;      /* S2TARGET                     */
  tpc23_24_s2target_y = -999.;      /* S2TARGET                     */
  tpc22_24_s2target_y = -999.;      /* S2TARGET                     */

  tpc_sc41_x = -999.;      /* SC41                     */
  tpc_sc41_y = -999.;      /* SC41 Y                   */
  tpc_sc42_x = -999.;      /* SC42                     */
  tpc_sc42_y = -999.;      /* tracked SC42 Y pos       */
  tpc_sc43_x = -999.;      /* SC43                     */
  tpc_sc43_y = -999.;      /* SC43 Y                   */

  tpc_music41_x = -999.;      /* MUSIC41 x                     */
  tpc_music41_y = -999.;      /* tracked MUSIC41 Y pos       */
  tpc_music42_x = -999.;      /* MUSIC42 x                     */
  tpc_music42_y = -999.;      /* tracked MUSIC42 Y pos       */
  tpc_music43_x = -999.;      /* MUSIC43 x                     */
  tpc_music43_y = -999.;      /* tracked MUSIC43 Y pos       */
  tpc_s4target_x = -999.;     /* S4 target */
  tpc_s4target_y = -999.;     /* S4 target */


    // TPC part
//     tpc_x    = new Float_t[7];
//     tpc_y    = new Float_t[7];
//     b_tpc_xy = new Bool_t[7];
//     tpc_de = new Float_t[7];
//     b_tpc_de = new Bool_t[7];

//     tpc_csum = new Int_t*[7];
//     b_tpc_csum = new Bool_t*[7];



//     for(int i=0; i < 7; ++i){
//
//     tpc_csum[i] = new Int_t[4];
//     b_tpc_csum[i] = new Bool_t[4];
//
//     }
  
    //TPCs 21 & 22 @ S2 focus
    tpc_x_s2_foc_21_22      = 0;
    tpc_y_s2_foc_21_22      = 0;
    tpc_angle_x_s2_foc_21_22    = 0;
    tpc_angle_y_s2_foc_21_22    = 0;

    //TPCs 23 & 24 @ S2 focus
    tpc_x_s2_foc_23_24      = 0;
    tpc_y_s2_foc_23_24      = 0;
    tpc_angle_x_s2_foc_23_24    = 0;
    tpc_angle_y_s2_foc_23_24    = 0;

    //TPCs 22 & 24 @ S2 focus
    tpc_x_s2_foc_22_24      = 0;
    tpc_y_s2_foc_22_24      = 0;
    tpc_angle_x_s2_foc_22_24    = 0;
    tpc_angle_y_s2_foc_22_24    = 0;

    //TPCs 3 & 4 @ S2 focus (old tracking)
    tpc_x_s2_foc        = 0;
    tpc_y_s2_foc        = 0;
    tpc_angle_x_s2_foc      = 0;
    tpc_angle_y_s2_foc      = 0;

    //TPCs 41 & 42 @ s4 focus
    tpc_x_s4            = 0;
    tpc_y_s4            = 0;
    tpc_angle_x_s4      = 0;
    tpc_angle_y_s4      = 0;

    //TPCs 5 & 6 @ S4 OTPC (exp s388)
    tpc_x_s4_target2        = 0;
    tpc_y_s4_target2        = 0;


    //TPCs 3 & 4 @ S2 first Si tracking detector (exp s388)
    tpc_x_s2_target1        = 0;
    tpc_y_s2_target1        = 0;
    //      Float_t tpc_angle_x_s4_target2;
    //      Float_t tpc_angle_y_s4_target2;

   // tpc_mw_sc21_x = 0;      /* SC21 x                   */
    tpc_sc41_x = 0;      /* SC41 x                   */
  //  tpc_sc21_y = 0;      /* SC21 y                   */
    tpc_sc41_y = 0;      /* SC41 y                   */

    music1_x1 = 0;       /* parameters to calibrate  */
    music1_x2 = 0;       /* parameters to calibrate  */
    music1_x3 = 0;       /* parameters to calibrate  */
    music1_x4 = 0;       /* parameters to calibrate  */
    music1_y1 = 0;       /* parameters to calibrate  */
    music1_y2 = 0;       /* parameters to calibrate  */
    music1_y3 = 0;       /* parameters to calibrate  */
    music1_y4 = 0;       /* parameters to calibrate  */
    music2_x  = 0;       /* MUSIC1,2 positions       */

 for(int module=0; module<VFTX_N; module++){
    for(int channel=0; channel<VFTX_MAX_CHN; channel++) {
      for(int hit=0; hit<VFTX_MAX_HITS; hit++) {
    vftx_cc[module][channel][hit] = 0;
    vftx_ft[module][channel][hit] = 0;
      }
      vftx_mult[module][channel] = 0;
    }
 }

    /******************************************************************/
    /*** ANALYSIS Parameters ***/

    /*** MUSIC Conditions ***/

        // MUSIC part
        music1_anodes_cnt = 0;
        music2_anodes_cnt = 0;
        music3_anodes_cnt = 0;

        music1_x_mean = -999.;
        music2_x_mean = -999.;
        music3_x_mean = -999.;

        music_b_e1 = new Bool_t[8];
        music_b_t1 = new Bool_t[8];
        music_b_e2 = new Bool_t[8];
        music_b_t2 = new Bool_t[8];
        music_b_e3 = new Bool_t[4];
        music_b_t3 = new Bool_t[4];

        for(int i = 0; i < 8; ++i){

        music_b_e1[i] = false;
        music_b_t1[i] = false;
        music_b_e2[i] = false;
        music_b_t2[i] = false;
        if(i < 4) music_b_e3[i] = false;
        if(i < 4) music_b_t3[i] = false;

        }

        b_de1 = false;
        b_de2 = false;
        b_de3 = false;

        de = new Float_t[3];
        de_cor = new Float_t[3];

        for(int i = 0; i < 3; ++i){

            de[i] = 0;
        de_cor[i] = 0;
        }

        b_dt3 = false;

        x1_mean = 0;



    //SCI part
    sci_l = new Float_t[12];
    sci_r = new Float_t[12];
    sci_e = new Float_t[12];
    sci_tx = new Float_t[12];
    sci_x = new Float_t[12];
    sci_tofll2 = 0;
    sci_tofrr2 = 0;
    sci_tof2 = 0;
    sci_tofll3 = 0;
    sci_tofrr3 = 0;
    sci_tof3 = 0;
    sci_tofll5 = 0;
    sci_tofrr5 = 0;
    sci_tof5 = 0;
    sci_tofll4 = 0;
    sci_tofrr4 = 0;
    sci_tof4 = 0;
    sci_tof2 = 0; sci_tof3 = 0; sci_tof4 = 0;


    sci_b_l = new Bool_t[12];
    sci_b_r = new Bool_t[12];
    sci_b_e = new Bool_t[12];
    sci_b_tx = new Bool_t[12];
    sci_b_x = new Bool_t[12];
    sci_b_u5 = false;
    sci_b_d5 = false;
    sci_b_ty5 = false;
    sci_b_y5 = false;
    sci_b_tofll2 = false;
    sci_b_tofrr2 = false;
    sci_b_tofll3 = false;
    sci_b_tofrr3 = false;
    sci_b_tofll4 = false;
    sci_b_tofrr4 = false;

    for(int i = 0; i < 12; ++i){

        sci_l[i] = 0;
        sci_r[i] = 0;
        sci_e[i] = 0;
        sci_tx[i] = 0;
        sci_x[i] = 0;

        sci_b_l[i] = false;
        sci_b_r[i] = false;
        sci_b_e[i] = false;
        sci_b_tx[i] = false;
        sci_b_x[i] = false;
    }

    // ID part
    id_x2 = 999;
    id_y2 = 999;
    id_a2 = 999;
    id_b2 = 999;
    id_x4 = 999;
    id_y4 = 999;
    id_a4 = 999;
    id_b4 = 999;
    id_x8 = 999;
    id_y8 = 999;
    id_a8 = 999;
    id_b8 = 999;
    for(int i=0; i<7; ++i){
    tpc_x[i] = 999;
    tpc_y[i] = 999;
    }

    tpc_sc41_x = -999.;      /* SC41                     */
    tpc_sc41_y = -999.;      /* SC41 Y                   */
    tpc_sc42_x = -999.;      /* SC42                     */
    tpc_sc42_y = -999.;      /* tracked SC42 Y pos       */
    tpc_sc43_x = -999.;      /* SC43                     */
    tpc_sc43_y = -999.;      /* SC43 Y                   */

    tpc_music41_x = -999.;      /* MUSIC41 x                     */
    tpc_music41_y = -999.;      /* tracked MUSIC41 Y pos       */
    tpc_music42_x = -999.;      /* MUSIC42 x                     */
    tpc_music42_y = -999.;      /* tracked MUSIC42 Y pos       */
    tpc_music43_x = -999.;      /* MUSIC43 x                     */
    tpc_music43_y = -999.;      /* tracked MUSIC43 Y pos       */
    tpc_s4target_x = -999.;     /* S4 target */
    tpc_s4target_y = -999.;     /* S4 target */

   // MultiHitTDC

   mhtdc_tof8121 = -999.9;

   mhtdc_tof4221 = -999.9;
   mhtdc_tof4321 = -999.9;
   mhtdc_tof3121 = -999.9;

   mhtdc_sc31lr_dt = -999.9;
   mhtdc_sc41lr_dt = -999.9;
   mhtdc_sc42lr_dt = -999.9;
   mhtdc_sc43lr_dt = -999.9;
   mhtdc_sc81lr_dt = -999.9;

   mhtdc_sc31lr_x = -999.9;
   mhtdc_sc41lr_x = -999.9;
   mhtdc_sc42lr_x = -999.9;
   mhtdc_sc43lr_x = -999.9;
   mhtdc_sc81lr_x = -999.9;

    id_b_x2 = false;
    id_b_x4 = false;


   for(int i=0; i<2;i++){
    id_brho[i]=0;      /* position-corr. BRho      */
    id_rho[i]=0;       /* Position-corrected Rho   */
    }

    id_beta = 0;        /* Beta from TOF            */
    id_beta3 = 0;        /* Beta from TOF            */
    id_gamma = 0;       /* Gamma from TOF           */
    id_AoQ = 0;
    id_AoQ_corr = 0;
    id_dEdeg = 0;
    id_dEdegoQ = 0;

    id_v_cor = 0;       /* Velocity correction  */
    id_v_cor2 = 0;      /* Velocity correction TUM 2 */
    id_v_cor3 = 0;      /* Velocity correction Old Music */
    id_z = 0;
    id_z2 = 0;
    id_z3 = 0;
 
   // id_trigger = 0;
//     id_scal_seconds = 0;
//     id_scal_geL = 0;
//     id_scal_sc21 = 0;
//     id_scal_sc41 = 0;
//     id_scal_sc42 = 0;
//     id_scal_sc43 = 0;
//     id_scal_sc81 = 0;
    id_de_s2tpc =0.0;
    id_b_de_s2tpc = kFALSE;
    id_z_sc81 = 0.0;
    id_v_cor_sc81 = 0.0;
    id_b_z_sc81 = kFALSE;
    id_z_s2tpc =0.0;
    id_v_cor_s2tpc =0.0;
    id_b_z_s2tpc = kFALSE;

    id_b_AoQ = false;
    id_b_z = false;
   // id_b_AoQ_s2s8    = kFALSE;

    id_b_z2 = false;
    id_b_z3 = false;
    //id_b_x2AoQ = false;

//     id_b_x2AoQ = new Bool_t[5];
//     id_b_x4AoQ = new Bool_t[5];
//     id_b_x4AoQ_Z = new Bool_t[5];
//     id_b_z_AoQ = new Bool_t[5];
 //   id_b_music_z = new Bool_t[5];


    mhtdc_sc21lr_x = new Float_t[10];
    mhtdc_sc21lr_dt= new Float_t[10];
    mhtdc_sc22lr_x = new Float_t[10];
    mhtdc_sc22lr_dt= new Float_t[10];
    mhtdc_tof4121 = new Float_t[10];
    mhtdc_tof4122 = new Float_t[10];
    id_mhtdc_delta_s2s4=new Float_t[10];
    id_mhtdc_beta_s2s4 = new Float_t[10];
    id_mhtdc_gamma_s2s4 = new Float_t[10];
    id_mhtdc_aoq_s2s4 = new Float_t[10];
    id_mhtdc_aoq_corr_s2s4 = new Float_t[10];
    id_mhtdc_z_music41  = new Float_t[10];
    id_mhtdc_z_music42 = new Float_t[10];
    id_mhtdc_v_cor_music41 = new Float_t[10];
    id_mhtdc_v_cor_music42= new Float_t[10];

  for(int i=0; i<10;i++) {
  mhtdc_tof4121[i] = -999.9;
  mhtdc_tof4122[i] = -999.9;
  id_mhtdc_beta_s2s4[i]  = -999;
  id_mhtdc_gamma_s2s4[i] = -999;
  id_mhtdc_aoq_s2s4[i]   = -999;
  id_mhtdc_aoq_corr_s2s4[i]   = -999;

  id_mhtdc_z_music41[i]  = -999;
  id_mhtdc_z_music42[i] =-999;
  id_mhtdc_v_cor_music41[i] =0;
  id_mhtdc_v_cor_music42[i] =0;

  mhtdc_sc21lr_x[i]=-999;
  mhtdc_sc21lr_dt[i]=-999;
  mhtdc_sc22lr_x[i]=-999;
  mhtdc_sc22lr_dt[i]=-999;
  id_mhtdc_delta_s2s4[i] = -999;
}

//     for(int i = 0; i < 5; i++){
//         id_b_x2AoQ[i] = false;
//         id_b_x4AoQ[i] = false;
//         id_b_x4AoQ_Z[i] = false;
//         id_b_z_AoQ[i] = false;
//         id_b_music_z[i] = false;
// 
//     }

    //firsttimestamp = 0;
  //  firstevent = false;

    ts = 0;  // relative time from start of the spill
    ts2 = 0;  // relative time from start of the spill does not reset at end extraction

    time_in_ms =0;
    spill_count =0;
    ibin_for_s =0;
    ibin_for_100ms =0;
    ibin_for_spill =0;
    ibin_clean_for_s=0;
    ibin_clean_for_100ms=0;
    ibin_clean_for_spill=0;
    // MRTOF part :

    Setup_Conditions();
    FRS_GainMatching();
    WR_Check(ts_mins);
}

//---------------------------------------------------------------

FRS_Detector_System::~FRS_Detector_System(){



   // for(int i = 0; i < 32; ++i){

   // delete[] vme2s[i];           // User TDC (V1290)
    //delete[] vme2s_trailing[i];  // User TDC (V1290)

    //delete[] leading_v1290_main[i];           // Mtof TDC (V1290)
    //delete[] trailing_v1290_main[i];  // Mtof TDC (V1290)

//    delete[] nhit5[i];       // multiplicity (V1290)
    //delete[] nhit_v1290_main[i];       // multiplicity (V1290)

    //}
    /*delete[] vme2s;           // User TDC (V1290)
    delete[] vme2s_trailing;  // User TDC (V1290) */

    //delete[] leading_v1290_main;           // Mtof TDC (V1290)
    //delete[] trailing_v1290_main;  // Mtof TDC (V1290)

   // delete[] nhit5;       // multiplicity (V1290)
  //  delete[] nhit_v1290_main;       // multiplicity (V1290)

    delete[] mhtdc_sc21lr_x;
    delete[] mhtdc_sc21lr_dt;
    delete[] mhtdc_sc22lr_x;
    delete[] mhtdc_sc22lr_dt;
    delete[] id_mhtdc_delta_s2s4;
    delete[] mhtdc_tof4121;
    delete[] mhtdc_tof4122;
    delete[] id_mhtdc_beta_s2s4;
    delete[] id_mhtdc_gamma_s2s4;
    delete[] id_mhtdc_aoq_s2s4;
    delete[] id_mhtdc_aoq_corr_s2s4;
    delete[] id_mhtdc_z_music41;
    delete[] id_mhtdc_z_music42;
    delete[] id_mhtdc_v_cor_music41;
    delete[] id_mhtdc_v_cor_music42;

    delete[] vme2scaler;         // User Crate Messhure
    delete[] vme3scaler;         // User Crate Messhure

    //delete[] firstTS;

    //delete[] previousTimeStamp;

    /*******************************************************************/
    /***SORT STUFF***/

   // delete[] ts_word; //for the titris time stammping
    //delete[] tsys_word; //for the system time

    // scaler readings
    //delete[] sc_long; //changed from 32 to 64 (10.07.2018)
   // delete[] sc_long2;


    // part of MW parameter
//     delete[]  mw_an;       /*  anode time              */
//     delete[] mw_xl;       /*  Rohdaten                */
//     delete[] mw_xr;       /*                          */
//     delete[] mw_yu;       /*                          */
//     delete[] mw_yd;       /*                          */
    

    // User multihit TDC

//     delete[] tdc_sc41l;
//     delete[] tdc_sc41r;
//     delete[] tdc_sc21l;
//     delete[] tdc_sc21r;
//     delete[] tdc_sc42l;
//     delete[] tdc_sc42r;
//     delete[] tdc_sc43l;
//     delete[] tdc_sc43r;
//     delete[] tdc_sc81l;
//     delete[] tdc_sc81r;
//     delete[] tdc_sc31l;
//     delete[] tdc_sc31r;
//     delete[] tdc_sc11;

    // MUSIC1 part
    delete[]  music_e1;     /* Raw energy signals       */
    delete[] music_t1;     /* Raw drift time           */
 //   delete[] music_pres;   /* Music Druck              */
  //  delete[]  music_temp;   /* Music Temperatur         */

    // MUSIC2 part
    delete[] music_e2;     /* Raw energy signals       */
    delete[] music_t2;     /* Raw drift time           */

    // MUSIC3 part (OLD MUSIC)
    delete[] music_e3;     /* Raw energy signals       */
    delete[] music_t3;     /* Raw drift times          */


    //Proc_iterator=0;

    /******************************************************************/
    /**CALIBRATION Parameters**/
///all the MON and MW stuff I removed since it isnt used A.K.M Jan 2022
    
    // TPC part //(HAPOL-25/03/06) 6 TPCs each one with 2 delay lines each!!
//     //7 TPCs (4 at S2, 2 at S4 and one at S3) 03.07.2018 SB
    
    for(int i=0; i < 7; ++i){

    delete[] tpc_l[i];
    delete[] tpc_r[i];
    delete[] tpc_a[i];
    for(int j=0; j < 2; ++j){
        delete[] tpc_lt[i][j];
        delete[] tpc_rt[i][j];
    }
    for(int j=0; j < 4; ++j) delete[] tpc_dt[i][j];
    delete[] tpc_dt[i];
    delete[] tpc_lt[i];
    delete[] tpc_rt[i];
    }
    delete[] tpc_l;
    delete[] tpc_r;
    delete[] tpc_dt;
    delete[] tpc_a;
    delete[] tpc_rt;
    delete[] tpc_lt;
//     delete[] tpc_x;
//     delete[] tpc_y;
//     delete[] b_tpc_xy;
//     delete[] tpc_de;
//     delete[] b_tpc_de;

//     for(int i=0; i < 7; ++i){
//
//     delete[] tpc_csum[i];
//     delete[] b_tpc_csum[i];
//
//     }
//     delete[] tpc_csum;
//     delete[] b_tpc_csum;

//    delete[] dssd_e; //[3][2][16]

    /******************************************************************/
    /*** ANALYSIS Parameters ***/

    /*** MUSIC Conditions ***/

    // MUSIC part

    delete[] music_b_e1;
    delete[] music_b_t1;
    delete[] music_b_e2;
    delete[] music_b_t2;
    delete[] music_b_e3;
    delete[] music_b_t3;

    delete[] de;
    delete[] de_cor;

    //SCI part
    delete[] sci_l;
    delete[] sci_r;
    delete[] sci_e;
    delete[] sci_tx;
    delete[] sci_x;

    delete[]  sci_b_l;
    delete[]  sci_b_r;
    delete[]  sci_b_e;
    delete[]  sci_b_tx;
    delete[]  sci_b_x;

    // ID part
//     for(int i=0; i<2;i++){
//     id_brho[i]=0;      /* position-corr. BRho      */
//     id_rho[i]=0;       /* Position-corrected Rho   */
//     }

//     delete[] id_b_x2AoQ;
//     delete[] id_b_x4AoQ;
// 
//     delete[] id_b_x4AoQ_Z;
//     delete[] id_b_z_AoQ;
//     delete[] id_b_music_z;
    
    ///Setup file

    for(int i = 0; i < 4; ++i){
       for(int j = 0; j < 7; ++j) delete[] lim_csum[i][j];
        delete[] lim_csum[i];
       
    }
    for(int i = 0; i < 13; ++i){
    delete[] lim_xsum[i];
    delete[] lim_ysum[i];
    }
    delete[] lim_csum;
    delete[] lim_xsum;
    delete[] lim_ysum;
    
    for(int i = 0; i < 8; ++i){
    delete[] cMusic1_E[i];
    delete[] cMusic1_T[i];
    delete[] cMusic2_E[i];
    delete[] cMusic2_T[i];
    if(i<4){
    delete[] cMusic3_T[i];
    delete[] cMusic3_E[i];
        }
    }
    delete[] cMusic1_E;
    delete[] cMusic1_T;
    delete[] cMusic2_E;
    delete[] cMusic2_T;
    delete[] cMusic3_E;
    delete[] cMusic3_T;
    
    delete[] cSCI_L;
    delete[] cSCI_R;
    delete[] cSCI_E;
    delete[] cSCI_Tx;
    delete[] cSCI_X;
    
    delete[] cSCI_LL2;
    delete[] cSCI_RR2;
    delete[] cSCI_LL3;
    delete[] cSCI_RR3;
    delete[] cSCI_LL4;
    delete[] cSCI_RR4;
    delete[] cSCI_LL5;
    delete[] cSCI_RR5;
    
    delete[] cID_x2;
    delete[] cID_x4;
    delete[] cID_Z_Z;
    
}

//---------------------------------------------------------------

void FRS_Detector_System::Process_MBS(TGo4MbsSubEvent* psubevt){

 skip=false;
     // cout<<"frs->dist_focS4 !!!!!!!!" << frs->dist_focS4<< endl;
   // cout<<"frs->bfield[0] " << frs->bfield[0]<< " frs->bfield[1]  " << frs->bfield[1] <<" frs->bfield[2] " << frs->bfield[2]<< " frs->bfield[3]  " << frs->bfield[3]<< endl;
   // Setup_Parameters();



    FRS_Unpack(psubevt);

    ///This is to use SCI 22 position for runs < 144 in S452 where the TPC delay was set incorrectly.
    string data = "";
    data = std::string(get_filename());
   size_t pos1, pos2, pos3;
   int filenumber;
   pos1 = data.find("S452");
  if(pos1!=string::npos){
     pos2 = data.find("f",pos1+1);
     pos3 = data.find("_",pos2+1);
     filenumber = stoi(data.substr(pos2+1,(pos3-pos2)-1));
  }

  if(filenumber<144){
    id->x_s2_select=3;
    id->mhtdc_s2pos_option=1;
  }
      if(filenumber>143){
	id->x_s2_select=1;
	id->mhtdc_s2pos_option=2;
      }
      
      if(filenumber<92){

      //index 2 for Sc21
     sci->x_a[0][2] =    830.4096;  //
     sci->x_a[1][2] =   -0.24044;  // 
     sci->x_a[2][2] =  0.000000;  //
     sci->x_a[3][2] =  0.000000;  //
     sci->x_a[4][2] =  0.000000;  //
     sci->x_a[5][2] =  0.000000;  //
     sci->x_a[6][2] =  0.000000;  //
      //index 3 for Sc22
     sci->x_a[0][3] =  1192.04677;  
     sci->x_a[1][3] = -0.3507;  
     sci->x_a[2][3] =  0.0000; 
     sci->x_a[3][3] =  0.000000;  
     sci->x_a[4][3] =  0.000000;  
     sci->x_a[5][3] =  0.000000;  
     sci->x_a[6][3] =  0.000000;  
  }
      else if(filenumber == 92) {
   
    //index 2 for Sc21   calibration is the same as files from f073 to f091 
     sci->x_a[0][2] =    830.4096;  //
     sci->x_a[1][2] =   -0.24044;  // 
     sci->x_a[2][2] =  0.000000;  //
     sci->x_a[3][2] =  0.000000;  //
     sci->x_a[4][2] =  0.000000;  //
     sci->x_a[5][2] =  0.000000;  //
     sci->x_a[6][2] =  0.000000;  //
        //index 3 for Sc22
     sci->x_a[0][3] =  724.7298;  
     sci->x_a[1][3] = -0.3574;  
     sci->x_a[2][3] =  0.0000; 
     sci->x_a[3][3] =  0.000000;  
     sci->x_a[4][3] =  0.000000;  
     sci->x_a[5][3] =  0.000000;  
     sci->x_a[6][3] =  0.000000;
  }
      else {
    //index 2 for Sc21
  sci->x_a[0][2] =    477.29;  // quickly done for s452 on 08.03.2021 (from online)
  sci->x_a[1][2] =   -0.2619;  // quickly done for s452 on 08.03.2021 (from online)
  sci->x_a[2][2] =  0.000000;  //
  sci->x_a[3][2] =  0.000000;  //
  sci->x_a[4][2] =  0.000000;  //
  sci->x_a[5][2] =  0.000000;  //
  sci->x_a[6][2] =  0.000000;  //
  
  //index 3 for Sc22
  sci->x_a[0][3] =  627.52;  // quickly done for s452 on 08.03.2021 (from online)
  sci->x_a[1][3] = -0.3751;  //quickly done for s452 on 08.03.2021 (from online)
  sci->x_a[2][3] =  0.0000;  //
  sci->x_a[3][3] =  0.000000;  //
  sci->x_a[4][3] =  0.000000;  //
  sci->x_a[5][3] =  0.000000;  //
  sci->x_a[6][3] =  0.000000;  //
      }


   // if(skip==false){
    FRS_Sort();
    FRS_Calib();
    FRS_Anl();
    //}

}

//-----------------------------------------------------------------//
//--------------------- UNPACKER STUFF ----------------------------//
//-----------------------------------------------------------------//

void FRS_Detector_System::FRS_Unpack(TGo4MbsSubEvent* psubevent){

  psubevt = psubevent;
  pdata = psubevt->GetDataField();



   len = 0;
   //vme_chn;
    bool skip_subevent=false;
 WR_Check(ts_mins);
// ///*    Int_t event_flag = *pdata++;  len++; // 0x200 or 0x000 etc. 20200123MERGE
//    if( !( (psubevt->GetType() == 10) && (psubevt->GetSubtype() == 1))  &&  //(t,s)=(12,1)->(10,1) modified on 2019/11/13
//           !( (psubevt->GetType() == 12) && (psubevt->GetSubtype() == 1))  &&  //(t,s)=(12,1)->(10,1) modified on 2019/11/13
//           !( (psubevt->GetType() == 36) && (psubevt->GetSubtype() == 3600) ) &&
//           !( (psubevt->GetType() == 88) && (psubevt->GetSubtype() == 8800) ) )
//         {  // for all data
//           std::cout << "getprocid  " << psubevt->GetProcid()  << std::endl;
//           std::cout << "getsubtype " << psubevt->GetSubtype() << std::endl;
//           std::cout << "gettype " << psubevt->GetType() << std::endl;
//           std::cout << "Wrong subevent type " << psubevt->GetType() << std::endl;
//           if( 3700==psubevt->GetSubtype() || 3800== psubevt->GetSubtype() ){//blacklist
//         std::cout << "bad event, skip this event for moment" << std::endl;
//         //return kFALSE;
//
//           skip_subevent=true; // skip subevent SL
//          // continue;
//         }
//         }
//
//        // if(skip_subevent==false){

 //  cout<<" ProcID "<<psubevt->GetProcid()<<" SubType " << psubevt->GetSubtype() << endl;

   if(psubevt->GetProcid()==10 && psubevt->GetSubtype()==1){
   for(int i=0; i<32; i++){
            for(int j=0; j<10; j++){
       leading_v1290_main[i][j]=0;

            }

       }
       for(int i=0; i<10; i++){
           mhtdc_tof4121[i]=-999;
           mhtdc_tof4122[i]=-999;
       }
    }
    if( (psubevt->GetType() == 36) && (psubevt->GetSubtype() == 3600) ) //tpat
   {
      Int_t lenMax = (psubevt->GetDlen()-2)/2;
          Int_t *pdata = psubevt->GetDataField();
        // int tpat_len = 0xFF & (*pdata) ;
          for(int ii=0; (ii<lenMax && ii<32) ; ii++){
             tpat_main[ii] = *pdata;
             // printf("write tpat data %d = 0x%08x\n",ii,tpat_main[ii]);
             pdata++;
          }
            if (lenMax >= 4) { utpat = tpat_main[4] & 0b1111111111111111 ; }
            // uphystrig takes priority lower to highest so I will loop desecnding
            for (int it=16;it>0;--it)
            {
              if ((utpat & ((Int_t) pow(2,it-1)))>0){
                uphystrig = it;
                unbtrig += 1;
              }
            }
            if(unbtrig == 2){
                  for (int it=0;it<16;it++)
                  {
                if ((utpat & ((Int_t) pow(2,it)))>0) {
                umaxtrig = it+1;
                }
                  }
            }
          //  continue;
   }
    if ((psubevt->GetType() == 12) && (psubevt->GetSubtype() == 1)) {
   Int_t *pdata = psubevt->GetDataField();
  Int_t len = 0;


            lenMax = (psubevt->GetDlen()-2)/2;
            Int_t event_flag = *pdata++;  len++;  *pdata++;  len++;// skip the first two words of an event
           // if(*pdata != ((Int_t) 0xbabababa)){ std::cout<<"E> ProcID :"<< psubevt->GetProcid() << "First Barrier missed!" << *pdata<< std::endl; }
            pdata++; len++;
  for(int i=0; i<21; i++) for(int j=0; j<32; j++) vme_main[i][j]=0;

  switch(psubevt->GetProcid())
    {

   // if ((psubevt->GetType() == 12) && (psubevt->GetSubtype() == 1)) {
    //===========
    case 30: ///FRS Crate


    { // start of v830 (do not remove this bracket)
       Int_t isADCgeo2 ; isADCgeo2= 0 ;
            Int_t scalertest; scalertest = getbits(*pdata,2,5,12) ;
 //		std::cout <<" should be 72 "<<scalertest <<endl ;
		if (scalertest == 72) // 72 is 0x48 for the header and number of words
		{
		 // start of v830 (do not remove this bracket)
	    Int_t vme_geo = getbits(*pdata,2,12,5);
	    Int_t vme_type = getbits(*pdata,2,9,3);
	    Int_t vme_nlw =  getbits(*pdata,2,3,6);

	    pdata++; len++;
	    //printf("Proc ID 30, geo %d, type %d\n", vme_geo, vme_type);
	    if(vme_type!=4){   std::cout<<"E> Scaler type missed match ! Proc ID 30 GEO "<<vme_geo<<" "<<" type 4 =/="<<vme_type<<std::endl; break ;  }
	    for(int i_ch=0; i_ch<vme_nlw; i_ch++){
	      scaler_frs[i_ch] = *pdata;
	      ////               printf("scaler_frs[ch=%d] = %d\n",i_ch,*pdata);
	      pdata++; len++;
	    }
	   } //end of V830

        //----- v775 TDC/V785 ADC -----//
        while (len < lenMax){
          /* read the header longword and extract slot, type & length  */
          Int_t vme_chn = 0;
          Int_t vme_geo = getbits(*pdata,2,12,5);
          Int_t vme_type = getbits(*pdata,2,9,3);
          Int_t vme_nlw =  getbits(*pdata,1,9,6);
          pdata++; len++;
     if (2 == vme_geo){ isADCgeo2=1 ; }
          /* read the data */
          if ((vme_type == 2) && (vme_nlw > 0)) {
            for(int i=0;i<vme_nlw;i++) {
              vme_geo = getbits(*pdata,2,12,5);
              vme_type = getbits(*pdata,2,9,3);
              vme_chn = getbits(*pdata,2,1,5);
              vme_frs[vme_geo][vme_chn] = getbits(*pdata,1,1,16);
              ////        printf("vme_frs[geo=%d][ch=%d] = %d\n",vme_geo,vme_chn,getbits(*pdata,1,1,16));
             // cout<<"vme_frs " << vme_frs[vme_geo][vme_chn] <<vme_frs[vme_geo][vme_chn] << " vme_geo " <<vme_geo << " vme_chn " <<vme_chn << endl;
              pdata++; len++;
            }
	      }

	      /* sanity check at the end of a v7x5 unpacking */
	  vme_type = getbits(*pdata,2,9,3);
     if (vme_type != 4 ) {std::cout <<"issue in unpacking Proc Id 30, existing" <<std::endl ; break ; }
      pdata++; len++;
           }  /* end of the while... loop  */

           if (1 == isADCgeo2 )
    {
	   for (int i =0 ; i < 32 ; i++)
	   {
	    vme_frs[3][i] = vme_frs[2][i] ;
	   }
	 }
    }
           break;


    //==========
    case 10:  /// Main crate

      if((psubevt->GetType() == 10) && (psubevt->GetSubtype() == 1) && lenMax < 15) // in this case, time stamp data.
      {

    int ii =0;
    while(len < lenMax){
       timestamp_main[ii] = *pdata;
      pdata++; len++; ii++;
    }
    break;
      }
    ///v1290 TDC
    if (len < lenMax){

      Int_t vme_geo = getbits(*pdata,1,1,5);
      Int_t vme_type = getbits(*pdata,2,12,5);
      pdata++; len++;
      Int_t multihit = 0;//, counter = 0;
      for(int i=0; i<32; i++) for(int j=0; j<2; j++)nhit_v1290_main[i][j]=0;


#ifdef DEBUG
      std::cout<<"mTDC geo = "<<vme_geo<<", type = "<<vme_type<<std::endl;
#endif

      if (vme_type == 8)
        {
          while (len < lenMax)
        {
#ifdef DEBUG
          std::cout<<"word : "<<std::bitset<32>(*pdata)<<" ";
#endif
          vme_type = getbits(*pdata,2,12,5);
          if(vme_type==1) // headerTDC
            {
              pdata++; len++;
            }
          //multihit = 0;
#ifdef DEBUG
          std::cout<<"reading :"<<vme_type<<std::endl;
#endif
          vme_type = getbits(*pdata,2,12,5);
#ifdef DEBUG
          std::cout<<"word : "<<std::bitset<32>(*pdata)<<" type:"<<vme_type<<" ";
#endif
          if(vme_type == 0)
            {

              /// this indicates a TDC measurement
              Int_t vme_chn = getbits(*pdata,2,6,5);
              Int_t LeadingOrTrailing = getbits(*pdata,2,11,1);
              Int_t value = getbits(*pdata,1,1,21);

              multihit =  nhit_v1290_main[vme_chn][LeadingOrTrailing];
//             cout<<"TDC!!!!!" << "vme_chn " << vme_chn<< " LeadingOrTrailing " <<LeadingOrTrailing << " value " <<value <<" multihit " <<multihit << endl;
#ifdef DEBUG
              std::cout << "     tdc vme_chn = " << vme_chn;
              std::cout << " multihit: " << multihit << " ";
#endif

              if (multihit >= 10)
            {
              pdata++; len++;
              continue;
            }

              if(LeadingOrTrailing == 0)
            {
#ifdef DEBUG
              std::cout << " +-> tdc L value = " << value << std::endl;
#endif
              if (value > 0)
                {
                   leading_v1290_main[vme_chn][multihit] = value;
                 //  cout<<"222Proc ID "<<psubevt->GetProcid()<<" SubType "  <<psubevt->GetSubtype() <<" vme_chn " <<vme_chn << endl;
                // cout<<"leading_v1290_main[vme_chn][multihit] " <<leading_v1290_main[vme_chn][multihit] << " vme_chn " << vme_chn << " multihit " <<multihit << endl;
                }
            }

              else
            {
#ifdef DEBUG
              std::cout << " +-> tdc T value = " << value << std::endl;
#endif
              if (value > 0)
                 trailing_v1290_main[vme_chn][multihit] = value;
            }
               nhit_v1290_main[vme_chn][LeadingOrTrailing]++;
          //  cout<<"2nd pass nhit_v1290_main" << nhit_v1290_main[vme_chn][LeadingOrTrailing] <<" vme_chn " <<vme_chn << " LeadingOrTrailing " <<LeadingOrTrailing << endl;
              pdata++; len++;
            }
          else
            {
              // TDC trailer vme_type == 3
#ifdef DEBUG
              std::cout<<"\n";
#endif
           //   if(vme_type != 3 && vme_type !=16)
            //std::cout<<"E> MTDC strange type :"<<vme_type<<std::endl;
              if(vme_type==16)
            {
              Int_t vme_geoEnd = getbits(*pdata,1,1,5);
             // if(vme_geo!=vme_geoEnd)
            //    std::cout<<"E> MTDC strange end buffer header :"<<vme_type<<" "<<vme_geo<<" != "<<vme_geoEnd<<std::endl;

              pdata++; len++;
              break;
            }
              pdata++; len++;
            }
           } ///while len loop
         }///if type==8
       }///end if len more due to strange logic // end of V1290



//   if(*pdata != 0xbabababa) {
//     std::cout<<"E> ProcID 10 : Barrier-3 missed !" << std::endl;
//
//      // break;
// }
      pdata++; len++;

      //----- Next is V830 Scaler-----
     // if(ModSetup->Nb_Scaler > 0)
      {// start of v830 (do not remove this bracket)

      // read the header longword and extract slot, type & length
      Int_t vme_geo = getbits(*pdata,2,12,5);
      Int_t vme_type = getbits(*pdata,2,9,3);
      Int_t vme_nlw =  getbits(*pdata,2,3,6);

          pdata++; len++;

        for(int i_ch=0; i_ch<vme_nlw; i_ch++){
          scaler_main[i_ch] = *pdata;
          //////         printf("scaler_main[ch=%d] = %d\n",i_ch,*pdata);
          pdata++; len++;
        }
          } ///end of V830

     ///--------the rest of the unpacking...V792--------


    //  while (len < (psubevt->GetDlen()-2)/2)
    {

      Int_t vme_chn = 0;
      Int_t vme_geo = getbits(*pdata,2,12,5);
      Int_t vme_type = getbits(*pdata,2,9,3);
      Int_t vme_nlw =  getbits(*pdata,1,9,6);

      pdata++; len++;
      // cout<<"1vme_geo " << vme_geo <<" vme_type " << vme_type << " vme_chn " <<vme_chn << endl;
      #ifdef DEBUG
          std::cout<<"data "<<vme_geo<<" "<<vme_type<<" "<<vme_nlw<<" idmod:"<<IdMod<<std::endl;
    #endif


      /// read the data
     if(vme_type == 6){

              // not valid data !
          }

          if ((vme_type == 2) && (vme_nlw > 0)){
            for(int i=0;i<vme_nlw;i++){

              vme_geo = getbits(*pdata,2,12,5);
              vme_type = getbits(*pdata,2,9,3);
              vme_chn = getbits(*pdata,2,1,5);
//               cout<<"2vme_geo " << vme_geo <<" vme_type " << vme_type << " vme_chn " <<vme_chn << endl;
              vme_geo = 4 ;
              vme_main[vme_geo][vme_chn] = getbits(*pdata,1,1,16);
             // int test = vme_main[4][vme_chn]&0xfff;
//cout<<"vme_main[4][vme_chn] " <<vme_main[4][vme_chn] <<" test "<<test<<  " vme_geo " <<vme_geo << " vme_chn " <<vme_chn<< " psubevt->GetProcid() " <<psubevt->GetProcid() <<endl;
               pdata++; len++;
            }

             /// read and ignore the expected "end-of-block" longword
            pdata++; len++;
          }
        }  /// end of the while... loop

//     //--------unpacking...2nd V792--------
//     {
//       Int_t vme_chn = 0;
//       Int_t vme_geo = getbits(*pdata,2,12,5);
//       Int_t vme_type = getbits(*pdata,2,9,3);
//       Int_t vme_nlw =  getbits(*pdata,1,9,6);
//       pdata++; len++;
//
// #ifdef DEBUG
//       std::cout<<"data "<<vme_geo<<" "<<vme_type<<" "<<vme_nlw<<" idmod:"<<IdMod<<std::endl;
// #endif
//       // read the data
//       if(vme_type == 6){
//           // not valid data !
//       }
//       if ((vme_type == 2) && (vme_nlw > 0)){
//         for(int i=0;i<vme_nlw;i++){
//           vme_geo = getbits(*pdata,2,12,5);
//           vme_type = getbits(*pdata,2,9,3);
//           vme_chn = getbits(*pdata,2,1,5);
//           vme_main[vme_geo][vme_chn] = getbits(*pdata,1,1,16);
//           cout<<"222222 vme_main" << vme_main[vme_geo][vme_chn] << " vme_geo " <<vme_geo << " vme_chn " <<vme_chn << endl;
//           pdata++; len++;
//
//         }
//         // read and ignore the expected "end-of-block" longword
//         pdata++; len++;
//       }
//       }

          break; /// proc ID 10
    //}
      ///====================================
  //case 25:
      case 20:

      //TPC crate

      // Next, here somewhat VME scaler V830 was placed recently.
      // not used ?? (I dont know exact purpose of this scaler)
      // it has a fixed lenth of 17 (32bit-word)
      for(int ii=0;ii<17;ii++){
             pdata++; len++;
      }
        for(int ii=0;ii<128;ii++)nhit_v1190_tpcs2[ii]=0;
      // check if end of this procid (with/without barrier)
      if(lenMax == len){ break; }
      ///HEY ANDREW FIX THIS!!!!!
     /// if(*pdata != 0xbabababa){ std::cout<<"E> ProcID 20 : Barrier missed !" << *pdata  << std::endl;}
     pdata++; len++;
      if(lenMax == len){ break; }

      // from here V1190
      while(len < lenMax && (*pdata)!=0xbabababa){
        int type_tpc_v1190 = 0x1F & ((*pdata)>>27);

       /// cout<<"type_tpc_v1190 " <<type_tpc_v1190 << endl;
        if(0x8 == type_tpc_v1190){
          //global header, ignore
        }else if(0x1 == type_tpc_v1190){
          //TDC header, ignore
        }else if(0x3 == type_tpc_v1190){
          //TDC trailer, ignore
        }else if(0x4 == type_tpc_v1190){
          //error status
          printf("TPC crate, V1190, error data are found: 0x%08x \n",*pdata); fflush(stdout);
        }else if(0x10 == type_tpc_v1190){
          //global trailer, ignore
        }else if(0x0 == type_tpc_v1190){

          // this is real data
          int ch_tpc_v1190 = 0x7F & ((*pdata)>>19);
          int check_leading_tpc_v1190 = 0x1 & ((*pdata)>>26); //0 leading, 1 trailing
          //cout<<"ch_tpc_v1190 " <<ch_tpc_v1190 << " check_leading_tpc_v1190 " <<check_leading_tpc_v1190 << endl;
          int data_tpc_v1190 = 0x7FFFF & (*pdata);//19bit
          //cout<<"data_tpc_v1190 " <<data_tpc_v1190 << endl;
          if(0 == check_leading_tpc_v1190){
             tmp_nhit_prev = nhit_v1190_tpcs2[ch_tpc_v1190];
            nhit_v1190_tpcs2[ch_tpc_v1190] ++;
           // cout<<"tmp_nhit_prev " <<tmp_nhit_prev <<" nhit_v1190_tpcs2[ch_tpc_v1190] " << nhit_v1190_tpcs2[ch_tpc_v1190] << "ch_tpc_v1190 " <<ch_tpc_v1190<<  endl;
            if(tmp_nhit_prev<16){ //16 is max prepared. ignore if >=16. nhit will be counted.

             leading_v1190_tpcs2[ch_tpc_v1190][tmp_nhit_prev]=data_tpc_v1190;

             //cout<<"psubevt->GetSubtype() " <<psubevt->GetSubtype() << " psubevt->GetProcid() " <<psubevt->GetProcid() << endl;
            }
//             hVME_TPCS2_V1190All->Fill(ch_tpc_v1190,data_tpc_v1190);
          }
        }else{
          //unknown data type ?
          printf("TPC crate, V1190, strange data are found: 0x%08x \n",*pdata); fflush(stdout);
        }
        pdata++; len++;
      }// end of TDC_V1190

      // check if end of this procid (with/without barrier)
      if(lenMax == len){ break; }
      if(*pdata == 0xbabababa){  pdata++; len++; }
      if(lenMax == len){ break; }

      // from here, 2 ADCs (opotional)
      while (len < lenMax){
        Int_t vme_type = 0x7 & ((*pdata)>>24);
        Int_t vme_geo  = 0x1F & ((*pdata)>>27);
        if(2 == vme_type){
          //header, ignore
        }else if(4==vme_type){
          //end-of-block, ignore
        }else if(0==vme_type){
          //data
           Int_t vme_chn    = 0x3F & ((*pdata)>>16);
           Int_t vme_data  =  0x3FFF & (*pdata);
           vme_tpcs2[vme_geo][vme_chn] = vme_data;

           //           printf("TPC crate, geo %d ch %d data %d\n",vme_geo, vme_chn, vme_data); fflush(stdout);
        }else if(*pdata == 0xbabababa){
          //barrier between 2 ADCs, for example, ignore
        }else{
          // unknown word?
          printf("TPC crate, ADC data, strange data are found: 0x%08x \n",*pdata); fflush(stdout);
        }
        pdata++; len++;
      }

      break;
      ///===============================================================================
      ///================================================================ =============

      case 35: // --- vftx at S2 SOFIA --- (2020/Mar/29)
            uint32_t p32_tmp, marker;
            uint16_t cnt, channel;
            int      word;
    ///  if((psubevt->GetType() == 12) && (psubevt->GetSubtype() == 1)) // in this case, time stamp data.
    ///  {
           for(int module=0; module<VFTX_N; module++)
            for(int channel=0; channel<VFTX_MAX_CHN; channel++) {
             for(int hit=0; hit<VFTX_MAX_HITS; hit++) {
           vftx_cc[module][channel][hit] = 0;
           vftx_ft[module][channel][hit] = 0;
             }
             vftx_mult[module][channel] = 0;
            }
         //  pdata++;
           for(int module=0; module<VFTX_N; module++){


  // first 32-bit word is a marker
  p32_tmp = (uint32_t)*pdata++;
  marker  = (uint32_t)(p32_tmp & 0xff000000);
  cnt     = (uint16_t)((p32_tmp & 0x0003fe00)>>9);

  //printf("1: 0x%x    %d %x\n",p32_tmp, cnt,marker);

  if(marker==0xab000000) {

    // second 32-bit word is the trigger window
    p32_tmp = (uint32_t)*pdata++;
    //printf("2: 0x%x\n",p32_tmp);
    // third 32-bit word is a header we don't care of
 //   p32_tmp = *pdata++;
  //printf("3: 0x%x\n",p32_tmp);
    // DATA BLOCK
    for(word=0; word<cnt-1;word++) {
      p32_tmp = (uint32_t)*pdata++;
     // channel = (uint16_t)((p32_tmp & 0x3e000000)>>25);
      channel = getbits(p32_tmp,2,11,5);
     // printf("3: 0x%x  %d  \n",p32_tmp,channel);
      //printf("error in UNPACK TDC/VFTX_%02d,  %02d: %02d \n",module,channel, vftx_mult[module][channel]);
      
    if(vftx_mult[module][channel]<VFTX_MAX_HITS && module<VFTX_N && channel<VFTX_MAX_CHN){
          ///Coarse clock
        vftx_cc[module][channel][vftx_mult[module][channel]] = (uint16_t)((p32_tmp & 0x00fff800)>>11);
        ///Fine time
        vftx_ft[module][channel][vftx_mult[module][channel]] = (uint16_t)(p32_tmp & 0x07ff);
        h1_vftx_ft[module][channel]->Fill(vftx_ft[module][channel][0]);

//  cout<<"vftx_ft " <<vftx_ft[module][channel][vftx_mult[module][channel]] << " CC " << vftx_cc[module][channel][vftx_mult[module][channel]]<< " channel " << channel<< " vftx_mult[module][channel] " <<vftx_mult[module][channel] << endl;
      }
      vftx_mult[module][channel]++;
    }

     #if CALIBRATION_VFTX
      for(channel=0; channel<VFTX_MAX_CHN; channel++) {
      Vftx_Stat[module][channel]++;
      cout<<"Vftx_Stat[module][channel] " << Vftx_Stat[module][channel]<<" module " << module << " channel " << channel <<"\r"<< flush;
      if(Vftx_Stat[module][channel]==25000) {
          VFTX_Calibration(module,channel);
        }
      }
#endif
  }





//   else {
//     printf("error in UNPACK TDC/VFTX_%02d marker: 0x%x\n",module,p32_tmp);
//   }

//      break;
        }
      ///}
      pdata++; len++;
      if(lenMax == len){ break; }
      {//----- Mesytec MQDC-32 -----
     Int_t vme_geo = 11;
     while(len < lenMax){
       pdata++;len++;
       Int_t vme_type = getbits(*pdata,2,15,2);
       Int_t module_id = getbits(*pdata,2,1,8); // depending on board coder settings
       if(vme_type == 1){ // header
         Int_t vme_nlw = getbits(*pdata,1,1,12); //indicates amount n of following 32-bit words: n-1 events +1 end of event marker)
         pdata++;len++;

         //
          Int_t  vme_type = getbits(*pdata,2,15,2);
          if ((vme_type == 0)  && (vme_nlw > 0)){// data
          for(int i=0;i<vme_nlw;i++) {
          //    cout<<"getbits(*pdata,2,1,5) " <<getbits(*pdata,2,1,5) << " i " << i << endl;
     //    Int_t vme_chn = getbits(*pdata,2,1,5); //number of ADC channel
         // Int_t value = getbits(*pdata,1,1,12);
         // Int_t overfolw = getbits(*pdata,1,16,1); // V = 1 indicates ADC over- or underflow
//             if (value > 0)
//               {
//              //  vme_tof[vme_geo][vme_chn] = value;
//                }
        pdata++; len++ ;
          }
         }
         else if(vme_type==3) printf("This is end of module 0.\n");// event mark

       /// else printf("Unknown data for Mesytec MQDC32\n");
       }
     }
    } //----- end of Mesytec MQDC-32 -----

    {//----- Mesytec MTDC-32 -----
     Int_t vme_geo = 16;
     while(len < lenMax){
       pdata++;len++;
       int module_id = getbits(*pdata,2,1,8); // depending on board coder settings
       int vme_type = getbits(*pdata,2,15,2);
       int hit = 0;

       if(vme_type == 1){
         int vme_nlw = getbits(*pdata,1,1,12); //indicates amount n of following 32-bit words: n-1 events + 1 end of event marker)
         for(int ii=0; ii<vme_nlw; ii++){
           pdata++;
           int value = getbits(*pdata,1,1,16);
           //printf("real data 0x%08x\n",value);

           if(vme_type == 0){//check data type
           int vme_chn = getbits(*pdata,2,1,5);
           int vme_trig = getbits(*pdata,2,6,1) ; //Trigger channel, {T,chan#} = 32 for trig0, or = 33 for trig1

           vme_tof[vme_geo][vme_chn] = value;

           /*  if( (mtdc01_s530[ch][hitmtdc01_s530[ch]]) <= 0 ){ //first-come-first-served, for detailed multi-hit analysis, investigation needed.
         mtdc01_s530[ch][hitmtdc01_s530[ch]] = tdc_data;
         hitmtdc01_s530[ch] = hitmtdc01_s530[ch] + 1;
         printf("mtdc01_s530[%d][%d] = %d; \n",ch,hitmtdc01_s530[ch],tdc_data);
           }
           */
           //printf("TDC data !!! vme_ch = %2d, TDC = %d \n",vme_ch, tdc_data);
           }else if(3 == getbits(*pdata,2,15,2)) printf("This is end of module 0.\n");
           else printf("Unknown data for vmetof\n");
         }
       }
     }
       // check if end of this procid (with/without barrier)
      if(lenMax == len){ break; }
      if(*pdata != 0xbabababa){/* std::cout<<"E> ProcID 35 : 3rd barrier missed !" << *pdata  << std::endl;*/} pdata++; len++;
      if(lenMax == len){ break; }} //----- end of Mesytec MTDC-32 -----

      break;


   ///===============================================================================
      ///================================================================ =============



         case 40: /// Travel music crate (2020/Jan/23)

           { ///-----MDPP module----- (do not remove this bracket)
 // header
         Int_t header = *pdata;
         Int_t nword_mdpp = (0x3FF & header);
         ///AKM I commented these out, are they needed?
//          Int_t adc_res = (*pdata,1,11,3);
//          Int_t tdc_res = (*pdata,1,14,3);
         pdata++; len++ ;

         // main data (data or time information or end counter)
         for(int ii=0; ii<nword_mdpp; ii++){
           int tmp_data = *pdata;
           if( 1 == (0xF & (tmp_data>>28))   ){
             //      printf("real data 0x%08x\n",tmp_data);
             int ch = 0x3F & (tmp_data >> 16);
             if(0<=ch && ch<=15){
               int adc_data = 0xFFFF & tmp_data;
               //    printf("ADC data !!! ch = %2d, ADC = %d \n",ch, adc_data);
               if( (vme_trmu_adc[ch]) <= 0 ){ //first-come-first-served, for detailed multi-hit analysis, investigation needed.
              vme_trmu_adc[ch] = adc_data;
             //// printf(" vme_trmu_adc[%d] = 0x%08x; \n",ch,adc_data);
               }
             }else if(16<=ch && ch<=31){
               int tdc_data = 0xFFFF & tmp_data;
               //printf("TDC data !!! ch = %2d, TDC = %d \n",ch-16, tdc_data);
               if( ( vme_trmu_tdc[ch-16]) <= 0 ){//first-come-first-served, for detailed multi-hit analysis, investigation needed.
              vme_trmu_tdc[ch-16] = tdc_data;
             //////          printf("vme_trmu_tdc[%d] = 0x%08x; \n",ch-16,tdc_data);
               }
             }     else if (trigger == 1){
           int trigger_data = 0xFFFF & tmp_data;
         printf("Trigger time stamp !!! ch = %2d, Tigger time stamp = %d \n",ch, trigger_data);
        // vme_trmu_trigger[ch] = trigger_data;
         //  printf("vme_trmu_adc[%d] = 0x%08x; \n",ch,adc_data);

         }
           }else if( 2 == (0xF & (tmp_data>>28))){
             // printf("ext time stamp 0x%08x\n",tmp_data);
           }else if(0x0 == tmp_data ){
             // printf("dummy 0x%08x\n",tmp_data);
           }else if( 3 == (0x3 & (tmp_data>>30))){
             // printf("end counter 0x%08x\n",tmp_data);
           }else{
             // printf("unknown data0x%08x\n",tmp_data);
           }
           pdata++; len++ ;
         }
           }//---end of MDPP module ---

           break;

         //=========
         default :
           break;

      } // end switch prodID

//      return kTRUE;
       // }
   // }
}
}

//-----------------------------------------------------------------//
//----------------------- SORT STUFF ------------------------------//
//-----------------------------------------------------------------//

void FRS_Detector_System::FRS_Sort(){
    ///CLEAR arrays to avoid multicounting for each proc ID
//         if(psubevt->GetProcid() == 25){
//
//         }


      ///Clear for main crate
      if(psubevt->GetProcid() == 10){
//           for (int n=0; n<32; n++){
//             scaler_frs[n]=0;
//            }
//            for(int o =0; o<64; o++){
//             sc_long[o]=0;
//             }
           if(skip==true){
               tdc_sc41l[0] = 0;
                tdc_sc41r[0] = 0;
                tdc_sc21l[0] = 0;
                tdc_sc21r[0] = 0;
                tdc_sc42l[0] = 0;
                tdc_sc42r[0] = 0;
                tdc_sc43l[0] = 0;
                tdc_sc43r[0] = 0;
                tdc_sc81l[0] = 0;
                tdc_sc81r[0] = 0;
                tdc_sc31l[0] = 0;
                tdc_sc31r[0] = 0;
                tdc_sc11[0]  = 0;
            for(int i=0; i<21; i++){
                for (int j=0; j<32;j++){
//                    //vme_tpc[i][j]=0;
//                   // vme_frs[i][j]=0;
                   vme_main[i][j]=0;
                   vme_tof[i][j]=0;


                }
           }
            
        tpc_x_s4 = -999;
        tpc_y_s4 = -999;
        tpc_angle_x_s4 = -999;
        tpc_angle_y_s4 = -999;
        tpc_sc41_x = -999;
        tpc_sc41_y = -999;
        tpc_sc42_x = -999;
        tpc_sc42_y = -999;

          for(int g=0; g<4; g++){
                    timestamp_main[g]=0;
                    ts_word[g]=0;
            }

           }///end skip
           for(int h=0; h<128; h++){
                nhit_v1190_tpcs2[h]=0;
                 for(int k=0; k<64; k++){
                    leading_v1190_tpcs2[h][k]=0;
                 }
            }

           for(int i=0; i<21; i++){
               for (int j=0; j<32;j++){
                   vme_tpcs2[i][j]=0;
                   vme_tpcs4[i][j]=0;
                   vme_frs[i][j]=0;
                  // vme_main[i][j]=0;
               }
           }
        id_x2=999;
        id_x4 =999;
        id_AoQ=0;
        id_AoQ_corr=0;
        id_dEdeg = 0;
        id_dEdegoQ = 0;

       for(int i=0; i<7; i++){
             for(int j=0; j<2; j++){
           
           tpc_l[i][j]=0;
           tpc_r[i][j]=0;
             }
             
             for(int j=0; j<4; j++){
                tpc_a[i][j]=0;
                tpc_csum[i][j] =0;
                }
                
            }

            for(int i=0; i<8; i++){
            tpc_nhit_timeref[i] = 0;    for(int j=0; j<64; j++){tpc_timeref[i][j] = -1;}


            }
           /* for(int i=0; i<10;i++){
        tdc_sc41l[i]= 0;
        tdc_sc41r[i] = 0;
        tdc_sc21l[i] = 0;
        tdc_sc21r[i] = 0;
        tdc_sc42l[i] = 0;
        tdc_sc42r[i] = 0;
        tdc_sc43l[i]= 0;
        tdc_sc43r[i]= 0;
        tdc_sc81l[i] = 0;
        tdc_sc81r[i] = 0;
            }  */

             for(int i=0;i<8;i++){

        music_e1[i] =0;
        music_e2[i] =0;
         //printf("anode value= %d\n",music_e1[i]);
        //music_e2[i] = vme_frs[12][24+i] & 0xfff;

        music_t1[i] =0;
        music_t2[i] =0;
        
        
                }

        }

        //Clear for case 30
        if(psubevt->GetProcid()==30){
//
           for(int i=0; i<21; i++){
               for (int j=0; j<32;j++){

                   vme_main[i][j]=0;
               }
           }

        dt_21l_21r =0;
        dt_41l_41r =0;
        dt_21l_41l =0;
        dt_21r_41r =0;
        dt_42l_42r =0;
        dt_42l_21l =0;
        dt_42r_21r =0;
        dt_43l_43r =0;
        dt_81l_81r =0;
        dt_21l_81l =0;
        dt_21r_81r =0;
        dt_22l_22r=0;
        dt_22l_41l=0;
        dt_22r_41r=0;
        dt_22l_81l=0;
        dt_22r_81r=0;

        }
   if(psubevt->GetProcid()==25||psubevt->GetProcid()==30||psubevt->GetProcid()==35){
       for(int i=0; i<10; i++){
    tdc_sc41l[i] = 0;
    tdc_sc41r[i] = 0;
    tdc_sc21l[i] = 0;
    tdc_sc21r[i] = 0;
    tdc_sc42l[i] = 0;
    tdc_sc42r[i] = 0;
    tdc_sc43l[i] = 0;
    tdc_sc43r[i] = 0;
    tdc_sc81l[i] = 0;
    tdc_sc81r[i] = 0;
    tdc_sc31l[i] = 0;
    tdc_sc31r[i] = 0;
    tdc_sc11[i]  = 0;

       }
//        for(int i=0; i<32; i++){
//             for(int j=0; j<10; j++){
//       // leading_v1290_main[i][j]=0;
//
//
//        }
// }

    de_21l = 0;
    de_21r = 0;

    de_41l = 0;
    de_41r = 0;
    de_42l = 0;
    de_42r =0;
    de_43l =0;
    de_43r = 0;

    de_81l = 0;
    de_81r = 0;
    de_31l = 0;
    de_31r = 0;
  //  if(psubevt->GetSubtype() ==1){
    TRaw_vftx_21l=0;
    TRaw_vftx_21r=0;
    TRaw_vftx_22l=0;
    TRaw_vftx_22r=0;
    TRaw_vftx_41l=0;
    TRaw_vftx_41r=0;
    TRaw_vftx_42l=0;
    TRaw_vftx_42r=0;
//     TRaw_vftx_sofia_l=0;
//     TRaw_vftx_sofia_r=0;
   // }

        }
         if(psubevt->GetSubtype() !=1){
    TRaw_vftx_21l=0;
    TRaw_vftx_21r=0;
    TRaw_vftx_41l=0;
    TRaw_vftx_41r=0;
//     TRaw_vftx_sofia_l=0;
//     TRaw_vftx_sofia_r=0;
    for(int i=0; i<32; i++){
       TRaw_vftx[i]=0;

    }
    }

      if(psubevt->GetProcid()==20||psubevt->GetProcid()==25){
//        for (int n=0; n<32; n++){
//             scaler_frs[n]=0;
//            }
//            for(int o =0; o<64; o++){
//             sc_long[o]=0;
//             }
      }

//     if(EventFlag == 0x100){
//     for(int i = 0; i < 4; ++i) ts_word[i] = vme_frs[20][i];
//     }
//     else if(EventFlag == 0x200){
//     for(int i = 0; i < 4; ++i) ts_word[i] = vme[3][20][i];
//     }
//     else if(EventFlag == 0x300){
//     for(int i = 0; i < 4; ++i) ts_word[i] = vme[4][20][i];
//     }

  ts_word[0] = timestamp_main[0];
  ts_word[1] = timestamp_main[1];
  ts_word[2] = timestamp_main[2];
  ts_word[3] = timestamp_main[3];

    timestamp = Long64_t(1)*ts_word[0] + Long64_t(0x10000)*ts_word[1] + Long64_t(0x100000000)*ts_word[2] + Long64_t(0x1000000000000)*ts_word[3];
    //cout<<"timestamp " <<timestamp << endl;
    // printf("qtrigger=%d timestamp=%ld \n",qtrigger,timestamp);

    tsys_word[0] = Long64_t(1)*ts_word[0] + Long64_t(0x10000)*ts_word[1] ; //s time low word
    tsys_word[1] = Long64_t(0x100000000)*ts_word[2] + Long64_t(0x1000000000000)*ts_word[3] ; //s time high worid... we do not use it

    if(PreviousTS < 0) tsys_word[2] = 0;

    else tsys_word[2] = (timestamp - PreviousTS)*1.e-5 ; //ms time since the previous s time (ftime routine)

    systemtime_s = tsys_word[2]*1e-3; //tsys_word[0] ;
    systemtime_ms= tsys_word[2];


    if (qtrigger == 12){

    StartOfSpilTime = timestamp;

    StartOfSpilTime2 = timestamp;

    }
    else if (qtrigger == 13){

    StartOfSpilTime = -1;
    }
    // rest are interesting only if trigger == 1

    // calculate time from spill start in sec
    if (StartOfSpilTime >= 0){

    timespill = (timestamp - StartOfSpilTime) * 1e-2;// microsec // 50000000.;
    }

    timespill2 = (timestamp - StartOfSpilTime2) * 1e-2; //microsec  // 50000000.;

  /* Trigger and TPAT*/
  trigger = qtrigger;
  pattern = utpat ;
  sptrigger = uphystrig;
  snbtrig = unbtrig;
  smaxtrig = umaxtrig;


  /* ### scalers:  */
  /* these are treated as 32-bit integers directly  */
//     for(int i = 0 ;i < 32; ++i){
//
//     sc_long[i]  = scaler_frs[i]; //frs crate
//     sc_long[32+i] = scaler_main[i]; //main crate
//
//        }
    if (psubevt->GetProcid() == 30 && psubevt->GetType() == 12)
    {
      for(int i = 0 ;i < 32; ++i){

        sc_long[i]  = scaler_frs[i]; //frs crate
       // cout<<"scaler_frs " << scaler_frs[i] << " i " << i << endl;
        sc_long[32+i] = scaler_main[i]; //main crate
       // cout<<"scaler_main " << scaler_main[i] << " i " << i << endl;
     }
    }

  /* ### TA Ionization Chamber dE:  */


//   /* ### MW anodes:  */
//   for(int i = 0; i < 13; ++i)
//     mw_an[i] = vme_frs[8][i] & 0xfff;
//
//   /* ### MW cathodes:  */
//   // from MW11 -> MW31
//   for(int i = 0; i < 4; ++i)
//     {
//       mw_xr[i] = vme_frs[8][16+i*4] & 0xfff;
//       mw_xl[i] = vme_frs[8][17+i*4] & 0xfff;
//       mw_yu[i] = vme_frs[8][18+i*4] & 0xfff;
//       mw_yd[i] = vme_frs[8][19+i*4] & 0xfff;
//     }
//   // from MW41 -> MW51
//   for(int i = 0 ;i < 3; ++i)
//     {
//       mw_xr[i+4] = vme_frs[9][0+i*4] & 0xfff;
//       mw_xl[i+4] = vme_frs[9][1+i*4] & 0xfff;
//       mw_yu[i+4] = vme_frs[9][2+i*4] & 0xfff;
//       mw_yd[i+4] = vme_frs[9][3+i*4] & 0xfff;
//     }
//   // skip MW61
//   //putting MW61 all to zero (09.07.2018)
//       mw_xr[7] = 0;
//       mw_xl[7] = 0;
//       mw_yu[7] = 0;
//       mw_yd[7] = 0;
//
//   // from MW71 -> MWB2
//   for(int i = 0; i < 5; ++i)
//     {
//       mw_xr[i+8] = vme_frs[9][12+i*4] & 0xfff;
//       mw_xl[i+8] = vme_frs[9][13+i*4] & 0xfff;
//       mw_yu[i+8] = vme_frs[9][14+i*4] & 0xfff;
//       mw_yd[i+8] = vme_frs[9][15+i*4] & 0xfff;
//     }



   //////////////////////////////////////
  // TPC part                         //
  //                                  //
  //////////////////////////////////////
    for(int i=0; i<7; i++){
     tpc_nhit_dt[i][0] = 0;   for(int j=0; j<64; j++){ tpc_dt[i][0][j] = -1; }
     tpc_nhit_dt[i][1] = 0;   for(int j=0; j<64; j++){ tpc_dt[i][1][j] = -1; }
     tpc_nhit_dt[i][2] = 0;   for(int j=0; j<64; j++){ tpc_dt[i][2][j] = -1; }
     tpc_nhit_dt[i][3] = 0;   for(int j=0; j<64; j++){ tpc_dt[i][3][j] = -1; }

     tpc_nhit_lt[i][0] = 0;  for(int j=0; j<64; j++){ tpc_lt[i][0][j] = 0; }
     tpc_nhit_lt[i][1] = 0;  for(int j=0; j<64; j++){ tpc_lt[i][1][j] = 0; }
     tpc_nhit_rt[i][0] = 0;  for(int j=0; j<64; j++){ tpc_rt[i][0][j] = 0; }
     tpc_nhit_rt[i][1] = 0;  for(int j=0; j<64; j++){ tpc_rt[i][1][j] = 0; }
     tpc_nhit_calibgrid[i] = 0; //for(int j=0; j<64; j++){ tpc_calibgrid[i][j] = -1; }
            }
  //ADC

  //TPC 1 at S2 (TPC 21) in vaccuum
   tpc_a[0][0]= vme_tpcs2[12][0] & 0xfff;
   tpc_a[0][1]= vme_tpcs2[12][1] & 0xfff;
   tpc_a[0][2]= vme_tpcs2[12][2] & 0xfff;
   tpc_a[0][3]= vme_tpcs2[12][3] & 0xfff;
   tpc_l[0][0]= vme_tpcs2[12][4] & 0xfff;
   tpc_r[0][0]= vme_tpcs2[12][5] & 0xfff;
   tpc_l[0][1]= vme_tpcs2[12][6] & 0xfff;
   tpc_r[0][1]= vme_tpcs2[12][7] & 0xfff;

  //TPC 2 at S2 (TPC 22) in vaccuum
   tpc_a[1][0]= vme_tpcs2[12][8] & 0xfff;
   tpc_a[1][1]= vme_tpcs2[12][9] & 0xfff;
   tpc_a[1][2]= vme_tpcs2[12][10] & 0xfff;
   tpc_a[1][3]= vme_tpcs2[12][11] & 0xfff;
   tpc_l[1][0]= vme_tpcs2[12][12] & 0xfff;
   tpc_r[1][0]= vme_tpcs2[12][13] & 0xfff;
   tpc_l[1][1]= vme_tpcs2[12][14] & 0xfff;
   tpc_r[1][1]= vme_tpcs2[12][15] & 0xfff;

  //TPC 3 at S2 (TPC 23) in air
   tpc_a[2][0]= vme_tpcs2[12][16] & 0xfff;
   tpc_a[2][1]= vme_tpcs2[12][17] & 0xfff;
   tpc_a[2][2]= vme_tpcs2[12][18] & 0xfff;
   tpc_a[2][3]= vme_tpcs2[12][19] & 0xfff;
   tpc_l[2][0]= vme_tpcs2[12][20] & 0xfff;
   tpc_r[2][0]= vme_tpcs2[12][21] & 0xfff;
   tpc_l[2][1]= vme_tpcs2[12][22] & 0xfff;
   tpc_r[2][1]= vme_tpcs2[12][23] & 0xfff;
  //TPC 4 at S2 (TPC 24) in air
   tpc_a[3][0]= vme_tpcs2[12][24] & 0xfff;
   tpc_a[3][1]= vme_tpcs2[12][25] & 0xfff;
   tpc_a[3][2]= vme_tpcs2[12][26] & 0xfff;
   tpc_a[3][3]= vme_tpcs2[12][27] & 0xfff;
   tpc_l[3][0]= vme_tpcs2[12][28] & 0xfff;
   tpc_r[3][0]= vme_tpcs2[12][29] & 0xfff;
   tpc_l[3][1]= vme_tpcs2[12][30] & 0xfff;
   tpc_r[3][1]= vme_tpcs2[12][31] & 0xfff;

  //TPC 5  at S4 (TPC 41) in air
   tpc_a[4][0]= vme_tpcs2[2][0] & 0xfff;
   tpc_a[4][1]= vme_tpcs2[2][1] & 0xfff;
   tpc_a[4][2]= vme_tpcs2[2][2] & 0xfff;
   tpc_a[4][3]= vme_tpcs2[2][3] & 0xfff;
   tpc_l[4][0]= vme_tpcs2[2][4] & 0xfff;
   tpc_r[4][0]= vme_tpcs2[2][5] & 0xfff;
   tpc_l[4][1]= vme_tpcs2[2][6] & 0xfff;
   tpc_r[4][1]= vme_tpcs2[2][7] & 0xfff;

  //TPC 6 at S4 (TPC 42) in air
   tpc_a[5][0]= vme_tpcs2[2][8] & 0xfff;
   tpc_a[5][1]= vme_tpcs2[2][9] & 0xfff;
   tpc_a[5][2]= vme_tpcs2[2][10] & 0xfff;
   tpc_a[5][3]= vme_tpcs2[2][11] & 0xfff;
   tpc_l[5][0]= vme_tpcs2[2][12] & 0xfff;
   tpc_r[5][0]= vme_tpcs2[2][13] & 0xfff;
   tpc_l[5][1]= vme_tpcs2[2][14] & 0xfff;
   tpc_r[5][1]= vme_tpcs2[2][15] & 0xfff;

  //TPC at S3 (TPC 31) (checkSB)
   tpc_a[6][0]= vme_tpcs2[2][16] & 0xfff;
   tpc_a[6][1]= vme_tpcs2[2][17] & 0xfff;
   tpc_a[6][2]= vme_tpcs2[2][18] & 0xfff;
   tpc_a[6][3]= vme_tpcs2[2][19] & 0xfff;
   tpc_l[6][0]= vme_tpcs2[2][20] & 0xfff;
   tpc_r[6][0]= vme_tpcs2[2][21] & 0xfff;
   tpc_l[6][1]= vme_tpcs2[2][22] & 0xfff;
   tpc_r[6][1]= vme_tpcs2[2][23] & 0xfff;


 //TDC
  for(int itpc=0; itpc<7; itpc++){
    //anode
    for(int j=0; j<4; j++){
      tpc_nhit_dt[itpc][j] = nhit_v1190_tpcs2[ (v1190_channel_dt[itpc][j]) ];
      for(int ihit=0; ihit<(tpc_nhit_dt[itpc][j]); ihit++){
        if(ihit<64){
          tpc_dt[itpc][j][ihit] = leading_v1190_tpcs2[ (v1190_channel_dt[itpc][j]) ][ihit];
//           if(tpc_dt[itpc][j][ihit]>0) cout<<"tpc_dt[itpc][j][ihit] " <<tpc_dt[itpc][j][ihit] << " itpc " << itpc << " j " << j << " ihit " << ihit << endl;
        }
      }
    }

    //delay line
    for(int j=0; j<2; j++){
      //Left side
      tpc_nhit_lt[itpc][j] = nhit_v1190_tpcs2[ (v1190_channel_lt[itpc][j]) ];
      for(int ihit=0; ihit<(tpc_nhit_lt[itpc][j]); ihit++){
        if(ihit<64){
          tpc_lt[itpc][j][ihit] = leading_v1190_tpcs2[ (v1190_channel_lt[itpc][j]) ][ihit];

        }
        else tpc_lt[itpc][j][ihit]=0;
      }
      
      //Right side
      tpc_nhit_rt[itpc][j] = nhit_v1190_tpcs2[ (v1190_channel_rt[itpc][j]) ];
      for(int ihit=0; ihit<(tpc_nhit_rt[itpc][j]); ihit++){
        if(ihit<64){
          tpc_rt[itpc][j][ihit] = leading_v1190_tpcs2[ (v1190_channel_rt[itpc][j]) ][ihit];

        }
        else tpc_rt[itpc][j][ihit]=0;
      }
    }

    //calib grid
    tpc_nhit_calibgrid[itpc] = nhit_v1190_tpcs2[ (v1190_channel_calibgrid[itpc]) ];
    for(int ihit=0; ihit<(tpc_nhit_calibgrid[itpc]); ihit++){
      if(ihit<64){
        tpc_calibgrid[itpc][ihit] = leading_v1190_tpcs2[ (v1190_channel_calibgrid[itpc]) ][ihit];
      }
    }
  }//  end of for(itpc)

  // TPC time ref TDCs
  for(int i=0; i<8; i++){
      tpc_nhit_timeref[i] = nhit_v1190_tpcs2[ (v1190_channel_timeref[i]) ];
      for(int ihit=0; ihit<(tpc_nhit_timeref[i]); ihit++){
        if(ihit<64){
          tpc_timeref[i][ihit] = leading_v1190_tpcs2[ (v1190_channel_timeref[i]) ][ihit];
        }
      }
  }

   de_21l = 0;
    de_21r = 0;

    de_41l = 0;
    de_41r = 0;
    de_42l = 0;
    de_42r =0;
    de_43l =0;
    de_43r = 0;

    de_81l = 0;
    de_81r = 0;
    de_31l = 0;
    de_31r = 0;

    /// SCI dE:
    /* ### SCI dE:  */
//     for(int i=0; i<32; i++){int test2 = vme_main[4][i] & 0xfff;
//         cout<<" vme_main[4][i] "  << vme_main[4][i] <<" test2 " << test2 <<" i " << i <<"  psubevt->GetProcid() " << psubevt->GetProcid()<< endl;
//     }
  de_41l = vme_main[4][13] & 0xfff; //vme_main[11][0] & 0xfff;
  de_41r = vme_main[4][1] & 0xfff;
  de_21l = vme_main[4][2] & 0xfff;

//  if(de_21l>2063&&de_21l<2066)
  de_21r = vme_main[4][3] & 0xfff;
  de_42l = vme_main[4][4] & 0xfff;
  de_42r = vme_main[4][5] & 0xfff;

  de_31l = vme_main[4][9] & 0xfff;
  de_31r = vme_main[4][7] & 0xfff;
  de_43l = vme_main[4][11] & 0xfff;
  de_43r = vme_main[4][12] & 0xfff;
  //  de_81l = vme_main[11][13] & 0xfff; // changed on 21/Feb/2020 23:00
  de_81l = vme_main[4][15] & 0xfff; // changed on 21/Feb/2020 23:00
  de_81r = vme_main[4][14] & 0xfff;
  de_81l = vme_main[4][0] & 0xfff; // sweapped with SC22L. This channel has problem!!! 21 Feb 2021
  de_81r = vme_main[4][14] & 0xfff;

//  de_22l = vme_main[4][0] & 0xfff; // changed on 17/Feb/2021
  de_22l = vme_main[4][15] & 0xfff; // changed on 17 Feb 2021, ch0 QDC seems to have a problem
  de_22r = vme_main[4][8] & 0xfff;



//     de_v1l = 0;
//     de_v1r = 0;
//     de_v2l = 0;
//     de_v2r = 0;
//     de_v3  = 0;


   /* ### SCI times:  */
  dt_21l_21r = vme_frs[12][0] & 0xfff;
  dt_41l_41r = vme_frs[12][1] & 0xfff;
  dt_42l_42r = vme_frs[12][2] & 0xfff;
  dt_43l_43r = vme_frs[12][3] & 0xfff;
  dt_81l_81r = vme_frs[12][4] & 0xfff;
  dt_21l_41l = vme_frs[12][5] & 0xfff;
  dt_21r_41r = vme_frs[12][6] & 0xfff;
  dt_42r_21r = vme_frs[12][7] & 0xfff;//swapped recently 28/02/2020
  dt_42l_21l = vme_frs[12][8] & 0xfff;//swapped recently 28/02/2020
  dt_21l_81l = vme_frs[12][9] & 0xfff;
  dt_21r_81r = vme_frs[12][10] & 0xfff;
  dt_22l_22r = vme_frs[12][11] & 0xfff;
  dt_22l_41l = vme_frs[12][12] & 0xfff;
  dt_22r_41r = vme_frs[12][13] & 0xfff;
  dt_22l_81l = vme_frs[12][14] & 0xfff;
  dt_22r_81r = vme_frs[12][15] & 0xfff;
//cout<<"dt_41l_41r " << dt_41l_41r <<endl;

   // Time raw in ps from VFTX module
      if(psubevt->GetSubtype() ==1){

     float r=0.;
   for(int i=0; i<32; i++){
       if((vftx_cc[SCI_MOD][i][0]!=0) && (vftx_ft[SCI_MOD][i][0]!=0)){
           r = (double)rand.Rndm() - 0.5 ;
   TRaw_vftx[i] = VFTX_GetTraw_ps(SCI_MOD,i,vftx_cc[SCI_MOD][i][0],vftx_ft[SCI_MOD][i][0],r);
       }
   }
   TRaw_vftx_21l = TRaw_vftx[SCI21L_CH];
   TRaw_vftx_21r = TRaw_vftx[SCI21R_CH];
   TRaw_vftx_22l = TRaw_vftx[SCI22L_CH];
   TRaw_vftx_22r = TRaw_vftx[SCI22R_CH];
   TRaw_vftx_41l = TRaw_vftx[SCI41L_CH];
   TRaw_vftx_41r = TRaw_vftx[SCI41R_CH];
   TRaw_vftx_42l = TRaw_vftx[SCI42L_CH];
   TRaw_vftx_42r = TRaw_vftx[SCI42R_CH];
//    TRaw_vftx_sofia_l = TRaw_vftx[SCISOFIAL_CH];
//    TRaw_vftx_sofia_r = TRaw_vftx[SCISOFIAR_CH];
      }

   ///AKM 12.07.20 since we only take the first hit (for now...)
  /* ### SCI Multihit TDC time:  */
//     for(int i = 0; i < 10; ++i){
// //     cout<<"leading_v1290_main[0][i] " << leading_v1290_main[0][i] << " tdc_sc41l[i] " << tdc_sc41l[i] << " i " << i << " psubevt->GetProcid() " <<psubevt->GetProcid() << endl;
//     tdc_sc41l[i] = leading_v1290_main[0][i];
//     tdc_sc41r[i] = leading_v1290_main[1][i];
//
//     tdc_sc21l[i] = leading_v1290_main[2][i];
//     tdc_sc21r[i] = leading_v1290_main[3][i];
//    cout<<" tdc_sc21l[i] " << tdc_sc21l[i] << "  tdc_sc21r[i] " << tdc_sc21r[i]<< " i " << i << " leading_v1290_main[3][i] " <<leading_v1290_main[3][i]<< endl;
//     tdc_sc42l[i] = leading_v1290_main[4][i];
//     tdc_sc42r[i] = leading_v1290_main[5][i];
//     tdc_sc43l[i] = leading_v1290_main[6][i];
//     tdc_sc43r[i] = leading_v1290_main[7][i];
//     tdc_sc81l[i] = leading_v1290_main[8][i];
//     tdc_sc81r[i] = leading_v1290_main[9][i];
//     tdc_sc31l[i] = leading_v1290_main[10][i];
//     tdc_sc31r[i] = leading_v1290_main[11][i];
//     tdc_sc11[i]  = leading_v1290_main[12][i];
//
//     }
  for(int i=0;i<10;i++){
    tdc_sc41l[i] = leading_v1290_main[0][i];
    tdc_sc41r[i] = leading_v1290_main[1][i];
    tdc_sc21l[i] = leading_v1290_main[2][i];
   // cout<<"leading_v1290_main[2][i] " <<leading_v1290_main[2][i] << endl;
    tdc_sc21r[i] = leading_v1290_main[3][i];
    tdc_sc42l[i] = leading_v1290_main[10][i]; //changed mapping 03.03.21
    tdc_sc42r[i] = leading_v1290_main[15][i]; //changed mapping 03.03.21
    tdc_sc43l[i] = leading_v1290_main[6][i];
    tdc_sc43r[i] = leading_v1290_main[7][i];
    tdc_sc81l[i] = leading_v1290_main[8][i];
    tdc_sc81r[i] = leading_v1290_main[9][i];
    //tdc_sc31l[i] = leading_v1290_main[10][i]; //changed mapping 03.03.21
    tdc_sc31r[i] = leading_v1290_main[11][i];
    tdc_sc11[i]  = leading_v1290_main[12][i];
    tdc_sc22l[i] = leading_v1290_main[13][i];
    tdc_sc22r[i]  = leading_v1290_main[14][i];
  }


 //---MUSIC configuration. 2x TUM-MUSIC from FRS crate and 1 TRavel-MUsic from TRMU crate (2020/Jan/23, YT)
       for(int i=0;i<8;i++)
        {
          music_e1[i] = (vme_frs[3][i]) & 0xfff;   //
          music_e2[i] = (vme_frs[3][8+i]) & 0xfff; // Travel-MUSIC (from special VME crate)
          music_e3[i] = (vme_trmu_adc[i]); //

          music_t1[i] = leading_v1290_main[16+i][0] & 0xfff; //TUM-MUSIC
          music_t2[i] = leading_v1290_main[24+i][0] & 0xfff; //TUM-MUSIC
          music_t3[i] = (vme_trmu_tdc[i]);                   //Travel-MUSIC (from special VME crate)
        }

      /* ### MUSIC temp & pressure:  */
      // music_pres[0] = 0;
      // music_temp[0] = 0;
      // music_pres[1] = 0;
      // music_temp[1] = 0;
      // music_pres[2] = 0;
      // music_temp[2] = 0;

      // //Channeltron detectors (vme must be adjusted)
      // ct_time = vme3s_MT[2][0] & 0xfff;
      // ct_signal = vme2scaler[20] & 0xfff;
      // ct_trigger_DU = vme2scaler[5]& 0xfff;
      // ct_trigger_SY = vme2scaler[6]& 0xfff;

      // //Electron current measurement (vme must be adjused)
      // ec_signal = vme0[10][1]& 0xfff;

      // // mrtof
      // mrtof_start = vme3s_MT[0][0] ;//& 0x7ffff;
      // mrtof_stopDelay = vme3s_MT[1][0];// & 0x7ffff;
      // mrtof_stop = vme3s_MT[2][0] ;//& 0x7ffff;

    //Electron current measurement (vme must be adjused)
    //ec_signal = vme_frs[10][1]& 0xfff;

    // mrtof
   // mrtof_start = leading_v1290_main[0][0] ;//& 0x7ffff;
   // mrtof_stopDelay = leading_v1290_main[1][0];// & 0x7ffff;
   // mrtof_stop = leading_v1290_main[2][0] ;//& 0x7ffff;

     v1190_channel_dt[0][0] = 0; //TPC21-A11
  v1190_channel_dt[0][1] = 1; //TPC21-A12
  v1190_channel_dt[0][2] = 2; //TPC21-A21
  v1190_channel_dt[0][3] = 3; //TPC21-A22
  v1190_channel_lt[0][0] = 4; //TPC21-DL1
  v1190_channel_rt[0][0] = 5; //TPC21-DR1
  // 6, 7 empty
  v1190_channel_lt[0][1] = 8; //TPC21-DL2
  v1190_channel_rt[0][1] = 9; //TPC21-DR2
  v1190_channel_dt[1][0] = 10; //TPC22-A11
  v1190_channel_dt[1][1] = 11; //TPC22-A12
  v1190_channel_dt[1][2] = 12; //TPC22-A21
  v1190_channel_dt[1][3] = 13; //TPC22-A22
  // 14, 15 empty
  //17(top channel of 3rd module is dead)
  //18(skip)
  v1190_channel_lt[1][0] = 18; //TPC22-DL1
  v1190_channel_rt[1][0] = 19; //TPC22-DR1
  v1190_channel_lt[1][1] = 20; //TPC22-DL2
  v1190_channel_rt[1][1] = 21; //TPC22-DR2
  // 22,23 empty

  // ======= middle NIM crate (TPC23+24)=========
  v1190_channel_dt[2][0] = 24; //TPC23-A11
  v1190_channel_dt[2][1] = 25; //TPC23-A12
  v1190_channel_dt[2][2] = 26; //TPC23-A21
  v1190_channel_dt[2][3] = 27; //TPC23-A22
  v1190_channel_lt[2][0] = 28; //TPC23-DL1
  v1190_channel_rt[2][0] = 29; //TPC23-DR1
  //30,31 empty
  v1190_channel_lt[2][1] = 32; //TPC23-DL2
  v1190_channel_rt[2][1] = 33; //TPC23-DR2
  v1190_channel_dt[3][0] = 34; //TPC24-A11
  v1190_channel_dt[3][1] = 35; //TPC24-A12
  v1190_channel_dt[3][2] = 36; //TPC24-A21
  v1190_channel_dt[3][3] = 37; //TPC24-A22
  //38,39 empty
  v1190_channel_lt[3][0] = 40; //TPC24-DL1
  v1190_channel_rt[3][0] = 41; //TPC24-DR1
  v1190_channel_lt[3][1] = 42; //TPC24-DL2
  v1190_channel_rt[3][1] = 43; //TPC24-DR2
  //46,47 empty


  // ======= bottom NIM crate (TPC41+42+31)=========
  v1190_channel_dt[4][0] = 64; //TPC41-A11
  v1190_channel_dt[4][1] = 65; //TPC41-A12
  v1190_channel_dt[4][2] = 66; //TPC41-A21
  v1190_channel_dt[4][3] = 67; //TPC41-A22
  v1190_channel_lt[4][0] = 68; //TPC41-DL1
  v1190_channel_rt[4][0] = 69; //TPC41-DR1
  //70,71 empty
  v1190_channel_lt[4][1] = 72; //TPC41-DL2
  v1190_channel_rt[4][1] = 73; //TPC41-DR2
  v1190_channel_dt[5][0] = 74; //TPC42-A11
  v1190_channel_dt[5][1] = 75; //TPC42-A12
  v1190_channel_dt[5][2] = 76; //TPC42-A21
  v1190_channel_dt[5][3] = 77; //TPC42-A22
  //78,79 empty
  v1190_channel_lt[5][0] = 80; //TPC42-DL1
  v1190_channel_rt[5][0] = 81; //TPC42-DR1
  v1190_channel_lt[5][1] = 82; //TPC42-DL2
  v1190_channel_rt[5][1] = 83; //TPC42-DR2
  v1190_channel_dt[6][0] = 84; //TPC31-A11
  v1190_channel_dt[6][1] = 85; //TPC31-A12
  //86,87 empty
  v1190_channel_dt[6][2] = 88; //TPC31-A21
  v1190_channel_dt[6][3] = 89; //TPC31-A22
  v1190_channel_lt[6][0] = 90; //TPC31-DL1
  v1190_channel_rt[6][0] = 91; //TPC31-DR1
  v1190_channel_lt[6][1] = 92; //TPC31-DL2
  v1190_channel_rt[6][1] = 93; //TPC31-DR2
  //94,95 empty

  //time reference signal
  v1190_channel_timeref[0] = 96; //accept trig
  v1190_channel_timeref[1] = 97; //sc21
  v1190_channel_timeref[2] = 98; //sc22
  v1190_channel_timeref[3] = 99; //sc31
  v1190_channel_timeref[4] =100; //sc41
  v1190_channel_timeref[5] =101; //
  v1190_channel_timeref[6] =102; //
  v1190_channel_timeref[7] =103; //

  //
  v1190_channel_calibgrid[0] = 104;//tpc21grid
  v1190_channel_calibgrid[1] = 105;//tpc22grid
  v1190_channel_calibgrid[2] = 106;//tpc23grid
  v1190_channel_calibgrid[3] = 107;//tpc24grid
  v1190_channel_calibgrid[4] = 108;//tpc41grid
  v1190_channel_calibgrid[5] = 109;//tpc42grid
  v1190_channel_calibgrid[6] = 110;//tpc31grid //to be checked maybe 111

}


void FRS_Detector_System::FRS_Calib(){
    ///Scalars
//     for(int jj=0; jj<64; jj++){
//     scaler_initial[jj] = sc_long[jj];
//
//     }
 // cout<<"psubevt->GetProcid() " <<psubevt->GetProcid() << "  psubevt->GetType()  " << psubevt->GetType()  << endl;
       if (psubevt->GetProcid() == 30 && psubevt->GetType() == 12)
   {
//      cout<<"TEST " << endl;
      if(13 == trigger || 12 == trigger|| 10 == trigger || 11 ==trigger) return; // skip spill trigger

      if(1==scaler_check_first_event){
        for(int ii=0; ii<64; ii++){
           scaler_initial[ii] = sc_long[ii];
           scaler_previous[ii] = sc_long[ii];
//             std::cout<<"scaler_initial[ii] " << scaler_initial[ii] <<" ii " << ii << std::endl;
//         std::cout<<"scaler_previous[ii] " << scaler_previous[ii] <<" ii " << ii << std::endl;
        }
        scaler_check_first_event = 0;
      }
      //  cout<<"sc_long[scaler_ch_1kHz] " << sc_long[scaler_ch_1kHz] << endl;
       time_in_ms  = sc_long[scaler_ch_1kHz]  - scaler_initial[scaler_ch_1kHz];

       if (time_in_ms < 0 ) {
    scaler_initial[scaler_ch_1kHz] = sc_long[scaler_ch_1kHz] ;
	 time_in_ms = 0 ;
  }

       spill_count = sc_long[scaler_ch_spillstart] - scaler_initial[scaler_ch_spillstart];

       ibin_for_s      = ((time_in_ms / 1000) % 1000) + 1;
       ibin_for_100ms  = ((time_in_ms / 100) % 4000) + 1;
       ibin_for_spill  = (spill_count % 1000) +1;

       for(int kk=0; kk<64; kk++){
       increase_scaler_temp[kk] =  sc_long[kk]  - scaler_previous[kk];
//     if(kk==8 || kk==9)cout<<"increase_scaler_temp[kk] " <<increase_scaler_temp[kk] <<" sc_long[kk] " <<sc_long[kk]<< " scaler_previous[kk] " << scaler_previous[kk] <<  " kk " << kk << endl;
       }
      extraction_time_ms += sc_long[scaler_ch_1kHz] - scaler_previous[scaler_ch_1kHz];
      if(0 != sc_long[scaler_ch_spillstart] - scaler_previous[scaler_ch_spillstart]){
        extraction_time_ms = 0;
      }


       ibin_clean_for_s      = (((time_in_ms / 1000) +20) % 1000) + 1; //
       ibin_clean_for_100ms  = (((time_in_ms / 100) +200 ) % 4000) + 1; //
       ibin_clean_for_spill  = ((spill_count + 990 )% 20) +1; //

      // put current data into _previous for the next event
      for(int ii=0; ii<64; ii++){
        scaler_previous[ii] = sc_long[ii];
      }
   }
 
//////////////////////////////////////////////////////////////////
///  ***********TPC Analysis*************************** //////////

 //================================
  // Nomenclature for TPCs
  //================================
  // TPCs at S2
  // TPC 1 = TPC 21 (in vaccum) [i=0]
  // TPC 2 = TPC 22 (in vaccum) [i=1]
  // TPC 3 = TPC 23 (in air)    [i=2]
  // TPC 4 = TPC 24 (in air)    [i=3]

  // TPCs at S4
  // TPC 5 = TPC 41 (in air)    [i=4]
  // TPC 6 = TPC 42 (in air)    [i=5]

  //TPC at S3
  // TPC 7 = TPC 31             [i=6]
   for(int u=0;u<8;u++){
  b_tpc_timeref[u]=false;
  tpc_timeref_s[u]=0;
   }
   for(int k=0;k<7;k++){
       tpc_dx12[k]=0;
       tpc_x[k] = 0;
       tpc_y[k] = 0;
       b_tpc_xy[k] = false;
       tpc_de[k] = 0;
       b_tpc_de[k]=false;

        for(int g=0;g<4;g++) {
            b_tpc_csum[k][g] =false;
          tpc_csum[k][g]=0;
        }
       for(int l=0;l<2;l++){

       tpc_lt_s[k][l] = 0;
       tpc_rt_s[k][l] = 0;
       tpc_xraw[k][l] = 0;
    }
    for(int l=0;l<4;l++){

       tpc_dt_s[k][l]=0;
      // tpc_xraw[k][l]=0;
       tpc_yraw[k][l]=0;

    }
   }

for(int i=0; i<8; i++){
      for( int ihit=0; ihit<(tpc_nhit_timeref[i]) && ihit<64; ihit++ ){
      // hTPC_SC_TIMEREF[i] ->Fill(src.tpc_timeref[i][ihit]);

          if(tpc_timeref[i][ihit]>tpc->lim_timeref[i][0] &&tpc_timeref[i][ihit]< tpc->lim_timeref[i][1])b_tpc_timeref[i]=true;
         // b_tpc_timeref[i] = Check_WinCond_Multi(tpc_timeref[i][ihit],cTPC_SC_TIMEREF,i );
          if(b_tpc_timeref[i]){
       // if( cTPC_SC_TIMEREF[i]->Test(src.tpc_timeref[i][ihit])){

          if( tpc_timeref_s[i] <=0 || (tpc_timeref_s[i]>0 && tpc_timeref[i][ihit]<tpc_timeref_s[i]) ){
              tpc_timeref_s[i] = tpc_timeref[i][ihit];
              //b_tpc_timeref[i] = kTRUE;
          }
        }
      }
  }

   bool checkrange1=0;
   bool checkrange2=0;
   bool checkrange3=0;
   bool checkrange4=0;
   bool checkrange5=0;
  for(int i=0;i<7;i++)
    {

  for(int ihit=0; ihit<(tpc_nhit_lt[i][0] && ihit<64); ihit++){

         Int_t thisdata = tpc_lt[i][0][ihit];
         Int_t currently_selected = tpc_lt_s[i][0];
        // cout<<"3 tpc_lt_s " <<tpc_lt_s[i][0]<< " thisdata " <<thisdata<< "i " << i << endl;
          if(thisdata>tpc->lim_lt[i][0][0] && thisdata<tpc->lim_lt[i][0][1]) checkrange1=true;
              /*
              cTPC_LT0[i][0] = tpc->lim_lt[i][0][0];
    cTPC_LT0[i][1] = tpc->lim_lt[i][0][1];*/
          //bool  checkrange = Check_WinCond_Multi(thisdata,cTPC_LT0,i);
          //cout<<"checkrange " <<checkrange << endl;
         ///hTPC_LT0[i]->Fill(thisdata);
          if(checkrange1 && (currently_selected<=0 || (currently_selected>0 && thisdata<currently_selected))){
           tpc_lt_s[i][0] = thisdata;
         // cout<<"4 " << tpc_lt[i][0][ihit] <<endl;
          }
        }

        for(int ihit=0; ihit<(tpc_nhit_rt[i][0] && ihit<64); ihit++){
          Int_t thisdata = tpc_rt[i][0][ihit];
          Int_t currently_selected = tpc_rt_s[i][0];

          if(thisdata>tpc->lim_rt[i][0][0] && thisdata<tpc->lim_rt[i][0][1]) checkrange2=true;
         // bool  checkrange = Check_WinCond_Multi(thisdata,cTPC_RT0,i);
         /// hTPC_RT0[i]->Fill(thisdata);
          if(checkrange2 && (currently_selected<=0 || (currently_selected>0 && thisdata<currently_selected))){
            tpc_rt_s[i][0] = thisdata;

          }
        }
        for(int ihit=0; ihit<(tpc_nhit_lt[i][1] && ihit<64); ihit++){
          Int_t thisdata = tpc_lt[i][1][ihit];
         // cout<<"tpc_lt[i][1][ihit] " <<tpc_lt[i][1][ihit] << endl;
          Int_t currently_selected = tpc_lt_s[i][1];
           if(thisdata>tpc->lim_lt[i][1][0] && thisdata<tpc->lim_lt[i][1][1]) checkrange3=true;
         // bool  checkrange = Check_WinCond_Multi(thisdata,cTPC_LT1,i);
        /// hTPC_LT1[i]->Fill(thisdata);
          if(checkrange3 && (currently_selected<=0 || (currently_selected>0 && thisdata<currently_selected))){
            tpc_lt_s[i][1] = thisdata;
           // cout<<"Check range tpc_lt_s[i][1] " <<tpc_lt_s[i][1] << endl;
          }
        }
        for(int ihit=0; ihit<(tpc_nhit_rt[i][1] && ihit<64); ihit++){
          Int_t thisdata = tpc_rt[i][1][ihit];
          Int_t currently_selected = tpc_rt_s[i][1];

            if(thisdata>tpc->lim_rt[i][1][0] && thisdata<tpc->lim_rt[i][1][1]) checkrange4=true;
        //  bool  checkrange = Check_WinCond_Multi(thisdata,cTPC_RT1,i);

          ///hTPC_RT1[i]->Fill(thisdata);
          if(checkrange4 && (currently_selected<=0 || (currently_selected>0 && thisdata<currently_selected))){
            tpc_rt_s[i][1] = thisdata;

          }
        }

       for(int j=0; j<4; j++){
          for(int ihit=0; ihit<(tpc_nhit_dt[i][j] && ihit<64); ihit++){
            Int_t thisdata = tpc_dt[i][j][ihit];
            Int_t currently_selected = tpc_dt_s[i][j];
            //bool  checkrange = cTPC_DT[i][j]->Test(thisdata);
              if(thisdata>tpc->lim_dt[i][j][0] && thisdata<tpc->lim_dt[i][j][1]) checkrange5=true;
            // bool  checkrange = Check_WinCond_Multi_Multi(thisdata,cTPC_DT,i,j);
            ///hTPC_DT[i][j]->Fill(thisdata);
            if(checkrange5 && (currently_selected<=0 || (currently_selected>0 && thisdata<currently_selected))){
              tpc_dt_s[i][j] = thisdata;
            }
          }
        }


      for(int j=0;j<4;j++)
    {

      /// calculate control sums
     if(j < 2 && tpc_lt_s[i][0]>0 && tpc_rt_s[i][0]>0 && tpc_dt_s[i][j]>0){
        tpc_csum[i][j] = (tpc_lt_s[i][0] + tpc_rt_s[i][0]- 2*tpc_dt_s[i][j]);

     }
      else if(tpc_lt_s[i][1]>0 && tpc_rt_s[i][1] >0 &&  tpc_dt_s[i][j] >0){
        tpc_csum[i][j] = (tpc_lt_s[i][1] + tpc_rt_s[i][1]- 2*tpc_dt_s[i][j]);

      }
      else{
               tpc_csum[i][j] = -9999999;
            }

     if(tpc_csum[i][0]> tpc->lim_csum1[i][0] && tpc_csum[i][0]<tpc->lim_csum1[i][1]) {b_tpc_csum[i][0]=true;

     }
     if(tpc_csum[i][1]> tpc->lim_csum2[i][0] && tpc_csum[i][1]<tpc->lim_csum2[i][1]){b_tpc_csum[i][1]=true;

     }
     if(tpc_csum[i][2]> tpc->lim_csum3[i][0] && tpc_csum[i][2]<tpc->lim_csum3[i][1]){ b_tpc_csum[i][2]=true;

     }
      if(tpc_csum[i][3]> tpc->lim_csum4[i][0] && tpc_csum[i][3]<tpc->lim_csum4[i][1]){ b_tpc_csum[i][3]=true;


      }
      //b_tpc_csum[i][j] = Check_WinCond_Multi_Multi(tpc_csum[i][j], lim_csum, j, i);
     // b_tpc_csum[i][j] = lim_csum[i][j]->Test(tpc_csum[i][j]);
//cout<<"b_tpc_csum[i][2] " <<b_tpc_csum[i][2]<<" b_tpc_csum[i][3] " <<b_tpc_csum[i][3] <<" i " << i <<" tpc_csum[i][j] " << tpc_csum[i][j] << " j " << j << endl;
    }
      ///xraw
        int countx = 0;
        float sumx = 0.0;
        float tmp_tpc_x0 = -99999.;
        float tmp_tpc_x1 = -99999.;
//        cout<<"!!!b_tpc_csum[i][0] " <<b_tpc_csum[i][0] << " b_tpc_csum[i][1] " <<b_tpc_csum[i][1] <<" b_tpc_csum[i][2] " <<b_tpc_csum[i][2] <<" b_tpc_csum[i][3] " <<b_tpc_csum[i][3] << endl;
        if ((b_tpc_csum[i][0] || b_tpc_csum[i][1])){
          tpc_xraw[i][0] = tpc_lt_s[i][0]-tpc_rt_s[i][0];
          tmp_tpc_x0 =  (tpc_xraw[i][0])*(tpc->x_factor[i][0]) + (tpc->x_offset[i][0]);
          sumx +=  tmp_tpc_x0;
          countx++;

         // cout<<"tpc_xraw[i][0] " <<tpc_xraw[i][0] <<" tpc_lt_s[i][0] " <<tpc_lt_s[i][0] << " tpc_rt_s[i][0] " << tpc_rt_s[i][0]  <<  " countx " << countx<< endl;

        }
        if ((b_tpc_csum[i][2] || b_tpc_csum[i][3])){
          tpc_xraw[i][1] = tpc_lt_s[i][1]-tpc_rt_s[i][1];
          tmp_tpc_x1 =  (tpc_xraw[i][1])*(tpc->x_factor[i][1]) + (tpc->x_offset[i][1]);
          sumx += tmp_tpc_x1;
            countx++;

//           cout<<"bsum2and 3 tpc_xraw[i][1] " <<tpc_xraw[i][1] <<" tpc_lt_s[i][1] " <<tpc_lt_s[i][1] << " tpc_rt_s[i][1] " << tpc_rt_s[i][1]  <<  " countx " << countx<<" sumx " <<sumx << " tmp_tpc_x1 " <<tmp_tpc_x1 <<  " i "<< i << endl;

           //  cout<<"tpc_xraw[i][1] " <<tpc_xraw[i][0] << endl;
        }
        if(countx>0 ){
            tpc_x[i] = sumx/((float)countx);
//             cout<<"TPC X defined here tpc_x[i]" <<tpc_x[i] << " sumx " << sumx << "(float)countx " <<(float)countx <<" i " << i <<  endl;
        }
        if(2==countx){
          tpc_dx12[i] =  tmp_tpc_x1 -tmp_tpc_x0;


        }

        ///yraw
        int county = 0;
        float sumy = 0.0;
        float tmp_tpc_y[4] = {-99999., -99999., -99999., -99999.};
        int index_timeref = tpc->id_tpc_timeref[i];

        for(int j=0;j<4;j++){
          if (b_tpc_csum[i][j] &&  b_tpc_timeref[index_timeref]){
            tpc_yraw[i][j] = tpc_dt_s[i][j] - tpc_timeref_s[index_timeref];
            tmp_tpc_y[j] =  (tpc_yraw[i][j])*(tpc->y_factor[i][j]) + (tpc->y_offset[i][j]);
            sumy +=   tmp_tpc_y[j];
            county ++;
          }
        }
        if(county>0){
            tpc_y[i] = sumy/((double)county);

        }

        if(countx>0 && county>0){
          b_tpc_xy[i] = kTRUE;


        }else{
          b_tpc_xy[i] = kFALSE;
        }

         //TPC anode amplitude quick analysis
        double temp_de = 1.0;
        int temp_count = 0;
        for(int j=0;j<4;j++){
          if( tpc_a[i][j] - tpc->a_offset[i][j] >5.0){
            temp_de *= (tpc_a[i][j] - tpc->a_offset[i][j]);  temp_count++;
          }
        }
        //ADC sqrt-mean is calculated only for 4hit events
        if(4==temp_count){
            tpc_de[i] = sqrt(sqrt( temp_de ));
            b_tpc_de[i] = kTRUE;
//            hTPC_dE[i]->Fill(tpc_de[i]);
        }
    }

  //*********************************************

  //================================
  // Distances of TPCs at S2 and S4
  //================================

  Float_t dist_TPC21_TPC22 = frs->dist_TPC22 - frs->dist_TPC21;
  Float_t dist_TPC23_TPC24 = frs->dist_TPC24 - frs->dist_TPC23;
  Float_t dist_TPC22_TPC24 = frs->dist_TPC24 - frs->dist_TPC22;
  Float_t dist_TPC21_focS2 = frs->dist_TPC21 - frs->dist_focS2;
  Float_t dist_TPC22_focS2 = frs->dist_TPC22 - frs->dist_focS2;
  Float_t dist_TPC23_focS2 = frs->dist_TPC23 - frs->dist_focS2;
  Float_t dist_TPC41_TPC42 = frs->dist_TPC42 - frs->dist_TPC41;
  Float_t dist_TPC42_focS4 = frs->dist_focS4 - frs->dist_TPC42;

  //=================================
  // Tracking with TPC 21 and TPC 22
  //=================================

  if (b_tpc_xy[0]&&b_tpc_xy[1])
    {
       tpc_angle_x_s2_foc_21_22 = (tpc_x[1] - tpc_x[0])/dist_TPC21_TPC22*1000.;
      tpc_angle_y_s2_foc_21_22 = (tpc_y[1] - tpc_y[0])/dist_TPC21_TPC22*1000.;
      tpc_x_s2_foc_21_22 = -tpc_angle_x_s2_foc_21_22 * dist_TPC21_focS2/1000. + tpc_x[0]; //check
      tpc_y_s2_foc_21_22 = -tpc_angle_y_s2_foc_21_22 * dist_TPC21_focS2/1000. + tpc_y[0]; //check

      Float_t dist_SC21_focS2 = frs->dist_SC21 - frs->dist_focS2;
      tpc21_22_sc21_x = (tpc_angle_x_s2_foc_21_22/1000.*dist_SC21_focS2)+tpc_x_s2_foc_21_22;
      tpc21_22_sc21_y = (tpc_angle_y_s2_foc_21_22/1000.*dist_SC21_focS2)+tpc_y_s2_foc_21_22;
      Float_t dist_SC22_focS2 = frs->dist_SC22 - frs->dist_focS2;
      tpc21_22_sc22_x = (tpc_angle_x_s2_foc_21_22/1000.*dist_SC22_focS2)+tpc_x_s2_foc_21_22;
      tpc21_22_sc22_y = (tpc_angle_y_s2_foc_21_22/1000.*dist_SC22_focS2)+tpc_y_s2_foc_21_22;
      Float_t dist_S2target_focS2 = frs->dist_S2target - frs->dist_focS2;
      tpc21_22_s2target_x = (tpc_angle_x_s2_foc_21_22/1000.*dist_S2target_focS2)+tpc_x_s2_foc_21_22;
      tpc21_22_s2target_y = (tpc_angle_y_s2_foc_21_22/1000.*dist_S2target_focS2)+tpc_y_s2_foc_21_22;

    }
 // else  tpc_x_s2_foc_21_22= -999 ;


  //=================================
  // Tracking with TPC 23 and TPC 24
  //=================================

  if (b_tpc_xy[2]&&b_tpc_xy[3])
    {
        ///Angle X at S2 focus
       tpc_angle_x_s2_foc_23_24 = (tpc_x[3] - tpc_x[2])/dist_TPC23_TPC24*1000.;
    ///Angle Y at S2 focus
       tpc_angle_y_s2_foc_23_24 = (tpc_y[3] - tpc_y[2])/dist_TPC23_TPC24*1000.;
       
       ///X position at S2 focus
       tpc_x_s2_foc_23_24 = -tpc_angle_x_s2_foc_23_24 * dist_TPC23_focS2/1000. + tpc_x[2]; //check
        
        ///Y position at S2 focus
       tpc_y_s2_foc_23_24 = -tpc_angle_y_s2_foc_23_24 * dist_TPC23_focS2/1000. + tpc_y[2]; //check
       
       /// TPC 23 24 X at SC21 focus 
       Float_t dist_SC21_focS2 = frs->dist_SC21 - frs->dist_focS2;
       tpc23_24_sc21_x = (tpc_angle_x_s2_foc_23_24/1000.*dist_SC21_focS2)+tpc_x_s2_foc_23_24;
       tpc23_24_sc21_y = (tpc_angle_y_s2_foc_23_24/1000.*dist_SC21_focS2)+tpc_y_s2_foc_23_24;
       
       /// TPC 23 24 X at SC22 focus ??
       Float_t dist_SC22_focS2 = frs->dist_SC22 - frs->dist_focS2;
       tpc23_24_sc22_x = (tpc_angle_x_s2_foc_23_24/1000.*dist_SC22_focS2)+tpc_x_s2_foc_23_24;
       
       tpc23_24_sc22_y = (tpc_angle_y_s2_foc_23_24/1000.*dist_SC22_focS2)+tpc_y_s2_foc_23_24;
       
        /// TPC 23 24 X at target focus ??
       Float_t dist_S2target_focS2 = frs->dist_S2target - frs->dist_focS2;
       tpc23_24_s2target_x = (tpc_angle_x_s2_foc_23_24/1000.*dist_S2target_focS2)+tpc_x_s2_foc_23_24;
       
       tpc23_24_s2target_y = (tpc_angle_y_s2_foc_23_24/1000.*dist_S2target_focS2)+tpc_y_s2_foc_23_24;

    }
  else  {
      tpc_x_s2_foc_23_24= -999 ;
      tpc_x_s2_foc_23_24= -999 ;
      tpc_y_s2_foc_23_24 =-999;
      tpc_angle_x_s2_foc_23_24 =-999;
      tpc_angle_y_s2_foc_23_24 =-999;
      tpc23_24_sc21_x =-999;
      tpc23_24_sc21_y =-999;
      tpc23_24_sc22_x =-999;
      tpc23_24_sc22_y =-999;   
  }

  //=================================
  // Tracking with TPC 22 and TPC 24
  //=================================

  if (b_tpc_xy[1]&&b_tpc_xy[3])
    {
      tpc_angle_x_s2_foc_22_24 = (tpc_x[3] - tpc_x[1])/dist_TPC22_TPC24*1000.;
      tpc_angle_y_s2_foc_22_24 = (tpc_y[3] - tpc_y[1])/dist_TPC22_TPC24*1000.;
      tpc_x_s2_foc_22_24 = -tpc_angle_x_s2_foc_22_24 * dist_TPC22_focS2/1000. + tpc_x[1]; //check
      tpc_y_s2_foc_22_24 = -tpc_angle_y_s2_foc_22_24 * dist_TPC22_focS2/1000. + tpc_y[1]; //check

      Float_t dist_SC21_focS2 = frs->dist_SC21 - frs->dist_focS2;
      tpc22_24_sc21_x = (tpc_angle_x_s2_foc_22_24/1000.*dist_SC21_focS2)+tpc_x_s2_foc_22_24;
      tpc22_24_sc21_y = (tpc_angle_y_s2_foc_22_24/1000.*dist_SC21_focS2)+tpc_y_s2_foc_22_24;
      Float_t dist_SC22_focS2 = frs->dist_SC22 - frs->dist_focS2;
      tpc22_24_sc22_x = (tpc_angle_x_s2_foc_22_24/1000.*dist_SC22_focS2)+tpc_x_s2_foc_22_24;
      tpc22_24_sc22_y = (tpc_angle_y_s2_foc_22_24/1000.*dist_SC22_focS2)+tpc_y_s2_foc_22_24;
      Float_t dist_S2target_focS2 = frs->dist_S2target - frs->dist_focS2;
      tpc22_24_s2target_x = (tpc_angle_x_s2_foc_22_24/1000.*dist_S2target_focS2)+tpc_x_s2_foc_22_24;
      tpc22_24_s2target_y = (tpc_angle_y_s2_foc_22_24/1000.*dist_S2target_focS2)+tpc_y_s2_foc_22_24;

    }
  else {
      tpc_x_s2_foc_22_24= -999 ;
      tpc_y_s2_foc_22_24 =-999;
      tpc_angle_x_s2_foc_22_24 =-999;
      tpc_angle_y_s2_foc_22_24 =-999;
      tpc22_24_sc21_x =-999;
      tpc22_24_sc21_y =-999;
      tpc22_24_sc22_x =-999;
      tpc22_24_sc22_y =-999;
      
  }

  //=====================================================
  // Tracking with TPC 41 and TPC 42 (TPC 5 and 6) at S4
  //=====================================================
  if (b_tpc_xy[4]&&b_tpc_xy[5])
    {

      tpc_angle_x_s4 = (tpc_x[5] - tpc_x[4])/dist_TPC41_TPC42*1000.;
    
      tpc_angle_y_s4 = (tpc_y[5] - tpc_y[4])/dist_TPC41_TPC42*1000.;
      tpc_x_s4 = tpc_angle_x_s4 * dist_TPC42_focS4/1000. + tpc_x[5];
      tpc_y_s4 = tpc_angle_y_s4 * dist_TPC42_focS4/1000. + tpc_y[5];

        Float_t dist_SC41_focS4 = frs->dist_SC41 - frs->dist_focS4;
       tpc_sc41_x = (tpc_angle_x_s4/1000.*dist_SC41_focS4)+tpc_x_s4;
       tpc_sc41_y = (tpc_angle_y_s4/1000.*dist_SC41_focS4)+tpc_y_s4;

       Float_t dist_SC42_focS4 = frs->dist_SC42 - frs->dist_focS4;
       tpc_sc42_x = (tpc_angle_x_s4/1000.*dist_SC42_focS4)+tpc_x_s4;
       tpc_sc42_y = (tpc_angle_y_s4/1000.*dist_SC42_focS4)+tpc_y_s4;

       Float_t dist_SC43_focS4 = frs->dist_SC43 - frs->dist_focS4;
       tpc_sc43_x = (tpc_angle_x_s4/1000.*dist_SC43_focS4)+tpc_x_s4;
       tpc_sc43_y = (tpc_angle_y_s4/1000.*dist_SC43_focS4)+tpc_y_s4;

       Float_t dist_MUSIC41_focS4 = frs->dist_MUSIC41 - frs->dist_focS4;
       tpc_music41_x = (tpc_angle_x_s4/1000.*dist_MUSIC41_focS4)+tpc_x_s4;
       tpc_music41_y = (tpc_angle_y_s4/1000.*dist_MUSIC41_focS4)+tpc_y_s4;

       Float_t dist_MUSIC42_focS4 = frs->dist_MUSIC42 - frs->dist_focS4;
       tpc_music42_x = (tpc_angle_x_s4/1000.*dist_MUSIC42_focS4)+tpc_x_s4;
       tpc_music42_y = (tpc_angle_y_s4/1000.*dist_MUSIC42_focS4)+tpc_y_s4;

       Float_t dist_MUSIC43_focS4 = frs->dist_MUSIC43 - frs->dist_focS4;
       tpc_music43_x = (tpc_angle_x_s4/1000.*dist_MUSIC43_focS4)+tpc_x_s4;
       tpc_music43_y = (tpc_angle_y_s4/1000.*dist_MUSIC43_focS4)+tpc_y_s4;

       Float_t dist_S4target_focS4 = frs->dist_S4target - frs->dist_focS4;
       tpc_s4target_x = (tpc_angle_x_s4/1000.* dist_S4target_focS4)+tpc_x_s4;
       tpc_s4target_y = (tpc_angle_y_s4/1000.* dist_S4target_focS4)+tpc_y_s4;

//       music1_x1 = tpc_angle_x_s4 * (frs->dist_MUSIC3+frs->dist_MUSICa1)/1000. + tpc_x[5];
//       music1_x2 = tpc_angle_x_s4 * (frs->dist_MUSIC3+frs->dist_MUSICa2)/1000. + tpc_x[5];
//       music1_x3 = tpc_angle_x_s4 * (frs->dist_MUSIC3+frs->dist_MUSICa3)/1000. + tpc_x[5];
//       music1_x4 = tpc_angle_x_s4 * (frs->dist_MUSIC3+frs->dist_MUSICa4)/1000. + tpc_x[5];
//
//       music1_y1 = tpc_angle_y_s4 * (frs->dist_MUSIC3+frs->dist_MUSICa1)/1000. + tpc_y[5];
//       music1_y2 = tpc_angle_y_s4 * (frs->dist_MUSIC3+frs->dist_MUSICa2)/1000. + tpc_y[5];
//       music1_y3 = tpc_angle_y_s4 * (frs->dist_MUSIC3+frs->dist_MUSICa3)/1000. + tpc_y[5];
//       music1_y4 = tpc_angle_y_s4 * (frs->dist_MUSIC3+frs->dist_MUSICa4)/1000. + tpc_y[5];


      //S4 entrance of OTPC tracked with TPCs 5 and 6 for s388
      //tpc_x_s4_target2 = tpc_angle_x_s4 * dist_TPC6_target2/1000. + tpc_x[5];
      //tpc_y_s4_target2 = tpc_angle_y_s4 * dist_TPC6_target2/1000. + tpc_y[5];

    }
    
     else  {
      tpc_angle_x_s4= -999 ;
      tpc_angle_y_s4= -999 ;
      tpc_x_s4 =-999;
      tpc_y_s4 =-999;
      tpc_sc42_x =-999;
      tpc_sc42_y =-999;
//       tpc23_24_sc21_y =-999;
//       tpc23_24_sc22_x =-999;
//       tpc23_24_sc22_y =-999;   
  }


  // tracking to musics and scis (S323,410 exp.)
  //Float_t dist_TPC3_SC21  = 1375.5;
  //Float_t dist_TPC6_SC41  = 510.; //8.09.11 //check AEv

  // X position at SC21 position:
  // SC21 is before TPC3 and TPC4
  //tpc_mw_sc21_x = tpc_x[2] - dist_TPC3_SC21 * tpc_angle_x_s2_foc/1000.;


  // Y position at SC21
  //tpc_sc21_y = tpc_y[2] - dist_TPC3_SC21 * tpc_angle_y_s2_foc/1000.;


  // X position at SC41
  // SC41 is after TPC6
 // tpc_sc41_x  = tpc_x[5] + dist_TPC6_SC41 * tpc_angle_x_s4 / 1000.;

  // Y position at SC41
  //tpc_sc41_y = tpc_y[5] + dist_TPC6_SC41 * tpc_angle_y_s4 /1000.;


//////////////////////////////////////////////////////////////////

}



void FRS_Detector_System::FRS_Anl(){

    ///==================================================================================///
                    /// Start of MUSIC  analysis
///==================================================================================///
  music1_anodes_cnt = 0;
  music2_anodes_cnt = 0;
  music3_anodes_cnt = 0;
  
  for(int i=0; i<2;i++){
      de[i]=0;
      de_cor[i]=0;
  }


   // Munich MUSIC

  for (int i=0;i<8;i++)
    {
      /* 8 anodes of TUM MUSIC */
      /****** first MUSIC ***** threshold changed to 5, 9/8/2012 **/
      if ( music_e1[i] > 5)
    {

      music_b_e1[i] = Check_WinCond_Multi(music_e1[i], cMusic1_E, i);//cMusic1_E[i]->Test(music_e1[i]);


      if (music_b_e1[i])
        music1_anodes_cnt++;
    }

        if (music_t1[i] > 0)
    {
      music_b_t1[i] = Check_WinCond_Multi(music_t1[i], cMusic1_T, i); // cMusic1_T[i]->Test(music_t1[i]);
    }


      //hMUSIC1_dE1dE2->Fill(music_e1[0],music_e1[1]);

      //       /****** second MUSIC *****/

      if ( music_e2[i] > 5)
    {
      music_b_e2[i] = Check_WinCond_Multi(music_e2[i], cMusic2_E, i);// cMusic2_E[i]->Test(music_e2[i]);
      if (music_b_e2[i]) music2_anodes_cnt++;
    }

      if (music_t2[i] > 0)
    {
      music_b_t2[i] = Check_WinCond_Multi(music_t2[i], cMusic2_T, i);// cMusic2_T[i]->Test(music_t2[i]);
    }
    }

  for (int i=0;i<4;i++)
    {
      /* 4 anodes of MUSIC OLD */
      /****** third MUSIC Travelling*****/
      if ( music_e3[i] > 0)
    {

      music_b_e3[i] = Check_WinCond_Multi(music_e3[i], cMusic3_E, i);// cMusic3_E[i]->Test(music_e3[i]);
      if (music_b_e3[i])
        music3_anodes_cnt++;
    }
      if (music_t3[i] > 0)
    {
      music_b_t3[i] = Check_WinCond_Multi(music_t3[i], cMusic3_T, i);// cMusic3_T[i]->Test(music_t3[i]);
    }
    }

  // calculate truncated dE from 8 anodes, Munich MUSIC

  if (music1_anodes_cnt == 8)
    {
      /* "quick-n-dirty solution according to Klaus:   */
      //      Float_t r1 = (music_e1[0] - music->e1_off[0])*(music_e1[1] - music->e1_off[1]);
      //      Float_t r2 = (music_e1[2] - music->e1_off[2])*(music_e1[3] - music->e1_off[3]);
      //      Float_t r3 = (music_e1[4] - music->e1_off[4])*(music_e1[5] - music->e1_off[5]);
      //      Float_t r4 = (music_e1[6] - music->e1_off[6])*(music_e1[7] - music->e1_off[7]);

      Float_t r1 = ((music_e1[0])*music->e1_gain[0] + music->e1_off[0])*((music_e1[1])*music->e1_gain[1] + music->e1_off[1]);
      Float_t r2 = ((music_e1[2])*music->e1_gain[2] + music->e1_off[2])*((music_e1[3])*music->e1_gain[3] + music->e1_off[3]);
      Float_t r3 = ((music_e1[4])*music->e1_gain[4] + music->e1_off[4])*((music_e1[5])*music->e1_gain[5] + music->e1_off[5]);
      Float_t r4 = ((music_e1[6])*music->e1_gain[6] + music->e1_off[6])*((music_e1[7])*music->e1_gain[7] + music->e1_off[7]);

      if ( (r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0) )
    {
      b_de1 = kTRUE;
      de[0] = sqrt( sqrt( sqrt(r1) * sqrt(r2) ) * sqrt( sqrt(r3) * sqrt(r4) ) );
      de_cor[0] = de[0];
    }
    }


  if (music2_anodes_cnt == 8)
    {

      Float_t r1 = ((music_e2[0])*music->e2_gain[0] + music->e2_off[0])*((music_e2[1])*music->e2_gain[1] + music->e2_off[1]);
      Float_t r2 = ((music_e2[2])*music->e2_gain[2] + music->e2_off[2])*((music_e2[3])*music->e2_gain[3] + music->e2_off[3]);
      Float_t r3 = ((music_e2[4])*music->e2_gain[4] + music->e2_off[4])*((music_e2[5])*music->e2_gain[5] + music->e2_off[5]);
      Float_t r4 = ((music_e2[6])*music->e2_gain[6] + music->e2_off[6])*((music_e2[7])*music->e2_gain[7] + music->e2_off[7]);


      if ( (r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0) )
    {
      b_de2 = kTRUE;
      de[1] = sqrt( sqrt( sqrt(r1) * sqrt(r2) ) * sqrt( sqrt(r3) * sqrt(r4) ) );
      de_cor[1] = de[1];
    }
    }


  if (music3_anodes_cnt == 8)
    {         // OLD MUSIC

      Float_t r1 = ((music_e3[0])*music->e3_gain[0] + music->e3_off[0])*((music_e3[1])*music->e3_gain[1] + music->e3_off[1]);
      Float_t r2 = ((music_e3[2])*music->e3_gain[2] + music->e3_off[2])*((music_e3[3])*music->e3_gain[3] + music->e3_off[3]);
      //Float_t r3 = ((music_e3[4])*music->e3_gain[4] + music->e3_off[4])*((music_e3[5])*music->e3_gain[5] + music->e3_off[5]);  //added on 22.05.2018 SB
      //Float_t r4 = ((music_e3[6])*music->e3_gain[6] + music->e3_off[6])*((music_e3[7])*music->e3_gain[7] + music->e3_off[7]);  //added on 22.05.2018 SB

      if ( (r1 > 0) && (r2 > 0) )
    {
    //  b_de3 = kTRUE;
      de[2] = sqrt( sqrt(r1) * sqrt(r2) ) ;  // corrrected JSW 19.03.2010
      //de[2] = sqrt( sqrt( sqrt(r1) * sqrt(r2) ) * sqrt( sqrt(r3) * sqrt(r4) ) );   //changed on 22.05.2018 SB
      de_cor[2] = de[2];
    }

//       if (music_b_t3[0] && music_b_t3[1] && music_b_t3[2] && music_b_t3[3])
//  b_dt3 = kTRUE;



    //hMUSIC1_MUSIC2->Fill(de[0],de[1]);

      /* Position (X) correction by TPC */

     if(b_tpc_xy[4]&&b_tpc_xy[5]){

    music1_x_mean = tpc_music41_x;
    music2_x_mean = tpc_music42_x;
    music3_x_mean = tpc_music43_x;

    Float_t power, Corr;
    // correction for MUSIC41
    if(b_de1){
      power = 1., Corr = 0.;
      for(int i=0;i<4;i++) {
    Corr += music->pos_a1[i] * power;
    power *= music1_x_mean;
      }
      if (Corr!=0) {
    Corr = music->pos_a1[0] / Corr;
    de_cor[0] = de[0] * Corr;
      }

    }

    // correction for MUSIC42
    if(b_de2){
      power = 1., Corr = 0.;
      for(int i=0;i<4;i++) {
    Corr += music->pos_a2[i] * power;
    power *= music2_x_mean;
      }
      if (Corr!=0) {
    Corr = music->pos_a2[0] / Corr;
    de_cor[1] = de[1] * Corr;
      }
        }
    // correction for MUSIC43
    if(b_de3){
      power = 1., Corr = 0.;
      for(int i=0;i<4;i++) {
    Corr += music->pos_a3[i] * power;
    power *= music3_x_mean;
      }
      if (Corr!=0) {
    Corr = music->pos_a3[0] / Corr;
    de_cor[2] = de[2] * Corr;
      }

            }
        }
    }
///==================================================================================///
                    /// Start of Scintillator  analysis
///==================================================================================///

for(int i=0; i<10;i++){
    mhtdc_sc21lr_dt[i]=0;
    mhtdc_sc22lr_dt[i]=0;
}
   mhtdc_sc31lr_dt=0;
   mhtdc_sc41lr_dt=0;
   mhtdc_sc42lr_dt=0;



   ///SCI 21
    for(int i=0; i<10; i++){
        if(0!=tdc_sc21l[i] && 0!=tdc_sc21r[i]){
            mhtdc_sc21lr_dt[i] = sci->mhtdc_factor_ch_to_ns*( rand3() + tdc_sc21l[i]  -  tdc_sc21r[i] );
            mhtdc_sc21lr_x[i]  = mhtdc_sc21lr_dt[i] * sci->mhtdc_factor_21l_21r + sci->mhtdc_offset_21l_21r;
        }
    float sc21pos_from_tpc    = -999.9;
    if(b_tpc_xy[0]&&b_tpc_xy[1]){
      sc21pos_from_tpc =  tpc21_22_sc21_x ;
    }else if(b_tpc_xy[2]&&b_tpc_xy[3]){
      sc21pos_from_tpc =  tpc23_24_sc21_x ;
    }
    
    ///SCI22
    if(0!=tdc_sc22l[i] && 0!=tdc_sc22r[i]){
        mhtdc_sc22lr_dt[i] = sci->mhtdc_factor_ch_to_ns*( rand3() + tdc_sc22l[i]  -  tdc_sc22r[i] );
        mhtdc_sc22lr_x[i]  = mhtdc_sc22lr_dt[i] * sci->mhtdc_factor_22l_22r + sci->mhtdc_offset_22l_22r;
    
    float sc22pos_from_tpc    = -999.9;
    if(b_tpc_xy[0]&&b_tpc_xy[1]){
      sc22pos_from_tpc =  tpc21_22_sc22_x ;
    }else if(b_tpc_xy[2]&&b_tpc_xy[3]){
      sc22pos_from_tpc =  tpc23_24_sc22_x ;
            }
        }
  }
  

  if(0!=tdc_sc41l[0] && 0!=tdc_sc41r[0]){
    mhtdc_sc41lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + tdc_sc41l[0]  -  tdc_sc41r[0] );
    mhtdc_sc41lr_x  = mhtdc_sc41lr_dt * sci->mhtdc_factor_41l_41r + sci->mhtdc_offset_41l_41r;
   }

  if(0!=tdc_sc42l[0] && 0!=tdc_sc42r[0]){
    mhtdc_sc42lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + tdc_sc42l[0]  -  tdc_sc42r[0] );
    mhtdc_sc42lr_x  = mhtdc_sc42lr_dt * sci->mhtdc_factor_42l_42r + sci->mhtdc_offset_42l_42r;
   }

  if(0!=tdc_sc43l[0] && 0!=tdc_sc43r[0]){
    mhtdc_sc43lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + tdc_sc43l[0]  -  tdc_sc43r[0] );
    mhtdc_sc43lr_x  = mhtdc_sc43lr_dt * sci->mhtdc_factor_43l_43r + sci->mhtdc_offset_43l_43r;
     }

  if(0!=tdc_sc31l[0] && 0!=tdc_sc31r[0]){
    mhtdc_sc31lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + tdc_sc31l[0]  -  tdc_sc31r[0] );
    mhtdc_sc31lr_x  = mhtdc_sc31lr_dt * sci->mhtdc_factor_31l_31r + sci->mhtdc_offset_31l_31r;

  }

  if(0!=tdc_sc81l[0] && 0!=tdc_sc81r[0]){
    mhtdc_sc81lr_dt = sci->mhtdc_factor_ch_to_ns*( rand3() + tdc_sc81l[0]  -  tdc_sc81r[0] );
    mhtdc_sc81lr_x  = mhtdc_sc81lr_dt * sci->mhtdc_factor_81l_81r + sci->mhtdc_offset_81l_81r;
      }


///21 -> 41
for (int i=0; i<10; i++){
  if(0!=tdc_sc21l[i] && 0!=tdc_sc21r[i] && 0!=tdc_sc41l[0] && 0!=tdc_sc41r[0] ){
    mhtdc_tof4121[i] = sci->mhtdc_factor_ch_to_ns*( 0.5*(tdc_sc41l[0]+tdc_sc41r[0])  - 0.5*(tdc_sc21l[i]+tdc_sc21r[i]) ) + sci->mhtdc_offset_41_21;
    

   ///22 -> 41
  if(0!=tdc_sc22l[i] && 0!=tdc_sc22r[i] && 0!=tdc_sc41l[0] && 0!=tdc_sc41r[0]){
    mhtdc_tof4122[i] = sci->mhtdc_factor_ch_to_ns*( 0.5*(tdc_sc41l[0]+tdc_sc41r[0])  - 0.5*(tdc_sc22l[i]+tdc_sc22r[i]) ) + sci->mhtdc_offset_41_22;
//    if(bDrawHist) hMultiHitTDC_TOF_41_22->Fill(mhtdc_tof4122);
    }
  }
}
  ///21 -> 42
  if(0!=tdc_sc21l[0] && 0!=tdc_sc21r[0] && 0!=tdc_sc42l[0] && 0!=tdc_sc42r[0]){
    mhtdc_tof4221 = sci->mhtdc_factor_ch_to_ns*( 0.5*(tdc_sc42l[0]+tdc_sc42r[0])  - 0.5*(tdc_sc21l[0]+tdc_sc21r[0]) ) + sci->mhtdc_offset_42_21;


  }
  ///21 -> 43
  if(0!=tdc_sc21l[0] && 0!=tdc_sc21r[0] && 0!=tdc_sc43l[0] && 0!=tdc_sc43r[0]){
    mhtdc_tof4321 = sci->mhtdc_factor_ch_to_ns*( 0.5*(tdc_sc43l[0]+tdc_sc43r[0])  - 0.5*(tdc_sc21l[0]+tdc_sc21r[0]) ) + sci->mhtdc_offset_43_21;
   // if(bDrawHist) hMultiHitTDC_TOF_43_21->Fill(mhtdc_tof4321);
  }
  ///21 -> 32
  if(0!=tdc_sc21l[0] && 0!=tdc_sc21r[0] && 0!=tdc_sc31l[0] && 0!=tdc_sc31r[0]){
    mhtdc_tof3121 = sci->mhtdc_factor_ch_to_ns*( 0.5*(tdc_sc31l[0]+tdc_sc31r[0])  - 0.5*(tdc_sc21l[0]+tdc_sc21r[0]) ) + sci->mhtdc_offset_31_21;
    //if(bDrawHist) hMultiHitTDC_TOF_31_21->Fill(mhtdc_tof3121);
  }
  ///21 -> 81
  if(0!=tdc_sc21l[0] && 0!=tdc_sc21r[0] && 0!=tdc_sc81l[0] && 0!=tdc_sc81r[0]){
    mhtdc_tof8121 = sci->mhtdc_factor_ch_to_ns*( 0.5*(tdc_sc81l[0]+tdc_sc81r[0])  - 0.5*(tdc_sc21l[0]+tdc_sc21r[0]) ) + sci->mhtdc_offset_81_21;
  //  if(bDrawHist) hMultiHitTDC_TOF_81_21->Fill(mhtdc_tof8121);
  }
 




        /*-------------------------------------------------------------------------*/
    /* focus index: detector number                  tof index  tof path       */
    /*       0:     Sc01                                0:     TA - S1         */
    /*       1:     Sc11                                1:     S1 - S2         */
    /*       2:     Sc21                                2:     S2 - S41        */
    /*       3:     Sc22                                3:     S2 - S42        */
    /*       4:     Sc31                                4:     S2 - 81         */
    /*       5:     Sc41                                5:     S2 - E1         */
    /*                                                                         */
    /*       6:     Sc42                              tof index not used up to */
    /*       7:     Sc43 (previously Sc51)             now, only separate      */
    /*       8:     Sc61                              variables for S2-S41 and */
    /*       9:     ScE1 (ESR)                                S2-S42           */
    /*      10:     Sc81                                                       */
    /*      11:     Sc82                                                       */
    /*-------------------------------------------------------------------------*/
    for(int i=0; i<12; i++){
    sci_l[i]=0;
    sci_r[i]=0;
    sci_tx[i]=0;
    sci_x[i]=0;
    }

  /*  Raw data  */
   sci_l[2] = de_21l;  /* 21L         */
   sci_r[2] = de_21r;  /* 21R         */
   sci_tx[2] = dt_21l_21r + rand3();


   sci_l[5] = de_41l;  /* 41L         */
   sci_r[5] = de_41r;  /* 41R         */
   sci_tx[5] = dt_41l_41r + rand3();

   sci_l[6] = de_42l;  /* 42L         */

   sci_r[6] = de_42r;  /* 42R         */
   sci_tx[6] = dt_42l_42r + rand3();

   sci_l[7] = de_43l;  /* 43L         */
   sci_r[7] = de_43r;  /* 43R         */
   sci_tx[7] = dt_43l_43r + rand3();

   sci_l[10] = de_81l; /* 81L         */
   sci_r[10] = de_81r; /* 81R         */
   sci_tx[10] = dt_81l_81r + rand3();

   sci_l[3] = de_22l;  /* 21L         */
   sci_r[3] = de_22r;  /* 21R         */
   sci_tx[3] = dt_22l_22r + rand3();

   for (int cnt=0;cnt<6;cnt++) //
     {
       int idx = 0 ;
       float posref =-999;
       //int mw_idx = 0;
       //Float_t mwx = 0;
       switch(cnt)
     {
     case 0:        /* SC21 */
       idx = 2;
        // posref from tpc
       if(b_tpc_xy[0]&&b_tpc_xy[1]){
         posref =  tpc21_22_sc21_x ;
       }else if(b_tpc_xy[2]&&b_tpc_xy[3]){
         posref =  tpc23_24_sc21_x ;
       }
       //mw_idx = 2;
       //mwx = mw_sc21_x;
       break;
     case 1:        /* SC21 delayed */
       idx = 3;
       if(b_tpc_xy[6]){ posref = tpc_x[6]; }
       //mw_idx = 2;
       //mwx = mw_sc21_x;
       break;
     case 2:        /* SC41 */
       idx = 5;
       if(b_tpc_xy[4]&&b_tpc_xy[5]){
         posref =  tpc_sc41_x ;
       }
       //mw_idx = 5;
       //mwx = tpc_sc41_x;
       break;
     case 3:        /* SC42 */
           idx = 6;
       if(b_tpc_xy[4]&&b_tpc_xy[5]){
         posref =  tpc_sc42_x ;
       }
       break;
     case 4:
       idx = 7;     /* SC43 */
       if(b_tpc_xy[4]&&b_tpc_xy[5]){
         posref =  tpc_sc43_x ;
       }
       break;
     case 5:
       idx = 10;    /* SC81 */
       // no position reference from tpc
       break;
     default: idx = 2;
     }


       sci_b_l[idx] = Check_WinCond(sci_l[idx], cSCI_L);// cSCI_L[idx]->Test(sci_l[idx]);
       sci_b_r[idx] = Check_WinCond(sci_r[idx], cSCI_R);// cSCI_R[idx]->Test(sci_r[idx]);

       if(sci_b_l[idx] && sci_b_r[idx])
     {
    ///   sci_e[idx] = sqrt( (sci_l[idx] - sci->le_a[0][idx]) * sci->le_a[1][idx]               * (sci_r[idx] - sci->re_a[0][idx]) * sci->re_a[1][idx]);
       sci_e[idx] = (sci_r[idx] - sci->re_a[0][idx]);
       sci_b_e[idx] = Check_WinCond(sci_e[idx], cSCI_E);// cSCI_E[idx]->Test(sci_e[idx]);
     }

       /*   Position in X direction:   */
       sci_b_tx[idx] = Check_WinCond(sci_tx[idx], cSCI_Tx);// cSCI_Tx[idx]->Test(sci_tx[idx]);
       if (sci_b_tx[idx])
     {

       /* mm-calibrated     */
       Float_t R = sci_tx[idx] ;//+ rand3();

       Float_t power = 1., sum = 0.;
       for(int i=0;i<7;i++)
         {
           sum += sci->x_a[i][idx] * power;
           power *= R;
         }

       sci_x[idx] = sum;

       sci_b_x[idx] = Check_WinCond(sci_x[idx], cSCI_X);// cSCI_X[idx]->Test(sci_x[idx]);
     }


     } // end of loop for indices 2,3,5,6,7,10


   /***  Scintillator Tof  spectra ***/

   /* S21 - S41 */

   /*  Calibrated tof  */
   sci_tofll2 = dt_21l_41l*sci->tac_factor[2] - sci->tac_off[2] ;   /* S41L- S21L */

   sci_tofrr2 = dt_21r_41r*sci->tac_factor[3] - sci->tac_off[3] ;   /* S41R- S21R */

   sci_b_tofll2 = Check_WinCond(sci_tofll2, cSCI_LL2);// cSCI_TofLL2->Test(sci_tofll2);
   sci_b_tofrr2 = Check_WinCond(sci_tofrr2, cSCI_RR2);// cSCI_TofRR2->Test(sci_tofrr2);

    /* sum of Tof_LL and Tof_RR corrects for position in stop/start scint.      */

    if(sci_b_tofll2 && sci_b_tofrr2){
        /* TOF SC41 - SC21 [ps]  */
     sci_tof2        =   (sci->tof_bll2 * sci_tofll2 + sci->tof_a2 + sci->tof_brr2 * sci_tofrr2)/2.0 ;  // tof_a2  is essentially unnecessary (even confusing) = 0
     sci_tof2_calib   =  -1.0*sci_tof2 + id->id_tofoff2;
      }
    else {sci_tof2=0;sci_tof2_calib=0;}
    /*   S21 - S42 Calibrated tof  */
   sci_tofll3 = dt_42l_21l*sci->tac_factor[5] - sci->tac_off[5] ;   /* S42L- S21L */  // tac_off is essentially unnecessary (even confusing)
   sci_tofrr3 = dt_42r_21r*sci->tac_factor[6] - sci->tac_off[6] ;   /* S42R- S21R */  // tac_off is essentially unnecessary (even confusing)
   sci_b_tofll3 = Check_WinCond(sci_tofll3,cSCI_LL3);
   sci_b_tofrr3 = Check_WinCond(sci_tofrr3,cSCI_LL3);
   if(sci_b_tofll3 && sci_b_tofrr3){
     sci_tof3        =   (sci->tof_bll3 * sci_tofll3 + sci->tof_a3 + sci->tof_brr3 * sci_tofrr3)/2.0 ;  // tof_a3  is essentially unnecessary (even confusing) = 0
     sci_tof3_calib   =  -1.0*sci_tof3 + id->id_tofoff3;
   }
    else {sci_tof3=0;sci_tof3_calib=0;}
  /*   S21 - S81 Calibrated tof  */
   sci_tofll4 = dt_21l_81l*sci->tac_factor[9] - sci->tac_off[9] ;     /* S81L- S21L */  // tac_off is essentially unnecessary (even confusing)
   sci_tofrr4 = dt_21r_81r*sci->tac_factor[10] - sci->tac_off[10] ;   /* S82R- S21R */  // tac_off is essentially unnecessary (even confusing)

   sci_b_tofll4 = Check_WinCond(sci_tofll4, cSCI_LL4);// cSCI_TofLL4->Test(sci_tofll4);
   sci_b_tofrr4 = Check_WinCond(sci_tofrr4, cSCI_RR4);// cSCI_TofRR4->Test(sci_tofrr4);


   /*   S22 - S41 Calibrated tof  */
   sci_tofll5 = dt_22l_41l*sci->tac_factor[12] - sci->tac_off[12] ;     /* S41L- S22L */  // tac_off is essentially unnecessary (even confusing)
   sci_tofrr5 = dt_22r_41r*sci->tac_factor[13] - sci->tac_off[13] ;     /* S41R- S22R */  // tac_off is essentially unnecessary (even confusing)

   sci_b_tofll5 = Check_WinCond(sci_tofll5,cSCI_LL5);
   sci_b_tofrr5 = Check_WinCond(sci_tofrr5,cSCI_RR5);

   if(sci_b_tofll5 && sci_b_tofrr5){
     sci_tof5        =   (sci->tof_bll5 * sci_tofll5 + sci->tof_a5 + sci->tof_brr5 * sci_tofrr5)/2.0 ;  // tof_a5  is essentially unnecessary (even confusing) = 0
     sci_tof5_calib   =  -1.0*sci_tof5 + id->id_tofoff5;

   }
    else {sci_tof5=0;sci_tof5_calib=0;}

   // sum of Tof_LL and Tof_RR corrects for position in stop/start scint.
   if (sci_b_tofll4 && sci_b_tofrr4)
     {      // TOF SC81 - SC21 [ps]
       sci_tof4 =  (sci->tof_bll4 * sci_tofll4 + sci->tof_a4
            + sci->tof_brr4 * sci_tofrr4)/2.0 ;

     }


   /* check for polygon in raw detof spectrum of SC41 */

  // sci_b_detof = Check_PolyCond_X_Y(sci_tof2, sci_e[5], cSCI_detof, 4); // cSCI_detof->Test(sci_tof2, sci_e[5]);
 ///==================================================================================///
                                /// Start of MHTDC ID analysis
///==================================================================================///
  float speed_light = 0.299792458; //m/ns
  float temp_tm_to_MeV = 299.792458;
  float temp_mu = 931.4940954; //MeV

  // Extraction of position to be used for momentum analysis
  float temp_s8x = mhtdc_sc81lr_x;
  float temp_s4x = -999.;
  if(b_tpc_xy[4] && b_tpc_xy[5]){
    temp_s4x = tpc_x_s4 ;
  //  cout<<"!!!temp_s4x " <<temp_s4x << endl;

  }
  float temp_s2x = -999.; //fill in the next if part
  float temp_s2x_mhtdc[10]={0};
  float temp_a2 = 0;
  for(int i=0; i<10; i++){
  if(1== id->mhtdc_s2pos_option){//SC21X from multihit tdc is used for S2X
    temp_s2x_mhtdc[i] = mhtdc_sc21lr_x[i];
    }
  if(3== id->mhtdc_s2pos_option){//SC22X from multihit tdc is used for S2X
     
    temp_s2x_mhtdc[i] = mhtdc_sc22lr_x[i];
    }
  }
  if(2== id->mhtdc_s2pos_option){//TPCX is used
    if(b_tpc_xy[2] && b_tpc_xy[3]){//tpc2324
      temp_s2x = tpc_x_s2_foc_23_24;
      temp_a2 =tpc_angle_x_s2_foc_23_24;
    }else if(b_tpc_xy[1] && b_tpc_xy[3]){//tpc2224
      temp_s2x = tpc_x_s2_foc_22_24;
      temp_a2 = tpc_angle_x_s2_foc_22_24;
    }else if (b_tpc_xy[0] && b_tpc_xy[1]){//tpc2122
      temp_s2x = tpc_x_s2_foc_21_22;
      temp_a2 = tpc_angle_x_s2_foc_21_22;
    }
  }

  ////=======================================
  ////   S2S4 MultihitTDC ID analysis
for(int i=0; i<10;i++){
  id_mhtdc_beta_s2s4[i]=0;
  id_mhtdc_aoq_s2s4[i]=0;
  id_mhtdc_gamma_s2s4[i]=0;
  id_mhtdc_aoq_corr_s2s4[i]=0;
  id_mhtdc_z_music42[i]=0;
  id_mhtdc_v_cor_music41[i]=0;
  id_mhtdc_z_music41[i]=0;
  id_mhtdc_v_cor_music42[i]=0;
  id_mhtdc_delta_s2s4[i]=0;
}

  float mean_brho_s2s4 =0;
///ID Select SC21(1) TPC(2) SC22(3)
if(1== id->mhtdc_s2pos_option){
  // Calculation of velocity beta and gamma
  for (int i=0; i<10; i++){
       if(1==id->tof_s4_select && mhtdc_tof4121[i]>-100)id_mhtdc_beta_s2s4[i]   =  ( id->mhtdc_length_s2s4 / mhtdc_tof4121[i]) / speed_light;
       if(3==id->tof_s4_select && mhtdc_tof4122[i]>-100)id_mhtdc_beta_s2s4[i]   =  ( id->mhtdc_length_s2s4 / mhtdc_tof4122[i]) / speed_light;
       
       id_mhtdc_gamma_s2s4[i]  = 1./sqrt(1. - id_mhtdc_beta_s2s4[i]*id_mhtdc_beta_s2s4[i]);

  // calculation of delta(momentum_deviation) and AoQ
   mean_brho_s2s4 = 0.5*( frs->bfield[2] + frs->bfield[3] );

    
   if(temp_s4x==-999 || temp_s2x_mhtdc[i]==-999){
      id_mhtdc_aoq_s2s4[i]=0;
      id_mhtdc_aoq_corr_s2s4[i]=0;
    }
  
   else if( -200<temp_s4x && temp_s4x<200. && -200.< temp_s2x_mhtdc[i] && temp_s2x_mhtdc[i]<200. ){
            ///id_mhtdc_delta_s2s4[i] = ( temp_s4x - (temp_s2x_mhtdc[i] * frs->magnification[1] ))/(-1.0 * frs->dispersion[1] *1000.0 ) ; //1000 is dispertsion from meter to mm. -1.0 is sign definition.
     id_mhtdc_delta_s2s4[i] = ( temp_s4x - (temp_s2x_mhtdc[i] * frs->magnification[1] ))/(-1.0 * frs->dispersion[1] *1000.0 ) ; //1000 is dispersion from meter to mm. -1.0 is sign definition.

       if(0.0 < id_mhtdc_beta_s2s4[i] && id_mhtdc_beta_s2s4[i] < 1.0){
            id_mhtdc_aoq_s2s4[i] = mean_brho_s2s4 *( 1. + id_mhtdc_delta_s2s4[i]   ) * temp_tm_to_MeV / (temp_mu * id_mhtdc_beta_s2s4[i] * id_mhtdc_gamma_s2s4[i]);
        
            for(int j=0; j<AoQ_Shift_array; j++){
                   if(ts_mins >=FRS_WR_i[j] && ts_mins < FRS_WR_j[j]){
            //Gain Match AoQ
            id_mhtdc_aoq_s2s4[i] = (id_mhtdc_aoq_s2s4[i] - AoQ_shift_Sci21_value[j])-0.029100;
            
                }
            }
            ///No angle correction for SCI
            id_mhtdc_aoq_corr_s2s4[i] = id_mhtdc_aoq_s2s4[i];
    
            

     mhtdc_gamma1square[i]  = 1.0 + TMath::Power(((299.792458/931.494)*(id_brho[0]/id_mhtdc_aoq_s2s4[i])),2);
               id_mhtdc_gamma_ta_s2[i]  = TMath::Sqrt(mhtdc_gamma1square[i] );
               id_mhtdc_dEdegoQ[i]     =  (id_mhtdc_gamma_ta_s2[i]  - id_mhtdc_gamma_s2s4[i])*id_mhtdc_aoq_s2s4[i];
               id_mhtdc_dEdeg[i]       =  id_mhtdc_dEdegoQ[i] * id_mhtdc_z_music41[i];
      }
    }
  else id_mhtdc_aoq_s2s4[i]=0;
  }
}
//ID Select TPC
if(2== id->mhtdc_s2pos_option){
   // Calculation of velocity beta and gamma
  for (int i=0; i<10; i++){
 
       if(1==id->tof_s4_select && mhtdc_tof4121[i]>-100)id_mhtdc_beta_s2s4[i]   =  ( id->mhtdc_length_s2s4 / mhtdc_tof4121[i]) / speed_light;
     
       if(3==id->tof_s4_select && mhtdc_tof4122[i]>-100)id_mhtdc_beta_s2s4[i]   =  ( id->mhtdc_length_s2s4 / mhtdc_tof4122[i]) / speed_light;
        id_mhtdc_gamma_s2s4[i]  = 1./sqrt(1. - id_mhtdc_beta_s2s4[i]*id_mhtdc_beta_s2s4[i]);

  // calculation of delta(momentum_deviation) and AoQ
   mean_brho_s2s4 = 0.5*( frs->bfield[2] + frs->bfield[3] );

    ///if(temp_s4x==-999 || temp_s2x_mhtdc[i]==-999){
   if(temp_s4x==-999 || temp_s2x==-999){
      id_mhtdc_aoq_s2s4[i]=0;
        id_mhtdc_aoq_corr_s2s4[i]=0;
    }

   // else if( -200<temp_s4x && temp_s4x<200. && -200.< temp_s2x_mhtdc[i] && temp_s2x_mhtdc[i]<200. ){
   else if( -200<temp_s4x && temp_s4x<200. && -200.< temp_s2x && temp_s2x<200. ){
            ///id_mhtdc_delta_s2s4[i] = ( temp_s4x - (temp_s2x_mhtdc[i] * frs->magnification[1] ))/(-1.0 * frs->dispersion[1] *1000.0 ) ; //1000 is dispertsion from meter to mm. -1.0 is sign definition.
     id_mhtdc_delta_s2s4[i] = ( temp_s4x - (temp_s2x * frs->magnification[1] ))/(-1.0 * frs->dispersion[1] *1000.0 ) ; //1000 is dispertsion from meter to mm. -1.0 is sign definition.

       if(0.0 < id_mhtdc_beta_s2s4[i] && id_mhtdc_beta_s2s4[i] < 1.0){
            id_mhtdc_aoq_s2s4[i] = mean_brho_s2s4 *( 1. + id_mhtdc_delta_s2s4[i]   ) * temp_tm_to_MeV / (temp_mu * id_mhtdc_beta_s2s4[i] * id_mhtdc_gamma_s2s4[i]);
           
            ///Gain Match AoQ
             for(int j=0; j<AoQ_Shift_array; j++){
               if(ts_mins >=FRS_WR_i[j] && ts_mins < FRS_WR_j[j]){
             id_mhtdc_aoq_s2s4[i] = id_mhtdc_aoq_s2s4[i] - AoQ_shift_TPC_value[j]-0.01097;
          
                }
             }
            
             id_mhtdc_aoq_corr_s2s4[i] = id_mhtdc_aoq_s2s4[i] - id->a2AoQCorr * temp_a2;
	  
             
     mhtdc_gamma1square[i] = 1.0 + TMath::Power(((299.792458/931.494)*(id_brho[0]/id_mhtdc_aoq_s2s4[i])),2);
               id_mhtdc_gamma_ta_s2[i] = TMath::Sqrt(mhtdc_gamma1square[i]);
               id_mhtdc_dEdegoQ[i]     =  (id_mhtdc_gamma_ta_s2[i]  - id_mhtdc_gamma_s2s4[i])*id_mhtdc_aoq_s2s4[i];
               id_mhtdc_dEdeg[i]       =  id_mhtdc_dEdegoQ[i] * id_mhtdc_z_music41[i];
             
      }
    }
  else id_mhtdc_aoq_s2s4[i]=0;
  }
}
  // calculation of dE and Z
  // from MUSIC41
  for (int k=0;k<10;k++){
  float temp_music41_de = de[0]>0.0;
  if( (temp_music41_de>0.0)  && (id_mhtdc_beta_s2s4[k]>0.0) && (id_mhtdc_beta_s2s4[k]<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){

      sum += power * id->mhtdc_vel_a_music41[i];
      power *= id_mhtdc_beta_s2s4[k];
      id_mhtdc_v_cor_music41[k] = sum;

    }
  }
  if(id_mhtdc_v_cor_music41[k]!=0)


    if (id_mhtdc_v_cor_music41[k] > 0.0){
      id_mhtdc_z_music41[k] = frs->primary_z * sqrt(de[0]/id_mhtdc_v_cor_music41[k] ) + id->mhtdc_offset_z_music41;

    }
  }

for (int k=0;k<10;k++){
  float temp_music42_de = de[1]>0.0;
  if( (temp_music42_de>0.0)  && (id_mhtdc_beta_s2s4[k]>0.0) && (id_mhtdc_beta_s2s4[k]<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){
      sum += power * id->mhtdc_vel_a_music42[i];
      power *= id_mhtdc_beta_s2s4[k];
    }
    id_mhtdc_v_cor_music42[k] = sum;
    if (id_mhtdc_v_cor_music42 [k]> 0.0){
      id_mhtdc_z_music42[k] = frs->primary_z * sqrt(de[1]/id_mhtdc_v_cor_music42[k] ) + id->mhtdc_offset_z_music42;
    }
  }
}


///Gain match Z
  for(int i=0; i<Z_Shift_array; i++){
           for (int k=0; k<10 ; k++) {
           if(ts_mins >=FRS_WR_a[i] && ts_mins < FRS_WR_b[i]){
               id_mhtdc_z_music41[k] = id_mhtdc_z_music41[k] - Z1_shift_value[i];
               id_mhtdc_z_music42[k] = id_mhtdc_z_music42[k] - Z2_shift_value[i];
                }
            }
      }
      for(int i=0; i<10; i++){
          if(id_mhtdc_aoq_s2s4[i]!=0){
        mhtdc_gamma1square[i] = 1.0 + TMath::Power(((299.792458/931.494)*(id_brho[0]/id_mhtdc_aoq_s2s4[i])),2);
               id_mhtdc_gamma_ta_s2[i] = TMath::Sqrt(mhtdc_gamma1square[i]);
               id_mhtdc_dEdegoQ[i]     =  (id_mhtdc_gamma_ta_s2[i]  - id_mhtdc_gamma_s2s4[i])*id_mhtdc_aoq_s2s4[i];
               id_mhtdc_dEdeg[i]       =  id_mhtdc_dEdegoQ[i] * id_mhtdc_z_music41[i];
        }
      }


//  id_trigger=trigger;

///TAC stuff starts here
  // focal plane information
  // S2 priority: tpc2324 -> tpc2224 -> tpc2122 -> sc22 -> sc21
     if(1 == id->x_s2_select){

  if(b_tpc_xy[2] && b_tpc_xy[3]){//tpc2324
    id_x2 = tpc_x_s2_foc_23_24;
    id_y2 = tpc_y_s2_foc_23_24;
    id_a2 = tpc_angle_x_s2_foc_23_24;

  //cout<<"a2 defined here tpc_angle_x_s2_foc_23_24 " << tpc_angle_x_s2_foc_23_24<< endl;
    id_b2 = tpc_angle_y_s2_foc_23_24;
  }else if (b_tpc_xy[1] && b_tpc_xy[3]){//tpc2224
    id_x2 = tpc_x_s2_foc_22_24;
    id_y2 = tpc_y_s2_foc_22_24;
    id_a2 = tpc_angle_x_s2_foc_22_24;
    id_b2 = tpc_angle_y_s2_foc_22_24;
  }else if (b_tpc_xy[0] && b_tpc_xy[1]){//tpc2122
    id_x2 = tpc_x_s2_foc_21_22;
    id_y2 = tpc_y_s2_foc_21_22;
    id_a2 = tpc_angle_x_s2_foc_21_22;
    id_b2 = tpc_angle_y_s2_foc_21_22;
  }
  }else if (2 == id->x_s2_select){
  if (sci_b_x[2]){//sc21
    id_x2 = sci_x[2];
    id_y2 = 0.0;
    id_a2 = 0.0;
    id_b2 = 0.0;
  }
  }else if(3 == id->x_s2_select){

    if (sci_b_x[3]){//sc22
      id_x2 = sci_x[3];
      id_y2 = 0.0;
      id_a2 = 0.0;
      id_b2 = 0.0;
    }
  }
  // S4 only 1 possibility =  TPC4142
  if(b_tpc_xy[4] && b_tpc_xy[5]){
    id_x4 = tpc_x_s4;
    id_a4 = tpc_angle_x_s4;
    id_y4 = tpc_y_s4;
    id_b4 = tpc_angle_y_s4;
  }

  // S8 only 1 possibility =  SC81x
  if( sci_b_x[10]){
    id_x8 = sci_x[10];
    id_a8 = 0.0;
    id_y8 = 0.0;
    id_b8 = 0.0;
  }

  /*  check that the positions are OK   */

  id_b_x2 = Check_WinCond(id_x2, cID_x2);// cID_x2->Test(id_x2);
  id_b_x4 = Check_WinCond(id_x4, cID_x4);// cID_x4->Test(id_x4);

 // id_b_x8 = Check_WinCond(id_x8, cID_x8);// cID_x4->Test(id_x4);


  // remove temporarily
  // hID_E_Xs4->Fill(id_x4,de[0]);// added by 2016Jun.16
  // hID_E_Xs2->Fill(id_x2,de[0]);// added by 2016Jun.16

  /*----------------------------------------------------------*/
  /* Determination of beta                                    */
  /* ID.TofOff(i)                   Flight time offset [ps]   */
  /* ID.Path(i)                     Flight path/c [ps]        */
  /* TOF(i)        BIN FLOAT(24),   Flight time  [ps]         */
  /*----------------------------------------------------------*/
    id_beta=0;
  //SC21-SC41
  if(1 == id->tof_s4_select){ //SC21-SC41
  if (sci_b_tofll2 && sci_b_tofrr2){
    //// id_beta = id->id_path2 /(id->id_tofoff2 - sci_tof2);
    id_beta = id->id_path2 /  sci_tof2_calib ;// calculate non-inverted "real" tof already in sci analysis.
   // cout<<"id_beta " <<id_beta <<" id->id_path2 " <<id->id_path2 << " sci_tof2_calib " <<sci_tof2_calib << endl;
//     if(bDrawHist){
//       hID_beta->Fill(id_beta*1000.);
    }
  }else if(2 == id->tof_s4_select){ //SC21-SC42
    if (sci_b_tofll3 && sci_b_tofrr3){
      id_beta = id->id_path3 /  sci_tof3_calib ;// calculate non-inverted "real" tof already in sci analysis.
//       if(bDrawHist){
//     hID_beta->Fill(id_beta*1000.);
//       }
    }
  }else if(3 == id->tof_s4_select){ //SC22-SC41
    if (sci_b_tofll5 && sci_b_tofrr5){
      id_beta = id->id_path5 /  sci_tof5_calib ;// calculate non-inverted "real" tof already in sci analysis.

//       cout<<"FRS id_beta " <<id_beta<<" sci_tof5_calib " <<sci_tof5_calib << " id->id_path5 " <<id->id_path5 << endl;
//       if(bDrawHist){
//     hID_beta->Fill(id_beta*1000.);
//       }
    }
  }

  //SC21-SC81
//   if (sci_b_tofll4 && sci_b_tofrr4){
//     id_beta_s2s8 = id->id_path4 /  sci_tof4_calib ;// calculate non-inverted "real" tof already in sci analysis.
// //     if(bDrawHist){
// //       hID_beta_s2s8->Fill(id_beta_s2s8*1000.);
// //     }
//   }


  // /*------------------------------------------------------*/
  // /* Determination of Brho                                */
  // /* Dispersion and magnification are still the same      */
  // /* variable for S41-S21 and S42-S41, adjust in setup.C  */
  // /*------------------------------------------------------*/

  // first half of FRS, TA-S2

  if (id_b_x2){
      id_rho[0]  = frs->rho0[0] * (1. - id_x2/1000./frs->dispersion[0]);
      id_brho[0] = (fabs(frs->bfield[0]) + fabs(frs->bfield[1]))/ 2. * id_rho[0];
     //   if(bDrawHist){  hID_BRho[0]->Fill(id_brho[0]); }
  }
  // second half S2-S4

  if (id_b_x2 && id_b_x4){
      id_rho[1] = frs->rho0[1] * (1. - (id_x4 - frs->magnification[1] * id_x2) / 1000. / frs->dispersion[1]) ;
      id_brho[1] = (fabs(frs->bfield[2]) + fabs(frs->bfield[3]))/ 2. * id_rho[1];

  }

  //cout<<"222 id_brho[1]  " << id_brho[1] << "frs->bfield[0]" << frs->bfield[2] << " frs->bfield[3] " << frs->bfield[3] << endl;
 // cout<<"id_rho[1] " << id_rho[1] << " frs->rho0[1] " << frs->rho0[1] << " id_x4 " << id_x4 << " frs->magnification[1] " << frs->magnification[1] << " id_x2 " << id_x2 << " frs->dispersion[1] " << frs->dispersion[1]<< endl;

 /*--------------------------------------------------------------*/
  /* Determination of A/Q                                         */
  /*--------------------------------------------------------------*/
  /* Beta(i)       BIN FLOAT(24),   Beta = v/c                    */
  /* Gamma(i)      BIN FLOAT(24),   Gamma= sqrt(1/1-beta**2)      */
  /*--------------------------------------------------------------*/
  Float_t f = 931.4940 / 299.792458 ;    /* factor needed for aoq calculation.. the u/(c*10^-6) factor  */


  /* for S2-S4 */

  if (sci_b_tofll2 && sci_b_tofrr2 && id_b_x2 && id_b_x4){


      if ((id_beta>0.0) && (id_beta<1.0)){
      id_gamma = 1./sqrt(1. - id_beta * id_beta);
      id_AoQ   = id_brho[1]/id_beta/id_gamma/f ;
      id_AoQ_corr = id_AoQ - id->a2AoQCorr * id_a2;  //correction for id_a2, JK 16.9.11
      if(id_AoQ_corr>0){
            
      for(int i=0; i<AoQ_Shift_array; i++){
           if(ts_mins >=FRS_WR_i[i] && ts_mins < FRS_WR_j[i]){
        
         if(2 == id->x_s2_select){
           id_AoQ = id_AoQ - AoQ_shift_Sci21_value[i];
               id_AoQ_corr = id_AoQ_corr - AoQ_shift_Sci21_value[i];
               
         }
         else if(3 == id->x_s2_select) {
           id_AoQ = id_AoQ - AoQ_shift_Sci22_value[i];
               id_AoQ_corr = id_AoQ_corr - AoQ_shift_Sci22_value[i];      
                   
        }
        else {
           id_AoQ = id_AoQ - AoQ_shift_TPC_value[i];
               id_AoQ_corr = id_AoQ_corr - AoQ_shift_TPC_value[i];
                
            }
        }
    }
}

     // cout<<"FRS Calc id_AoQ " << id_AoQ <<" id_AoQ_corr "<<id_AoQ_corr <<" id_a2 " <<id_a2 <<  endl;

      // if (!b_tpc_xy[4] || !b_tpc_xy[5]) // no sense to do "if TPC4142 dont work, correct with S4 angle ... "
      //   id_AoQ_corr = id_AoQ - id->a4AoQCorr * id_a4;
//        if(bDrawHist)
//          {
//            hID_AoQ->Fill(id_AoQ);
//            hID_AoQcorr->Fill(id_AoQ_corr);
//        hID_DeltaBrho_AoQ->Fill(id_AoQ,id_brho[0]-id_brho[1]);
//          }
      id_b_AoQ = true;
      }
  }

  /* for S2-S8  */
//   if (sci_b_tofll4 && sci_b_tofrr4 && id_b_x2 && id_b_x8){
//     if ((id_beta_s2s8>0.0) && (id_beta_s2s8<1.0)){
//       id_gamma_s2s8 = 1./sqrt(1. - id_beta_s2s8 * id_beta_s2s8);
//       id_AoQ_s2s8      = id_brho[2]/id_beta_s2s8/id_gamma_s2s8/ f ;
//       if(bDrawHist)
//  {
//    hID_AoQ_s2s8->Fill(id_AoQ_s2s8);
//  }
//       id_b_AoQ_s2s8 = kTRUE;
//     }
//   }


  /*------------------------------------------------*/
  /* Determination of Z                             */
  /*------------------------------------------------*/
  /****  S4  (MUSIC 1)   */
  //  if((de_cor[0]>0.0) && (id_beta>0.0) && (id_beta<1.0)) {

  if((de[0]>0.0) && (id_beta>0.0) && (id_beta<1.0))
    {
      Double_t power = 1., sum = 0.;
      for (int i=0;i<4;i++){
      sum += power * id->vel_a[i];
      power *= id_beta;
      }
      id_v_cor = sum;
      if (id_v_cor > 0.0){
    id_z = frs->primary_z * sqrt(de[0]/id_v_cor) + id->offset_z;
      }
      if ((id_z>0.0) && (id_z<100.0)){
    id_b_z = kTRUE;
      }
    }


  /****  S4  (MUSIC 2)   */

  if((de[1]>0.0) && (id_beta>0.0) && (id_beta<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++)
      {
    sum += power * id->vel_a2[i];
    power *= id_beta;
      }
    id_v_cor2 = sum;

    if (id_v_cor2 > 0.0){
      id_z2 = frs->primary_z * sqrt(de[1]/id_v_cor2) + id->offset_z2;

    }
    if ((id_z2>0.0) && (id_z2<100.0)){
      id_b_z2 = kTRUE;
    }
  }
//Gainmatch Z
for(int i=0; i<Z_Shift_array; i++){
           if(ts_mins >=FRS_WR_a[i] && ts_mins < FRS_WR_b[i]){
               id_z = id_z - Z1_shift_value[i];
               id_z2 = id_z2 - Z2_shift_value[i];
            }
      }
      
      
  /****  S4  (MUSIC)   */
  if((de[2]>0.0) && (id_beta>0.0) && (id_beta<1.0)){
    Double_t power = 1., sum = 0.;
    for (int i=0;i<4;i++){
      sum += power * id->vel_a3[i];
      power *= id_beta;
    }
    id_v_cor3 = sum;
    if (id_v_cor3 > 0.0){
      id_z3 = frs->primary_z * sqrt(de[2]/id_v_cor3) + id->offset_z3;
    }

    if ((id_z3>0.0) && (id_z3<100.0)){
      id_b_z3 = kTRUE;
    }
  }


  //Z from sc81
//   if((sci_e[10]>0.0) && (id_beta_s2s8>0.0) && (id_beta_s2s8<1.0)){
//     Double_t power = 1., sum = 0.;
//     for (int i=0;i<4;i++){
//       sum += power * id->vel_a_sc81[i];
//       power *= id_beta_s2s8;
//     }
//     id_v_cor_sc81 = sum;
//     if (id_v_cor_sc81 > 0.0){
//       id_z_sc81 = frs->primary_z * sqrt(sci_e[10]/id_v_cor_sc81) + id->offset_z_sc81;
//     }
//
//     if ((id_z_sc81>0.0) && (id_z_sc81<100.0)){
//       id_b_z_sc81 = kTRUE;
//     }
//   }

  //Z from tpc21222324
  double temp_s2tpc_de=1.0; int temp_s2tpc_de_count=0;
  for(int ii=0; ii<4; ii++){
    if(b_tpc_de[ii]){
      temp_s2tpc_de *=tpc_de[ii]; temp_s2tpc_de_count++;
    }
  }
  if(temp_s2tpc_de_count == 2){
    id_de_s2tpc = pow(temp_s2tpc_de, 1./temp_s2tpc_de_count);
    id_b_de_s2tpc = kTRUE;
  }

//   if(id_b_de_s2tpc && (id_beta_s2s8>0.0) && (id_beta_s2s8<1.0)){
//     Double_t power = 1., sum = 0.;
//     for (int i=0;i<4;i++){
//       sum += power * id->vel_a_s2tpc[i];
//       power *= id_beta_s2s8;
//     }
//     id_v_cor_s2tpc = sum;
//     if (id_v_cor_s2tpc > 0.0){
//       id_z_s2tpc = frs->primary_z * sqrt( id_de_s2tpc/id_v_cor_s2tpc ) + id->offset_z_s2tpc;
//       //printf("id_de_s2tpc = %f, v_cor = %f, z_s2tpc = %f\n",id_de_s2tpc, id_v_cor_s2tpc, id_z_s2tpc);
//     }
//
//     if ((id_z_s2tpc>0.0) && (id_z_s2tpc<100.0)){
//       id_b_z_s2tpc = kTRUE;
//     }
//   }
 /// charge state for high Z
  /// S468 2020 April

  if(id_b_AoQ && id_b_x2 && id_b_z){
    float gamma1square = 1.0 + TMath::Power(((299.792458/931.494)*(id_brho[0]/id_AoQ)),2);
    id_gamma_ta_s2 = TMath::Sqrt(gamma1square);
    id_dEdegoQ     =  (id_gamma_ta_s2  - id_gamma)*id_AoQ;
    id_dEdeg       =  id_dEdegoQ * id_z;
  //  cout<<"id_dEdeg " <<id_dEdeg <<" id_gamma_ta_s2 " <<id_gamma_ta_s2 << " id_gamma " <<id_gamma <<" id_AoQ " <<id_AoQ <<    endl;
  }
   /*------------------------------------------------*/
   /* Identification Plots                           */
   /*------------------------------------------------*/

   /****  for S2-S4  ****/

//    for (int i=0;i<5;i++){
//      id_b_x4AoQ[i] = Check_PolyCond_Multi_X_Y(id_AoQ, id_x4, cID_x4AoQ, 5, 0);
//      id_b_x2AoQ[i] = Check_PolyCond_Multi_X_Y(id_AoQ, id_x2, cID_x2AoQ, 5, 0);
//      id_b_z_AoQ[i] =  Check_PolyCond_Multi_X_Y(id_AoQ, id_z, cID_Z_AoQ, 5, i);
//    }
//          mhtdc_tof4121=0;
//    mhtdc_tof4122=0;
//    mhtdc_tof4221=0;

}
/// WR to FRS branch
Int_t FRS_Detector_System::WR_Check(int ts_minutes){
    ts_mins =ts_minutes;
    return ts_mins;
}
 ///A.K.M. NOTE: Multi-dimensional arrays don't decay to pointers as one-dimensional arrays do https://stackoverflow.com/questions/12674094/array-to-pointer-decay-and-passing-multidimensional-arrays-to-functions
void FRS_Detector_System::get_Event_data(Raw_Event* RAW){

    RAW->set_DATA_MUSIC(de, de_cor, music_e1, music_e2, music_t1, music_t2);
    RAW->set_DATA_SCI(sci_l, sci_r, sci_e, sci_tx, sci_x);
    RAW->set_DATA_SCI_dT(dt_21l_21r, dt_41l_41r, dt_21l_41l, dt_21r_41r, dt_42l_42r, dt_43l_43r,dt_42l_21l, dt_42r_21r, dt_81l_81r, dt_21l_81l, dt_21r_81r);
    RAW->set_DATA_SCI_ToF(sci_tofll2, sci_tofll3, sci_tofll5, sci_tof2, sci_tofrr2, sci_tofrr3, sci_tofrr5, sci_tof3,sci_tof5,sci_tof2_calib,sci_tof3_calib,sci_tof5_calib);
    
    RAW->set_DATA_TPC(tpc_lt,tpc_rt, tpc_x, tpc_y, tpc_a, tpc_l, tpc_r, tpc_dt);
    
    RAW->set_DATA_TPC_S2(tpc_x_s2_foc_23_24, tpc_y_s2_foc_23_24, tpc_angle_x_s2_foc_23_24, tpc_angle_y_s2_foc_23_24,tpc23_24_sc21_x,tpc23_24_sc21_y,tpc23_24_sc22_x ,tpc23_24_sc22_y);
    
     RAW->set_DATA_TPC_S4(tpc_x_s4, tpc_y_s4, tpc_angle_x_s4, tpc_angle_y_s4,tpc_sc41_x,tpc_sc41_y, tpc_sc42_x,tpc_sc42_y);
    
    RAW->set_DATA_ID_2_4(id_x2, id_y2, id_a2, id_b2, id_x4, id_y4, id_a4, id_b4);
    RAW->set_DATA_ID_Beta_Rho(id_brho, id_rho, id_beta, id_beta3, id_gamma);
    RAW->set_DATA_ID_Z_AoQ(id_AoQ, id_AoQ_corr, id_z, id_z2, id_z3,id_dEdeg,id_dEdegoQ);
    RAW->set_DATA_ID_Timestamp(timestamp, ts, ts2);
    RAW->set_DATA_FRS_SCALERS(time_in_ms,spill_count,ibin_for_s,ibin_for_100ms,ibin_for_spill,ibin_clean_for_s,ibin_clean_for_100ms, ibin_clean_for_spill,increase_scaler_temp);
    RAW->set_DATA_VFTX(TRaw_vftx_21l,TRaw_vftx_21r,TRaw_vftx_22l,TRaw_vftx_22r,TRaw_vftx_41l,TRaw_vftx_41r,TRaw_vftx_42l,TRaw_vftx_42r,TRaw_vftx);

    RAW->set_DATA_RAW_MHTDC(mhtdc_sc21lr_dt,mhtdc_sc21lr_x,mhtdc_sc22lr_dt,mhtdc_sc22lr_x,mhtdc_sc41lr_dt,mhtdc_sc41lr_x,mhtdc_sc42lr_dt,mhtdc_sc42lr_x);

    RAW->set_DATA_ID_MHTDC(id_mhtdc_aoq_s2s4, id_mhtdc_aoq_corr_s2s4, id_mhtdc_z_music41, id_mhtdc_z_music42, id_mhtdc_dEdeg, id_mhtdc_dEdegoQ, id_mhtdc_beta_s2s4, mhtdc_tof4121, mhtdc_tof4221,mhtdc_tof4122);
}

//---------------------------------------------------------------

int* FRS_Detector_System::get_pdata(){return pdata;}

//---------------------------------------------------------------

Float_t FRS_Detector_System::rand3(){

  return random3.Uniform(-0.5,0.5);

}

//---------------------------------------------------------------

Int_t FRS_Detector_System::getbits(Int_t value, int nword, int start, int length){

  UInt_t buf = (UInt_t) value;
  buf = buf >> ((nword-1)*16 + start - 1);
  buf = buf & ((1 << length) - 1);
  return buf;

}

//---------------------------------------------------------------

Int_t FRS_Detector_System::get2bits(Int_t value, int nword, int start, int length){

  UInt_t buf = (UInt_t) value;
  buf = buf >> ((nword-1)*32 + start - 1);
  buf = buf & ((1 << length) - 1);
  return buf;

}

//---------------------------------------------------------------
Bool_t FRS_Detector_System::Check_WinCond(Float_t P, Float_t* V){

    if(P >= V[0] && P <= V[1]) return true;
    else return false;

}

//---------------------------------------------------------------
Bool_t FRS_Detector_System::Check_WinCond_Multi(Float_t P, Float_t** V, int cond_num){

    if(P >= V[cond_num][0] && P <= V[cond_num][1]) return true;
    else return false;

}

//---------------------------------------------------------------
Bool_t FRS_Detector_System::Check_WinCond_Multi_Multi(Float_t P, Float_t*** V, int cond_num, int cond_num_2){

    if(P >= V[cond_num][cond_num_2][0] && P <= V[cond_num][cond_num_2][1]) return true;
    else return false;

}

//---------------------------------------------------------------

// cn_PnPoly(): crossing number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
//      Return:  0 = outside, 1 = inside
// This code is patterned after [Franklin, 2000]
Bool_t FRS_Detector_System::Check_PolyCond(Float_t* P, Float_t** V, int n ){
    int    cn = 0;    // the  crossing number counter

    // loop through all edges of the polygon
    for (int i=0; i<n; i++) {    // edge from V[i]  to V[i+1]
       if (((V[i][1] <= P[1]) && (V[i+1][1] > P[1]))     // an upward crossing
        || ((V[i][1] > P[1]) && (V[i+1][1] <=  P[1]))) { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float)(P[1]  - V[i][1]) / (V[i+1][1] - V[i][1]);
            if (P[0] <  V[i][0] + vt * (V[i+1][0] - V[i][0])) // P.x < intersect
                 ++cn;   // a valid crossing of y=P.y right of P.x
        }
    }

    if((cn&1) == 0) return false;
    if((cn&1) == 1) return true;
    else return false;

    //return (cn&1);    // 0 if even (out), and 1 if  odd (in)

}

//---------------------------------------------------------------

// cn_PnPoly(): crossing number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
//      Return:  0 = outside, 1 = inside
// This code is patterned after [Franklin, 2000]
Bool_t FRS_Detector_System::Check_PolyCond_Multi(Float_t* P, Float_t*** V, int n, int cond_num )
{
    int    cn = 0;    // the  crossing number counter

    // loop through all edges of the polygon
    for (int i=0; i<n; i++) {    // edge from V[i]  to V[i+1]
       if (((V[cond_num][i][1] <= P[1]) && (V[cond_num][i+1][1] > P[1]))     // an upward crossing
        || ((V[cond_num][i][1] > P[1]) && (V[cond_num][i+1][1] <=  P[1]))) { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float)(P[1]  - V[cond_num][i][1]) / (V[cond_num][i+1][1] - V[cond_num][i][1]);
            if (P[0] <  V[cond_num][i][0] + vt * (V[cond_num][i+1][0] - V[cond_num][i][0])) // P.x < intersect
                 ++cn;   // a valid crossing of y=P.y right of P.x
        }
    }

    if((cn&1) == 0) return false;
    if((cn&1) == 1) return true;
    else return false;

    //return (cn&1);    // 0 if even (out), and 1 if  odd (in)

}
//---------------------------------------------------------------

// cn_PnPoly(): crossing number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
//      Return:  0 = outside, 1 = inside
// This code is patterned after [Franklin, 2000]
Bool_t FRS_Detector_System::Check_PolyCond_X_Y(Float_t X, Float_t Y, Float_t** V, int n ){
    int    cn = 0;    // the  crossing number counter

    // loop through all edges of the polygon
    for (int i=0; i<n; i++) {    // edge from V[i]  to V[i+1]
       if (((V[i][1] <= Y) && (V[i+1][1] > Y))     // an upward crossing
        || ((V[i][1] > Y) && (V[i+1][1] <=  Y))) { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float)(Y  - V[i][1]) / (V[i+1][1] - V[i][1]);
            if (X <  V[i][0] + vt * (V[i+1][0] - V[i][0])) // P.x < intersect
                 ++cn;   // a valid crossing of y=P.y right of P.x
        }
    }

    if((cn&1) == 0) return false;
    if((cn&1) == 1) return true;
    else return false;

    //return (cn&1);    // 0 if even (out), and 1 if  odd (in)

}

//---------------------------------------------------------------

// cn_PnPoly(): crossing number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
//      Return:  0 = outside, 1 = inside
// This code is patterned after [Franklin, 2000]
Bool_t FRS_Detector_System::Check_PolyCond_Multi_X_Y(Float_t X, Float_t Y, Float_t*** V, int n, int cond_num )
{
    int    cn = 0;    // the  crossing number counter

    // loop through all edges of the polygon
    for (int i=0; i<n; i++) {    // edge from V[i]  to V[i+1]
       if (((V[cond_num][i][1] <= Y) && (V[cond_num][i+1][1] > Y))     // an upward crossing
        || ((V[cond_num][i][1] > Y) && (V[cond_num][i+1][1] <=  Y))) { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float)(Y  - V[cond_num][i][1]) / (V[cond_num][i+1][1] - V[cond_num][i][1]);
            if (X <  V[cond_num][i][0] + vt * (V[cond_num][i+1][0] - V[cond_num][i][0])) // P.x < intersect
                 ++cn;   // a valid crossing of y=P.y right of P.x
        }
    }

    if((cn&1) == 0) return false;
    if((cn&1) == 1) return true;
    else return false;

    //return (cn&1);    // 0 if even (out), and 1 if  odd (in)

}

//---------------------------------------------------------------

void FRS_Detector_System::Setup_Conditions(){

    string line;
    int line_number = 0;

    const char* format = "%f %f %f %f %f %f %f %f %f %f %f %f %f %f";

    ifstream cond_a("Configuration_Files/FRS/FRS_Window_Conditions/lim_csum.txt");

    lim_csum = new Float_t**[4];

    for(int i = 0; i < 4; ++i){

    lim_csum[i] = new Float_t*[7];

        for(int j = 0; j < 7; ++j){


        lim_csum[i][j] = new Float_t[2];

        }
    }


    while(/*cond_a.good()*/getline(cond_a,line,'\n')){

    //getline(cond_a,line,'\n');
    if(line[0] == '#') continue;


        sscanf(line.c_str(),format,&lim_csum[line_number][0][0],&lim_csum[line_number][0][1]
                    ,&lim_csum[line_number][1][0],&lim_csum[line_number][1][1]
                    ,&lim_csum[line_number][2][0],&lim_csum[line_number][2][1]
                    ,&lim_csum[line_number][3][0],&lim_csum[line_number][3][1]
                    ,&lim_csum[line_number][4][0],&lim_csum[line_number][4][1]
                    ,&lim_csum[line_number][5][0],&lim_csum[line_number][5][1]
                    ,&lim_csum[line_number][6][0],&lim_csum[line_number][6][1]);

    line_number++;


    }

   /*lim_csum = {{{300,1800},{350,1800},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}},
                 {{300,1800},{300,1800},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}},
                 {{300,1800},{300,1840},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}},
                 {{300,1800},{300,1810},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}}};
    */



    lim_xsum = new Float_t*[13];
    lim_ysum = new Float_t*[13];

    for(int i = 0; i < 13; ++i){


    lim_xsum[i] = new Float_t[2];
    lim_ysum[i] = new Float_t[2];

    //lim_xsum[i][0] = 1;
    //lim_xsum[i][1] = 8000;
    //lim_ysum[i][0] = 2;
    //lim_ysum[i][1] = 8000;


    }

    line_number = 0;

    format = "%f %f";

    ifstream cond_b("Configuration_Files/FRS/FRS_Window_Conditions/lim_xsum.txt");

    while(/*cond_b.good()*/getline(cond_b,line,'\n')){

    //getline(cond_b,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&lim_xsum[line_number][0],&lim_xsum[line_number][1]);

    line_number++;
    }

    line_number = 0;

    format = "%f %f";

     ifstream cond_c("Configuration_Files/FRS/FRS_Window_Conditions/lim_ysum.txt");

    while(/*cond_c.good()*/getline(cond_c,line,'\n')){

    //getline(cond_c,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&lim_ysum[line_number][0],&lim_ysum[line_number][1]);

    line_number++;
    }

    /*lim_xsum = {  {1,8000},  // MW11
                {1,8000},  // MW21
                {1,8000},  // MW22
                {1,8000},  // MW31
                {1,8000},  // MW41
                {1,8000},  // MW42
                {1,8000},  // MW51
                {1,8000},  // MW61
                {1,8000},  // MW71
                {1,8000},  // MW81
                {1,8000},  // MW82
                {1,8000},  // MWB1
                {1,8000}};  // MWB2

    lim_ysum = { {2,8000},  // MW11
                {2,8000},  // MW21
                {2,8000},  // MW22
                {2,8000},  // MW31
                {2,8000},  // MW41
                {2,8000},  // MW42
                {2,8000},  // MW51
                {2,8000},  // MW61
                {2,8000},  // MW71
                {2,8000},  // MW81
                {2,8000},  // MW82
                {2,8000},  // MWB1
                {2,8000}};  // MWB2*/



    /*for(int i=0;i<7;i++){

    //    cTPC_CSUM[i][0]=MakeWindowCond("TPC/CSUM1",condname,lim_csum1[i][0],
    //                 lim_csum1[i][1],"CSUM1");
    char condname[40];

    sprintf(condname,"TPC/CSUM1%s",tpc_name_ext1[i]);
    cTPC_CSUM[i][0]=MakeWinCond(condname,lim_csum1[i][0],lim_csum1[i][1],"CSUM1");

    sprintf(condname,"CSUM2%s",tpc_name_ext1[i]);
    cTPC_CSUM[i][1]=MakeWindowCond("TPC/CSUM2",condname,lim_csum2[i][0],lim_csum2[i][1],"CSUM2");

    sprintf(condname,"CSUM3%s",tpc_name_ext1[i]);
    cTPC_CSUM[i][2]=MakeWindowCond("TPC/CSUM3",condname,lim_csum3[i][0],lim_csum3[i][1],"CSUM3");

    sprintf(condname,"CSUM4%s",tpc_name_ext1[i]);
    cTPC_CSUM[i][3]=MakeWindowCond("TPC/CSUM4",condname,lim_csum4[i][0],lim_csum4[i][1],"CSUM4");
    }

      for(int i=0;i<13;i++){  // up to MW31
       //up to MWB2 (09.07.2018)

      char condname[40];
      sprintf(condname,"XSUM%s",mw_name_ext[i]);
      cMW_XSUM[i] = MakeWindowCond("MW/XSUM", condname, lim_xsum[i][0], lim_xsum[i][1], MW_XSUM);

      sprintf(condname,"YSUM%s",mw_name_ext[i]);
      cMW_YSUM[i] = MakeWindowCond("MW/YSUM", condname, lim_ysum[i][0], lim_ysum[i][1], MW_YSUM);
    }*/


    /*** MUSIC Conditions ***/

    cMusic1_E = new Float_t*[8];
    cMusic1_T = new Float_t*[8];
    cMusic2_E = new Float_t*[8];
    cMusic2_T = new Float_t*[8];
    cMusic3_T = new Float_t*[4];
    cMusic3_E = new Float_t*[4];

    cMusic3_dec = new Float_t[2];

    for(int i = 0; i < 8; ++i){


    cMusic1_E[i] = new Float_t[2];
    cMusic1_T[i] = new Float_t[2];
    cMusic2_E[i] = new Float_t[2];
    cMusic2_T[i] = new Float_t[2];

    if(i < 4){
        cMusic3_E[i] = new Float_t[2];
        cMusic3_T[i] = new Float_t[2];
        }
    }


    line_number = 0;

    format = "%f %f %f %f";

     ifstream cond_d("Configuration_Files/FRS/FRS_Window_Conditions/MUSIC1.txt");

    while(/*cond_d.good()*/getline(cond_d,line,'\n')){

    //getline(cond_d,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cMusic1_E[line_number][0],&cMusic1_E[line_number][1],&cMusic1_T[line_number][0],&cMusic1_T[line_number][1]);

    line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

     ifstream cond_e("Configuration_Files/FRS/FRS_Window_Conditions/MUSIC2.txt");

    while(/*cond_e.good()*/getline(cond_e,line,'\n')){

    //getline(cond_e,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cMusic2_E[line_number][0],&cMusic2_E[line_number][1],&cMusic2_T[line_number][0],&cMusic2_T[line_number][1]);

    line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

     ifstream cond_f("Configuration_Files/FRS/FRS_Window_Conditions/MUSIC3.txt");

    while(/*cond_f.good()*/getline(cond_f,line,'\n')){

    //getline(cond_f,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cMusic3_E[line_number][0],&cMusic3_E[line_number][1],&cMusic3_T[line_number][0],&cMusic3_T[line_number][1]);

    line_number++;
    }


    line_number = 0;

    format = "%f %f";

     ifstream cond_g("Configuration_Files/FRS/FRS_Window_Conditions/MUSIC_dEc3.txt");

    while(/*cond_g.good()*/getline(cond_g,line,'\n')){

    //getline(cond_g,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cMusic3_dec[0],&cMusic3_dec[1]);
    }

///DESPEC code doesnt use window conditions for the TPCs (extracts gates directly from FRS setup file - no real difference) A.K.M. 2022
/*
    cTPC_LT0= new Float_t*[7];
    cTPC_RT0= new Float_t*[7];
    cTPC_LT1= new Float_t*[7];
    cTPC_RT1= new Float_t*[7];
    cTPC_DT= new Float_t**[7];
    cTPC_SC_TIMEREF= new Float_t*[8];*/

//     for(int i=0; i<8; i++) cTPC_SC_TIMEREF[i] =  new Float_t[2];
// 
//     for(int i=0; i<7; i++){
//         cTPC_LT0[i] =  new Float_t[2];
//         cTPC_RT0[i] =  new Float_t[2];
//         cTPC_LT1[i] =  new Float_t[2];
//         cTPC_RT1[i] =  new Float_t[2];
// 
//         cTPC_DT[i] =    new Float_t*[4];
//          for(int j=0; j<4; j++)cTPC_DT[i][j]=  new Float_t[2];
//     }


//     for(int i=0; i<8; i++){
//     cTPC_SC_TIMEREF[i][0] = tpc->lim_timeref[i][0];
//     cTPC_SC_TIMEREF[i][1] = tpc->lim_timeref[i][1];
// 
//     }
//     for(int i=0; i<7; i++){
//     cTPC_LT0[i][0] = tpc->lim_lt[i][0][0];
//     cTPC_LT0[i][1] = tpc->lim_lt[i][0][1];
//     cTPC_RT0[i][0] = tpc->lim_rt[i][0][0];
//     cTPC_RT0[i][1] = tpc->lim_rt[i][0][1];
// 
//     cTPC_LT1[i][0] = tpc->lim_lt[i][1][0];
//     cTPC_LT1[i][1] = tpc->lim_lt[i][1][1];
//     cTPC_RT1[i][0] = tpc->lim_rt[i][1][0];
//     cTPC_RT1[i][1] = tpc->lim_rt[i][1][1];
// 
//     for(int j=0; j<4; j++){
//     cTPC_DT[i][j][0] = tpc->lim_dt[i][j][0];
//     cTPC_DT[i][j][1] = tpc->lim_dt[i][j][1];
//         }
//     }

    /***SCINTILATOR Condtions***/

    cSCI_L = new Float_t[2];
    cSCI_R = new Float_t[2];
    cSCI_E = new Float_t[2];
    cSCI_Tx = new Float_t[2];
    cSCI_X = new Float_t[2];


    line_number = 0;

    format = "%f %f";

     ifstream cond_h("Configuration_Files/FRS/FRS_Window_Conditions/SCI_Cons.txt");

    while(/*cond_h.good()*/getline(cond_h,line,'\n')){

    //getline(cond_h,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cSCI_L[0],&cSCI_L[1]);

    getline(cond_h,line,'\n');
        sscanf(line.c_str(),format,&cSCI_R[0],&cSCI_R[1]);

    getline(cond_h,line,'\n');
        sscanf(line.c_str(),format,&cSCI_E[0],&cSCI_E[1]);

    getline(cond_h,line,'\n');
        sscanf(line.c_str(),format,&cSCI_Tx[0],&cSCI_Tx[1]);

    getline(cond_h,line,'\n');
        sscanf(line.c_str(),format,&cSCI_X[0],&cSCI_X[1]);

    }

    cSCI_LL2 = new Float_t[2];
    cSCI_RR2 = new Float_t[2];
    cSCI_LL3 = new Float_t[2];
    cSCI_RR3 = new Float_t[2];
    cSCI_LL4 = new Float_t[2];
    cSCI_RR4 = new Float_t[2];
    cSCI_LL5 = new Float_t[2];
    cSCI_RR5 = new Float_t[2];

    format = "%f %f";

    ifstream cond_i("Configuration_Files/FRS/FRS_Window_Conditions/SCI_LLRR.txt");

    while(/*cond_i.good()*/getline(cond_i,line,'\n')){


    //getline(cond_i,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cSCI_LL2[0],&cSCI_LL2[1]);
    getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR2[0],&cSCI_RR2[1]);

    getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL3[0],&cSCI_LL3[1]);

    getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR3[0],&cSCI_RR3[1]);


    getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL4[0],&cSCI_LL4[1]);

    getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR4[0],&cSCI_RR4[1]);

    getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL5[0],&cSCI_LL5[1]);

    getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR5[0],&cSCI_RR5[1]);

    }

    /***ID Condtions***/

    cID_x2 = new Float_t[2];
    cID_x4 = new Float_t[2];
    cID_Z_Z = new Float_t[2];

    format = "%f %f";

     ifstream cond_k("Configuration_Files/FRS/FRS_Window_Conditions/ID_x2.txt");


    while(/*cond_k.good()*/getline(cond_k,line,'\n')){

    //getline(cond_k,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cID_x2[0],&cID_x2[1]);

    }

     ifstream cond_l("Configuration_Files/FRS/FRS_Window_Conditions/ID_x4.txt");

    while(/*cond_l.good()*/getline(cond_l,line,'\n')){

    //getline(cond_l,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cID_x4[0],&cID_x4[1]);

    }


     ifstream cond_m("Configuration_Files/FRS/FRS_Window_Conditions/ID_Z_Z.txt");

    while(/*cond_m.good()*/getline(cond_m,line,'\n')){

    //getline(cond_m,line,'\n');
    if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cID_Z_Z[0],&cID_Z_Z[1]);

    }

    /*for(int i=0;i<8;i++){

       sprintf(name,"Music1_E(%f)",i);
       cMusic1_E[i] = MakeWindowCond("MUSIC/MUSIC(1)/E",name, 10, 4086, "hMUSIC1_E");

        sprintf(name,"Music1_T(%d)",i);
       cMusic1_T[i] = MakeWindowCond("MUSIC/MUSIC(1)/T",name, 10, 4086,"hMUSIC1_T");

       sprintf(name,"Music2_E(%d)",i);
       cMusic2_E[i] = MakeWindowCond("MUSIC/MUSIC(2)/E",name, 10, 4086, "hMUSIC2_E");

       sprintf(name,"Music2_T(%d)",i);
       cMusic2_T[i] = MakeWindowCond("MUSIC/MUSIC(2)/T",name, 10, 4086, "hMUSIC2_T");
     }

   for(int i=0;i<4;i++){

       sprintf(name,"Music3_E(%d)",i);
       cMusic3_E[i] = MakeWindowCond("MUSIC/MUSIC(3)/E",name, 10, 4086, "hMUSIC3_E");

       sprintf(name,"Music3_T(%d)",i);
       cMusic3_T[i] = MakeWindowCond("MUSIC/MUSIC(3)/T",name, 10, 4086, "hMUSIC3_T");
    }


    cMusic3_dec = MakeWindowCond("MUSIC/MUSIC 3","Music3_dec", 10., 4000., "hMUSIC3_dECOR");*/

}
///--------------------------------------------------------------------------------

void FRS_Detector_System::FRS_GainMatching(){
     ifstream    file;
   string line;
   Float_t frs_wr_a;
   Float_t frs_wr_b;
   Float_t frs_wr_i;
   Float_t frs_wr_j;
   Float_t z1_shift_value;
   Float_t z2_shift_value;
   Float_t aoq_shift_value;
   Float_t aoq_shift_tpc_value;
   Float_t aoq_shift_sci21_value;
   Float_t aoq_shift_sci22_value;
 
   
   int f=0;
   int d=0;
   file.open("Configuration_Files/FRS/Z1_Z2_Shift.txt");
   while(file.good()){
    getline(file,line,'\n');
    if(line[0] == '#') continue;
    sscanf(line.c_str(),"%f %f %f %f",&frs_wr_a,&frs_wr_b,&z1_shift_value,&z2_shift_value);
       //if(IsData(file)) file >> FRS_WR_a[i]>> FRS_WR_b[i]>>Z1_shift_value[i] ;
    FRS_WR_a[f]=frs_wr_a;
    FRS_WR_b[f]=frs_wr_b;
    Z1_shift_value[f]=z1_shift_value;
    Z2_shift_value[f]=z2_shift_value;
    Z_Shift_array=f;
       f++;
       
     }

  file.close();
  ///--------------------------------------------------------------------------------

      file.open("Configuration_Files/FRS/AoQ_Shift.txt");
   while(file.good()){
       
    getline(file,line,'\n');
    if(line[0] == '#') continue;
    sscanf(line.c_str(),"%f %f %f %f %f",&frs_wr_i,&frs_wr_j,&aoq_shift_tpc_value,&aoq_shift_sci21_value,&aoq_shift_sci22_value);

    FRS_WR_i[d]=frs_wr_i;
    
    FRS_WR_j[d]=frs_wr_j;
    AoQ_shift_TPC_value[d]=aoq_shift_tpc_value;
    AoQ_shift_Sci21_value[d]=aoq_shift_sci21_value;
    AoQ_shift_Sci22_value[d]=aoq_shift_sci22_value;
    AoQ_Shift_array=d;
       d++;
       
     }

  file.close();
    
}

#ifdef CALIBRATION_VFTX
void FRS_Detector_System::VFTX_Calibration(int module, int channel) {
    cout<<"!!!!VFTX CALIBRATION!!!"<<endl;
  int l_VFTX_SN[VFTX_N] = VFTX_SN;
  double integral_ft;
  //double integral_tot_ft;
  int    FirstBin_ft;
  double integral [1000];
  double calib[1000];
  for (int bin=1; bin<=1000; bin++) {
    calib[bin-1] = 0. ;
    integral [bin-1] = 0. ;
  }
  std::ofstream f_int;
  std::ofstream f_cal;
  f_cal.open(Form("Configuration_Files/FRS/VFTX_Calib/VFTX_%05d_Bin2Ps_ch%02d.dat",l_VFTX_SN[module],channel),std::ios::out);
  f_int.open(Form("Configuration_Files/FRS/VFTX_Int/VFTX_%05d_INT_ch%02d.txt",l_VFTX_SN[module],channel),std::ios::out);
  // calculation of the integral
  //integral_tot_ft = (double)h1_vftx_ft[module][channel]->Integral();
  integral_ft     = (double)h1_vftx_ft[module][channel]->Integral(5,1000);
  cout<<"integral_ft "<<integral_ft<<" module " << module << " channel " << channel << endl;
  // calculation of the first bin
  FirstBin_ft = 1 ;
  for (int bin=2; bin<=1000; bin++)     {
    if (h1_vftx_ft[module][channel]->GetBinContent(bin)>0) {
      FirstBin_ft = bin;
      break;
    }
  }//end of for(bin)
  // calculation of the calibration parameters
  if(integral_ft>0){
    for (int bin=FirstBin_ft; bin<=1000; bin++) {
      integral[bin-1]  = integral[bin-2]+h1_vftx_ft[module][channel]->GetBinContent(bin);
      calib[bin-1]     = (integral[bin-1]*5000.)/integral_ft ;
    }
  }//end of if spectrum not empty
  //SAVE
  for(int bin=1; bin<=1000;bin++)       {
    f_cal <<std::setw(4) <<bin-1 <<" " <<std::setw(15) <<std::fixed <<std::setprecision(9) <<calib[bin-1]    <<std::endl;
    f_int <<std::setw(4) <<bin-1 <<" " <<std::setw(15) <<std::fixed <<std::setprecision(9) <<integral[bin-1] <<std::endl;
  }
  f_cal.close();
  f_int.close();
  return;
}
#endif

// --- ----------------------------------- --- //
// --- RECONSTRUCT Traw FROM THE VFTX DATA --- //
// --- ----------------------------------- --- //
void FRS_Detector_System::m_VFTX_Bin2Ps(){
  int l_VFTX_SN[VFTX_N]  = VFTX_SN;

  for(int i=0; i<VFTX_N; i++)
    for(int j=0; j<VFTX_MAX_CHN; j++)
      for(int k=0; k<1000; k++)
    VFTX_Bin2Ps[i][j][k]=0.;

  int b; double ft_ps;
  for(int mod=0; mod<VFTX_N; mod++){
    for(int ch=0; ch<VFTX_MAX_CHN; ch++){
      std::ifstream in;
      in.open(Form("Configuration_Files/FRS/VFTX_Calib/VFTX_%05d_Bin2Ps_ch%02d.dat",l_VFTX_SN[mod],ch));
      if(!in.is_open()){
    for(int bin=0; bin<1000; bin++)
      VFTX_Bin2Ps[mod][ch][bin] = 0.; // no data in ps if we don't have the files
    printf("WARNING : VFTX %05d ch %02d file not found, you will not have precise data\n",l_VFTX_SN[mod],ch);
      }
      else {
    while(!in.eof()) {
      in >>b >>ft_ps;
      VFTX_Bin2Ps[mod][ch][b] = ft_ps;
      if(b>1000) printf(" !!! WARNING !!!! file Configuration_Files/VFTX_Calib/VFTX%02d_Bin2Ps_ch%2d.dat, overflow b=%i \n",mod,ch,b);
    }// end of for (ch over VFTX_CHN)
    in.close();
      }
    }//end of for (ch)
  }// end of for (mod over VFTX_N
  return;
}

Double_t FRS_Detector_System::VFTX_GetTraw_ps(int module, int channel, int cc, int ft, float rand) {
  Double_t gain;
  Double_t calib = (Double_t)VFTX_Bin2Ps[module][channel][ft];

  if (calib==0) calib = ft;
  if(rand<0) {
    Double_t calib_prev = (Double_t)VFTX_Bin2Ps[module][channel][ft-1];
    gain = calib - calib_prev;
  }
  else {
    Double_t calib_next = (Double_t)VFTX_Bin2Ps[module][channel][ft+1];
    gain = calib_next - calib;
  }
  double ft_ps = calib + gain*(double)rand ;
  double cc_ps = (double)(cc);
  return (5000.*cc_ps - ft_ps);
}

const char* FRS_Detector_System::get_filename(){
    const char* filename;
    filename = TGo4Analysis::Instance()->GetInputFileName();
    return filename;
}
