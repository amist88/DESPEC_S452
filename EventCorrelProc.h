// $Id: EventCorrelProc.h 755 2011-05-20 08:04:11Z linev $
//Mistry 10.04.19
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

#ifndef EVENTCORRELPROCESSOR_H
#define EVENTCORRELPROCESSOR_H

#include "TGo4EventProcessor.h"

#include "CorrelParameter.h"
#include "CalibParameter.h"
#include "EventUnpackStore.h"
#include "EventAnlStore.h"
#include "AIDA_Headers.h"
#include "AIDA_Event.h"
#include "AIDA_Data_Types.h"
#include "FATIMA_tofCorr.h"
#include "TimingCube.h"  //includes THnSparse
#include "Go4ConditionsBase/TGo4WinCond.h"
#include "Go4ConditionsBase/TGo4PolyCond.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

#include "TTree.h"
#include "TFile.h"

//Max lengths
#define  maxdef(a,b) ( ((a) > (b)) ? (a) : (b) )
//Absolute value
#define ABS(x)  ((x)>=0 ? (x):-(x))

class EventAnlStore;
class EventCorrelStore;
class TSCNParameter;

class AidaHitPID : public TObject
{
public:
  int Event;

  int DSSD;
  // Coordinate in Strip & Position
  double StripX;
  double StripY;
  double PosX;
  double PosY;


  double Energy;
  double EnergyFront;
  double EnergyBack;

  // Cluster Size for correlations
  int StripXMin;
  int StripXMax;
  int StripYMin;
  int StripYMax;
  int ClusterSizeX;
  int ClusterSizeY;

  int64_t Time;
  int64_t TimeFront;
  int64_t TimeBack;
  int64_t FastTime;
  int64_t FastTimeFront;
  int64_t FastTimeBack;

  // Add extra PID stuff for implants

  Int_t GatePass;
  Float_t FRS_Z;
  Float_t FRS_AoQ;

  // If the implant is believed to have stopped here (AIDA only veto)
  bool Stopped;

  AidaHitPID() { Zero(); }
  void Zero() {}
  virtual ~AidaHitPID() {}

  ClassDef(AidaHitPID, 3)
};


class EventCorrelProc : public TGo4EventProcessor {
   public:
      EventCorrelProc();
      EventCorrelProc(const char * name);
      virtual ~EventCorrelProc();
       CorrelParameter *fCorrel;
       CalibParameter *fCal;

      virtual Bool_t BuildEvent(TGo4EventElement* dest);
        std::vector<AidaCluster> EventsToClusters(std::vector<AidaEvent> const&);
        AidaHit ClusterPairToHit(std::pair<AidaCluster, AidaCluster> const&);
        std::multimap<int64_t, AidaHitPID> implantMap;

    void get_used_systems();
    void Ge_2DPromptFlashCut();
    void Fat_2DPromptFlashCut();
  //  void Fat_TimeCorrection(EventAnlStore* cInput);
    void Beta_Gates();

    int  IsData(std::ifstream &f);

    void Make_FRS_AIDA_Histos();

    void Make_FRS_Prompt_Ge_Histos();
    void Make_FRS_Prompt_Fat_Histos();

    void Make_FRS_LongIso_Ge_Histos();
    void Make_FRS_LongIso_Fatima_Histos();

    void Make_Beta_Gamma_bPlast_SpillOff_Histos();
    void Make_Beta_Gamma_Histos();
    void Make_Timemachine_Histos();

    //
    void Make_FRS_AIDA_FATIMA_Histos();

    void Process_FRS_AIDA(EventAnlStore* cInput, EventCorrelStore* cOutput);

    void Process_FRS_Prompt_Fat(EventAnlStore* cInput, EventCorrelStore* cOutput);
    void Process_FRS_Prompt_Ge(EventAnlStore* cInput, EventCorrelStore* cOutput);

    void Process_FRS_LongIso_Ge(EventAnlStore* cInput, EventCorrelStore* cOutput);
    void Process_FRS_LongIso_Fat(EventAnlStore* cInput, EventCorrelStore* cOutput);

    void Process_Beta_Gamma_bPlast_SpillOff(EventAnlStore* cInput, EventCorrelStore* cOutput);

    void Process_Beta_Gamma(EventAnlStore* cInput, EventCorrelStore* cOutput);
    void Process_Timemachine(EventAnlStore* cInput, EventCorrelStore* cOutput);

    //FATIMA tof corrected:
    //Includes FATIMA_tofCorrection!
    void Process_FRS_AIDA_FATIMA (EventAnlStore* cInput, EventCorrelStore* cOutput);
    FATIMA_tofCorr *fatTC;
    double ggtarray[3]; //Will be needed for filling the cube.
    THnSparseD *ggt_nocorr;
    THnSparseD *ggt_tofcorr;
    int    FAT_dt_FRS_gate;
    double Fat_t1;
    double Fat_t2;
    double Fat_e1;
    double Fat_e2;
    int    Fat_n1;
    int    Fat_n2;

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

    //  std::vector<TH2*> hA_FRS_Z1Z2_implants_strip_xy;
      std::vector<TH2*> hA_FRS_Z1Z2_implants_pos_xy;
      std::vector<TH1*> hA_FRS_Z1Z2_implants_e;
      std::vector<TH2*> hA_FRS_Z1Z2_implants_e_xy;

      //For the long isomer correlations
        std::vector<float> tag_all;
        std::vector<Long64_t> ts_all;
        std::vector<double> GeE_all;
        std::vector<Long64_t> GeT_all;
        Long64_t dT_frsge_long;
        Long64_t dT_frsge_prompt;
        Long64_t dT_frsge_mult_long;
        Long64_t dT_frsge_mult_prompt;
        Long64_t dT_GeT_long;
        Long64_t dT_GeT_prompt;
        Long64_t Ge_FirstT_long;
        Long64_t Ge_FirstT_prompt;
        Int_t Ge_mult_long;
        Int_t Ge_mult_prompt;
        Long64_t dT_Ge_SCI;

        double GeE_Long[Germanium_MAX_HITS];
        double GeT_Long[Germanium_MAX_HITS];
        double GeE_Prm_Long[Germanium_MAX_HITS];
        double GeT_Prm_Long[Germanium_MAX_HITS];
        Long64_t ts;

        std::vector<float> tag_fat_all;
        std::vector<Long64_t> ts_fat_all;

        Long64_t dT_frsfat_long;
        Long64_t dT_frsfat_prompt;
        Long64_t dT_FRS_Fatima_WR;
        Long64_t dT_frsfat_mult_long;
        Long64_t dT_frsfat_mult_prompt;
        Long64_t dT_FatT_long;
        Long64_t dT_FatT_prompt;
        Long64_t Fat_FirstT_long;
        Long64_t Fat_FirstT_prompt;
        Int_t Fat_mult_long;
        Int_t Fat_mult_prompt;

        double FatE_Long[FAT_VME_MAX_MULTI];
        double FatT_Long[FAT_VME_MAX_MULTI];
        double FatE_Prm_Long[FAT_VME_MAX_MULTI];
        double FatT_Prm_Long[FAT_VME_MAX_MULTI];
        Long64_t ts_fat;
        long long lastAIDAWR;
        long long lastAIDAdecayWR;

        Int_t bPlast_Det;
        Int_t bPlast_Chan;
        Int_t Beta_Gate_Low[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
        Int_t Beta_Gate_High[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];

        TH1 *hAida_Implant_deadtime;
        TH1 *hAida_Decay_deadtime;
        TH1 *hFatVME_TMdT;
        TH1 *hFatTAMEX_TMdT;
        TH1 *hGe_TMdT;
        TH1 *hbPlastic_TMdT;
        TH1 *hAida_TMdT;

        TH1 *hAIDA_WRTM_FRS;
        TH1 *hAIDA_WRTM_Ge;
        TH1 *hAIDA_WRTM_FatVME;
        TH1 *hAIDA_WRTM_FatTAMEX;
        TH1 *hAIDA_WRTM_bPlast;

        TH2 *hFatVME_FatTAMEX_TM;
        TH2 *hFatVME_Ge_TM;
        TH2 *hFatVME_bPlast_TM;
        TH2 *hFatVME_AIDA_TM;
        TH2 *hFatTAMEX_Ge_TM;
        TH2 *hFatTAMEX_bPlast_TM;
        TH2 *hFatTAMEX_AIDA_TM;
        TH2 *hGe_bPlast_TM;
        TH2 *hGe_AIDA_TM;
        TH2 *hAIDA_bPlast_TM;
//       std::vector<std::vector<TH2*>> hA_FRS_ZAoQ_implants_strip_xy;
//       std::vector<std::vector<TH1*>> hA_FRS_ZAoQ_implants_e_gate;
      TH2 *hA_FRS_Z1Z2_implants_strip_xy[MAX_FRS_GATE][3];
      TH2 *hA_FRS_ZAoQ_implants_strip_xy[MAX_FRS_GATE][3];
      TH2 *hA_FRS_ZAoQ_implants_position[MAX_FRS_GATE][3];
      TH2 *hA_FRS_ZAoQ_implants_position_stopped[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_implants_position[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_implants_strip_xy_stopped[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_implants_position_stopped[MAX_FRS_GATE][3];
      TH2 *hA_FRS_ZAoQ_implants_strip_xy_stopped[MAX_FRS_GATE][3];
      TH1 *hA_FRS_ZAoQ_implants_e[MAX_FRS_GATE][3];
      TH1 *hA_FRS_ZAoQ_implants_e_stopped[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_x2AoQ_implants_strip_xy[MAX_FRS_GATE][3];
      TH1 *hA_FRS_Z1Z2_x2AoQ_implants_e[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_x2AoQ_implants_strip_xy_stopped[MAX_FRS_GATE][3];
      TH1 *hA_FRS_Z1Z2_x2AoQ_implants_e_stopped[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_x2AoQ_implants_position[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_x2AoQ_implants_position_stopped[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_x4AoQ_implants_strip_xy[MAX_FRS_GATE][3];
      TH1 *hA_FRS_Z1Z2_x4AoQ_implants_e[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_x4AoQ_implants_strip_xy_stopped[MAX_FRS_GATE][3];
      TH1 *hA_FRS_Z1Z2_x4AoQ_implants_e_stopped[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_x4AoQ_implants_position[MAX_FRS_GATE][3];
      TH2 *hA_FRS_Z1Z2_x4AoQ_implants_position_stopped[MAX_FRS_GATE][3];

      std::vector<TH2*> hA_FRS_ZAoQ_implants_pos_xy;
     // std::vector<TH1*> hA_FRS_ZAoQ_implants_e;

     // std::vector<TH2*> hA_FRS_ZAoQ_implants_strip_xy_gate1;

     // std::vector<TH2*> hA_FRS_Z1Z2_x2AoQ_implants_e_xy;
      std::vector<TH1*> hA_FRS_ZAoQ_implants_time_delta;
      std::vector<TH1*> hA_FRS_ZAoQ_implants_strip_1d;
      std::vector<TH1*> hA_FRS_ZAoQ_implants_per_event;
      std::vector<TH2*> hA_FRS_ZAoQ_implants_strip_xy_dssdg;
      TH1 *hA_Imp_FRS_dT;
      TH1 *hA_bPlast_dT;

      TH1 *hAida_Imp_bPlas_dT;
      TH1 *hFRS_bPlast_dT;

      TH1 *hA_impdec_dT;
      TH1 *hA_impdec_dT_FRS_gated;


      TGo4WinCond  *fconHis1;
      TGo4WinCond  *fWinCon1;

      TH1 *hA_implant_FatdT;
      TH1 *hA_implant_FatE;
      TH2 *hA_implant_FatdT_FatE;

        Long64_t Fat_time_mins_ZAoQ;

      TH1 *hA_FRSWR_FatWR;
      TH1 *hA_FRS_FatE;
      TH1 *hA_FRS_ZAoQ_FatE[MAX_FRS_GATE];
      TH2 *hA_FRS_ZAoQ_FatEvsT[MAX_FRS_GATE];
      TH2 *hA_FRS_ZAoQ_FatE1vsE2[MAX_FRS_GATE];
      TH1 *hFat_Energy_GainMonitor_188Ta;

      TH1 *hA_FRS_Z1Z2_X2AoQ_FatE[MAX_FRS_GATE];
      TH2 *hA_FRS_Z1Z2_X2AoQ_FatEvsT[MAX_FRS_GATE];
      TH2 *hA_FRS_Z1Z2_X2AoQ_FatE1vsE2[MAX_FRS_GATE];
      TH1 *hA_FRS_Z1Z2_X4AoQ_FatE[MAX_FRS_GATE];
      TH2 *hA_FRS_Z1Z2_X4AoQ_FatEvsT[MAX_FRS_GATE];
      TH2 *hA_FRS_Z1Z2_X4AoQ_FatE1vsE2[MAX_FRS_GATE];

      ///Prompt fatima LT analysis
      TH1 *hA_FRS_Fat_LT1_start_stop;
      TH1 *hA_FRS_Fat_LT1_start_stop_ns;
      TH1 *hA_FRS_Fat_LT2_start_stop;
      TH1 *hA_FRS_Fat_LT2_start_stop_ns;
      TH1 *hA_FRS_Fat_LT3_start_stop;
      TH1 *hA_FRS_Fat_LT3_start_stop_ns;

      TH1 *hA_FRS_Fat_LT1_stop_start;
      TH1 *hA_FRS_Fat_LT1_stop_start_ns;
      TH1 *hA_FRS_Fat_LT2_stop_start;
      TH1 *hA_FRS_Fat_LT2_stop_start_ns;
      TH1 *hA_FRS_Fat_LT3_stop_start;
      TH1 *hA_FRS_Fat_LT3_stop_start_ns;


      TH1 *hA_FRS_Z1Z2_X2AoQX4AoQ_FatE[MAX_FRS_GATE];

      TH1 *hA_FRSWR_GeWR;
      TH1 *hA_FRS_GeE;
      TH2 *hA_FRS_ZAoQ_GeEvsT_all;
      TH1 *hA_FRS_ZAoQ_GeE[MAX_FRS_GATE];
      TH1 *hA_FRS_Z1Z2_X2AoQ_GeE[MAX_FRS_GATE];
      TH2 *hA_FRS_Z1Z2_X2AoQ_GeEvsT[MAX_FRS_GATE];
      TH1 *hA_FRS_Z1Z2_X4AoQ_GeE[MAX_FRS_GATE];
      TH2 *hA_FRS_Z1Z2_X4AoQ_GeEvsT[MAX_FRS_GATE];
     // TH2 *hA_FRS_GeEvsT;
      TH2 *hA_FRS_ZAoQ_GeEvsT[MAX_FRS_GATE];
      TH2 *hA_FRS_ZAoQ_GeE1_GeE2[MAX_FRS_GATE];
      TH2 *hA_FRS_Z1Z2_X2AoQ_GeE1_GeE2[MAX_FRS_GATE];
      TH2 *hA_FRS_Z1Z2_X4AoQ_GeE1_GeE2[MAX_FRS_GATE];

      TH1 *hA_FRS_ZAoQ_GeE_LongIso;
      TH2 *hA_FRS_GeEvsT_LongIsoGated;
      TH2 *hA_FRS_GeE1vsGeE2_LongIsoGated;

      TH1 *hA_FRS_PID_FatE_LongIso;
      TH2 *hA_FRS_FatEvsT_LongIsoGated;
      TH2 *hA_FRS_FatE1vsFatE2_LongIsoGated;

      //Spill of Beta-Gamma
      TH1 *hbPlast_SpillOff_Fatima;
      TH2 *hbPlast_SpillOff_Fatima_gammagamma;
      TH2 *hbPlast_SpillOff_Germanium_gammagamma;
      TH2 *hbPlast_SpillOff_Fatima_GamGam;
      TH1 *hbPlast_SpillOff_Germanium;
      TH2 *hbPlast_SpillOff_Germanium_GamGam;
      TH1 *hbPlas_ToT_SpillOff[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
      TH1 *hbPlas_ToT_SpillOn[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];

     ///AIDA BDG's
      TH1 *hGe_BetaGamma;
      TH1 *hAidaImpDecdT;
      TH1 *hAida_Dec_Ge_dT;
      TH1 *hAida_Dec_bPlas_dT;
      TH1 *hAida_Dec_Fatima_dT;
      TH1 *hDecPIDGated[MAX_FRS_GATE];
      TH1 *hGe_BetaGamma_E[MAX_FRS_GATE];
      TH1 *hGe_BetaGamma_GeE1_GeE2[MAX_FRS_GATE];
      TH1 *hGe_BetaGamma_dT[MAX_FRS_GATE];
      TH2 *hGe_BetaGamma_EdT[MAX_FRS_GATE];
      TH1 *hGe_BetaGamma_GeE1_GatedTrans;

      TH1 *hFat_LT1_start_stop;
      TH1 *hFat_LT1_start_stop_ns;
      TH1 *hFat_LT2_start_stop;
      TH1 *hFat_LT2_start_stop_ns;

      TH1 *hFat_LT1_stop_start;
      TH1 *hFat_LT1_stop_start_ns;
      TH1 *hFat_LT2_stop_start;
      TH1 *hFat_LT2_stop_start_ns;

      TH1 *hFat_95Rh_All_LT;
      TH1 *hFat_BetaGamma_E[MAX_FRS_GATE];
      TH2 *hFat_BetaGamma_E1_E2[MAX_FRS_GATE];

    //  bool AIDA_implantation_gate;

      TGo4PolyCond  *cGe_EdT_cut[MAX_FRS_GATE];
      TGo4PolyCond  *cFat_EdT_cut[MAX_FRS_GATE];

      int event_number;
      int Used_Systems[7];
      Long64_t AIDA_WR;
      Long64_t FRS_WR;
      Long64_t bPLAS_WR;
      Long64_t FAT_WR;
      Long64_t Ge_WR;
      Long64_t dT_AIDA_FRS;
      Long64_t dT_AIDA_bPlast;
      Long64_t dT_FRS_bPlast;
      Long64_t dT_AIDA_Ge;
      Long64_t dT_AIDA_Fat;
      TSCNParameter *fParam1;

      Int_t Ge_dT_cut_num;
      Float_t X_Ge_EdT_cut[MAX_FRS_GATE][MAX_FRS_PolyPoints],Y_Ge_EdT_cut[MAX_FRS_GATE][MAX_FRS_PolyPoints];

      Int_t Fat_dT_cut_num;
      Float_t X_Fat_EdT_cut[MAX_FRS_GATE][MAX_FRS_PolyPoints],Y_Fat_EdT_cut[MAX_FRS_GATE][MAX_FRS_PolyPoints];

      Int_t C_ZAoQgnum,C_Z1Z2gnum,C_X2AoQgnum,C_X4AoQgnum,C_dEdeggnum;
      Float_t C_X_ZAoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints],C_Y_ZAoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints];

      Int_t Fat_det_num;
      Float_t fat_timecorrection[FAT_MAX_VME_CHANNELS];



//       //Long64_t*** aidatime;

       Long64_t aida_imptime[3][128][128];
       Long64_t aida_imptime_FRS_gated[3][128][128];

       Double_t FatimaVME_TimeMachine_dT[10];
       Double_t FatimaTAMEX_TimeMachine_dT[10];
       Long64_t Germanium_TimeMachine_dT;
       Double_t bPlast_TimeMachine_dT[10];
       Double_t AIDA_TimeMachine_dT;

      ClassDef(EventCorrelProc, 1)
    };
#endif
