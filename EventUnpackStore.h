// Adapted for DESPEC by A.K.Mistry 2020
//
//---------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//       Experiment Data Processing at EE department, GSI
//---------------------------------------------------------------
//
//Copyright (C) 2000- Gesellschaft f. Schwerionenforschung, GSI
//                    Planckstr. 1, 64291 Darmstadt, Germany
//Contact:            http://go4.gsi.de
//----------------------------------------------------------------
//This software can be used under the license agreements as stated
//in Go4License.txt file which is part of the distribution.
//----------------------------------------------------------------

#ifndef UNPACKEVENTSTORE_H
#define UNPACKEVENTSTORE_H


#include "AIDA_Event.h"
#include "TGo4EventElement.h"

#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

struct AidaUnpackData {
     uint64_t AIDATime;
     int AIDAHits;

      std::vector<AidaEvent> ImplantEvents;
      std::vector<AidaEvent> DecayEvents;

      std::vector<AidaHit> Implants;
      std::vector<AidaHit> Decays;
};

class EventUnpackStore : public TGo4EventElement {
public:
        EventUnpackStore();
        EventUnpackStore(const char* name);
        virtual ~EventUnpackStore();

        /** Method called by the framework to clear the event element. */
        void Clear(Option_t *t="");
        //Clear the members
        //void ClearEvent();


        //FRS Output
   Float_t fFRS_Music_dE[3], fFRS_Music_dE_corr[3];
   Float_t fFRS_Music_E1[8], fFRS_Music_E2[8], fFRS_Music_T1[8], fFRS_Music_T2[8];
   Float_t fFRS_sci_l[12], fFRS_sci_r[12], fFRS_sci_e[12], fFRS_sci_tx[12], fFRS_sci_x[12];


   Double_t fTRaw_vftx_21l,fTRaw_vftx_21r,fTRaw_vftx_22l,fTRaw_vftx_22r,fTRaw_vftx_41l,fTRaw_vftx_41r,fTRaw_vftx_42l,fTRaw_vftx_42r;
  //  Float_t fFRS_sci_e[12];
  //  Float_t fFRS_sci_tofll2, fFRS_sci_tofll3, fFRS_sci_tof2, fFRS_sci_tofrr2, fFRS_sci_tofrr3, fFRS_sci_tof3;
    Float_t fFRS_sci_tof2;
    Float_t fFRS_ID_x2, fFRS_ID_y2, fFRS_ID_a2, fFRS_ID_b2;
    Float_t fFRS_ID_x4, fFRS_ID_y4, fFRS_ID_a4, fFRS_ID_b4;
  //  Int_t fFRS_sci_dt_21l_21r, fFRS_sci_dt_41l_41r, fFRS_sci_dt_42l_42r, fFRS_sci_dt_43l_43r;
   // Int_t fFRS_sci_dt_21l_41l, fFRS_sci_dt_21r_41r, fFRS_sci_dt_21l_42l, fFRS_sci_dt_21r_42r;
   // Float_t fFRS_ID_brho[2], fFRS_ID_rho[2];
    Float_t fFRS_beta, fFRS_gamma;
    Float_t fFRS_tof4121, fFRS_tof4221;
    Float_t fFRS_AoQ, fFRS_AoQ_corr;
    Float_t fFRS_z, fFRS_z2;
    Float_t fFRS_dEdeg, fFRS_dEdegoQ;

    Float_t fFRS_AoQ_mhtdc[10], fFRS_AoQ_corr_mhtdc[10];

    Float_t fFRS_z_mhtdc[10], fFRS_z2_mhtdc[10];
    Float_t fFRS_dEdeg_mhtdc[10];
    Float_t fFRS_dEdegoQ_mhtdc[10];
    Float_t fFRS_beta_mhtdc[10];
    Float_t fFRS_tof4121_mhtdc[10];
    Float_t fFRS_tof4122_mhtdc[10];
    Float_t fFRS_tof4221_mhtdc;

  //  Float_t fFRS_timestamp, fFRS_ts, fFRS_ts2;
    Long64_t     fFRS_WR;
    Float_t      fFRS_TPC_x[7];
    Float_t      fFRS_TPC_y[7];
    UInt_t       fFRS_scaler[64];
    UInt_t       fFRS_scaler_delta[64];
        //AIDA output
        std::vector<AidaUnpackData> Aida;
        std::vector<AidaScaler> fAidaScalers;

         int      fAIDAHits;
         int      AIDAHits;
         Long64_t AIDATime;
         Long64_t fAIDA_WR;

        //General Output
        Int_t     fevent_number;
        Int_t     fTrigger;
        Int_t     fProcID[7];
        Int_t     fScalar_fired;
        Int_t     fScalar_ID;

        UInt_t    fFat_mult;

        UInt_t    fFat_SC40mult;
        UInt_t    fFat_SC41mult;
        Int_t    fFat_TMCh1mult;
        Int_t    fFat_TMCh2mult;



        UInt_t    fFat_QDC_Multiplicity;
        Int_t     fFat_QDC_ID[FAT_MAX_VME_CHANNELS];
        Double_t  fFat_QDC_E[FAT_MAX_VME_CHANNELS];
        Double_t  fFat_QDC_E_Raw[FAT_MAX_VME_CHANNELS];
        Long64_t  fFat_QDC_T_coarse[FAT_MAX_VME_CHANNELS];
        Double_t  fFat_QDC_T_fine[FAT_MAX_VME_CHANNELS];

        Int_t     fFat_TDC_ID[FAT_MAX_VME_CHANNELS];
        UInt_t    fFat_TDC_Multiplicity[FAT_MAX_VME_CHANNELS];
        Long64_t  fFat_WR;
        double_t  fSC40[10];
        double_t  fSC41[10];
        double_t  fFat_TMCh1[10];
        double_t  fFat_TMCh2[10];
        double_t  fFat_bplastChanT[6];



        Long64_t  fFat_TDC_Time[FAT_MAX_VME_CHANNELS];
        Long64_t  fFat_TDC_Time_Raw [FAT_MAX_VME_CHANNELS];

        Int_t     fFat_TDC_Singles_ID[FAT_MAX_VME_CHANNELS];
        Long64_t  fFat_TDC_Singles_t[FAT_MAX_VME_CHANNELS];
        Long64_t  fFat_TDC_Singles_t_Raw[FAT_MAX_VME_CHANNELS];
        Int_t     fFat_QDC_Singles_ID[FAT_MAX_VME_CHANNELS];
        Double_t  fFat_QDC_Singles_E[FAT_MAX_VME_CHANNELS];
        Double_t  fFat_QDC_Singles_E_Raw[FAT_MAX_VME_CHANNELS];
        Long64_t  fFat_QDC_Singles_t_coarse[FAT_MAX_VME_CHANNELS];
        Double_t  fFat_QDC_Singles_t_fine[FAT_MAX_VME_CHANNELS];
        UInt_t    fFat_tdcsinglescount;
        UInt_t    fFat_qdcsinglescount;

         Int_t    fGe_fired;
         Int_t    fGe_Detector[Germanium_MAX_HITS];
         Int_t    fGe_Crystal[Germanium_MAX_HITS];
         Double_t fGe_E[Germanium_MAX_HITS];
         ULong64_t fGe_T[Germanium_MAX_HITS];
         ULong64_t fGe_Event_T[Germanium_MAX_HITS];
         ULong64_t fGe_cfT[Germanium_MAX_HITS];
         bool     fGe_Pileup[Germanium_MAX_HITS];
         bool     fGe_Overflow[Germanium_MAX_HITS];
         Long64_t fGe_WR;


        Long64_t fFinger_WR;
       Int_t fFing_Strip_N[52];
       Double_t fFing_Lead_Up[52][100];
       Double_t fFing_Trail_Up[52][100];
       Double_t fFing_Lead_Down[52][100];
       Double_t fFing_Trail_Down[52][100];
       Int_t fFing_Strip_N_LU[52];
       Int_t fFing_Strip_N_TU[52];
       Int_t fFing_Strip_N_LD[52];
       Int_t fFing_Strip_N_TD[52];
       Double_t fFing_SC41_lead[2][50];
       Double_t fFing_SC41_trail[2][50];

       Int_t fFing_PMT_Lead_N[52];
       Int_t fFing_PMT_Trail_N[52];
       Double_t fFing_Lead_PMT[52][10];
       Double_t fFing_Trail_PMT[52][10];
       //FATIMA TAMEX

//        Double_t fFat_SC41_lead[2][50];
//        Double_t fFat_SC41_trail[2][50];
//        Int_t fFat_PMT_Lead_N[FATIMA_TAMEX_CHANNELS];
//        Int_t fFat_PMT_Trail_N[FATIMA_TAMEX_CHANNELS];
//        Double_t fFat_Lead_PMT[FATIMA_TAMEX_CHANNELS][FATIMA_TAMEX_HITS];
//        Double_t fFat_Trail_PMT[FATIMA_TAMEX_CHANNELS][FATIMA_TAMEX_HITS];
       Long64_t fFat_Tamex_WR;

       Int_t fFat_Fast_Lead_N[100];
       Int_t fFat_Slow_Lead_N[100];
       Int_t fFat_Fast_Trail_N[100];
       Int_t fFat_Slow_Trail_N[100];
       Double_t fFat_Lead_Fast[100][100];
       Double_t fFat_Lead_Slow[100][100];
       Double_t fFat_Trail_Fast[100][100];
       Double_t fFat_Trail_Slow[100][100];

         Int_t  fbPlasDetNum_Fast;
       Int_t  fbPlasDetNum_Slow;
       Int_t  fbPlas_FastChan[bPLASTIC_TAMEX_MODULES+1];
       Int_t  fbPlas_SlowChan[bPLASTIC_TAMEX_MODULES+1];
       Int_t  fbPlast_Fast_Lead_N[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
       Int_t  fbPlast_Slow_Lead_N[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
       Int_t  fbPlast_Fast_Trail_N[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
       Int_t  fbPlast_Slow_Trail_N[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
       Double_t fbPlast_Fast_Lead[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
       Double_t fbPlast_Slow_Lead[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
       Double_t fbPlast_Fast_Trail[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
       Double_t fbPlast_Slow_Trail[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
       
        //bPlas TAMEX
       Long64_t fbPlas_WR;
       Int_t  fbPlasDetNum;
       Int_t fbPlasChan[bPLASTIC_TAMEX_MODULES+1];
       Int_t fbPlas_PMT_Lead_N[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
       Int_t fbPlas_PMT_Trail_N[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET];
       Double_t fbPlas_Lead_PMT[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];
       Double_t fbPlas_Trail_PMT[bPLASTIC_TAMEX_MODULES+1][bPLASTIC_CHAN_PER_DET][bPLASTIC_TAMEX_HITS];

   ClassDef(EventUnpackStore,1)
};
#endif //TEVENT_H




//----------------------------END OF GO4 SOURCE FILE ---------------------
