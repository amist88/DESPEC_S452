#include "CorrelParameter.h"
#include <iostream>

using namespace std;

CorrelParameter::CorrelParameter()
: TGo4Parameter("AnaOnlineCorPar")
{
    GSetup_corr_FRS_Ge =false;
    GSetup_corr_FRS_Gamma_Gamma =false;
    GSetup_corr_FRS_Ge_long =false;
    GSetup_corr_FRS_Ge_LongIso_incprmt = false;
    GSetup_corr_FRS_fat = false;
    GSetup_corr_FRS_Fatima_LT = false;
    
    GSetup_corr_FRS_Aida =false;
    GSetup_corr_Beta_Gamma_bPlastSpillOff=false;
    GSetup_corr_Beta_Gamma=false;
    GSetup_corr_Beta_Gamma_Gamma=false;
    GSetup_corr_Beta_Gamma_Fatima=false;
    GSetup_corr_Beta_Gamma_Fatima_LT=false;
    
    GZ1Z2_Gate=0;
   
    GbPlast_Egate_low = 0;
    GbPlast_Egate_high = 0;
    
    GFRS_AIDA_TLow = 0;
    GFRS_AIDA_THigh = 0;
    GAIDA_Imp_bPlas_TLow = 0;
    GAIDA_Imp_bPlas_THigh = 0;
    GAIDA_bPlas_TLow = 0;
    GAIDA_bPlas_THigh = 0;
    GFRS_Ge_TLow = 0;
    GFRS_Ge_THigh = 0;
    GbPlas_Fat_TLow=0;
    GbPlas_Fat_THigh=0;
    GbPlas_Fattam_TLow=0;
    GbPlas_Fattam_THigh=0;
    GbPlast_Ge_TLow = 0;
    GbPlast_Ge_THigh = 0;
    GFat_Fattam_TLow = 0;
    GFat_Fattam_THigh = 0;
    GFat_Ge_TLow = 0;
    GFat_Ge_THigh = 0;
    GFattam_Ge_TLow = 0;
    GFattam_Ge_THigh = 0;
    GAIDA_TM_FRS_TLow = 0;
    GAIDA_TM_FRS_THigh = 0;
    GAIDA_TM_Ge_TLow = 0; 
    GAIDA_TM_Ge_THigh = 0;
    GAIDA_TM_Fat_TLow = 0;
    GAIDA_TM_Fat_THigh = 0;
    GAIDA_TM_Fattam_TLow = 0;
    GAIDA_TM_Fattam_THigh = 0;
    GAIDA_TM_bPlast_TLow = 0;
    GAIDA_TM_bPlast_THigh = 0;
    
   
//     GGe_SCI41_Low=0;
//     GGe_SCI41_High=0;
    GGe1_Ge2_Low =0;
    GGe1_Ge2_High =0;
    GGe1_Ge2_HistoBin =0;
    GGe1_Ge2_HistoMin =0;
    GGe1_Ge2_HistoMax =0;
    GLongIso_PID_Gate = 0;
    GFRS_Ge_LongIso_THigh = 0;
    GFRS_Ge_LongIso_TLow = 0;
    GFRS_Ge_LongIso_HBin = 0;
    GFRS_Ge_LongIso_HLow = 0;
    GFRS_Ge_LongIso_HHigh = 0;
    GFRS_Ge_LongIso_TScale = 0;
    
    GBDG_FRS_Gate=0;
    GAidaImpDecT_Low = 0;
    GAidaImpDecT_High = 0;
    GAidaImpDecT_HBin = 0;
    GAidaFB_dT = 0;
    GAidaFB_dE = 0;
    GAIDA_DecEFront_Max = 0;
    GAIDA_DecEBack_Max = 0; 
    GAIDA_DecEFront_Min = 0;
    GAIDA_DecEBack_Min = 0; 
    
    GAida_Ge_WRdT_Low=0;
    GAida_Ge_WRdT_High=0;
    
    GAida_Fat_WRdT_High=0;
    GAida_Fat_WRdT_Low=0;
    GFat1_Fat2_Low=0;
    GFat1_Fat2_High=0;
    GPID_Gate_Beta_Gamma_Fatima_LT=0;
    GBDGFat_LT1LowStart=0, GBDGFat_LT1HighStart=0, GBDGFat_LT2LowStart=0, GBDGFat_LT2HighStart=0;
    GBDGFat_LT1LowStop=0, GBDGFat_LT1HighStop=0, GBDGFat_LT2LowStop=0, GBDGFat_LT2HighStop=0;
    
    GFRS_Fat_TLow = 0;
    GFRS_Fat_THigh = 0;
    GFRS_Fattam_TLow = 0;
    GFRS_Fattam_THigh = 0;
    GFRS_bPlast_TLow = 0;
    GFRS_bPlast_THigh = 0;
    
    GPID_Gate_FRS_Fatima_LT=0;
    GFRSFat_LT1LowStart=0, GFRSFat_LT1HighStart=0, GFRSFat_LT2LowStart=0, GFRSFat_LT2HighStart=0;
    GFRSFat_LT1LowStop=0, GFRSFat_LT1HighStop=0, GFRSFat_LT2LowStop=0, GFRSFat_LT2HighStop=0;
    
//     GFRS_AIDA_DSSD1 = false;
//     GFRS_AIDA_DSSD2 = false;
//     GFRS_AIDA_DSSD3 = false;
    
}
//-------------------------------------------------------------------------------------------//
// constructor
// reads correlation parameters from the file Correlations_config.dat
CorrelParameter::CorrelParameter(const Text_t* name)
: TGo4Parameter(name)
{
  ifstream    file;
  
      file.open("Configuration_Files/DESPEC_General_Setup/Correlations_config.dat");
  if (file.fail()) {
        cout << "ERROR: CorrelParameter - Could not open file: Configuration_Files/DESPEC_General_Setup/Correlations_config.dat ! Correlations disabled!!\n"; 
         GSetup_corr_FRS_Ge =false;
         GSetup_corr_FRS_Gamma_Gamma =false;
         GSetup_corr_FRS_Ge_long=false;
         GSetup_corr_FRS_Ge_LongIso_incprmt=false;
         GSetup_corr_FRS_fat=false;
         
         GSetup_corr_FRS_Fatima_LT = false;
         GSetup_corr_FRS_Aida =false;
         GSetup_corr_Beta_Gamma_bPlastSpillOff=false;
         GSetup_corr_Beta_Gamma=false;
         GSetup_corr_Beta_Gamma_Gamma=false;
         GSetup_corr_Beta_Gamma_Fatima=false;
         GSetup_corr_Beta_Gamma_Fatima_LT=false;
         
         GZ1Z2_Gate=0;
    
         GFRS_AIDA_TLow = -1000;
         GFRS_AIDA_THigh = 1000;
         GAIDA_Imp_bPlas_TLow = -10000;
         GAIDA_Imp_bPlas_THigh = 10000;
         GAIDA_bPlas_TLow = -1000;
         GAIDA_bPlas_THigh = 1000;
         GbPlas_Fat_TLow=-1000;
         GbPlas_Fat_THigh=1000;
         GbPlas_Fattam_TLow=-1000;
         GbPlas_Fattam_THigh=1000;
         
         GFRS_Ge_TLow = -1000;
         GFRS_Ge_THigh = 1000;
         
         GbPlast_Ge_TLow = -1000;
         GbPlast_Ge_THigh = 1000;
         GFat_Fattam_TLow = -1000;
         GFat_Fattam_THigh = 1000;
         GFat_Ge_TLow = -1000;
         GFat_Ge_THigh = 1000;
         GFattam_Ge_TLow = -1000;
         GFattam_Ge_THigh = 1000;
         GAIDA_TM_FRS_TLow = -1000;
         GAIDA_TM_FRS_THigh = 1000;
         GAIDA_TM_Ge_TLow = -1000; 
         GAIDA_TM_Ge_THigh = 1000;
         GAIDA_TM_Fat_TLow = -1000;
         GAIDA_TM_Fat_THigh = 1000;
         GAIDA_TM_Fattam_TLow = -1000;
         GAIDA_TM_Fattam_THigh = 1000;
         GAIDA_TM_bPlast_TLow = -1000;
         GAIDA_TM_bPlast_THigh = 1000;
         
         
//          GGe_SCI41_Low=-20000;
//          GGe_SCI41_High=20000;
         GLongIso_PID_Gate=0;
         GGe1_Ge2_Low= -20000;
         GGe1_Ge2_High = 20000;
         GGe1_Ge2_HistoBin =2000;
         GGe1_Ge2_HistoMin =0;
         GGe1_Ge2_HistoMax =2000;
         GFRS_Ge_LongIso_TLow = 0;
         GFRS_Ge_LongIso_THigh = 20000;
         GFRS_Ge_LongIso_HBin = 700;
         GFRS_Ge_LongIso_HLow =0;
         GFRS_Ge_LongIso_HHigh = 700; 
         GFRS_Ge_LongIso_TScale = 1000;
         
         GBDG_FRS_Gate=1;
         GAidaImpDecT_Low = 0;
         GAidaImpDecT_High = 5;
         GAidaImpDecT_HBin = 50;
         GAidaFB_dT = 3000;
         GAidaFB_dE = 200;
         GAIDA_DecEFront_Max = 1500;
         GAIDA_DecEBack_Max = 1500; 
         GAIDA_DecEFront_Min = 0;
         GAIDA_DecEBack_Min = 0; 
         
         GAida_Ge_WRdT_Low=0;
         GAida_Ge_WRdT_High=20000;
         
         GAida_Fat_WRdT_High=0;
         GAida_Fat_WRdT_Low=20000;
         GFat1_Fat2_Low =-20000;
         GFat1_Fat2_High=20000;
         GPID_Gate_Beta_Gamma_Fatima_LT=0;
         GBDGFat_LT1LowStart=0, GBDGFat_LT1HighStart=0, GBDGFat_LT2LowStart=0, GBDGFat_LT2HighStart=0;
         GBDGFat_LT1LowStop=0, GBDGFat_LT1HighStop=0, GBDGFat_LT2LowStop=0, GBDGFat_LT2HighStop=0;
         
         GFRS_Fat_TLow = -1000;
         GFRS_Fat_THigh = 1000;
         GFRS_Fattam_TLow = -1000;
         GFRS_Fattam_THigh = 1000;
         GFRS_bPlast_TLow = -1000;
         GFRS_bPlast_THigh = 1000;
         
         GPID_Gate_FRS_Fatima_LT=0;
         GFRSFat_LT1LowStart=0, GFRSFat_LT1HighStart=0, GFRSFat_LT2LowStart=0, GFRSFat_LT2HighStart=0, GFRSFat_LT3LowStart=0, GFRSFat_LT3HighStart=0;
         GFRSFat_LT1LowStop=0, GFRSFat_LT1HighStop=0, GFRSFat_LT2LowStop=0, GFRSFat_LT2HighStop=0, GFRSFat_LT3LowStop=0, GFRSFat_LT3HighStop=0;

        
         
//          GFRS_AIDA_DSSD1 = true;
//          GFRS_AIDA_DSSD2 = true;
//          GFRS_AIDA_DSSD3 = true;
//          
       
         GbPlast_Egate_low = 0;
         GbPlast_Egate_high = 5000;
  }
  
else {
cout << "CorrelParameter - reading from Configuration_Files/DESPEC_General_Setup/Correlations_config.dat";
        ///Detector system correlation pairs
       if(IsData(file)) file >> GSetup_corr_FRS_Aida;
       if(IsData(file)) file >> GSetup_corr_FRS_Ge >> GSetup_corr_FRS_Gamma_Gamma;
       if(IsData(file)) file >> GSetup_corr_FRS_Ge_long >>GSetup_corr_FRS_Ge_LongIso_incprmt;
       if(IsData(file)) file >> GSetup_corr_FRS_fat;
       if(IsData(file)) file >> GSetup_corr_FRS_Fatima_LT;
       if(IsData(file)) file >> GSetup_corr_Beta_Gamma_bPlastSpillOff;
       if(IsData(file)) file >> GSetup_corr_Beta_Gamma >> GSetup_corr_Beta_Gamma_Gamma >> GSetup_corr_Beta_Gamma_Fatima;
       if(IsData(file)) file >> GSetup_corr_Beta_Gamma_Fatima_LT;
       if(IsData(file)) file >>GZ1Z2_Gate;
    
       //White rabbit read in: 
        ///1. AIDA Implants FRS WR Time Gate
       if(IsData(file)) file >> GFRS_AIDA_TLow >>GFRS_AIDA_THigh;
        ///2. FRS Germanium WR Time Gate
       if(IsData(file)) file >> GFRS_Ge_TLow >>GFRS_Ge_THigh;
        ///3. FRS Fatima VME WR Time Gate
       if(IsData(file)) file >> GFRS_Fat_TLow >>GFRS_Fat_THigh;
       
        ///4. FRS Fatima TAMEX WR Time Gate
       if(IsData(file)) file >> GFRS_Fattam_TLow >>GFRS_Fattam_THigh;
       
        ///5. FRS bPlast WR Time Gate
       if(IsData(file)) file >> GFRS_bPlast_TLow >>GFRS_bPlast_THigh;
       
        ///6. AIDA(Decays)-Ge WR dT 
       if(IsData(file)) file >>GAida_Ge_WRdT_Low >>GAida_Ge_WRdT_High;
     
        ///7. AIDA(Decays)-Fatima WR dT 
       if(IsData(file)) file >>GAida_Fat_WRdT_Low >>GAida_Fat_WRdT_High;
        
       ///8. AIDA Implants bPlas WR Time Gate
       if(IsData(file)) file >> GAIDA_Imp_bPlas_TLow >>GAIDA_Imp_bPlas_THigh;
       
       ///9. AIDA Decays bPlas WR Time Gate
       if(IsData(file)) file >> GAIDA_bPlas_TLow >>GAIDA_bPlas_THigh;
       
       ///10. bPlas FATIMA VME WR Time Gate
       if(IsData(file)) file >> GbPlas_Fat_TLow >>GbPlas_Fat_THigh;
       
        ///11. bPlas FATIMA TAMEX WR Time Gate
       if(IsData(file)) file >> GbPlas_Fattam_TLow >>GbPlas_Fattam_THigh;
       
        ///12. bPlas Germanium WR Time Gate
       if(IsData(file)) file >> GbPlast_Ge_TLow >>GbPlast_Ge_THigh;
       
        ///13. bPlas Germanium WR Time Gate
       if(IsData(file)) file >> GFat_Fattam_TLow >>GFat_Fattam_THigh;
       
        ///14. Fatima VME Germanium WR Time Gate
       if(IsData(file)) file >> GFat_Ge_TLow >>GFat_Ge_THigh;
       
        ///15. Fatima TAMEX Germanium WR Time Gate
       if(IsData(file)) file >> GFattam_Ge_TLow >>GFattam_Ge_THigh;
       
       ///16. AIDA Timemachine - FRS WR Time Gate
       if(IsData(file)) file >> GAIDA_TM_FRS_TLow >>GAIDA_TM_FRS_THigh;
       
        ///17. AIDA Timemachine - Germanium WR Time Gate
       if(IsData(file)) file >> GAIDA_TM_Ge_TLow >>GAIDA_TM_Ge_THigh;
       
        ///18. AIDA Timemachine - FATIMA VME WR Time Gate
       if(IsData(file)) file >> GAIDA_TM_Fat_TLow >>GAIDA_TM_Fat_THigh;
       
       ///19. AIDA Timemachine - FATIMA TAMEX WR Time Gate
       if(IsData(file)) file >> GAIDA_TM_Fattam_TLow >>GAIDA_TM_Fattam_THigh;
       
       ///20. AIDA Timemachine - bPlast WR Time Gate
       if(IsData(file)) file >> GAIDA_TM_bPlast_TLow >>GAIDA_TM_bPlast_THigh;
       
       
       
       
       /// Gamma-Gamma Germanium Time gate 
        if(IsData(file)) file >> GGe1_Ge2_Low >>GGe1_Ge2_High;
       /// Gamma-Gamma Germanium Histogram Size
        if(IsData(file)) file >> GGe1_Ge2_HistoBin >>GGe1_Ge2_HistoMin>>GGe1_Ge2_HistoMax;
       ///FRS Germanium PID Gate Long isomer
       if(IsData(file)) file >> GLongIso_PID_Gate;
      
       ///FRS Germanium WR Time Gate Long isomer
       if(IsData(file)) file >> GFRS_Ge_LongIso_TLow >> GFRS_Ge_LongIso_THigh>> GFRS_Ge_LongIso_HBin>> GFRS_Ge_LongIso_HLow>> GFRS_Ge_LongIso_HHigh>> GFRS_Ge_LongIso_TScale;
      
       
       /// Gamma-Gamma Germanium Time gate 
       if(IsData(file)) file >> GFat1_Fat2_Low >>GFat1_Fat2_High;
        ///Fatma Lifetime PID Gate for prompt
       if(IsData(file)) file >> GPID_Gate_FRS_Fatima_LT;
       ///Fatima Lifetime Energy gates prompt
       if(IsData(file)) file >> GFRSFat_LT1LowStart >>GFRSFat_LT1HighStart >> GFRSFat_LT1LowStop >> GFRSFat_LT1HighStop;
       if(IsData(file)) file >> GFRSFat_LT2LowStart >>GFRSFat_LT2HighStart >> GFRSFat_LT2LowStop >> GFRSFat_LT2HighStop;
       if(IsData(file)) file >> GFRSFat_LT3LowStart >>GFRSFat_LT3HighStart >> GFRSFat_LT3LowStop >> GFRSFat_LT3HighStop;
       
       ///Beta-delayed gammas FRS gate type
        if(IsData(file)) file >>GBDG_FRS_Gate;
       ///AIDA Implant Decay time window
       if(IsData(file)) file >>GAidaImpDecT_Low >>GAidaImpDecT_High>>GAidaImpDecT_HBin;
       
       ///AIDA Front-back conditions
       if(IsData(file)) file >>GAidaFB_dT >>GAidaFB_dE;
       
       ///AIDA Max decay energy conditions
       if(IsData(file)) file >>GAIDA_DecEFront_Min>>GAIDA_DecEFront_Max >>GAIDA_DecEBack_Min>>GAIDA_DecEBack_Max;
       
       /// Plastic energy gates 
       if(IsData(file)) file >> GbPlast_Egate_low>> GbPlast_Egate_high;

       ///Fatma Lifetime PID Gate for BDG
       if(IsData(file)) file >> GPID_Gate_Beta_Gamma_Fatima_LT;
       ///Fatima Lifetime Energy gates (BDG)
       if(IsData(file)) file >> GBDGFat_LT1LowStart >>GBDGFat_LT1HighStart >> GBDGFat_LT1LowStop >> GBDGFat_LT1HighStop;
       if(IsData(file)) file >> GBDGFat_LT2LowStart >>GBDGFat_LT2HighStart >> GBDGFat_LT2LowStop >> GBDGFat_LT2HighStop;
       
       if (file.fail()) cout << " !!!There is a problem in the correlation file !!!";
    
  }
  file.close();
}
//--------------------------------------------------------------------------//
CorrelParameter::~CorrelParameter()
{}
//---------------------------------------------------------------------------//
Int_t CorrelParameter::PrintParameter(Text_t *buf, Int_t)
{
  cout<<" ==================================================================================="<<endl; 
     
  cout<<" ======================== Correlations Setup File ==========================\n";
  cout<<" ======= Configuration_Files/DESPEC_General_Setup/Correlations_config.dat ======="<<endl;
  cout<<" ==================================================================================="<<endl; 
  cout <<"\t\tActive Correlations: " << endl;
  cout<< "\tFRS-AIDA:: " <<  GSetup_corr_FRS_Aida << endl;
  
  cout << "\tFRS-Germanium Short isomers:: " << GSetup_corr_FRS_Ge << ", FRS-Germanium Long isomers: " << GSetup_corr_FRS_Ge_long <<" (prompt gammas for LongCorr ("<<GSetup_corr_FRS_Ge_LongIso_incprmt <<"))"<< " Include gamma-gamma matices? " << GSetup_corr_FRS_Gamma_Gamma <<  endl;
  
  cout << "\tFRS-Fatima Short isomers:: " <<GSetup_corr_FRS_fat <<endl;
  
  cout<<  "\tBeta-delayed Gammas With bPlast Spill Off:: " <<  GSetup_corr_Beta_Gamma_bPlastSpillOff  <<endl;
  
  
  cout<<  "\tBeta-delayed Gammas With AIDA:: " <<  GSetup_corr_Beta_Gamma  <<"  ,Ge Gamma-Gamma: " << GSetup_corr_Beta_Gamma_Gamma << " ,BDG with Fatima: " << GSetup_corr_Beta_Gamma_Fatima << " ,BDG Lifetimes " << GSetup_corr_FRS_Fatima_LT<<endl;

  cout<<"\tZ1 vs Z2 PID gate number for Z1Z2 AND X2/X4 AoQ analysis " <<GZ1Z2_Gate << endl; 
  
  cout<<"==================================================================================="<<endl; 
  cout << "\tAIDA FRS WR Time Gate::  "  << GFRS_AIDA_TLow << " -- " <<  GFRS_AIDA_THigh << " ns " << endl;
  
  cout<<" ==================================================================================="<<endl; 
  cout << "\tGermanium-FRS WR Time Gate:: "<< GFRS_Ge_TLow <<" -- " <<  GFRS_Ge_THigh <<  " ns " <<endl;
  
  
  // cout << "\tGermanium-SCI41 Time Gate:: "<< GGe_SCI41_Low <<" -- " <<  GGe_SCI41_High <<  " ns " <<endl;
  
  cout<<" ==================================================================================="<<endl; 
  cout << "\tGermanium Gamma-Gamma Time gate::  "<< GGe1_Ge2_Low << " -- " <<  GGe1_Ge2_High <<" ns " <<  endl;
   cout << "\tGermanium Gamma-Gamma 2D Histogram Binning::  "<< GGe1_Ge2_HistoBin << " -- " <<  GGe1_Ge2_HistoMin <<" -- " <<GGe1_Ge2_HistoMax<<  endl;
  
  
  cout<<" ==================================================================================="<<endl; 
  cout<<"\t\tFRS Germanium Time Gate Long isomer" <<endl;
  cout << "\tPID Gate Num: " << GLongIso_PID_Gate << ", Min T: " << GFRS_Ge_LongIso_TLow << ", Max T: " <<  GFRS_Ge_LongIso_THigh << ", Long Isomer Scale Time (from ns) "<< GFRS_Ge_LongIso_TScale  <<endl;
  cout<<"\tLong Isomer Histogramming: (Num of Bins, Min, Max) ("<< GFRS_Ge_LongIso_HBin <<", " << GFRS_Ge_LongIso_HLow <<", " << GFRS_Ge_LongIso_HHigh << ")"<<endl;
  
  cout<<" ==================================================================================="<<endl; 
  cout << "\tFRS Fatima VME WR Time Gate" << GFRS_Fat_TLow << " -- " <<  GFRS_Fat_THigh << " --  TAMEX "<<  GFRS_Fattam_TLow <<" -- " << GFRS_Fattam_THigh  <<endl;
  
  cout<<" ==================================================================================="<<endl; 
  cout << "\tFatima Gamma-Gamma Time gate (ns) " << GFat1_Fat2_Low << " -- " <<  GFat1_Fat2_High <<  endl;
  
  cout<<" ==================================================================================="<<endl; 
  cout<<"\t\tFatima Prompt Lifetime Analysis gates " << endl;
  cout<<"\t PID Gate " << GPID_Gate_FRS_Fatima_LT<<endl;
  cout << "\tStart Lifetime1 E gate:: " << GFRSFat_LT1LowStart << "  -- " << GFRSFat_LT1HighStart   << "\tStop Lifetime1: " << GFRSFat_LT1LowStop << "  -- " << GFRSFat_LT1HighStop<<endl;
  
  cout << "\tStart Lifetime2 E Gate:: " << GFRSFat_LT2LowStart << "  -- " << GFRSFat_LT2HighStart   << "\tStop Lifetime2: " << GFRSFat_LT2LowStop << "  -- " << GFRSFat_LT2HighStop<<endl;
  
  cout << "\tStart Lifetime3 E Gate:: " << GFRSFat_LT3LowStart << "  -- " << GFRSFat_LT3HighStart   << "\tStop Lifetime3: " << GFRSFat_LT3LowStop << "  -- " << GFRSFat_LT3HighStop<<endl;
  
  cout<<" ==================================================================================="<<endl; 
  cout<<" ======================= Beta-delayed gamma conditions ============================= \n";

  if(GBDG_FRS_Gate==1)cout<<"\t Beta-delayed-Gammas FRS Gate type:: "<< "Z vs A/Q" << endl;
  if(GBDG_FRS_Gate==2)cout<<"\t Beta-delayed-Gammas FRS Gate type:: "<< "Z1 vs Z2 AND X2 vs A/Q" << endl;
  if(GBDG_FRS_Gate==3)cout<<"\t Beta-delayed-Gammas FRS Gate type:: "<< "Z1 vs Z2 AND X4 vs A/Q" << endl;
  
  cout <<"\tAIDA Implant-Decay Time window:: " << " Min T: " << GAidaImpDecT_Low<<"s" << ",  \t Max T: " <<  GAidaImpDecT_High <<"s"<<" \t dT Histo Binning " << GAidaImpDecT_HBin<<endl;
  
  cout <<"\n\tAIDA(decays) Ge WR Time Gate:: " << GAida_Ge_WRdT_Low << " -- " <<  GAida_Ge_WRdT_High<<endl;
  
  cout <<"\n\tAIDA(decays) Fatima WR Time Gate:: " << GAida_Fat_WRdT_Low << " -- " <<  GAida_Fat_WRdT_High<<endl;
  
  cout <<"\n\tAida Front-Back dT: " << GAidaFB_dT << ", Aida Front-Back dE: " <<  GAidaFB_dE<<endl;
  
  cout <<"\n\tAida Decay Energy Min-Max Front(keV): "<< GAIDA_DecEFront_Min<<" -- " << GAIDA_DecEFront_Max << ", Aida Decay Energy Min-Max Back(keV) " << GAIDA_DecEBack_Min<<" -- " <<  GAIDA_DecEBack_Max<<endl;

  
  cout << "\n\tAIDA Implants bPlas WR Time Gate:: " << GAIDA_Imp_bPlas_TLow << " -- " <<  GAIDA_Imp_bPlas_THigh <<  endl;
    
 
  cout << "\n\tAIDA Decays bPlas WR Time Gate:: " << GAIDA_bPlas_TLow << " -- " <<  GAIDA_bPlas_THigh <<  endl;
  
  cout << "\n\tbPlastic ToT Gate limits::  " << GbPlast_Egate_low << " -- " << GbPlast_Egate_high <<  endl;
  
  
  cout << "\n =============== Fatima Beta-Delayed Gamma Lifetime Analysis gates ================\n";
  cout<<"\t PID Gate:: " << GPID_Gate_Beta_Gamma_Fatima_LT<<endl;
  cout << "\tStart Lifetime1 E gate: " << GBDGFat_LT1LowStart << "  -- " << GBDGFat_LT1HighStart   << "\tStop Lifetime1: " << GBDGFat_LT1LowStop << "  -- " << GBDGFat_LT1HighStop<<endl;
  
  cout << "\tStart Lifetime2 E Gate : " << GBDGFat_LT2LowStart << "  -- " << GBDGFat_LT2HighStart   << "\tStop Lifetime2: " << GBDGFat_LT2LowStop << "  -- " << GBDGFat_LT2HighStop<<endl;
 cout<<" ==================================================================================="<<endl;
//   cout << "//////bPlas Germanium WR Time Gate\n";
//   cout << "////Lower: " << GbPlast_Ge_TLow << "  \t Upper: " <<  GbPlast_Ge_THigh <<  endl;

  
//   cout << "//////Use AIDA DSSD 2D position Gate\n";
//   cout << "////DSSD1: " << GFRS_AIDA_DSSD1 << "  \t DSSD2: " <<  GFRS_AIDA_DSSD2 << "  \t DSSD3: "<<GFRS_AIDA_DSSD3 <<endl;


  return 1;
}
//---------------------------------------------------------------------------//
Bool_t CorrelParameter::UpdateFrom(TGo4Parameter *pp)
{
  if(pp->InheritsFrom("CorrelParameter"))
  {
    CorrelParameter *from = (CorrelParameter *) pp;
      GSetup_corr_FRS_Aida = from->GSetup_corr_FRS_Aida;
      GSetup_corr_FRS_Ge = from->GSetup_corr_FRS_Ge;
      GSetup_corr_FRS_Gamma_Gamma = from->GSetup_corr_FRS_Gamma_Gamma;
      GSetup_corr_FRS_Ge_long = from->GSetup_corr_FRS_Ge_long;
      GSetup_corr_FRS_fat = from->GSetup_corr_FRS_fat;
      GSetup_corr_FRS_Ge_LongIso_incprmt = from->GSetup_corr_FRS_Ge_LongIso_incprmt;

      GSetup_corr_Beta_Gamma_bPlastSpillOff = from->GSetup_corr_Beta_Gamma_bPlastSpillOff;
      GSetup_corr_Beta_Gamma = from->GSetup_corr_Beta_Gamma;
      GSetup_corr_Beta_Gamma_Gamma = from->GSetup_corr_Beta_Gamma_Gamma;
      GSetup_corr_Beta_Gamma_Fatima = from->GSetup_corr_Beta_Gamma_Fatima;
      GSetup_corr_Beta_Gamma_Fatima_LT = from->GSetup_corr_Beta_Gamma_Fatima_LT;
      
      GZ1Z2_Gate= from->GZ1Z2_Gate;
      
      GFRS_AIDA_TLow = from->GFRS_AIDA_TLow;
      GFRS_AIDA_THigh = from->GFRS_AIDA_THigh;
     
      GFRS_Ge_TLow = from->GFRS_Ge_TLow; 
      GFRS_Ge_THigh = from->GFRS_Ge_THigh; 
      
      GbPlast_Ge_TLow = from->GbPlast_Ge_TLow; 
      GbPlast_Ge_THigh = from->GbPlast_Ge_THigh; 
      
      GFat_Fattam_TLow = from->GFat_Fattam_TLow; 
      GFat_Fattam_THigh = from->GFat_Fattam_THigh;
      
      GFat_Ge_TLow = from->GFat_Ge_TLow; 
      GFat_Ge_THigh = from->GFat_Ge_THigh; 
      
      GFattam_Ge_TLow = from->GFattam_Ge_TLow; 
      GFattam_Ge_THigh = from->GFattam_Ge_THigh; 
      
       GAIDA_TM_FRS_TLow = from->GAIDA_TM_FRS_TLow;
         GAIDA_TM_FRS_THigh = from->GAIDA_TM_FRS_THigh;
         GAIDA_TM_Ge_TLow = from->GAIDA_TM_Ge_TLow; 
         GAIDA_TM_Ge_THigh = from->GAIDA_TM_Ge_THigh;
         GAIDA_TM_Fat_TLow = from->GAIDA_TM_Fat_TLow;
         GAIDA_TM_Fat_THigh = from->GAIDA_TM_Fat_THigh;
         GAIDA_TM_Fattam_TLow = from->GAIDA_TM_Fattam_TLow;
         GAIDA_TM_Fattam_THigh = from->GAIDA_TM_Fattam_THigh;
         GAIDA_TM_bPlast_TLow = from->GAIDA_TM_bPlast_TLow;
         GAIDA_TM_bPlast_THigh = from->GAIDA_TM_bPlast_THigh;

      GFRS_Fat_TLow = from->GFRS_Fat_TLow; 
      GFRS_Fat_THigh = from->GFRS_Fat_THigh; 
      GFRS_Fattam_TLow = from->GFRS_Fattam_TLow; 
      GFRS_Fattam_THigh = from->GFRS_Fattam_THigh;
      GFRS_bPlast_TLow = from->GFRS_bPlast_TLow; 
      GFRS_bPlast_THigh = from->GFRS_bPlast_THigh;
      
      GAIDA_Imp_bPlas_TLow = from->GAIDA_Imp_bPlas_TLow;
      GAIDA_Imp_bPlas_THigh = from->GAIDA_Imp_bPlas_THigh;
       
      GAIDA_bPlas_TLow = from->GAIDA_bPlas_TLow;
      GAIDA_bPlas_THigh = from->GAIDA_bPlas_THigh;
      
      GbPlas_Fat_TLow = from ->GbPlas_Fat_TLow;
      GbPlas_Fat_THigh = from ->GbPlas_Fat_THigh;
      
      GbPlas_Fattam_TLow = from ->GbPlas_Fattam_TLow;
      GbPlas_Fattam_THigh = from ->GbPlas_Fattam_THigh;
      
      
      GGe1_Ge2_Low = from->GGe1_Ge2_Low;
      GGe1_Ge2_High = from->GGe1_Ge2_High;
      GGe1_Ge2_HistoBin = from->GGe1_Ge2_HistoBin;
      GGe1_Ge2_HistoMin = from->GGe1_Ge2_HistoMin;
      GGe1_Ge2_HistoMax = from->GGe1_Ge2_HistoMax;
      GLongIso_PID_Gate = from-> GLongIso_PID_Gate;
      GFRS_Ge_LongIso_TLow = from-> GFRS_Ge_LongIso_TLow;
      GFRS_Ge_LongIso_THigh = from-> GFRS_Ge_LongIso_THigh;
      GFRS_Ge_LongIso_HBin = from-> GFRS_Ge_LongIso_HBin;
      GFRS_Ge_LongIso_HLow = from->GFRS_Ge_LongIso_HLow;
      GFRS_Ge_LongIso_HHigh = from->GFRS_Ge_LongIso_HHigh;
      GFRS_Ge_LongIso_TScale = from-> GFRS_Ge_LongIso_TScale;
      
      GBDG_FRS_Gate = from->GBDG_FRS_Gate;
      GAidaImpDecT_Low  = from-> GAidaImpDecT_Low;
      GAidaImpDecT_High = from-> GAidaImpDecT_High;
      GAidaImpDecT_HBin  = from->GAidaImpDecT_HBin;
      
      GAidaFB_dT = from->GAidaFB_dT;
      GAidaFB_dE = from->GAidaFB_dE;
      
      GAIDA_DecEFront_Max = from->GAIDA_DecEFront_Max;
      GAIDA_DecEBack_Max = from->GAIDA_DecEBack_Max;
      GAIDA_DecEFront_Min = from->GAIDA_DecEFront_Min;
      GAIDA_DecEBack_Min = from->GAIDA_DecEBack_Min;

      GFat1_Fat2_Low = from->GFat1_Fat2_Low;
      GFat1_Fat2_High = from->GFat1_Fat2_High;
      GPID_Gate_FRS_Fatima_LT=from->GPID_Gate_FRS_Fatima_LT;
       GFRSFat_LT1LowStart= from-> GFRSFat_LT1LowStart;
       GFRSFat_LT1HighStart= from-> GFRSFat_LT1HighStart;
       GFRSFat_LT2LowStart= from-> GFRSFat_LT2LowStart;
       GFRSFat_LT2HighStart= from->GFRSFat_LT2HighStart;
       GFRSFat_LT1LowStop= from-> GFRSFat_LT1LowStop;
       GFRSFat_LT1HighStop= from-> GFRSFat_LT1HighStop;
       GFRSFat_LT2LowStop= from-> GFRSFat_LT2LowStop;
       GFRSFat_LT2HighStop= from->GFRSFat_LT2HighStop;

     
      
       GPID_Gate_Beta_Gamma_Fatima_LT=from->GPID_Gate_Beta_Gamma_Fatima_LT;
       GBDGFat_LT1LowStart= from-> GBDGFat_LT1LowStart;
       GBDGFat_LT1HighStart= from-> GBDGFat_LT1HighStart;
       GBDGFat_LT2LowStart= from-> GBDGFat_LT2LowStart;
       GBDGFat_LT2HighStart= from->GBDGFat_LT2HighStart;
       GBDGFat_LT1LowStop= from-> GBDGFat_LT1LowStop;
       GBDGFat_LT1HighStop= from-> GBDGFat_LT1HighStop;
       GBDGFat_LT2LowStop= from-> GBDGFat_LT2LowStop;
       GBDGFat_LT2HighStop= from->GBDGFat_LT2HighStop;
//       GFRS_AIDA_DSSD1 = from->GFRS_AIDA_DSSD1;
//       GFRS_AIDA_DSSD2 = from->GFRS_AIDA_DSSD2;
//       GFRS_AIDA_DSSD3 = from->GFRS_AIDA_DSSD3;
//       
    
      GbPlast_Egate_low  = from->GbPlast_Egate_low;
      GbPlast_Egate_high = from->GbPlast_Egate_high;

       cout << "CorrelParameter - Parameter : " << GetName() << " UPDATED\n";
  }
  else {
      cout << "ERROR: CorrelParameter - Wrong parameter object: " << pp->ClassName() << endl;}
        return kTRUE;
  }
  //---------------------------------------------------------------------------//
  int CorrelParameter::IsData(ifstream &f) {
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
  while ((dum == '#') || ((int)dum == 10) || (dum == ' ')); 

  f.unget();   // go one character back
  retval = 1;
  return retval;
}
ClassImp(CorrelParameter)
