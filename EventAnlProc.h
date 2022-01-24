// $Id: EventAnlProc.h 755 2011-05-20 08:04:11Z linev $
// Adapted for DESPEC by A.K.Mistry 2020
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum f�r Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

#ifndef EVENTANLPROCESSOR_H
#define EVENTANLPROCESSOR_H

#include "TGo4EventProcessor.h"

#include "EventUnpackStore.h"
#include "EventAnlStore.h"
#include "CalibParameter.h"
#include "CorrelParameter.h"
#include "AIDA_Headers.h"
#include "AIDA_Event.h"
#include "AIDA_Data_Types.h"
#include "TCutG.h"
#include "TGraph.h"
#include "Go4ConditionsBase/TGo4WinCond.h"
#include "Go4ConditionsBase/TGo4PolyCond.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"
#include "TFRSParameter.h"

//These are for TAMEX
#define CYCLE_TIME  (Double_t) 5000
#define COARSE_CT_RANGE  0x800  // 11 bits

// Uncomment this to align the AIDA ASICs with a pulser
//  Only needed if the ASICs didn't align properly
//#define AIDA_PULSER_ALIGN

class EventAnlStore;


class EventAnlProc : public TGo4EventProcessor {
   public:
      EventAnlProc();
      EventAnlProc(const char * name);
      virtual ~EventAnlProc();
      CalibParameter *fCal;
      CorrelParameter *fCorrel;
     // AidaAnlData    pAida;

      virtual Bool_t BuildEvent(TGo4EventElement* dest);
      virtual void UserPostLoop();
      TIDParameter* frs_id;


      void get_used_systems();
    void Fat_TimeCorrection(EventUnpackStore* pInput);
      long long lastFatWR = 0;
	  long long lastFatTAMWR = 0;
	  long long lastGeWR = 0;
      long long lastbPlastWR = 0;
      long long lastFRSWR = 0;

        //double lead_lead_bplas[48][100], trail_trail_bplas[48][100];
      //  double lead_lead_fat[48][100];

        double ToT_bplas[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS] ;
        double lead_bplas[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS] ;
        double trail_bplas[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS] ;
        //double lead_lead_bplas_gated[48][100];
        double lead_lead_bplas_Ref1[bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
        double lead_lead_bplas_Ref2[bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
        double lead_lead_bplas_Ref3[bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];


        double lead_fast_fat[FATIMA_TAMEX_CHANNELS+1][FATIMA_TAMEX_HITS], trail_fast_fat[FATIMA_TAMEX_CHANNELS+1][FATIMA_TAMEX_HITS];
        double lead_slow_fat[FATIMA_TAMEX_CHANNELS+1][FATIMA_TAMEX_HITS], trail_slow_fat[FATIMA_TAMEX_CHANNELS+1][FATIMA_TAMEX_HITS];
        double lead_lead_slow_fat_Ref1[FATIMA_TAMEX_CHANNELS+1][FATIMA_TAMEX_HITS];
        double lead_lead_fast_fat_Ref1[FATIMA_TAMEX_CHANNELS+1][FATIMA_TAMEX_HITS];
        double ToT_fast_fat[FATIMA_TAMEX_CHANNELS+1][FATIMA_TAMEX_HITS];
        double ToT_slow_fat[FATIMA_TAMEX_CHANNELS+1][FATIMA_TAMEX_HITS];
        double ToT_slow_fat_calib[FATIMA_TAMEX_CHANNELS+1][FATIMA_TAMEX_HITS];
        double FatTam_Fast_RefCh0[FATIMA_TAMEX_HITS];
        double FatTam_Slow_RefCh0[FATIMA_TAMEX_HITS];
        double SC41L_ANA_lead_fat[FATIMA_TAMEX_HITS], SC41R_ANA_lead_fat[FATIMA_TAMEX_HITS];
        double SC41L_DIG_lead_fat[FATIMA_TAMEX_HITS], SC41R_DIG_lead_fat[FATIMA_TAMEX_HITS];
        double bPlasDet1_coin_lead_Fat[FATIMA_TAMEX_HITS], bPlasDet2_coin_lead_Fat[FATIMA_TAMEX_HITS] ;
        int hits_fat_lead, hits_fat_trail;
        int Fat_tot_hits[FATIMA_TAMEX_CHANNELS+1];

        double bPlas_fatimatamex_dT[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS], bPlas_fatimavme_dT[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
        double SC41L_ANA_lead_bPlas[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS], SC41R_ANA_lead_bPlas[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
        double SC41L_DIG_lead_bPlas[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS], SC41R_DIG_lead_bPlas[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
        double lead_lead_fat_Ref0[bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
        int hits_bplas_lead = 0, hits_bplas_trail=0;
        int hits_bplas_lead_fast = 0, hits_bplas_trail_fast=0;
        int hits_bplas_lead_slow = 0, hits_bplas_trail_slow=0;
        
        double ToT_bplas_Fast[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS] ;
        double ToT_bplas_Slow[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS] ;
        double lead_bplas_fast[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS] ;
        double lead_bplas_slow[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS] ;
        double trail_bplas_fast[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS] ;
        double trail_bplas_slow[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS] ;


        double bPlas_TAM_SC41L_ANA;
        double bPlas_TAM_SC41R_ANA;
        double bPlas_TAM_SC41L_DIG;
        double bPlas_TAM_SC41R_DIG;
        double bPlas_TAM_FATVME;
        double bPlas_TAM_FATTAM;

        double bPlas_RefCh0_Det1[bPLASTIC_TAMEX_HITS];
        double bPlas_RefCh0_Det2[bPLASTIC_TAMEX_HITS];
        double bPlas_RefCh0_Det3[bPLASTIC_TAMEX_HITS];

        double Fat_TAM_SC41L_ANA;
        double Fat_TAM_SC41R_ANA;
        double Fat_TAM_SC41L_DIG;
        double Fat_TAM_SC41R_DIG;
        double Fat_RefCh[10];
        double bPlas_AND_Coinc[100];

      //FRS Histograms and conditions setup
        TH1I* MakeH1I(const char* foldername,
        const char* histoname,
        Int_t nbins,
        Float_t xmin, Float_t xmax,
        const char* xtitle = "channels",
        Color_t linecolor = 2,
        Color_t fillcolor = 6,
        const char* ytitle = 0);

      TH2I* MakeH2I(const char* foldername,
        const char* histoname,
        Int_t nbinsx, Float_t xmin, Float_t xmax,
        Int_t nbinsy, Float_t ymin, Float_t ymax,
        const char* xtitle, const char* ytitle,
        Color_t marker);

        TGo4WinCond* MakeWindowCond(const char* foldername,
                  const char* condname,
                  float left = 0.,
                  float right = 4096.,
                  const char* HistoName = 0);

        TGo4PolyCond* MakePolyCond(const char* foldername,
                 const char* condname,
                 Int_t size,
                 Float_t (*points)[2],
                 const char* HistoName = 0);

         Bool_t Check_PolyCond_Multi_X_Y(Float_t X, Float_t Y, Float_t*** V, int n, int cond_num);
         Bool_t Check_PolyCond_X_Y(Float_t X, Float_t Y, Float_t** V, int n );
         void FRS_Gates();

      void ProcessAida(EventUnpackStore* pInput, EventAnlStore* pOutput);


      int PrcID_Conv[7];
      int Used_Systems[7];
      int event_number;
      bool VMEorTAMEX_bPlas;
      bool VMEorTAMEX_fatima;
      bool VMEandTAMEX_fatima;

      void get_used_Systems();
      void load_GermaniumMap_File();
      //void checkTAMEXorVME();

      Float_t  FRS_dE[2],  FRS_dE_cor[2];
      Float_t  FRS_sci_l[12],  FRS_sci_r[12],  FRS_sci_e[12],  FRS_sci_tx[12],  FRS_sci_x[12];
      Float_t FRS_tpc_x[7],FRS_tpc_y[7];
      Float_t  FRS_sci_tofll2,  FRS_sci_tofll3, FRS_sci_tof2, FRS_sci_tofrr2, FRS_sci_tofrr3, FRS_sci_tof3;
      Float_t  FRS_ID_x2, FRS_ID_y2, FRS_ID_a2, FRS_ID_b2;
      Float_t  FRS_ID_x4, FRS_ID_y4, FRS_ID_a4, FRS_ID_b4;
      Int_t    FRS_sci_dt_21l_21r, FRS_sci_dt_41l_41r, FRS_sci_dt_42l_42r, FRS_sci_dt_43l_43r;
      Int_t    FRS_sci_dt_21l_41l, FRS_sci_dt_21r_41r, FRS_sci_dt_21l_42l, FRS_sci_dt_21r_42r;
      Float_t  FRS_ID_brho[2], FRS_ID_rho[2];
      Float_t  FRS_beta, FRS_beta3, FRS_gamma;
      Float_t  FRS_AoQ, FRS_AoQ_corr;
      Float_t  FRS_z, FRS_z2, FRS_z3;
      Float_t  FRS_dEdeg, FRS_dEdegoQ;
//    Float_t  FRS_AoQ_mhtdc, FRS_AoQ_corr_mhtdc;
//      Float_t  FRS_z_mhtdc, FRS_z2_mhtdc;
      Float_t  FRS_dEdeg_mhtdc[10], FRS_dEdegoQ_mhtdc[10];
      Float_t  FRS_beta_mhtdc[10];
      Float_t  FRS_timestamp, FRS_ts, FRS_ts2;
      bool FRS_spill;
      Long64_t FRS_time_mins;
      Float_t  FRS_AoQ_mhtdc[10], FRS_AoQ_corr_mhtdc[10] , FRS_z_mhtdc[10], FRS_z2_mhtdc[10];

      //Float_t  FRS_z_shifted, FRS_z2_shifted;
      int Z_Shift_array;
      Float_t FRS_WR_a[200];
      Float_t FRS_WR_b[200] ;
      Float_t Z1_shift_value[200] ;
      Float_t Z2_shift_value[200] ;
        // FRS_AoQ_shifted;
      int AoQ_Shift_array;
      Float_t FRS_WR_i[200];
      Float_t FRS_WR_j[200] ;
      Float_t AoQ_shift_value[200] ;
      Float_t AoQ_shift_TPC_value[200] ;
      Float_t AoQ_shift_Sci21_value[200] ;
      Float_t AoQ_shift_Sci22_value[200] ;

//       int Fat_Shift_array;
//       int FAT_DET_GFF[1500];
//       Float_t FAT_WR_GFF_Low[1500][36];
//       Float_t FAT_WR_GFF_High[1500][36];
//       Float_t FAT_FACTOR_GFF[1500][36];
      int Fat_Shift_array;
    //  int FAT_DET_GFF[1500];
      Float_t FAT_WR_GFF_Low[100];
      Float_t FAT_WR_GFF_High[100];
      Float_t FAT_FACTOR_GFF[100];
       Float_t FAT_COEFF_GFF[100];

      Int_t ZAoQgnum,Z1Z2gnum,X2AoQgnum,X4AoQgnum,dEdeggnum;
      Float_t X_ZAoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints],Y_ZAoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints];
      Float_t X_ZZ2[MAX_FRS_GATE][MAX_FRS_PolyPoints],Y_ZZ2[MAX_FRS_GATE][MAX_FRS_PolyPoints];
      Float_t X_ZZ2_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints],Y_ZZ2_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints];
      Float_t XX4_AoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints], YX4_AoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints];
      Float_t XX4_AoQ_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints], YX4_AoQ_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints];
      Float_t XX2_AoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints], YX2_AoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints];
      Float_t XX2_AoQ_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints], YX2_AoQ_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints];

      Float_t X_dEdeg[MAX_FRS_GATE][MAX_FRS_PolyPoints], Y_dEdeg[MAX_FRS_GATE][MAX_FRS_PolyPoints];
      Float_t X_dEdeg_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints], Y_dEdeg_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints];
      Float_t X_ZAoQ_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints],Y_ZAoQ_mhtdc[MAX_FRS_GATE][MAX_FRS_PolyPoints];
      int       Aida_Fired;



//       int    bPlasQDCFired;
//       int    bPlasQDCID[32];
//       double bPlasQDC[32];
//       double bPlasQDCGain[32];
//
//       int    bPlasTDCFired;
//       int    bPlasTDCID[50];
//       double bPlasTDC_TS[50][32];
//       double bPlasTDC_ref;
//       int    bPlas_TDC_Multiplicity[32];
//       double bPlas_TDC_diff[50];
//       double bPlas_TDC_diff_sum;
      int    ScalarFired;
      int    ScalarID;


      int   Fatmult;
      int    SC40mult;
      int    SC41mult;
      int    stdcmult;
      int    sqdcmult;
      Long64_t Fat_time_mins;
      int    Fat_QDC_ID[FAT_MAX_VME_CHANNELS];
      double Fat_QDC_E[FAT_MAX_VME_CHANNELS];
      double Fat_QDC_E_Raw[FAT_MAX_VME_CHANNELS];
      ULong64_t timeLAST_Fat, timeFIRST_Fat;
       double FatRealTime;

      Long64_t Fat_QDC_T_coarse[FAT_MAX_VME_CHANNELS];
      double Fat_QDC_T_fine[FAT_MAX_VME_CHANNELS];

      int    Fat_TDC_ID[FAT_VME_MAX_MULTI];
      Long64_t Fat_TDC_T[FAT_VME_MAX_MULTI];
      Long64_t Fat_TDC_T_Raw[FAT_VME_MAX_MULTI];
      //Long64_t FatTDC_TS[50][50];
//       int    FatTDC_Multipl[FAT_VME_MAX_MULTI];
      double Fat_Cha_Ref_TDC;
      Long64_t Fat_WR;
      double SC40[FAT_VME_MAX_MULTI];
      double SC41[FAT_VME_MAX_MULTI];
      double Fat_VME_bPlast[6];


      int Fat_TDC_Singles_ID[FAT_VME_MAX_MULTI];
      int Fat_QDC_Singles_ID[FAT_VME_MAX_MULTI];
      double Fat_QDC_Singles_E[FAT_VME_MAX_MULTI];
      double Fat_QDC_Singles_E_Raw[FAT_VME_MAX_MULTI];
      Long64_t Fat_TDC_Singles_t[FAT_VME_MAX_MULTI];
      Long64_t Fat_TDC_Singles_t_Raw[FAT_VME_MAX_MULTI];
      Long64_t Fat_QDC_Singles_t_coarse[FAT_VME_MAX_MULTI];
      double_t Fat_QDC_Singles_t_fine[FAT_VME_MAX_MULTI];


       // From unpacker
          int    GeFired;
          int    GeDet[Germanium_MAX_HITS];
          int    GeCrys[Germanium_MAX_HITS];
          double GeE[Germanium_MAX_HITS];
          double GeE_Cal[Germanium_MAX_HITS];
          ULong64_t GeT[Germanium_MAX_HITS];
          ULong64_t GeCF_T[Germanium_MAX_HITS];
          ULong64_t RefTGe, RefCFDGe;
          Long64_t Ge_time_mins;
          double GeEventT[Germanium_MAX_HITS];
          bool GePileUp[Germanium_MAX_HITS];
          bool GeOverFlow[Germanium_MAX_HITS];


          int Gam_mult;
            Long64_t dT_Ge,dT_Ge_cfd;
            Long64_t dT_Align,dT_CFD_Align;
            Long64_t Ge_Talign[Germanium_MAX_HITS],Ge_cfd_Talign[Germanium_MAX_HITS];
            Long64_t dT_Addback;

      Long64_t Ge_WR;

      int    Fing_firedTamex;
      int    Fing_leadHits[4];
      int    Fing_trailHits[4];
      int    Fing_iterator[4];
      double Fing_trig[4];
      int    Fing_tamex_ch[4][32];
      int    Fing_leadChan[4][32];
      int    Fing_trailChan[4][32];
      double Fing_lead_coarse[4][32];
      double Fing_lead_fine[4][32];
      double Fing_trail_coarse[4][32];
      double Fing_trail_fine[4][32];

      double Fing_leadT[4][32];
      double Fing_trailT[4][32];
      double Fing_TOT[4][32];
      double Fing_TOT_added[4][32];
      int    Fing_chID[4][32];
      double dataSetPerEvent[50];
      double pmtSetPerEvent[50];
      double totaltimeEvent[50];
      double maxToT;
      int    maxToTChan;
      double maxToT_added;
      int    maxToT_added_Chan;

     void Make_FRS_Histos();
     void Make_Aida_Histos();
    // void Make_Plastic_VME_Histos();
     void Make_Plastic_Twinpeaks_Histos();
     void Make_Plastic_Tamex_Histos();
     void Make_Fatima_Tamex_Histos();
     void Make_Fatima_Histos();
     void Make_Fatima_VME_Tamex_Histos();
     void Make_Germanium_Histos();
     void Make_Finger_Histos();
     void Make_WR_Histos();

     void Make_Fat_Plas_Histos();
     void Make_Fing_Plas_Histos();

     void Process_FRS_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput);
   //  void Process_Plastic_VME_Histos(EventAnlStore* pOutput);
     void Process_Plastic_Tamex_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput);
     void Process_Plastic_Twinpeaks_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput);
     void Process_Fatima_Tamex_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput);
     void Process_Fatima_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput);

     void Process_Fatima_VME_Tamex_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput);
     void Process_Germanium_Histos(EventAnlStore* pOutput);
     void Process_Finger_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput);
     void Process_Fing_Plas_Histos(EventAnlStore* pOutput);
     void Process_Fat_Plas_Histos(EventAnlStore* pOutput);
     void Process_WR_Histos(EventUnpackStore* pInput);
      // TH1 *GermaniumCal;




    long lastTime;
    int ID;
    AidaEvent old;
    AidaEvent evt;
    long startTime;
    long stopTime;

         //   GeEvent gal;

      /* Multiplexer correction */


            int totalEvents;
            int implantEvents;
            int goodImplantEvents;
            int stoppedEvents;
            int decayEvents;
            int pulserEvents;
            int nonsenseEvents;

            std::vector<TH2*> implants_strip_xy;
	    std::vector<TH2*> implants_strip_xy_stopped;
            std::vector<TH2*> implants_pos_xy;
	    std::vector<TH2*> implants_pos_xy_stopped;
            std::vector<TH1*> implants_e;
            std::vector<TH2*> implants_e_xy;
            std::vector<TH1*> implants_time_delta;
            std::vector<TH1*> implants_strip_1d;
            std::vector<TH1*> implants_per_event;
            std::vector<TH1*> implants_channels;
            std::vector<TH2*> implants_x_ex;
            std::vector<TH2*> implants_y_ey;
            #ifdef AIDA_PULSER_ALIGN
            TH2* aida_pulser_time;
            #endif

            std::vector<TH2*> decays_strip_xy;
            std::vector<TH2*> decays_pos_xy;
            std::vector<TH1*> decays_e;
            std::vector<TH2*> decays_e_xy;
            std::vector<TH1*> decays_time_delta;
            std::vector<TH1*> decays_strip_1d;
            std::vector<TH1*> decays_per_event;
            std::vector<TH1*> decays_channels;

            std::vector<AidaCluster> EventsToClusters(std::vector<AidaEvent> const&);
            AidaHit ClusterPairToHit(std::pair<AidaCluster, AidaCluster> const&);

            int      IsData(std::ifstream &f);

            TH1 *hFat_deadtime;
            TH1 *hFatTAM_deadtime;
            TH1 *hGe_deadtime;
            TH1 *hbPlast_deadtime;
            TH1 *hFRS_deadtime;
            TH1 *hAida_Fat_WRdT;
            TH1 *hAida_Ge_WRdT;
            TH1 *hAida_bPlas_WRdT;
            TH1 *hbPlas_Fat_WRdT;
            TH1 *hbPlas_Ge_WRdT;
            TH1 *hFat_Ge_WRdT;
            TH1 *hFatTAM_Ge_WRdT;
            TH1 *hFRS_Ge_WRdT;
            TH1 *hFRS_bPlas_WRdT;
            TH1 *hFRS_FatVME_WRdT;
            TH1 *hFRS_FatTAM_WRdT;
            TH1 *hFRS_FatVME_FatTAM;
            TH1 *hbPlast_FatTAM;

            //FRS Histograms
            TH2  *hID_Z1_vs_T;
            TH2  *hID_AoQ_vs_T;
            TH2  *hID_Z_AoQ;
            TH2  *hID_Z_AoQ_corr;
            TH2  *hID_Z_AoQ_zsame; 
            TH2  *hID_x4AoQ_zsame;
            TH2  *hID_x2AoQ_zsame;
            TH2  *hID_x2AoQ;
            TH2  *hID_x4AoQ;
            TH2  *hID_a2AoQ;
            TH2  *hID_a4AoQ;
            TH2  *hdEdegoQ_Z;
            TH2  *hdEdeg_Z;
            TH2  *hID_Z_Z2;
            TH2  *hID_Z_dE2;
            TH2  *hSCI_dE24;
            TH2  *hID_Z_Sc21E; 
            TH2  *hID_Z_Sc21E_mhtdc;
            TH2  *hID_x2z;
            TH2  *hID_x4z;
            TH2  *hID_E_Xs4;
            TH2  *hID_E_Xs2;
            TH2  *hID_x2a2;
            TH2  *hID_y2b2;
            TH2  *hID_x4a4;
            TH2  *hID_y4b4;
            TH2  *hID_x2x4;
            TH2  *hID_SC41dE_AoQ;
            TH2  *hID_dEToF;
                 
            TH2  *hID_AoQ_mhtdc_T;
            TH2  *hID_Z_mhtdc_T;
            TH2  *hID_Z_AoQ_mhtdc;
            TH2  *hID_Z_AoQ_corr_mhtdc;
            TH2  *hID_Z_Z2_mhtdc;
            TH2  *hID_Z_AoQ_zsame_mhtdc;
            TH2  *hID_x4AoQ_zsame_mhtdc;
            TH2  *hID_x2AoQ_mhtdc;
            TH2  *hID_x2AoQ_zsame_mhtdc;
            TH2  *hID_x4AoQ_mhtdc;
            TH2  *hID_a2AoQ_mhtdc;
            TH2  *hID_a4AoQ_mhtdc;
            TH2  *hdEdegoQ_Z_mhtdc;
            TH2  *hdEdeg_Z_mhtdc;
            TH2  *hID_Z_dE2_mhtdc;
            TH2  *hID_x2z_mhtdc;
            TH2  *hID_x4z_mhtdc;
            // TH2 *hID_Z_AoQ_mhtdc_first_hit;
            // TH2 *hID_Z_AoQ_mhtdc_excluding_first_hit;
            // TH2 *hID_Z_AoQ_corr_mhtdc_first_hit;
            // TH2 *hID_Z_AoQ_corr_mhtdc_excluding_first_hit;
            
             TGo4PolyCond  *cID_Z_AoQ[MAX_FRS_GATE];
             
             TGo4PolyCond  *cID_Z_Z2gate[MAX_FRS_GATE];
             TGo4PolyCond  *cID_x2AoQ[MAX_FRS_GATE];
             TGo4PolyCond  *cID_x4AoQ[MAX_FRS_GATE];
             TGo4PolyCond  *cID_dEdegZ1[MAX_FRS_GATE];

             TGo4PolyCond  *cID_Z_AoQ_mhtdc[MAX_FRS_GATE];
             TGo4PolyCond  *cID_Z_Z2gate_mhtdc[MAX_FRS_GATE];
             TGo4PolyCond  *cID_x2AoQ_mhtdc[MAX_FRS_GATE];
             TGo4PolyCond  *cID_x4AoQ_mhtdc[MAX_FRS_GATE];
             TGo4PolyCond  *cID_dEdegZ1_mhtdc[MAX_FRS_GATE];
                 
             ///Z AoQ gated
             TH2 *hID_ZAoQ_ZAoQgate[MAX_FRS_GATE];
             TH2 *hID_Z1Z2_ZAoQgate[MAX_FRS_GATE];
             TH2 *hID_x2AoQ_Z1AoQgate[MAX_FRS_GATE];
             TH2 *hID_x4AoQ_Z1AoQgate[MAX_FRS_GATE];
             TH2 *hID_dEdegoQ_Z1_Z1AoQgate[MAX_FRS_GATE];
             TH2 *hID_dEdegZ1_Z1AoQgate[MAX_FRS_GATE];
             TH2 *hID_a2AoQ_Z1AoQgate[MAX_FRS_GATE];
             TH2 *hID_a4AoQ_Z1AoQgate[MAX_FRS_GATE];
                   
            ///Z1 Z2 gated
             TH2 *hID_Z1_Z2gate[MAX_FRS_GATE];
             TH2 *hID_x2AoQ_Z1Z2gate[MAX_FRS_GATE];
             TH2 *hID_x4AoQ_Z1Z2gate[MAX_FRS_GATE];
             TH2 *hID_ZAoQ_Z1Z2gate[MAX_FRS_GATE];
             TH2 *hID_a2AoQ_Z1Z2gate[MAX_FRS_GATE];
             TH2 *hID_a4AoQ_Z1Z2gate[MAX_FRS_GATE];
             TH2 *hID_dEdegZ1_Z1Z2gate[MAX_FRS_GATE];
             TH2 *hID_dEdegoQ_Z1_Z1Z2gate[MAX_FRS_GATE];
                   
             ///X2 AoQ gated
             TH2 *hID_x2AoQ_x2AoQgate[MAX_FRS_GATE];
             TH2 *hID_Z1Z2_x2AoQgate[MAX_FRS_GATE];
             ///Z1 Z2 + X2 AoQ gated
             TH2 *hID_x2AoQ_Z1Z2x2AoQgate[MAX_FRS_GATE];
             TH2 *hID_x4AoQ_Z1Z2x2AoQgate [MAX_FRS_GATE];
             TH2 *hID_ZAoQ_Z1Z2x2AoQgate[MAX_FRS_GATE];
             TH2 *hID_Z1Z2_Z1Z2x2AoQgate[MAX_FRS_GATE];
             TH2 *hID_dEdegZ1_Z1Z2x2AoQgate[MAX_FRS_GATE];
             TH2 *hID_dEdegoQ_Z1_Z1Z2x2AoQgate[MAX_FRS_GATE];
             TH2 *hID_a2AoQ_Z1Z2x2AoQgate[MAX_FRS_GATE];
             TH2 *hID_a4AoQ_Z1Z2x2AoQgate[MAX_FRS_GATE];
             
             ///X4 AoQ gated
             TH2 *hID_x4AoQ_x4AoQgate[MAX_FRS_GATE];
             TH2 *hID_Z1Z2_x4AoQgate[MAX_FRS_GATE];
             ///Z1 Z2 + X2 AoQ gated
             TH2 *hID_x2AoQ_Z1Z2x4AoQgate[MAX_FRS_GATE];
             TH2 *hID_x4AoQ_Z1Z2x4AoQgate[MAX_FRS_GATE]; 
             TH2 *hID_ZAoQ_Z1Z2x4AoQgate[MAX_FRS_GATE];
             TH2 *hID_Z1Z2_Z1Z2x4AoQgate[MAX_FRS_GATE];
             TH2 *hID_dEdegZ1_Z1Z2x4AoQgate[MAX_FRS_GATE];
             TH2 *hID_dEdegoQ_Z1_Z1Z2x4AoQgate[MAX_FRS_GATE];
             TH2 *hID_a2AoQ_Z1Z2x4AoQgate[MAX_FRS_GATE];
             TH2 *hID_a4AoQ_Z1Z2x4AoQgate[MAX_FRS_GATE];
             
             ///dEdegZ Gated
             TH2 *hID_Z1AoQ_dEdegZgate[MAX_FRS_GATE];
             TH2 *hID_Z1AoQ_zsame_dEdegZgate[MAX_FRS_GATE];
             TH2 *hID_Z1Z2_dEdegZgate[MAX_FRS_GATE];
             TH2 *hID_x2AoQ_dEdegZgate[MAX_FRS_GATE];
             TH2 *hID_x4AoQ_dEdegZgate[MAX_FRS_GATE];
             TH2 *hID_a2AoQ_dEdegZgate[MAX_FRS_GATE];
             TH2 *hID_a4AoQ_dEdegZgate[MAX_FRS_GATE];
 
             ///MHTDC
             ///Z vs AoQ Gated
             TH2 *hID_ZAoQ_ZAoQgate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_Z1Z2_ZAoQgate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_x2AoQ_Z1AoQgate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_x4AoQ_Z1AoQgate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_dEdegoQ_Z1_Z1AoQgate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_dEdegZ1_Z1AoQgate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_a2AoQ_Z1AoQgate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_a4AoQ_Z1AoQgate_mhtdc[MAX_FRS_GATE];
             
             ///Z1 vs Z2 Gated
             TH2 *hID_Z1_Z2gate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_x2AoQ_Z1Z2gate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_x4AoQ_Z1Z2gate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_ZAoQ_Z1Z2gate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_a2AoQ_Z1Z2gate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_a4AoQ_Z1Z2gate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_dEdegZ1_Z1Z2gate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_dEdegoQ_Z1_Z1Z2gate_mhtdc[MAX_FRS_GATE];
             
              ///X2 vs AoQ Gated
             TH2 *hID_x2AoQ_x2AoQgate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_Z1Z2_x2AoQgate_mhtdc[MAX_FRS_GATE];
              ///Z1 Z2 + X2 vs AoQ Gated
              TH2 *hID_x2AoQ_Z1Z2x2AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_x4AoQ_Z1Z2x2AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_Z1Z2_Z1Z2x2AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_ZAoQ_x2AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_dEdegZ1_Z1Z2x2AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_dEdegoQ_Z1_Z1Z2x2AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_a2AoQ_Z1Z2x2AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_a4AoQ_Z1Z2x2AoQgate_mhtdc[MAX_FRS_GATE];
              
              ///X4 vs AoQ Gated
             TH2 *hID_x4AoQ_x4AoQgate_mhtdc[MAX_FRS_GATE];
             TH2 *hID_Z1Z2_x4AoQgate_mhtdc[MAX_FRS_GATE];
              ///Z1 Z2 + X4 vs AoQ Gated
              TH2 *hID_x2AoQ_Z1Z2x4AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_x4AoQ_Z1Z2x4AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_Z1Z2_Z1Z2x4AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_ZAoQ_x4AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_dEdegZ1_Z1Z2x4AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_dEdegoQ_Z1_Z1Z2x4AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_a2AoQ_Z1Z2x4AoQgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_a4AoQ_Z1Z2x4AoQgate_mhtdc[MAX_FRS_GATE];
              
               ///dE S2 deg vs Z1 Gated
              TH2 *hID_dEdegZ1_dEdegZ1Gated_mhtdc[MAX_FRS_GATE];
              TH2 *hID_Z1AoQ_dEdegZgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_Z1AoQ_zsame_dEdegZgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_Z1Z2_dEdegZgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_x2AoQ_dEdegZgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_x4AoQ_dEdegZgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_a2AoQ_dEdegZgate_mhtdc[MAX_FRS_GATE];
              TH2 *hID_a4AoQ_dEdegZgate_mhtdc[MAX_FRS_GATE];
             
            ///bPlast Histograms

            TH1 *hbPlas_ToT_det[4][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_Multiplicity_Chan[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];

            TH1 *hbPlas_Lead_T[4][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_Trail_T[4][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_Lead_dT_coinc[4][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_Multiplicity_Det1;
            TH1 *hbPlas_Multiplicity_Det2;
            TH1 *hbPlas_Multiplicity_Det3;

            TH1 *hbPlas_lead_lead_ref_det[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_lead_lead_gated[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_ToT[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];

            TH1 *hbPlas_trail_trail[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_Energy_Calib[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_fatimatamex_dT[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_fatimavme_dT[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_SC41L_Digi_lead[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_SC41R_Digi_lead[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_ToT_Sum[bPLASTIC_TAMEX_MODULES+1];
       // TH1 *hbPlas_ToT_Sum_FibreCorr[bPLASTIC_TAMEX_MODULES+1];

            TH1 *hbPlas_hit_pattern_det[bPLASTIC_TAMEX_MODULES+1];
            
            ///Additional for twinpeaks
            TH1 *hbPlas_ToT_Sum_Slow[bPLASTIC_TAMEX_MODULES+1];
            TH1 *hbPlas_ToT_Sum_Fast[bPLASTIC_TAMEX_MODULES+1];
            TH1 *hbPlas_Lead_T_Slow[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
            TH1 *hbPlas_Lead_T_Fast[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];         
            TH1 *hbPlas_ToT_det_Slow[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];  
            TH1 *hbPlas_ToT_det_Fast[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];  
            TH2 *hbPlas_ToT_Slow_vs_Fast_Det1;
            TH2 *hbPlas_ToT_Slow_vs_Fast_Det2;
	    // NEW H.M.A.
// 	    TH2 *hFIMP_ToT_Correlation_Comb1;
// 	    TH2 *hFIMP_ToT_Correlation_Comb2;


             TH1 *hFat_Lead_Fast_T[FATIMA_TAMEX_CHANNELS+1];
             TH1 *hFat_Lead_Slow_T[FATIMA_TAMEX_CHANNELS+1];
             TH1 *hFat_Trail_Fast_T[FATIMA_TAMEX_CHANNELS+1];
             TH1 *hFat_Trail_Slow_T[FATIMA_TAMEX_CHANNELS+1];
             TH1 *hFat_lead_lead_fast_ref[FATIMA_TAMEX_CHANNELS+1];
             TH1 *hFat_lead_lead_slow_ref[FATIMA_TAMEX_CHANNELS+1];
             TH1 *hFat_ToT_Fast_det[FATIMA_TAMEX_CHANNELS+1];
             TH1 *hFat_ToT_Slow_det[FATIMA_TAMEX_CHANNELS+1];
             TH1 *hFat_ToT_Slow_det_calib[FATIMA_TAMEX_CHANNELS+1];
             TH1 *hFat_ToT_Fast_Sum;
             TH1 *hFat_ToT_Slow_Sum;
             TH1 *hFat_ToT_Slow_Sum_Calib;
             TH1 *hFat_tamex_hit_pattern;
             TH1 *hFat_tamex_multiplicity;
             TH2 *hFat_ToT_Slow_vs_Fast;
             TH2 *hFat_FRSFatTamdT_vs_ToT_ch11;

            TH1 *hScalar_hit_pattern;
            //Fatima Histograms
            TH1 *hFAT_Energy[FAT_MAX_VME_CHANNELS];
            TH1 *hFAT_QDCdt[FAT_MAX_VME_CHANNELS];
            TH1 *hFAT_EnergySum;
            TH1 *hFAT_EnergySum_Large;
            TH1 *hFAT_hits_QDC;
            TH1 *hFAT_TDCdt_refCha[FAT_MAX_VME_CHANNELS];
            TH1 *hFat_SC41L_TDC_dT[FAT_MAX_VME_CHANNELS];
            TH1 *hFAT_TDC_bPlast_Cha[FAT_MAX_VME_CHANNELS][6];


            TH1 *hFat_time;

            TH1 *hFAT_Multipl;
            TH1 *hFAT_hits_TDC;
            TH1 *hFat_Energy_GainMonitor;



//             TH1 *hFAT_lead_lead[50];
//             TH1 *hFAT_lead_lead_ref[50];
//             TH1 *hFAT_lead_lead_gated[50];
//             TH1 *hFAT_lead_lead_gated1[50];
//             TH1 *hFAT_lead_lead_gated2[50];
//             TH2 *hFAT_lead_lead_energy[50];
//             TH1 *hFAT_ToT[50];
//             TH1 *hFAT_trail_trail[50];
//             TH2 *hFAT_gamma_gamma;

           // TH1* hFAT_lead_lead_QDC_Gate[50];

            ///Germanium Histograms
            TH1 *hGe_Chan_E[Germanium_MAX_DETS][Germanium_CRYSTALS];
            TH1 *hGe_ERaw[Germanium_MAX_DETS][Germanium_CRYSTALS];
            TH1 *hGe_Chan_E_halfkev[Germanium_MAX_DETS][Germanium_CRYSTALS];
            //TH1 *hGe_Chan_E2;
            TH1 *hGe_Chan_Egate;
            TH1 *hGe_AddbackSum;
            TH1 *hGe_AddbackSum_halfkev;
            TH1 *hGe_dTaddback;
            TH1 *hGe_dTgammagamma;
            TH1 *hGe_CFdT_gammagamma;
            TH1 *hGe_Energy_GainMonitor;
            TH1 *hGe_Chan_E_vsTime;
            TH1 *hGe_SC41L;
            TH1 *hGe_SC41R;
            TH1 *hGe_SC41L_digi;
            TH1 *hGe_SC41R_digi;
            TH1 *hGe_Chan_Time_Diff[Germanium_MAX_DETS][Germanium_CRYSTALS];
            TH1 *hGe_Chan_Time_Diff_CF[Germanium_MAX_DETS][Germanium_CRYSTALS];
            //TH1 *hGe_Time_Diff_vs_Energy[32];
            TH1 *hGe_ESum;
            TH1 *hGe_Mult;
            TH1 *hGe_ESum_halfkev;
            TH1 *hGe_ESum_largerange_OF;
            TH1 *hGe_ESum_largerange_PU;
            TH1 *hGe_Hit_Pat;
            TH2 *hGe_Chan_E_Mat;
            TH2 *hGe_Chan_E_vsCrys;
            TH2 *hGe_Time_Diff_vs_Energy_sum;
            TH2 *hGe_Chan_E_vsDet;
            TH2 *hGe_MultvsdT;
          //  TH1 *hGe_Chan_E_gate[32];
            TH1 *hGe_ge_time_difference_gg;


            //Finger Histograms
            TH1 *hFING_Hit_Pat;
//             TH1 *hFING_lead_lead[52];
//             TH1 *hFING_trail_trail[52];
//             TH1 *hFING_ToT[52];
//             TH1 *hFING_MaxToT[52];
//             TH1 *hFING_ToTMaxAdded[52];
//             TH1 *hFING_trig_lead[52];
//             TH1 *hFING_SC41_ToT;
//             TH2 *hFING_ToT_StripID;
//             TH2 *hFING_ToT_StripID_UpDown;
//             TH2 *hFING_ToT_StripID_UpDown_max;
//             TH2 *hFING_Pos_ToT;
//             TH2 *hFING_Pos_ToT_Max;
//             TH1 *hFING_Pos_ToT_gated;
//             TH2 *hFING_MaxToT_StripID;
//             TH2 *hFING_MaxToTExp_StripID;
//             TH2 *hFING_ToT_lead_lead[52];
//             TH2 *hFING_Pos;                 //E.Sahin 24.05
//             TH2 *hFING_ToT_StripID_Exp;
//             TH1 *hFING_fcoarse[52];
//             TH1 *hFING_ffine[52];
//             TH2* hFING_LeadLead_StripID;
            TH1 *hFING_Multiplicity;
            TH1 *hFING_ToT_Strip[52];
            TH1 *hFING_MaxToT_Strip[52];
            TH2 *hFING_ToT_v_Strip;
            TH2 *hFING_MaxToT_v_Strip;

            TH1 *hFING_ToT_PMT[52];
            TH2 *hFING_ToT_v_PMT;
            TH1 *hFING_lead_lead[52];
            TH1 *hFING_trail_trail[52];
            TH1 *hFING_Sc41lead_leadmaxtot[52];
            TH2* hFing_ToTRatio_v_Strip;
            TH2* hFing_MaxToTRatio_v_Strip;

            TH1 *hFING_SC41_lead_lead;
            TH1 *hFING_SC41_trail_trail;
            TH1 *hFING_SC41_tot;
            TH1 *hSC41FatPlas;

private :
     ///TEMP
                    bool fired_det1, fired_det2;
                    int bPlas_tot_hits[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET] ;

            bool FAT_dist_corr_used; // Read from General Setup File
            int  FAT_exclusion_dist; // Read from General Setup File
            int  FAT_num_TDC_modules; // Read from General Setup File
            bool FAT_nearest_neighbour_exclusion; // Read from General Setup File
            bool same_ring_exclusion; // Read from General Setup File
            bool output_position_matrix; // Read from General Setup File
            bool VME_TAMEX_bPlas,VME_TAMEX_Fatima, VME_AND_TAMEX_Fatima;

      ClassDef(EventAnlProc, 1)
	};
#endif //EVENTANLPROCESSOR_H
