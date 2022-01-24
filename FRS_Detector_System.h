
#ifndef FRS_DETECTOR_SYSTEM_H
#define FRS_DETECTOR_SYSTEM_H

#include "FRS_Detector_System.h"

#include "Riostream.h"

#include "TH1.h"
#include "TMap.h"
#include "TObject.h"

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
#include "TGo4AnalysisObjectManager.h"
#include "TGo4EventProcessor.h"
#include "DESPECAnalysis.h"
#include "TFRSParameter.h"
#include "Go4StatusBase/TGo4Parameter.h"

#include "Detector_System.cxx"

#include <sys/stat.h>
#include <sys/types.h>
#include <TRandom3.h>

// This should be discommented only for vftx channel calibration
#define CALIBRATION_VFTX 0

// ID for vftx module
#define VFTX_SN   {11000}

#define VFTX_N  1
#define VFTX_MAX_CHN   32
#define VFTX_MAX_HITS   20

/// Setup of VFTX channels
#define SCI_MOD 0
///SOFIA L
// #define SCI21L_CH 0 ///SCI21 L
// #define SCI21R_CH 2 ///SCI21 R
// #define SCI22L_CH 24 ///SCI22 L
// #define SCI22R_CH 26 ///SCI22 R
// #define SCI41L_CH 4 ///SCI41 L
// #define SCI41R_CH 6 ///SCI41 R
// #define SCI42L_CH 8 ///SCI42 L
// #define SCI42R_CH 10 ///SCI42 R


// #define SCI21L_CH 6 ///SCI21 L //6
// #define SCI21R_CH 7 ///SCI21 R //7
// #define SCI22L_CH 13 ///SCI22 L //13
// #define SCI22R_CH 14 ///SCI22 R //14
// #define SCI41L_CH 8 ///SCI41 L //8
// #define SCI41R_CH 9 ///SCI41 R //9
// #define SCI42L_CH 4 ///SCI42 L //4
// #define SCI42R_CH 5 ///SCI42 R //5

#define SCI21L_CH 5 ///SCI21 L //6
#define SCI21R_CH 6 ///SCI21 R //7
#define SCI22L_CH 12 ///SCI22 L //13
#define SCI22R_CH 13 ///SCI22 R //14
#define SCI41L_CH 7 ///SCI41 L //8
#define SCI41R_CH 8 ///SCI41 R //9
#define SCI42L_CH 3 ///SCI42 L //4
#define SCI42R_CH 4 ///SCI42 R //5

class FRS_Detector_System : public Detector_System{

    public:
    FRS_Detector_System();
   // void  get_params(TGo4Parameter* name);

virtual ~FRS_Detector_System();

    //void Process_FRS(TModParameter* , TGo4MbsSubEvent* , TGo4MbsEvent*){};
    void Process_MBS(TGo4MbsSubEvent* psubevt);
    void Process_MBS_Anl();

    UInt_t Vftx_Stat[VFTX_N][VFTX_MAX_CHN];
     // void VFTX_Calibration();

 // TH1 * h1_vftx_ft[VFTX_N][VFTX_MAX_CHN];
     TH1D  *h1_vftx_ft[1][32] ;
    //void Process_FRS(TGo4MbsSubEvent* psubevt);
  //  TModParameter* ModSetup;
    TMWParameter* mw;
    TTPCParameter* tpc;
    TSIParameter* si;
   // TModParameter* ModPar;

    TMUSICParameter* music;
    TSCIParameter* sci;
    TFRSParameter* frs;
    TIDParameter* id;
    TMRTOFMSParameter* mrtof;

    int            scaler_ch_1kHz=0;
    int            scaler_ch_spillstart=0;
    UInt_t         scaler_initial[64];
    UInt_t         scaler_previous[64];
    int            scaler_check_first_event = 1;

    void Process_MBS(int*){};
    void get_Event_data(Raw_Event*);
    int* get_pdata();

    bool calibration_done(){return false;}
    void write(){return;};
    void set_Gain_Match_Filename(std::string){return;};
    void VFTX_Calibration(int module, int channel);
    const char* get_filename();
//     #if CALIBRATION_VFTX
//   void VFTX_Calibration(int module, int channel);
// #endif

typedef unsigned long long ULong64_t;

private:

    TGo4MbsSubEvent* psubevt;

    Int_t *pdata;
    Int_t len = 0;
    Int_t vme_chn;
    Int_t lenMax;

    Int_t nbins;
    Double_t min_val,max_val;
    Double_t bins_x_arr[1000];
    double VFTX_Cal_arr[1][32][1001];

     //void load_VFTX_Calibration_Files();




    /**************************************************************/
    /***UNPACK STUFF***/


    void FRS_Unpack(TGo4MbsSubEvent* psubevt);
    void Build_FRS_Event(TGo4EventElement* dest);

    void FRS_Timestamp_Module(int);

    void FRS_Scaler_Module(int);

    void FRS_775_TDC_785_ADC_Modules(int);

    void FRS_Rest_Of_Unpacking(int);

    void Clear_all();

    UInt_t vme[6][21][32];         // FRS crate
    UInt_t vme_tpcs2[21][32];// TPC crate (S2 TPC)
    UInt_t vme_tpcs4[21][32];// TPC crate (S4/S3 TPC)
    UInt_t vme_frs[21][32];
    UInt_t vme_main[21][32];
    UInt_t vme_tof[21][32]; // TOF crate
    UInt_t leading_v1190_tpcs2[128][64];         // TPC crate (S2 TPC)
    UInt_t nhit_v1190_tpcs2[128];         // TPC crate (S2 TPC)



    UInt_t vme_trmu_adc[16];              // Travel Music crate
    UInt_t vme_trmu_tdc[16];              // Travel Music crate
    UInt_t vme_trmu_trigger[2];              // Travel Music crate
    UInt_t vme_actstop[21][32];       //active stopper
    //UInt_t*** vme0;         // FRS crate
    //UInt_t*** vme1;         // TPC crate
    //UInt_t*** vme3;         // Mtof crate
    //UInt_t*** vme4 ; // SOFIA crate temp need multiplicity for both MDPP and vftx

    //UInt_t*** vme5;          //Main Crate or User Crate



    Int_t* vme2scaler;         // User Crate Messhure
    Int_t* vme3scaler;         // User Crate Messhure

    //Int_t** vme2s;           // User TDC (V1290)
   // Int_t** vme2s_trailing;  // User TDC (V1290)
    //Int_t** nhit5;            // multiplicity (V1290)

    //Int_t** vme3s_MT;           // Mtof TDC (V1290)
   // Int_t** vme3s_MT_trailing;  // Mtof TDC (V1290)
    //Int_t** vme3_MT_nhit5;       // multiplicity (V1290)

    // UInt_t vme_main[21][32];          // Main crate
  ULong64_t timestamp_main[32];        // Time stamp in main crate
  UInt_t scaler_main[32];           // VME scaler in main crate
  UInt_t nhit_v1290_main[32][2];    // multi-hit TDC in main crate [ch][leading or trailing]
  UInt_t leading_v1290_main[32][10];     // leading timing V1290 in main crate
  UInt_t trailing_v1290_main[32][10];    // trailing timing V1290 in main crate
  UInt_t tpat_main[32];
  UInt_t scaler_frs[32];            // VME scaler in frs crate

  UShort_t vftx_cc[VFTX_N][VFTX_MAX_CHN][VFTX_MAX_HITS];
  UShort_t vftx_ft[VFTX_N][VFTX_MAX_CHN][VFTX_MAX_HITS];
  UShort_t vftx_mult[VFTX_N][VFTX_MAX_CHN];

  Int_t Proc_iterator;
   bool skip;


    int tmp_nhit_prev;

    //bool* firstTS;
   // Long64_t* previousTimeStamp;
    //Long64_t currentTimeStamp;

    //Int_t EventFlag;

    Int_t         qlength;         /* From event header     */
    Int_t         qtype;           /*                       */
    Int_t         qsubtype;        /*                       */
    Int_t         qdummy;          /*                       */
    Int_t         qtrigger;        /*                       */
    Int_t         qevent_nr;       /*                       */

    // special nurdlib
    Int_t              utpat;  //! //This is to pass down the line
    Int_t              uphystrig; //! // to have something else than TPC
    Int_t              unbtrig; //! // number of triggers in utpat
    Int_t              umaxtrig; //! // second trigger in utpat

//Phystrig is build based on tpat, but trigger priority first tpat
//trigger box, sc41..... etc.


    /*******************************************************************/
    /***SORT STUFF***/

    void FRS_Sort();

  /* *************************************** */
  /*         VFTX : RAW TIME IN PS           */
  /* *************************************** */
  TRandom3 rand;
  void   m_VFTX_Bin2Ps();
  float  VFTX_Bin2Ps[VFTX_N][VFTX_MAX_CHN][1000];
  double VFTX_GetTraw_ps(int, int, int, int, float);

    Long64_t StartOfSpilTime;
    Long64_t StartOfSpilTime2; //does not reset at end of extraction
    Long64_t PreviousTS;

    Int_t counter;

     void v1190_channel_init();
     Int_t v1190_channel_dt[7][4];
     Int_t v1190_channel_lt[7][2];
     Int_t v1190_channel_rt[7][2];
     Int_t v1190_channel_timeref[8];
     Int_t v1190_channel_calibgrid[7];

    // time stamp data
    Int_t         ts_id;
    ULong64_t     ts_word[4]; //for the titris time stammping
    Int_t         tsys_word[3]; //for the system time
    Long64_t      timestamp;  // absolute time stamp value
    Double_t      timespill;  // relative time from start of the spill
    Double_t      timespill2;  // relative time from start of the spill does not reset at end extraction
    Double_t      systemtime_ms;
    Double_t      systemtime_s;

    Int_t         pattern;
    Int_t         trigger;
    Int_t         sptrigger;
    Int_t         snbtrig;
    Int_t         smaxtrig ;

    // scaler readings
    UInt_t sc_long[64]; //changed from 32 to 64 (10.07.2018)
    //UInt_t* sc_long2;


    // SEETRAM calib IC energy
    //      Int_t         ic_de;           /*                          */


    // part of MW parameter
//     Int_t*         mw_an;       /*  anode time              */
//     Int_t*         mw_xl;       /*  Rohdaten                */
//     Int_t*         mw_xr;       /*                          */
//     Int_t*         mw_yu;       /*                          */
//     Int_t*         mw_yd;       /*                          */

    // TPC part //(HAPOL-25/03/06) 6 TPCs each one with 2 delay lines each!!
    //7 TPCs (4 at S2, 2 at S4 and one at S3) 03.07.2018 SB
//     Int_t** tpc_l;
//     Int_t** tpc_r;
//     Int_t** tpc_lt;
//     Int_t** tpc_rt;
//     Int_t* tpc_timeref;

    // [index][anode_no]
//     Int_t** tpc_dt;


//     Int_t tpc_l[7][2]; //[i_tpc][i_delayline_L]
//     Int_t tpc_r[7][2]; //[i_tpc][i_delayline_R]
//     Int_t tpc_a[7][4]; //[i_tpc][i_anode]

    Int_t** tpc_l; //[i_tpc][i_delayline_L]
    Int_t** tpc_r; //[i_tpc][i_delayline_R]
    Int_t** tpc_a; //[i_tpc][i_anode]

//     Int_t tpc_lt[7][2][64];//multihit up to 16
//     Int_t tpc_rt[7][2][64];//multihit up to 16
    Int_t*** tpc_lt;//multihit up to 16
    Int_t*** tpc_rt;//multihit up to 16
    Int_t*** tpc_dt;//multihit up to 16
//     Int_t tpc_dt[7][4][64];//multihit up to 16
    Int_t tpc_nhit_lt[7][2];//multihit number
    Int_t tpc_nhit_rt[7][2];//multihit number
    Int_t tpc_nhit_dt[7][4];//multihit number

    Int_t tpc_calibgrid[7][64];//multihit up to 16
    Int_t tpc_timeref[8][64];//multihit up to 16
    Int_t tpc_nhit_calibgrid[7];//multihit number
    Int_t tpc_nhit_timeref[8];//multihit number

    // SCI part
    Int_t         de_21l;          /* dE SCI21 left            */
    Int_t         de_21r;          /* de SCI21 right           */
    Int_t         de_41l;          /* dE SCI41 left            */
    Int_t         de_41r;          /* dE SCI41 right           */
    Int_t         de_41u;          /* dE SCI41 up              */
    Int_t         de_41d;          /* dE SCI41 down            */
    Int_t         de_42l;          /* de SCI42 left            */
    Int_t         de_42r;          /* de SCI42 right           */
    Int_t         de_43l;          /* de SCI43 left            */
    Int_t         de_43r;          /* de SCI43 right           */
    Int_t         de_81l;          /* de SCI81 left            */
    Int_t         de_81r;          /* de SCI81 right           */
    Int_t         de_31l;          /* de SCI31 left            */
    Int_t         de_31r;          /* de SCI31 right           */
    Int_t         de_22l;
    Int_t         de_22r;
    Int_t         dt_21l_21r;      /*                          */
    Int_t         dt_41l_41r;      /*                          */
    Int_t         dt_21l_41l;      /*                          */
    Int_t         dt_21r_41r;      /*                          */
    Int_t         dt_42l_42r;      /*                          */
    Int_t         dt_43l_43r;      /*                          */
    Int_t         dt_42l_21l;      /*                          */
    Int_t         dt_42r_21r;      /*                          */
    Int_t         dt_41u_41d;      /*                          */
    Int_t         dt_81l_81r;
    Int_t         dt_21l_81l;
    Int_t         dt_21r_81r;
    Int_t         dt_22l_22r;
    Int_t         dt_22l_41l;
    Int_t         dt_22r_41r;
    Int_t         dt_22l_81l;
    Int_t         dt_22r_81r;


    // VFTX for new ToF
    Double_t TRaw_vftx_21l;
    Double_t TRaw_vftx_21r;
    Double_t TRaw_vftx_22l;
    Double_t TRaw_vftx_22r;
    Double_t TRaw_vftx_41l;
    Double_t TRaw_vftx_41r;
    Double_t TRaw_vftx_42l;
    Double_t TRaw_vftx_42r;
    Double_t TRaw_vftx_sofia_l;
    Double_t TRaw_vftx_sofia_r;
    Double_t TRaw_vftx[32];

    // User multihit TDC

    Int_t tdc_sc41l[10];
    Int_t tdc_sc41r[10];
    Int_t tdc_sc21l[10];
    Int_t tdc_sc21r[10];
    Int_t tdc_sc42l[10];
    Int_t tdc_sc42r[10];
    Int_t tdc_sc43l[10];
    Int_t tdc_sc43r[10];
    Int_t tdc_sc81l[10];
    Int_t tdc_sc81r[10];
    Int_t tdc_sc31l[10];
    Int_t tdc_sc31r[10];
    Int_t tdc_sc11[10];
    Int_t tdc_sc22l[10];
    Int_t tdc_sc22r[10];

    // MUSIC1 part
    Int_t*         music_e1;     /* Raw energy signals       */
    Int_t*         music_t1;     /* Raw drift time           */
   // Int_t*         music_pres;   /* Music Druck              */
 //   Int_t*         music_temp;   /* Music Temperatur         */

    // MUSIC2 part
    Int_t*         music_e2;     /* Raw energy signals       */
    Int_t*         music_t2;     /* Raw drift time           */

    // MUSIC3 part (OLD MUSIC)
    Int_t*         music_e3;     /* Raw energy signals       */
    Int_t*        music_t3;     /* Raw drift times          */
    
     int Z_Shift_array;
      Float_t FRS_WR_a[200];
      Float_t FRS_WR_b[200];
      Float_t Z1_shift_value[200];
      Float_t Z2_shift_value[200];
        // FRS_AoQ_shifted;
      int AoQ_Shift_array;
      Float_t FRS_WR_i[200];
      Float_t FRS_WR_j[200];
      Float_t AoQ_shift_value[200];
      Float_t AoQ_shift_TPC_value[200];
      Float_t AoQ_shift_Sci21_value[200];
      Float_t AoQ_shift_Sci22_value[200];
      
//         Float_t FRS_WR_a[200];
//    Float_t FRS_WR_b[200];
//    Float_t Z1_shift_value[200];
//    Float_t Z2_shift_value[200];
//    int Z_Shift_array;
//    Float_t AoQ_shift_TPC_value[200];
//    Float_t AoQ_shift_Sci21_value[200];
//    Float_t AoQ_shift_Sci22_value[200];
//    Float_t FRS_WR_i[200];
//    Float_t FRS_WR_j[200];
//    int AoQ_Shift_array;

    /*******************************************************************/
    /***CALIBRATION STUFF***/

    void FRS_Calib();

    Float_t*** lim_csum;

    Float_t** lim_xsum;
    Float_t** lim_ysum;

    /*Float_t lim_csum[4][7][2] = {{{300,1800},{350,1800},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}},
				 {{300,1800},{300,1800},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}},
				 {{300,1800},{300,1840},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}},
				 {{300,1800},{300,1810},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}}}*///;


    //lim_csum[0][7][2] = {{300,1800},{350,1800},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}};
    //lim_csum[1][7][2] = {{300,1800},{300,1800},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}};
    //lim_csum[2][7][2] = {{300,1800},{300,1840},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}};
    //lim_csum[3][7][2] = {{300,1800},{300,1810},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}};


    //Float_t lim_csum2[7][2]={{300,1800},{300,1800},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}};
    //Float_t lim_csum3[7][2]={{300,1800},{300,1840},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}};
    //Float_t lim_csum4[7][2]={{300,1880},{300,1810},{300,1800},{300,1700},{300,2000},{300,2000},{300,2000}};

    /*Float_t lim_xsum[13][2] = {	{1,8000},  // MW11
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

    Float_t lim_ysum[13][2] = { {2,8000},  // MW11
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


    // MON data declarations

    //int* check_first_event;
//     int scaler_channel_10khz;//YT 20Jun
//     Long64_t*  scaler_time_count;
//     Long64_t*  scaler_spill_count; //UInt_t
//     Long64_t*  scaler_time_check_last;//UInt_t
//     Long64_t*  scaler_spill_check_last;//UInt_t
//     Long64_t*  check_increase_time;//UInt_t
//     Long64_t*  check_increase_spill;//UInt_t
//     Long64_t*  scaler_increase_event;//UInt_t
//     Long64_t*  scaler_last_event;


//     TGo4WinCond   *cMW_XSUM[13];
//     TGo4WinCond   *cMW_YSUM[13];
// 
//     ////condtition for control sum
//     TGo4WinCond *cTPC_CSUM[7][4];
//     TGo4PolyCond *cTPC_XY[7];

//     UInt_t freeTrig;
//     UInt_t acptTrig;

    Int_t         extraction_time_ms;

    Float_t       focx_s2;         /*  FRS foci                */
    Float_t       focy_s2;         /*                          */
    Float_t       focx_s4;         /*                          */
    Float_t       focy_s4;         /*                          */
    Float_t       focx_s8;         /*  FRS foci                */
    Float_t       focy_s8;         /*                          */
    Float_t       angle_x_s2;      /*                          */
    Float_t       angle_y_s2;      /*                          */
    Float_t       angle_x_s4;      /*                          */
    Float_t       angle_y_s4;      /*                          */
    Float_t       angle_x_s8;      /*                          */
    Float_t       angle_y_s8;      /*                          */

    // TPC part
//     Int_t** tpc_csum;
//     Float_t* tpc_x;
//     Float_t* tpc_y;
//     Bool_t** b_tpc_csum;
//     Bool_t* b_tpc_xy;
//     Float_t* tpc_de;
//     Bool_t* b_tpc_de;

    Int_t tpc_lt_s[7][2];
    Int_t tpc_rt_s[7][2];
    Int_t tpc_xraw[7][2];
    Int_t tpc_dt_s[7][4];//selected from multihit
    Int_t tpc_yraw[7][4];
    Int_t tpc_csum[7][4];
    Float_t tpc_x[7];
    Float_t tpc_y[7];
    Bool_t b_tpc_csum[7][4];
    Bool_t b_tpc_xy[7];
    Float_t tpc_de[7];
    Float_t tpc_dx12[7];
    Bool_t b_tpc_de[7];
    //timeref
    Bool_t b_tpc_timeref[8];
    Int_t tpc_timeref_s[8];

    //TPCs 21 & 22 @ S2 focus
    Float_t tpc_x_s2_foc_21_22;
    Float_t tpc_y_s2_foc_21_22;
    Float_t tpc_angle_x_s2_foc_21_22;
    Float_t tpc_angle_y_s2_foc_21_22;

    //TPCs 23 & 24 @ S2 focus
    Float_t tpc_x_s2_foc_23_24;
    Float_t tpc_y_s2_foc_23_24;
    Float_t tpc_angle_x_s2_foc_23_24;
    Float_t tpc_angle_y_s2_foc_23_24;

    //TPCs 22 & 24 @ S2 focus
    Float_t tpc_x_s2_foc_22_24;
    Float_t tpc_y_s2_foc_22_24;
    Float_t tpc_angle_x_s2_foc_22_24;
    Float_t tpc_angle_y_s2_foc_22_24;

    //TPCs 3 & 4 @ S2 focus (old tracking)
    Float_t tpc_x_s2_foc;
    Float_t tpc_y_s2_foc;
    Float_t tpc_angle_x_s2_foc;
    Float_t tpc_angle_y_s2_foc;

    //TPCs 41 & 42 @ s4 focus
    Float_t tpc_x_s4;
    Float_t tpc_y_s4;
    Float_t tpc_angle_x_s4;
    Float_t tpc_angle_y_s4;

    //TPCs 5 & 6 @ S4 OTPC (exp s388)
    Float_t tpc_x_s4_target2;
    Float_t tpc_y_s4_target2;

  Float_t       tpc21_22_sc21_x;      /* SC21 x                    */
  Float_t       tpc21_22_sc21_y;    /* SC21 y                    */
  Float_t       tpc23_24_sc21_x;      /* SC21 x                    */
  Float_t       tpc23_24_sc21_y;    /* SC21 y                    */
  Float_t       tpc22_24_sc21_x;      /* SC21 x                    */
  Float_t       tpc22_24_sc21_y;    /* SC21 y                    */

  Float_t       tpc21_22_sc22_x;     /* SC22 x                    */
  Float_t       tpc21_22_sc22_y;     /* SC22 y                    */
  Float_t       tpc23_24_sc22_x;      /* SC22 x                    */
  Float_t       tpc23_24_sc22_y;      /* SC22 x                    */
  Float_t       tpc22_24_sc22_x;     /* SC22 x                    */
  Float_t       tpc22_24_sc22_y;     /* SC22 x                    */

  Float_t       tpc21_22_s2target_x;      /* S2TARGET x                    */
  Float_t       tpc21_22_s2target_y;    /* S2TARGET y                    */
  Float_t       tpc23_24_s2target_x;      /* S2TARGET x                    */
  Float_t       tpc23_24_s2target_y;    /* S2TARGET y                    */
  Float_t       tpc22_24_s2target_x;      /* S2TARGET x                    */
  Float_t       tpc22_24_s2target_y;    /* S2TARGET y                    */
    //TPCs 3 & 4 @ S2 first Si tracking detector (exp s388)
    Float_t tpc_x_s2_target1;
    Float_t tpc_y_s2_target1;
    //      Float_t tpc_angle_x_s4_target2;
    //      Float_t tpc_angle_y_s4_target2;


  Float_t       tpc_sc41_x;      /* SC41 x                    */
  Float_t       tpc_sc41_y;      /* SC41 y                    */
  Float_t       tpc_sc42_x;      /* SC42 x                    */
  Float_t       tpc_sc42_y;      /* SC42 y                    */
  Float_t       tpc_sc43_x;      /* SC43 x                    */
  Float_t       tpc_sc43_y;      /* SC43 y                    */
  Float_t       tpc_music41_x;      /* MUSIC41 x                    */
  Float_t       tpc_music41_y;      /* MUSIC41 y                    */
  Float_t       tpc_music42_x;      /* MUSIC42 x                    */
  Float_t       tpc_music42_y;      /* MUSIC42 y                    */
  Float_t       tpc_music43_x;      /* MUSIC43 x                    */
  Float_t       tpc_music43_y;      /* MUSIC43 y                    */
  Float_t       tpc_s4target_x;      /* S4 target x                    */
  Float_t       tpc_s4target_y;      /* S4 target y                    */

    Float_t       music1_x1;       /* parameters to calibrate  */
    Float_t       music1_x2;       /* parameters to calibrate  */
    Float_t       music1_x3;       /* parameters to calibrate  */
    Float_t       music1_x4;       /* parameters to calibrate  */
    Float_t       music1_y1;       /* parameters to calibrate  */
    Float_t       music1_y2;       /* parameters to calibrate  */
    Float_t       music1_y3;       /* parameters to calibrate  */
    Float_t       music1_y4;       /* parameters to calibrate  */
    Float_t       music2_x;        /* MUSIC1,2 positions       */

    /*******************************************************************/
    /***ANALYSIS STUFF***/

    void FRS_Anl();

    Float_t**  cMusic1_E;
    Float_t**  cMusic1_T;
    Float_t**  cMusic2_E;
    Float_t**  cMusic2_T;
    Float_t**  cMusic3_T;
    Float_t**  cMusic3_E;

    Float_t*  cMusic3_dec;

    Float_t*  cSCI_L;
    Float_t*  cSCI_R;
    Float_t*  cSCI_E;
    Float_t*  cSCI_Tx;
    Float_t*  cSCI_X;
    
//     Float_t** cTPC_SC_TIMEREF;
//     Float_t** cTPC_LT0;
//     Float_t** cTPC_RT0;
//     Float_t** cTPC_LT1;
//     Float_t** cTPC_RT1;
//     Float_t*** cTPC_DT;
    Float_t*  cSCI_LL2;
    Float_t*  cSCI_RR2;
    Float_t*  cSCI_LL3;
    Float_t*  cSCI_RR3;
    Float_t*  cSCI_LL4;
    Float_t*  cSCI_RR4;
    Float_t*  cSCI_RR5;
    Float_t*  cSCI_LL5;

   // Float_t**  cSCI_detof;

    Float_t*  cID_x2;
    Float_t*  cID_x4;
    Float_t*  cID_Z_Z;
    //Float_t*  cID_x8;
   // Float_t** cID_dEToF;

  //  Float_t** cID_x4AoQ_Z;

//     Float_t*** cID_x2AoQ;
//     Float_t*** cID_x4AoQ;
//     Float_t*** cID_Z_AoQ;

    Float_t rand3(void);
    TRandom3 random3;

      /*sprintf(name, "cSCI%s_L", count_title1[index]);
      cSCI_L[index] = MakeWindowCond(fname,name, 10, 4000, hSCI_L[index]->GetName());

      sprintf(name, "cSCI%s_R", count_title1[index]);
      cSCI_R[index] = MakeWindowCond(fname,name, 10, 4000, hSCI_R[index]->GetName());

      sprintf(name, "cSCI%s_E", count_title1[index]);
      cSCI_E[index] = MakeWindowCond(fname,name, 10, 4000, hSCI_E[index]->GetName());

      sprintf(name, "cSCI%s_Tx", count_title1[index]);
      cSCI_Tx[index] = MakeWindowCond(fname,name,200,4000, hSCI_Tx[index]->GetName());

      sprintf(name, "cSCI%s_X", count_title1[index]);
      cSCI_X[index] = MakeWindowCond(fname,name,-100,100, hSCI_X[index]->GetName());*/


    /*TGo4WinCond   *cID_x2;
    TGo4WinCond   *cID_x4;
    TGo4PolyCond  *cID_dEToF;
    TGo4PolyCond  *cID_x2AoQ[6];
    TGo4PolyCond  *cID_Z_AoQ[5];
    TGo4PolyCond  *cID_x4AoQ_Z[5];
    TGo4WinCond   *cID_Z_Z[5];

    TGo4PolyCond  *cMUSIC_13;

    TGo4WinCond   *cSCI_L[12];
    TGo4WinCond   *cSCI_R[12];
    TGo4WinCond   *cSCI_E[12];
    TGo4WinCond   *cSCI_Tx[12];
    TGo4WinCond   *cSCI_X[12];

    TGo4WinCond   *cSCI_TofLL2;
    TGo4WinCond   *cSCI_TofRR2;
    TGo4WinCond   *cSCI_TofLL3;
    TGo4WinCond   *cSCI_TofRR3;
    TGo4WinCond   *cSCI_TofLL4;
    TGo4WinCond   *cSCI_TofRR4;

    TGo4PolyCond  *cSCI_detof;*/
    Int_t PrcID;
    Int_t SubIterator;
    // MUSIC part
	Int_t         music1_anodes_cnt;
	Int_t         music2_anodes_cnt;
	Int_t         music3_anodes_cnt;
	Bool_t*       music_b_e1;
	Bool_t*       music_b_t1;
	Bool_t*       music_b_e2;
	Bool_t*       music_b_t2;
	Bool_t*       music_b_e3;
	Bool_t*       music_b_t3;
    Float_t       music1_x_mean;
    Float_t       music2_x_mean ;
    Float_t       music3_x_mean ;

	Bool_t        b_de1;
	Bool_t        b_de2;
	Bool_t        b_de3;
	Float_t*      de;
	Float_t*      de_cor;
	Bool_t        b_dt3;
	Float_t       x1_mean;
    //SCI part
	Float_t*      sci_l;
	Float_t*      sci_r;
	Float_t*      sci_e;
	Float_t*      sci_tx;
	Float_t*      sci_x;
	Float_t       sci_tofll2;
	Float_t       sci_tofrr2;
	Float_t       sci_tof2;
    Float_t       sci_tof2_calib;
	Float_t       sci_tofll3;
	Float_t       sci_tofrr3;
	Float_t       sci_tof3;
    Float_t       sci_tof3_calib;
	Float_t       sci_tofll4;
	Float_t       sci_tofrr4;
	Float_t       sci_tof4;
    Float_t       sci_tof4_calib;
    Float_t       sci_tofll5;
    Float_t       sci_tofrr5;
    Float_t       sci_tof5;
    Float_t       sci_tof5_calib;

	Bool_t*       sci_b_l;
	Bool_t*       sci_b_r;
	Bool_t*       sci_b_e;
	Bool_t*       sci_b_tx;
	Bool_t*       sci_b_x;
	Bool_t        sci_b_u5, sci_b_d5;
	Bool_t        sci_b_ty5;
	Bool_t        sci_b_y5;
	Bool_t        sci_b_tofll2;
	Bool_t        sci_b_tofrr2;
	Bool_t        sci_b_tofll3;
	Bool_t        sci_b_tofrr3;
	Bool_t        sci_b_tofll4;
	Bool_t        sci_b_tofrr4;
    Bool_t        sci_b_tofll5;
    Bool_t        sci_b_tofrr5;

     // MultiHitTDC
  Float_t       mhtdc_tof8121;
  Float_t*      mhtdc_tof4121;
  Float_t       mhtdc_tof4221;
  Float_t*      mhtdc_tof4122;
  Float_t       mhtdc_tof4321;
  Float_t       mhtdc_tof3121;


  Float_t*      mhtdc_sc21lr_dt;
  Float_t*      mhtdc_sc22lr_dt;
  Float_t       mhtdc_sc31lr_dt;
  Float_t       mhtdc_sc41lr_dt;
  Float_t       mhtdc_sc42lr_dt;
  Float_t       mhtdc_sc43lr_dt;
  Float_t       mhtdc_sc81lr_dt;

  Float_t*      mhtdc_sc21lr_x;
  Float_t*      mhtdc_sc22lr_x;
  Float_t       mhtdc_sc31lr_x;
  Float_t       mhtdc_sc41lr_x;
  Float_t       mhtdc_sc42lr_x;
  Float_t       mhtdc_sc43lr_x;
  Float_t       mhtdc_sc81lr_x;
    // ID part

	Float_t       id_x2;
	Float_t       id_y2;
	Float_t       id_a2;
	Float_t       id_b2;
	Float_t       id_x4;
	Float_t       id_y4;
	Float_t       id_a4;
	Float_t       id_b4;
	Float_t       id_x8;
	Float_t       id_y8;
	Float_t       id_a8;
	Float_t       id_b8;

	Bool_t        id_b_x2;
	Bool_t        id_b_x4;

	Float_t       id_brho[2];      /* position-corr. BRho      */
	Float_t       id_rho[2];       /* Position-corrected Rho   */

	Float_t       id_beta;        /* Beta from TOF            */
	Float_t       id_beta3;        /* Beta from TOF            */
	Float_t       id_gamma;       /* Gamma from TOF           */
	Float_t       id_AoQ;
	Float_t       id_AoQ_corr;

	Float_t       id_v_cor;       /* Velocity correction  */
	Float_t       id_v_cor2;      /* Velocity correction TUM 2 */
	Float_t       id_v_cor3;      /* Velocity correction Old Music */
	Float_t       id_z;
	Float_t       id_z2;
	Float_t       id_z3;

    Float_t       id_de_s2tpc;
    Bool_t        id_b_de_s2tpc;
    Float_t       id_z_sc81;
    Float_t       id_v_cor_sc81;
    Float_t       id_b_z_sc81;
    Float_t       id_z_s2tpc;
    Float_t       id_v_cor_s2tpc;
    Float_t       id_b_z_s2tpc;
    Float_t       id_gamma_ta_s2;//highZ analysis
    Float_t       id_dEdegoQ;
    Float_t       id_dEdeg;
    Float_t       id_dEdegBeta;
	
	//Int_t         id_trigger;
// 	Int_t         id_scal_seconds;
// 	Int_t         id_scal_geL;
// 	Int_t         id_scal_sc21;
// 	Int_t         id_scal_sc41;
// 	Int_t         id_scal_sc42;
// 	Int_t         id_scal_sc43;
// 	Int_t         id_scal_sc81;

	Bool_t        id_b_AoQ;
    //Bool_t        id_b_AoQ_s2s8;
	Bool_t        id_b_z;
	Bool_t        id_b_z2;
	Bool_t        id_b_z3;
// 	Bool_t*       id_b_x2AoQ;
//     Bool_t*       id_b_x4AoQ;
// 	Bool_t*       id_b_x4AoQ_Z;
// 	Bool_t*       id_b_z_AoQ;
// 	Bool_t*       id_b_music_z;

  Float_t*       id_mhtdc_beta_s2s4;
  Float_t*       id_mhtdc_gamma_s2s4;
  Float_t*       id_mhtdc_delta_s2s4;
  Float_t*       id_mhtdc_aoq_s2s4;
  Float_t*       id_mhtdc_aoq_corr_s2s4;
  Float_t*       id_mhtdc_z_music41;
  Float_t*       id_mhtdc_zcor_music41;
  Float_t*       id_mhtdc_v_cor_music41;
  Float_t*       id_mhtdc_z_music42;
  Float_t*       id_mhtdc_zcor_music42;
  Float_t*       id_mhtdc_v_cor_music42;
  Float_t       id_mhtdc_dEdegoQ[10];
  Float_t       id_mhtdc_gamma_ta_s2[10];
  Float_t       mhtdc_gamma1square[10];
  Float_t       id_mhtdc_dEdeg[10];

// 	Long64_t      firsttimestamp;
// 	Bool_t        firstevent;

	Double_t      ts;  // relative time from start of the spill
	Double_t      ts2;  // relative time from start of the spill does not reset at end extraction

	Int_t time_in_ms;
    Int_t spill_count;
    Int_t ibin_for_s;
    Int_t ibin_for_100ms;
    Int_t ibin_for_spill;
    Int_t ibin_clean_for_s;
    Int_t ibin_clean_for_100ms;
    Int_t ibin_clean_for_spill;
	UInt_t increase_scaler_temp[64];
    
    
   

	string setup_directory_name; //Read from  Setup File

	bool FRS_File_Setup; // Read from Setup File

    void read_config_variables(string config_filename);

    void read_setup_variables_from_file(); // Reads parameters from Setup Files

    void Setup_Parameters();

    void Write_Setup_Parameters();

    Int_t getbits(Int_t, int, int, int);

    Int_t get2bits(Int_t, int, int, int);



    Bool_t Check_WinCond(Float_t P, Float_t* V);
    Bool_t Check_WinCond_Multi(Float_t P, Float_t** V, int cond_num);
    Bool_t Check_WinCond_Multi_Multi(Float_t P, Float_t*** V, int cond_num, int cond_num_2);

    Bool_t Check_PolyCond(Float_t* P, Float_t** V, int n );
    Bool_t Check_PolyCond_X_Y(Float_t X, Float_t Y, Float_t** V, int n );

    Bool_t Check_PolyCond_Multi(Float_t* P, Float_t*** V, int n, int cond_num );
    Bool_t Check_PolyCond_Multi_X_Y(Float_t X, Float_t Y, Float_t*** V, int n, int cond_num);

    void Setup_Conditions();
    void FRS_GainMatching();
 
    ///Shift WR to FRS branch
    Int_t WR_Check(int ts_minutes);
    Int_t ts_mins;
    unsigned long next_ts_for_update() {return 1;};
    bool do_gain_matching(int ts_ns) {WR_Check(ts_ns); return 1;};
    //bool do_gain_matching(int ts_ns) { return 1;};

};



#endif
