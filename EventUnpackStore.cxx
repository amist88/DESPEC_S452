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
#define ZERO_ARRAY(x) memset(x, 0, sizeof(x))
#include "EventUnpackStore.h"

#include "Riostream.h"

//***********************************************************
EventUnpackStore::EventUnpackStore() :
        TGo4EventElement()
{
     //   cout << "**** EventUnpackStore: Create instance" << endl;
}
//***********************************************************
EventUnpackStore::EventUnpackStore(const char* name) :
        TGo4EventElement(name)
{
       // cout << "**** EventUnpackStore: Create instance " << name << endl;
}
//***********************************************************
EventUnpackStore::~EventUnpackStore()
{
      // cout << "**** EventUnpackStore: Delete instance " << endl;
}

//-----------------------------------------------------------
void  EventUnpackStore::Clear(Option_t *t)
{
     if (fFRS_WR != 0) {
    ///FRS
    ZERO_ARRAY(fFRS_Music_dE);
    ZERO_ARRAY(fFRS_Music_dE_corr);
    ZERO_ARRAY(fFRS_Music_E1);
    ZERO_ARRAY(fFRS_Music_E2);
    ZERO_ARRAY(fFRS_Music_T1);
    ZERO_ARRAY(fFRS_Music_T2);

  ZERO_ARRAY(fFRS_sci_l);
  ZERO_ARRAY(fFRS_sci_r);
  ZERO_ARRAY(fFRS_sci_e);
  ZERO_ARRAY(fFRS_sci_tx);
  ZERO_ARRAY(fFRS_sci_x);
  ZERO_ARRAY(fFRS_scaler);
  ZERO_ARRAY(fFRS_scaler_delta);




  fTRaw_vftx_21l=0;
  fTRaw_vftx_21r=0;
  fTRaw_vftx_22l=0;
  fTRaw_vftx_22r=0;
  fTRaw_vftx_41l=0;
  fTRaw_vftx_41r=0;
  fTRaw_vftx_41r=0;
  fTRaw_vftx_42l=0;
  fTRaw_vftx_42r=0;

   fFRS_sci_tof2=0;
   fFRS_ID_x2 = 0;
   fFRS_ID_y2 = 0;
   fFRS_ID_a2 = 0;
   fFRS_ID_b2 = 0;
   fFRS_ID_x4 = 0;
   fFRS_ID_y4 = 0;
   fFRS_ID_a4 = 0;
   fFRS_ID_b4 = 0;
//    fFRS_sci_dt_21l_21r = 0;
//    fFRS_sci_dt_41l_41r = 0;
//    fFRS_sci_dt_42l_42r = 0;
//    fFRS_sci_dt_43l_43r = 0;
//    fFRS_sci_dt_21l_41l = 0;
//    fFRS_sci_dt_21r_41r = 0;
//    fFRS_sci_dt_21l_42l = 0;
//    fFRS_sci_dt_21r_42r = 0;

    fFRS_beta = 0;
    fFRS_tof4121=0;
    fFRS_tof4221=0;
//    fFRS_beta3 = 0;
   fFRS_gamma = 0;
   fFRS_AoQ = 0;
   fFRS_AoQ_corr = 0;
   fFRS_z = 0;
   fFRS_z2 = 0;
   fFRS_dEdeg = 0;
   fFRS_dEdegoQ = 0;

  // fFRS_z_mhtdc= 0;
  // fFRS_z2_mhtdc= 0;
//   fFRS_dEdeg_mhtdc= 0;
   
   //fFRS_tof4221_mhtdc= 0;
   
    ZERO_ARRAY(fFRS_dEdeg_mhtdc);
    ZERO_ARRAY(fFRS_dEdegoQ_mhtdc);
    ZERO_ARRAY(fFRS_AoQ_mhtdc);
    ZERO_ARRAY(fFRS_AoQ_corr_mhtdc);
    ZERO_ARRAY(fFRS_beta_mhtdc);
    ZERO_ARRAY(fFRS_tof4121_mhtdc);
    ZERO_ARRAY(fFRS_tof4122_mhtdc);
    ZERO_ARRAY(fFRS_z_mhtdc);
    ZERO_ARRAY(fFRS_z2_mhtdc);



//   fFRS_z3 = 0;
   /*fFRS_timestamp = 0;
   fFRS_ts = 0;
   fFRS_ts2 = 0; */
    }
  fFRS_WR = 0;

   if (fAIDA_WR != 0) {
   ///Aida
    fAIDAHits = 0;
    AIDATime = 0;
    AIDAHits = 0;
    Aida.clear();
    fAidaScalers.clear();
      }
  fAIDA_WR =0;
  fevent_number = 0;
  fTrigger=0;
  memset(fProcID, -1, sizeof(fProcID));
///Fatima VME

   if (fFat_WR != 0) {
        fScalar_fired = -1;
        fScalar_ID = -1;
        fFat_TMCh1mult = 0;
        fFat_TMCh1mult = 0;

            ZERO_ARRAY(fFat_TDC_ID);
            ZERO_ARRAY(fFat_QDC_ID);
            ZERO_ARRAY(fFat_QDC_E);
            ZERO_ARRAY(fFat_QDC_E_Raw);
            ZERO_ARRAY(fFat_QDC_T_coarse);
            ZERO_ARRAY(fFat_QDC_T_fine);
            ZERO_ARRAY(fSC40);
            ZERO_ARRAY(fSC41);
            ZERO_ARRAY(fFat_TMCh1);
            ZERO_ARRAY(fFat_TMCh2);
            ZERO_ARRAY(fFat_bplastChanT);
            ZERO_ARRAY(fFat_TDC_Multiplicity);
            ZERO_ARRAY(fFat_TDC_Time);
            ZERO_ARRAY(fFat_TDC_Time_Raw);

            ZERO_ARRAY(fFat_TDC_Singles_ID);
            ZERO_ARRAY(fFat_TDC_Singles_t);
            ZERO_ARRAY(fFat_TDC_Singles_t_Raw);
            ZERO_ARRAY(fFat_QDC_Singles_ID);
            ZERO_ARRAY(fFat_QDC_Singles_E);
            ZERO_ARRAY(fFat_QDC_Singles_E_Raw);
            ZERO_ARRAY(fFat_QDC_Singles_t_coarse);
            ZERO_ARRAY(fFat_QDC_Singles_t_fine);
            fFat_tdcsinglescount=0;
            fFat_qdcsinglescount=0;


            fFat_WR = 0;
            fFat_QDC_Multiplicity = 0;
            fFat_SC40mult = 0;
            fFat_SC41mult = 0;
	        fFat_mult=0;
             }
  fFat_WR = 0;
      ///Germanium
//             fGe_Pileup = 0;


  if (fGe_WR != 0) {
        fGe_fired = 0;
        ZERO_ARRAY(fGe_Detector);
        ZERO_ARRAY(fGe_Crystal);
        ZERO_ARRAY(fGe_E);
        ZERO_ARRAY(fGe_T);
        ZERO_ARRAY(fGe_cfT);
        ZERO_ARRAY(fGe_Pileup);
        ZERO_ARRAY(fGe_Overflow);
       }
  fGe_WR = 0;
///Finger
   if (fFinger_WR != 0) {
        fFinger_WR = 0;
        ZERO_ARRAY(fFing_SC41_lead);
        ZERO_ARRAY(fFing_SC41_trail);
        ZERO_ARRAY(fFing_Strip_N);
        ZERO_ARRAY(fFing_Strip_N_LU);
        ZERO_ARRAY(fFing_Strip_N_TU);
        ZERO_ARRAY(fFing_Strip_N_LD);
        ZERO_ARRAY(fFing_Strip_N_TD);
        ZERO_ARRAY(fFing_PMT_Lead_N);
        ZERO_ARRAY(fFing_PMT_Trail_N);
        ZERO_ARRAY(fFing_Lead_Up);
        ZERO_ARRAY(fFing_Lead_Down);
        }
  fFinger_WR = 0;
        ///Fatima Tamex
   if (fFat_Tamex_WR != 0) {
        ZERO_ARRAY(fFat_Fast_Lead_N);
        ZERO_ARRAY(fFat_Slow_Lead_N);
        ZERO_ARRAY(fFat_Fast_Trail_N);
        ZERO_ARRAY(fFat_Slow_Trail_N);
        ZERO_ARRAY(fFat_Lead_Fast);
        ZERO_ARRAY(fFat_Lead_Slow);
        ZERO_ARRAY(fFat_Trail_Fast);
        ZERO_ARRAY(fFat_Trail_Slow);
        fFat_Tamex_WR=0;
        }
  fFat_Tamex_WR=0;
  
    ///bPlastic Twin Peaks
  if (fbPlas_WR != 0) {
    fbPlasDetNum_Fast=0;
    fbPlasDetNum_Slow=0;
    ZERO_ARRAY(fbPlas_FastChan);
    ZERO_ARRAY(fbPlas_SlowChan);
    ZERO_ARRAY(fbPlast_Fast_Lead_N);
    ZERO_ARRAY(fbPlast_Slow_Lead_N);
    ZERO_ARRAY(fbPlast_Fast_Trail_N);
    ZERO_ARRAY(fbPlast_Slow_Trail_N);
    ZERO_ARRAY(fbPlast_Fast_Lead);
    ZERO_ARRAY(fbPlast_Slow_Lead);
    ZERO_ARRAY(fbPlast_Fast_Trail);
    ZERO_ARRAY(fbPlast_Slow_Trail);
    
        ///bPlastic Tamex
    fbPlas_WR = 0;
    ZERO_ARRAY(fbPlasChan);
    fbPlasDetNum=-1;
    ZERO_ARRAY(fbPlas_PMT_Lead_N);
    ZERO_ARRAY(fbPlas_PMT_Trail_N);
    ZERO_ARRAY(fbPlas_Lead_PMT);
    ZERO_ARRAY(fbPlas_Trail_PMT);
        }
  fbPlas_WR = 0;
}
