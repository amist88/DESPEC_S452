// $Id: EventAnlProc.cxx 754 2011-05-18 11:04:52Z adamczew $
// Adapted for DESPEC by A.K.Mistry 2020
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
    //-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

// Uncomment this to align the AIDA ASICs with a pulser
//  Only needed if the ASICs didn't align properly
//#define AIDA_PULSER_ALIGN

#include "EventAnlProc.h"

#include <cstdlib>
#include <math.h>
#include <unordered_map>

#include "TH1.h"
#include "TH2.h"
#include "Riostream.h"
#include "TROOT.h"
#include "TFile.h"

#include "TGo4WinCond.h"
#include "TGo4Analysis.h"

#include "TGo4Picture.h"

#include "EventAnlStore.h"
#include "EventUnpackStore.h"

#include "TAidaConfiguration.h"
#include "TFRSParameter.h"
#include "DESPECAnalysis.h"

#define ABS(x)  ((x)>=0 ? (x):-(x))  // absolute_value(x)
///#define ZERO_ARRAY(x) memset(x, 0, sizeof(x)) //reset arrays to 0
//-----------------------------------------------------------
EventAnlProc::EventAnlProc() :
TGo4EventProcessor()
{
}
//-----------------------------------------------------------
EventAnlProc::EventAnlProc(const char* name) :
TGo4EventProcessor(name)
{
  //Clear up for AIDA
  implantEvents = 0;
  goodImplantEvents = 0;
  stoppedEvents = 0;
  decayEvents = 0;
  pulserEvents = 0;
  nonsenseEvents = 0;
  
  FRS_spill=0;
  


  cout << "**** EventAnlProc: Create" << endl;

  //checkTAMEXorVME();

   fCal = (CalibParameter*) GetParameter("CalibPar"); 
   fCorrel = (CorrelParameter*) GetParameter("CorrelPar"); 
   
   DESPECAnalysis* an = dynamic_cast<DESPECAnalysis*> (TGo4Analysis::Instance());
   frs_id = dynamic_cast<TIDParameter*> (an->GetParameter("IDPar"));
  
    for(int i=0;i<200;i++){
           FRS_WR_a[i]=0;
           FRS_WR_b[i]=0 ;
           Z1_shift_value[i]=0 ;
           Z2_shift_value[i] =0;
           /// AoQ_shift 
	   FRS_WR_i[i]=0;
           FRS_WR_j[i]=0 ;
           AoQ_shift_value[i]=0 ;
        }
        
        Fat_Shift_array=0;
//         for(int i=0;i<1500;i++){
//             FAT_DET_GFF[i]=0;
//             
//             for(int j=0;j<36;j++){
//                 FAT_WR_GFF_High[i][j]=0;
//                 FAT_WR_GFF_Low[i][j]=0;
//                 FAT_FACTOR_GFF[i][j]=0;
//             
//                 }
//         }
        for(int i=0;i<100;i++){
           
            
            
                FAT_WR_GFF_High[i]=0;
                FAT_WR_GFF_Low[i]=0;
                FAT_FACTOR_GFF[i]=0;
                FAT_COEFF_GFF[i]=0;
                
        }
        

   /// read_setup_parameters();
    get_used_systems();
    FRS_Gates();
    Fat_GainCorrection();
}
//-----------------------------------------------------------
EventAnlProc::~EventAnlProc()
{
  cout << "**** EventAnlProc: Delete" << endl;

}

void EventAnlProc::UserPostLoop()
{
  TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
  if (!conf->ShowStats()) return;
  std::cout << "AIDA Analysis Statistics" << std::endl;
  std::cout << "Incoming Implant Events: " << implantEvents << std::endl;
  std::cout << "Good Implant Events    : " << goodImplantEvents << " (" << (100. * goodImplantEvents / implantEvents) << "%)" << std::endl;
  std::cout << "Stopped Implant Events : " << stoppedEvents << " (" << (100. * stoppedEvents / implantEvents) << "%)" << std::endl;
}

//-----------------------------------------------------------


Bool_t EventAnlProc::BuildEvent(TGo4EventElement* dest)
{
     for(int i=0; i<7; i++){
        PrcID_Conv[i]=-1;
        }

  Bool_t isValid=kFALSE; // validity of output event

  EventUnpackStore* pInput  = (EventUnpackStore*) GetInputEvent();
  EventAnlStore* pOutput = (EventAnlStore*) dest;

//   pAida.Implants.clear();
//   pAida.Decays.clear();


  if((pInput==0) || !pInput->IsValid()){ // input invalid
    pOutput->SetValid(isValid); // invalid
    return isValid; // must be same is for SetValid
  }
  isValid=kTRUE;

   ///general inputs from the unpacker
    event_number = pInput->fevent_number;
    pOutput->pOnSpill = FRS_spill;
    pOutput->pTrigger = pInput->fTrigger;
    pOutput->pEvent_Number = event_number;
//     VMEorTAMEX_bPlas = VME_TAMEX_bPlas;
//     VMEorTAMEX_fatima = VME_TAMEX_Fatima;
//     VMEandTAMEX_fatima = VME_AND_TAMEX_Fatima;


  for (int i = 0; i<7; i++){
      if(pInput->fProcID[i]>-1){
      PrcID_Conv[i] = pInput->fProcID[i];
      pOutput->pPrcID_Conv[i] = pInput->fProcID[i];
    }

  }
 

   static bool create =false;
  //Create histograms
  if (!create)
  {
    Make_WR_Histos();
    if(Used_Systems[0])  Make_FRS_Histos();
    if(Used_Systems[1])  Make_Aida_Histos();
    if(Used_Systems[2])  Make_Plastic_Tamex_Histos();
    if(Used_Systems[3]) Make_Fatima_Histos();
    if(Used_Systems[4]) Make_Fatima_Tamex_Histos();
    if(Used_Systems[5]) Make_Germanium_Histos();
    //if (Used_Systems[6]) Make_Finger_Histos();
       
        }

        create = true;
        Do_WR_Histos(pInput);
        Fat_TimeCorrection(pInput);
                 /** Now extract the data from the stored Unpacker array (root tree)**/
    ///--------------------------------------/**FRS Input**/------------------------------------------///
 
    // if (PrcID_Conv[0]==0 && Used_Systems[0]==1){
       //  cout<<"ANL USED FRS " << endl;
       
      if (PrcID_Conv[0]==0 && Used_Systems[0]==1){
        
          pOutput->pFRS_WR = pInput->fFRS_WR;
        ///MUSIC
//        for(int i =0; i<2; ++i){
//             FRS_dE[i] = pInput->fFRS_Music_dE[i];
//             FRS_dE_cor[i] = pInput->fFRS_Music_dE_corr[i];
//            }
       
          ///SCI
        for(int l=0;l<12;++l){
          
           FRS_sci_l[l] = pInput->fFRS_sci_l[l];
           //if(pInput->fFRS_sci_l[l]!=0)cout<<"pInput->fFRS_sci_l[l] " << pInput->fFRS_sci_l[l] <<" l " << l << endl;
           FRS_sci_r[l] = pInput->fFRS_sci_r[l];
           FRS_sci_e[l] = pInput->fFRS_sci_e[l];
           FRS_sci_tx[l] = pInput->fFRS_sci_tx[l];
           FRS_sci_x[l] = pInput->fFRS_sci_x[l];
           
        }
        ///VFTX
        pOutput->pTRaw_vftx_21l = pInput->fTRaw_vftx_21l;
        pOutput->pTRaw_vftx_21r = pInput->fTRaw_vftx_21r;
        pOutput->pTRaw_vftx_22l = pInput->fTRaw_vftx_22l;
        pOutput->pTRaw_vftx_22r = pInput->fTRaw_vftx_22r;
        pOutput->pTRaw_vftx_41l = pInput->fTRaw_vftx_41l;
        pOutput->pTRaw_vftx_41r = pInput->fTRaw_vftx_41r;
        pOutput->pTRaw_vftx_42l = pInput->fTRaw_vftx_42l;
        pOutput->pTRaw_vftx_42r = pInput->fTRaw_vftx_42r;
        for(int i = 0; i < 7; i++)
        {
          pOutput->pFRS_tpc_x[i] = pInput->fFRS_TPC_x[i];
          pOutput->pFRS_tpc_y[i] = pInput->fFRS_TPC_y[i];
        }
            for (int i = 0; i < 64; i++)
        {
          pOutput->pFRS_scaler[i] = pInput->fFRS_scaler[i];
          pOutput->pFRS_scaler_delta[i] = pInput->fFRS_scaler_delta[i];
        }
        if (pOutput->pFRS_scaler_delta[8] > 0)
        {
          FRS_spill = true;
          pOutput->pOnSpill = true;
	 // cout<<"OnSpill " <<pOutput->pOnSpill << endl;
        }
        if (pOutput->pFRS_scaler_delta[9] > 0)
        {
          FRS_spill = false;
          pOutput->pOnSpill = false;
	  // cout<<"Offspill " <<pOutput->pOnSpill << endl;
        }
        
      
        ///SCI TOF
       // FRS_sci_tofll2 = pInput->fFRS_sci_tofll2;
       // FRS_sci_tofll3 = pInput->fFRS_sci_tofll3;
        //FRS_sci_tof2 = pInput->fFRS_sci_tof2;
       // FRS_sci_tofrr2 = pInput->fFRS_sci_tofrr2;
        //FRS_sci_tofrr3 = pInput->fFRS_sci_tofrr3;
      //  FRS_sci_tof3 = pInput->fFRS_sci_tof3;
        ///ID 2 4
        FRS_ID_x2 = pInput->fFRS_ID_x2;
        FRS_ID_y2 = pInput->fFRS_ID_y2;
        FRS_ID_a2 = pInput->fFRS_ID_a2;
        FRS_ID_b2 = pInput->fFRS_ID_b2;

        FRS_ID_x4 = pInput->fFRS_ID_x4;
        FRS_ID_y4 = pInput->fFRS_ID_y4;
        FRS_ID_a4 = pInput->fFRS_ID_a4;
        FRS_ID_b4 = pInput->fFRS_ID_b4;
            ///SCI dT
//         FRS_sci_dt_21l_21r = pInput->fFRS_sci_dt_21l_21r;
//         FRS_sci_dt_41l_41r = pInput->fFRS_sci_dt_41l_41r;
//         FRS_sci_dt_42l_42r = pInput->fFRS_sci_dt_42l_42r;
//         FRS_sci_dt_43l_43r = pInput->fFRS_sci_dt_43l_43r;
//
//         FRS_sci_dt_21l_41l = pInput->fFRS_sci_dt_21l_41l;
//         FRS_sci_dt_21r_41r = pInput->fFRS_sci_dt_21r_41r;
//
//         FRS_sci_dt_21l_42l = pInput->fFRS_sci_dt_21l_42l;
//         FRS_sci_dt_21r_42r = pInput->fFRS_sci_dt_21r_42r;
            ///ID Beta Rho
//         for(int i =0; i<2; ++i){
//        // FRS_ID_brho[i] = pInput->fFRS_ID_brho[i];
//       //  FRS_ID_rho[i] = pInput->fFRS_ID_rho[i];
//         }
       
//         FRS_beta3 = pInput->fFRS_beta3;
      //  FRS_gamma  = pInput->fFRS_gamma;
            ///ID Z AoQ
        if(MHTDC_OR_TAC==0){
        FRS_AoQ = pInput->fFRS_AoQ;
        FRS_AoQ_corr = pInput->fFRS_AoQ_corr;
        FRS_z = pInput->fFRS_z;
        FRS_z2 = pInput->fFRS_z2;
        FRS_dEdeg = pInput->fFRS_dEdeg;
        FRS_dEdegoQ = pInput->fFRS_dEdegoQ;
        FRS_beta = pInput->fFRS_beta;
        }
        else if (MHTDC_OR_TAC==1){
        FRS_AoQ = pInput->fFRS_AoQ_mhtdc;
        FRS_AoQ_corr = pInput->fFRS_AoQ_corr_mhtdc;
        FRS_z = pInput->fFRS_z_mhtdc;
        FRS_z2 = pInput->fFRS_z2_mhtdc;
        FRS_dEdeg = pInput->fFRS_dEdeg_mhtdc;
        FRS_dEdegoQ = pInput->fFRS_dEdegoQ_mhtdc;
        FRS_beta = pInput->fFRS_beta_mhtdc;
        }
        else {cout<<"TOF vs TAC Parameter not set correctly in DESPEC_Setup_File.h"<<endl; exit(0);}
        FRS_AoQ_mhtdc = pInput->fFRS_AoQ_mhtdc;
        FRS_AoQ_corr_mhtdc = pInput->fFRS_AoQ_corr_mhtdc;
        FRS_z_mhtdc = pInput->fFRS_z_mhtdc;
        FRS_z2_mhtdc = pInput->fFRS_z2_mhtdc;
        FRS_dEdeg_mhtdc = pInput->fFRS_dEdeg_mhtdc;
        FRS_dEdegoQ_mhtdc = pInput->fFRS_dEdegoQ_mhtdc;
        FRS_beta_mhtdc = pInput->fFRS_beta_mhtdc;
       // FRS_z3 = pInput->fFRS_z3;
            ///ID Timestamp
       // FRS_timestamp = pInput->fFRS_timestamp;
//         FRS_ts = pInput->fFRS_ts;
//         FRS_ts2 = pInput->fFRS_ts2;
 // if(pOutput->pEvent_Number==42715 ){       }
  Do_FRS_Histos(pOutput);
            }


   ///-------------------------------- /**AIDA Input**/ --------------------------------///
      //  if (Used_Systems[1]&&  PrcID_Conv[1]==1) {ProcessAida(pInput);}
      if (Used_Systems[1]&&  PrcID_Conv[1]==1){
        ProcessAida(pInput, pOutput);
        Aida_Fired = 0;
        Aida_Fired = pInput->fAIDAHits;
        pOutput->pAidaScalers = pInput->fAidaScalers;
      }
   ///-------------------------------- /**bPlastic VME Input**/ --------------------------------///
        ///Disabled A.M. 11.12.19
       
///--------------------------------------/**bPlastic TAMEX Input**/------------------------------------------///
        
       
  if (PrcID_Conv[2] ==2 && Used_Systems[2]==1){

      for(int i=0; i<bPLASTIC_TAMEX_HITS; i++){
         bPlas_RefCh0_Det1[i] =0;
         bPlas_RefCh0_Det2[i] =0;
        // bPlas_RefCh0_Det3[i] =0;
         }
          for (int j = 0; j < bPLASTIC_CHAN_PER_DET; j++)    
                {   
                    for(int k=0; k<bPLASTIC_TAMEX_HITS;k++){    
                        lead_lead_bplas_Ref1[j][k]=0;  
                        lead_lead_bplas_Ref2[j][k]=0;  
                        lead_lead_fat_Ref0[j][k]=0;   
                    }
                }
                 
         for (int i=1; i<4; i++){
            for (int j = 0; j < bPLASTIC_CHAN_PER_DET; j++)    
                {   
                    for(int k=0; k<bPLASTIC_TAMEX_HITS;k++){    
                 SC41L_ANA_lead_bPlas[i][j][k] = 0;    
                 SC41R_ANA_lead_bPlas[i][j][k] = 0;    
                 SC41L_DIG_lead_bPlas[i][j][k] = 0;    
                 SC41R_DIG_lead_bPlas[i][j][k] = 0;    
                    }
                }   
            }
  
                pOutput->pbPLAS_WR = pInput->fbPlas_WR;
                
                bPlas_TAM_FATTAM = pInput->fbPlas_Lead_PMT[bPLASTIC_ADDITIONAL_CH_MOD][bPLASTIC_FATTAMEX][0];
                bPlas_TAM_FATVME = pInput->fbPlas_Lead_PMT[bPLASTIC_ADDITIONAL_CH_MOD][bPLASTIC_FATVME][0];
                bPlas_TAM_SC41L_DIG = pInput->fbPlas_Lead_PMT[bPLASTIC_ADDITIONAL_CH_MOD][SC41L_bPLASTIC][0];
                bPlas_TAM_SC41R_DIG = pInput->fbPlas_Lead_PMT[bPLASTIC_ADDITIONAL_CH_MOD][SC41R_bPLASTIC][0];

       ///bPlas_AND_Coinc[j] = pInput->fFat_Lead_PMT[9][j];
       
  // if(pOutput->pEvent_Number==100598) 
     for(int i=1; i<4; i++){ ///Detector number
                 for (int j = 0; j <bPLASTIC_CHAN_PER_DET ; j++){  ///Channel number 
                     
                for(int k=0; k<bPLASTIC_TAMEX_HITS; k++){ 
                    //Fat_RefCh[j] = pInput->fFat_Lead_PMT[1][j]; 
                    bPlas_RefCh0_Det1[k] = pInput->fbPlas_Lead_PMT[1][bPlastRefCh_Det1][k];
                    bPlas_RefCh0_Det2[k] = pInput->fbPlas_Lead_PMT[2][bPlastRefCh_Det2][k];
//                     bPlas_RefCh0_Det3[k] = pInput->fbPlas_Lead_PMT[3][bPlastRefCh_Det3][k];
            
                        }      
                    }
              }
  Do_Plastic_Tamex_Histos(pInput,pOutput);
    
   }
  
  ///--------------------------------------/**Fatima TAMEX Input**/------------------------------------------///
   if (PrcID_Conv[4] ==4 ){
      Do_Fatima_Tamex_Histos(pInput,pOutput);  
        pOutput->pFAT_Tamex_WR = pInput->fFat_Tamex_WR;
        
        Fat_TAM_SC41L_ANA = pInput->fFat_Lead_Fast[FATIMA_TAMEX_SC41L][0];
        Fat_TAM_SC41R_ANA = pInput->fFat_Lead_Fast[FATIMA_TAMEX_SC41R][0];
//         Fat_TAM_SC41L_DIG = pInput->fFat_Lead_PMT[50][0];
//         Fat_TAM_SC41R_DIG = pInput->fFat_Lead_PMT[51][0];
   }

   ///--------------------------------------/**Fatima VME Input**/------------------------------------------///
  
        SC40mult = 0;
        SC41mult = 0;
        Fatmult = 0;
        Fat_Cha_Ref_TDC = 0;
        Fat_WR = 0;
        stdcmult = 0;
        sqdcmult = 0;
        
       //bplast chans in fatima VME
        for(int i=0; i<6; i++) Fat_VME_bPlast[i] =0;
    for(int i=0; i<FAT_VME_MAX_MULTI; i++){
         //Fat_QDC_E[i] = 0;
         //Fat_QDC_T[i] =0;
         SC40[i] = 0;
         SC41[i] = 0;
         Fat_TDC_ID[i] = -2;
         Fat_QDC_ID[i] = -1;
         Fat_TDC_T[i] = 0;
         
         Fat_TDC_Singles_ID[i] = -2;
         Fat_QDC_Singles_ID[i] = -1;
         Fat_QDC_Singles_E[i] = 0;
         Fat_QDC_Singles_t_coarse[i] = 0;
         Fat_QDC_Singles_t_fine[i] = 0;
         Fat_TDC_Singles_t[i] = 0;      
         
}//End for initialise arrays

  if ( PrcID_Conv[3]==3 ){
      
    Fat_WR = pInput->fFat_WR;

    Fatmult =  pInput->fFat_mult;
    
    //cout << " anl proc fat mult " << Fatmult << endl; 
  
    
if(Fatmult > 0){

    //QDC
    for (int i = 0; i<Fatmult; i++){
      Fat_QDC_ID[i] = pInput->fFat_QDC_ID[i];
      Fat_QDC_E[i] = pInput->fFat_QDC_E[i];
     }//End QDC for loop
     
     

    //TDC
      
    for (int i = 0; i<Fatmult; i++){
      Fat_TDC_ID[i] = pInput->fFat_TDC_ID[i];
      Fat_TDC_T[i] = pInput->fFat_TDC_Time[i];
       if(Fat_TDC_ID[i]==FAT_TDC_REF_CHANNEL)Fat_Cha_Ref_TDC = Fat_TDC_T[i]; 
    }//End TDC for loop
}
//                  INPUTS

    for(int i = 0; i < 6; i++){
        Fat_VME_bPlast[i] = pInput->fFat_bplastChanT[i];
    }

      SC40mult =  pInput->fFat_SC40mult;
      SC41mult =  pInput->fFat_SC41mult; 
 
        for(int i = 0; i < SC40mult; i++){
            
        SC40[i] = pInput->fSC40[i]; 
            
        }//End sc41 for fill
        
        for(int i = 0; i < SC41mult; i++){
            
            SC41[i] = pInput->fSC41[i]; 
            
        }//End sc41 for fill
       

		//Inputting singles TDC and QDC hits
        stdcmult = pInput->fFat_tdcsinglescount;
        sqdcmult = pInput->fFat_qdcsinglescount;

       for (int i = 0; i<stdcmult; i++){
        Fat_TDC_Singles_t[i] = pInput->fFat_TDC_Singles_t[i];
        Fat_TDC_Singles_ID[i] = pInput->fFat_TDC_Singles_ID[i];
       }

       for (int i = 0; i<sqdcmult; i++){
        Fat_QDC_Singles_E[i] = pInput->fFat_QDC_Singles_E[i];
        Fat_QDC_Singles_ID[i] = pInput->fFat_QDC_Singles_ID[i];
        Fat_QDC_Singles_t_coarse[i] = pInput->fFat_QDC_Singles_t_coarse[i];
        Fat_QDC_Singles_t_fine[i] = pInput->fFat_QDC_Singles_t_fine[i];
       }
        Do_Fatima_Histos(pInput, pOutput);
  }//End of proc ID


  ///--------------------------------------/**Germanium Input**/------------------------------------------///
       GeFired = -1;
       RefTGe=0;
       //Ge_WR = 0;
       for(int g = 0; g<Germanium_MAX_HITS; g++){
          GeDet[g] = -1;
          GeCrys[g] = -1;
          GeE[g] = -1;
          GeE_Cal[g] = -1;
          GeT[g] =-1;
          GePileUp[g] = false;
          GeOverFlow[g] = false;
          Ge_Talign[g]=0;
       }
    
       if ( PrcID_Conv[5]==5){
        GeFired =  pInput->fGe_fired;
    //    GePileup = pInput->fGe_Pileup;
        Ge_WR = pInput->fGe_WR;
     
        for (int i = 0; i<GeFired; i++)
        {
          GeDet[i] = pInput->fGe_Detector[i];
          GeCrys[i] = pInput->fGe_Crystal[i];
          GePileUp[i] = pInput->fGe_Pileup[i];
          GeOverFlow[i] = pInput->fGe_Overflow[i];
          GeE[i] = pInput->fGe_E[i];
          GeEventT[i]=pInput->fGe_Event_T[i];
          GeT[i] = pInput->fGe_T[i];
          GeCF_T[i] = pInput->fGe_cfT[i];
	  
          // Maybe keep this for auto calibration program purposes
          int id = GeDet[i] * Germanium_CRYSTALS + GeCrys[i];
	  if(id<32){
          GeE_Cal[i] = (fCal->AGe[id]* pow( GeE[i],2) + fCal->BGe[id]*  GeE[i] + fCal->CGe[id]);
          
        //  cout<<"1GeE_Cal[i] " << GeE_Cal[i] <<" i " << i << " GeDet[i] " <<GeDet[i] << " GeCrys[i] " <<GeCrys[i]<< endl;
	  }
            // int id_Ge = det * Germanium_CRYSTALS +  crys;
    
     if(id==1) {
         RefTGe=GeT[i];
         RefCFDGe=GeCF_T[i];
     }
    
      Ge_Talign[i] = (GeT[i]-fCal->Ge_T_align_par[id]);
     
             pOutput->pGe_T_Aligned[GeDet[i]][GeCrys[i]]=Ge_Talign[i];
    //cout<<"1event "<< event_number<<"GeDet[i] " << GeDet[i] << " GeCrys[i] " << GeCrys[i]<< " Ge_Talign[i] " << Ge_Talign[i] <<" GeT[i] " << GeT[i]<<" CalGe_T_align_par[id] " <<fCal->Ge_T_align_par[id] << " id " << id  << " i " << i << endl;
    
                   //Do the CFD time alignment (detector vs all)
              Ge_cfd_Talign[i] = GeCF_T[i]+fCal->Ge_cfd_align_par[id];
              pOutput->pGe_CF_T_Aligned[GeDet[i]][GeCrys[i]] = Ge_cfd_Talign[i];
        }
 
            Do_Germanium_Histos(pOutput);
      }

 ///--------------------------------------/**Finger Input**/------------------------------------------///
      
  pOutput->SetValid(isValid);
  return isValid;

 }  //End of BuildEvent




/**----------------------------------------------------------------------------------------------**/
 /**--------------------------------------    White Rabbit   ---------------------------------------------**/
 /**----------------------------------------------------------------------------------------------**/
 void EventAnlProc::Make_WR_Histos(){
//Added on 01/03 from MP to check the subsystems' deadtime
   hFat_deadtime = MakeTH1('I',"WR/DeadTime/Fat_deadtime","Dead Time Fatima VME", 500, 0, 500,"WR dT(Fatima VME)[us]", "Counts");
   
   hFatTAM_deadtime = MakeTH1('I',"WR/DeadTime/FatTAM_deadtime","Dead Time Fatima TAMEX", 500, 0, 500,"WR dT(Fatima TAMEX)[us]", "Counts");
   
   hGe_deadtime = MakeTH1('I',"WR/DeadTime/HPGe_deadtime","Dead Time Germanium", 500, 0, 500,"WR dT(Germanium)[us]", "Counts");
   
   hbPlast_deadtime = MakeTH1('I',"WR/DeadTime/bPlast_deadtime","Dead Time bPlastic", 500, 0, 500,"WR dT(bPlastic)[us]", "Counts");
   
   hFRS_deadtime = MakeTH1('I',"WR/DeadTime/FRS_deadtime","Dead Time FRS", 500, 0, 500,"WR dT(FRS)[us]", "Counts");
     
   hbPlas_Fat_WRdT = MakeTH1('I',"WR/bPlast-FatimaVME_dT","White Rabbit bPlast-Fatima VME",10000,-10000,10000,"WR dT(bPlast-Fatima VME)[ns]", "Counts");
   
   hbPlas_Ge_WRdT = MakeTH1('I',"WR/bPlast-Germanium_dT","White Rabbit bPlast-Germanium",10000,-10000,10000,"WR dT(bPlast-Germanium)[ns]", "Counts");
   
   hFat_Ge_WRdT = MakeTH1('I',"WR/FatimaVME-Germanium_dT","White Rabbit Fatima-Germanium",10000,-10000,10000,"WR dT(Fatima-Germanium)Time[ns]", "Counts");
   
   hFatTAM_Ge_WRdT = MakeTH1('I',"WR/FatimaTAMEX-Germanium_dT","White Rabbit Fatima TAMEX-Germanium",10000,-10000,10000,"WR dT(Fatima Tamex-Germanium)Time[ns]", "Counts");

   hFRS_Ge_WRdT =  MakeTH1('I',"WR/Germanium-FRS_dT","White Rabbit FRS WR -Germanium WR ",10000,-10000,10000,"WR dT(Germanium-FRS)[ns]", "Counts");
   
   hFRS_bPlas_WRdT = MakeTH1('I',"WR/bPlast-FRS_dT","White Rabbit FRS_bPlas",10000,-10000,10000,"WR dT(bPlast-FRS)[ns]", "Counts");
   
   hFRS_FatVME_WRdT = MakeTH1('I',"WR/FatimaVME-FRS_dT","White Rabbit FRS_Fatima VME",10000,-10000,10000,"WR dT(Fatima VME-FRS)[ns]", "Counts");
   
   hFRS_FatTAM_WRdT = MakeTH1('I',"WR/FRS-FatimaTAMEX_dT","White Rabbit FRS_Fatima Tamex ",10000,-10000,10000,"WR dT(Fatima TAMEX-FRS)[ns]", "Counts");
   
   hFRS_FatVME_FatTAM = MakeTH1('I',"WR/FatimaVME-FatimaTAMEX_dT","White Rabbit dT Fatima VME - Fatima Tamex ",10000,-10000,10000,"WR dT(Fatima VME-Fatima TAMEX)[ns]", "Counts");

   hbPlast_FatTAM = MakeTH1('I',"WR/bPlast-FatimaTAMEX_dT","White Rabbit dT bPlast - Fatima Tamex ",10000,-10000,10000,"WR dT(bPlast-Fatima TAMEX)[ns]", "Counts");


}
 void EventAnlProc::Do_WR_Histos(EventUnpackStore* pInput){
     /// FATIMA DEAD TIME
       if (pInput->fFat_WR > 0) {
       
  
        if (lastFatWR == 0) {
          lastFatWR = pInput->fFat_WR;
        } else {
     
          hFat_deadtime->Fill((long long)(pInput->fFat_WR - lastFatWR)/1000);
          lastFatWR = pInput->fFat_WR;
        }
      }
      
 /// FATIMA TAMEX DEAD TIME
       if (pInput->fFat_Tamex_WR > 0) {
       
  
        if (lastFatTAMWR == 0) {
          lastFatTAMWR = pInput->fFat_Tamex_WR;
        } else {
    
          hFatTAM_deadtime->Fill((long long)(pInput->fFat_Tamex_WR - lastFatTAMWR)/1000);
          lastFatTAMWR = pInput->fFat_Tamex_WR;
        }
      }

 /// Germanium DEAD TIME
       if (pInput->fGe_WR > 0) {
       
        if (lastGeWR == 0) {
          lastGeWR = pInput->fGe_WR;
        } else {
    
          hGe_deadtime->Fill((long long)(pInput->fGe_WR - lastGeWR)/1000);
          lastGeWR = pInput->fGe_WR;
        }
      }
      
      /// bPlastic DEAD TIME
       if (pInput->fbPlas_WR > 0) {

        if (lastbPlastWR == 0) {
          lastbPlastWR = pInput->fbPlas_WR;
        } else {
    
          hbPlast_deadtime->Fill((long long)(pInput->fbPlas_WR - lastbPlastWR)/1000);
          lastbPlastWR = pInput->fbPlas_WR;
        }
      }
      
       /// FRS DEAD TIME
       if (pInput->fFRS_WR > 0) {

        if (lastFRSWR == 0) {
          lastFRSWR = pInput->fFRS_WR;
        } else {
    
          hFRS_deadtime->Fill((long long)(pInput->fFRS_WR - lastFRSWR)/1000);
          lastFRSWR = pInput->fFRS_WR;
        }
      }
 
 ///Aida deadtime in Correl proc
 
 
     ///WR dT(bPlas-Fatima)
  if(pInput->fFat_WR>0 && pInput->fbPlas_WR>0)hbPlas_Fat_WRdT->Fill(pInput->fbPlas_WR -pInput->fFat_WR);
  
    ///WR dT(bPlas-Germanium)
  if(pInput->fGe_WR>0 && pInput->fbPlas_WR>0)hbPlas_Ge_WRdT->Fill(pInput->fbPlas_WR - pInput->fGe_WR);
  
   ///WR dT(Fatima VME -Germanium)
  if(pInput->fGe_WR>0 && pInput->fFat_WR>0)hFat_Ge_WRdT->Fill(pInput->fFat_WR - pInput->fGe_WR);
  
   ///WR dT(Fatima TAMEX -Germanium)
  if(pInput->fGe_WR>0 && pInput->fFat_Tamex_WR>0)hFatTAM_Ge_WRdT->Fill(pInput->fFat_Tamex_WR - pInput->fGe_WR);
  
   ///WR dT(Germanium - FRS)
  if(pInput->fGe_WR>0 && pInput->fFRS_WR>0)hFRS_Ge_WRdT->Fill(pInput->fGe_WR - pInput->fFRS_WR );
  
  ///WR dT(Fatima VME - FRS ) 
  if(pInput->fFat_WR>0 && pInput->fFRS_WR>0)hFRS_FatVME_WRdT->Fill(pInput->fFat_WR-pInput->fFRS_WR );
  
  ///WR dT(FRS - Fatima TAMEX) 
  if(pInput->fFat_Tamex_WR>0 && pInput->fFRS_WR>0)hFRS_FatTAM_WRdT->Fill( pInput->fFat_Tamex_WR-pInput->fFRS_WR );
  
  ///WR dT(Fatima VME - Fatima TAMEX) 
  if(pInput->fFat_Tamex_WR>0 && pInput->fFat_WR>0)hFRS_FatVME_FatTAM->Fill(pInput->fFat_WR - pInput->fFat_Tamex_WR);
  
   ///WR dT(bPlast - Fatima TAMEX) 
  if(pInput->fFat_Tamex_WR>0 && pInput->fbPlas_WR>0)hbPlast_FatTAM->Fill(pInput->fbPlas_WR - pInput->fFat_Tamex_WR);
  
    ///WR dT(bPlast- FRS)
  if(pInput->fbPlas_WR>0 && pInput->fFRS_WR>0)hFRS_bPlas_WRdT->Fill(pInput->fbPlas_WR-pInput->fFRS_WR);
 
 }


/**----------------------------------------------------------------------------------------------**/
 /**--------------------------------------    FRS   ---------------------------------------------**/
 /**----------------------------------------------------------------------------------------------**/
void EventAnlProc::Make_FRS_Histos(){
     
    hID_x2AoQ = MakeTH2('D',"FRS/ID/ID_x2AoQ", "X2 vs A/Q",1500,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "X at S2 [mm]");
//     ('F', Form("AIDA/Implants/DSSD%d_implants_y_ey", i+1), Form("DSSD %d Ey vs Y position", i+1), 128, 0, 128, 1000, 0, 10000, "Y Strip", "Y Energy");
//     MakeTH2('D', "bPlastic/FIMP_ToT_Correlation_Comb1", "ToT vs ToT for 2 FIMP channels, combination 1",500,0,100000,500,0,100000);
    
    hID_x4AoQ = MakeTH2('D',"FRS/ID/ID_x4AoQ", "X4 vs A/Q",1500,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "X at S4 [mm]");
    
    hID_x4AoQ_zsame = MakeTH2('D',"FRS/ID/ID_x4AoQ_zsame","X4 vs A/Q Zsame", 1500,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 300,-150.,100.,"A/Q s2-s4", "X at S4 [mm]");

    hID_Z_AoQ = MakeTH2('D',"FRS/ID/ID_Z1_AoQ", "Z1 vs A/Q",1500,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 1000,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", "Z1 s2-s4");
    
    hID_Z1_vs_T = MakeTH2('D',"FRS/ID/ID_Z1_Time", "Z1 vs Time",1240,16600,29000, 1500,frs_id->min_z_plot,frs_id->max_z_plot,"Time (/10 mins)", "Z1 s2-s4");
    
   // hID_AoQ_mhtdc_T = MakeTH2('D',"FRS/ID/ID_AoQmhtdc_Time", "AoQ mhtdc vs Time",1200,17000,29000,1500,frs_id->min_aoq_plot,frs_id->max_aoq_plot,"Time (/10 mins)", "AoQ mhtdc s2-s4");
    
    //hID_Z_AoQ = MakeTH2('D',"FRS/ID/ID_Z1_AoQ", "Z1 vs A/Q",1500,6,7, 1000,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", "Z1 s2-s4");
    
    hID_Z_AoQ_zsame = MakeTH2('D',"FRS/ID/ID_Z1_AoQ_zsame","Z1 vs Z2: mod(Z1-Z2)<0.4", 1500,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 1000,frs_id->min_z_plot,frs_id->max_z_plot,"Z1==Z2 A/Q s2-s4", "Z s2-s4");
    

    
    hID_Z_AoQ_corr = MakeTH2('D',"FRS/ID/ID_Z1_AoQ_S2-S4corr", "",1500,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 1000,frs_id->min_z_plot,frs_id->max_z_plot, "A/Q s2-s4", "Z s2-s4");
    
    //High-Z charge state
    hdEdegoQ_Z = MakeTH2('D',"FRS/ID/ID_dEdegoQZ1","dE in s2 degrader/Q vs. Z1", 1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 0.1,0.8, "Z from MUSIC41", "dE(S2deg)/Q [a.u.]");
    
    hdEdeg_Z   = MakeTH2('D',"FRS/ID/ID_dEdeg_Z1" ,"dE in s2 degrader vs. Z1" , 1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,70., "Z from MUSIC41", "dE(S2deg) [a.u.]");
   
    
    hID_Z_Z2 = MakeTH2('D',"FRS/ID/ID_Z1_Z2","Z1 vs. Z2", 2000,frs_id->min_z_plot,frs_id->max_z_plot, 400,frs_id->min_z_plot,frs_id->max_z_plot,"Z1", "Z2");
    
    
    int num_ID_x2AoQ = {MAX_FRS_GATE};
    int num_ID_x4AoQ = {MAX_FRS_GATE};
    int num_ID_Z_Z2 = {MAX_FRS_GATE};
    int num_ID_Z_AoQ = {MAX_FRS_GATE};
    int num_ID_dEdeg_Z1{MAX_FRS_GATE};
     Float_t init_ID_x2AoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints][2];
     Float_t init_ID_x4AoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints][2];
     Float_t init_ID_Z_Z2[MAX_FRS_GATE][MAX_FRS_PolyPoints][2];
     Float_t init_ID_Z_AoQ[MAX_FRS_GATE][MAX_FRS_PolyPoints][2];
     Float_t init_dEdeg_Z1[MAX_FRS_GATE][MAX_FRS_PolyPoints][2];
     ///FRS gates initialisation
   for(int i=0; i<MAX_FRS_GATE; i++){
       for(int j=0; j<MAX_FRS_PolyPoints; j++){
        init_ID_x2AoQ[i][j][0] = XX2_AoQ[i][j];
        init_ID_x2AoQ[i][j][1] = YX2_AoQ[i][j];
        init_ID_x4AoQ[i][j][0] = XX4_AoQ[i][j];
        init_ID_x4AoQ[i][j][1] = YX4_AoQ[i][j];
        init_ID_Z_Z2[i][j][0] = X_ZZ2[i][j];
        init_ID_Z_Z2[i][j][1] = Y_ZZ2[i][j];
        init_dEdeg_Z1[i][j][0] =X_dEdeg[i][j];
        init_dEdeg_Z1[i][j][1] =Y_dEdeg[i][j];
        init_ID_Z_AoQ[i][j][0] =X_ZAoQ[i][j];
        init_ID_Z_AoQ[i][j][1] =Y_ZAoQ[i][j];
        
       }
   }
    char name[50], title[100];
  ///Z vs AoQ
          for(int i=0; i<MAX_FRS_GATE; i++){
      sprintf(name,"cID_Z1_AoQ%d",i);
      cID_Z_AoQ[i] = MakePolyCond("FRS_Z1_AoQ_Gates", name, num_ID_Z_AoQ, init_ID_Z_AoQ[i], hID_Z_AoQ->GetName());
      
//       sprintf(name,"ID_Z1_AoQgate%d",i);
//        hID_Z_AoQgate[i] = MakeTH2('D',"FRS/ID_Gated/Z1AoQ/Z1AoQGated/ID_Z1_AoQgate%d",i,  1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 1000,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", "Z s2-s4");
       
        hID_Z_AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1AoQ/Z1AoQGated/ID_Z1_AoQgate%d",i), Form("Z1 A/Q gated, Z1 A/Q Gate %d", i), 1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 1000,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", "Z s2-s4");
        

        hID_dEdegoQ_Z1_Z1AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdegoQ/dEdegoQZ1_Z1AoQGated/dEdegoQZ1_Z1AoQgate%d",i), Form("dEdegoQZ1_Z1AoQgate%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,50., "Z1 from MUSIC41", "dE(S2deg)/Q [a.u.]");
       
        hID_dEdeg_Z1_Z1AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdeg/dEdeg_Z1_Z1AoQ/dEdeg_Z1_Z1AoQgate%d",i), Form("dEdeg_Z1_Z1AoQgate%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,50., "Z1 from MUSIC41", "dE(S2deg) [a.u.]");
      
       ///Z vs Z2
        
      sprintf(name,"cID_Z1_Z2_Gate%d",i);
      cID_Z_Z2gate[i] = MakePolyCond("FRS_Z1_Z2_Gates",name,num_ID_Z_Z2,init_ID_Z_Z2[i], hID_Z_Z2 ->GetName());
       
//       sprintf(name,"ID_Z1_Z2gate%d",i);
//        hID_Z1_Z2gate[i] = MakeH2I("FRS/ID_Gated/Z1Z2/Z1Z2Gated",name,  2000,frs_id->min_z_plot,70, 2000,frs_id->min_z_plot,frs_id->max_z_plot,"Z1 s2-s4", "Z2 s2-s4", 2);
       
       
        hID_Z1_Z2gate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1Z2/Z1Z2Gated/ID_Z1_Z2gate%d",i), Form("ID_Z1_Z2gate%d",i),2000,frs_id->min_z_plot,frs_id->max_z_plot, 2000,frs_id->min_z_plot,frs_id->max_z_plot,"Z1 s2-s4", "Z2 s2-s4");
       
        hID_x2AoQ_Z1Z2gate[i] = MakeTH2('I', Form("FRS/ID_Gated/x2AoQ/x2AoQ_Z1Z2Gated/ID_x2AoQ_Z1Z2gate%d",i), Form("ID_x2AoQ_Z1Z2gate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "gate on Z X at S2 [mm]");
        
        hID_x2AoQ_Z1AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/x2AoQ/x2AoQ_Z1AoQGated/ID_x2AoQ_Z1AoQgate%d",i), Form("ID_x2AoQ_Z1AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "gate on Z X at S2 [mm]");
      
        hID_x4AoQ_Z1Z2gate[i] = MakeTH2('I', Form("FRS/ID_Gated/x4AoQ/x4AoQ_Z1Z2Gated/ID_x4AoQ_Z1Z2gate%d",i), Form("ID_x4AoQ_Z1Z2gate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "gate on Z X at S4 [mm]");
        
        hID_x4AoQ_Z1AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/x4AoQ/x4AoQ_Z1AoQGated/ID_x4AoQ_Z1AoQgate%d",i), Form("ID_x4AoQ_Z1AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "gate on Z X at S4 [mm]");

        hID_ZAoQ_Z1Z2gate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1AoQ/Z1AoQ_Z1Z2Gated/ID_Z1AoQ_Z1Z2gate%d",i), Form("ID_Z1AoQ_Z1Z2gate%d",i),300,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 1000,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music2");
      
      
//       hID_dEdeg_Z1_Z1Z2gate[i] = MakeTH2('D',"FRS/ID_Gated/ID_dEdeg_Z1/dEdeg_Z1_Z1Z2gated%d",i,  1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,50., "Z from MUSIC41", "dE(S2deg) [a.u.]");
      
      hID_dEdeg_Z1_Z1Z2gate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdeg/Z1Z2/dEdeg_Z1_Z1Z2gated%d",i), Form("dEdeg_Z1_Z1Z2gated%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,100., "Z from MUSIC41", "dE(S2deg) [a.u.]");

       hID_dEdegoQ_Z1_Z1Z2gate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdegoQ/dEdegoQZ1_Z1Z2gated/dEdegoQZ1_Z1Z2gated%d",i), Form("dEdegoQZ1_Z1Z2gated%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,100., "Z from MUSIC41", "dE(S2deg)/Q [a.u.]");
      
      ///Z1 Z2 and X4/X2 A/Q gated Z vs A/Q
      
       hID_ZAoQ_Z1Z2_X2AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1AoQ/Z1AoQ_Z1Z2_X2AoQGated/ID_Z1AoQ_Z1Z2_X2AoQgate%d",i), Form("ID_Z1AoQ_Z1Z2_X2AoQgate%d",i),300,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 1000,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music2");

       hID_ZAoQ_Z1Z2_X4AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1AoQ/Z1AoQ_Z1Z2_X4AoQGated/ID_Z1AoQ_Z1Z2_X4AoQgate%d",i), Form("ID_Z1AoQ_Z1Z2_X4AoQgate%d",i),300,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 1000,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music2");
      
      //hID_dEdeg_Z1_Z1Z2_X2AoQgate[i] = MakeTH2('D',"FRS/ID_Gated/ID_dEdeg_Z1/ID_dEdeg_Z1_Z1Z2_X2AoQgated%d",  i,  1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,50., "Z from MUSIC41", "dE(S2deg)/Q [a.u.]");
      
      ///dE Deg  Z1Z2 X2 AoQ Gated
       hID_dEdeg_Z1_Z1Z2_X2AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdeg/dEdegZ_Z1Z2X2AoQGated/ID_dEdeg_Z1_Z1Z2_X2AoQgated%d",i), Form("ID_dEdeg_Z1_Z1Z2_X2AoQgated%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,100., "Z from MUSIC41", "dE(S2deg) [a.u.]");
      
       ///dE Deg  Z1Z2 X4 AoQ Gated
      hID_dEdeg_Z1_Z1Z2_X4AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdeg/dEdegZ_Z1Z2X4AoQGated/ID_dEdegZ1_Z1Z2_X4AoQgated%d",i), Form("ID_dEdeg_Z1_Z1Z2_X4AoQgated%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,100., "Z from MUSIC41", "dE(S2deg) [a.u.]");
      
       
       ///dE Deg/Q  Z1Z2 X2 AoQ Gated
      hID_dEdegoQ_Z1_Z1Z2_X2AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdegoQ/dEdegoQZ1_Z1Z2X2AoQGated/ID_dEdegoQZ1_Z1Z2_X2AoQgated%d",i), Form("ID_dEdegoQZ1_Z1Z2_X2AoQgated%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,100., "Z from MUSIC41", "dE(S2deg)/Q [a.u.]");
       
           ///dE Deg/Q  Z1Z2 X4 AoQ Gated
      hID_dEdegoQ_Z1_Z1Z2_X4AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdegoQ/dEdegoQZ1_Z1Z2X4AoQGated/ID_dEdegoQZ1_Z1Z2_X4AoQgated%d",i), Form("ID_dEdegoQZ1_Z1Z2_X4AoQgated%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,100., "Z from MUSIC41", "dE(S2deg)/Q [a.u.]");

    
///X2 vs AoQ
      sprintf(name,"cID_x2AoQ%d",i);
      cID_x2AoQ[i] = MakePolyCond("FRS_X2_Gates",name,num_ID_x2AoQ,init_ID_x2AoQ[i], hID_x2AoQ->GetName());
      
      hID_x2AoQ_x2AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/x2AoQ/x2AoQ_x2AoQGated/ID_x2AoQ_x2AoQgate%d",i), Form("ID_x2AoQ_x2AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "gate on FRS AoQ, ID X2: X at S2 [mm]");
      
      hID_x4AoQ_x2AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/x4AoQ/x4AoQ_x2AoQGated/ID_x4AoQ_x2AoQgate%d",i), Form("ID_x4AoQ_x2AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "gate on FRS AoQ, ID X2: X at S4 [mm]");
      
      hID_ZAoQ_x2AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1AoQ/Z1AoQ_x2AoQGated/ID_Z1AoQ_x2AoQgate%d",i), Form("ID_Z1AoQ_x2AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 400,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music2");

      
      hID_dEdeg_Z1_X2AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdeg/Z1AoQ_x2AoQGated/ID_dEdeg_Z1_X2AoQgate%d",i), Form("ID_dEdeg_Z1_X2AoQgate%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,100., "Z1 from MUSIC41", "dE(S2deg) [a.u.]");

      hID_dEdegoQ_Z1_X2AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdegoQ/Z1AoQ_x2AoQGated/dEdegoQZ1_X2AoQgate%d",i), Form("ID_dEdegoQ_Z1_X2AoQgate%d",i),1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,100., "Z1 from MUSIC41", "dE(S2deg)/Q [a.u.]");
      
      
//       hID_dEdegoQ_Z1_X2AoQgate[i] = MakeTH2('D',"FRS/ID_Gated/ID_dEdegoQ_Z1/dEdegoQ_Z1_X2AoQgated%d",i,  1000,frs_id->min_z_plot,frs_id->max_z_plot, 1000, 10.,50., "Z1 from MUSIC41", "dE(S2deg)/Q [a.u.]");
      
      ///X4 vs AoQ
       sprintf(name,"cID_x4AoQ%d",i);
      cID_x4AoQ[i] = MakePolyCond("FRS_X4_Gates",name,num_ID_x4AoQ,init_ID_x4AoQ[i], hID_x4AoQ->GetName());
      
       hID_x2AoQ_x4AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/x2AoQ/x2AoQ_x4AoQGated/ID_x2AoQ_x4AoQgate%d",i), Form("ID_x2AoQ_x4AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "gate on FRS AoQ, ID X4: X at S2 [mm]");
      
      hID_x4AoQ_x4AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/x4AoQ/x4AoQ_x4AoQGated/ID_x4AoQ_x4AoQgate%d",i), Form("ID_x4AoQ_x4AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 200,-100.,100.,"A/Q s2-s4", "gate on FRS AoQ, ID X4: X at S4 [mm]");
      
      hID_ZAoQ_x4AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1AoQ/Z1AoQ_x4AoQGated/ID_Z1AoQ_x4AoQgate%d",i), Form("ID_Z1AoQ_x4AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 400,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music41");
      
     
      hID_dEdeg_Z1_X4AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdeg/dEdeg_x4AoQGated/ID_dEdeg_Z1_X4AoQgate%d",i), Form("ID_dEdeg_Z1_X4AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 400,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music41");
      
      hID_dEdegoQ_Z1_X4AoQgate[i] = MakeTH2('I', Form("FRS/ID_Gated/dEdegoQ/dEdegoQ_x4AoQGated/ID_dEdegoQ_Z1_X4AoQgate%d",i), Form("ID_dEdegoQ_Z1_X4AoQgate%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 400,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music41");
          
      ///dE_deg (high charge states)
      sprintf(name,"dEdeg_Z1_%d",i);
      cID_dEdeg_Z1[i] = MakePolyCond("FRS_dEdeg_Z1",name, num_ID_dEdeg_Z1,init_dEdeg_Z1[i], hdEdeg_Z->GetName());
      
      hID_Z1_AoQ_dEdegZgate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1AoQ/Z1AoQ_dEdegZ1Gated/ID_Z1_AoQ_dEdegZ1_%d",i), Form("ID_Z1_AoQ_dEdegZ1_%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 400,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music41");
    
      
      hID_Z1_AoQ_zsame_dEdegZgate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1AoQ/Z1AoQ_dEdegated/ID_Z1_AoQ_zsame_cdEdegZ%d",i), Form("ID_Z1_AoQ_zsame_cdEdegZ%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 400,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music41");
      
      
      hID_Z1_AoQcorr_dEdegZgate[i] = MakeTH2('I', Form("FRS/ID_Gated/Z1AoQ/Z1AoQ_dEdegated/AoQcorr/ID_Z1_AoQcorr_dEdegZ%d",i), Form("ID_Z1_AoQcorr_cdEdegZ%d",i),1000,frs_id->min_aoq_plot,frs_id->max_aoq_plot, 400,frs_id->min_z_plot,frs_id->max_z_plot,"A/Q s2-s4", " Z music41");
      
    
      
        }
      ///////////////////////////////////////////////////////
 
      //------------------------------------------------------------------------------------------------//

   
      
}

void EventAnlProc::Do_FRS_Histos(EventAnlStore* pOutput){
    FRS_time_mins = 0;
  
    if(pOutput->pFRS_WR>0) FRS_time_mins =(pOutput->pFRS_WR/60E9)-26900000;
   
      for(int i=0; i<Z_Shift_array; i++){
           if(FRS_time_mins >=FRS_WR_a[i] && FRS_time_mins < FRS_WR_b[i]){
               FRS_z = FRS_z - Z1_shift_value[i];
               FRS_z2 = FRS_z2 - Z2_shift_value[i];
            }
      }
      
        for(int i=0; i<AoQ_Shift_array; i++){
           if(FRS_time_mins >=FRS_WR_i[i] && FRS_time_mins < FRS_WR_j[i]){
               FRS_AoQ = FRS_AoQ - AoQ_shift_value[i];
               FRS_AoQ_corr = FRS_AoQ_corr - AoQ_shift_value[i];
            
            }
      }
  
    ///Defined in the setup file.
     if(FRS_CORR==true) FRS_AoQ = FRS_AoQ_corr;
   
     if(MHTDC_OR_TAC==0){
     pOutput->pFRS_AoQ = FRS_AoQ;
     pOutput->pFRS_z = FRS_z;
     pOutput->pFRS_z2 = FRS_z2;
     pOutput->pFRS_beta = FRS_beta;
     pOutput->pFRS_dEdeg = FRS_dEdeg;
     pOutput->pFRS_dEdegoQ = FRS_dEdegoQ;
     }
     
     else if (MHTDC_OR_TAC==1){
     pOutput->pFRS_AoQ = FRS_AoQ_mhtdc;
     pOutput->pFRS_z = FRS_z_mhtdc;
     pOutput->pFRS_z2 = FRS_z2_mhtdc;
     pOutput->pFRS_beta = FRS_beta_mhtdc;
     pOutput->pFRS_dEdeg = FRS_dEdeg_mhtdc;
     pOutput->pFRS_dEdegoQ = FRS_dEdegoQ_mhtdc;
     }
      else {cout<<"TOF vs TAC Parameter not set correctly in DESPEC_Setup_File.h"<<endl; exit(0);}
    
     pOutput->pFRS_ID_x2 = FRS_ID_x2;
     pOutput->pFRS_ID_y2 = FRS_ID_y2;
     pOutput->pFRS_ID_a2 = FRS_ID_a2;
     pOutput->pFRS_ID_b2 = FRS_ID_b2;
     
     pOutput->pFRS_ID_x4 = FRS_ID_x4;
     pOutput->pFRS_ID_y4 = FRS_ID_y4;
     pOutput->pFRS_ID_a4 = FRS_ID_a4;
     pOutput->pFRS_ID_b4 = FRS_ID_b4;

     
     
    
     for(int l=0; l<12;l++){
     pOutput->pFRS_sci_l[l] = FRS_sci_l[l];
     pOutput->pFRS_sci_r[l] = FRS_sci_r[l];
     pOutput->pFRS_sci_e[l] = FRS_sci_e[l];
     pOutput->pFRS_sci_tx[l] = FRS_sci_tx[l];
     pOutput->pFRS_sci_x[l] = FRS_sci_x[l];

     }

     //Helena
     if(pOutput->pFRS_WR > 0) pOutput->pt_lastSC41 = pOutput->pFRS_WR;
  
    ///AoQ vs X 
   if(FRS_AoQ>0 && FRS_ID_x2>-100 && FRS_ID_x2<100)  hID_x2AoQ->Fill(FRS_AoQ, FRS_ID_x2);
   if(FRS_AoQ>0 && FRS_ID_x4>-100 && FRS_ID_x4<100)  hID_x4AoQ->Fill(FRS_AoQ, FRS_ID_x4);

   ///Z and A/Q Time in mins
   if(FRS_z>0 && FRS_time_mins>0)hID_Z1_vs_T->Fill(FRS_time_mins,FRS_z);
   
     ///AoQ vs Z
   if(FRS_AoQ>0 && FRS_z>0) hID_Z_AoQ->Fill(FRS_AoQ, FRS_z);
   
  // if(FRS_AoQ_mhtdc>0 && FRS_time_mins>0) hID_AoQ_mhtdc_T->Fill(FRS_time_mins, FRS_AoQ_mhtdc);
   
   
   
   if(FRS_AoQ_corr>0 && FRS_z>0)   hID_Z_AoQ_corr->Fill(FRS_AoQ_corr, FRS_z);  //S2-S4 correlated
     
     ///Z1 Z2
   if(FRS_z>0 && FRS_z2>0) hID_Z_Z2->Fill(FRS_z,FRS_z2);
//        if(TMath::Abs(FRS_z-FRS_z2-0.3)<0.6)
//             {
//               hID_Z_AoQ_zsame->Fill(FRS_AoQ, FRS_z);
//             }
 ///High charge states
   if(FRS_z>0 && FRS_dEdegoQ!=0)   hdEdegoQ_Z->Fill(FRS_z, FRS_dEdegoQ);
   if(FRS_z>0 && FRS_dEdeg!=0)  hdEdeg_Z->Fill(FRS_z, FRS_dEdeg);
    
      //  if(TMath::Abs(FRS_z-FRS_z2-0.3)<0.6)
      if(TMath::Abs(FRS_z-FRS_z2)<0.4)
            {
              hID_Z_AoQ_zsame->Fill(FRS_AoQ, FRS_z);
              hID_x4AoQ_zsame->Fill(FRS_AoQ, FRS_ID_x4);
            }
    
        ///GATE: ID vs x2AoQ
     for(int i=0; i<MAX_FRS_GATE; i++){
      if(cID_x2AoQ[i]->Test(FRS_AoQ, FRS_ID_x2)==true)
        {
          pOutput->pFRS_x2AoQ_pass[i] = true;
          
           if(FRS_AoQ>1 && FRS_AoQ<3 &&   FRS_ID_x2 > -100 && FRS_ID_x2<100){

          hID_x2AoQ_x2AoQgate[i]->Fill(FRS_AoQ, FRS_ID_x2);
             if (FRS_z2) hID_ZAoQ_x2AoQgate[i]->Fill(FRS_AoQ, FRS_z2);
             
             hID_dEdeg_Z1_X2AoQgate[i]->Fill(FRS_z,FRS_dEdeg);
             hID_dEdegoQ_Z1_X2AoQgate[i]->Fill(FRS_z,FRS_dEdegoQ);

        }
          if(FRS_AoQ>1 && FRS_AoQ<3 &&   FRS_ID_x4 > -100 && FRS_ID_x4<100){
          hID_x4AoQ_x2AoQgate[i]->Fill(FRS_AoQ, FRS_ID_x4);}
          if (FRS_z) hID_ZAoQ_x2AoQgate[i]->Fill(FRS_AoQ, FRS_z);
          
            }
     }
        ///GATE: ID vs x4AoQ
        for(int i=0; i<MAX_FRS_GATE; i++){
      if(cID_x4AoQ[i]->Test(FRS_AoQ, FRS_ID_x4)==true)
        {
                pOutput->pFRS_x4AoQ_pass[i] = true;
                hID_x2AoQ_x4AoQgate[i]->Fill(FRS_AoQ, FRS_ID_x2);
                hID_x4AoQ_x4AoQgate[i]->Fill(FRS_AoQ, FRS_ID_x4);
          if (FRS_z2) hID_ZAoQ_x4AoQgate[i]->Fill(FRS_AoQ, FRS_z2);
                hID_dEdeg_Z1_X4AoQgate[i]->Fill(FRS_z,FRS_dEdeg);
                hID_dEdegoQ_Z1_X4AoQgate[i]->Fill(FRS_z,FRS_dEdegoQ);
            }
        }
        for(int i=0; i<MAX_FRS_GATE; i++){
          ///GATE: Z1 vs Z2
            if(cID_Z_Z2gate[i]->Test(FRS_z, FRS_z2)==true)
            {
                 pOutput->pFRS_Z_Z2_pass[i] = true;
                
                hID_dEdeg_Z1_Z1Z2gate[i]->Fill(FRS_z,FRS_dEdeg);
                hID_dEdegoQ_Z1_Z1Z2gate[i]->Fill(FRS_z,FRS_dEdegoQ);
                
                hID_Z1_Z2gate[i]->Fill(FRS_z,FRS_z2);
                 if(FRS_AoQ>1 && FRS_AoQ<3 &&   FRS_ID_x2 > -100 && FRS_ID_x2<100){
                 
                hID_x2AoQ_Z1Z2gate[i]->Fill(FRS_AoQ, FRS_ID_x2);
                
                }
                   if(FRS_AoQ>1 && FRS_AoQ<3   && FRS_ID_x4 > -100 && FRS_ID_x4<100){
                   
                hID_x4AoQ_Z1Z2gate[i]->Fill(FRS_AoQ, FRS_ID_x4);
                   }
                   if(FRS_AoQ>1 && FRS_AoQ<3){
                   hID_ZAoQ_Z1Z2gate[i] ->Fill(FRS_AoQ, FRS_z);
                   }
            }
               // hID_SC43Z1_Z1Z2gate[i]->Fill(FRS_sci_e[7], FRS_z);
        ///The selected Z1 Z2 gate for this part can be found in the Correlations_config.dat file
            if(cID_Z_Z2gate[fCorrel->GZ1Z2_Gate]->Test(FRS_z, FRS_z2)==true){
                if(cID_x2AoQ[i]->Test(FRS_AoQ, FRS_ID_x2)==true){
                    hID_ZAoQ_Z1Z2_X2AoQgate[i]->Fill(FRS_AoQ, FRS_z);
                    hID_dEdeg_Z1_Z1Z2_X2AoQgate[i]->Fill(FRS_z,FRS_dEdeg);
                    hID_dEdegoQ_Z1_Z1Z2_X2AoQgate[i]->Fill(FRS_z,FRS_dEdegoQ);
                }
                
                 if(cID_x4AoQ[i]->Test(FRS_AoQ, FRS_ID_x4)==true){
                     hID_ZAoQ_Z1Z2_X4AoQgate[i]->Fill(FRS_AoQ, FRS_z);
                     hID_dEdeg_Z1_Z1Z2_X4AoQgate[i]->Fill(FRS_z,FRS_dEdeg);
                     hID_dEdegoQ_Z1_Z1Z2_X4AoQgate[i]->Fill(FRS_z,FRS_dEdegoQ);
                     
                 }
            }
        }
        for(int g=0; g<MAX_FRS_GATE; g++){
     
        ///GATE: AoQ vs Z
      
       if( cID_Z_AoQ[g]->Test(FRS_AoQ, FRS_z)==true){
         pOutput->pFRS_ZAoQ_pass[g] =true;
          hID_x2AoQ_Z1AoQgate[g]->Fill(FRS_AoQ, FRS_ID_x2);
          hID_x4AoQ_Z1AoQgate[g]->Fill(FRS_AoQ, FRS_ID_x4);
       // cout<<"event_number " << pOutput->pEvent_Number<<" pOutput->pFRS_ZAoQ_pass[g] " <<  pOutput->pFRS_ZAoQ_pass[g] << " g " <<g<<endl;
         hID_Z_AoQgate[g]->Fill(FRS_AoQ, FRS_z);
         hID_dEdeg_Z1_Z1AoQgate[g]->Fill(FRS_z,FRS_dEdeg);
         hID_dEdegoQ_Z1_Z1AoQgate[g]->Fill(FRS_z,FRS_dEdegoQ);
            }
        }
        
         ///High charge states
      for(int g=0; g<MAX_FRS_GATE; g++){
      if(cID_dEdeg_Z1[g]->Test(FRS_z,FRS_dEdeg)==true){ // dEdeg_vs_Z check
          pOutput->pFRS_dEdeg_Z1_pass[g]=true;
        hID_Z1_AoQ_dEdegZgate[g]->Fill(FRS_AoQ, FRS_z);
        hID_Z1_AoQcorr_dEdegZgate[g]->Fill(FRS_AoQ_corr, FRS_z);
   
    if(fabs(FRS_z2-FRS_z)<0.4){ // in addition Z same
      hID_Z1_AoQ_zsame_dEdegZgate[g]->Fill(FRS_AoQ, FRS_z);
     // hID_Z1_AoQcorr_zsame_dEdegZgate[g]->Fill(FRS_AoQ_corr, FRS_z);
            }
        }
      }         
    }


/**----------------------------------------------------------------------------------------------**/
/**--------------------------------------    AIDA   ---------------------------------------------**/
/**----------------------------------------------------------------------------------------------**/

void EventAnlProc::Make_Aida_Histos(){
  TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
  implants_strip_xy.resize(conf->DSSDs());
  implants_pos_xy.resize(conf->DSSDs());
  implants_strip_xy_stopped.resize(conf->DSSDs());
  implants_pos_xy_stopped.resize(conf->DSSDs());
  implants_e.resize(conf->DSSDs());
  implants_e_xy.resize(conf->DSSDs());
  implants_time_delta.resize(conf->DSSDs());
  implants_strip_1d.resize(conf->DSSDs());
  implants_per_event.resize(conf->DSSDs());
  decays_strip_xy.resize(conf->DSSDs());
  decays_pos_xy.resize(conf->DSSDs());
  decays_e.resize(conf->DSSDs());
  decays_e_xy.resize(conf->DSSDs());
  decays_time_delta.resize(conf->DSSDs());
  decays_strip_1d.resize(conf->DSSDs());
  decays_per_event.resize(conf->DSSDs());
//   implants_channels.resize(conf->DSSDs());
//   decays_channels.resize(conf->DSSDs());
  implants_x_ex.resize(conf->DSSDs());
  implants_y_ey.resize(conf->DSSDs());
#ifdef AIDA_PULSER_ALIGN
  aida_pulser_time = MakeTH2('I', "AIDA/Pulser_Time", "AIDA Pulser Time Comparison", 768, 0, 768, 2000, -4000, 4000);
#endif
  for (int i = 0; i < conf->DSSDs(); ++i)
  {
    implants_strip_xy[i] = MakeTH2('I', Form("AIDA/Implants/DSSD%d_implants_strip_XY", i+1), Form("DSSD %d implant hit pattern", i+1), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
    implants_strip_xy_stopped[i]= MakeTH2('I', Form("AIDA/Implants_Stopped/DSSD%d_implants_stopped_strip_XY", i+1), Form("DSSD %d implant stopped hit pattern", i+1), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
    implants_pos_xy[i] = MakeTH2('D', Form("AIDA/Implants/DSSD%d_implants_pos_XY", i+1), Form("DSSD %d implant position", i+1), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
    implants_pos_xy_stopped[i]= MakeTH2('I', Form("AIDA/Implants_Stopped/DSSD%d_implants_stopped_pos_XY", i+1), Form("DSSD %d implant stopped position hit pattern", i+1), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
    implants_e[i] = MakeTH1('F', Form("AIDA/Implants/DSSD%d_implants_energy", i+1), Form("DSSD %d implant energy", i+1), 1000, 0, 10000, "Implant Energy/MeV");
    //implants_e_xy[i] = MakeTH2('F', Form("AIDA/Implants/DSSD%d_implants_energy_XY", i+1), Form("DSSD %d implant front energy vs back energy", i+1), 1000, 0, 10000, 1000, 0, 10000, "X Energy", "Y Energy");
    implants_time_delta[i] = MakeTH1('F', Form("AIDA/Implants/DSSD%d_implants_time_delta", i+1), Form("DSSD %d implant front vs back time", i+1), 1000, -10000, 10000, "Time Difference/ns");
    implants_strip_1d[i] = MakeTH1('I', Form("AIDA/Implants/DSSD%d_implants_strip_1d", i+1), Form("DSSD %d implant 1D hit pattern", i+1), 256, 0, 256, "Strip number");
    implants_per_event[i] = MakeTH1('I', Form("AIDA/Implants/DSSD%d_implants_per_event", i+1), Form("DSSD %d implants per event", i+1), 100, 0, 100, "Number of implants");
    implants_x_ex[i] = MakeTH2('F', Form("AIDA/Implants/DSSD%d_implants_x_ex", i+1), Form("DSSD %d Ex vs X position", i+1), 128, 0, 128, 1000, 0, 10000, "X Strip", "X Energy");
    implants_y_ey[i] = MakeTH2('F', Form("AIDA/Implants/DSSD%d_implants_y_ey", i+1), Form("DSSD %d Ey vs Y position", i+1), 128, 0, 128, 1000, 0, 10000, "Y Strip", "Y Energy");

    decays_strip_xy[i] = MakeTH2('I', Form("AIDA/Decays/DSSD%d_decays_strip_XY", i+1), Form("DSSD %d decay hit pattern", i+1), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
    decays_pos_xy[i] = MakeTH2('D', Form("AIDA/Decays/DSSD%d_decays_pos_XY", i+1), Form("DSSD %d decay position", i+1), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
    decays_e[i] = MakeTH1('F', Form("AIDA/Decays/DSSD%d_decays_energy", i+1), Form("DSSD %d decay energy", i+1), 1000, 0, 20000, "Decay Energy/keV");
    decays_e_xy[i] = MakeTH2('F', Form("AIDA/Decays/DSSD%d_decays_energy_XY", i+1), Form("DSSD %d decay front energy vs back energy", i+1), 1000, 0, 10000, 1000, 0, 20000, "X Energy", "Y Energy");
    decays_time_delta[i] = MakeTH1('F', Form("AIDA/Decays/DSSD%d_decays_time_delta", i+1), Form("DSSD %d decay front vs back time", i+1), 1000, -10000, 10000, "Time Difference/ns");
    decays_strip_1d[i] = MakeTH1('I', Form("AIDA/Decays/DSSD%d_decays_strip_1d", i+1), Form("DSSD %d decay 1D hit pattern", i+1), 256, 0, 256, "Strip number");
    decays_per_event[i] = MakeTH1('I', Form("AIDA/Decays/DSSD%d_decays_per_event", i+1), Form("DSSD %d decays per event", i+1), 100, 0, 100, "Number of decays");

//     implants_channels[i] = MakeTH1('I', Form("AIDA/DSSD%d_implants_channels", i+1), Form("DSSD %d number of implant channels", i+1), 769, 0, 769);
//     decays_channels[i] = MakeTH1('I', Form("AIDA/DSSD%d_decays_channels", i+1), Form("DSSD %d number of decay channels", i+1), 769, 0, 769);
  }
}

///-----------------------------------------------------------------------------------------------------------------------------------------------------------------------///
//
using aida_coord_t = std::tuple<int, int, int>;

// https://stackoverflow.com/a/7222201/916549
template<typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
  std::hash<T> hasher;
  seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct aida_coord_hash
{
  inline size_t operator()(const aida_coord_t& val) const
  {
    size_t seed = 0;
    hash_combine(seed, std::get<0>(val));
    hash_combine(seed, std::get<1>(val));
    hash_combine(seed, std::get<2>(val));
    return seed;
  }
};

void EventAnlProc::ProcessAida(EventUnpackStore* pInputMain, EventAnlStore* pOutput) {
 // int Aida_hits =0;
//       double bPlasQDCGainMatch_AIDA[32] ={0};
  TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();


  int ev = 0;
  for(AidaUnpackData& pInputD : pInputMain->Aida)
  {
    ev++;
    AidaUnpackData* pInput = &pInputD;
    //pOutput->pAida = pAida;
    pOutput->pAIDA_WR = pInputMain->fAIDA_WR;
   
    AidaAnlData aida;
    if (pInput->ImplantEvents.size() > 1)
    {

      //         cout << " pInput->ImplantEvents.size() " << pInput->ImplantEvents.size() <<  endl;

      implantEvents++;


      // Cluster events on adjecent strips into one
      std::vector<AidaCluster> clusters = EventsToClusters(pInput->ImplantEvents);
      //
      //     // Match front-back clusters which define physical hits on the detector
      std::vector<std::pair<AidaCluster, AidaCluster>> hits;
      //
      //
      // Track the number of implants in every DSSD
      std::vector<int> counts(conf->DSSDs(), 0);
      int max_dssd = 0;

      for (auto& i : clusters)
      {
        if (i.DSSD == -1) continue;

        counts[i.DSSD - 1]++;
        if (i.DSSD > max_dssd) max_dssd = i.DSSD;

        if(i.Side != conf->DSSD(i.DSSD -1).XSide) continue;

        for (auto& j : clusters)
        {
          if(j.DSSD != i.DSSD || j.Side != conf->DSSD(j.DSSD -1).YSide) continue;
          /// Gates (set in TAidaConfiguration)
          if (abs(i.Energy - j.Energy) < conf->FrontBackEnergyH() && i.IsGoodTime(j, conf->FrontBackWindow()))
          {
            hits.push_back({i, j});
          }
        }
      }

      int channels[768] = {0};
      for (auto& i : pInput->ImplantEvents)
      {
        channels[i.Module * 64 + i.Channel]++;
      }
      int channelM = 0;
      for (int i = 0; i < 768; ++i){
        if (channels[i]) ++channelM;
      }
      //implants_channels[0]->Fill(channelM);

      //     // Generate stored data for hits and plot the histograms

      for (auto& i : hits)
      {
        AidaHit hit = ClusterPairToHit(i);
        hit.Event = ev;

        hit.Stopped = (hit.DSSD == max_dssd);

        // Check that every DSSD before has at least one implant event
        for(int j = hit.DSSD - 1; j > 0; j--)
        {
            if (counts[j - 1] == 0) hit.Stopped = false;
        }
        //
        //
        if (hit.Stopped) stoppedEvents++;
      //  pInput->Implants.push_back(hit);

      //  pOutput->pAida.Implants.push_back(hit);
        aida.Implants.push_back(hit);
        implants_strip_xy[hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
	if (hit.Stopped)implants_strip_xy_stopped[hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
	
	// Helena
	if(hit.Stopped){
	   if(hit.DSSD==1){
	     pOutput->pt_lastIMP_DSSD1 = hit.TimeFront;
	     pOutput->plastIMP_DSSD1_StripX = hit.StripX;
	   }
	   if(hit.DSSD==2){
	     pOutput->pt_lastIMP_DSSD2 = hit.TimeFront;
	     pOutput->plastIMP_DSSD2_StripX = hit.StripX;
	   }
	   if(hit.DSSD==3){
	     pOutput->pt_lastIMP_DSSD3 = hit.TimeFront;
	     pOutput->plastIMP_DSSD3_StripX = hit.StripX;	     
	  }
	}
	
//       cout<<"ANALYSIS AIDA " <<pOutput->pEvent_Number<< " Energy " <<  hit.Energy << " hit.DSSD - 1 " <<hit.DSSD - 1 << endl;
        implants_pos_xy[hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
        implants_e[hit.DSSD - 1]->Fill(hit.Energy);
  

      //  implants_e_xy[hit.DSSD - 1]->Fill(hit.EnergyFront, hit.EnergyBack);
        //implants_time_delta[hit.DSSD - 1]->Fill(hit.TimeFront - hit.TimeBack);
        implants_time_delta[hit.DSSD - 1]->Fill(hit.FastTimeFront - hit.FastTimeBack);

        implants_x_ex[hit.DSSD - 1]->Fill(hit.StripX, hit.EnergyFront);
        implants_y_ey[hit.DSSD - 1]->Fill(hit.StripY, hit.EnergyBack);

        int channel = i.first.Strip;
        implants_strip_1d[hit.DSSD - 1]->Fill(channel);
        channel = i.second.Strip + 128;
        implants_strip_1d[hit.DSSD - 1]->Fill(channel);
      }
      //
      if (hits.size() > 0)
      {
        implants_per_event[0]->Fill(hits.size());
        goodImplantEvents++;
      }
    }
    else if (pInput->DecayEvents.size() > 1)
    {
      decayEvents++;

      int channels[768] = {0};
#ifdef AIDA_PULSER_ALIGN
      int64_t wr_base = 0;
#endif
      for (auto& i : pInput->DecayEvents)
      {
        channels[i.Module * 64 + i.Channel]++;
#ifdef AIDA_PULSER_ALIGN
        if(i.Module == 0 && i.Channel == 0) wr_base = i.Time;
#endif
      }
      int channelM = 0;
      for (int i = 0; i < 768; ++i)
      if (channels[i]) ++channelM;
      
     // decays_channels[0]->Fill(channelM);

      if (channelM > 400)
      {
        decayEvents--;
        pulserEvents++;
#ifdef AIDA_PULSER_ALIGN
        if(channelM > 700)
        //if(pInputMain->fTrigger == 3)
        {
          std::cout << "Identified a pulser event!" << std::endl;
          std::vector<int> offsets;
          offsets.resize(conf->FEEs());
          for (int i = 0; i < offsets.size(); i++) offsets[i] = 0;

          for (auto& i : pInput->DecayEvents)
          {
            if (i.Energy < 1000) continue;
            std::cout << i.Module << ", " << i.Channel << ", " << i.Energy << ", " << std::hex << i.Time << "," << i.FastTime << std::dec << std::endl;
            int offset = (i.Time - wr_base) % 2000;
            if (offsets[i.Module] == 0)
            {
              offsets[i.Module] = offset;
            }
            else if (offset > offsets[i.Module])
            {
              // confirm the offset is 2us out
              if (abs(offset - offsets[i.Module]) % 2000 != 0)
                std::cout << "LOGICAL MISTAKE IN ALIGNMENT" << std::endl;
            }
            else if (offset < offsets[i.Module])
            {
              if (abs(offset - offsets[i.Module]) % 2000 != 0)
                std::cout << "LOGICAL MISTAKE IN ALIGNMENT" << std::endl;
              offsets[i.Module] = offset;
            }

            aida_pulser_time->Fill(i.Module * 64 + i.Channel, offsets[i.Module]);
          }

          std::cout << std::endl;

          std::cout << "Put this into AIDA_Times.txt" << std::endl;
          for (int i  = 0; i < offsets.size(); i++)
          {
            std::cout << i << " " << offsets[i] << std::endl;
          }

          throw TGo4UserException(3,"");
        }
#endif
        return;
      }

      // Clean up huge event buffers - for now we just destroy them
      if (pInput->DecayEvents.size() > 400)
      {
        decayEvents--;
        nonsenseEvents++;
//        pInput->SetValid(kFALSE); ///NEEDED!?
        return;
      }

      std::vector<AidaCluster> clusters = EventsToClusters(pInput->DecayEvents);

      std::vector<std::pair<AidaCluster, AidaCluster>> hits;
      std::unordered_map<aida_coord_t, int, aida_coord_hash> mults;

      for (auto& i : clusters)
      {

        if(i.DSSD == -1 || i.Side != conf->DSSD(i.DSSD -1).XSide) continue;

        //if(i.Energy < 100) continue;
        for (auto& j : clusters)
        {
          if(j.DSSD != i.DSSD || j.Side != conf->DSSD(j.DSSD -1).YSide) continue;
          //if(j.Energy < 100) continue;
          // Gates
          if (abs(i.Energy - j.Energy) < conf->FrontBackEnergyL() && i.IsGoodTime(j, conf->FrontBackWindow()))
          {
            aida_coord_t x{i.DSSD, i.Side, i.Strip};
            aida_coord_t y{j.DSSD, j.Side, j.Strip};
            mults[x]++;
            mults[y]++;
            hits.push_back({i, j});
          }
        }
      }

      for (auto& i : hits)
      {
        AidaHit hit = ClusterPairToHit(i);
        hit.Event = ev;

        aida_coord_t x{i.first.DSSD, i.first.Side, i.first.Strip};
        aida_coord_t y{i.second.DSSD, i.second.Side, i.second.Strip};
        if (mults[x] > 1 || mults[y] > 1)
          continue;

//         pInput->Decays.push_back(hit);
//         //pOutput->pAida.push_back(hit); ///TEST
// 
//         if (hit.DSSD != 3)
//         pOutput->pAida.Decays.push_back(hit);
        if (hit.DSSD != 3 || (hit.EnergyBack > 150 && hit.EnergyFront > 150 ))
          aida.Decays.push_back(hit);
        decays_strip_xy[hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
        decays_pos_xy[hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
        decays_e[hit.DSSD - 1]->Fill(hit.Energy);
        decays_e_xy[hit.DSSD - 1]->Fill(hit.EnergyFront, hit.EnergyBack);
        decays_time_delta[hit.DSSD - 1]->Fill(hit.TimeFront - hit.TimeBack);
        //decays_time_delta[hit.DSSD - 1]->Fill(hit.FastTimeFront - hit.FastTimeBack);

        int channel = i.first.Strip;
        decays_strip_1d[hit.DSSD - 1]->Fill(channel);
        channel = i.second.Strip + 128;
        decays_strip_1d[hit.DSSD - 1]->Fill(channel);
      }

      if (clusters.size() > 0)
      {
        decays_per_event[0]->Fill(clusters.size());
      }
      //   cout <<" decayEvents " << decayEvents << endl;
    }
    else
    {
      nonsenseEvents++;
      //pInput->SetValid(kFALSE);
    }
    pOutput->pAida.push_back(aida);
  }
}


std::vector<AidaCluster> EventAnlProc::EventsToClusters(std::vector<AidaEvent> const& events)
{
  // track strip multiplicity and reject bad strips
  std::unordered_map<aida_coord_t, int, aida_coord_hash> stripm;

  std::vector<AidaCluster> clusters;
  for (auto& i : events)
  {
    // Don't cluster invalid events
    if (i.DSSD == -1) continue;
 
    aida_coord_t coord{i.DSSD, i.Side, i.Strip};
    if(++stripm[coord] > 1)
      continue;

    bool added = false;
    AidaCluster* cluster;
    // Try to add the event to an existing cluster
     // Weird loop because we can remove clusters too
    auto it = std::begin(clusters);
    while (it != std::end(clusters))
    {
      auto& j = *it;
      if(j.IsAdjacent(i) && j.IsGoodTime(i))
      {
        // Add the event to the cluster
        if (!added)
        {
          j.AddEvent(i);
          cluster = &j;
          added = true;
        }
        // If we match again the two clusters are merged into one
        // The old cluster is then removed
        else
        {
          cluster->AddCluster(j);
          it = clusters.erase(it);
          continue;
        }
      }
      ++it;
    }
    // Otherwise make a new cluster for the event
    if (!added)
    {
      AidaCluster c_test;
      c_test.AddEvent(i);
      clusters.push_back(c_test);
    }
  }

  // remove bad strips again
  auto it = std::begin(clusters);
  while (it != std::end(clusters))
  {
    auto&j = *it;
    bool destroy = false;
    for(int s = j.StripMin; s <= j.StripMax; s++)
    {
      aida_coord_t coord{j.DSSD, j.Side, s};
      if (stripm[coord] > 1) {
        destroy = true;
      }
    }
    if (destroy) {
      it = clusters.erase(it);
      continue;
    }
    ++it;
  }

  return clusters;
}

AidaHit EventAnlProc::ClusterPairToHit(std::pair<AidaCluster, AidaCluster> const& i)
{
  AidaHit hit;
  hit.DSSD = i.first.DSSD;

  hit.StripX = i.first.Strip;
  hit.StripY = i.second.Strip;
  hit.PosX = 75.6 * i.first.Strip / 128. - 37.75;
  hit.PosY = 75.6 * i.second.Strip / 128. - 37.75;

  hit.StripXMin = i.first.StripMin;
  hit.StripXMax = i.first.StripMax;
  hit.StripYMin = i.second.StripMin;
  hit.StripYMax = i.second.StripMax;
  hit.ClusterSizeX  = i.first.N;
  hit.ClusterSizeY = i.second.N;

  hit.Energy = (i.first.Energy + i.second.Energy) / 2;
  hit.EnergyFront = i.first.Energy;
  hit.EnergyBack = i.second.Energy;

  hit.Time = std::min(i.first.Time, i.second.Time);
  hit.TimeFront = i.first.Time;
  hit.TimeBack = i.second.Time;
  hit.FastTime = std::min(i.first.FastTime, i.second.FastTime);
  hit.FastTimeFront = i.first.FastTime;
  hit.FastTimeBack = i.second.FastTime;

  return hit;
}
                                                    ///End of Aida ///

 /**----------------------------------------------------------------------------------------------**/   
     /**--------------------------------------  bPlastic  TAMEX ----------------------------------------------   **/
     //**----------------------------------------------------------------------------------------------**/  
        
    void EventAnlProc::Make_Plastic_Tamex_Histos(){ 
        
         for (int i =1; i<4; i++)   
            { 
                hbPlas_ToT_Sum[i] = MakeTH1('D', Form("bPlastic/ToT_Sum_Det.%2d",i), Form("bPlastic Sum ToT Det. %2d",i), 5000, 0, 3000000);
  
                 hbPlas_hit_pattern_det[i]= MakeTH1('D', Form("bPlastic/Stats/HitPattern_Det.%2d",i), Form("bPlastic Hit pattern Det. %2d",i), bPLASTIC_CHAN_PER_DET, 0, bPLASTIC_CHAN_PER_DET);
             
          for(int j=0; j<bPLASTIC_CHAN_PER_DET; j++){  
              
             hbPlas_Lead_T[i][j] = MakeTH1('D', Form("bPlastic/Lead-/Lead T Plas Det. %2d Ch.%2d",  i,j), Form("Lead - Time Det %2d Ch. %2d", i,j),2500, 0, 2000);
               
              if(i<3){//Take only cards with bPlast channels
            
            hbPlas_Lead_dT_coinc[i][j] = MakeTH1('D', Form("bPlastic/Lead-LeadCoincidenceChan/Lead dT Plas Det. %2d Ch %d Ref Coincidence",i,j), Form("Lead dT Plas Det. %2d Ch %d Ref Coincidence",i,j),500,-200,200);
        }
               
            hbPlas_ToT_det[i][j] = MakeTH1('D', Form("bPlastic/ToT/ToT Plas Det. %2d Ch. %2d",  i,j), Form("ToT Det. %2d Ch. %2d", i,j),20000, 0., 200000.);   
            
            hbPlas_Multiplicity_Chan[i][j] = MakeTH1('D', Form("bPlastic/Stats/Mulitplicity_per_Chan/bPlast Multiplicity Det. %2d Ch. %2d",  i,j), Form("ToT Det. %2d Ch. %2d", i,j),50, 0., 50.);   

            hbPlas_lead_lead_ref_det[i][j] = MakeTH1('D', Form("bPlastic/Lead-Lead_Ref/Lead-Lead Plas Det. %2d RefCh. - Ch. %d", i,j), Form("Lead Ref Ch.0 - Lead Det.%2d Ch. %2d", i,j),2500, -50000., 50000.);
        
//         hbPlas_lead_lead_ref_det2[i][j] = MakeTH1('D', Form("bPlastic/Lead-Lead_Ref/Lead-Lead Plas Det. %2d RefCh. %2d", i,j), Form("Lead Ref Ch.0 - Lead Det.%2d Ch. %2d", i,j),2500, -50000., 50000.);
//         hbPlas_lead_lead_ref_det3[i][j] = MakeTH1('D', Form("bPlastic/Lead-Lead_Ref/Lead-Lead Plas Det. %2d RefCh. %2d", i,j), Form("Lead Ref Ch.0 - Lead Det.%2d Ch. %2d", i,j),2500, -50000., 50000.);
          
       // hbPlas_lead_lead_gated[i][j] = MakeTH1('D', Form("bPlastic/Lead-Lead_Egated/Lead-Lead Egated Plas Det. %2d Ch. %2d",  i,j), Form("Lead - Lead Energy gated Det. %2d Ch.  %2d", i,j),2500, -50000., 50000.); 
            
       // hbPlas_SC41L_lead[i][j] = MakeTH1('D', Form("bPlastic/SC41-Lead_Plas/SC41_Lead Plas Det. %2d Ch.%02d", i,j), Form("SC41 Lead - bPlas Lead Det. %2d Lead Ch. %2d ", i,j), 4002, -100000., 100000.);    
         hbPlas_fatimatamex_dT[i][j] = MakeTH1('D', Form("bPlastic/AdditionalChannels/FatTamChan-Lead_bPlas/(bPlast)FatTamChan_Lead bPlas Det.%2d Ch.%02d", i,j), Form("FATIMA tamex channel in bPlast: Lead - bPlas Lead Det. %2d Lead Ch. %2d ", i,j), 4000, -100000., 100000.); 
         
         hbPlas_fatimavme_dT[i][j] = MakeTH1('D', Form("bPlastic/AdditionalChannels/FatVMEChan-Lead_bPlas/(bPlast)FatVMEChan_Lead bPlas Det.%2d Ch.%02d", i,j), Form("FATIMA VME channel in bPlast: Lead - bPlas Lead Det. %2d Lead Ch. %2d ", i,j), 4000, -100000., 100000.); 
            
         hbPlas_fatimavme_dT[i][j] = MakeTH1('D', Form("bPlastic/AdditionalChannels/SC41R_Anal-Lead_bPlas/SC41R_Ana_Lead bPlas Det. %2d Ch.%02d", i,j), Form("SC41R Analogue Lead - bPlas Lead Det. %2d Lead Ch. %2d ", i,j), 4000, -100000., 100000.);    
            
         hbPlas_SC41L_Digi_lead[i][j] = MakeTH1('D', Form("bPlastic/AdditionalChannels/SC41L_Digi-Lead_bPlas/SC41L_Digi_Lead bPlas Det. %2d Ch.%02d", i,j), Form("SC41L Digital Lead - bPlas Lead Det. %2d Lead Ch. %2d ", i,j), 4000, -100000., 100000.); 
            
         hbPlas_SC41R_Digi_lead[i][j] = MakeTH1('D', Form("bPlastic/SC41R_Digi-Lead_bPlas/SC41R_Digi_Lead bPlas Det. %2d Ch.%02d", i,j), Form("SC41R Digital Lead - bPlas Lead Det. %2d Lead Ch. %2d ", i,j), 4000, -100000., 100000.);             
        
          }
  }
        
        // New histogram looking at correlation between Fibre implanted channels 1 and 9 (2 and 10 if A=1->4 etc). H.M.A (don't blame me though...)
        
//         hFIMP_ToT_Correlation_Comb1 = MakeTH2('D', "bPlastic/FIMP_ToT_Correlation_Comb1", "ToT vs ToT for 2 FIMP channels, combination 1",500,0,100000,500,0,100000);
// 
//         hFIMP_ToT_Correlation_Comb2 = MakeTH2('D', "bPlastic/FIMP_ToT_Correlation_Comb2", "ToT vs ToT for 2 FIMP channels, combination 2",500,0,100000,500,0,100000);
                                 
//         hSC41_Analogue_Tamex = MakeTH1('D',"bPlastic/SC41/Analogue L-R","SC41 Analogue L - R",4002, -100000., 100000.); 
//         hSC41_Digital_Tamex = MakeTH1('D',"bPlastic/SC41/Digital L-R","SC41 Analogue L - R",4002, -100000., 100000.);   
           
            
        hbPlas_Multiplicity_Det1 = MakeTH1('D',"bPlastic/Stats/Multiplicity_Det1","bPlastic Multiplicity Det 1",32,0,32);   
        hbPlas_Multiplicity_Det2 = MakeTH1('D',"bPlastic/Stats/Multiplicity_Det2","bPlastic Multiplicity Det 2",32,0,32);   
       /* hbPlas_Multiplicity_Det3 = MakeTH1('D',"bPlastic/Stats/Multiplicity_Fibre","bPlastic Multiplicity Fibre",32,0,32); */  
       
      
        
    }   
    /////////////////////////////////////////////////// 
    void EventAnlProc::Do_Plastic_Tamex_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput){   
    
         fired_det1=false, fired_det2=false;    
         //ZERO_ARRAY(bPlas_tot_hits);
         for(int i=1; i<4; i++){
             for(int j=0; j<16; j++){
             bPlas_tot_hits[i][j]=0;
             }
         }
         bool Fibre=false;
    
       
         for(int a=1; a<4; a++){
                 for (int b = 0; b < bPLASTIC_CHAN_PER_DET; b++){  
                     for(int k=0; k<bPLASTIC_TAMEX_HITS; k++){
                        lead_bplas[a][b][k]=0; 
                        ToT_bplas[a][b][k] = 0;   
                     }
                 }
         }
        
          
            
        
     ///**---------------------------------------------LEAD -------------------------------------------------**/        
           ///Loop on channels First    
                           
              for(int i=1; i<4; i++){ ///Detector number
                 for (int j = 0; j < 16; j++){  ///Channel number 
                     
                for(int k=0; k< bPLASTIC_TAMEX_HITS; k++){ 
                    //Fat_RefCh[j] = pInput->fFat_Lead_PMT[1][j]; 
                    bPlas_RefCh0_Det1[k] = pInput->fbPlas_Lead_PMT[1][0][k];
                    bPlas_RefCh0_Det2[k] = pInput->fbPlas_Lead_PMT[2][0][k];
                    bPlas_RefCh0_Det3[k] = pInput->fbPlas_Lead_PMT[3][0][k];
            
                        }      
                    }
              }
            ////////////////////////////    
              ///Loop over channels 
              pOutput->pbPlasDetNum= pInput->fbPlasDetNum;
           // cout<<"pInput->fbPlasDetNum " <<pInput->fbPlasDetNum << endl;
              for(int a=1; a<4; a++){ ///Detector number
                    pOutput->pbPlasChan[a]= pInput->fbPlasChan[a];
             
                 for (int b = 0; b < bPLASTIC_CHAN_PER_DET; b++){  ///Channel number 
                   
                    
 ///**---------------------------------------------Plastic Lead Time ----------------------------------**/    
                       
            if(pInput->fbPlas_PMT_Lead_N[a][b]<bPLASTIC_TAMEX_HITS){
                pOutput->pbPlas_PMT_Lead_N[a][b] = pInput->fbPlas_PMT_Lead_N[a][b]; 
      
               for(int j=0; j< bPLASTIC_TAMEX_HITS; j++){ ///Hits 
                   // if(j<20){
                   
                    lead_bplas[a][b][j] = pInput->fbPlas_Lead_PMT[a][b][j];  
        
                if(lead_bplas[a][b][j]!=0){
                    hbPlas_Lead_T[a][b]->Fill(lead_bplas[a][b][j]);
                    hits_bplas_lead++;  
                    pOutput->pbPlas_LeadT[a][b][j] = lead_bplas[a][b][j];    
                    pOutput->pbPlas_LeadHits = hits_bplas_lead; 
                    pOutput->pbPlas_LeadT_Avg = lead_bplas[a][b][j]/hits_bplas_lead;
                
    ///**---------------------------bPlast Channels - AND signal  ----------------------------------**/     
        if(a==bPLASTIC_DOWNSTREAM_DET && pInput->fbPlas_Lead_PMT[bPLASTIC_ADDITIONAL_CH_MOD][bPLASTIC_DOWN_COIN][0] !=0 && lead_bplas[bPLASTIC_DOWNSTREAM_DET][b][j]!=0){ // s452 a==1 is the downstream detector. Coincidence is in a=3, b=0.
        hbPlas_Lead_dT_coinc[bPLASTIC_DOWNSTREAM_DET][b]->Fill((lead_bplas[bPLASTIC_DOWNSTREAM_DET][b][j] - pInput->fbPlas_Lead_PMT[bPLASTIC_ADDITIONAL_CH_MOD][bPLASTIC_DOWN_COIN][0])*5);
     }
   //  cout<<"a " << a << " b " << b << " j " << j << endl;
     if(a==bPLASTIC_UPSTREAM_DET && pInput->fbPlas_Lead_PMT[bPLASTIC_ADDITIONAL_CH_MOD][bPLASTIC_UP_COIN][0] != 0&&  lead_bplas[bPLASTIC_UPSTREAM_DET][b][j]!=0){ // s452 a==2 is the upstream detector. Coincidence is in a=3, b=1.
         
        hbPlas_Lead_dT_coinc[bPLASTIC_UPSTREAM_DET][b]->Fill((lead_bplas[bPLASTIC_UPSTREAM_DET][b][j] - pInput->fbPlas_Lead_PMT[bPLASTIC_ADDITIONAL_CH_MOD][bPLASTIC_UP_COIN][0])*5);
     }      
    }
    
             
//     ///**---------------------------------------------Plastic Lead Ref dT ----------------------------------**/          
//                           
//                     if(i>15 && pInput->fbPlas_Lead_PMT[16][j]>0 && pInput->fbPlas_Lead_PMT[a][b][j]>0) {   
                
        if(bPlas_RefCh0_Det1[j]>0 && lead_bplas[1][b][j]>0){
            lead_lead_bplas_Ref1[b][j] = (bPlas_RefCh0_Det1[j] -  lead_bplas[1][b][j])*CYCLE_TIME; 
     
        }
        if(bPlas_RefCh0_Det2[j]>0 && lead_bplas[2][b][j]>0){
            lead_lead_bplas_Ref2[b][j] = (bPlas_RefCh0_Det2[j] -  lead_bplas[2][b][j])*CYCLE_TIME;
        }
              if(lead_lead_bplas_Ref1[b][j]!=0 && a==1) hbPlas_lead_lead_ref_det[1][b] ->Fill(lead_lead_bplas_Ref1[b][j]);
          
       // cout<<"ANL EVENT " << pInput->fevent_number << " a " << a << " b " << b << " j " << j << endl;
              if(lead_lead_bplas_Ref2[b][j]!=0 && a==2) hbPlas_lead_lead_ref_det[2][b] ->Fill(lead_lead_bplas_Ref2[b][j]);
            
//               
              ///Reference signals
                ///Fatima tamex OR in bplast tamex
               if(bPlas_TAM_FATTAM>0 && lead_bplas[a][b][j]>0){
                    bPlas_fatimatamex_dT[a][b][j] = (bPlas_TAM_FATTAM -  lead_bplas[a][b][j])*CYCLE_TIME;
                    hbPlas_fatimatamex_dT[a][b]->Fill(bPlas_fatimatamex_dT[a][b][j] );
                }
                ///Fatima VME OR in bplast tamex
                if(bPlas_TAM_FATVME>0 && lead_bplas[a][b][j]>0){
                    bPlas_fatimavme_dT[a][b][j] = (bPlas_TAM_FATVME -  lead_bplas[a][b][j])*CYCLE_TIME;
                    hbPlas_fatimavme_dT[a][b]->Fill(bPlas_fatimavme_dT[a][b][j] );
                    }
                  ///SC41L in bplast tamex  
                if(bPlas_TAM_SC41L_DIG>0 && lead_bplas[a][b][j]>0){
                    bPlas_fatimatamex_dT[a][b][j] = (bPlas_TAM_SC41L_DIG -  lead_bplas[a][b][j])*CYCLE_TIME;
                    hbPlas_SC41L_Digi_lead[a][b]->Fill(SC41L_DIG_lead_bPlas[a][b][j] );
                    }
                    ///SC41R in bplast tamex
                if(bPlas_TAM_SC41R_DIG>0 && lead_bplas[a][b][j]>0){
                    bPlas_fatimavme_dT[a][b][j] = (bPlas_TAM_SC41R_DIG -  lead_bplas[a][b][j])*CYCLE_TIME;
                    hbPlas_SC41R_Digi_lead[a][b]->Fill(SC41R_DIG_lead_bPlas[a][b][j] );
                    }
           
                }
        
            ///AKM note: lead clear of malloc 29.04.21
//             
//                                 
//       ///**---------------------------------------------Plastic Trail ----------------------------------**/  
//                                                      
                pOutput->pbPlas_PMT_Trail_N[a][b] = pInput->fbPlas_PMT_Trail_N[a][b]; 
                if(a<4 && b<bPLASTIC_CHAN_PER_DET){
               for(int j=0; j< bPLASTIC_TAMEX_HITS; j++){ ///Hits 
               // if(j<20){
                    
                   /* trail_bplas[a][b][j] = ; */ 

                    //hbPlas_Trail_T[a][b]->Fill(trail_bplas[a][b][j]);
                  if(pOutput->pbPlas_TrailT[a][b][j]!=0)  hits_bplas_trail++;  
                    pOutput->pbPlas_TrailT[a][b][j] = pInput->fbPlas_Trail_PMT[a][b][j];  
                        }
                    }
                    ///AKM note: trail clear of malloc 29.04.21
        
//                
//    ///**--------------------Plastic ToT --------------------------------**/  
//           
              for(int j=0; j< bPLASTIC_TAMEX_HITS; j++){ 
             
                  if(pInput->fbPlas_Trail_PMT[a][b][j] >0 && pInput->fbPlas_Lead_PMT[a][b][j]>0){ 
                
        ToT_bplas[a][b][j] = (pInput->fbPlas_Trail_PMT[a][b][j] - pInput->fbPlas_Lead_PMT[a][b][j]);   
                 
                ///Correction for overflows 
                if(ABS(ToT_bplas[a][b][j]) >(double)(COARSE_CT_RANGE>>1)) {   
                    
                       ToT_bplas[a][b][j] = CYCLE_TIME*(ToT_bplas[a][b][j] + COARSE_CT_RANGE);    
                      } 
                 else{  
                           ToT_bplas[a][b][j]= CYCLE_TIME*ToT_bplas[a][b][j];                         
                       }    
                       ///Gain matching  
               // pOutput-> pbPlas_ToTCalib[a][b][j] = fCal->Abplas_TAMEX_ZAoQ[i]* ToT_bplas[a][b][j] + fCal->Bbplas_TAMEX_ZAoQ[i];
               pOutput-> pbPlas_ToTCalib[a][b][j] =ToT_bplas[a][b][j];
           
                       if(ToT_bplas[a][b][j]>0) {
                        hbPlas_ToT_det[a][b] ->Fill(ToT_bplas[a][b][j]);   
                        hbPlas_ToT_Sum[a]->Fill(ToT_bplas[a][b][j]);   
                        hbPlas_hit_pattern_det[a]->Fill(b);     
                          //bPlas_tot_hits++; 
                          bPlas_tot_hits[a][b]++;      
                       
                          hbPlas_Multiplicity_Chan[a][b] ->Fill(bPlas_tot_hits[a][b]);  
                           
                         if(a==1) hbPlas_Multiplicity_Det1->Fill(bPlas_tot_hits[1][b]);
                         if(a==2) hbPlas_Multiplicity_Det2->Fill(bPlas_tot_hits[2][b]);
                      //   if(a==3) hbPlas_Multiplicity_Det3->Fill(bPlas_tot_hits);
                            
                          }//ToT>0
                        }//Lead+Trail>0         
                      }//hits
                    }//Limit hits loop
                 }  //Channel
              }  ///Detector 
        } ///Function
    
    /**-----------------------------------------------------------------------------------------------**/
    /**--------------------------------------  FATIMA TAMEX ------------------------------------------**/
    /**-----------------------------------------------------------------------------------------------**/
 void EventAnlProc::Make_Fatima_Tamex_Histos(){
   //  cout<<"FATIMA_TAMEX_CHANNELS+1 " <<FATIMA_TAMEX_CHANNELS+1 << " FATIMA_TAMEX_HITS " <<FATIMA_TAMEX_HITS << endl;
     for(int i=1; i<=FATIMA_TAMEX_CHANNELS; i++){ 
        
//          hFat_Lead_Fast_T[i] =  MakeTH1('D', /*Form("FATIMA_TAMEX/Fast/LeadT/Fast/Lead Time Fast Ch.%2d",i), Form("Lead Fast time. %2d",i), 5000,0,5000);
//          hFat_Trail_Fast_T[i] =  MakeTH1('D', Form("FATIMA_TAMEX/Fast/TrailT/Fast/Trail Time Fast Ch.%2d",i), Form("Trail Slow time. %2d",i), 5000,0,5000);
//          
//          hFat_Lead_Slow_T[i] =  MakeTH1('D', Form("FATIMA_TAMEX/Slow/LeadT/Lead Time Slow Ch.%2d",i), Form("Lead Fast time. %2d",i), 5000,0,5000);
//          hFat_Trail_Slow_T[i] =  MakeTH1('D', Form("FATIMA_TAMEX/Slow/TrailT/Trail Time Slow Ch.%2d",i), Form("Trail Slow time. %2d",i), 5000,0,5000);*/
         
         hFat_lead_lead_fast_ref[i] =   MakeTH1('D', Form("FATIMA_TAMEX/Fast/LeadRef-Lead/Lead-Lead Fast Time Ref Ch1- Ch.%2d",i), Form("RefLead-Lead time. %2d",i), 1000,-10000,10000);
         hFat_lead_lead_slow_ref[i] =   MakeTH1('D', Form("FATIMA_TAMEX/Slow/LeadRef-Lead/Lead-Lead Slow Time Ref Ch1- Ch.%2d",i), Form("RefLead-Lead time. %2d",i), 1000,-10000,10000);
         
        // hFat_ToT_Fast_det[i]=   MakeTH1('D', Form("FATIMA_TAMEX/Fast/ToT/ToT Fast Ch.%2d",i), Form("ToT Fast %2d",i), 5000,0,150000);      
         
         hFat_ToT_Slow_det[i]=   MakeTH1('D', Form("FATIMA_TAMEX/Slow/ToT/ToT Slow Ch.%2d",i), Form("ToT Slow %2d",i), 15000,0,150000);     
         
         hFat_ToT_Slow_det_calib[i]=   MakeTH1('D', Form("FATIMA_TAMEX/Slow/ToT_Calib/ToT Slow Calib Ch.%2d",i), Form("ToT Slow Calibrated %2d",i), 10000,0,10000);     
     }
          hFat_ToT_Fast_Sum= MakeTH1('D', "FATIMA_TAMEX/Fast/ToTFastSum", "ToT LaBr Fast (all detectors)",5000,0,150000);
          hFat_ToT_Slow_Sum= MakeTH1('D', "FATIMA_TAMEX/Slow/ToTSlowSum", "ToT LaBr Slow (all detectors)",15000,0,150000);
          hFat_ToT_Slow_Sum_Calib= MakeTH1('D', "FATIMA_TAMEX/Slow/ToTSlowSum_Calib", "ToT LaBr Slow calibrated (all detectors)",10000,0,10000);
          
          hFat_ToT_Slow_vs_Fast=MakeTH2('D',"FATIMA_TAMEX/Fast_vs_Slow_Ch11","Fast ToT vs Slow ToT Ch.11",2000,0,20000,2000,0,20000);
          
          hFat_tamex_hit_pattern =  MakeTH1('D', "FATIMA_TAMEX/Fatima_Hitpattern", "Fatima Hit pattern",48,0,48);  
          hFat_tamex_multiplicity =  MakeTH1('D', "FATIMA_TAMEX/Fatima_Multiplicity", "Fatima Multiplicity",48,0,48);  
 }
 
 
//-----------------------------------------------------------------------------------------------//
void EventAnlProc::Do_Fatima_Tamex_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput){   
          
        //bool fired_det1=false, fired_det2=false;    
         
         hits_fat_lead=0;
         hits_fat_trail=0;
                 for (int i = 0; i < 66; i++){
                    
                    Fat_tot_hits[i] = 0;
                     for(int j=0; j<FATIMA_TAMEX_HITS; j++){
                        lead_slow_fat[i][j]=0; 
                        lead_fast_fat[i][j]=0; 
                        ToT_slow_fat[i][j] = 0; 
                        ToT_slow_fat_calib[i][j] = 0; 
                        ToT_fast_fat[i][j] = 0; 
                        lead_lead_slow_fat_Ref1[i][j]=0;
                        lead_lead_fast_fat_Ref1[i][j]=0;
//                         SC41L_ANA_lead_fat[i][j] = 0;  
//                         SC41R_ANA_lead_fat[i][j] = 0;  
//                         SC41L_DIG_lead_fat[i][j] = 0;  
//                         SC41R_DIG_lead_fat[i][j] = 0;  
                     }
                 }
         
         for(int i=0; i<FATIMA_TAMEX_HITS; i++){
         FatTam_Fast_RefCh0[i] =0;
         FatTam_Slow_RefCh0[i] =0;
         SC41L_ANA_lead_fat[i] =0;
         SC41R_ANA_lead_fat[i] =0;
         bPlasDet1_coin_lead_Fat[i] =0;
         bPlasDet2_coin_lead_Fat[i] =0;
         
         }
                
     ///**---------------------------------------------LEAD -------------------------------------------------**/        
           ///Loop on channels First    
                           
              for(int i=1; i<=FATIMA_TAMEX_CHANNELS; i++){ ///Channel number
                  
                  // Fast Branch for timing
                 for (int j = 0; j < FATIMA_TAMEX_HITS; j++){  ///Hit 
                     
                    
                    FatTam_Fast_RefCh0[j] = pInput->fFat_Lead_Fast[1][j];
                    SC41L_ANA_lead_fat[j]=pInput->fFat_Lead_Fast[4][j];
                    SC41R_ANA_lead_fat[j]=pInput->fFat_Lead_Fast[5][j];
                    bPlasDet1_coin_lead_Fat[j]=pInput->fFat_Lead_Fast[6][j];
                    bPlasDet2_coin_lead_Fat[j]=pInput->fFat_Lead_Fast[7][j];
                 
                   
                        }      
                 for (int j = 0; j < FATIMA_TAMEX_HITS; j++){  
                        FatTam_Slow_RefCh0[j] = pInput->fFat_Lead_Slow[1][j];
              }
              }
            ////////////////////////////    
              ///Loop over channels 
              for(int i=1; i<=FATIMA_TAMEX_CHANNELS; i++){ ///Channel number
              
 ///**------------------------Fatima Lead Fast Time ----------------------**/    
   
                for (int j = 0; j < FATIMA_TAMEX_HITS; j++){  ///Hit 

                    lead_fast_fat[i][j] = pInput->fFat_Lead_Fast[i][j];  
		    
               if(lead_fast_fat[i][j]!=0)     hFat_Lead_Fast_T[i]->Fill(lead_fast_fat[i][j]);    
                    pOutput->pFat_Fast_LeadT[i][j] = lead_fast_fat[i][j];    
                    pOutput->pFat_LeadHits = hits_fat_lead; 
                     hits_fat_lead++;  
               
        
    ///**-----------------------Fatima Lead Fast Ref dT ----------------------------**/          
                          
//                     if(i>15 && pInput->fFat_Lead_PMT[16][j]>0 && pInput->fFat_Lead_PMT[i][j]>0) {   
                
        if(FatTam_Fast_RefCh0[j]>0 && lead_fast_fat[i][j]>0){
            lead_lead_fast_fat_Ref1[i][j] = (FatTam_Fast_RefCh0[j] -  lead_fast_fat[i][j])*CYCLE_TIME; 

        }
                              
              if(lead_lead_fast_fat_Ref1[i][j]!=0) hFat_lead_lead_fast_ref[i] ->Fill(lead_lead_fast_fat_Ref1[i][j]);
          
           
                }///End of fast lead
                
        ///**------------------------Fatima Lead Slow Time ----------------------**/    
   
                for (int j = 0; j < FATIMA_TAMEX_HITS; j++){  ///Hit 

                    lead_slow_fat[i][j] = pInput->fFat_Lead_Slow[i][j];  
		    
                    //hFat_Lead_Slow_T[i]->Fill(lead_slow_fat[i][j]);    
                    pOutput->pFat_Slow_LeadT[i][j] = lead_slow_fat[i][j];    
                 //   pOutput->pFat_LeadHits = hits_fat_lead; 
                   //  hits_fat_lead++;  
               
        
    ///**-----------------------Fatima Lead Slow Ref dT ----------------------------**/          
                          
//                     if(i>15 && pInput->fFat_Lead_PMT[16][j]>0 && pInput->fFat_Lead_PMT[i][j]>0) {   
                
        if(FatTam_Slow_RefCh0[j]>0 && lead_slow_fat[i][j]>0){
            lead_lead_slow_fat_Ref1[i][j] = (FatTam_Slow_RefCh0[j] -  lead_slow_fat[i][j])*CYCLE_TIME; 

        }
             // clear;make -j 8; go4analysis -file ~/lustre/gamma/DESPEC_S452_FILES/ts/S452f074_0062.lmd -disable-asf               
              if(lead_lead_slow_fat_Ref1[i][j]!=0){ 
                   //cout<<"i " << i << " j " << j <<" lead_lead_slow_fat_Ref1[i][j] " << lead_lead_slow_fat_Ref1[i][j]<<  endl;
                  hFat_lead_lead_slow_ref[i] ->Fill(lead_lead_slow_fat_Ref1[i][j]);
                  
              }
          
           
                }///End of slow lead
                         
      ///**---------------------Fatima Fast Trail ----------------------------------**/  
                                                            
               // pOutput->pFat_PMT_Trail_N[a][b] = pInput->fFat_PMT_Trail_N[a][b]; 
                
               for(int j=0; j< FATIMA_TAMEX_HITS; j++){ ///Hits 

                    
                    trail_fast_fat[i][j] = pInput->fFat_Trail_Fast[i][j];  
                   // hFat_Trail_Fast_T[i]->Fill(trail_fast_fat[i][j]);
//                    pOutput->pFat_TrailHits = hits_fat_trail; 
                    hits_fat_trail++;  
                    
                 
                    pOutput->pFat_Fast_TrailT[i][j] = trail_fast_fat[i][j];  
                     }
                     
    ///**---------------------Fatima Slow Trail ------------------**/  
                                                            
               // pOutput->pFat_PMT_Trail_N[a][b] = pInput->fFat_PMT_Trail_N[a][b]; 
                
               for(int j=0; j< FATIMA_TAMEX_HITS; j++){ ///Hits 

                    
                    trail_slow_fat[i][j] = pInput->fFat_Trail_Slow[i][j];  
                   // hFat_Trail_Slow_T[i]->Fill(trail_slow_fat[i][j]);
//                    pOutput->pFat_TrailHits = hits_fat_trail; 
                    //hits_fat_trail++;  
                    
                 
                    pOutput->pFat_Slow_TrailT[i][j] = trail_slow_fat[i][j];  
                     }
   ///**---------------------Fatima Fast ToT ----------------------------------**/  
              for(int j=0; j< FATIMA_TAMEX_HITS; j++){ 
                      if(j<FATIMA_TAMEX_HITS){
                // cout<< " pInput->fFat_Trail_PMT[i][j] " << pInput->fFat_Trail_PMT[i][j]<< " pInput->fFat_Lead_PMT[i][j] " <<pInput->fFat_Lead_PMT[i][j] <<" i " <<i << " j " << j << endl;
                  if(pInput->fFat_Trail_Fast[i][j] >0 && pInput->fFat_Lead_Fast[i][j]>0){ 
                
        ToT_fast_fat[i][j] = (pInput->fFat_Trail_Fast[i][j] - pInput->fFat_Lead_Fast[i][j]);   
             // cout<<"ToT_fat[i][j] " <<ToT_fat[i][j] << " i " << i << " j " << j << endl;
                ///Correction for overflows 
                if(ABS(ToT_fast_fat[i][j]) >(double)(COARSE_CT_RANGE>>1)) {   
                    
                       ToT_fast_fat[i][j] = CYCLE_TIME*(ToT_fast_fat[i][j] + COARSE_CT_RANGE);    
                      } 
                 else{  
                           ToT_fast_fat[i][j]= CYCLE_TIME*ToT_fast_fat[i][j];                         
                       }    
                       ///Gain matching  
               // pOutput-> pFat_ToTCalib[i][j] = fCal->Afat_TAMEX_ZAoQ[i]* ToT_fat[i][j] + fCal->Bfat_TAMEX_ZAoQ[i];
               pOutput-> pFat_Fast_ToTCalib[i][j] =ToT_fast_fat[i][j];
                       if(ToT_fast_fat[i][j]>0) {
                       // hFat_ToT_Fast_det[i] ->Fill(ToT_fast_fat[i][j]*0.1);   
                        
//                        if(i!=FatVME_TimeMachineCh1 && i!=FatVME_TimeMachineCh2 && i!=FATIMA_TAMEX_SC41L && i!=FATIMA_TAMEX_SC41R && i!=FATIMA_TAMEX_SC41L_Digi && i!=FATIMA_TAMEX_SC41R_Digi) hFat_ToT_Fast_Sum->Fill(ToT_fast_fat[i][j]*0.1);   
//                       
                       hFat_tamex_hit_pattern->Fill(i);  
                      
                    
                       ///Fill the Channel map and multiplicity here
                          Fat_tot_hits[i]++; 
                          hFat_tamex_multiplicity->Fill(Fat_tot_hits[i]);
                            
                            }
                          }
                        }         
                    }///end of fast fatima ToT
                    
    ///**---------------------Fatima Slow ToT ----------------------------------**/  
              for(int j=0; j< FATIMA_TAMEX_HITS; j++){ 
                 
                // cout<< " pInput->fFat_Trail_PMT[i][j] " << pInput->fFat_Trail_PMT[i][j]<< " pInput->fFat_Lead_PMT[i][j] " <<pInput->fFat_Lead_PMT[i][j] <<" i " <<i << " j " << j << endl;
                  if(pInput->fFat_Trail_Slow[i][j] >0 && pInput->fFat_Lead_Slow[i][j]>0){ 
                
        ToT_slow_fat[i][j] = (pInput->fFat_Trail_Slow[i][j] - pInput->fFat_Lead_Slow[i][j]);   
          
                ///Correction for overflows 
                if(ABS(ToT_slow_fat[i][j]) >(double)(COARSE_CT_RANGE>>1)) {   
                    
                       ToT_slow_fat[i][j] = CYCLE_TIME*(ToT_slow_fat[i][j] + COARSE_CT_RANGE);    
                      } 
                 else{  
                           ToT_slow_fat[i][j]= CYCLE_TIME*ToT_slow_fat[i][j];                         
                       }    
            ///Gain matching  (slow branch): I have to scale it
              
       ToT_slow_fat_calib[i][j] = (fCal->Afat_TAMEX[i-1] * pow(ToT_slow_fat[i][j]*0.01,3)+ fCal->Bfat_TAMEX[i-1] *pow(ToT_slow_fat[i][j]*0.01,2) + fCal->Cfat_TAMEX[i-1] *ToT_slow_fat[i][j]*0.01 + fCal->Dfat_TAMEX[i-1]);      
       
              
              //cout<<"ToT_slow_fat[i][j] " << ToT_slow_fat[i][j]<< endl;
//                pOutput-> pFat_Slow_ToTCalib[i][j] =ToT_slow_fat[i][j];
              // cout<<"ToT_slow_fat[i][j] " <<ToT_slow_fat[i][j] << " i " << i << " j " << j <<" pInput->fFat_Trail_Slow[i][j] " <<pInput->fFat_Trail_Slow[i][j] << " pInput->fFat_Lead_Slow[i][j] " <<pInput->fFat_Lead_Slow[i][j] << endl;
//         cout<<"event " << pInput->fevent_number << " i " << i <<" j" << j << endl;
//                             pOutput->pFat_Tamex_chan[j] = i;
//                             cout<<"pOutput->pFat_Tamex_chan[j] " <<pOutput->pFat_Tamex_chan[j]<< " j " << j <<" ToT_slow_fat[i][j]*0.01 " <<ToT_slow_fat[i][j]*0.01 << endl;
                       if(ToT_slow_fat[i][j]>0) {
                          // if(i==1){
//                            cout<<"event " << pInput->fevent_number << " i " << i <<" j" << j << endl;
//                             pOutput->pFat_Tamex_chan[j] = i;
//                             cout<<"pOutput->pFat_Tamex_chan[j] " <<pOutput->pFat_Tamex_chan[j]<< " j " << j <<" ToT_slow_fat[i][j]*0.01 " <<ToT_slow_fat[i][j]*0.01 << endl;
                        hFat_ToT_Slow_det[i] ->Fill(ToT_slow_fat[i][j]*0.01); 
                        hFat_ToT_Slow_det_calib[i] ->Fill(ToT_slow_fat_calib[i][j]); 
                          // }
                 if(i==11)   {  hFat_ToT_Slow_vs_Fast->Fill(ToT_slow_fat[11][j]*0.01,pOutput-> pFat_Fast_ToTCalib[11][j]*0.01);
             
                 }
                        
        if(i!=FatVME_TimeMachineCh1 && i!=FatVME_TimeMachineCh2 && i!=FATIMA_TAMEX_SC41L && i!=FATIMA_TAMEX_SC41R && i!=FATIMA_TAMEX_SC41L_Digi && i!=FATIMA_TAMEX_SC41R_Digi){ //hFat_ToT_Slow_Sum->Fill(ToT_slow_fat[i][j]*0.01);  
          //  hFat_ToT_Slow_Sum_Calib->Fill(ToT_slow_fat_calib[i][j]);      
                       }
                       
                       // hFat_tamex_hit_pattern->Fill(i);  
                    
                         // Fat_tot_hits++; 
                         // hFat_tamex_multiplicity->Fill(Fat_tot_hits);
                            
                            }
                        }         
                    //end of slow fatima ToT
                }
              }
}
            
  /**----------------------------------------------------------------------------------------------**/
 /**--------------------------------------  FATIMA VME ----------------------------------------------**/

void EventAnlProc::Make_Fatima_Histos(){


  for (int i=0; i<FAT_MAX_VME_CHANNELS; i++){
    hFAT_Energy[i] =  MakeTH1('D', Form("FATIMA_VME/Energy/EnergyCalib/LaBr_ECalib_Ch.%2d",i), Form("QDC Calib Ch. %2d",i), 4000,0,4000);
   // hFAT_QDCdt[i]   = MakeTH1('D', Form("FATIMA_VME/Timing/QDCdt/QDCdt%2d",i), Form("QDCdT Ch.%2d",i), 3201,-40,40);
    //hFAT_TDCCalib1[i] =  MakeTH1('D', Form("FATIMA/Timing/TDCCalib/LaBr_Tcalib%2d",i), Form("TDC channel Calib %2d",i), 1E5,0,2E5);
   
    hFAT_TDCdt_refCha[i] = MakeTH1('D', Form("FATIMA_VME/Timing/TDC_REF-TDC_dT/TDCdT_Cha_LaBr%02d_LaBr%02d", FAT_TDC_REF_CHANNEL, i), Form("TDC dt Channel All Multip LaBr%02d - LaBr%02d",FAT_TDC_REF_CHANNEL , i),4E4,-2E4,2E4);
    
    hFat_SC41L_TDC_dT[i] = MakeTH1('D', Form("FATIMA_VME/Timing/SC41-TDC_dT/TDCdT_SCI41_Cha_LaBr%02d", i), Form("TDC dt Channel All Multip SCI41 - LaBr%02d", i),250,-2E4,2E4);
    for (int j=0; j<6; j++){
       
    hFAT_TDC_bPlast_Cha[i][j] = MakeTH1('D', Form("FATIMA_VME/Timing/bPlastVMECh%2d/FatCh.%2d-bPlastVMECh.%2d",  j,i,j), Form("FatCh %2d -bPlast VME Ch. %2d", i,j),250, -2E4, 2E4);
    }
   
  }

    hFAT_EnergySum = MakeTH1('D', "FATIMA_VME/Energy/Fat_VME_EnergySum", "LaBr Energy (all detectors)",2000,0,4000);
    hFAT_EnergySum_Large = MakeTH1('D', "FATIMA_VME/Energy/Fat_VME_EnergySum_LargeRange", "LaBr Energy (all detectors)",20000,0,40000);
    hFAT_hits_QDC       = MakeTH1('D', "FATIMA_VME/Stats/QDC_FAThits", "FATIMA QDC hit pattern",50,0,50);
    hFAT_hits_TDC       = MakeTH1('D', "FATIMA_VME/Stats/TDC_FAThits", "FATIMA TDC hit pattern",50,0,50);
    hFAT_Multipl       = MakeTH1('D', "FATIMA_VME/Stats/Fatima_VME_Multiplicity", "FATIMA TDC Multiplicity",50,0,50);

     hFat_Energy_GainMonitor= MakeTH2('D',"FATIMA_VME/Stats/Fatima_GainMonitor","FATIMA Energy-Time Matrix",1240,16600,29000,2500,0,5000,"Time (minutes)","Fat Energy (keV)");
     
     hFat_time= MakeTH1('D', "FATIMA_VME/Stats/Fatima_Time", "",12400,16600,29000);
    
}
///-----------------------------------------------------------------------------------------------------------------------------------------------------------------------///
void EventAnlProc::Do_Fatima_Histos(EventUnpackStore* pInput, EventAnlStore* pOutput){
    
    Fat_time_mins =0; 
    if(Fat_WR>0) {Fat_time_mins =(Fat_WR/60E9)-26900000;
    hFat_time->Fill(Fat_time_mins);
    }
    Long64_t Fat_Ch_dT[FAT_MAX_VME_CHANNELS];
    Long64_t Fat_Ch_SC41L_dT[FAT_MAX_VME_CHANNELS];
    double Fat_bPlastCh_dT[FAT_MAX_VME_CHANNELS][6];
   
    for(int i=0; i< FAT_MAX_VME_CHANNELS; i++){
        Fat_Ch_dT[i]=0;
        Fat_Ch_SC41L_dT[i]=0;
        
        for(int j=0; j<6; j++){
            Fat_bPlastCh_dT[i][j]=0;
        }
    }
    pOutput->pFAT_WR = Fat_WR;
    pOutput->pFatmult =  Fatmult;
    
  
    
if(Fatmult > 0){
            hFAT_Multipl->Fill(Fatmult);
            
             
    //QDC and TDC outputs
    for (int i = 0; i<Fatmult; i++){
        
//         for(int l=0; l<Fat_Shift_array; l++){
//             
//           //  cout<<" Fat_time_mins " <<Fat_time_mins<< " FAT_WR_GFF_Low[l][Fat_QDC_ID[i]] "<<FAT_WR_GFF_Low[l][Fat_QDC_ID[i]]<< " l " << l << " Fat_QDC_ID[i] " <<Fat_QDC_ID[i] << " i " << i << endl;
//            if(Fat_time_mins >=FAT_WR_GFF_Low[l][Fat_QDC_ID[i]] && Fat_time_mins < FAT_WR_GFF_High[l][Fat_QDC_ID[i]]){
//               //cout<<"Fat_QDC_E[i] " <<Fat_QDC_E[i] << " i " << i << endl;
//                 Fat_QDC_E[i] = Fat_QDC_E[i] * FAT_FACTOR_GFF[l][Fat_QDC_ID[i]];
//              //  cout<<"FAT_WR_GFF_Low[l][Fat_QDC_ID[i]] " <<FAT_WR_GFF_Low[l][Fat_QDC_ID[i]]<<" FAT_WR_GFF_High[l][Fat_QDC_ID[i]] " <<FAT_WR_GFF_High[l][Fat_QDC_ID[i]] <<" l " << l << " Fat_QDC_ID[i] " <<Fat_QDC_ID[i] << " FAT_FACTOR_GFF[l][Fat_QDC_ID[i]]  " <<FAT_FACTOR_GFF[l][Fat_QDC_ID[i]] << " Fat_QDC_E[i] " << Fat_QDC_E[i]<<endl;
// //               cout<<"Fat_QDC_E[i] " <<Fat_QDC_E[i] << " FAT_FACTOR_GFF[l][Fat_QDC_ID[i]] " << FAT_FACTOR_GFF[l][Fat_QDC_ID[i]] << " l " << l << " Fat_QDC_ID[i] " << Fat_QDC_ID[i] <<" FAT_WR_GFF[l][Fat_QDC_ID[i]] " <<FAT_WR_GFF[l][Fat_QDC_ID[i]] << " i " << i <<  " Fat_time_mins " <<Fat_time_mins << endl;
//             }
//       }
        
        for(int l=0; l<Fat_Shift_array; l++){
            if(Fat_time_mins >=FAT_WR_GFF_Low[l]&& Fat_time_mins <= FAT_WR_GFF_High[l]){
                Fat_QDC_E[i] = Fat_QDC_E[i]* FAT_FACTOR_GFF[l] + FAT_COEFF_GFF[l];
            }
            else Fat_QDC_E[i]=0;
            
        }
        
      pOutput->pFat_QDC_ID[i] = Fat_QDC_ID[i];
      pOutput->pFat_QDC_E[i] = Fat_QDC_E[i];
      pOutput->pFat_QDC_T_coarse[i] = Fat_QDC_T_coarse[i];
      pOutput->pFat_QDC_T_fine[i] = Fat_QDC_T_fine[i];
      pOutput->pFat_QDC_E_Raw[i] = Fat_QDC_E_Raw[i];

      pOutput->pFat_TDC_ID[i] = Fat_TDC_ID[i];
      pOutput->pFat_TDC_T[i] = Fat_TDC_T[i];
      pOutput->pFat_TDC_T_Raw[i] = Fat_TDC_T_Raw[i];
    
      ///Fatima Energy 
      hFAT_Energy[Fat_QDC_ID[i]]->Fill(Fat_QDC_E[i]);    
      hFAT_EnergySum->Fill(Fat_QDC_E[i]);
      hFAT_EnergySum_Large->Fill(Fat_QDC_E[i]);
      
          
         ///Hit patterns
          hFAT_hits_QDC->Fill(Fat_QDC_ID[i]);
          hFAT_hits_TDC->Fill(Fat_TDC_ID[i]);
          
         
    if(Fat_time_mins>0 && Fat_QDC_E[i]>0){ hFat_Energy_GainMonitor->Fill(Fat_time_mins,Fat_QDC_E[i]);
   
    }
         
            
          /// Fatima Time PMT - PMT Ch.x Energy gated
         
               
                for(int j = 0; j < SC41mult; j++){
                  
                   Fat_Ch_SC41L_dT[Fat_TDC_ID[i]] =  (SC41[j] - Fat_TDC_T[i]);
         
                   if( Fat_Ch_SC41L_dT[Fat_TDC_ID[i]]!=0)  hFat_SC41L_TDC_dT[Fat_TDC_ID[i]]->Fill(Fat_Ch_SC41L_dT[Fat_TDC_ID[i]] );
              
                   
            }
     
     
      double t2, t1;
      if(Fat_TDC_T[i]!=0){
    t1 = Fat_TDC_T[i];
  
    if (Fat_TDC_ID[i] == 1){
        //  cout<<"t1 " << t1 << endl;
         //if (Fat_TDC_ID[i] == 1 && Fat_QDC_E[i] > 1310 && Fat_QDC_E[i] < 1390) {
     //cout << " t1 " << t1 << endl;
           for(int j = 0; j < Fatmult; j++){
                   if(Fat_TDC_T[j]){
                // if (Fat_QDC_E[j] > 1160 && Fat_QDC_E[j] < 1215) {
                 t2 = Fat_TDC_T[j];
        // cout << " t2 " << t2 << endl;
         //cout << " diff " << t1-t2 << endl;
                 hFAT_TDCdt_refCha[Fat_TDC_ID[j]]->Fill(int(t1-t2));

                 }
             // }
          }
        }
      }
     
          //   Fat_Ch_dT[Fat_TDC_ID[i]] =  (Fat_Cha_Ref_TDC - Fat_TDC_T[i]);
                    ///Reference channel dT
//                     if( Fat_TDC_ID[i]!=0){
//                       //  hFAT_TDCdt_refCha[Fat_TDC_ID[i]]->Fill(Fat_Ch_dT[Fat_TDC_ID[i]]);
//                     }
                    
                    ///bPlast channels dT VME
                     for(int j = 0; j < 6; j++){
                    Fat_bPlastCh_dT[Fat_TDC_ID[i]][j] =  (Fat_VME_bPlast[j] - Fat_TDC_T[i]);
                    
                    if( Fat_TDC_ID[i]!=0){
                        hFAT_TDC_bPlast_Cha[Fat_TDC_ID[i]][j]->Fill(Fat_bPlastCh_dT[Fat_TDC_ID[i]][j]);
                        }
                    }
                }
                
                
      pOutput->pSC40mult =  SC40mult;
      pOutput->pSC41mult =  SC41mult; 
 
        for(int i = 0; i < SC40mult; i++){
            
            pOutput->pSC40[i] = SC40[i];    
            
        }//End sc40 for fill
        
        for(int i = 0; i < SC41mult; i++){
            
            pOutput->pSC41[i] = SC41[i];    
            
        }//End sc41 for fill        
    }     
  //  cout<<"pInput->fFat_TMCh1mult " << pInput->fFat_TMCh1mult <<endl;
    for(int i =0; i<pInput->fFat_TMCh1mult; i++)  pOutput->pFat_TMCh1[i] = pInput->fFat_TMCh1[i];
    for(int i =0; i<pInput->fFat_TMCh2mult; i++)  pOutput->pFat_TMCh2[i] = pInput->fFat_TMCh2[i];
    for(int i =0; i<6; i++)                       pOutput->pFat_bplastChanT[i]=pInput->fFat_bplastChanT[i];
    
       pOutput->pstdcmult =  stdcmult;
       pOutput->pstdcmult =  stdcmult; 

       pOutput->pFat_TMCh1mult = pInput->fFat_TMCh1mult;
       pOutput->pFat_TMCh2mult = pInput->fFat_TMCh2mult;

		//Outputting singles TDC and QDC data
      for(int i = 0; i < stdcmult; i++){
            
         pOutput->pFat_TDC_Singles_t[i] = Fat_TDC_Singles_t[i];    
         pOutput->pFat_TDC_Singles_t[i] = Fat_TDC_Singles_t_Raw[i];    
         pOutput->pFat_TDC_Singles_ID[i] = Fat_TDC_Singles_ID[i];

         //cout << " i: " << i << " stdcmult " << stdcmult <<  " singles time " << Fat_TDC_Singles_t[i] << " singles tid " << Fat_TDC_Singles_ID[i] << endl;

      }

      for(int i = 0; i < sqdcmult; i++){
            
         pOutput->pFat_QDC_Singles_E[i] = Fat_QDC_Singles_E[i];    
         pOutput->pFat_QDC_Singles_E_Raw[i] = Fat_QDC_Singles_E_Raw[i];    
         pOutput->pFat_QDC_Singles_ID[i] = Fat_QDC_Singles_ID[i];
         pOutput->pFat_QDC_Singles_t_coarse[i] = Fat_QDC_Singles_t_coarse[i];    
         pOutput->pFat_QDC_Singles_t_fine[i] = Fat_QDC_Singles_t_fine[i];

         //cout << " i: " << i << " sqdcmult " << sqdcmult <<  " singles energy " << Fat_QDC_Singles_E[i] << " singles qid " << Fat_QDC_Singles_ID[i] << endl;

      }
     

}//end of fatima vme

    /**----------------------------------------------------------------------------------------------**/
    /**--------------------------------------  Germanium  ---------------------------------------------**/
    /**----------------------------------------------------------------------------------------------**/
    void EventAnlProc::Make_Germanium_Histos()
    {
      hGe_ESum = MakeTH1('I',"Germanium/Sum/Germanium_ESum_1keV","Germanium Energy Sum",20000,0,20000);
      hGe_ESum_halfkev = MakeTH1('I',"Germanium/Sum/Germanium_ESum_0_5keV","Germanium Energy Sum 0_5keV",10000,0,5000);
      
      hGe_Mult = MakeTH1('I',"Germanium/Stats/Germanium_Multiplicity","Germanium Multiplicity",30,0,30);
      
      hGe_SC41L = MakeTH1('I',"Germanium/SCI41/Germanium_SC41L_Ana","Germanium SC41 Left",5000,0,5000);
      hGe_SC41R = MakeTH1('I',"Germanium/SCI41/Germanium_SC41R_Ana","Germanium SC41 Right",5000,0,5000);
      hGe_SC41L_digi = MakeTH1('I',"Germanium/SCI41/Germanium_SC41L_Digi","Germanium SC41 Left",5000,0,5000);
      hGe_SC41R_digi = MakeTH1('I',"Germanium/SCI41/Germanium_SC41R_Digi","Germanium SC41 Right",5000,0,5000);
      
      hGe_ESum_largerange_OF = MakeTH1('I',"Germanium/Sum/Germanium_largerange_OF","Germanium Energy Sum (Overflow)",5000,0,5000);
      hGe_ESum_largerange_PU = MakeTH1('I',"Germanium/Sum/Germanium_largerange_PU","Germanium Energy Sum (Pileup)",5000,0,5000);
      hGe_Hit_Pat = MakeTH1('I',"Germanium/Stats/Germanium_Hit_Pat","Germanium Hit Pattern",Germanium_MAX_HITS,0,Germanium_MAX_HITS);
      
      hGe_Chan_E_Mat = MakeTH2('D',"Germanium/Sum/Germanium_E_Mat","Germanium Energy-Energy Matrix",2000,0,2000,2000,0,2000);
        
      hGe_Chan_E_vsDet = MakeTH2('D',"Germanium/Sum/Germanium_E_DetectorID","Germanium Energy vs Dectector Matrix",Germanium_MAX_HITS,0,Germanium_MAX_HITS,5000,0,5000);
      
      hGe_MultvsdT = MakeTH2('D',"Germanium/Stats/Germanium_Mult_vs_GamGamdT","Germanium Multiplicity vs Gamma Gamma dT",Germanium_MAX_HITS,0,Germanium_MAX_HITS,200,-1000,1000);
     
      hGe_AddbackSum = MakeTH1('I',"Germanium/Sum/Germanium_Addback_1keV","Germanium Addback Energy Sum 1keV",5000,0,5000);
      
      hGe_AddbackSum_halfkev = MakeTH1('I',"Germanium/Sum/Germanium_Addback_0_5keV","Germanium Addback Energy Sum 0.5keV",10000,0,5000);
      
       hGe_dTaddback = MakeTH1('I',"Germanium/Sum/Germanium_Addback_dT","Germanium Addback dT",100,-1000,1000);
       
       hGe_dTgammagamma = MakeTH1('D',"Germanium/Sum/Germanium_GammaGamma_dT","Germanium Gamma-Gamma dT",200,-1000,1000);
       
       hGe_CFdT_gammagamma = MakeTH1('D',"Germanium/Sum/Germanium_GammaGamma_CF_dT","Germanium Gamma-Gamma dT",2000,-1000,1000);
       
       hGe_Energy_GainMonitor= MakeTH2('D',"Germanium/Stats/Germanium_GainMonitor","Germanium Energy-Time Matrix",1240,16600,29000,2500,0,5000,"Time (minutes)","Ge Energy (keV)");
    
      for (int i=0; i<Germanium_MAX_DETS; i++)
      {
        for (int j = 0; j < Germanium_CRYSTALS; j++)
        {
          hGe_Chan_E[i][j] = MakeTH1('D',Form("Germanium/Energy_Ch_1keV/Germanium_E_Det_%2d_%1d",i, j), Form("Germanium Channel Energy Detector %2d Crystal %1d",i, j),5000,0,5000);
          
          hGe_Chan_E_halfkev[i][j] = MakeTH1('D',Form("Germanium/Energy_Ch_0_5keV/Germanium_E_0_5keV_Det_%2d_%1d",i, j), Form("Germanium Channel 0.5keV Energy Detector %2d Crystal %1d",i, j),10000,0,5000);
          
          hGe_Chan_Time_Diff[i][j] = MakeTH1('D',Form("Germanium/Time_diff/Germanium_Chan_Time_Diff_Det_%2d_Chan_%2d",i,j), Form("Germanium Channel Time Difference for Detector %2d Channel %2d",i,j),200,-1000,1000);
          
          hGe_Chan_Time_Diff_CF[i][j] = MakeTH1('D',Form("Germanium/Time_diff_CF/Germanium_Chan_Time_CF_Diff_Det_%2d_Chan_%2d",i,j), Form("Germanium Channel Time Difference with Const Frac for Detector %2d Channel %2d",i,j),2000,-1000,1000);
          
          
        }
      //  hGe_FatdT[j] = MakeTH1('I',Form("Correlations/Fatima_Geilieo/Fat_GAldT%2d",j),Form("Germanium Fatima dT Ch. %2d",j),2000,-1000,1000);
       // hGe_Chan_E2[j] = MakeTH1('D',Form("Germanium/Germanium_Energy2/Germanium_E2%2d",j), Form("Germanium Channel Energy Channel %2d",j),5000,0,5000);
        //hGe_Chan_Egate[j] = MakeTH1('D',Form("Germanium/gated energy/Germanium_Egate%2d",j), Form("Germanium Channel Energy Channel %2d",j),5000,0,5000);
        }
      //for (int k=0; k<32; k++){
    
    
    
        
        //hGe_Chan_Timedifference_new[k] = MakeTH1('D',Form("Germanium/Timediff_new/Germanium_Chan_T_Diff%2d",k), Form("Germanium Channel T Difference for %2d",k),2000,-1000,1000);
       // hGe_Time_Diff_vs_Energy[k] = MakeTH2('D',Form("Germanium/Germanium_dT_vs_Energy_Spectra/Germanium_dT_vs_E%2d",k), Form("Germanium Time Difference Vs Channel Energy Channel %2d",k),5000,0,5000,100,-1000,1000);
      //}
        }
    ///-----------------------------------------------------------------------------------------------------------------------------------------------------------------------///
    void EventAnlProc::Do_Germanium_Histos(EventAnlStore* pOutput)
    {
        Ge_time_mins=0;
      if(Ge_WR>0) Ge_time_mins =(Ge_WR/60E9)-26900000;
      
        pOutput->pGe_WR=Ge_WR;
        Gam_mult=0;
        dT_Ge=0;
//         timeFIRST_Ge=0;
        
       
        dT_Addback=0;
        dT_Ge_cfd=0;
        // Process hits once
       
        for (int i = 0; i < GeFired; i++)
        {
              int det = GeDet[i];
              int crys = GeCrys[i];
              
              pOutput->pGePileUp[i]=GePileUp[i];
              pOutput->pGeOverFlow[i]=GeOverFlow[i];
           // Skip pileup/overflow events
           if (GePileUp[i] && (det!=Germanium_SC41_Det  && det!=Germanium_SC41_Det_Digi && det!=Germanium_TimeMachine_Det))
           {
              hGe_ESum_largerange_PU->Fill(GeE_Cal[i]);
              continue;
   
            }
  
           if (GeOverFlow[i]&& (det!=Germanium_SC41_Det  && det!=Germanium_SC41_Det_Digi && det!=Germanium_TimeMachine_Det))
           {
             hGe_ESum_largerange_OF->Fill(GeE_Cal[i]);
             continue;
            }
            
	   if(det>-1){
           pOutput->pGe_Event_T[det][crys] = GeEventT[i];
          
           pOutput->pGe_T[det][crys] = Ge_Talign[i];
            
           pOutput->pGe_CF_T[det][crys] = Ge_cfd_Talign[i];
           pOutput->pGe_E[det][crys] = GeE_Cal[i];
           pOutput->pGe_E_Raw[det][crys] = GeE[i];
  
          
         
         
           if(det!=Germanium_SC41_Det  && det!=Germanium_SC41_Det_Digi && det!=Germanium_TimeMachine_Det){
           hGe_ESum->Fill(GeE_Cal[i]);
           
             hGe_Hit_Pat->Fill(det * Germanium_CRYSTALS + crys);
        
           hGe_ESum_halfkev->Fill(GeE_Cal[i]);
//            cout<<"det " << det <<endl;
            hGe_Chan_E_vsDet->Fill(det,GeE_Cal[i]);
            
           
            if(Ge_time_mins>0 && GeE_Cal[i]>0)  hGe_Energy_GainMonitor->Fill(Ge_time_mins,GeE_Cal[i]);
           
            
           
           hGe_Chan_E[det][crys]->Fill(GeE_Cal[i]);
           hGe_Chan_E_halfkev[det][crys]->Fill(GeE_Cal[i]);
     
     //cout<<"2GeE_Cal[i] " << GeE_Cal[i] <<" det " << det << " crys " << crys <<endl;
           
           }
           // Cross correlations
    if ( det!=Germanium_TimeMachine_Det&& det!=Germanium_SC41_Det  && det!=Germanium_SC41_Det_Digi){
        Gam_mult++;
        
         //Time alignment (detector vs all)
                   
                 //Aligned dT 
//         if(det!=0 && crys!=1){
//             if(RefTGe!=0){
//                    dT_Align= Ge_Talign[i]-RefTGe;
//                    hGe_dTgammagamma->Fill(dT_Align);
//                    hGe_Chan_Time_Diff[det][crys]->Fill(dT_Align);
//                    
// //                    cout<<"2event " << event_number <<" det " << det << " crys " << crys << " dT_Align " << dT_Align <<" Ge_Talign[i] " << Ge_Talign[i] << " RefTGe " << R/*efTGe << " i " << i << endl;
//             }
            /*        ///Constant fraction time testing 03.02.21
                    if(RefCFDGe!=0){
                        //CFD Time alignment
                     
                        //Aligned CFD dT
                        dT_CFD_Align= Ge_cfd_Talign[i]-RefCFDGe;
                        hGe_CFdT_gammagamma->Fill(dT_CFD_Align);
                        hGe_Chan_Time_Diff_CF[det][crys]->Fill(dT_CFD_Align);
                    }
        }*/     
            
            
            
           for (int j = 0; j < GeFired; j++)
           {
              if (i == j) continue;
      
              if(GeE_Cal[i]>0 && GeE_Cal[j]>0){
                  //dT Germanium raw
                  //dT_Ge= GeT[i]-GeT[j];
                    dT_Align= Ge_Talign[i]-Ge_Talign[j];
                  hGe_Chan_Time_Diff[det][crys]->Fill(dT_Align);
         
                   dT_CFD_Align= Ge_cfd_Talign[i]-Ge_cfd_Talign[j];
                   hGe_Chan_Time_Diff_CF[det][crys]->Fill(dT_CFD_Align);
         
         
              hGe_Mult->Fill(Gam_mult);
           

              hGe_MultvsdT->Fill(Gam_mult,dT_CFD_Align);
              
              
              
              ///Gamma-Gamma Time gate
              if((dT_CFD_Align)>fCorrel->GGe1_Ge2_Low && (dT_CFD_Align)< fCorrel->GGe1_Ge2_High && det!=Germanium_SC41_Det  && det!=Germanium_SC41_Det_Digi ){
              hGe_Chan_E_Mat->Fill(GeE_Cal[i], GeE_Cal[j]);
                        }
                    }
                }
            }  
       }
    }
       
       
       ////ADDBACK
        static const long dT_addback = 100;
        static const double energy_thres_addback = 100;
               
        // Detector addback
        for (int i = 0; i < Germanium_MAX_DETS; i++)
        {
            double E[Germanium_CRYSTALS] = { 0 };
            long T[Germanium_CRYSTALS] = { 0 };
            int n[Germanium_CRYSTALS] = { 0 };
            int crys[Germanium_CRYSTALS] = { 0 };
            int v = 0;
            for (int j = 0; j < Germanium_CRYSTALS; j++)
                {
              if (pOutput->pGe_E[i][j] == 0) continue;
              bool added = false; 
        
              // Try to addback to an existing hit
              for (int k = 0; k < v; k++)
              {
                  dT_Addback=T[k] - pOutput->pGe_T[i][j];
                  hGe_dTaddback->Fill(dT_Addback);
        if (T[k] - pOutput->pGe_T[i][j] < dT_addback){
             hGe_dTaddback->Fill(T[k] - pOutput->pGe_T[i][j]);
            if(pOutput->pGe_E[i][j]>energy_thres_addback){
                
                  E[k] += pOutput->pGe_E[i][j];
                  T[k] = (T[k] + pOutput->pGe_T[i][j]) / (n[k] + 1);
                  n[k] += 1;
                  added = true;
                    }
                }
              }
               
              // Add to a new hit
              if (!added)
              {
                T[v] = pOutput->pGe_T[i][j];
                E[v] = pOutput->pGe_E[i][j];
                crys[v] = j;
                n[v] = 1;
                v++;
              }
            }         
            // Fill and write to Tree the addback energies
            for (int j = 0; j < v; j++)
            {
                
                pOutput->pGe_EAddback[i][crys[j]] = E[j];
                pOutput->pGe_T[i][crys[j]] = T[j];
                
              ///  SCI41 Signals
               if(pOutput->pGe_EAddback[Germanium_SC41_Det][Germanium_SC41L_Crystal]>0) hGe_SC41L->Fill(pOutput->pGe_EAddback[Germanium_SC41_Det][Germanium_SC41L_Crystal]);
               
               if(pOutput->pGe_EAddback[Germanium_SC41_Det][Germanium_SC41R_Crystal]>0) hGe_SC41R->Fill(pOutput->pGe_EAddback[Germanium_SC41_Det][Germanium_SC41R_Crystal]);
               
               if(pOutput->pGe_EAddback[Germanium_SC41_Det_Digi][Germanium_SC41R_Crystal_Digi]>0) hGe_SC41R_digi->Fill(pOutput->pGe_EAddback[Germanium_SC41_Det_Digi][Germanium_SC41R_Crystal_Digi]);
               
               if(pOutput->pGe_EAddback[Germanium_SC41_Det_Digi][Germanium_SC41L_Crystal_Digi]>0) hGe_SC41L_digi->Fill(pOutput->pGe_EAddback[Germanium_SC41_Det_Digi][Germanium_SC41L_Crystal_Digi]);
                
               
                 if(GePileUp[i]==0 && GeOverFlow[i]==0 ){
           
            if(i!=Germanium_SC41_Det && i!=Germanium_SC41_Det_Digi && i!=Germanium_TimeMachine_Det)   {     
                hGe_AddbackSum->Fill(E[j]);
                hGe_AddbackSum_halfkev->Fill(E[j]);
                    }
                }
            }
        }
    }//end of Do_Germanium_Histos()
    
//--------------------------------------------------------------------------------------------------------------------//
// TH1I* EventAnlProc::MakeH1I(const char* fname,
//                             const char* hname,
//                             Int_t nbinsx,
//                             Float_t xmin, Float_t xmax,
//                             const char* xtitle,
//                             Color_t linecolor,
//                             Color_t fillcolor,
//                             const char* ytitle) {
// //    TNamed* res = TestObject((getfunc)&TGo4EventProcessor::GetHistogram, fname, hname);
// //    if (res!=0) return dynamic_cast<TH1I*>(res);
// 
//    TH1I* histo = new TH1I(hname, hname, nbinsx, xmin, xmax);
//    histo->SetXTitle(xtitle);
//    if (ytitle) histo->SetYTitle(ytitle);
//    histo->SetLineColor(linecolor);
//    histo->SetFillColor(fillcolor);
//    AddHistogram(histo, fname);
//    return histo;
// }
//-----------------------------------------------------------------------------------------------------------------------------//

// TH2I* EventAnlProc::MakeH2I(const char* fname,
//                              const char* hname,
//                              Int_t nbinsx, Float_t xmin, Float_t xmax,
//                              Int_t nbinsy, Float_t ymin, Float_t ymax,
//                              const char* xtitle, const char* ytitle,
//                              Color_t markercolor) {
// //    TNamed* res = TestObject((getfunc)&TGo4EventProcessor::GetHistogram, fname, hname);
// //    if (res!=0) return dynamic_cast<TH2I*>(res);
// 
//    TH2I* histo = new TH2I(hname, hname, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
//    histo->SetMarkerColor(markercolor);
//    histo->SetXTitle(xtitle);
//    histo->SetYTitle(ytitle);
//    AddHistogram(histo, fname);
//    return histo;
// }
//-----------------------------------------------------------------------------------------------------------------------------//

TGo4WinCond* EventAnlProc::MakeWindowCond(const char* fname,
                                           const char* cname,
                                           float left,
                                           float right,
                                           const char* HistoName) {
  // TNamed* res = TestObject((getfunc)&TGo4EventProcessor::GetAnalysisCondition, fname, cname);
   //if (res!=0) return dynamic_cast<TGo4WinCond*>(res);

   TGo4WinCond* cond = new TGo4WinCond((Text_t*)cname);
   cond->SetValues(left, right);
   cond->Enable();
   if (HistoName!=0)
     cond->SetHistogram(HistoName);
   AddAnalysisCondition(cond, fname);
   return cond;
}
//-----------------------------------------------------------------------------------------------------------------------------//

TGo4PolyCond* EventAnlProc::MakePolyCond(const char* fname,
                                          const char* cname,
                                          Int_t size,
                                          Float_t (*points)[2],
                                          const char* HistoName) {
   //TNamed* res = TestObject((getfunc)&TGo4EventProcessor::GetAnalysisCondition, fname, cname);
   //if (res!=0) return dynamic_cast<TGo4PolyCond*>(res);

   Float_t fullx[size+1], fully[size+1];
   int numpoints = size;

   for (int i=0;i<numpoints;i++) {
     fullx[i] = points[i][0];
     fully[i] = points[i][1];
   }

   // connect first and last points
   if ((fullx[0]!=fullx[numpoints-1]) || (fully[0]!=fully[numpoints-1])) {
      fullx[numpoints] = fullx[0];
      fully[numpoints] = fully[0];
      numpoints++;
   }

   TCutG mycat("initialcut", numpoints, fullx, fully);
   TGo4PolyCond* cond = new TGo4PolyCond((Text_t*)cname);
   cond->SetValues(&mycat);
   cond->Enable();
   if (HistoName!=0)
     cond->SetHistogram(HistoName);
   AddAnalysisCondition(cond, fname);
   return cond;
}
///-------------------------------------------------------------------------------------------------------
void EventAnlProc::FRS_Gates(){
  Int_t i;
  ifstream    file;
   string line;
   Float_t frs_wr_a;
   Float_t frs_wr_b;
   Float_t frs_wr_i;
   Float_t frs_wr_j;
   Float_t z1_shift_value;
   Float_t z2_shift_value;
   Float_t aoq_shift_value;
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
    sscanf(line.c_str(),"%f %f %f",&frs_wr_i,&frs_wr_j,&aoq_shift_value);

    FRS_WR_i[d]=frs_wr_i;
    FRS_WR_j[d]=frs_wr_j;
    AoQ_shift_value[d]=aoq_shift_value;
    AoQ_Shift_array=d;
       d++;
     }
  
  file.close();
  
   file.open("Configuration_Files/2D_Gates/ID_x2AoQ.txt");
        
    for (i = 0; i < MAX_FRS_GATE; i++){
         for (int j = 0; j < MAX_FRS_PolyPoints ; j++){
       if(IsData(file)) file >> XX2_AoQ[i][j]>> YX2_AoQ[i][j] ;
     // cout<<" XX2_AoQ[i][j] " << XX2_AoQ[i][j] << " YX2_AoQ[i][j] " <<YX2_AoQ[i][j] << " i " << i << " j " << j << endl;
         }
    }
  file.close();
  
  
 ///--------------------------------------------------------------------------------
  file.open("Configuration_Files/2D_Gates/ID_x4AoQ.txt");

    for (i = 0; i < MAX_FRS_GATE; i++){
        for (int j = 0; j < MAX_FRS_PolyPoints ; j++){
       if(IsData(file)) file >>XX4_AoQ[i][j]>> YX4_AoQ[i][j] ;
        }
    }
  file.close();
  
  
 ///--------------------------------------------------------------------------------
  
  file.open("Configuration_Files/2D_Gates/ID_Z_Z2.txt");
 for (i = 0; i < MAX_FRS_GATE; i++){
    for (int j = 0; j < MAX_FRS_PolyPoints ; j++){
       if(IsData(file)) file >> X_ZZ2[i][j]>> Y_ZZ2[i][j] ;
    
    }
    }
  file.close();
  
  
 ///--------------------------------------------------------------------------------
      file.open("Configuration_Files/2D_Gates/ID_ZvsAoQ.txt");
    
    for (i = 0; i < MAX_FRS_GATE; i++){
        for(int j=0; j<MAX_FRS_PolyPoints; j++){
       if(IsData(file)) file >> X_ZAoQ[i][j]>> Y_ZAoQ[i][j] ;
       
     //  cout<<"X_ZAoQ[i][j] " <<X_ZAoQ[i][j] <<" Y_ZAoQ[i][j] " <<Y_ZAoQ[i][j] << " i " << i << endl;
        }
    }
  file.close();
  
  ///--------------------------------------------------------------------------------
      file.open("Configuration_Files/2D_Gates/ID_dEdeg_Z1.txt");
    
    for (i = 0; i < MAX_FRS_GATE; i++){
        for(int j=0; j<MAX_FRS_PolyPoints; j++){
       if(IsData(file)) file >> X_dEdeg[i][j]>> Y_dEdeg[i][j] ;
    }
    }
  file.close();
}
///-------------------------------------------------------------------------------------------------------
 int EventAnlProc::IsData(ifstream &f) {
        char dum;
        char dumstr[300];
        int retval = 0;

        /* 'operator >>' does not read End-of-line, therefore check if read 
            character is not EOL (10) */
        do {
            dum = f.get();
            if (dum == '#')    // comment line => read whole line and throw it away
            f.getline(dumstr,300);
        }
        while ((dum == '#') || ((int)dum == 10)); 

        f.unget();   // go one character back
        retval = 1;
        return retval;
    }
///-------------------------------------------------------------------------------------------------------

void EventAnlProc::get_used_systems(){
    for(int i = 0;i < 6;i++) Used_Systems[i] = false;

  ifstream data("Configuration_Files/DESPEC_General_Setup/Used_Systems.txt");
  if(data.fail()){
    cerr << "Could not find Used_Systems config file!" << endl;
    exit(0);
  }
  int i = 0;
  int id = 0;
  string line;
  char s_tmp[100];
  while(data.good()){
    getline(data,line,'\n');
    if(line[0] == '#') continue;
    sscanf(line.c_str(),"%s %d",s_tmp,&id);
    Used_Systems[i] = (id == 1);
    i++;
  }
  string DET_NAME[7] = {"FRS","AIDA","PLASTIC","FATIMA_VME","FATIMA_TAMEX","Germanium","FINGER"};


}

void EventAnlProc::Fat_TimeCorrection(EventUnpackStore* pInput){
   ///Do the dT time corrections
    for(uint k=0; k<pInput->fFat_mult; k++){
      // cout<<" BEFORE pInput->fFat_TDC_Time[i] " << pInput->fFat_TDC_Time[k] << " k " << k << endl;
        ///This was for S480
//         if(cInputMain->pFat_TDC_ID[k] == 6 || cInputMain->pFat_TDC_ID[k] == 10 || cInputMain->pFat_TDC_ID[k] == 13 || cInputMain->pFat_TDC_ID[k] == 22 || cInputMain->pFat_TDC_ID[k] == 23 || cInputMain->pFat_TDC_ID[k] == 32 || cInputMain->pFat_TDC_ID[k] == 33 || cInputMain->pFat_TDC_ID[k] == 34 || cInputMain->pFat_TDC_ID[k] == 35 ){
//         cInputMain->pFat_TDC_T[k] = 0.;
//            }
           
        if(pInput->fFat_TDC_Time[k]>0){

     pInput->fFat_TDC_Time[k] = pInput->fFat_TDC_Time[k]+fCal->TFatTDC_Chref_dT[pInput->fFat_TDC_ID[k]];
     
   
        }
     }
}
// void EventAnlProc::Fat_GainCorrection(){
//      ifstream    file;
//      string line;
//      Int_t f=0;
//      Int_t fat_det_tmp;
//      float_t fat_peak_tmp;
//      float_t fat_factor_tmp;
//      float_t fat_wr_tmp_low;
//      float_t fat_wr_tmp_high;
//     
//       file.open("Configuration_Files/FATIMA/Gain_Factor_Fatima.txt");
//    while(file.good()){
//        cout<<"file good " << endl;
//         getline(file,line,'\n');
//     if(line[0] == '#') continue;
//     sscanf(line.c_str(),"%d %f %f %f %f",&fat_det_tmp,&fat_peak_tmp,&fat_factor_tmp,&fat_wr_tmp_low, &fat_wr_tmp_high);
//       
//     FAT_DET_GFF[f]=fat_det_tmp;
//     //FAT_PEAK_GFF[f][fat_det_tmp]=fat_peak_tmp;
//     FAT_FACTOR_GFF[f][fat_det_tmp]=fat_factor_tmp;
//     FAT_WR_GFF_Low[f][fat_det_tmp]=fat_wr_tmp_low;
//     FAT_WR_GFF_High[f][fat_det_tmp]=fat_wr_tmp_high;
//     Fat_Shift_array=f;
//     // cout<<"FAT_FACTOR_GFF[f][fat_det_tmp] " <<FAT_FACTOR_GFF[f][fat_det_tmp] << " f " << f << " fat_det_tmp " <<fat_det_tmp <<"  FAT_WR_GFF_Low[f][fat_det_tmp] " << FAT_WR_GFF_Low[f][fat_det_tmp] <<" FAT_WR_GFF_High[f][fat_det_tmp] "<<FAT_WR_GFF_High[f][fat_det_tmp]<< endl;
//        f++;
// 
//      }
//   
//   file.close();
//        
//    }
   
   
   void EventAnlProc::Fat_GainCorrection(){
     ifstream    file;
     string line;
     Int_t f=0;
     float_t fat_coeff_tmp;
     float_t fat_factor_tmp;
     float_t fat_wr_tmp_low;
     float_t fat_wr_tmp_high;
    
      file.open("Configuration_Files/FATIMA/Gain_Factor_Fatima_Linear.txt");
   while(file.good()){
       cout<<"file good " << endl;
        getline(file,line,'\n');
    if(line[0] == '#') continue;
    sscanf(line.c_str(),"%f %f %f %f",&fat_factor_tmp,&fat_coeff_tmp,&fat_wr_tmp_low, &fat_wr_tmp_high);
      
    //FAT_DET_GFF[f]=fat_det_tmp;
    //FAT_PEAK_GFF[f][fat_det_tmp]=fat_peak_tmp;
    FAT_FACTOR_GFF[f]=fat_factor_tmp;
    FAT_COEFF_GFF[f]=fat_coeff_tmp;
    FAT_WR_GFF_Low[f]=fat_wr_tmp_low;
    FAT_WR_GFF_High[f]=fat_wr_tmp_high;
    Fat_Shift_array=f;
    
   // cout<<"FAT_WR_GFF_High[f]" << FAT_WR_GFF_High[f] << " FAT_COEFF_GFF[f] " << FAT_COEFF_GFF[f] << endl;
    // cout<<"FAT_FACTOR_GFF[f][fat_det_tmp] " <<FAT_FACTOR_GFF[f][fat_det_tmp] << " f " << f << " fat_det_tmp " <<fat_det_tmp <<"  FAT_WR_GFF_Low[f][fat_det_tmp] " << FAT_WR_GFF_Low[f][fat_det_tmp] <<" FAT_WR_GFF_High[f][fat_det_tmp] "<<FAT_WR_GFF_High[f][fat_det_tmp]<< endl;
       f++;

     }
  
  file.close();
       
   }
     
  
//-----------------------------------------------------------------------------------------------------------------------------//
//                                                            END                                                              //
//-----------------------------------------------------------------------------------------------------------------------------//
