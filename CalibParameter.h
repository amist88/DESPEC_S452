#ifndef CALIBPAR_H
#define CALIBPAR_H

#include "Go4StatusBase/TGo4Parameter.h"
#include <iomanip>
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"
class CalibParameter : public TGo4Parameter {

public:
          CalibParameter();
          CalibParameter(const Text_t *name);
  virtual ~CalibParameter();
  Int_t   PrintParameter(Text_t *buf, Int_t);
  Bool_t  UpdateFrom(TGo4Parameter *);
  int      IsData(std::ifstream &f);

 Double_t Abplas_TAMEX[48], Bbplas_TAMEX[48];
 Int_t DetIDPlas_TAMEX;
 
 Int_t TDCfatID;
 
 Double_t TFatTDC_Chref_dT[FAT_MAX_VME_CHANNELS];
 //Double_t Afat[FAT_MAX_VME_CHANNELS], Bfat[FAT_MAX_VME_CHANNELS], Cfat[FAT_MAX_VME_CHANNELS], Dfat[FAT_MAX_VME_CHANNELS], Extra1fat[FAT_MAX_VME_CHANNELS], , TFatTDC_SC41dT[FAT_MAX_VME_CHANNELS];
 
 //Int_t DetIDFAT, 
 
 Double_t Afat_TAMEX[FATIMA_TAMEX_CHANNELS], Bfat_TAMEX[FATIMA_TAMEX_CHANNELS], Cfat_TAMEX[FATIMA_TAMEX_CHANNELS], Dfat_TAMEX[FATIMA_TAMEX_CHANNELS];
 
 Int_t DetIDFAT_TAMEX;

 
 Int_t DetIDGe;
 Double_t AGe[Germanium_MAX_CHANNELS], BGe[Germanium_MAX_CHANNELS], CGe[Germanium_MAX_CHANNELS];
 
 Int_t DetIDGe_cfdalign,DetIDGe_talign;
 Double_t Ge_cfd_align_par[Germanium_MAX_CHANNELS], Ge_T_align_par[Germanium_MAX_CHANNELS];
//  Double_t Aff[60], Bff[60];
//  Double_t Ab[32], Bb[32];
//  Double_t Ag[4], Bg[4];

ClassDef(CalibParameter,5)
};

#endif
