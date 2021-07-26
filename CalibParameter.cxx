#include "CalibParameter.h"
#include <iostream>

using namespace std;
 
CalibParameter::CalibParameter()
: TGo4Parameter("AnaOnlineCalPar")
{ Int_t i;
    
     for(i=0; i<48; i++){
        
       DetIDPlas_TAMEX = 0; 
       Abplas_TAMEX[i] = 0;
       Bbplas_TAMEX[i] = 0;
       
}
     //FATIMA VME + TAMEX
//        DetIDFAT = 0; 
           //
     for (i = 0; i < FAT_MAX_VME_CHANNELS; i++){
            TFatTDC_Chref_dT[i] = 0;
            }
//        Extra1fat[i] = 0;   
//        Afat[i] = 0;
//        Bfat[i] = 0;
//        Cfat[i] = 0;
//        Dfat[i] = 0;
//     }
    TDCfatID = 0;
    DetIDFAT_TAMEX = 0; 
    for (i = 0; i < FATIMA_TAMEX_CHANNELS; i++){
       
      
       Afat_TAMEX[i] = 0;
       Bfat_TAMEX[i] = 0;
       Cfat_TAMEX[i] = 0;
       Dfat_TAMEX[i] = 0;
       
       
      // TFatTDC_SC41dT[i] = 0;
    
    }
       
       
//        TFatTDC_Chref_dT[i] = 0;
//        TFatTDC_SC41dT[i] = 0;
//        TDCfatID = 0;
        
     //Germanium
      DetIDGe = 0;
      DetIDGe_cfdalign=0;
   
     for (i = 0; i < Germanium_MAX_CHANNELS; i++){
      
       AGe[i] = 0;
       BGe[i] = 0;
       CGe[i] = 0;
       Ge_T_align_par[i]=0;
       Ge_cfd_align_par[i]=0;
        } 
    } 

  //----------------------------------------------
CalibParameter::CalibParameter(const Text_t *name)
: TGo4Parameter(name)
{
  Int_t i;
  ifstream    file;
  
    
  
    //-----------------------------------------------------------------------------------------------------//
   file.open("Configuration_Files/bPlast/Plastic_TAMEX_Energy_Calibration.txt");
  if (file.fail()) {
    cout << "ERROR:  Could not open file: Plastic_TAMEX_Energy_Calibration.txt ! (params set to 1 and 0)\n";
    for (i = 0; i < 48; i++){
       DetIDPlas_TAMEX = i; 
       Abplas_TAMEX[i] = 1;
       Bbplas_TAMEX[i] = 0;
    }
  }
  
   else {
    cout << "CalibParameter - reading calibration from: Plastic_TAMEX_Energy_Calibration.txt\n";
    for (i = 0; i < 48; i++){
      if(IsData(file)) file >> DetIDPlas_TAMEX  >> Abplas_TAMEX[i] >> Bbplas_TAMEX[i] ;
       if (file.fail()) cout << "ERROR reading Plastic_TAMEX_Energy_Calibration.txt\n ";
    }
  }
  file.close();
  
  //-----------------------------------------------------------------------------------------------------//
//    file.open("Configuration_Files/FATIMA/FATIMA_Energy_Calibration.txt");
//   if (file.fail()) {
//     cout << "ERROR:  Could not open file: FATIMA_Energy_Calibration.txt ! (params set to 0 1 and 0)\n";
//     for (i = 0; i < FAT_MAX_VME_CHANNELS; i++){
//        DetIDFAT = i; 
//        Extra1fat[i] = 0;    
//        Afat[i] = 0;
//        Bfat[i] = 0;
//        Cfat[i] = 1;
//        Dfat[i] = 0;
//     }
//   }
//   
//    else {
//     cout << "CalibParameter - reading calibration from: FATIMA_Energy_Calibration.txt\n";
//     for (i = 0; i < 50; i++){
//       if(IsData(file)) file >> DetIDFAT>> Extra1fat[i]   >> Afat[i] >> Bfat[i] >>Cfat[i] >>Dfat[i] ;
//        if (file.fail()) cout << "ERROR reading FATIMA_Energy_Calibration.txt\n ";
//     }
//   }
//   file.close();

   //-----------------------------------------------------------------------------------------------------//
   file.open("Configuration_Files/FATIMA/FATIMA_TAMEX_Energy_Slow_Calibration.txt");
  if (file.fail()) {
    cout << "ERROR:  Could not open file: FATIMA_TAMEX_Energy_Slow_Calibration.txt ! (params set to 0 1 and 0)\n";
    for (i = 0; i < FATIMA_TAMEX_CHANNELS; i++){
       DetIDFAT_TAMEX = i; 
    
       Afat_TAMEX[i] = 0;
       Bfat_TAMEX[i] = 0;
       Cfat_TAMEX[i] = 1;
       Dfat_TAMEX[i] = 0;
    }
  }
  
   else {
    cout << "CalibParameter - reading calibration from: FATIMA_TAMEX_Energy_Slow_Calibration.txt\n";
    for (i = 0; i < FATIMA_TAMEX_CHANNELS; i++){
      if(IsData(file)) file >> DetIDFAT_TAMEX  >> Afat_TAMEX[i] >> Bfat_TAMEX[i] >>Cfat_TAMEX[i] >>Dfat_TAMEX[i] ;
       if (file.fail()) cout << "ERROR reading FATIMA_TAMEX_Energy_Slow_Calibration.txt\n ";
    }
  }
  file.close();
  //------------------------------------------------------------------------------//
  file.open("Configuration_Files/FATIMA/FATIMA_Ref_Time_Correction.txt");
  if (file.fail()) {
    cout << "ERROR:  Could not open file: FATIMA_Ref_Time_Correction.txt ! (param set 0)\n";
    for (i = 0; i < FAT_MAX_VME_CHANNELS; i++){
          cout<<  " TDCfatID " << TDCfatID <<endl;
       TDCfatID = i;
       TFatTDC_Chref_dT[i] = 0;
       //TFatTDC_SC41dT[i] = 0;
    }
  }
  
   else {
    cout << "CalibParameter - reading calibration from: FATIMA_Ref_Time_Correction.txt\n";
    for (i = 0; i < FAT_MAX_VME_CHANNELS; i++){
      if(IsData(file)) file >> TDCfatID >> TFatTDC_Chref_dT[i];
    
       if (file.fail()) cout << "ERROR reading FATIMA_Ref_Time_Correction.txt\n";
    }
  }
  file.close();
  
  //------------------------------------------------------------------------------//
  file.open("Configuration_Files/Germanium/Germanium_Energy_Calibration.txt");
  if (file.fail()) {
    cout << "ERROR:  Could not open file: Germanium_Energy_Calibration.txt ! (params set to 1 and 0)\n";
    for (i = 0; i < Germanium_MAX_CHANNELS; i++){
       DetIDGe=i;
       AGe[i] = 0.;
       BGe[i] = 1.;
       CGe[i] = 0.;
      
    }
  }
  
   else {
    cout << " CalibParameter - reading calibration from: Germanium_Energy_Calibration.txt\n";
    for (i = 0; i < Germanium_MAX_CHANNELS; i++){
      if(IsData(file)) file >> DetIDGe >>AGe[i] >> BGe[i] >> CGe[i] ;
    
       if (file.fail()) cout << "ERROR reading Germanium_Energy_Calibration.txt\n";
    }
  }
  file.close();
   //------------------------------------------------------------------------------//
   file.open("Configuration_Files/Germanium/Germanium_CFD_TimeAlignment.txt");
  if (file.fail()) {
    cout << "ERROR:  Could not open file: Germanium_CFD_TimeAlignment.txt ! (params set to 1 and 0)\n";
    for (i = 0; i < Germanium_MAX_CHANNELS; i++){
 
       DetIDGe_cfdalign=i;
       Ge_cfd_align_par[i]=0;
    }
  }
  
   else {
    cout << " CalibParameter - reading calibration from: Germanium_CFD_TimeAlignment.txt\n";
    for (i = 0; i < Germanium_MAX_CHANNELS; i++){
      if(IsData(file)) file >> DetIDGe_cfdalign >>Ge_cfd_align_par[i] ;

       if (file.fail()) cout << "ERROR reading Germanium_CFD_TimeAlignment.txt\n";
    }
  }
  file.close();
  
   //------------------------------------------------------------------------------//
   file.open("Configuration_Files/Germanium/Germanium_TimeAlignment.txt");
  if (file.fail()) {
    cout << "ERROR:  Could not open file: Germanium_TimeAlignment.txt ! (params set to 1 and 0)\n";
    for (i = 0; i < Germanium_MAX_CHANNELS; i++){
 
       DetIDGe_talign=i;
       Ge_T_align_par[i]=0;
    }
  }
  
   else {
    cout << " CalibParameter - reading calibration from: Germanium_TimeAlignment.txt\n";
    for (i = 0; i < Germanium_MAX_CHANNELS; i++){
      if(IsData(file)) file >> DetIDGe_talign >>Ge_T_align_par[i] ;

       if (file.fail()) cout << "ERROR reading Germanium_CFD_TimeAlignment.txt\n";
    }
  }
  file.close();
}
//------------------------------------------------------------------------------//

CalibParameter::~CalibParameter()
{}
//------------------------------------------------------------------------------

Int_t CalibParameter::PrintParameter(Text_t *buf, Int_t)
{
  //Int_t  i;
  //cout << "\n AnaOnline Calibration Parameter: " << GetName() << endl;

  //Plastic main
//   cout << "Plastic Energy calibration:\n";
//   for (i = 0; i < 32; i++){
//       cout << "strip " << i << "  \t A = " << AplasQDC[i] << "\t B = " << BplasQDC[i] << endl;
//     }
//     
//     cout << "Plastic Timing calibration:\n";
//   for (i = 0; i < 32; i++){
//       cout << "strip " << i << "  \t A = " << AplasTDC_Chref_dT[i] << endl;
//     }
//     
//     //FATIMA
//     cout << "FATIMA Energy calibration:\n";
//   for (i = 0; i < 50; i++){
//       cout << "detector " << i << "  \t A = " << Afat[i] << "\t B = " << Bfat[i] << "\t C = " << Cfat[i]<< "\t D = " << Dfat[i]<<  endl;
//     }
// //     
// //       cout << "FATIMA RefPlas-Fat calibration:\n";
// //   for (i = 0; i < 50; i++){
// //       cout << "strip " << i << "  \t A = " << Tfat[i] << endl;
//   
//         cout << "Germanium Energy calibration:\n";
//         for (i = 0; i < 36; i++){
//         cout << "strip " << i << "  \t A = " << AGe[i] << "  \t B = " << BGe[i] << "  \t C = " << CGe[i]<< endl;
//     }
    return 1;
}

//------------------------------------------------------------------------------

Bool_t CalibParameter::UpdateFrom(TGo4Parameter *pp)
{
  if(pp->InheritsFrom("CalibParameter"))
  {
    Int_t i;
    CalibParameter *from = (CalibParameter *) pp;
    
   
      for (i = 0; i < 48; i++){
       DetIDPlas_TAMEX = from->DetIDPlas_TAMEX; 
       Abplas_TAMEX[i] = from->Abplas_TAMEX[i];
       Bbplas_TAMEX[i] = from->Bbplas_TAMEX[i];
       
      }
     
   
//        DetIDFAT = from->DetIDFAT; 
//       for (i = 0; i < FAT_MAX_VME_CHANNELS; i++){
//        Extra1fat[i] = from->Extra1fat[i];
//        
//        Afat[i] = from->Afat[i];
//        Bfat[i] = from->Bfat[i];
//        Cfat[i] = from->Cfat[i];
//        Dfat[i] = from->Dfat[i];
//       }
      
       DetIDFAT_TAMEX = from->DetIDFAT_TAMEX; 
      
       for (i = 0; i < FATIMA_TAMEX_CHANNELS; i++){
      
       
       Afat_TAMEX[i] = from->Afat_TAMEX[i];
       Bfat_TAMEX[i] = from->Bfat_TAMEX[i];
       Cfat_TAMEX[i] = from->Cfat_TAMEX[i];
       Dfat_TAMEX[i] = from->Dfat_TAMEX[i];
       }
       
       TDCfatID = from-> TDCfatID;
    for (i = 0; i < FAT_MAX_VME_CHANNELS; i++)TFatTDC_Chref_dT[i]  = from->TFatTDC_Chref_dT[i];
 
      // TFatTDC_SC41dT[i]  = from->TFatTDC_SC41dT[i];
       
      
      cout << "CalibParameter - Parameter : " << GetName() << " UPDATED\n";
    
  
        DetIDGe_cfdalign= from->DetIDGe_cfdalign;
        DetIDGe = from->DetIDGe;
    for (i = 0; i < Germanium_MAX_CHANNELS; i++){
       
       AGe[i]  = from->AGe[i];
       BGe[i]  = from->BGe[i];
       CGe[i]  = from->CGe[i];
       
       Ge_cfd_align_par[i] = from->Ge_cfd_align_par[i];
       
       cout << "CalibParameter - Parameter : " << GetName() << " UPDATED\n";
     }
  }
     
      else {
      cout << "ERROR: CalibParameter - Wrong parameter object: " << pp->ClassName() << endl;}
 
        return kTRUE;
         
}
    int CalibParameter::IsData(ifstream &f) {
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

ClassImp(CalibParameter)
