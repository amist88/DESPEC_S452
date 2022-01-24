// $Id: TSCNCalEvent.cxx 755 2011-05-20 08:04:11Z linev $
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
#define ZERO_ARRAY(x) memset(x, 0, sizeof(x))

#include "EventAnlStore.h"
void EventAnlStore::Clear(Option_t *t)
{

      pAIDA_WR = 0;

      pAida.clear();
      pAidaScalers.clear();
      pEvent_Number=0;

    ZERO_ARRAY(pPrcID_Conv);
     if (pFRS_WR != 0)
   {
       pFRS_AoQ = 0;
       pFRS_ID_x2 = 0 ;
       pFRS_ID_y2 = 0 ;
       pFRS_ID_a2 = 0 ;
       pFRS_ID_b2 = 0 ;


       pFRS_ID_x4 = 0;
       pFRS_ID_y4 = 0;
       pFRS_ID_a4 = 0;
       pFRS_ID_b4 = 0;

       pFRS_z = 0;
       pFRS_z2 = 0;
       pFRS_dEdeg = 0;
       pFRS_dEdegoQ = 0;
       pFRS_beta=0;

    ZERO_ARRAY(pFRS_sci_l);
    ZERO_ARRAY(pFRS_sci_r);
    ZERO_ARRAY(pFRS_sci_e);
    ZERO_ARRAY(pFRS_sci_tx);
    ZERO_ARRAY(pFRS_sci_x);
    ZERO_ARRAY(pFRS_tpc_x);
    ZERO_ARRAY(pFRS_tpc_y);
    ZERO_ARRAY(pFRS_ZAoQ_pass);
    ZERO_ARRAY(pFRS_ZAoQ_pass_mhtdc);
    ZERO_ARRAY(pFRS_x2AoQ_pass);
    ZERO_ARRAY(pFRS_x2AoQ_pass_mhtdc);
    ZERO_ARRAY(pFRS_x4AoQ_pass);
    ZERO_ARRAY(pFRS_x4AoQ_pass_mhtdc);
    ZERO_ARRAY(pFRS_Z_Z2_pass);
    ZERO_ARRAY(pFRS_Z_Z2_pass_mhtdc);
    ZERO_ARRAY(pFRS_scaler);
    ZERO_ARRAY(pFRS_scaler_delta);
    ZERO_ARRAY(pFRS_Music_dE);
    
    ZERO_ARRAY(pFRS_dEdegZ1_pass);
    ZERO_ARRAY(pFRS_dEdegZ1_pass_mhtdc);

    ZERO_ARRAY(pFRS_AoQ_mhtdc);      
    ZERO_ARRAY(pFRS_z_mhtdc);
    ZERO_ARRAY(pFRS_z2_mhtdc);
    ZERO_ARRAY(pFRS_beta_mhtdc);
    ZERO_ARRAY(pFRS_dEdeg_mhtdc);
    ZERO_ARRAY(pFRS_dEdegoQ_mhtdc);



    pTRaw_vftx_21l=0;
    pTRaw_vftx_21r=0;
    pTRaw_vftx_22l=0;
    pTRaw_vftx_22r=0;
    pTRaw_vftx_41l=0;
    pTRaw_vftx_41r=0;
    pTRaw_vftx_42l=0;
    pTRaw_vftx_42r=0;
   }
     pFRS_WR = 0;
   // for(int i=0; i< 50; i++){
       //Fatima QDC ID
      if (pFAT_WR != 0) {
    ZERO_ARRAY(pFat_QDC_ID);
    //Fatima energy
    ZERO_ARRAY(pFat_QDC_E);
    ZERO_ARRAY(pFat_QDC_E_Raw);
    ZERO_ARRAY(pFat_QDC_T_coarse);
    ZERO_ARRAY(pFat_QDC_T_fine);
    //Fatimsa TDC ID
    ZERO_ARRAY(pFat_TDC_ID);
    //Fatima TDC time
    ZERO_ARRAY(pFat_TDC_T);
    ZERO_ARRAY(pFat_TDC_T_Raw);
    ZERO_ARRAY(pSC40);
    ZERO_ARRAY(pSC41);

    ZERO_ARRAY(pFat_TDC_Singles_ID);
    ZERO_ARRAY(pFat_TDC_Singles_t);
    ZERO_ARRAY(pFat_TDC_Singles_t_Raw);
    ZERO_ARRAY(pFat_QDC_Singles_t_coarse);
    ZERO_ARRAY(pFat_QDC_Singles_t_fine);
    ZERO_ARRAY(pFat_QDC_Singles_ID);
    ZERO_ARRAY(pFat_QDC_Singles_E);
    ZERO_ARRAY(pFat_QDC_Singles_E_Raw);

    pstdcmult=0;
    psqdcmult=0;
    pFat_TMCh1mult=0;
    pFat_TMCh2mult=0;
    ZERO_ARRAY(pFat_TMCh1);
    ZERO_ARRAY(pFat_TMCh2);
    ZERO_ARRAY(pFat_bplastChanT);
    }
   pFAT_WR = 0;

     if (pFAT_Tamex_WR != 0) {
    ZERO_ARRAY(pFat_Tamex_chan);
    pFat_LeadHits = 0;

    ZERO_ARRAY(pFat_Fast_ToTCalib);
    ZERO_ARRAY(pFat_Fast_LeadT);
    ZERO_ARRAY(pFat_Fast_TrailT);
    ZERO_ARRAY(pFat_Slow_ToTCalib);
    ZERO_ARRAY(pFat_Slow_LeadT);
    ZERO_ARRAY(pFat_Slow_TrailT);

      }
   pFAT_Tamex_WR = 0;


    if (pbPLAS_WR != 0) {
    pbPlas_LeadHits = 0;
    pbPlas_TrailHits = 0;
    pbPlas_LeadT_Avg = 0;
    pbPlasDetNum=0;

    ZERO_ARRAY(pbPlas_PMT_Lead_N);
    ZERO_ARRAY(pbPlas_PMT_Trail_N);
    ZERO_ARRAY(pbPlasChan);
    ZERO_ARRAY(pbPlas_ToTCalib);
    ZERO_ARRAY(pbPlas_LeadT);
    ZERO_ARRAY(pbPlas_TrailT);
    
     pbPlasDetNum_Fast=0;
      pbPlasDetNum_Slow=0;
      ZERO_ARRAY(pbPlas_FastChan);
      ZERO_ARRAY(pbPlas_SlowChan);
      ZERO_ARRAY(pbPlas_Fast_Lead_N);
      ZERO_ARRAY(pbPlas_Slow_Lead_N);
      ZERO_ARRAY(pbPlas_FastLeadT);
      ZERO_ARRAY(pbPlas_SlowLeadT);
      pbPlas_FastLeadHits=0;
      pbPlas_SlowLeadHits=0;
      ZERO_ARRAY(pbPlast_Fast_Trail_N);
      ZERO_ARRAY(pbPlast_Slow_Trail_N);
      ZERO_ARRAY(pbPlas_Fast_TrailT);
      ZERO_ARRAY(pbPlas_Slow_TrailT);
      ZERO_ARRAY(pbPlas_Fast_ToTCalib);
      ZERO_ARRAY(pbPlas_Slow_ToTCalib);
  }
   pbPLAS_WR = 0;
///      pFat_LeadT[i][j] = 0;
///         pFat_TrailT[i][j] = 0;

   if (pGe_WR != 0) {
    ZERO_ARRAY(pGe_T);
    ZERO_ARRAY(pGe_T_Aligned);
    ZERO_ARRAY(pGe_CF_T_Aligned);
    ZERO_ARRAY(pGe_CF_T);
    ZERO_ARRAY(pGe_E);
    ZERO_ARRAY(pGe_E_Raw);
    ZERO_ARRAY(pGe_EAddback);
    ZERO_ARRAY(pGePileUp);
    ZERO_ARRAY(pGeOverFlow);
      }
   pGe_WR = 0;
    //FINGER
  /*
    pFing_tot = 0;
    pFing_stripID = 0;
    pFing_maxtot= 0;
    pFing_maxtotchan= 0;*/

//    ZERO_ARRAY(pFing_lead_lead);
//     ZERO_ARRAY(pFing_Lead_Up);
//     ZERO_ARRAY(pFing_Lead_Down);
//     ZERO_ARRAY(pFing_Trail_Up);
//     ZERO_ARRAY(pFing_Trail_Down);

}
