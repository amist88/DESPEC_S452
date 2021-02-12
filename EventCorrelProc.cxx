// $Id: EventCorrelProc.cxx 754 2011-05-18 11:04:52Z adamczew $
//Adapted for DESPEC by A.K.Mistry 2020
//-----------------------------------------------------------------------
    //       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum für Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

#include "EventCorrelProc.h"

#include <cstdlib>
#include <math.h>

#include "TH1.h"
#include "TH2.h"
#include "Riostream.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

#include "TGo4WinCond.h"
#include "TGo4CondArray.h"
#include "TGo4Analysis.h"

#include "TGo4Picture.h"

#include "EventCorrelStore.h"
#include "EventUnpackStore.h"
#include "EventAnlStore.h"

#include "TAidaConfiguration.h"



//-----------------------------------------------------------
EventCorrelProc::EventCorrelProc() :
  TGo4EventProcessor()/*,
  fParam1(0),
  fTimeDiff(0),
  fGatedHist(0),
  fCoincQ1A1(0),
  fCoincQ1T1(0),
  fconHis1(0)*/
  
{
 
}
   AidaHitPID jPID;
//-----------------------------------------------------------
EventCorrelProc::EventCorrelProc(const char* name) :
   TGo4EventProcessor(name)
{
    cout << "**** EventCorrelProc: Create" << endl;
     fCorrel = (CorrelParameter*) GetParameter("CorrelPar"); 
       if(fCorrel) fCorrel->PrintParameter(0,0);
     fCal = (CalibParameter*) GetParameter("CalibPar"); 
     
    
  tag_all.clear();
  ts_all.clear();
  GeE_all.clear();

  get_used_systems();
  Ge_2DPromptFlashCut();
  Fat_2DPromptFlashCut();
 // Fat_TimeCorrection();
  FRS_Gates_corrProc();
  

 }
//-----------------------------------------------------------
EventCorrelProc::~EventCorrelProc()
{
  cout << "**** EventCorrelProc: Delete" << endl;
}

//-----------------------------------------------------------
Bool_t EventCorrelProc::BuildEvent(TGo4EventElement* dest)
{
  Bool_t isValid=kFALSE; // validity of output event
  
  EventAnlStore* cInput  = (EventAnlStore*) GetInputEvent();
  EventCorrelStore* cOutput = (EventCorrelStore*) dest;

  if((cInput==0) || !cInput->IsValid()){ /// input invalid
    cOutput->SetValid(isValid); /// invalid
    return isValid; /// must be same is for SetValid
  }
    isValid=kTRUE;
    static bool create =false;
    if(!create){
        
    Make_Timemachine_Histos();
        
    if(fCorrel->GSetup_corr_FRS_Aida==true)   Make_FRS_AIDA_Histos();
        
    if(fCorrel->GSetup_corr_FRS_Ge==true)  Make_FRS_Prompt_Ge_Histos();
    
    if(fCorrel->GSetup_corr_FRS_Ge_long==true) {
        Make_FRS_LongIso_Ge_Histos();
        Make_FRS_LongIso_Fatima_Histos();
    }
    
    if(fCorrel->GSetup_corr_FRS_fat==true) Make_FRS_Prompt_Fat_Histos(); 
         
    if(fCorrel->GSetup_corr_Beta_Gamma==true) Make_Beta_Gamma_Histos();
        
    
     create=true;
   
    }
   
    
   
        Process_Timemachine(cInput, cOutput);
   
      if(Used_Systems[0]==1) { 
///Demand at least FRS to be activated to do correlations
          Fat_TimeCorrection(cInput);
          if(fCorrel->GSetup_corr_FRS_Aida==true)Process_FRS_AIDA(cInput, cOutput); 
       
          if(fCorrel->GSetup_corr_FRS_Ge==true) Process_FRS_Prompt_Ge(cInput, cOutput);
          
          if(fCorrel->GSetup_corr_FRS_Ge_long==true){
              Process_FRS_LongIso_Ge(cInput, cOutput);
              Process_FRS_LongIso_Fat(cInput, cOutput);
          }
          
          if(fCorrel->GSetup_corr_FRS_fat==true)Process_FRS_Prompt_Fat(cInput, cOutput); 
          
          if(fCorrel->GSetup_corr_Beta_Gamma==true) Process_Beta_Gamma(cInput, cOutput); 
                                                     
          
      }
  
  event_number = cInput->pEvent_Number;
  cOutput->cEvent_number = event_number;
  
  ///White Rabbit inputs
    AIDA_WR = cInput->pAIDA_WR;   
    FRS_WR = cInput->pFRS_WR;
    bPLAS_WR = cInput->pbPLAS_WR;
    FAT_WR = cInput->pFAT_WR;
    GAL_WR = cInput->pGe_WR;
   
    cOutput->cAIDA_WR = cInput->pAIDA_WR;   
    cOutput->cFRS_WR = cInput->pFRS_WR;
    cOutput->cbPlast_WR = cInput->pbPLAS_WR;
    cOutput->cFAT_WR = cInput->pFAT_WR;
    cOutput->cGAL_WR = cInput->pGe_WR;
    
      ///FRS Outputs    
    cOutput->cFRS_AoQ = cInput->pFRS_AoQ;   
    cOutput->cFRS_ID_x2 = cInput-> pFRS_ID_x2;  
    cOutput->cFRS_ID_x4 = cInput-> pFRS_ID_x4;  
    cOutput->cFRS_z = cInput-> pFRS_z;  
    cOutput->cFRS_z2 = cInput-> pFRS_z2;
    
   
//    
    
   //  cout<<"AIDA_WR " << AIDA_WR <<" FAT_WR " << FAT_WR <<" AIDA_WR - FAT_WR "<< AIDA_WR - FAT_WR<< endl;
  ///Gates input TESTING!!!
//     cInput->pFRS_Z_Z2_pass=true;
//     cInput->pFRS_x2AoQ_pass=true;
 

 cOutput->SetValid(isValid);
  return isValid;
}
   /**----------------------------------------------------------------------------------------------**/
 /**----------------------------------    Timemachine   -------------------------**/
 /**----------------------------------------------------------------------------------------------**/
 void EventCorrelProc::Make_Timemachine_Histos(){
     hFatVME_TMdT= MakeTH1('I',"TimeMachine/Systems_dT/Fatima_VME_TimeMachinedT","Fatima VME TM Ch.1 -Ch.2 ",200,0,2000);
     
     hFatTAMEX_TMdT= MakeTH1('I',"TimeMachine/Systems_dT/Fatima_Tamex_TimeMachinedT","Fatima TAMEX TM Ch.1 -Ch.2 ",200,0,2000);
     hGe_TMdT= MakeTH1('I',"TimeMachine/Systems_dT/Ge_FEBEX_TimeMachinedT","Germanium FEBEX TM Ch.1 -Ch.2 ",200,0,2000);
     
     hbPlastic_TMdT= MakeTH1('I',"TimeMachine/Systems_dT/bPlast_TAMEX_TimeMachinedT","bPlastic TAMEX TM Ch.1 -Ch.2 ",200,0,2000);
     hAida_TMdT= MakeTH1('I',"TimeMachine/Systems_dT/AIDA_TimeMachinedT","AIDA TM Ch.1 -Ch.2 ",200,0,2000);
     
     
      hFatVME_FatTAMEX_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/FatimaVME_FatTAMEX","Time Machine FATIMA VME vs Fatima TAMEX ", 200,0,2000, 200,0,2000,"Fatima VME TimeMachine", "Fatima TAMEX TimeMachine");
      
      hFatVME_Ge_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/FatimaVME_Germanium","Time Machine FATIMA VME vs Germanium ", 200,0,2000, 200,0,2000,"Fatima VME TimeMachine", "Germanium FEBEX TimeMachine");
     
      hFatVME_bPlast_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/FatimaVME_bPlast","Time Machine FATIMA VME vs bPlast ", 200,0,2000, 200,0,2000,"Fatima VME TimeMachine", "bPlastic TAMEX TimeMachine");
      
      hFatVME_AIDA_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/FatimaVME_AIDA","Time Machine FATIMA VME vs bPlast ", 200,0,2000, 200,0,2000,"Fatima VME TimeMachine", "AIDA TimeMachine");
      
      hFatTAMEX_Ge_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/FatimaTAMEX_Germanium","Time Machine FATIMA TAMEX vs Germanium ", 200,0,2000, 200,0,2000,"Fatima TAMEX TimeMachine", "Germanium FEBEX TimeMachine");
      
      hFatTAMEX_bPlast_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/FatimaTAMEX_bPlast","Time Machine FATIMA TAMEX vs bPlastic TAMEX ", 200,0,2000, 200,0,2000,"Fatima TAMEX TimeMachine", "bPlast TAMEX TimeMachine");
     
      hFatTAMEX_AIDA_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/FatimaTAMEX_AIDA","Time Machine FATIMA VME vs AIDA ", 200,0,2000, 200,0,2000,"Fatima TAMEX TimeMachine", "AIDA TimeMachine");
      
      hGe_bPlast_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/Germanium_bPlast","Time Machine Germanium vs bPlastic TAMEX", 200,0,2000, 200,0,2000,"Germanium FEBEX TimeMachine","bPlast TAMEX TimeMachine");
      
      hGe_AIDA_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/Germanium_AIDA","Time Machine Germanium vs AIDA", 200,0,2000, 200,0,2000,"Germanium FEBEX TimeMachine","AIDA TimeMachine");
      
      hAIDA_bPlast_TM = MakeTH2('D',"TimeMachine/Correlation_matrices/AIDA_bPlastic","Time Machine AIDA vs bPlastic TAMEX", 200,0,2000, 200,0,2000,"AIDA TimeMachine","bPlastic TAMEX TimeMachine");
}
 void EventCorrelProc::Process_Timemachine(EventAnlStore* cInputMain, EventCorrelStore* cOutput){
 
     ///Fatima VME
    for(int aa=0; aa<cInputMain->pFat_TMCh1mult; aa++){
    
    
             if(cInputMain->pFat_TMCh1[aa] !=0 && cInputMain->pFat_TMCh2[aa] !=0){                 
                 FatimaVME_TimeMachine_dT[aa] =  cInputMain->pFat_TMCh2[aa]-cInputMain->pFat_TMCh1[aa];
                 hFatVME_TMdT->Fill(FatimaVME_TimeMachine_dT[aa]);
		 cOutput->cFatimaVME_TimeMachine_dT[aa] =  FatimaVME_TimeMachine_dT[aa]; 

            }
        }
    
     ///Fatima TAMEX
     for(int b=0; b<cInputMain->pFat_LeadHits; b++){
        if(cInputMain->pFat_LeadT[FatTAMEX_TimeMachineCh1][b]!=0 && cInputMain->pFat_LeadT[FatTAMEX_TimeMachineCh2][b]!=0){ 
                FatimaTAMEX_TimeMachine_dT[b] = (cInputMain->pFat_LeadT[FatTAMEX_TimeMachineCh2][b]-cInputMain->pFat_LeadT[FatTAMEX_TimeMachineCh1][b])*5;
                hFatTAMEX_TMdT->Fill(FatimaTAMEX_TimeMachine_dT[b]);
		cOutput->cFatimaTAMEX_TimeMachine_dT[b] = FatimaTAMEX_TimeMachine_dT[b];
        }
     }
     ///Germanium
     
         if(cInputMain->pGe_T[Germanium_TimeMachine_Det][Germanium_TimeMachineCh1]!=0 && cInputMain->pGe_T[Germanium_TimeMachine_Det][Germanium_TimeMachineCh2]!=0){       
             Germanium_TimeMachine_dT = cInputMain->pGe_T[Germanium_TimeMachine_Det][Germanium_TimeMachineCh2] - cInputMain->pGe_T[Germanium_TimeMachine_Det][Germanium_TimeMachineCh1];
             hGe_TMdT->Fill(Germanium_TimeMachine_dT);
	     cOutput->cGermanium_TimeMachine_dT=Germanium_TimeMachine_dT;
	    
         }
     
      ///bPlastic
      for(int c=0; c<10; c++){

        if(cInputMain->pbPlas_LeadT[bPlastTimeMachineBoard][bPlastTimeMachineCh1][c]!=0 && cInputMain->pbPlas_LeadT[bPlastTimeMachineBoard][bPlastTimeMachineCh2][c]!=0){        
          bPlast_TimeMachine_dT[c] = (cInputMain->pbPlas_LeadT[bPlastTimeMachineBoard][bPlastTimeMachineCh2][c] - cInputMain->pbPlas_LeadT[bPlastTimeMachineBoard][bPlastTimeMachineCh1][c])*5;
	  
	  
          hbPlastic_TMdT->Fill(bPlast_TimeMachine_dT[c]);
	   cOutput->cbPlast_TimeMachine_dT[c] = bPlast_TimeMachine_dT[c];
        }
      }
      
     ///AIDA
    int64_t aida_t_o = 0, aida_t_d = 0;
    for (auto sv : cInputMain->pAidaScalers)
    {
      if (sv.Module + 1 == 3) aida_t_o = sv.Time;
      if (sv.Module + 1 == 4) aida_t_d = sv.Time;
    }
     
     AIDA_TimeMachine_dT=0;
     if (aida_t_o && aida_t_d) AIDA_TimeMachine_dT = aida_t_d - aida_t_o;
     if (AIDA_TimeMachine_dT)
      hAida_TMdT->Fill(AIDA_TimeMachine_dT);
     cOutput->cAIDA_TimeMachine_dT = AIDA_TimeMachine_dT;
    
    
     
     
     ///Now cross correlate
    
     for(int a=0; a<10; a++){
          ///Fatima VME vs Fatima TAMEX
         if(cOutput->cFatimaVME_TimeMachine_dT[a]!=0 && cOutput->cFatimaTAMEX_TimeMachine_dT[a]!=0){
             hFatVME_FatTAMEX_TM->Fill(cOutput->cFatimaVME_TimeMachine_dT[a], cOutput->cFatimaTAMEX_TimeMachine_dT[a]);  
         }
     
     ///Fatima VME vs Germanium
  
        if(cOutput->cFatimaVME_TimeMachine_dT[a]!=0 &&  cOutput->cGermanium_TimeMachine_dT!=0){
            hFatVME_Ge_TM->Fill(cOutput->cFatimaVME_TimeMachine_dT[a], cOutput->cGermanium_TimeMachine_dT);
	  
	
        }
     
     ///Fatima VME bPlast
        if(cOutput->cFatimaVME_TimeMachine_dT[a]!=0 && cOutput->cbPlast_TimeMachine_dT[a]!=0){
            hFatVME_bPlast_TM->Fill(cOutput->cFatimaVME_TimeMachine_dT[a], cOutput->cbPlast_TimeMachine_dT[a]);
        }
     
     ///Fatima VME AIDA
        if(cOutput->cFatimaVME_TimeMachine_dT[a]!=0 && cOutput->cAIDA_TimeMachine_dT!=0){
            hFatVME_AIDA_TM->Fill(cOutput->cFatimaVME_TimeMachine_dT[a], cOutput->cAIDA_TimeMachine_dT);

        }
     
     
     ///FATIMA TAMEX Germanium
     if(cOutput->cFatimaTAMEX_TimeMachine_dT[a]!=0 && cOutput->cGermanium_TimeMachine_dT!=0){
        hFatTAMEX_Ge_TM->Fill(cOutput->cFatimaTAMEX_TimeMachine_dT[a], cOutput->cGermanium_TimeMachine_dT);
      }
      ///Fatima TAMEX bPlast
        if(cOutput->cFatimaTAMEX_TimeMachine_dT[a]!=0&& cOutput->cbPlast_TimeMachine_dT[a]!=0){
       hFatTAMEX_bPlast_TM->Fill(cOutput->cFatimaTAMEX_TimeMachine_dT[a], cOutput->cbPlast_TimeMachine_dT[a]);
      }
      ///Fatima TAMEX AIDA
        if(cOutput->cFatimaTAMEX_TimeMachine_dT[a]!=0 && cOutput->cAIDA_TimeMachine_dT!=0){
        hFatTAMEX_AIDA_TM->Fill(cOutput->cFatimaTAMEX_TimeMachine_dT[a], cOutput->cAIDA_TimeMachine_dT);
      }
      ///Germanium bPlast
        if(cOutput->cFatimaTAMEX_TimeMachine_dT[a]!=0 && cOutput->cAIDA_TimeMachine_dT!=0){
      hGe_bPlast_TM->Fill(cOutput->cGermanium_TimeMachine_dT,cOutput->cbPlast_TimeMachine_dT[a]);
       }
     
     ///Germanium AIDA
        if(cOutput->cGermanium_TimeMachine_dT!=0 && cOutput->cAIDA_TimeMachine_dT!=0){
    hGe_AIDA_TM->Fill(cOutput->cGermanium_TimeMachine_dT, cOutput->cAIDA_TimeMachine_dT);
     }
     ///AIDA bPlast
        if(cOutput->cAIDA_TimeMachine_dT!=0 && cOutput->cbPlast_TimeMachine_dT[a]!=0){
    hAIDA_bPlast_TM->Fill(cOutput->cAIDA_TimeMachine_dT,cOutput->cbPlast_TimeMachine_dT[a]);
        }
     }
}
 
 
 /**----------------------------------------------------------------------------------------------**/
 /**----------------------------------     FRS-AIDA (Implanted ion)   -------------------------**/
 /**----------------------------------------------------------------------------------------------**/
 void EventCorrelProc::Make_FRS_AIDA_Histos(){
      TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
     // hA_FRS_Z1Z2_implants_strip_xy.resize(conf->DSSDs());
      //hA_FRS_Z1Z2_implants_pos_xy.resize(conf->DSSDs());
      //hA_FRS_Z1Z2_implants_e.resize(conf->DSSDs());
     // hA_FRS_Z1Z2_implants_e_xy.resize(conf->DSSDs());
      
      hA_Imp_FRS_dT = MakeTH1('I',"WR/AIDA/Aida_Implant-FRS_WR_dT","White Rabbit Aida Implant-FRS ",16000,-40000,40000);
       
     
     for (int i = 0; i < conf->DSSDs(); ++i)
  {    
        
        
      //  hA_FRS_Z1Z2_implants_e_xy[i] = MakeTH2('F', Form("Correlations/AIDA-FRS/Implants/Z1Z2_Gate/DSSD%d_implants_energy_XY_Z1Z2g", i+1), Form("DSSD %d implant front energy vs back energy FRS Z1 Z2 gated", i+1), 1000, 0, 10000, 1000, 0, 10000, "X Energy", "Y Energy");
    
//         hA_FRS_ZAoQ_implants_strip_xy[i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/ZvsAoQ_Gate/DSSD%d_implants_strip_XY_ZvsAoQ_Gate", i+1), Form("DSSD %d implant hit pattern FRS ZvsAoQ Gate", i+1), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
//            
//         hA_FRS_ZAoQ_implants_e[i] = MakeTH1('F', Form("Correlations/AIDA-FRS/Implants/ZvsAoQ_Gate/DSSD%d_implants_energy_ZvsAoQ_Gate", i+1), Form("DSSD %d implant energy FRS AoQ vs Z Gate", i+1), 1000, 0, 10000, "Implant Energy/MeV");
        
        
        ///Z vs AoQ
        for(int gate=0; gate<MAX_FRS_GATE; gate++){
        hA_FRS_ZAoQ_implants_strip_xy[gate][i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/All/Z1vsAoQ/Z1vsAoQ_Gate%d/DSSD_XY/DSSD%d_implants_strip_XY_Z1vsAoQ_Gate%d", gate,i+1,gate), Form("DSSD %d implant hit pattern FRS Z1vsAoQ Gate%d", i+1,gate), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
        
        hA_FRS_ZAoQ_implants_position[gate][i] = MakeTH2('D', Form("Correlations/AIDA-FRS/Implants/All/Z1vsAoQ/Z1vsAoQ_Gate%d/DSSD_Position/DSSD%d_implant_Position_Z1vsAoQ_Gate%d", gate, i+1,gate), Form("DSSD %d implant position Z vs AoQ Gate %d", i+1,gate), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
        
        hA_FRS_ZAoQ_implants_e[gate][i] = MakeTH1('F', Form("Correlations/AIDA-FRS/Implants/All/Z1vsAoQ/Z1vsAoQ_Gate%d/Energy/DSSD%d_implants_energy_Z1vsAoQ_Gate%d", gate,i+1,gate), Form("DSSD %d implant energy FRS AoQ vs Z Gate%d", i+1,gate), 1000, 0, 10000, "Implant Energy/MeV");
        
        hA_FRS_ZAoQ_implants_strip_xy_stopped[gate][i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1vsAoQ/Z1vsAoQ_Gate%d/DSSD_XY/DSSD%d_implants_stopped_strip_XY_Z1vsAoQ_Gate%d",gate, i+1,gate), Form("DSSD %d stopped implant hit pattern FRS Z1vsAoQ Gate%d", i+1,gate), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
        
        hA_FRS_ZAoQ_implants_position_stopped[gate][i] = MakeTH2('D', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1vsAoQ/Z1vsAoQ_Gate%d/DSSD_Position/DSSD%d_implant_stopped_Position_Z1vsAoQ_Gate%d", gate, i+1,gate), Form("DSSD %d implant stopped position Z vs AoQ Gate%d ", i+1,gate), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
           
        hA_FRS_ZAoQ_implants_e_stopped[gate][i] = MakeTH1('F', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1vsAoQ/Z1vsAoQ_Gate%d/Energy/DSSD%d_implants_stopped_energy_Z1vsAoQ_Gate%d", gate,i+1,gate), Form("DSSD %d stopped implant energy FRS AoQ vs Z Gate%d", i+1,gate), 1000, 0, 10000, "Implant Energy/MeV");
        
        
        
        hA_FRS_Z1Z2_implants_strip_xy[gate][i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/All/Z1vsZ2/Z1vsZ2_Gate%d/DSSD_XY/DSSD%d_implants_strip_XY_Z1Z2g%d", gate,i+1,gate), Form("DSSD %d implant hit pattern, FRS Z1 Z2 Gate %d", i+1,gate), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
        
        hA_FRS_Z1Z2_implants_position[gate][i] = MakeTH2('D', Form("Correlations/AIDA-FRS/Implants/All/Z1vsZ2/Z1vsZ2_Gate%d/DSSD_Position/DSSD%d_implant_Position_Z1vsZ2_Gate%d", gate, i+1,gate), Form("DSSD %d implant position FRS Z1 Z2 gate %d", i+1,gate), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
        
        hA_FRS_Z1Z2_implants_strip_xy_stopped[gate][i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1vsZ2/Z1vsZ2_Gate%d/DSSD_XY/DSSD%d_implants_stopped_strip_XY_Z1Z2g%d", gate,i+1,gate), Form("DSSD %d implant hit pattern, FRS Z1 Z2 Gate %d", i+1,gate), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
        
        hA_FRS_Z1Z2_implants_position_stopped[gate][i] = MakeTH2('D', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1vsZ2/Z1vsZ2_Gate%d/DSSD_Position/DSSD%d_implants_stopped_Position_Z1vsZ2_Gate%d", gate, i+1,gate), Form("DSSD %d implant stopped position Z1 Z2 Gate%d", i+1,gate), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
        
    
        
        ///Z1Z2 X2AoQ
        hA_FRS_Z1Z2_x2AoQ_implants_strip_xy[gate][i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/All/Z1Z2_x2AoQ/Z1Z2_x2AoQ_Gate%d/DSSD_XY/DSSD%d_implants_strip_Z1Z2_x2AoQ_Gate%d",gate, i+1,gate), Form("DSSD %d implant hit pattern FRS Z1Z2_x2AoQ_Gate Gate%d", i+1,gate), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
           
        hA_FRS_Z1Z2_x2AoQ_implants_e[gate][i] = MakeTH1('F', Form("Correlations/AIDA-FRS/Implants/All/Z1Z2_x2AoQ/Z1Z2_x2AoQ_Gate%d/Energy/DSSD%d_implants_energy_Z1Z2_x2AoQ_Gate%d",gate, i+1,gate), Form("DSSD %d implant energy FRS Z1Z2_x2AoQ_Gate%d", i+1,gate), 1000, 0, 10000, "Implant Energy/MeV");
        
        hA_FRS_Z1Z2_x2AoQ_implants_position[gate][i] = MakeTH2('D', Form("Correlations/AIDA-FRS/Implants/All/Z1Z2_x2AoQ/DSSD_Position/Z1Z2_x2AoQ_Gate%d/DSSD_Position/DSSD%d_implants_Position_Z1Z2_x2AoQ_Gate%d", gate, i+1,gate), Form("DSSD %d implant position Z1Z2_x2AoQ Gate%d", i+1,gate), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
        
        hA_FRS_Z1Z2_x2AoQ_implants_position_stopped[gate][i] = MakeTH2('D', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1Z2_x2AoQ/Z1Z2_x2AoQ_Gate%d/DSSD_Position/DSSD%d_implants_stopped_Position_Z1Z2_x2AoQ_Gate%d", gate, i+1,gate), Form("DSSD %d implant stopped position Z1Z2_x2AoQ Gate%d", i+1,gate), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
        
        hA_FRS_Z1Z2_x2AoQ_implants_strip_xy_stopped[gate][i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1Z2_x2AoQ/Z1Z2_x2AoQ_Gate%d/DSSD_XY/DSSD%d_implants_stopped_strip_Z1Z2_x2AoQ_Gate%d",gate, i+1,gate), Form("DSSD %d implant hit pattern FRS Z1Z2_x2AoQ_Gate Gate%d", i+1,gate), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
           
        hA_FRS_Z1Z2_x2AoQ_implants_e_stopped[gate][i] = MakeTH1('F', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1Z2_x2AoQ/Energy/Z1Z2_x2AoQ_Gate%d/Energy/DSSD%d_implants_stopped_energy_Z1Z2_x2AoQ_Gate%d",gate, i+1,gate), Form("DSSD %d stopped implant energy FRS Z1Z2_x2AoQ_Gate%d", i+1,gate), 1000, 0, 10000, "Implant Energy/MeV");
        
        
        
        ///Z1Z2 X4AoQ
        hA_FRS_Z1Z2_x4AoQ_implants_strip_xy[gate][i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/All/Z1Z2_x4AoQ/Z1Z2_x4AoQ_Gate%d/DSSD_XY/DSSD%d_implants_strip_Z1Z2_x4AoQ_Gate%d",gate, i+1,gate), Form("DSSD %d implant hit pattern FRS Z1Z2_x4AoQ_Gate Gate%d", i+1,gate), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
           
        hA_FRS_Z1Z2_x4AoQ_implants_e[gate][i] = MakeTH1('F', Form("Correlations/AIDA-FRS/Implants/All/Z1Z2_x4AoQ/Z1Z2_x4AoQ_Gate%d/Energy/DSSD%d_implants_energy_Z1Z2_x4AoQ_Gate%d",gate, i+1,gate), Form("DSSD %d implant energy FRS Z1Z2_x4AoQ_Gate%d", i+1,gate), 1000, 0, 10000, "Implant Energy/MeV");
        
        hA_FRS_Z1Z2_x4AoQ_implants_position[gate][i] = MakeTH2('D', Form("Correlations/AIDA-FRS/Implants/All/Z1Z2_x4AoQ/Z1Z2_x4AoQ_Gate%d/DSSD_Position/DSSD%d_implants_Position_Z1Z2_x4AoQ_Gate%d", gate, i+1,gate), Form("DSSD %d implant position Z1Z2_x4AoQ Gate%d", i+1,gate), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
        
        hA_FRS_Z1Z2_x4AoQ_implants_position_stopped[gate][i] = MakeTH2('D', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1Z2_x4AoQ/Z1Z2_x4AoQ_Gate%d/DSSD_Position/DSSD%d_implants_stopped_Position_Z1Z2_x4AoQ_Gate%d", gate, i+1,gate), Form("DSSD %d implant stopped position Z1Z2_x4AoQ Gate%d", i+1,gate), 128, -37.8, 37.8, 128, -37.8, 37.8, "X position/mm", "Y position/mm");
        
        hA_FRS_Z1Z2_x4AoQ_implants_strip_xy_stopped[gate][i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1Z2_x4AoQ/Z1Z2_x4AoQ_Gate%d/DSSD_XY/DSSD%d_implants_stopped_strip_Z1Z2_x4AoQ_Gate%d",gate, i+1,gate), Form("DSSD %d implant hit pattern FRS Z1Z2_x4AoQ_Gate Gate%d", i+1,gate), 128, 0, 128, 128, 0, 128, "X strip", "Y strip");
           
        hA_FRS_Z1Z2_x4AoQ_implants_e_stopped[gate][i] = MakeTH1('F', Form("Correlations/AIDA-FRS/Implants/Stopped/Z1Z2_x4AoQ/Z1Z2_x4AoQ_Gate%d/Energy/DSSD%d_implants_stopped_energy_Z1Z2_x4AoQ_Gate%d",gate, i+1,gate), Form("DSSD %d stopped implant energy FRS Z1Z2_x4AoQ_Gate%d", i+1,gate), 1000, 0, 10000, "Implant Energy/MeV");
        
        }
//         
       
       
       
      /* // hA_FRS_ZAoQ_implants_e_xy[i] = MakeTH2('F', Form("Correlations/AIDA-FRS/Implants/Z1Z2_x2AoQ_Gate/DSSD%d_implants_energy_XY_Z1Z2IDx2AoQg", i+1), Form("DSSD %d implant front energy vs back energy FRS Z1 Z2, and X2AoQ or X4AoQ And ZAoQ gated", i+1), 1000, 0, 10000, 1000, 0, 10000, "X Energy", "Y Energy");
        hA_FRS_ZAoQ_implants_time_delta[i] = MakeTH1('F', Form("Correlations/AIDA-FRS/Implants/Z1Z2_x2AoQ_Gate/DSSD%d_implants_time_delta_Z1Z2IDx2AoQg", i+1), Form("DSSD %d implant front vs back time FRS Z1 Z2, and X2AoQ And X4AoQ gated And ZAoQ", i+1), 1000, -10000, 10000, "Time Difference/ns");
        
        hA_FRS_ZAoQ_implants_strip_1d[i] = MakeTH1('I', Form("Correlations/AIDA-FRS/Implants/Z1Z2_x2AoQ_Gate/DSSD%d_implants_strip_1d_Z1Z2IDx2AoQg", i+1), Form("DSSD %d implant 1D hit pattern FRS Z1 Z2, and X2AoQ or X4AoQ gated And ZAoQ", i+1), 256, 0, 256, "Strip number");
        
        hA_FRS_ZAoQ_implants_per_event[i] = MakeTH1('I', Form("Correlations/AIDA-FRS/Implants/Z1Z2_x2AoQ_Gate/DSSD%d_implants_per_event_Z1Z2IDx2AoQg", i+1), Form("DSSD %d implants per event FRS Z1 Z2, and X2AoQ or X4AoQ And ZAoQ gated", i+1), 100, 0, 100, "Number of implants");  
        *///hA_FRS_ZAoQ_implants_strip_xy_dssdg[i] = MakeTH2('I', Form("Correlations/AIDA-FRS/Implants/Z1Z2_x2AoQ_Gate/DSSD%d_implants_strip_XY_Z1Z2IDx2AoQg_DSSDGate", i+1), Form("DSSD %d implant hit pattern FRS Z1 Z2, and X2AoQ or X4AoQ gated, DSSD Ion gate", i+1), 128, 0, 128, 128, 0, 128, "X strip", "Y strip"); 
    }
     ///2D AIDA Ion position Gates DSSD 1-3
  
    Float_t init_ID_AIDA_ION_DSSD1[7][2] =
    
    {{34, 55.45},{37,50.5},{40, 50.5}, {41, 59}, {37,60}, {33,60}, {34, 55}}; 
   
    Float_t init_ID_AIDA_ION_DSSD2[7][2] =
     {{0.0, 0.0},{40.0, 0.0},{80.0, 0.0}, {128.0, 0.0}, {128.0, 126.0}, {0.0, 128.0}, {0.0, 0.0}}; 
    
    Float_t init_ID_AIDA_ION_DSSD3[7][2] =
      {{0.0, 0.0},{40.0, 0.0},{80.0, 0.0}, {128.0, 0.0}, {128.0, 126.0}, {0.0, 128.0}, {0.0, 0.0}};  
      
     
    
      cAIDA_IMPgate_DSSD1 = MakePolyCond("cID_AIDA_IMP_DSSD1","FRS Gated AIDA ion pos DSSD1",7,init_ID_AIDA_ION_DSSD1, "AIDA Implantation DSSD1");
      
      cAIDA_IMPgate_DSSD2 = MakePolyCond("cID_AIDA_IMP_DSSD2","FRS Gated AIDA ion pos DSSD1",7,init_ID_AIDA_ION_DSSD2, "AIDA Implantation DSSD2");
      
      cAIDA_IMPgate_DSSD3 = MakePolyCond("cID_AIDA_IMP_DSSD3","FRS Gated AIDA ion pos DSSD1",7,init_ID_AIDA_ION_DSSD3, "AIDA Implantation DSSD3");
      
     
     
}
/**----------------------------------------------------------------------------------------------**/
 void EventCorrelProc::Process_FRS_AIDA(EventAnlStore* cInputMain, EventCorrelStore* cOutput){
   
     TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
     //Branches from AnlProc     
      for (auto& cInputRef : cInputMain->pAida)
     {
       auto* cInput = &cInputRef;
       ///AIDA Implants
         std::vector<AidaHit> hits = cInput->Implants;     
//        
        for (auto& i : hits)
      {
         AidaHit hit = i;

             if(hit.Time>0 && cInputMain->pFRS_WR>0){
               
                hA_Imp_FRS_dT -> Fill(hit.Time-cInputMain->pFRS_WR); 
        }   
     if(hit.Time-cInputMain->pFRS_WR > fCorrel->GFRS_AIDA_TLow && hit.Time-cInputMain->pFRS_WR < fCorrel->GFRS_AIDA_THigh){    
       
      for(int gate=0; gate<MAX_FRS_GATE;gate++){
        
    ///Gate on FRS Z vs AoQ -> AIDA Implantation
          if(cInputMain->pFRS_ZAoQ_pass[gate]==true ){  
         
          
         hA_FRS_ZAoQ_implants_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
         hA_FRS_ZAoQ_implants_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
         hA_FRS_ZAoQ_implants_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
               }
       
       ///Gate on FRS Z1 Z2  -> AIDA Implantation      
        if(cInputMain->pFRS_Z_Z2_pass[gate]==true ){  
            hA_FRS_Z1Z2_implants_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
            hA_FRS_Z1Z2_implants_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
          
          
       ///Gate on FRS Z1_Z2 AND X2vsAoQ-> AIDA Implantation
    
         if(cInputMain->pFRS_x2AoQ_pass[gate]==true ){
             
         hA_FRS_Z1Z2_x2AoQ_implants_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
         hA_FRS_Z1Z2_x2AoQ_implants_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
         hA_FRS_Z1Z2_x2AoQ_implants_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
      
            }     
      ///Gate on FRS Z1_Z2 AND X4vsAoQ-> AIDA Implantation
    
         if(cInputMain->pFRS_x4AoQ_pass[gate]==true ){
             
         hA_FRS_Z1Z2_x4AoQ_implants_strip_xy[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
         hA_FRS_Z1Z2_x4AoQ_implants_position[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
         hA_FRS_Z1Z2_x4AoQ_implants_e[gate][hit.DSSD - 1]->Fill(hit.Energy);
      
            }     
        }
        ///AIDA STOPPED
        if(hit.Stopped){   
            
            ///Gate on FRS Z vs AoQ -> AIDA Stopped Implantation
        if(cInputMain->pFRS_ZAoQ_pass[gate]==true ){     
          
         hA_FRS_ZAoQ_implants_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
         hA_FRS_ZAoQ_implants_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
         hA_FRS_ZAoQ_implants_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
               }
               
             ///Gate on FRS Z1 vs Z2-> AIDA Stopped Implantation
          if(cInputMain->pFRS_Z_Z2_pass[gate]==true ){ 
          
            hA_FRS_Z1Z2_implants_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
            hA_FRS_Z1Z2_implants_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);

        ///Gate on FRS Z1_Z2 AND  X2vsAoQ-> AIDA Stopped Implantation                 
          if(cInputMain->pFRS_x2AoQ_pass[gate]==true){
            hA_FRS_Z1Z2_x2AoQ_implants_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
            hA_FRS_Z1Z2_x2AoQ_implants_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
            hA_FRS_Z1Z2_x2AoQ_implants_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                            }
                            
      ///Gate on FRS Z1_Z2 AND  X4vsAoQ-> AIDA Stopped Implantation                 
            if(cInputMain->pFRS_x4AoQ_pass[gate]==true){
            hA_FRS_Z1Z2_x4AoQ_implants_strip_xy_stopped[gate][hit.DSSD - 1]->Fill(hit.StripX, hit.StripY);
            hA_FRS_Z1Z2_x4AoQ_implants_e_stopped[gate][hit.DSSD - 1]->Fill(hit.Energy);
            hA_FRS_Z1Z2_x4AoQ_implants_position_stopped[gate][hit.DSSD - 1]->Fill(hit.PosX, hit.PosY);
                                    }///End of X4AoQ
                                }///End of Z1Z2
                            }//End of stopped
                        }/// End of gate loop 
                    }//End of White rabbit gate
                }//End of implant loop
             }  //End of AIDA loop
          }
       
  
  /**----------------------------------------------------------------------------------------------**/
 /**--------------------------------  FRS-Germanium Prompt (Isomers)  -------------**/
 /**----------------------------------------------------------------------------------------------**/
 void EventCorrelProc::Make_FRS_Prompt_Ge_Histos(){
      
//       hA_FRSWR_GeWR =  MakeTH1('I',"Correlations/FRS-Prompt_Ge/FRS-Ge_WR_dT","T Diff FRS WR -Germanium WR ",10000,-10000,10000,"Time[ns]", "Counts");
      
     // hA_FRS_GeE = MakeTH1('D', "Correlations/FRS-Prompt_Ge/Ge_EnergySum_allFRS", "Germanium Energy FRS (all) gated",6000, 0, 6000);
      
      for(int i=0; i<MAX_FRS_GATE; i++){
       hA_FRS_ZAoQ_GeE[i]  = MakeTH1('F', Form("Correlations/FRS-Prompt_Ge/Z1vsAoQ_Ge/SinglesEnergy/Ge_EnergySum_Z1vsAoQ_Gate%d", i), Form("Germanium Energy FRS PID gated %d", i), 6000, 0, 6000, "Energy/keV");
 
       if(fCorrel->GSetup_corr_FRS_Gamma_Gamma==1){
       hA_FRS_ZAoQ_GeE1_GeE2[i]  = MakeTH2('D',Form("Correlations/FRS-Prompt_Ge/Z1vsAoQ_Ge/Gamma-Gamma/GeE1_vs_GeE2_Z1vsAoQ_Gate%d",i),Form("Gamma-Gamma PID Gated: %d",i), fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax,  fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax, "Ge Energy1 (keV)", "Ge Energy2 (keV)");
       }
       hA_FRS_ZAoQ_GeEvsT[i]  = MakeTH2('D',Form("Correlations/FRS-Prompt_Ge/Z1vsAoQ_Ge/GeE_vs_FRSGe_dT/GeE_vs_FRSGe_dT_Z1vsAoQ_Gate%d",i),Form("T Diff FRS WR - Germanium T vs Germanium Energy Gate %d",i), 2100,-1000,20000,fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax,"FRS - Ge time (ns)", "Ge Energy (keV)");
     
       //Z1Z2 X2AoQ
       hA_FRS_Z1Z2_X2AoQ_GeE[i]  = MakeTH1('F', Form("Correlations/FRS-Prompt_Ge/Z1Z2_X2AoQ_Ge/SinglesEnergy/Ge_Energy_Z1Z2_X2AoQGate%d", i), Form("Germanium Energy FRS Z1Z2_X2AoQ Gate %d", i), 2000, 0, 2000, "Energy/keV");
       
       hA_FRS_Z1Z2_X2AoQ_GeEvsT[i]  = MakeTH2('D',Form("Correlations/FRS-Prompt_Ge/Z1Z2_X2AoQ_Ge/GeE_vs_dT/GeE_vs_FRSGe_dT_Z1Z2_X2AoQGate%d",i),Form("T Diff FRS - Ge vs Ge Energy Z1Z2X4X2AoQ Gate %d",i), 2100,-1000,20000,2000, 0, 2000,"FRS - Ge time (ns)", "Ge Energy (keV)");
       
       if(fCorrel->GSetup_corr_FRS_Gamma_Gamma==1){
       hA_FRS_Z1Z2_X2AoQ_GeE1_GeE2[i]  = MakeTH2('D',Form("Correlations/FRS-Prompt_Ge/Z1Z2_X2AoQ_Ge/Gamma-Gamma/GeE1_vs_GeE2_Z1Z2_X2AoQ_Gate%d",i),Form("Gamma-Gamma Z1Z2_X2AoQ_Ge Gated: %d",i), fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax,  fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax, "Ge Energy1 (keV)", "Ge Energy2 (keV)");
       }
       
        //Z1Z2 X2AoQ
       hA_FRS_Z1Z2_X4AoQ_GeE[i]  = MakeTH1('F', Form("Correlations/FRS-Prompt_Ge/Z1Z2_X4AoQ_Ge/SinglesEnergy/Ge_Energy_Z1Z2_X4AoQGate%d", i), Form("Germanium Energy FRS Z1Z2_X4AoQ Gate %d", i), 2000, 0, 2000, "Energy/keV");
       
       hA_FRS_Z1Z2_X4AoQ_GeEvsT[i]  = MakeTH2('D',Form("Correlations/FRS-Prompt_Ge/Z1Z2_X4AoQ_Ge/GeE_vs_dT/GeE_vs_FRSGe_dT_Z1Z2_X4AoQGate%d",i),Form("T Diff FRS - Ge vs Ge Energy Z1Z2X4X4AoQ Gate %d",i),  2100,-1000,20000,2000, 0, 2000,"SCI41 - Ge time (ns)", "Ge Energy (keV)");
       
       if(fCorrel->GSetup_corr_FRS_Gamma_Gamma==1){
       hA_FRS_Z1Z2_X4AoQ_GeE1_GeE2[i]  = MakeTH2('D',Form("Correlations/FRS-Prompt_Ge/Z1Z2_X4AoQ_Ge/Gamma-Gamma/GeE1_vs_GeE2_Z1Z2_X4AoQ_Gate%d",i),Form("Gamma-Gamma Z1Z2_X4AoQ_Ge Gated: %d",i), fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax,  fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax, "Ge Energy1 (keV)", "Ge Energy2 (keV)");
       }
       
      }
//       hA_FRS_GeEvsT  = MakeTH2('D',"Correlations/FRS-Prompt_Ge/FRS_T-GALWR_T_vs_GeE","T Diff FRS - Ge vs Ge Energy", 1250, 0, 5000, 1000,-10000,10000,"Ge Energy (keV)", "FRS WR - Ge WR time (ns)");
      
      Float_t init_Ge_EdT_cut[MAX_FRS_GATE][MAX_FRS_PolyPoints][2]; 
      //Float_t init_ID_Z_AoQ_corrstep_Ge[8][8][2];
      for(int m=0; m<MAX_FRS_GATE; m++){
          for(int n=0; n<MAX_FRS_PolyPoints; n++){
           init_Ge_EdT_cut[m][n][0]=X_Ge_EdT_cut[m][n];
           init_Ge_EdT_cut[m][n][1]=Y_Ge_EdT_cut[m][n];
      /*
           init_ID_Z_AoQ_corrstep_Ge[m][n][0] =C_X_ZAoQ[m][n];
           init_ID_Z_AoQ_corrstep_Ge[m][n][1] =C_Y_ZAoQ[m][n];*/
      }
 }
//       {{73.3971, 350.091},{185.883, -105.534},{1985.66, -120.795}, {1988.47,-168.755}, {512.092, -165.512}, {19.9662, -170.935}, {25.5905, 286.871},{73.3971, 350.091}};  
      char name[50];
      for(int i=0; i<MAX_FRS_GATE; i++){
      
//         sprintf(name,"cID_Z_AoQ_corrstep_Ge%d",i);
//         cID_Z_AoQ_corrstep_Ge[i] = MakePolyCond("FRS_ID_Gated_CorrStep_Ge", name, 8, init_ID_Z_AoQ_corrstep_Ge[i], "ZvsAoQ_Ge");
      
        sprintf(name,"cGe_EdT_cut%d",i);
        cGe_EdT_cut[i] = MakePolyCond("cGe_EdT_cut", name,MAX_FRS_PolyPoints, init_Ge_EdT_cut[i], "Ge Prompt flash cut");
      }
    }
  /**----------------------------------------------------------------------------------------------**/
           
 void EventCorrelProc::Process_FRS_Prompt_Ge(EventAnlStore* cInputMain, EventCorrelStore* cOutput){
 
     int    GeHitsPrm=0;
     double GeE_Prm[Germanium_MAX_HITS];
     double GeT_Prm[Germanium_MAX_HITS];
     for(int x=0; x< Germanium_MAX_HITS; x++){
         GeE_Prm[x]=0;
         GeT_Prm[x]=0;
     }
      dT_frsge_prompt=0;
      Ge_mult_prompt=0;
      dT_frsge_mult_prompt=0;
      dT_GeT_prompt=0;
      Ge_FirstT_prompt=0;

     
    if(cInputMain->pFRS_WR>0 && cInputMain->pGe_WR>0)  dT_frsge_prompt = (cInputMain->pGe_WR - cInputMain->pFRS_WR);
   // if(dT_frsge_prompt!=0) hA_FRSWR_GeWR->Fill(dT_frsge_prompt);
     
    
  
    
    if(GAL_WR!=0){
     for(int g=0; g<Germanium_MAX_DETS; g++){
            for(int h=0; h<Germanium_CRYSTALS; h++){
                if(g!=Germanium_SC41_Det||g!=Germanium_SC41_Det_Digi||g!=Germanium_TimeMachine_Det){
                 
                    if (cInputMain->pGe_EAddback[g][h]>0) {
        GeE_Prm[Ge_mult_prompt] = cInputMain->pGe_EAddback[g][h];
        GeT_Prm[Ge_mult_prompt] = cInputMain->pGe_T[g][h];
                    
             Ge_mult_prompt++;
             
                    }
///WR Time gate FRS-Ge GLOBAL dT GATE
    if(dT_frsge_prompt>fCorrel->GFRS_Ge_TLow && dT_frsge_prompt < fCorrel->GFRS_Ge_THigh &&cInputMain->pGe_EAddback[g][h]>1){}
      
    for(int gate=0;gate<MAX_FRS_GATE;gate++){
     
        ///Cut the prompt flash with 2D poly
        if(cGe_EdT_cut[gate]->Test((cInputMain->pGe_T[g][h] - cInputMain->pGe_T[Germanium_SC41_Det][Germanium_SC41L_Crystal]),cInputMain->pGe_EAddback[g][h])==true) {
           
                ///Energy vs WR dT all 
//                 hA_FRS_GeEvsT->Fill(cInputMain->pGe_EAddback[g][h],dT_frsge_prompt);

         ///SC41 - Gamma dT gate (individual PID Gates)
//             if((cInputMain->pGe_T[g][h] - cInputMain->pGe_T[Germanium_SC41_Det][Germanium_SC41L_Crystal])>fCorrel->GGe_SCI41_Low && (cInputMain->pGe_T[g][h] - cInputMain->pGe_T[Germanium_SC41_Det][Germanium_SC41L_Crystal])<fCorrel->GGe_SCI41_High){   
  
       ///Get the 'first' gamma
            if(Ge_mult_prompt==1){
                     Ge_FirstT_prompt=cInputMain->pGe_T[g][h];
                     
       
          //  hA_FRS_GeE->Fill(cInputMain->pGe_EAddback[g][h]);           
            ///Now FRS gated           
        // cout<<"cInputMain->pGe_EAddback[g][h]" <<cInputMain->pGe_EAddback[g][h] << endl;
               ///Z vs A/Q gated 
              if(cInputMain->pFRS_ZAoQ_pass[gate]==true){
              //  if(cID_Z_AoQ_corrstep_Ge[gate]->Test(cInputMain->pFRS_AoQ, cInputMain->pFRS_z)==true){
                  //  cout<<"PASS" << endl;
                 hA_FRS_ZAoQ_GeE[gate]->Fill(cInputMain->pGe_EAddback[g][h]);
                 hA_FRS_ZAoQ_GeEvsT[gate]->Fill((cInputMain->pGe_T[g][h] - cInputMain->pGe_T[Germanium_SC41_Det][Germanium_SC41L_Crystal]),cInputMain->pGe_EAddback[g][h]);
//                  cout<<"cInputMain->pGe_EAddback[g][h]" <<cInputMain->pGe_EAddback[g][h] << endl;
                 
                                    }
                                    
              if(cInputMain->pFRS_Z_Z2_pass[fCorrel->GZ1Z2_Gate]==true){              
               ///Z1Z2 X2 AoQ gated                          
                if(cInputMain->pFRS_x2AoQ_pass[gate]==true ){
                    hA_FRS_Z1Z2_X2AoQ_GeE[gate]->Fill(cInputMain->pGe_EAddback[g][h]);
                    hA_FRS_Z1Z2_X2AoQ_GeEvsT[gate]->Fill((cInputMain->pGe_T[g][h] - cInputMain->pGe_T[Germanium_SC41_Det][Germanium_SC41L_Crystal]),cInputMain->pGe_EAddback[g][h]);  
                            }
                        
                ///Z1Z2 X4 AoQ gated      
                if(cInputMain->pFRS_x4AoQ_pass[gate]==true){ 
                    hA_FRS_Z1Z2_X4AoQ_GeE[gate]->Fill(cInputMain->pGe_EAddback[g][h]);
                    hA_FRS_Z1Z2_X4AoQ_GeEvsT[gate]->Fill((cInputMain->pGe_T[g][h] - cInputMain->pGe_T[Germanium_SC41_Det][Germanium_SC41L_Crystal]),cInputMain->pGe_EAddback[g][h]);  
                                    }
                                }
                            }///End of Multiplicity 1 gammas             
      
        ///Correct the times for more than one gamma in an event        
            if(Ge_mult_prompt>1 && cInputMain->pGe_T[g][h]>0 ){              
                  dT_GeT_prompt = (cInputMain->pGe_T[g][h]-Ge_FirstT_prompt);
                  
                  dT_frsge_mult_prompt=(cInputMain->pGe_T[g][h] - cInputMain->pGe_T[Germanium_SC41_Det][Germanium_SC41L_Crystal]) + ABS(dT_GeT_prompt);
               
              if(cInputMain->pGe_EAddback[g][h]>1){
                  ///Z vs A/Q gated 
                  if(cInputMain->pFRS_ZAoQ_pass[gate]==true ){
                      
                 
                        
                       hA_FRS_ZAoQ_GeE[gate]->Fill(cInputMain->pGe_EAddback[g][h]);
                       hA_FRS_ZAoQ_GeEvsT[gate]->Fill(dT_frsge_mult_prompt,cInputMain->pGe_EAddback[g][h]);
                  }
                
                            
        ///Z1Z2 X2 AoQ gated
     if(cInputMain->pFRS_Z_Z2_pass[fCorrel->GZ1Z2_Gate]==true){
        if( cInputMain->pFRS_x2AoQ_pass[gate]==true ){

         hA_FRS_Z1Z2_X2AoQ_GeE[gate]->Fill(cInputMain->pGe_EAddback[g][h]);
            hA_FRS_Z1Z2_X2AoQ_GeEvsT[gate]->Fill(dT_frsge_mult_prompt,cInputMain->pGe_EAddback[g][h]);
                        }
       
            if(cInputMain->pFRS_x4AoQ_pass[gate]==true){ 
               hA_FRS_Z1Z2_X4AoQ_GeE[gate]->Fill(cInputMain->pGe_EAddback[g][h]);
            hA_FRS_Z1Z2_X4AoQ_GeEvsT[gate]->Fill(dT_frsge_mult_prompt,cInputMain->pGe_EAddback[g][h]); 
                                            }
                                        }///End of Z1 Z2 Gate
                                    } ///End of GeE>1                               
                                }///End of multiplicity>1 gammas
                           // }///End of prompt flash cut
                        }///End of gate loop
                    //}
                }///End of WR gate
            }///End of Detector number '8' i.e. Extra signals condition
        }// Crystals
     }///Detector
}///Ge WR
                ///Gamma-Gamma Z vs A/Q
                for(int gate=0; gate< MAX_FRS_GATE; gate ++){
              
                for(int m=0; m<Ge_mult_prompt; m++){
                for(int n=0; n<Ge_mult_prompt; n++){
                    if(m==n) continue;
                  if((GeT_Prm[m]-GeT_Prm[n])>fCorrel->GGe1_Ge2_Low && (GeT_Prm[m]-GeT_Prm[n])<fCorrel->GGe1_Ge2_High){
                
    if(cGe_EdT_cut[gate]->Test(GeT_Prm[m] - cInputMain->pGe_T[Germanium_SC41_Det][Germanium_SC41L_Crystal],GeE_Prm[m])==true && cGe_EdT_cut[gate]->Test(GeT_Prm[n] - cInputMain->pGe_T[Germanium_SC41_Det][Germanium_SC41L_Crystal],GeE_Prm[n])==true) {
                    
                if(cInputMain->pFRS_ZAoQ_pass[gate]==true && fCorrel->GSetup_corr_FRS_Gamma_Gamma==1)    hA_FRS_ZAoQ_GeE1_GeE2[gate]->Fill(GeE_Prm[m],GeE_Prm[n]);
                     
                                    
                if(cInputMain->pFRS_Z_Z2_pass[fCorrel->GZ1Z2_Gate]==true ){
                    
                        if(cInputMain->pFRS_x2AoQ_pass[gate]==true){
                        hA_FRS_Z1Z2_X2AoQ_GeE1_GeE2[gate]->Fill(GeE_Prm[m],GeE_Prm[n]);
                            
                        }
                  
                    if(cInputMain->pFRS_x4AoQ_pass[gate]==true){ 
                    hA_FRS_Z1Z2_X4AoQ_GeE1_GeE2[gate]->Fill(GeE_Prm[m],GeE_Prm[n]);
                                            
                                        }
                                    }///Z1 Z2             
                                }///prompt cut
                            }///Gamma-Gamma Time gate
                        }///Ge2
                    }///Ge 1                
                }///gate loop    
        }
     
 
 /**----------------------------------------------------------------------------------------------**/
 /**--------------------------------  FRS-Germanium Long Isomers -------------**/
 /**----------------------------------------------------------------------------------------------**/
 void EventCorrelProc::Make_FRS_LongIso_Ge_Histos(){
    
      hA_FRS_ZAoQ_GeE_LongIso  = MakeTH1('F', "Correlations/FRS_LongCorrelation_Ge/Z1vsAoQ_Gated/Ge_SinglesEnergy_LongCorrelationTime", "Long T search GeE", 2000, 0, 2000, "Energy/keV");
           
      hA_FRS_GeEvsT_LongIsoGated  = MakeTH2('D',"Correlations/FRS_LongCorrelation_Ge/Z1vsAoQ_Gated/dT_vs_GeE_LongCorrelationTime","Long T search dT vs GeE", fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax,fCorrel->GFRS_Ge_LongIso_HBin,fCorrel->GFRS_Ge_LongIso_HLow,fCorrel->GFRS_Ge_LongIso_HHigh,"Ge Energy (keV)", "dT(mus)");
      
      hA_FRS_GeE1vsGeE2_LongIsoGated  = MakeTH2('D',"Correlations/FRS_LongCorrelation_Ge/Z1vsAoQ_Gated/GeE1_vs_GeE2_LongCorrelationTime","Gamma-Gamma Long isomer gated", fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax,fCorrel->GGe1_Ge2_HistoBin,fCorrel->GGe1_Ge2_HistoMin,fCorrel->GGe1_Ge2_HistoMax,"Ge Energy1 (keV)", "Ge Energy2 (keV)");
    }
  /**----------------------------------------------------------------------------------------------**/                  
 void EventCorrelProc::Process_FRS_LongIso_Ge(EventAnlStore* cInputMain, EventCorrelStore* cOutput){
      
      //for(int i=0; i<8; i++)dT_frsge[i]=0;
     ///reset everything
    
  
       for(int x=0; x< Germanium_MAX_HITS; x++){
           GeE_Long[x]=0;
           GeT_Long[x]=0;
           GeE_Prm_Long[x]=0;
           GeT_Prm_Long[x]=0;
       }
        dT_frsge_long=0;
        dT_frsge_prompt=0;
        Ge_mult_long=0;
        Ge_mult_prompt=0;
        dT_frsge_mult_long=0;
        dT_frsge_mult_prompt=0;
        dT_GeT_long=0;
        dT_GeT_prompt=0;
        Ge_FirstT_long=0;
        Ge_FirstT_prompt=0;
      
        if(cInputMain-> pGe_WR> 0){
                    
                    if(cInputMain->pFRS_ZAoQ_pass[fCorrel->GLongIso_PID_Gate]==true && cInputMain-> pFRS_WR!=0){
                        ts= cInputMain-> pFRS_WR;
                    }
                  
                  else if (cInputMain-> pGe_WR>0){
            
                        ts=cInputMain-> pGe_WR;
                    }
    }
          ///------ reset the local variables in case the time is too long ------//
         if(tag_all.size()>0)
             {
                 for(int i=0; i<tag_all.size();i++)
                     {
                 ///The reset time windows are set in Configuration_Files/DESPEC_General_Setup/Correlations_config.dat                 
                   if((ts-ts_all.at(i))>fCorrel->GFRS_Ge_LongIso_THigh )

                             {
                                 tag_all.erase(tag_all.begin()+i);
                                 ts_all.erase(ts_all.begin()+i);
                          
                             }
                     }
             }///End of removing/clearing arrays for long correlations
             

             if(cInputMain->pFRS_WR>0  && cInputMain->pFRS_ZAoQ_pass[fCorrel->GLongIso_PID_Gate]==true){
                    if(tag_all.size()==0)
                        { 
                         tag_all.push_back(1);
                         ts_all.push_back(ts);
                        }
             
        } ///end of FRS long correlations set initial values

       else if (cInputMain->pGe_WR>0 ){
  
            for(int i=(tag_all.size()-1); i>=0; i--)
                             {
            /// ---------- frs-gamma long correlations -------  //
                 if(tag_all.at(i)==1 &&  (ts-ts_all.at(i))>fCorrel->GFRS_Ge_LongIso_TLow) {
                     
                                   dT_frsge_long=ts-ts_all.at(i);
                                   
                    for(int g=0; g<Germanium_MAX_DETS; g++){
                            for (int h=0; h<Germanium_CRYSTALS; h++){

                          if(cInputMain->pGe_EAddback[g][h]>0 &&  (g!=Germanium_SC41_Det||g!=Germanium_SC41_Det_Digi||g!=Germanium_TimeMachine_Det)) {
                             GeE_Long[Ge_mult_long] = cInputMain->pGe_EAddback[g][h];
                             GeT_Long[Ge_mult_long] = cInputMain->pGe_T[g][h];
                            
                             Ge_mult_long++;
                          }
                                 
                          if(cInputMain->pGe_EAddback[g][h]>10 && dT_frsge_long>0 &&( g!=Germanium_SC41_Det||g!=Germanium_SC41_Det_Digi||g!=Germanium_TimeMachine_Det )){

                             if(Ge_mult_long==1 && cInputMain->pGe_EAddback[g][h]>0){
           ///Note that Ge_FirstT_Long is not always necessarily the 'first' gamma (i.e. lowest time) since it loops over all detectors starting from 0
                                    Ge_FirstT_long=cInputMain->pGe_T[g][h];
                            
                                    hA_FRS_ZAoQ_GeE_LongIso->Fill(cInputMain->pGe_EAddback[g][h]);
                                    
                    hA_FRS_GeEvsT_LongIsoGated->Fill(cInputMain->pGe_EAddback[g][h],dT_frsge_long/fCorrel->GFRS_Ge_LongIso_TScale);
                            }
                        
                ///This is for when there is more than 1 gamma in an event to get the correct time                    
                    if(Ge_mult_long>1 && cInputMain->pGe_T[g][h]>0 ){
                            dT_GeT_long =(cInputMain->pGe_T[g][h]-Ge_FirstT_long);
                            dT_frsge_mult_long=dT_frsge_long + ABS(dT_GeT_long);
                                 
                         if(cInputMain->pGe_EAddback[g][h]>10 && dT_frsge_mult_long>0){
                             
                            hA_FRS_GeEvsT_LongIsoGated->Fill(cInputMain->pGe_EAddback[g][h],dT_frsge_mult_long/fCorrel->GFRS_Ge_LongIso_TScale);
                            hA_FRS_ZAoQ_GeE_LongIso->Fill(cInputMain->pGe_EAddback[g][h]);
                                 }
                              }                                           
                          }         
                     }
                }  
                ///Gamma Gamma Test phase Long isomer AKM170920
                for(int m=0; m<Ge_mult_long; m++){
                for(int n=0; n<Ge_mult_long; n++){
                if(m==n) continue;
                  if((GeT_Long[m]-GeT_Long[n])>fCorrel->GGe1_Ge2_Low && (GeT_Long[m]-GeT_Long[n])<fCorrel->GGe1_Ge2_High){

                 hA_FRS_GeE1vsGeE2_LongIsoGated->Fill(GeE_Long[m],GeE_Long[n]);
                                
                        }
                    }
                } 
            }
        }
       }
        
        ///Now add the prompt gammas to the histograms. This can be selected on and off in correlations.dat
        if (fCorrel->GSetup_corr_FRS_Ge_LongIso_incprmt==true){
           dT_frsge_prompt = 0;
        // bool Ge_dT_cut=false;
            if(cInputMain->pFRS_WR>0 && cInputMain->pGe_WR>0)  dT_frsge_prompt = (cInputMain->pGe_WR - cInputMain->pFRS_WR);

            if(GAL_WR!=0 && cInputMain->pFRS_ZAoQ_pass[fCorrel->GLongIso_PID_Gate]==true){
    
                for(int g=0; g<Germanium_MAX_DETS; g++){
                    for(int h=0; h<Germanium_CRYSTALS; h++){
                        if((g!=Germanium_SC41_Det||g!=Germanium_SC41_Det_Digi||g!=Germanium_TimeMachine_Det) && cInputMain->pGe_EAddback[g][h]>0){
                             GeE_Prm_Long[Ge_mult_prompt] = cInputMain->pGe_EAddback[g][h];
                             GeT_Prm_Long[Ge_mult_prompt] = cInputMain->pGe_T[g][h];
                            Ge_mult_prompt++;
                   
                    ///Cut the prompt flash with 2D poly
                        if(cGe_EdT_cut[fCorrel->GLongIso_PID_Gate]->Test(dT_frsge_prompt,cInputMain->pGe_EAddback[g][h])==true) {
                    ///Get the 'first' gamma
                 if(Ge_mult_prompt==1){
                     Ge_FirstT_prompt=cInputMain->pGe_T[g][h];
               
                     ///Energy vs  dT
                    hA_FRS_ZAoQ_GeE_LongIso->Fill(cInputMain->pGe_EAddback[g][h]);
                    hA_FRS_GeEvsT_LongIsoGated->Fill(dT_frsge_prompt/fCorrel->GFRS_Ge_LongIso_TScale,cInputMain->pGe_EAddback[g][h]);
                 }
                            
              ///Correct the times for more than one gamma in an event
                 if(Ge_mult_prompt>1 && cInputMain->pGe_T[g][h]>0 ){    
               
                  dT_GeT_prompt = (cInputMain->pGe_T[g][h]-Ge_FirstT_prompt);
                  dT_frsge_mult_prompt=(cInputMain->pGe_WR-cInputMain->pFRS_WR) + ABS(dT_GeT_prompt);
         
                  hA_FRS_ZAoQ_GeE_LongIso->Fill(cInputMain->pGe_EAddback[g][h]);
                
                    if(dT_frsge_mult_prompt!=0){ 
    
                        hA_FRS_GeEvsT_LongIsoGated->Fill(dT_frsge_mult_prompt/fCorrel->GFRS_Ge_LongIso_TScale,cInputMain->pGe_EAddback[g][h]);   
                                    }
                                }
                            }
                        }
                    }
                }
               
               //Gamma gamma for the long isomers, prompt part (needs testing)
                for(int m=0; m<Ge_mult_prompt; m++){
                for(int n=0; n<Ge_mult_prompt; n++){
                    if(GeE_Prm_Long[m]>0 && GeE_Prm_Long[n]>0){
                    if(m==n) continue;
                  if((GeT_Prm_Long[m]-GeT_Prm_Long[n])>fCorrel->GGe1_Ge2_Low && (GeT_Prm_Long[m]-GeT_Prm_Long[n])<fCorrel->GGe1_Ge2_High){
                
                      if(cGe_EdT_cut[fCorrel->GLongIso_PID_Gate]->Test(dT_frsge_prompt,GeE_Prm_Long[m])==true && cGe_EdT_cut[fCorrel->GLongIso_PID_Gate]->Test(dT_frsge_prompt,GeE_Prm_Long[n])==true) {
                    
                if(cInputMain->pFRS_ZAoQ_pass[fCorrel->GLongIso_PID_Gate]==true)    hA_FRS_GeE1vsGeE2_LongIsoGated->Fill(GeE_Prm_Long[m],GeE_Prm_Long[n]);
                                    }
                                }
                            }
                        }
                    }  
            }
      }
}
 
 

/**----------------------------------------------------------------------------------------------**/
 /**--------------------------------  FRS-FATIMA Prompt (Isomers)  -------------------------------**/
 /**----------------------------------------------------------------------------------------------**/
 void EventCorrelProc::Make_FRS_Prompt_Fat_Histos(){
     
      //hA_FRSWR_FatWR =  MakeTH1('I',"Correlations/FRS-Prompt_Fatima/FRS-FATWR_dT","T Diff FRS WR -Fatima QR ",10000,-10000,10000,"Time[ns]", "Counts");

      //hA_FRS_FatE = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Fat_EnergySum_allFRS", "Fatima Energy FRS (all) gated",2000,0,4000);
      
//       hA_FRS_Fat_LT1_start_stop = MakeTH2('D', "Correlations/FRS-Prompt_Fatima/96Pd_Lifetime/FatdT_339keV", "",1000,-50,50,1600,0,1600, "dT(ns)","Energy (keV)");
//    
//       hA_FRS_Fat_LT2_start_stop = MakeTH2('D', "Correlations/FRS-Prompt_Fatima/96Pd_Lifetime/FatdT_680keV", "",1000,-50,50,1600,0,1600, "dT(ns)","Energy (keV)");
//       
//       hA_FRS_Fat_LT3_start_stop = MakeTH2('D', "Correlations/FRS-Prompt_Fatima/96Pd_Lifetime/FatdT_1415keV", "",1000,-50,50,1600,0,1600, "dT(ns)","Energy (keV)");
      
      hA_FRS_Fat_LT1_start_stop = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Start-Stop/FRS_Fat_LT1_start_stop", "FRS-Fatima Lifetime Start-Stop Lifetime 1",20000,-10000,10000, "dT(ps)","Counts");
      
      hA_FRS_Fat_LT1_start_stop_ns = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Start-Stop/FRS_Fat_LT1_start_stop_ns", "FRS-Fatima Lifetime Start-Stop Lifetime 1 ns ",1000,-50,50, "dT(ns)","Counts/100ps");
      
      hA_FRS_Fat_LT2_start_stop = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Start-Stop/FRS_Fat_LT2_start_stop", "FRS-Fatima Lifetime Start-Stop Lifetime 2",20000,-10000,10000, "dT(ps)","Counts");
      
      hA_FRS_Fat_LT2_start_stop_ns = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Start-Stop/FRS_Fat_LT2_start_stop_ns", "FRS-Fatima Lifetime Start-Stop Lifetime 2 ns",1000,-50,50, "dT(ns)","Counts/100ps");
      
      hA_FRS_Fat_LT3_start_stop = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Start-Stop/FRS_Fat_LT3_start_stop", "FRS-Fatima Lifetime Start-Stop Lifetime 3",20000,-10000,10000, "dT(ps)","Counts");
      
      hA_FRS_Fat_LT3_start_stop_ns = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Start-Stop/FRS_Fat_LT3_start_stop_ns", "FRS-Fatima Lifetime Start-Stop Lifetime 3 ns",1000,-50,50, "dT(ns)","Counts/100ps");
      
      
      hA_FRS_Fat_LT1_stop_start = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Stop-Start/FRS_Fat_LT1_stop_start", "FRS-Fatima Lifetime Stop-Start Lifetime 1",20000,-10000,10000, "dT(ps)","Counts");
      
      hA_FRS_Fat_LT1_stop_start_ns = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Stop-Start/FRS_Fat_LT1_stop_start_ns", "FRS-Fatima Lifetime Stop-Start Lifetime 1 ns",1000,-50,50, "dT(ns)","Counts/100ps");
      
      hA_FRS_Fat_LT2_stop_start = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Stop-Start/FRS_Fat_LT2_stop_start", "FRS-Fatima Lifetime Stop-Start Lifetime 2",20000,-10000,10000, "dT(ps)","Counts");
      
      hA_FRS_Fat_LT2_stop_start_ns = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Stop-Start/FRS_Fat_LT2_stop_start_ns", "FRS-Fatima Lifetime Stop-Start Lifetime 2 ns",1000,-50,50, "dT(ns)","Counts/100ps");
      
      hA_FRS_Fat_LT3_stop_start = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Stop-Start/FRS_Fat_LT3_stop_start", "FRS-Fatima Lifetime Stop-Start Lifetime 3",20000,-10000,10000, "dT(ps)","Counts");
      
      hA_FRS_Fat_LT3_stop_start_ns = MakeTH1('D', "Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Lifetime/Stop-Start/FRS_Fat_LT3_stop_start_ns", "FRS-Fatima Lifetime Stop-Start Lifetime 3 ns",1000,-50,50, "dT(ns)","Counts/100ps");
      
   
      
      for(int i=0; i<MAX_FRS_GATE; i++){
          ///ZAoQ
      hA_FRS_ZAoQ_FatE[i]  = MakeTH1('F', Form("Correlations/FRS-Prompt_Fatima/Z1vsAoQ/SinglesEnergy/Fat_EnergySum_Z1vsAoQ_Gate%d", i), Form("Fatima Energy FRS PID gated %d", i), 2000, 0, 2000, "Energy/keV");
      
      hA_FRS_ZAoQ_FatEvsT[i] = MakeTH2('D',Form("Correlations/FRS-Prompt_Fatima/Z1vsAoQ/FatE_vs_FRSFat_dT/Fat_EdT_ZAoQGate%2d",i), Form("T Diff Fatima T - SCI41 vs Fatima Energy: Z vs AoQ Gate%2d",i),2100,-1000,20000,1000, 0, 2000," Fat T- SCI41 (ns)", "Fatima Energy (keV)"); 
      
      hA_FRS_ZAoQ_FatE1vsE2[i] = MakeTH2('D',Form("Correlations/FRS-Prompt_Fatima/Z1vsAoQ/Gamma-Gamma/FatE1_vs_FatE2_Z1vsAoQ_gate%2d",i), Form("Fatima Energy 1 vs Energy 2 Z vs A/Q Gate:%2d",i),2000, 0, 2000, 2000,0,2000); 
      
       ///Z1Z2 X2AoQ
      hA_FRS_Z1Z2_X2AoQ_FatE[i]  = MakeTH1('F', Form("Correlations/FRS-Prompt_Fatima/Z1Z2_X2AoQ/SinglesEnergy/Fat_EnergySum_Z1Z2_X2AoQGate%d", i), Form("Fatima Energy Z1Z2 AND X2AoQ Gate%d", i), 2000, 0, 2000, "Energy/keV");
      
      
      hA_FRS_Z1Z2_X2AoQ_FatEvsT[i] = MakeTH2('D',Form("Correlations/FRS-Prompt_Fatima/Z1Z2_X2AoQ/FatE_vs_FRSFat_dT/Fat_EdT_Z1Z2_X2AoQGate%2d",i), Form("T Diff Fatima T - SCI41 vs Fatima Energy: Z1 vs Z2 AND X2 vs AoQ Gate%2d",i),2750,-500,5000,2000, 0, 2000," Fat T- SCI41 (ns)", "Fatima Energy (keV)");
      
      hA_FRS_Z1Z2_X2AoQ_FatE1vsE2[i] = MakeTH2('D',Form("Correlations/FRS-Prompt_Fatima/Z1Z2_X2AoQ/Gamma-Gamma/FatE1_vs_FatE2_Z1Z2_X2AoQgate%2d",i), Form("Fatima Energy 1 vs Energy 2 Z1 vs Z2 AND X2 vs AoQ Gate:%2d",i),2000, 0, 2000, 2000,0,2000); 
      
       ///Z1Z2 X4AoQ
      hA_FRS_Z1Z2_X4AoQ_FatE[i]  = MakeTH1('F', Form("Correlations/FRS-Prompt_Fatima/Z1Z2_X4AoQ/SinglesEnergy/Fat_EnergySum_Z1Z2_X4AoQGate%d", i), Form("Fatima Energy FRS Z1 vs Z2 AND X4 vs AoQ gate%d", i), 2000, 0, 2000, "Energy/keV");
      
      hA_FRS_Z1Z2_X4AoQ_FatEvsT[i]  = MakeTH2('F', Form("Correlations/FRS-Prompt_Fatima/Z1Z2_X4AoQ/FatE_vs_FRSFat_dT/Fat_EdT_Z1Z2_X4AoQGate%d", i), Form("T Diff SC41 - Fatima T vs Fatima Energy Z1 vs Z2 AND X2 vs AoQ gate%d", i),2750,-500,5000,2000, 0, 2000,"SCI41 - Fat time (ns)", "Fatima Energy (keV)");
      
      hA_FRS_Z1Z2_X4AoQ_FatE1vsE2[i] = MakeTH2('D',Form("Correlations/FRS-Prompt_Fatima/Z1Z2_X2AoQ/Gamma-Gamma/FatE1_vs_FatE2_Z1Z2_X2AoQgate%2d",i), Form("Fatima Energy 1 vs Energy 2 Z1 vs Z2 AND X2 vs AoQ Gate:%2d",i),2000, 0, 2000, 2000,0,2000);
     
     

       }
     
     Float_t init_Fat_EdT_cut[MAX_FRS_GATE][MAX_FRS_PolyPoints][2]; 
     //int num_ID_Z_AoQ_corrstep_fat = {6};
    // Float_t init_ID_Z_AoQ_corrstep_fat[8][8][2];
      for(int m=0; m<MAX_FRS_GATE; m++){
          for(int n=0; n<MAX_FRS_PolyPoints; n++){
           init_Fat_EdT_cut[m][n][0]=X_Fat_EdT_cut[m][n];
           init_Fat_EdT_cut[m][n][1]=Y_Fat_EdT_cut[m][n];
           
//            init_ID_Z_AoQ_corrstep_fat[m][n][0] =C_X_ZAoQ[m][n];
//            init_ID_Z_AoQ_corrstep_fat[m][n][1] =C_Y_ZAoQ[m][n];
      
      }
    }
    char name[50];
      for(int i=0; i<MAX_FRS_GATE; i++){
      
       sprintf(name,"cFat_EdT_cut%d",i);
     
        cFat_EdT_cut[i] = MakePolyCond("cFat_EdT_cut", name, MAX_FRS_PolyPoints, init_Fat_EdT_cut[i], "Fatima Prompt flash cut");
      }
 }
/**----------------------------------------------------------------------------------------------**/
  
 void EventCorrelProc::Process_FRS_Prompt_Fat(EventAnlStore* cInputMain, EventCorrelStore* cOutput){
     Long64_t dT_FRS_Fatima = 0;
  
      if(cInputMain->pFRS_WR>0 && cInputMain->pFAT_WR>0) dT_FRS_Fatima = cInputMain->pFAT_WR - cInputMain->pFRS_WR;
     //   if(dT_FRS_Fatima!=0) hA_FRSWR_FatWR->Fill(dT_FRS_Fatima);
        
         for(int k=0; k<cInputMain->pFatmult; k++){
         
          ///Energy WR dT
                 
                 ///WR Time gate FRS-Fatima
         
                if(dT_FRS_Fatima>fCorrel->GFRS_Fat_TLow && dT_FRS_Fatima < fCorrel->GFRS_Fat_THigh){
                  
                    
                    if(cInputMain->pFat_QDC_E[k]>0){
                     //   hA_FRS_FatE->Fill(cInputMain->pFat_QDC_E[k]);           
                      
                       
                     for(int gate=0;gate<MAX_FRS_GATE;gate++){
                          
                        
              if(cInputMain->pSC40[0]>0 && cInputMain->pFat_TDC_T[k]>0){
                         ///Cut the prompt flash with 2D poly
        
                    ///This is a Prompt flash cut
      if(cFat_EdT_cut[gate]->Test((cInputMain->pFat_TDC_T[k]-cInputMain->pSC40[0])*0.025,cInputMain->pFat_QDC_E[k])==true){
             
                         ///Z vs A/Q spectra
                   
            if(cInputMain->pFRS_ZAoQ_pass[gate]==true ){
                        
                hA_FRS_ZAoQ_FatE[gate]->Fill(cInputMain->pFat_QDC_E[k]);
                    
                    if(cInputMain->pFat_TDC_T[k]>0) hA_FRS_ZAoQ_FatEvsT[gate]->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pSC40[0])*0.025, cInputMain->pFat_QDC_E[k]);
                            
                
                         }
                for(int l=0; l<cInputMain->pFatmult; l++){
                    if(k!=l && (cInputMain->pFat_TDC_T[l] - cInputMain->pSC41[0])*0.025 > 25. && (cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025>fCorrel->GFat1_Fat2_Low && (cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025>fCorrel->GFat1_Fat2_High){
                         
                        hA_FRS_ZAoQ_FatE1vsE2[gate]->Fill(cInputMain->pFat_QDC_E[k],cInputMain->pFat_QDC_E[l]);
                         }
                }
                
                   if(cInputMain->pFRS_Z_Z2_pass[fCorrel->GZ1Z2_Gate]==true){
                    ///Z1 Z2:  X2 A/Q gate
                      if(cInputMain->pFRS_x2AoQ_pass[gate]==true){
                           hA_FRS_Z1Z2_X2AoQ_FatE[gate]->Fill(cInputMain->pFat_QDC_E[k]);
                        
                      if(cInputMain->pFat_TDC_T[k]>0) hA_FRS_Z1Z2_X2AoQ_FatEvsT[gate]->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pSC40[0])*0.025, cInputMain->pFat_QDC_E[k]);
                      
                      for(int l=0; l<cInputMain->pFatmult; l++){
                    if(k!=l && (cInputMain->pFat_TDC_T[l] - cInputMain->pSC41[0])*0.025 > 25. && (cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025>fCorrel->GFat1_Fat2_Low && (cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025>fCorrel->GFat1_Fat2_High){
                         
                        hA_FRS_Z1Z2_X2AoQ_FatE1vsE2[gate]->Fill(cInputMain->pFat_QDC_E[k],cInputMain->pFat_QDC_E[l]);
                                    }
                                }
                      
                  }
                 ///Z1 Z2:  X4 A/Q gate
                       if(cInputMain->pFRS_x4AoQ_pass[gate]==true){  
                        
                        hA_FRS_Z1Z2_X4AoQ_FatE[gate]->Fill(cInputMain->pFat_QDC_E[k]);
                       
                        if(cInputMain->pFat_TDC_T[k]>0) hA_FRS_Z1Z2_X4AoQ_FatEvsT[gate]->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pSC40[0])*0.025, cInputMain->pFat_QDC_E[k]);
                        
                         for(int l=0; l<cInputMain->pFatmult; l++){
                    if(k!=l && (cInputMain->pFat_TDC_T[l] - cInputMain->pSC41[0])*0.025 > 25. && (cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025>fCorrel->GFat1_Fat2_Low && (cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025>fCorrel->GFat1_Fat2_High){
                         
                        hA_FRS_Z1Z2_X4AoQ_FatE1vsE2[gate]->Fill(cInputMain->pFat_QDC_E[k],cInputMain->pFat_QDC_E[l]);
                                    }
                                }
                                
                            }
                        }
                    }
                }
            }
        }
    }
}
              
              ///Tested 16.09.20 fatima dT gate on 325, 680keV, 1415 keV gammas in 96Pd
              
              
               if(dT_FRS_Fatima>fCorrel->GFRS_Fat_TLow && dT_FRS_Fatima < fCorrel->GFRS_Fat_THigh){
              
              
              for(int k=0; k<cInputMain->pFatmult; k++){
              
               if((cInputMain->pFat_TDC_T[k] - cInputMain->pSC41[0])*0.025 > 25.){
                            
               ///Start with Fatima prompt lifetime analysis 
               if(fCorrel->GSetup_corr_FRS_Fatima_LT==true){
                   if(cInputMain->pFRS_ZAoQ_pass[fCorrel->GPID_Gate_FRS_Fatima_LT]==true ){

      /// --------------------Start-Stop -------------------------------------///           
      
        for(int l=0; l<cInputMain->pFatmult; l++){
            if(k!=l && (cInputMain->pFat_TDC_T[l] - cInputMain->pSC41[0])*0.025 > 25.){
        ///Lifetime 1 (2+ 96Pd)
        if(cInputMain->pFat_QDC_E[k]>fCorrel->GFRSFat_LT1LowStart && cInputMain->pFat_QDC_E[k]<fCorrel->GFRSFat_LT1HighStart && cInputMain->pFat_QDC_E[l]>fCorrel->GFRSFat_LT1LowStop && cInputMain->pFat_QDC_E[l]<fCorrel->GFRSFat_LT1HighStop) {
            
            hA_FRS_Fat_LT1_start_stop->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);
            hA_FRS_Fat_LT1_start_stop_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);

                         }
                         
        ///Lifetime 2 (4+ 96Pd)            
        if(cInputMain->pFat_QDC_E[k]>fCorrel->GFRSFat_LT2LowStart && cInputMain->pFat_QDC_E[k]<fCorrel->GFRSFat_LT2HighStart && cInputMain->pFat_QDC_E[l]>fCorrel->GFRSFat_LT2LowStop && cInputMain->pFat_QDC_E[l]<fCorrel->GFRSFat_LT2HighStop) {
                            
             hA_FRS_Fat_LT2_start_stop_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);
             hA_FRS_Fat_LT2_start_stop->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);
                            
                         
                    }
                      
        ///Lifetime 3 (6+ 96Pd)           
        if(cInputMain->pFat_QDC_E[k]>fCorrel->GFRSFat_LT3LowStart && cInputMain->pFat_QDC_E[k]<fCorrel->GFRSFat_LT3HighStart && cInputMain->pFat_QDC_E[l]>fCorrel->GFRSFat_LT3LowStop && cInputMain->pFat_QDC_E[l]<fCorrel->GFRSFat_LT3HighStop) {
          
            hA_FRS_Fat_LT3_start_stop->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);
            hA_FRS_Fat_LT3_start_stop_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);
                       
                                                }
                                                
            /// --------------------Stop-Start -------------------------------------///                                            
         ///Lifetime 1 (2+ 96Pd)
        if(cInputMain->pFat_QDC_E[k]>fCorrel->GFRSFat_LT1LowStop && cInputMain->pFat_QDC_E[k]<fCorrel->GFRSFat_LT1HighStop && cInputMain->pFat_QDC_E[l]>fCorrel->GFRSFat_LT1LowStart && cInputMain->pFat_QDC_E[l]<fCorrel->GFRSFat_LT1HighStart) {
            
            hA_FRS_Fat_LT1_start_stop->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);
            hA_FRS_Fat_LT1_start_stop_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);

                         }
                         
        ///Lifetime 2 (4+ 96Pd)            
        if(cInputMain->pFat_QDC_E[k]>fCorrel->GFRSFat_LT2LowStop && cInputMain->pFat_QDC_E[k]<fCorrel->GFRSFat_LT2HighStop && cInputMain->pFat_QDC_E[l]>fCorrel->GFRSFat_LT2LowStart && cInputMain->pFat_QDC_E[l]<fCorrel->GFRSFat_LT2HighStart) {
                            
             hA_FRS_Fat_LT2_start_stop_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);
             hA_FRS_Fat_LT2_start_stop->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);
                            
                         
                    }
                      
        ///Lifetime 3 (6+ 96Pd)           
        if(cInputMain->pFat_QDC_E[k]>fCorrel->GFRSFat_LT3LowStop && cInputMain->pFat_QDC_E[k]<fCorrel->GFRSFat_LT3HighStop && cInputMain->pFat_QDC_E[l]>fCorrel->GFRSFat_LT3LowStart && cInputMain->pFat_QDC_E[l]<fCorrel->GFRSFat_LT3HighStart) {
          
            hA_FRS_Fat_LT3_start_stop->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);
            hA_FRS_Fat_LT3_start_stop_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);
                       
                                                }                                        
                    ///End of Stop Start                             
                                            }
                                        }
                                    } 
                                }///End of Fatima prompt lifetime analysis
                             }
                         }        
                   }
                }
        
  /**----------------------------------------------------------------------------------------------**/ 
 /**-------------------------------------FRS-FATIMA Long (Isomers) ---------------------------------------------------------**/  
 
  void EventCorrelProc::Make_FRS_LongIso_Fatima_Histos(){
    
      hA_FRS_PID_FatE_LongIso  = MakeTH1('F', "Correlations/FRS-LongIso_Fat/ZvsAoQ_Fat/LongdT_Fat_EnergySum_PIDGated", "Long T isomer search FatE", 4000, 0, 4000, "Energy/keV");
           
      hA_FRS_FatEvsT_LongIsoGated  = MakeTH2('D',"Correlations/FRS-LongIso_Fat/ZvsAoQ_Fat/LongdT_vs_FatE_PIDGated","Long T isomer search dT vs GeE", 4000, 0, 4000, fCorrel->GFRS_Ge_LongIso_HBin,fCorrel->GFRS_Ge_LongIso_HLow,fCorrel->GFRS_Ge_LongIso_HHigh,"Fat Energy (keV)", "dT");
      
      hA_FRS_FatE1vsFatE2_LongIsoGated  = MakeTH2('D',"Correlations/FRS-LongIso_Fat/FatE1_vs_FatE2_LongIsomer","Gamma-Gamma Long isomer gated", 2000, 0, 2000, 2000,0,2000,"Fat Energy1 (keV)", "Fat Energy2 (keV)");
      
     // sprintf(name,"cGe_EdT_cut%d",i);
     //   cGe_EdT_cut[i] = MakePolyCond("cGe_EdT_cut", name, 8, init_Ge_EdT_cut[i], "Ge Prompt flash cut");
      
    }
     /**----------------------------------------------------------------------------------------------**/  
void EventCorrelProc::Process_FRS_LongIso_Fat(EventAnlStore* cInputMain, EventCorrelStore* cOutput){
    

  
       for(int x=0; x< FAT_VME_MAX_MULTI; x++){
           FatE_Long[x]=0;
           FatT_Long[x]=0;
           FatE_Prm_Long[x]=0;
           FatT_Prm_Long[x]=0;
       }
        dT_frsfat_long=0;
        dT_frsfat_prompt=0;
        dT_FRS_Fatima_WR=0;
        Fat_mult_long=0;
        Fat_mult_prompt=0;
        dT_frsfat_mult_long=0;
        dT_frsfat_mult_prompt=0;
        dT_FatT_long=0;
        dT_FatT_prompt=0;
        Fat_FirstT_long=0;
        Fat_FirstT_prompt=0;
       
        if(cInputMain-> pFAT_WR> 0){
      
                if(cInputMain->pFRS_ZAoQ_pass[fCorrel->GLongIso_PID_Gate]==true && cInputMain-> pFRS_WR!=0){
                        ts_fat= cInputMain-> pFRS_WR;
                    }
                  
                  else if (cInputMain-> pFAT_WR>0){
            
                        ts_fat=cInputMain-> pFAT_WR;
                    }
    }
          ///------ reset the local variables in case the time is too long ------//
		 if(tag_all.size()>0)
			 {
				 for(int i=0; i<tag_fat_all.size();i++)
					 {
                 ///The reset time windows are set in Configuration_Files/correlations.dat                 
                   if((ts_fat-ts_fat_all.at(i))>fCorrel->GFRS_Ge_LongIso_THigh )

							 {
								 tag_fat_all.erase(tag_fat_all.begin()+i);
								 ts_fat_all.erase(ts_fat_all.begin()+i);
                          
							 }
                     }
             }///End of removing/clearing arrays for long correlations
             

             if(cInputMain->pFRS_WR>0  && cInputMain->pFRS_ZAoQ_pass[fCorrel->GLongIso_PID_Gate]==true ){
//                   if(cGe_EdT_cut[gate]->Test(cInputMain->pGal_EAddback[g][h],dT_frsge_prompt)==false) 
                    if(tag_fat_all.size()==0)
                        { 
                         tag_fat_all.push_back(1);
                         ts_fat_all.push_back(ts_fat);
                        }
             
        } ///end of FRS long correlations set initial values

       else if (cInputMain->pFAT_WR>0 ){
  
            for(int i=(tag_fat_all.size()-1); i>=0; i--)
							 {
            /// ---------- frs-gamma long correlations -------  //
			     if(tag_fat_all.at(i)==1&&    (ts_fat-ts_fat_all.at(i))>fCorrel->GFRS_Ge_LongIso_TLow)
									 {
                                   dT_frsfat_long=ts_fat-ts_fat_all.at(i);
                                   
                    for(int k=0; k<cInputMain->pFatmult; k++){

                          if(cInputMain->pFat_QDC_E[k]>0) {
                             FatE_Long[Fat_mult_long] = cInputMain->pFat_QDC_E[k];
                             FatT_Long[Fat_mult_long] = cInputMain->pFat_TDC_T[k];
                            
                             Fat_mult_long++;
                          }
                                 
                          if(cInputMain->pFat_QDC_E[k]>0 && dT_frsfat_long>0  ){

                             if(Fat_mult_long==1 ){
           ///Note that Fat_FirstT_Long is not always necessarily the 'first' gamma (i.e. lowest time) since it loops over all detectors starting from 0
                                    Fat_FirstT_long=cInputMain->pFat_TDC_T[k];
                            
                                    hA_FRS_PID_FatE_LongIso->Fill(cInputMain->pFat_QDC_E[k]);
                                    hA_FRS_FatEvsT_LongIsoGated->Fill(cInputMain->pFat_QDC_E[k],dT_frsfat_long/fCorrel->GFRS_Ge_LongIso_TScale);
                            }
                        
                ///This is for when there is more than 1 gamma in an event to get the correct time                    
                    if(Fat_mult_long>1 && cInputMain->pFat_TDC_T[k]>0 ){
                            dT_FatT_long =(cInputMain->pFat_TDC_T[k]-Fat_FirstT_long);
                            dT_frsfat_mult_long=dT_frsfat_long + ABS(dT_FatT_long);
                                 
                         if(cInputMain->pFat_QDC_E[k]>10 && dT_frsfat_mult_long>0){
                             
                            hA_FRS_FatEvsT_LongIsoGated->Fill(cInputMain->pFat_QDC_E[k],dT_frsfat_mult_long/fCorrel->GFRS_Ge_LongIso_TScale);
                            
                        
                            hA_FRS_PID_FatE_LongIso->Fill(cInputMain->pFat_QDC_E[k]);
                            
                          
                                 }
                              }                                           
                          }         
                     }
                //}  
                ///Gamma Gamma Test phase Long isomer AKM170920
                for(int m=0; m<Fat_mult_long; m++){
                for(int n=0; n<Fat_mult_long; n++){
                if(m==n) continue;
                  if((FatT_Long[m]-FatT_Long[n])>fCorrel->GGe1_Ge2_Low && (FatT_Long[m]-FatT_Long[n])<fCorrel->GGe1_Ge2_High){

                 hA_FRS_FatE1vsFatE2_LongIsoGated->Fill(FatE_Long[m],FatE_Long[n]);
                                
                        }
                    }
                } 
            }
        }
       }
        
        ///Now add the prompt gammas to the histograms. This can be selected on and off in correlations.dat
        if (fCorrel->GSetup_corr_FRS_Ge_LongIso_incprmt==true){
            
           dT_frsfat_prompt = 0;
        // bool Fat_dT_cut=false;
    if(cInputMain->pFRS_WR>0 && cInputMain->pFAT_WR>0)  dT_FRS_Fatima_WR = cInputMain->pFAT_WR - cInputMain->pFRS_WR;
    
        if(dT_FRS_Fatima_WR>fCorrel->GFRS_Fat_TLow && dT_FRS_Fatima_WR < fCorrel->GFRS_Fat_THigh){

        if(cInputMain->pFRS_ZAoQ_pass[fCorrel->GLongIso_PID_Gate]==true){
          
       
                for(int k=0; k<cInputMain->pFatmult; k++){
dT_frsfat_prompt = ((cInputMain->pFat_TDC_T[k]-cInputMain->pSC40[0])*0.025);

                        if( cInputMain->pFat_QDC_E[k]>0){
                             FatE_Prm_Long[Fat_mult_prompt] = cInputMain->pFat_QDC_E[k];
                             FatT_Prm_Long[Fat_mult_prompt] = cInputMain->pFat_TDC_T[k];
                            Fat_mult_prompt++;
                        }
       
       ///Cut the prompt flash with 2D poly            
        if( cFat_EdT_cut[fCorrel->GLongIso_PID_Gate]->Test((cInputMain->pFat_TDC_T[k]-cInputMain->pSC40[0])*0.025,cInputMain->pFat_QDC_E[k])==true){
 
           
                  
                    ///Get the 'first' gamma
                 if(Fat_mult_prompt==1){
                   
                     Fat_FirstT_prompt=cInputMain->pFat_TDC_T[k];
              
                if(cInputMain->pFat_QDC_E[k]>1){ 
                     ///Energy vs WR dT
                    hA_FRS_PID_FatE_LongIso->Fill(cInputMain->pFat_QDC_E[k]);
                    hA_FRS_FatEvsT_LongIsoGated->Fill(cInputMain->pFat_QDC_E[k],dT_frsfat_prompt/fCorrel->GFRS_Ge_LongIso_TScale);
        
                    
                      }
                 }///End of multiplicity 1 gammas
   
     
     if(cFat_EdT_cut[fCorrel->GLongIso_PID_Gate]->Test(dT_frsfat_prompt,cInputMain->pFat_QDC_E[k])==true) {
              ///Correct the times for more than one gamma in an event
                 if(Fat_mult_prompt>1 && cInputMain->pFat_TDC_T[k]>0 ){    
               
                  dT_FatT_prompt = (cInputMain->pFat_TDC_T[k]-Fat_FirstT_prompt);
                
                  dT_frsfat_mult_prompt=(cInputMain->pFAT_WR-cInputMain->pFRS_WR) + ABS(dT_FatT_prompt);
                
                  hA_FRS_PID_FatE_LongIso->Fill(cInputMain->pFat_QDC_E[k]);
                
                  if(dT_frsfat_mult_prompt!=0){ 
    
                        hA_FRS_FatEvsT_LongIsoGated->Fill(cInputMain->pFat_QDC_E[k],dT_frsfat_mult_prompt/fCorrel->GFRS_Ge_LongIso_TScale); 
                      
                          
                                    }
                                }
                            }
                        }
                    
               }
            }
               
               //Gamma gamma for the long isomers, prompt part (needs testing)
                for(int m=0; m<Fat_mult_prompt; m++){
                for(int n=0; n<Fat_mult_prompt; n++){
                    if(FatE_Prm_Long[m]>0 && FatE_Prm_Long[n]>0){
                    if(m==n) continue;
                  if((FatT_Prm_Long[m]-FatT_Prm_Long[n])>fCorrel->GGe1_Ge2_Low && (FatT_Prm_Long[m]-FatT_Prm_Long[n])<fCorrel->GGe1_Ge2_High){
                
                      if(cFat_EdT_cut[fCorrel->GLongIso_PID_Gate]->Test(dT_frsfat_prompt,FatE_Prm_Long[m])==true && cFat_EdT_cut[fCorrel->GLongIso_PID_Gate]->Test(dT_frsfat_prompt,FatE_Prm_Long[n])==true) {
                    
                if(cInputMain->pFRS_ZAoQ_pass[fCorrel->GLongIso_PID_Gate]==true)    hA_FRS_FatE1vsFatE2_LongIsoGated->Fill(FatE_Prm_Long[m],FatE_Prm_Long[n]);
                                    }
                                }
                            }
                        }
                    }  
                }
            }
      }
    /**----------------------------------------------------------------------------------------------**/ 

 /**----------------------------------------------------------------------------------------------**/
 /**--------------------------------- (FRS)-AIDA-bPlastic-Germanium  (Beta-Delayed Gammas)  ------**/
 /**----------------------------------------------------------------------------------------------**/
 void EventCorrelProc::Make_Beta_Gamma_Histos(){
     TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
     
     hGe_BetaGamma = MakeTH1('F', "Correlations/Beta_Delayed_Gammas/Germanium/Ge_Energy_ImplantDecay_All", "Beta-Gamma Correlated energy", 4000, 0, 2000, "Energy/keV");
     
     hAida_Imp_bPlas_dT=  MakeTH1('I',"WR/AIDA/Aida_Implant-bPlast_WR_dT","White Rabbit Aida Implant-bPlas",10000,-100000,100000,"WR dT(Aida Implant - bPlast)[ns]", "Counts");
      
     hAida_Dec_bPlas_dT=  MakeTH1('I',"WR/AIDA/Aida_Decay-bPlast_WR_dT","White Rabbit Aida Decay-bPlast",1000,-100000,100000,"WR dT(Aida Decays-bPlast)[ns]", "Counts");
      
     hAida_Dec_Ge_dT=  MakeTH1('I',"WR/AIDA/Aida_Decay-Germanium_WR_dT","White Rabbit Aida Decay Germanium",1000,-100000,100000,"WR dT(Aida Decays - Germanium)[ns]", "Counts");
     
     hAida_Dec_Fatima_dT=  MakeTH1('I',"WR/AIDA/Aida_Decay-FatimaVME_WR_dT","White Rabbit Aida Decay-Fatima VME",1000,-100000,100000,"WR dT(Aida Decays - Fatima)[ns]", "Counts");
     
     hAidaImpDecdT = MakeTH1('F', "Correlations/Beta_Delayed_Gammas/Germanium/dT(Implant-Decay)_All", " Implant Decay Time", fCorrel->GAidaImpDecT_HBin, fCorrel->GAidaImpDecT_Low, fCorrel->GAidaImpDecT_High, "Energy/keV","Imp-Dec (s)");
     

     
     if(fCorrel->GSetup_corr_Beta_Gamma_Gamma==true){
//       hGe_BetaGamma_GeE1_GatedTrans = MakeTH1('I',"Correlations/Beta_Delayed_Gammas/Germanium/Energy/Gamma-Gamma/GeE1_GatedTrans","Fatima 95Pd BDG 382,716,1351 gated",4000,0,2000,"Energy (keV)", "Counts");
     }
      char name[50];
     for(int i =0; i<MAX_FRS_GATE; i++){
     hGe_BetaGamma_E[i] = MakeTH1('F', Form("Correlations/Beta_Delayed_Gammas/Germanium/Energy/Ge_BetaGam_Energy_PIDGate%d", i), Form("Germanium Energy Aida Beta-Gamma PID %d", i), 2000, 0, 2000, "Energy/keV");
     
     if(fCorrel->GSetup_corr_Beta_Gamma_Gamma==true){
     hGe_BetaGamma_GeE1_GeE2[i] = MakeTH2('D',Form("Correlations/Beta_Delayed_Gammas/Germanium/Energy/Gamma-Gamma/Ge1Ge2_BetaGam_PIDGate%d",i),Form("Germanium Gamma-Gamma Imp-Dec, PID Gate: %d",i), 4000, 0, 2000, 4000,0,2000,"Ge Energy1 (keV)", "Ge Energy2 (keV)");
     }
     
     hGe_BetaGamma_dT[i] = MakeTH1('F', Form("Correlations/Beta_Delayed_Gammas/Germanium/dT(Implant-Decay)/Implant-DecaydT_PIDGate%d", i), Form("dT Aida Implant-Decay Beta-Gamma PID %d", i), fCorrel->GAidaImpDecT_HBin,fCorrel->GAidaImpDecT_Low,fCorrel->GAidaImpDecT_High, "Implant-Decay dT (s)");
      
     hGe_BetaGamma_EdT[i] = MakeTH2('D',Form("Correlations/Beta_Delayed_Gammas/Germanium/EnergyvsdT(Implant-Decay)/Ge_BetaGam_EnergyvsdT_Gate%d",i),Form("dT Aida Implant-Decay vs Germanium Energy PID Gate %d",i), 4000, 0, 2000, fCorrel->GAidaImpDecT_HBin,fCorrel->GAidaImpDecT_Low,fCorrel->GAidaImpDecT_High,"Ge Energy (keV)", "Implant-Decay dT (s)");
     
     
    
     }
     ///2D Gates
//      Float_t init_ID_Z_AoQ_corrstep_BDG[8][8][2];
//       for(int m=0; m<8; m++){
//           for(int n=0; n<8; n++){
//            
//            
//            init_ID_Z_AoQ_corrstep_BDG[m][n][0] =C_X_ZAoQ[m][n];
//            init_ID_Z_AoQ_corrstep_BDG[m][n][1] =C_Y_ZAoQ[m][n];
//       
//       }
//     }
    
    // char name[50];
//      for(int i =0; i<8; i++){
//       sprintf(name,"cID_Z_AoQ_corrstep_BDG%d",i);
//       cID_Z_AoQ_corrstep_BDG[i] = MakePolyCond("FRS_ID_Gated_CorrStep_BDG", name, 8, init_ID_Z_AoQ_corrstep_BDG[i], "ZvsAoQ_BDG");
//      }
     ///Fatima
     if(fCorrel->GSetup_corr_Beta_Gamma_Fatima==true){

        
         

         for(int i=0; i<MAX_FRS_GATE; i++){
          hFat_BetaGamma_E[i] = MakeTH1('F', Form("Correlations/Beta_Delayed_Gammas/Fatima/Energy/Fat_BetaGam_Energy_PIDGated%d", i), Form("Fatima Energy Beta-Gamma PID %d", i), 2000, 0, 2000, "Energy/keV");
          
          hFat_BetaGamma_E1_E2[i] = MakeTH2('D',Form("Correlations/Beta_Delayed_Gammas/Fatima/Gamma-Gamma/FatE1FatE2_BetaGam_PIDGate%d",i),Form("Fatima Gamma-Gamma Beta Corr Gate: %d",i), 2000, 0, 2000, 2000,0,2000,"Fatima Energy1 (keV)", "Fatima Energy2 (keV)");
         }
     
        if(fCorrel->GSetup_corr_Beta_Gamma_Fatima_LT==true){
         hFat_LT1_start_stop= MakeTH1('I',"Correlations/Beta_Delayed_Gammas/Fatima/Lifetime/Start-Stop/Fat_LT1_start_stop","Fatima Lifetime 1 Start-Stop gated",20000,-10000,10000,"Time [ps]", "Counts/ps");
         
         hFat_LT1_start_stop_ns= MakeTH1('I',"Correlations/Beta_Delayed_Gammas/Fatima/Lifetime/Start-Stop/Fat_LT1_start_stop_ns","Fatima Lifetime 1 Start-Stop gated (ns)",100,-50,50,"Time [ns]", "Counts/1ns");
         
         hFat_LT2_start_stop= MakeTH1('I',"Correlations/Beta_Delayed_Gammas/Fatima/Lifetime/Start-Stop/Fat_LT2_start_stop","Fatima 95Pd Lifetime 2 gated",20000,-10000,10000,"Time [ps]", "Counts/ps");
         
         hFat_LT2_start_stop_ns= MakeTH1('I',"Correlations/Beta_Delayed_Gammas/Fatima/Lifetime/Start-Stop/Fat_LT2_start_stop_ns","Fatima 95Pd Lifetime 2 gated (ns)",100,-50,50,"Time [ns]", "Counts/1ns");
///---------------------------------------------------------------------------------------------//
         
         hFat_LT1_stop_start= MakeTH1('I',"Correlations/Beta_Delayed_Gammas/Fatima/Lifetime/Stop-Start/Fat_LT1_BetaGam_stop_start","Fatima Lifetime 1 Stop-Start gated",20000,-10000,10000,"Time [ps]", "Counts/ps");
         
         hFat_LT1_stop_start_ns= MakeTH1('I',"Correlations/Beta_Delayed_Gammas/Fatima/Lifetime/Stop-Start/Fat_LT1_BetaGam_stop_start_ns","Fatima Lifetime 1 Stop-Start gated (ns)",100,-50,50,"Time [ns]", "Counts/1ns");
         
         hFat_LT2_stop_start= MakeTH1('I',"Correlations/Beta_Delayed_Gammas/Fatima/Lifetime/Stop-Start/Fat_LT2_BetaGam_stop_start","Fatima Lifetime 2 Stop-Start gated",20000,-10000,10000,"Time [ps]", "Counts/ps");
         
         hFat_LT2_stop_start_ns= MakeTH1('I',"Correlations/Beta_Delayed_Gammas/Fatima/Lifetime/Stop-Start/hFat_LT2_BetaGam_stop_start_ns","Fatima Lifetime 2 Stop-Start gated (ns)",100,-50,50,"Time [ns]", "Counts/1ns");
              
          }
     }
}
 /**------------------------------------(FRS)-AIDA-bPlastic  (Beta Decay)----------------------------**/
 ///This is an adpated version of the tree reader to look for Beta-gamma correlations by HMA/NH
 void EventCorrelProc::Process_Beta_Gamma(EventAnlStore* cInputMain, EventCorrelStore* cOutput){    
     
 
     TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
      
        Long64_t AIDA_dT_imp_decay;
        Long64_t AIDA_dT_imp_decay_FRS_gated = 0;
        Long64_t AIDA_dT_decay_bPlast = 0;
        bool bPlas_punchthrough =false;
        bool bPlas_fired=false;
        bool SC41_fired = false;
        int ImpIterator =0, DecayIterator=0;
        double lastdT = 1E15;
        int numImpIonsAIDA=0;
        int AidaDecMult=0;
        int64_t minTime = 0;
        int strx = 0;
        int stry = 0;
        int64_t dT = 0;
        Int_t GateTemp=100;
        Int_t goodhit = 0;
        int64_t dT_Gate[8];
        double lastdT_Gate[8]; ///I had to declare this a double to avoid a crash (was int64_t)
        Int_t DSSD_Gate[8];
        Int_t strx_Gate[8];
        Int_t stry_Gate[8];
        int64_t DecTime_Gate[8];
        Int_t B = 1;
        int64_t DecTime = 0;
     ///   double testbg[100];
        int galhits=0;
        double GeE[Germanium_MAX_HITS];
        
        for(int x=0; x<Germanium_MAX_HITS; x++)GeE[x]=0;
        
  /// for(int i=0;i<100; i++)testbg[i]=0;
        
        for(int i=0; i<MAX_FRS_GATE; i++)lastdT_Gate[i]=0;
         //for(int i=0; i<32; i++)  cInputMain-> pbPlas_ToTCalib[i]=100;
         
//         ///Get Plastic fired
//     for(int a=1; a<3; a++){ ///Detector number
//         for (int b = 0; b < 16; b++){  ///Channel number
//             for (int c = 0; c < cInputMain->pbPlas_PMT_Lead_N[a][b]; c++){ 
//        if (cInputMain-> pbPlas_ToTCalib[2][b][c]>0) bPlas_punchthrough=true;
//        if (cInputMain-> pbPlas_ToTCalib[a][b][c]>fCorrel->GbPlast_Egate_low && cInputMain-> pbPlas_ToTCalib[a][b][c]<fCorrel->GbPlast_Egate_high) bPlas_fired=true;
//                         }
//                  }
//              }
        ///AIDA
        for (auto& cInputRef : cInputMain->pAida)
        {
          auto* cInput = &cInputRef;
       if(AIDA_WR>0 && bPLAS_WR>0){
       dT_AIDA_bPlast = AIDA_WR - bPLAS_WR;
       ///hA_bPlast_dT->Fill(dT_AIDA_bPlast);
       
       dT_FRS_bPlast = FRS_WR-bPLAS_WR;
       ///hFRS_bPlast_dT->Fill(dT_FRS_bPlast);
             }
             

     std::vector<AidaHit> imphits = cInput->Implants;
     std::vector<AidaHit> dechits = cInput->Decays; 
    
      AidaHit firstDec;
      AidaHit BestImp;
     ///IMPLANTS
     for(auto& i : imphits){
          AidaHit imphit = i;
          hAida_Imp_bPlas_dT->Fill(imphit.Time- cInputMain->pbPLAS_WR);
            ///Get Plastic fired
   if(imphit.Time> fCorrel->GAIDA_Imp_bPlas_TLow && imphit.Time< fCorrel->GAIDA_Imp_bPlas_TLow){
    for(int a=1; a<=cInputMain->pbPlasDetNum; a++){ ///Detector number
        for (int b = 0; b <=cInputMain->pbPlasChan[a]; b++){  ///Channel number
            for (int c = 0; c <= cInputMain->pbPlas_PMT_Lead_N[a][b]; c++){ 
      
       ///Punchthrough in bPlast Downstream         
       if (cInputMain-> pbPlas_ToTCalib[2][b][c]>0) bPlas_punchthrough=true;
      
       if (cInputMain-> pbPlas_ToTCalib[a][b][c]>fCorrel->GbPlast_Egate_low && cInputMain-> pbPlas_ToTCalib[a][b][c]<fCorrel->GbPlast_Egate_high) bPlas_fired=true;
       
//        if(cInputMain-> pbPlas_ToTCalib[a][b][c]>0 && cInputMain->pOnSpill==false) bPlas_ToT_ch_beamoff[a][b]->Fill(cInputMain-> pbPlas_ToTCalib[a][b][c]);
//        if(cInputMain-> pbPlas_ToTCalib[a][b][c]>0 && cInputMain->pOnSpill==true) bPlas_ToT_ch_beamon[a][b]->Fill(cInputMain-> pbPlas_ToTCalib[a][b][c]);
       
                        }       
                    }
                 }
             } ///End of bPlastic punchthrough/fired conditions
         
     if(bPlas_punchthrough == 0){ /// Check this isn't a punchthrough event
     
      int ImpstripX = imphit.StripX;
      int ImpstripY = imphit.StripY;  
      int ImpDSSD = imphit.DSSD-1;
      if(imphit.DSSD<=2 && imphit.Stopped){ 
          jPID.Event = imphit.Event;
                jPID.DSSD = imphit.DSSD;
                jPID.StripX = imphit.StripX;
                jPID.StripY = imphit.StripY;
                jPID.PosX = imphit.PosX;
                jPID.PosY = imphit.PosY;
                jPID.Energy = imphit.Energy;
                jPID.EnergyFront = imphit.EnergyFront;
                jPID.EnergyBack = imphit.EnergyBack;
                jPID.StripXMin = imphit.StripXMin;
                jPID.StripXMax = imphit.StripXMax;
                jPID.StripYMin = imphit.StripYMin;
                jPID.StripYMax = imphit.StripYMax;
                jPID.ClusterSizeX = imphit.ClusterSizeX;
                jPID.ClusterSizeY = imphit.ClusterSizeY;
                jPID.Time = imphit.Time;
                jPID.TimeFront = imphit.TimeFront;
                jPID.TimeBack = imphit.TimeBack;
                jPID.FastTime = imphit.FastTime;
                jPID.FastTimeFront = imphit.FastTimeFront;
                jPID.FastTimeBack = imphit.FastTimeBack;
                jPID.Stopped = imphit.Stopped;
                
               // jPID.FRS_Z = *FRS_z;
               // jPID.FRS_AoQ = *FRS_AoQ;
                jPID.GatePass = 100;
              
                for(int gate=0;gate<MAX_FRS_GATE;gate++){
                    if(fCorrel->GBDG_FRS_Gate==1 && cInputMain->pFRS_ZAoQ_pass[gate]==true ){ 
                         
                        jPID.GatePass = gate;
                      
                    }
                    if(fCorrel->GBDG_FRS_Gate==2 && cInputMain->pFRS_Z_Z2_pass[fCorrel->GZ1Z2_Gate]==true && cInputMain->pFRS_x2AoQ_pass[gate]==true){ 
                         
                        jPID.GatePass = gate;
  
                    }
                    if(fCorrel->GBDG_FRS_Gate==3 && cInputMain->pFRS_Z_Z2_pass[fCorrel->GZ1Z2_Gate]==true && cInputMain->pFRS_x4AoQ_pass[gate]==true){ 
                         
                        jPID.GatePass = gate;
  
                    }
                } 
                implantMap.emplace(jPID.Time,jPID);
               ///Histograms to be implemented
                //hAidaBestImpHitPat[imphit.DSSD-1]->Fill(imphit.StripX,imphit.StripY); 
            
                numImpIonsAIDA++;
                BestImp = imphit;
        }
      }
     }///End of implants
     
     
     for (auto& j : dechits){
    
     
     
         AidaHit dechit = j;
           
       
           if(bPlas_punchthrough == 0){ /// Check this isn't a punchthrough event
            if(AidaDecMult == 0){
          firstDec = dechit;/// Take the first decay in the stitched event as a reference time.

          /// Remove all implants from map that came >Xs ago (defined in Correlations.dat)
            minTime = j.Time - fCorrel->GAidaImpDecT_High*1e9;
              auto itLow = implantMap.lower_bound(minTime);
            if (itLow != implantMap.end()){
                if(itLow == implantMap.begin()){}
                else if(std::prev(itLow) == implantMap.begin()){
                  implantMap.erase(implantMap.begin());
                }
                else{
                  implantMap.erase(implantMap.begin(),std::prev(itLow));
                  //Erase all entries out of correlation window
                }
            }          
      }
      AidaDecMult++;

      ///Set the gates 
      
          
      if((dechit.TimeFront - dechit.TimeBack)<fCorrel->GAidaFB_dT && (dechit.TimeFront - dechit.TimeBack)>-fCorrel->GAidaFB_dT){/// Front-Back Time condition
     if(dechit.Time!=0 && cInputMain->pbPLAS_WR!=0 )hAida_Dec_bPlas_dT->Fill(dechit.Time-cInputMain->pbPLAS_WR);
           
           
    //  if((dechit.Time - cInputMain->pbPLAS_WR)>fCorrel->GAIDA_bPlas_TLow && (dechit.Time - cInputMain->pbPLAS_WR)<fCorrel->GAIDA_bPlas_THigh && bPlas_fired==1){ /// Gate on coincidences with bPlast
          
      if((dechit.EnergyFront-dechit.EnergyBack)<fCorrel->GAidaFB_dE && (dechit.EnergyFront - dechit.EnergyBack)>-fCorrel->GAidaFB_dE){/// Front-Back Energy condition   
          
      if(dechit.EnergyFront < fCorrel->GAIDA_DecEFront && dechit.EnergyBack < fCorrel->GAIDA_DecEBack){ ///"good" decay conditions here
                 
      
      ///dT for detector systems
     if(dechit.Time!=0 && cInputMain->pGe_WR!=0) hAida_Dec_Ge_dT->Fill(dechit.Time-cInputMain->pGe_WR);
     if(dechit.Time!=0 && cInputMain->pFAT_WR!=0) hAida_Dec_Fatima_dT->Fill(dechit.Time-cInputMain->pFAT_WR);
     
          /// Initialising...  
            dT = 1E15;
            lastdT = 1E15;
            strx = 0;
            stry = 0; 
            DecTime = 0;
            GateTemp = 100; 
            goodhit = 1;

            
for(int i=0;i<MAX_FRS_GATE;i++){
        
    dT_Gate[i] = 1E15;
    lastdT_Gate[i] = 1E15;
    DSSD_Gate[i] = 0;
    strx_Gate[i] = 0;
    stry_Gate[i] = 0;
    DecTime_Gate[i] = 0;
     
}
          /// Loop over implant map and look for correlations
        for(auto impIt = implantMap.begin(); impIt != implantMap.end(); impIt++){
               
         if(impIt->second.DSSD == dechit.DSSD ){ 
            
              if(dechit.StripXMax >= (impIt->second.StripXMin-B) && dechit.StripXMin <= impIt->second.StripXMax+B){
              if(dechit.StripYMax >= (impIt->second.StripYMin-B) && dechit.StripYMin <= impIt->second.StripYMax+B){
                                 
               
                  dT = (dechit.Time) - impIt->second.Time;
                  GateTemp = impIt->second.GatePass;
            
                  if(dT < lastdT){
                      lastdT = dT;
                      DecTime = dechit.Time;
                      strx = dechit.StripX;
                      stry = dechit.StripY;
                      
                  }
               
                  dT_Gate[GateTemp] = (dechit.Time) - impIt->second.Time;
                    
                  if(dT_Gate[GateTemp] < lastdT_Gate[GateTemp]){
                      lastdT_Gate[GateTemp] = dT_Gate[GateTemp];
                    
                      DecTime_Gate[GateTemp] = dechit.Time;
                      strx_Gate[GateTemp] = dechit.StripX;
                      stry_Gate[GateTemp] = dechit.StripY; 
                }                                     
              }
            }
          }    
        } /// Searching the implant multimap
      }///Good decay criteria 
     } /// Front-Back Energy condition   
    }/// Front-Back Time condition   
   //} ///WR coincidences with bPlast
 }///End of punchthrough 
}///End of Decays
     
     ///Here we go with the beta-gamma coincidences: This is for all
     if(double(lastdT)/1e9 < fCorrel->GAidaImpDecT_High &&  double(lastdT)/1e9 > fCorrel->GAidaImpDecT_Low && goodhit == 1){
    
   
      hAidaImpDecdT->Fill(double(lastdT)/1E9);  /// Time difference for all correlations
       
       // Looking at bPlast coincidences (AKM This will come later)
    //   if(*bPlasWR>0){
    //       hbPlastAidaDecWRdT_corr->Fill(DecTime-*bPlasWR);
    //   }   
   //    if(*bPlasWR==0) hbPlastAidaDecWRdT_corr->Fill(0);
       
    
       if((DecTime - cInputMain->pGe_WR)>fCorrel->GAida_Ge_WRdT_Low && (DecTime - cInputMain->pGe_WR)<fCorrel->GAida_Ge_WRdT_High){/// Gate on coincidence with Gammas
           
         // hAidaImpDecdT_GeCoin->Fill(double(lastdT)/1E6);  // Time difference for correlations with a gamma
          //cout << "Gate is: " << GateTemp << endl << endl;
          //cout << "lastdT is: " << lastdT << endl << endl;
          //cout << "lastdT_Gate[GateTemp]: " <<  lastdT_Gate[GateTemp] << endl << endl;
          
            for(int g=0; g<Germanium_MAX_DETS; g++){
                    for (int h=0; h<Germanium_CRYSTALS; h++){
                            if(cInputMain->pGe_EAddback[g][h]>0&& (g!=Germanium_SC41_Det||g!=Germanium_SC41_Det_Digi||g!=Germanium_TimeMachine_Det)){
                                hGe_BetaGamma->Fill(cInputMain->pGe_EAddback[g][h]); 
  
                }
            }
          } ///End of Ge loop  
       }///End of Ge time gate 
     }///End of beta-gamma coincidences
     
     
     ///Beta-gamma coincidences PID Gated 
     
       
       for(int i=0;i<MAX_FRS_GATE;i++){
          if(double(lastdT_Gate[i])/1e9 < fCorrel->GAidaImpDecT_High &&  double(lastdT_Gate[i])/1e9 > fCorrel->GAidaImpDecT_Low && goodhit == 1 ){
              
          if((DecTime_Gate[i]-cInputMain->pGe_WR)>fCorrel->GAida_Ge_WRdT_Low && (DecTime_Gate[i]-cInputMain->pGe_WR)<fCorrel->GAida_Ge_WRdT_High){ 
    
              //cout << "New lastdT_Gate[i]: " << lastdT_Gate[i] << endl << endl;
              //hAidaImpDecdT_Gate[i]->Fill(double(lastdT_Gate[i])/1E6);
             // hAidaDecHitPat_corr_Gate[DSSD_Gate[i]-1][i]->Fill(strx_Gate[i],stry_Gate[i]);

            galhits=0;
            ///  Correlated Germanium gammas
              for(int g=0; g<Germanium_MAX_DETS; g++){
                    for (int h=0; h<Germanium_CRYSTALS; h++){
                        
                        
                 if(cInputMain->pGe_EAddback[g][h]>0&& (g!=Germanium_SC41_Det||g!=Germanium_SC41_Det_Digi||g!=Germanium_TimeMachine_Det) && lastdT_Gate[i]!=0){
               
                       hGe_BetaGamma_E[i]->Fill(cInputMain->pGe_EAddback[g][h]);    
                       hGe_BetaGamma_dT[i]->Fill(double(lastdT_Gate[i])/1e9); 
                       hGe_BetaGamma_EdT[i]->Fill(cInputMain->pGe_EAddback[g][h],double(lastdT_Gate[i])/1e9); 

                       GeE[galhits]=cInputMain->pGe_EAddback[g][h];
                       galhits++;
                    
               }
            }
          }
          
               ///Gamma-Gamma
               if(fCorrel->GSetup_corr_Beta_Gamma_Gamma==true){
                   for(int x=0; x<galhits; x++){
                   for(int y=0; y<galhits; y++){
                        if (x==y) continue;
                     hGe_BetaGamma_GeE1_GeE2[i]->Fill(GeE[x],GeE[y]);
                      
                       
                       }
                   }
               }
                                    
        }///End of Germaniums
         
         ///Fatima beta-delayed gammas
         if(fCorrel->GSetup_corr_Beta_Gamma_Fatima==true){
         
             if((DecTime_Gate[i]-cInputMain->pFAT_WR)>fCorrel->GAida_Fat_WRdT_Low && (DecTime_Gate[i]-cInputMain->pFAT_WR)<fCorrel->GAida_Fat_WRdT_High){ 
           
         for(int k=0; k<cInputMain->pFatmult; k++){

             if(cInputMain->pFat_QDC_E[k]>0 )   hFat_BetaGamma_E[i]->Fill(cInputMain->pFat_QDC_E[k]); 
        
             
             ///Gamma-Gamma Fatima       
                for(int l=0; l<cInputMain->pFatmult; l++){
                    
                 if(k==l) continue;
                if(cInputMain->pFat_QDC_E[k]>0 && cInputMain->pFat_QDC_E[l]>0) hFat_BetaGamma_E1_E2[i]->Fill(cInputMain->pFat_QDC_E[k], cInputMain->pFat_QDC_E[l]); 
              
                
                if(fCorrel->GSetup_corr_Beta_Gamma_Fatima_LT==true){
                if(i==fCorrel->GPID_Gate_Beta_Gamma_Fatima_LT){
                
             
  ///---------------------------------------- BDG Start-Stop -----------------------------///               
                     
                      
                 ///Lifetime 1 Start-Stop gates
                 if(cInputMain->pFat_QDC_E[k]>fCorrel->GBDGFat_LT1LowStart && cInputMain->pFat_QDC_E[k]<fCorrel->GBDGFat_LT1HighStart && cInputMain->pFat_QDC_E[l]>fCorrel->GBDGFat_LT1LowStop && cInputMain->pFat_QDC_E[l]<fCorrel->GBDGFat_LT1HighStop && cInputMain->pFat_TDC_T[k]>0 && cInputMain->pFat_TDC_T[l]>0) {
                            
                              hFat_LT1_start_stop->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);///Try ps   
                              
                              hFat_LT1_start_stop_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);///Try ns   
                               
                       } 
                       
                ///Lifetime 2 Start-Stop gates
                 if(cInputMain->pFat_QDC_E[k]>fCorrel->GBDGFat_LT2LowStart && cInputMain->pFat_QDC_E[k]<fCorrel->GBDGFat_LT2HighStart && cInputMain->pFat_QDC_E[l]>fCorrel->GBDGFat_LT2LowStop && cInputMain->pFat_QDC_E[l]<fCorrel->GBDGFat_LT2HighStop && cInputMain->pFat_TDC_T[k]>0 && cInputMain->pFat_TDC_T[l]>0) {
                            
                              hFat_LT2_start_stop->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);///Try ps 
                              
                              hFat_LT2_start_stop_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);///Try ns 
                            
                            } 
                            
      ///------------------------------------ BDG Stop-start -----------------------------///               
                     
                      
                 ///Lifetime 1 Stop-Start gates
    
                     if(cInputMain->pFat_QDC_E[k]>fCorrel->GBDGFat_LT1LowStop && cInputMain->pFat_QDC_E[k]<fCorrel->GBDGFat_LT1HighStop && cInputMain->pFat_QDC_E[l]>fCorrel->GBDGFat_LT1LowStart && cInputMain->pFat_QDC_E[l]<fCorrel->GBDGFat_LT1HighStart && cInputMain->pFat_TDC_T[k]>0 && cInputMain->pFat_TDC_T[l]>0) {
                            
                              hFat_LT1_stop_start->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);///Try ps   
                              
                              hFat_LT1_stop_start_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);///Try ns   
                              
                       } 
                       
                     ///Lifetime 2 Stop-Start gates
                     if(cInputMain->pFat_QDC_E[k]>fCorrel->GBDGFat_LT2LowStop && cInputMain->pFat_QDC_E[k]<fCorrel->GBDGFat_LT2HighStop && cInputMain->pFat_QDC_E[l]>fCorrel->GBDGFat_LT2LowStart && cInputMain->pFat_QDC_E[l]<fCorrel->GBDGFat_LT2HighStart && cInputMain->pFat_TDC_T[k]>0 && cInputMain->pFat_TDC_T[l]>0) {
                            
                              hFat_LT2_stop_start->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*25);///Try ps 
                              
                              hFat_LT2_stop_start_ns->Fill((cInputMain->pFat_TDC_T[k]-cInputMain->pFat_TDC_T[l])*0.025);///Try ns 
                            
                                } 
                          
   ///---------------------------------------- End of Centroid shift checks--------------------///   
                           }
                        }
                    }
                }
            }
         } 
       }///End of beta-gamma coincidences
      }/// end of PID gates loop
     
     
     lastdT=0;
     for (int i=0; i<MAX_FRS_GATE; i++) lastdT_Gate[i]=0;
    } ///End of aida
 }///end of function

 /**----------------------------------------------------------------------------------------------**/
 /**------------------------------------- End of Correlations ------------------------------------**/
 /**----------------------------------------------------------------------------------------------**/
  TGo4WinCond* EventCorrelProc::MakeWindowCond(const char* fname,
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
/**----------------------------------------------------------------------------------------------**/
 TGo4PolyCond* EventCorrelProc::MakePolyCond(const char* fname,
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
///-------------------------------------------------------------------------------------------------///
void EventCorrelProc::get_used_systems(){
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
}
  ///-------------------------------------------------------------------------------------------------///
  void EventCorrelProc::Ge_2DPromptFlashCut(){
  Int_t i, j;
  ifstream    file;
file.open("Configuration_Files/2D_Gates/Ge_PromptFlashCut.txt");
    
    for (i = 0; i < MAX_FRS_GATE; i++){
        for(j=0; j < MAX_FRS_PolyPoints; j++){
       if(IsData(file)) file  >> X_Ge_EdT_cut[i][j]>> Y_Ge_EdT_cut[i][j] ;
      
        }
    }
    if(file.good())cout<<"Setting Ge Prompt flash cuts"<<endl;
  file.close();
  }
  ///-------------------------------------------------------------------------------------------------///
  void EventCorrelProc::Fat_2DPromptFlashCut(){
  Int_t i, j;
  ifstream    file;
file.open("Configuration_Files/2D_Gates/Fatima_PromptFlashCut.txt");
    
    for (i = 0; i < MAX_FRS_GATE; i++){
        for(j=0; j < MAX_FRS_PolyPoints; j++){
       if(IsData(file)) file  >> X_Fat_EdT_cut[i][j]>> Y_Fat_EdT_cut[i][j] ;
       
        }
    }
    if(file.good())cout<<"Setting Fatima Prompt flash cuts"<<endl;
  file.close();
  }
  ///-------------------------------------------------------------------------------------------------///
  void EventCorrelProc::Fat_TimeCorrection(EventAnlStore* cInputMain){
   ///Do the dT time corrections
    for(int k=0; k<cInputMain->pFatmult; k++){
        if(cInputMain->pFat_TDC_ID[k] == 6 || cInputMain->pFat_TDC_ID[k] == 10 || cInputMain->pFat_TDC_ID[k] == 13 || cInputMain->pFat_TDC_ID[k] == 22 || cInputMain->pFat_TDC_ID[k] == 23 || cInputMain->pFat_TDC_ID[k] == 32 || cInputMain->pFat_TDC_ID[k] == 33 || cInputMain->pFat_TDC_ID[k] == 34 || cInputMain->pFat_TDC_ID[k] == 35 ){
        cInputMain->pFat_TDC_T[k] = 0.;
           }
           
        if(cInputMain->pFat_TDC_T[k]>0){

     cInputMain->pFat_TDC_T[k] = cInputMain->pFat_TDC_T[k]-fCal->TFatTDC_Chref_dT[cInputMain->pFat_TDC_ID[k]];
     
//      cout<<"1111 Event " << cInputMain->pEvent_Number << " cInputMain->pFat_TDC_T[k] " << cInputMain->pFat_TDC_T[k] << " fCal->TFatTDC_Chref_dT[cInputMain->pFat_TDC_ID[k]] " <<fCal->TFatTDC_Chref_dT[cInputMain->pFat_TDC_ID[k]] << " cInputMain->pFat_TDC_ID[k] " <<cInputMain->pFat_TDC_ID[k] << " k " << k << endl;
     
   
        }
     }
  }


///-------------------------------------------------------------------------------------------------///
  void EventCorrelProc::FRS_Gates_corrProc(){
  Int_t i;
  ifstream    file;
  
//    file.open("Configuration_Files/2D_Gates/dT_Det_SC41.txt");
//     if(!file.good()) cout<<"Configuration_Files/2D_Gates/ID_ZvsAoQ.txt Not found!"<<endl;
//    
//     for (i = 0; i < 8; i++){
//         for(int j=0; j<8; j++){
//        if(IsData(file)) file >>PID gated  >> C_X_ZAoQ[i][j]>> C_Y_ZAoQ[i][j] ;
//  
//         }
//     }
  file.close();
   
//    file.open("Configuration_Files/2D_Gates/ID_x2AoQ.txt");
//     if(!file.good()) cout<<"Configuration_Files/2D_Gates/ID_x2AoQ.txt Not found!"<<endl;
//     for (i = 0; i < 8; i++){
//          for (int j = 0; j < 6; j++){
//        if(IsData(file)) file >>X2AoQgnum>> XX2_AoQ[i][j]>> YX2_AoQ[i][j] ;
//          }
//     }
//   file.close();
  
  
 ///--------------------------------------------------------------------------------
//   file.open("Configuration_Files/2D_Gates/ID_x4AoQ.txt");
//     if(!file.good()) cout<<"Configuration_Files/2D_Gates/ID_x4AoQ.txt Not found!"<<endl;
//     for (i = 0; i < 8; i++){
//         for (int j = 0; j < 6; j++){
//        if(IsData(file)) file >> X4AoQgnum>>XX4_AoQ[i][j]>> YX4_AoQ[i][j] ;
//         }
//     }
//   file.close();
  
  
 ///--------------------------------------------------------------------------------
  
//   file.open("Configuration_Files/2D_Gates/ID_Z_Z2.txt");
//   if(!file.good()) cout<<"Configuration_Files/2D_Gates/ID_Z_Z2.txt Not found!"<<endl;
//  for (i = 0; i < 8; i++){
//     for (int j = 0; j < 6; j++){
//        if(IsData(file)) file >>Z1Z2gnum>> X_ZZ2[i][j]>> Y_ZZ2[i][j] ;
//     }
//     }
//   file.close();
  
  
 ///--------------------------------------------------------------------------------
//       file.open("Configuration_Files/2D_Gates/ID_ZvsAoQ.txt");
//     if(!file.good()) cout<<"Configuration_Files/2D_Gates/ID_ZvsAoQ.txt Not found!"<<endl;
//    
//     for (i = 0; i < 8; i++){
//         for(int j=0; j<8; j++){
//        if(IsData(file)) file >>C_ZAoQgnum >> C_X_ZAoQ[i][j]>> C_Y_ZAoQ[i][j] ;
//  
//         }
//     }
//   file.close();
  ///--------------------------------------------------------------------------------
//       file.open("Configuration_Files/2D_Gates/ID_dEdeg_Z1.txt");
//     
//     for (i = 0; i < 8; i++){
//         for(int j=0; j<6; j++){
//        if(IsData(file)) file >>dEdeggnum >> X_dEdeg[i][j]>> Y_dEdeg[i][j] ;
//         }
//     }
//   file.close();
  
  
}
  ///-------------------------------------------------------------------------------------------------///
  int EventCorrelProc::IsData(ifstream &f) {
        char dum;
        char dumstr[300];
        int retval = 0;

        /* 'operator >>' does not read End-of-line, therefore check if read 
            character is not EOL (10) */
        do {
            dum = f.get();
            if (dum == '#' || dum==' ')    // comment line => read whole line and throw it away
            f.getline(dumstr,300);
        }
        while ((dum == '#') || ((int)dum == 10)|| dum==' '); 

        f.unget();   // go one character back
        retval = 1;
        return retval;
    }

/**----------------------------------------------------------------------------------------------**/
/**----------------------------------------------------------------------------------------------**/
/**----------------------------------------------------------------------------------------------**/
