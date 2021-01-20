#ifndef TFRSPARAMETER_H
#define TFRSPARAMETER_H

#include "Go4StatusBase/TGo4Parameter.h"
#include "TMap.h"
#include <map>

class TFRSParameter : public TGo4Parameter {
public:
  TFRSParameter();
  TFRSParameter(const char* name);
  virtual ~TFRSParameter();
  virtual void Print(Option_t* t="") const;
  virtual Bool_t UpdateFrom(TGo4Parameter *);

  Bool_t        fill_raw_histos; // fill raw histograms in unpack step

  // common FRS part


  /*-----------------------*/
  /*    distances  S2      */
  /*-----------------------*/
  Float_t       dist_focS2;      /* All distances from    */
  Float_t       dist_MW21;       /*       TS3QT33         */
  Float_t       dist_MW22;       /*                       */
  Float_t       dist_SC21;       /*        in mm          */
  Float_t       dist_SC22;       /*        in mm          */
  Float_t       dist_TPC21;
  Float_t       dist_TPC22;
  Float_t       dist_TPC23;
  Float_t       dist_TPC24;
  Float_t       dist_S2target;

  /*-----------------------*/
  /*    distanes  S4      */
  /*-----------------------*/
  Float_t       dist_focS4;      /* All distances from    */
  Float_t       dist_SC41;       /*        in mm          */
  Float_t       dist_SC42;       /*        in mm          */
  Float_t       dist_SC43;       /*        in mm          */
  Float_t       dist_TPC41;
  Float_t       dist_TPC42;
  Float_t       dist_MUSIC41;     /*  MUSIC1               */
  Float_t       dist_MUSIC42;     /*  MUSIC2               */
  Float_t       dist_MUSIC43;     /*  MUSIC3               */
  Float_t       dist_S4target;


  /*-----------------------*/
  /*    distances not used */
  /*-----------------------*/
  Float_t       dist_focS8;      /* All distances from    */
  Float_t       dist_MW81;       /*       TS????          */
  Float_t       dist_MW82;       /*                       */
  Float_t       dist_SC81;       /*        in mm          */


  Float_t       dispersion[7];   /* d* Disp. S0-S2,S2-S4  */
  Float_t       magnification[7];
  Float_t       bfield[7];       /* D1/D2 D3/D4 Feld      */
  Float_t       rho0[7];         /* S2/4 Sollbahnradius s */
  Float_t       primary_z;       /* Z of primary beam     */

  ClassDef(TFRSParameter,1)
};

class Map1 : public TObject
{
public :
  std::map<int,int> map;
  Map1():TObject() { }
  Map1(const char* name):TObject() { }
  ClassDef(Map1,1);
};


// *************************************************************************

class TMWParameter : public TGo4Parameter {
public:
  TMWParameter();
  TMWParameter(const char* name);
  virtual ~TMWParameter();
  virtual void Print(Option_t* t="") const;
  virtual Bool_t UpdateFrom(TGo4Parameter*);

  Float_t       x_factor[13];    /*  MWPC calibration        */
  Float_t       x_offset[13];    /*  mm                        */
  Float_t       y_factor[13];    /*                          */
  Float_t       y_offset[13];    /*  mm                        */

  Float_t       gain_tdc[5][13]; /* 14.09.05 CN+AM  TDC calibration ns/ch */
  ClassDef(TMWParameter,1)
};

// *************************************************************************

class TTPCParameter : public TGo4Parameter {
public:
  TTPCParameter();
  TTPCParameter(const Text_t* name);
  virtual ~TTPCParameter();
  virtual void Print(Option_t* t="") const;
  virtual Bool_t UpdateFrom(TGo4Parameter*);

  Float_t       x_factor[7][2];     /* [mm/ch]                  */
  Float_t       x_offset[7][2];     /*                          */
  Float_t       y_factor[7][4];     /* [mm/ch]                  */
  Float_t       y_offset[7][4];     /*                          */

  Float_t       a_offset[7][4];
  Float_t       tdc1_factor[32];
  Float_t       tdc2_factor[32];
  //  Float_t       tdc_reference[7];
  Int_t         id_tpc_timeref[7];
  Float_t       timeref_calibrun[7];

  Float_t lim_csum1[7][2];
  Float_t lim_csum2[7][2];
  Float_t lim_csum3[7][2];
  Float_t lim_csum4[7][2];

  ClassDef(TTPCParameter,1)
};
// *************************************************************************





class TMUSICParameter : public TGo4Parameter {
public:
  TMUSICParameter();
  TMUSICParameter(const char* name);
  virtual ~TMUSICParameter();
  virtual void Print(Option_t* t="") const;
  virtual Bool_t UpdateFrom(TGo4Parameter*);

  Int_t         e1_off[8];       /* ADC offsets              */
  Float_t       e1_gain[8];      /* ADC gains                */
  Int_t         e2_off[8];       /* ADC offsets              */
  Float_t       e2_gain[8];      /* ADC gains                */
  Int_t         e3_off[8];       /* ADC offsets              */
  Float_t       e3_gain[8];      /* ADC gains                */
  Bool_t        b_selfcorr1;     /* 1 => Music1 x correction */
  Float_t       pos_a1[7];       /* pos. corr. de(i) ->  MUSIC41 */
  Float_t       pos_a2[7];       /* pos. corr. de(i) ->  MUSIC42 */
  Float_t       pos_a3[7];       /* pos. corr. de(i) ->  MUSIC43 */
  Float_t       dist_MUSICa1;    /*  MUSIC(window-anode1) */
  Float_t       dist_MUSICa2;    /*  MUSIC(window-anode2) */
  Float_t       dist_MUSICa3;    /*  MUSIC(window-anode3) */
  Float_t       dist_MUSICa4;    /*  MUSIC(window-anode4) */


  // MUSIC histogram setup
  int max_adc_music1;
  int max_adc_music2;
  int max_adc_music3;
  int max_tdc_music1;
  int max_tdc_music2;
  int max_tdc_music3;

  ClassDef(TMUSICParameter,1)
};

// -------------------------------------------------------------------------

class TSCIParameter : public TGo4Parameter {
public:
  TSCIParameter();
  TSCIParameter(const char* name);
  virtual ~TSCIParameter();
  virtual void Print(Option_t* t="") const;
  virtual Bool_t UpdateFrom(TGo4Parameter*);

  Float_t       le_a[2][12];     /* dE-left   shift,gain     */
  Float_t       re_a[2][12];     /* dE-right  shift,gain     */
  Float_t       le_veto_a[2][3]; /* veto dE-left  shift,gain */
  Float_t       re_veto_a[2][3]; /* veto dE-right shift,gain */

  Float_t       tac_factor[16];   /* TAC factor               */
  Float_t       tac_off[16];      /* TAC offset               */
  Float_t       x_a[7][12];      /* pos. corr. de(i) ->  (1) */
  Float_t       y5_a[7];         /* pos. corr. de(i) ->  (1) */

  Float_t       tof_bll2;        /* [ps/channel]             */
  Float_t       tof_brr2;        /* [ps/channel]             */
  Float_t       tof_a2;          /* shift [channels]         */
  Float_t       tof_bll3;        /* [ps/channel]             */
  Float_t       tof_brr3;        /* [ps/channel]             */
  Float_t       tof_a3;          /* shift [channels]         */
  Float_t       tof_bll4;        /* [ps/channel]             */
  Float_t       tof_brr4;        /* [ps/channel]             */
  Float_t       tof_a4;          /* shift [channels]         */
  Float_t       tof_bll5;        /* [ps/channel]             */
  Float_t       tof_brr5;        /* [ps/channel]             */
  Float_t       tof_a5;          /* shift [channels]         */
  Float_t       tof_bll6;        /* [ps/channel]             */
  Float_t       tof_brr6;        /* [ps/channel]             */
  Float_t       tof_a6;          /* shift [channels]         */


  //-----for multihit TDC analysis------
  float mhtdc_factor_ch_to_ns;
  float mhtdc_offset_21l_21r;  float mhtdc_factor_21l_21r ;
  float mhtdc_offset_41l_41r;  float mhtdc_factor_41l_41r ;
  float mhtdc_offset_42l_42r;  float mhtdc_factor_42l_42r ;
  float mhtdc_offset_43l_43r;  float mhtdc_factor_43l_43r ;
  float mhtdc_offset_31l_31r;  float mhtdc_factor_31l_31r ;
  float mhtdc_offset_81l_81r;  float mhtdc_factor_81l_81r ;
  float mhtdc_offset_22l_22r;  float mhtdc_factor_22l_22r;
  float mhtdc_offset_41_21;
  float mhtdc_offset_42_21;
  float mhtdc_offset_43_21;
  float mhtdc_offset_31_21;
  float mhtdc_offset_81_21;
  float mhtdc_offset_41_22;
  float mhtdc_offset_81_22;

  ClassDef(TSCIParameter,1)
};

// -------------------------------------------------------------------------

class TIDParameter : public TGo4Parameter {
public:
  TIDParameter();
  TIDParameter(const char* name);
  virtual ~TIDParameter();
  virtual void Print(Option_t* t="") const;
  virtual Bool_t UpdateFrom(TGo4Parameter*);

  Int_t         x_s2_select; //1=tpc,2=sc21,3=sc22
  Int_t         tof_s4_select; //1=sc21-41, 2=sc21-42, 3=sc22-41
  Int_t         tof_s8_select; //1=sc21-81, 2=sc22-81
  
  Float_t       id_tofoff2;      /* Tof offset S2-S4 [ps]    */
  Float_t       id_tofoff3;      /* Tof offset S2-S4 [ps]    */ //2nd tof from S2 - S4
  Float_t       id_tofoff4;      /* Tof offset S2-S8 [ps]    */
  Float_t       id_tofoff5;      /* Tof offset S2-S4 [ps]    */ //Plastic22
  Float_t       id_tofoff6;      /* Tof offset S2-S8 [ps]    */ //Plastic22
  Float_t       id_path2;        /* Flight path/c S2-S4 [ps] */
  Float_t       id_path3;        /* Flight path/c S2-S4 [ps] */ //2nd tof from S2 - S4
  Float_t       id_path4;        /* Flight path/c S2-S8 [ps] */
  Float_t       id_path5;        /* Flight path/c S2-S4 [ps] */ //Plastic22
  Float_t       id_path6;        /* Flight path/c S2-S8 [ps] */ //Plastic22
  Float_t       id_tofcorr2;     /* Tof correction for x4    */
  Float_t       id_tofcorr3;     /* Tof correction for x4    */ //2nd tof from S2 - S4
  Float_t       id_tofcorr4;     /* Tof correction for x8    */
  Float_t       id_tofcorr5;     /* Tof correction for x4    */ //Plastic 22
  Float_t       id_tofcorr6;     /* Tof correction for x8    */ //Plastic 22

  Float_t       offset_z;
  Float_t       offset_z2;
  Float_t       offset_z3;
  Float_t       offset_z_sc81;
  Float_t       offset_z_s2tpc;

  Float_t       a2AoQCorr;  /* Correction of AoQ based on S2 angle in x */
  Float_t       a4AoQCorr;  /* Correction of AoQ based on S4 angle in x */

  Float_t       vel_a[4];
  Float_t       vel_a2[4];
  Float_t       vel_a3[4];
  Float_t       vel_a_sc81[4];
  Float_t       vel_a_s2tpc[4];

  //
  Float_t       pos_offset_sc81x;

  //id analysis with multihit tdc
  Int_t         mhtdc_s2pos_option;
  Float_t       mhtdc_length_s2s8;
  Float_t       mhtdc_vel_a_sc81[4];
  Float_t       mhtdc_vel_a_s2tpc[4];
  Float_t       mhtdc_offset_z_s2tpc;
  Float_t       mhtdc_offset_z_sc81;
  Float_t       mhtdc_length_s2s4;
  Float_t       mhtdc_vel_a_music41[4];
  Float_t       mhtdc_vel_a_music42[4];
  Float_t       mhtdc_offset_z_music41;
  Float_t       mhtdc_offset_z_music42;

  //---------Setup for histogram ranges------------
  float min_aoq_plot;
  float max_aoq_plot;
  float min_z_plot;
  float max_z_plot;

  Int_t   ID_Z_AoverQ_num[5];
  Float_t ID_Z_AoverQ [5][5][2];

  Int_t   ID_x2AoverQ_num[6];
  Float_t ID_x2AoverQ [6][5][2];

  Int_t   ID_x4AoverQ_num[6];
  Float_t ID_x4AoverQ [6][5][2];

  ClassDef(TIDParameter,1)
};


// SI parameters
class TSIParameter : public TGo4Parameter {
public:
  TSIParameter();
  TSIParameter(const char* name);
  virtual ~TSIParameter();
  virtual void Print(Option_t* t="") const;
  virtual Bool_t UpdateFrom(TGo4Parameter*);

  Float_t si_factor1;
  Float_t si_factor2;
  Float_t si_factor3;
  Float_t si_factor4;
  Float_t si_factor5;

  Float_t si_offset1;
  Float_t si_offset2;
  Float_t si_offset3;
  Float_t si_offset4;
  Float_t si_offset5;

  //Float_t dssd_offset[32];
  //Float_t dssd_factor[32];

  Float_t dssd_offset_det1[32];
  Float_t dssd_factor_det1[32];

  Float_t dssd_offset_det2[32];
  Float_t dssd_factor_det2[32];

  Float_t dssd_offset_det3[32];
  Float_t dssd_factor_det3[32];

  Float_t dssd_offset_det4[32];
  Float_t dssd_factor_det4[32];

  Float_t dssd_offset_det5[32];
  Float_t dssd_factor_det5[32];

  Float_t dssd_offset_det6[32];
  Float_t dssd_factor_det6[32];



  ClassDef(TSIParameter,1)
};

// MRTOF parameters
class TMRTOFMSParameter : public TGo4Parameter {
public:
  TMRTOFMSParameter();
  TMRTOFMSParameter(const char* name);
  virtual ~TMRTOFMSParameter();
  virtual void Print(Option_t* t="") const;
  virtual Bool_t UpdateFrom(TGo4Parameter*);

  Float_t MRTOFMS_a;
  Float_t MRTOFMS_b;
  Float_t MRTOFMS_t0;
  Float_t MRTOFMS_tFRS;

  ClassDef(TMRTOFMSParameter,1)
};

#endif //TFRSPARAMETER_H
