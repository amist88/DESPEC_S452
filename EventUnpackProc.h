// $Id: TSCNUnpackProc.h 755 2011-05-20 08:04:11Z linev $
// Adapted for DESPEC by A.K.Mistry 2020
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

#ifndef EVENTUNPACKPROC_H
#define EVENTUNPACKPROC_H

#include "Riostream.h"

// Root Includes //
#include "TROOT.h"
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include "TCutG.h"
#include "TArc.h"
#include "TTree.h"
#include <string>
#include <array>
#include <vector>
#include <deque>

// Go4 Includes //
#include "TGo4UserException.h"
#include "TGo4Picture.h"
#include "TGo4MbsEvent.h"

#include "EventUnpackStore.h"
#include "CalibParameter.h"
#include "CorrelParameter.h"

#include "Detector_System.cxx"
#include "AIDA_Detector_System.h"
#include "FATIMA_Detector_System.h"
#include "PLASTIC_TAMEX_Detector_System.h"
#include "Germanium_Detector_System.h"
#include "DESPECAnalysis.h"
#include "FRS_Detector_System.h"

#include "White_Rabbit.h"
#include "AIDA_Event.h"
#include "AIDA_Decay_Event_Store.h"
#include "Raw_Event.h"
#include "AIDA_Headers.h"
#include "AIDA_Event.h"
#include "AIDA_Data_Types.h"
#include "TGo4MbsEvent.h"
#include "EventUnpackStore.h"
#include "Detector_System.cxx"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

///////////////////////////////

using namespace std;

#include "TGo4EventProcessor.h"

	class EventUnpackStore;


	class EventUnpackProc : public TGo4EventProcessor
	{
		public:

            EventUnpackProc();
			EventUnpackProc(const char* name);
            virtual ~EventUnpackProc();
						virtual void UserPostLoop();
			//FATIMA variables
			double FATgate1_low, FATgate1_high;
			double FATgate2_low, FATgate2_high;

            Bool_t BuildEvent(TGo4EventElement* dest);
             void Process_AIDA_Event(EventUnpackStore* event);


             TIDParameter* frs_id;

//            std::vector<AidaCluster> EventsToClusters(std::vector<AidaEvent> const&);
//             AidaHit ClusterPairToHit(std::pair<AidaCluster, AidaCluster> const&);

            //parameters
            CalibParameter *fCal;
            CorrelParameter *fCorrel;
            EventUnpackStore *fOutput;
            AidaUnpackData    fAida;

		protected:
//                 TGo4MbsEvent *fInput;

            //FRS histogram settings
      TH1I* MakeH1I(const char* foldername,
        const char* histoname,
        Int_t nbins,
        Float_t xmin, Float_t xmax,
        const char* xtitle = "channels",
        Color_t linecolor = 2,
        Color_t fillcolor = 6,
        const char* ytitle = 0);

      TH2I* MakeH2I(const char* foldername,
        const char* histoname,
        Int_t nbinsx, Float_t xmin, Float_t xmax,
        Int_t nbinsy, Float_t ymin, Float_t ymax,
        const char* xtitle, const char* ytitle,
        Color_t marker);

      TH1I* MakeH1I_TPC(const char* foldername, const char* name, int nameindex,
            Int_t nbins, Float_t xmin, Float_t xmax,
            const char* xtitle = "channels", Color_t linecolor = 2, Color_t fillcolor = 6);

        const static char* tpc_name_ext1[7];
        const static char* tpc_folder_ext1[7];

        //--------Scaler Graphs----------
  TH1          *hScaler_per_s[64];
  TH1          *hScaler_per_100ms[64];
  TH1          *hScaler_per_spill[64];
  int            scaler_ch_1kHz=0;
  int            scaler_ch_spillstart=0;
  UInt_t         scaler_initial[64];
  UInt_t         scaler_previous[64];
  int            scaler_check_first_event = 1;

   Float_t Music_dE[3], Music_dE_corr[3];

    Int_t Music_E1[8], Music_E2[8], Music_T1[8], Music_T2[8];

    Float_t sci_l[12], sci_r[12], sci_e[12], sci_tx[12], sci_x[12];

    Float_t sci_tofll2,  sci_tofrr2, sci_tof2, sci_tofll3, sci_tofrr3, sci_tof3,sci_tofll5, sci_tofrr5, sci_tof5;

    Float_t sci_tof2_calib, sci_tof3_calib, sci_tof5_calib;

    Float_t ID_x2, ID_y2, ID_a2, ID_b2;

    Float_t ID_x4, ID_y4, ID_a4, ID_b4;

    Float_t TPC_X[7], TPC_Y[7];
    Int_t TPC_LT[7][2][64], TPC_RT[7][2][64];
    Int_t TPC_A[7][4], TPC_L[7][2],TPC_R[7][2];
    Int_t TPC_DT[7][4][64];
   // Float_t TPC_X0, TPC_X1;
    Float_t TPC_X_s2_foc_23_24, TPC_Y_s2_foc_23_24, TPC_X_angle_s2_foc_23_24, TPC_Y_angle_s2_foc_23_24;
    Float_t TPC_23_24_X_sc21, TPC_23_24_Y_sc21, TPC_23_24_X_sc22, TPC_23_24_Y_sc22;
    Float_t TPC_X_s4, TPC_Y_s4, TPC_X_angle_s4, TPC_Y_angle_s4;
    Float_t TPC_X_sc41, TPC_Y_sc41, TPC_X_sc42, TPC_Y_sc42;
    Int_t sci_dt_21l_21r, sci_dt_41l_41r, sci_dt_42l_42r, sci_dt_43l_43r;

    Int_t sci_dt_21l_41l, sci_dt_21r_41r, sci_dt_21l_42l, sci_dt_21r_42r;

    Float_t ID_brho[2], ID_rho;

    Float_t beta, beta3, gamma;

    Float_t AoQ, AoQ_corr;

    Float_t ID_z, ID_z2, ID_z3;

    Float_t AoQ_mhtdc[10], AoQ_corr_mhtdc[10];

    Float_t ID_z_mhtdc[10], ID_z2_mhtdc[10];

    Float_t beta_mhtdc[10];

    Float_t ID_tof4121_mhtdc[10], ID_tof4221_mhtdc,ID_tof4122_mhtdc[10];

    Float_t timestamp, ts, ts2;

    Int_t time_in_ms;
    Int_t spill_count;
    Int_t ibin_for_s;
    Int_t ibin_for_100ms;
    Int_t ibin_for_spill;
    Int_t ibin_clean_for_s;
    Int_t ibin_clean_for_100ms;
    Int_t ibin_clean_for_spill;
    UInt_t* increase_scaler_temp;
    UInt_t frs_scaler_value[64];

    Double_t TRaw_vftx_21l, TRaw_vftx_21r,TRaw_vftx_22l, TRaw_vftx_22r;
    Double_t TRaw_vftx_41l, TRaw_vftx_41r, TRaw_vftx_42l, TRaw_vftx_42r;
    Double_t TRaw_vftx[32];
			TH1* hID_x2;
			TH1* hID_y2;
			TH1* hID_a2;
			TH1* hID_b2;

			TH1* hID_x4;
			TH1* hID_y4;
			TH1* hID_a4;
			TH1* hID_b4;


            /// positions and control sum

            TH1 *hTPC_X[7];
            TH1 *hTPC_Y[7];
            TH2 *hcTPC_XY[7];
            TH2 *hTPC_LTRT[7];
            TH1 *hTPC_DELTAX[7];
            TH1 *hTPC_A[7][4];
            TH1 *hTPC_DT[7][4];
            TH1 *hTPC_L0[7];
            TH1 *hTPC_L1[7];
            TH1 *hTPC_R0[7];
            TH1 *hTPC_R1[7];
            TH1 *hTPC_LT0[7];
            TH1 *hTPC_LT1[7];
            TH1 *hTPC_RT0[7];
            TH1 *hTPC_RT1[7];
            
            TH1 *hTPC_X_S2_TPC_23_24;
            TH1 *hTPC_Y_S2_TPC_23_24;
            TH1 *hTPC_AX_S2_TPC_23_24;
            TH1 *hTPC_AY_S2_TPC_23_24;
            TH2 *hTPC_X_AX_S2_TPC_23_24;
            TH2 *hTPC_Y_AY_S2_TPC_23_24;
            
            TH1 *hTPC_X_S4;
            TH1 *hTPC_Y_S4;
            TH1 *hTPC_AX_S4;
            TH1 *hTPC_AY_S4;
            TH2 *hTPC_X_AX_S4;
            TH2 *hTPC_Y_AY_S4;

            // CSUM[index][anode_no]
            TH1I *hTPC_CSUM[7][4];

            TH1* htpc_X2;
            TH1* htpc_Y2;
            TH1* htpc_X4;
            TH1* htpc_Y4;

            TH1 *hSCI_L[12];
            TH1 *hSCI_R[12];
            TH1 *hSCI_E[12];
            TH1 *hSCI_Tx[12];
            TH1 *hSCI_X[12];
            TH2 *hSCI_dE24;
           
            TH2 *hSCI_Tx_XTPC[12];
            TH2 *hSCI_X_XTPC[12];

            TH2I *hSCIdE41_TPC42X;
            TH2I *hSCIdE41L_TPC41X;
            TH2I *hSCIdE41L_TPC42X;
            TH2I *hSCIdE41R_TPC42X;
            TH2I *hSCIdE41R_TPC41X;
            TH2I *hSCIdE21_TPC42X;
            TH2I *hSCIdE21L_TPC42X;
            TH2I *hSCIdE21L_TPC41X;
            TH2I *hSCIdE21R_TPC42X;
            TH2I *hSCIdE21R_TPC41X;

            TH1 *hSCI_TofLL2;
            TH1 *hSCI_TofLL3;
            TH1 *hSCI_TofLL5;
            TH1 *hSCI_Tof2;
            TH1 *hSCI_TofRR2;
            TH1 *hSCI_TofRR3;
            TH1 *hSCI_TofRR5;
            TH1 *hSCI_Tof3;
            TH1 *hSCI_Tof5;

            TH1 *hSCI_Tof2_calib;
            TH1 *hSCI_Tof3_calib;
            TH1 *hSCI_Tof5_calib;

			TH1* hSCI_dT_21l_41l;
			TH1* hSCI_dT_21r_41r;

			TH1* hSCI_dT_21l_42l;
			TH1* hSCI_dT_21r_42r;

			TH1* hSCI_dT_21l_81l;
			TH1* hSCI_dT_21r_81r;

			TH1 *hID_AoQ;
            TH1 *hID_AoQ_corr;
            TH2 *hID_AoQa2;
            TH2 *hID_AoQa4;
            
            

            TH1 *hID_AoQ_mhtdc;
            TH1 *hID_AoQ_corr_mhtdc;
            TH1 *hID_beta_mhtdc;
//             TH1 *hID_beta_mhtdc_first_hit;
//             TH1 *hID_beta_mhtdc_excl_first_hit;
//             TH2 *hID_AoQ_vsAngle2_mhtdc;

//             TH2 *hID_Z_AoQ_mhtdc;
//             TH2 *hID_Z_AoQ_corr_mhtdc;
    //        TH2 *hID_Z_Z2_mhtdc;

			TH1 *hID_Z;
            TH1 *hID_Z2;

            TH1 *hID_Z_mhtdc;
            TH1 *hID_Z2_mhtdc;

          //  TH2I *hID_Z_Z2;
           // TH2I *hID_Z_Z3;

            //TH2 *hID_dEToF;
            TH1 *hID_beta;
            TH1 *hMultiHitTDC_TOF_41_21;
            TH1 *hMultiHitTDC_TOF_42_21;
            TH1 *hMultiHitTDC_TOF_41_22;
            TH1 *hID_BRho[2];
						TH1 *hMultiHitTDC_TOF_41_21_first_hit;
						TH1 *hMultiHitTDC_TOF_41_21_excl_first_hit;

            TH1* hvftx_TRaw[32];
            TH1* hvftx_Hit_Pattern;
            TH1* hvftx_Sci21PosRaw;
            TH1* hvftx_Sci22PosRaw;

            TH1* hvftx_Sci41PosRaw;
            TH1* hvftx_Sci42PosRaw;
            TH1* hvftx_ToFraw_2141;
            TH1* hvftx_ToFraw_2141LL;
            TH1* hvftx_ToFraw_2141RR;
            TH1* hvftx_ToFraw_2142LL;
            TH1* hvftx_ToFraw_2142RR;

			TH1* htimestamp;
			TH1* hts;
			TH1* hts2;

            TH1 *hMUSIC1_E[8];
            TH1 *hMUSIC1_T[8];
            TH1 *hMUSIC1_dE;

            TH1 *hMUSIC2_E[8];
            TH1 *hMUSIC2_T[8];
            TH1 *hMUSIC2_dE;

            TH2 *hMUSIC1_dE1dE2;

            TH2 *hMUSIC1_MUSIC2;


			//Fatima histograms
			//-general
			TH1* hFAT_Esum;
			TH2* hFAT_gg;
            TH1* hFAT_TDCdt_ref_sum;
			TH1* hFAT_TDCdt_refcalib_sum;
            TH1* hFAT_TDCdt_ref0_sum;
			TH1* hFAT_QDCdtsum;
			TH1* hFAT_TDCdtsum_ref_gated;
            TH1* hFAT_TDCdtsum_ref0_gated;
			TH1* hFAT_QDCdtsum_ref_gated;   //for now...
			TH1* hFAT_Angular_Diff_ref_gated; // Histogram of Gated Angular Differences
			//-statistics
			TH1* hFAT_hits;		     //number of hits per detector id
			TH1* hFAT_hits_QDC;
			TH1* hFAT_hits_TDC;
            TH1* hFAT_TDC_multi;

			TH1*  hFAT_Traw_VME[FAT_MAX_VME_CHANNELS];
			TH1*  hFAT_Eraw_VME[FAT_MAX_VME_CHANNELS];

			TH1* hFAT_TDC_multich[FAT_MAX_VME_CHANNELS];

            TH1 *hScaler_hit_pattern;
			//Plastic histograms
			//TH1*** tamex_Mult_Ch_lead;
			//TH1*** tamex_Mult_Ch_trail;
			//TH2** tamex_mult_mat_lead;
			//TH2** tamex_mult_mat_trail;
			//TH1*** Trail_LEAD;
			TH1**** TRAIL_TRAIL;
			TH1**** LEAD_LEAD;

			//TH1*** Coarse;
			//TH1** DIFF_ARR;
			TH1**** TOT_TOT;
			TH1*** TOT_Single;
			//TH1*** LEAD_LEAD_Total;

			TH1 *hFatima_test;

            TH1 *hFATlead_Coarse[FATIMA_TAMEX_CHANNELS];
            TH1 *hFATlead_Fine[FATIMA_TAMEX_CHANNELS];
            TH1 *hFATtrail_Coarse[FATIMA_TAMEX_CHANNELS];
            TH1 *hFATtrail_Fine[FATIMA_TAMEX_CHANNELS];

        int TAMEX_bPlasFat_ID[6][80];
			// Germanium Histograms //
			TH1 *hGe_Raw_E[Germanium_MAX_HITS];
            TH1 *hFebTime;

		private:


            int AIDA_Hits=0;
            double AIDA_Energy[AIDA_MAX_HITS] = {0};
            int AIDA_FEE[AIDA_MAX_HITS] = {0};
            int AIDA_ChID[AIDA_MAX_HITS] = {0};
            ULong64_t AIDA_Time[AIDA_MAX_HITS] = {0};
            bool AIDA_HighE_veto[AIDA_MAX_HITS] = {false};
            int AIDA_Side[AIDA_MAX_HITS] = {0};
            int AIDA_Strip[AIDA_MAX_HITS] = {0};
            int AIDA_evtID[AIDA_MAX_HITS] = {0};

			Int_t PrcID_Array[10][9];
			bool Used_Systems[10];

            Int_t Type;
            Int_t SubType;

            int fingID[4][16];
            int TAMEX_Fat_ID[FATIMA_TAMEX_MODULES][FATIMA_TAMEX_CHANNELS];
            int TAMEX_bPlast_Det[bPLASTIC_TAMEX_MODULES][bPLASTIC_TAMEX_CHANNELS];
            //int TAMEX_bPlast_Det;
            int TAMEX_bPlast_Chan[4][bPLASTIC_TAMEX_CHANNELS];
			bool PADI_OR_PADIWA,VME_TAMEX_bPlas,VME_TAMEX_Fatima, VME_AND_TAMEX_Fatima;

        ///For AIDA

            long lastTime;
            int ID;
            AidaEvent old;
            AidaEvent evt;

            long startTime;
            long stopTime;

      /* Multiplexer correction */
						std::vector<std::array<uint64_t, 4>> adcLastTimestamp;
						std::vector<std::array<int, 4>> adcCounts;
            void ResetMultiplexer();
            void CorrectTimeForMultiplexer(AidaEvent& evt);

            int totalEvents;
            int implantEvents;
            int decayEvents;
            int pulserEvents;
            int nonsenseEvents;

						// AIDA histograms
						std::vector<std::array<std::array<TH1*, 2>, 64>>	hAIDA_ADC;
						TH2* hAIDA_ADC_unaligned;
						TH2* hAIDA_ADC_aligned;
                                                std::map<int, TH1*> hAIDA_Scaler;
                                                std::map<int, std::deque<int>> aida_scaler_queue;
                                                std::map<int, int> aida_scaler_cur_sec;
						TH1* hAIDA_TimeMachine;

      ///End AIDA
			int val_it;
            int event_number;



			bool WR_used;
			bool WHITE_RABBIT_USED; // Read from General Setup File

			int data_file_number = 0;

			Detector_System** Detector_Systems;
			White_Rabbit* WR;
			Raw_Event* RAW;

			Int_t get_Conversion(Int_t);
			void get_used_systems();

            void load_FingerID_File();
            void load_FatTamex_Allocationfile();
            void load_bPlasticTamex_Allocationfile();
			void load_PrcID_File();

			void Make_FRS_Histos();
			void Fill_FRS_Histos(int,int,int);

            void Make_AIDA_Histos();
            void Fill_AIDA_Histos();

			void Make_Plastic_Histos();
			void Fill_Plastic_Histos();

            void Make_Plastic_VME_Histos();
            void Fill_Plastic_VME_Histos();

			void Make_FATIMA_Histos();
			void Fill_FATIMA_Histos(EventUnpackStore* fOutput);

            void Make_FATIMA_TAMEX_Histos();
            void Fill_FATIMA_TAMEX_Histos();

			void Make_Germanium_Histos();
			void Fill_Germanium_Histos();

            void Make_Finger_Histos();
            void Fill_Finger_Histos();

			void FILL_HISTOGRAMS(int,int,int,EventUnpackStore* fOutput);

			void checkPADI_or_PADIWA();


           // void checkTAMEXorVME();
            void PrintDespecParameters();
			void print_MBS(int*,int);

			int count;
			int iterator;

			ULong64_t WR_tmp;
            ULong64_t WR_main;
            int WR_count;
            int WR_d;
			ClassDef(EventUnpackProc,1)
	};

#endif
