///Should be set for each experiment depending upon configuration
#ifndef DESPEC_SETUP_FILE
#define DESPEC_SETUP_FILE

///Note that channels start from 0

#define WHITE_RABBIT_ENABLED 1

///Use FRS MHTDC for Analysis (1) or NIM TAC (0)
#define MHTDC_OR_TAC 0
///Use FRS angle corrected A/Q for Analysis (1) or none-corrected (0)
#define FRS_CORR 1
///For Z1 Z2 AND X A/Q Gate: Use FRS X2 vs A/Q (1) OR X4 vs A/Q (0) 
#define X2_or_X4 1
//Set the white rabbit offset time in minutes for the FRS (used only for gain matching of Z and A/Q over time): Defined in the EventUnpackProc and used in FRS_Detector_System
#define FRS_WR_GAINOFFSET 26900000

#define FRS_MIN_AoQ 2.0
#define FRS_MAX_AoQ 3.0
#define FRS_MIN_Z 30
#define FRS_MAX_Z 90
///Use High charge state gate for Correlations
#define USE_dEdeg_Z1_GATE 0

///Define number of FRS gates and Polygon Points
#define MAX_FRS_GATE 8
#define MAX_FRS_PolyPoints 8

#define FINGER_TAMEX_MODULES 4
#define FINGER_TAMEX_HITS    512

///FATIMA VME 
#define FAT_TDC_NUMBER 2
#define SCALER_MODULE_ON 1
#define FAT_MAX_VME_CHANNELS 51 
#define FAT_TDC_REF_CHANNEL 1
#define FAT_VME_MAX_MULTI 51
#define SC41L_FatVME  36
#define SC41R_FatVME  37
#define SC41L_FatVME_Digi  38
#define SC41R_FatVME_Digi  39
#define FatVME_TimeMachineCh1 40
#define FatVME_TimeMachineCh2 41
#define FatVME_bPlast_UP 42
#define FatVME_bPlast_DOWN 43
#define FatVME_bPlast_MASTER 44
#define FatVME_bPlast_StartCh 45
#define FatVME_bPlast_StopCh 50
#define FatGM_Offset 26916384
///FATIMA TAMEX
#define FATIMA_TAMEX_MODULES 4
#define FATIMA_TAMEX_HITS 50
#define FATIMA_TAMEX_CHANNELS 65
#define FATIMA_TAMEX_SC41L  49
#define FATIMA_TAMEX_SC41R  50 
#define FATIMA_TAMEX_SC41L_Digi  51
#define FATIMA_TAMEX_SC41R_Digi  52
#define FatTAMEX_TimeMachineCh1 53
#define FatTAMEX_TimeMachineCh2 54

///bPLASTIC 
///1:twin peaks,  0 for pQDC 
#define bPLASTIC_TWINPEAKS 0
#define bPLASTIC_TAMEX_MODULES 3
#define bPLASTIC_TAMEX_HITS 20
#define bPLASTIC_TAMEX_CHANNELS 16
///bPlastic number of channels per detector 
#define bPLASTIC_CHAN_PER_DET 16
///bPlastic Upstream Detector
#define bPLASTIC_UPSTREAM_DET 2
///bPlastic Downstream Detector
#define bPLASTIC_DOWNSTREAM_DET 1
///bPlast Additional signals Module Num
#define bPLASTIC_ADDITIONAL_CH_MOD 3
///bPlast Additional signals Channel Num
#define bPLASTIC_FATTAMEX 5
#define bPLASTIC_FATVME 6
#define SC41L_bPLASTIC 3
#define SC41R_bPLASTIC 4
#define bPLASTIC_OR_UP_DOWN 13
#define bPLASTIC_UP_COIN 12
#define bPLASTIC_DOWN_COIN 11
///bPlast Time Machine Channels
#define bPlastTimeMachineCh1 7
#define bPlastTimeMachineCh2 8
///bPlastic refence channels
#define bPlastRefCh_Det1 0
#define bPlastRefCh_Det2 0
#define bPlastRefCh_Det3 0

///FIBRE
#define FIBRE_BOARD 3

///Germanium (including additonal channel detectors (e.g.SC41 det)
#define Germanium_MAX_DETS 4
#define Germanium_CRYSTALS 7
#define Germanium_MAX_HITS (Germanium_MAX_DETS * Germanium_CRYSTALS)
///Important for FEBEX
#define Germanium_FEBEX_MODULES 2
#define Germanium_MAX_CHANNELS 49
///Define here where SC41 is plugged into FEBEX ("Detector" and "crystal" for mapping purposes) Use the germanium allocation file for mapping of this
#define Germanium_SC41_Det 2
#define Germanium_SC41L_Crystal 2
#define Germanium_SC41R_Crystal 3
#define Germanium_SC41_Det_Digi 3
#define Germanium_SC41L_Crystal_Digi 2
#define Germanium_SC41R_Crystal_Digi 3
#define Germanium_TimeMachine_Det 2
#define Germanium_TimeMachineCh1 0
#define Germanium_TimeMachineCh2 1

#define AIDA_MAX_HITS 13000

#endif /* DESPEC_SETUP_FILE */
