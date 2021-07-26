#include "Riostream.h"
    
void setup_er2019_FRS000_018()
{

    DESPECAnalysis* an = dynamic_cast<DESPECAnalysis*> (TGo4Analysis::Instance());
  if (an==0) {
    cout << "!!!  Script should be run in FRS analysis" << endl;
    return;
  }
  
   
   
  TFRSParameter* frs = dynamic_cast<TFRSParameter*> (an->GetParameter("FRSPar"));
  if (frs==0) {
    cout << "!!!  Parameter FRSPar not found" << endl;
    return;
  }

  TMWParameter* mw = dynamic_cast<TMWParameter*> (an->GetParameter("MWPar"));
  if (mw==0) {
    cout << "!!!  Parameter MWPar not found" << endl;
    return;
  }

  TMUSICParameter* music = dynamic_cast<TMUSICParameter*> (an->GetParameter("MUSICPar"));
  if (music==0) {
    cout << "!!!  Parameter MUSICPar not found" << endl;
    return;
  }

  TSCIParameter* sci = dynamic_cast<TSCIParameter*> (an->GetParameter("SCIPar"));
  if (sci==0) {
    cout << "!!!  Parameter SCIPar not found" << endl;
    return;
  }

  TIDParameter* id = dynamic_cast<TIDParameter*> (an->GetParameter("IDPar"));
  if (id==0) {
    cout << "!!!  Parameter IDPar not found" << endl;
    return;
  }
   
  TTPCParameter* tpc = dynamic_cast<TTPCParameter*> (an->GetParameter("TPCPar"));
  if (tpc==0) {
    cout << "!!!  Parameter TPCPar not found" << endl;
    return;
  }

  TSIParameter* si = dynamic_cast<TSIParameter*> (an->GetParameter("SIPar"));
  if (si==0) {
    cout << "!!!  Parameter SIPar not found" << endl;
    return;
  }

  TMRTOFMSParameter* mrtof = dynamic_cast<TMRTOFMSParameter*> (an->GetParameter("MRTOFMSPar"));
  if (mrtof==0) {
    cout << "!!!  Parameter MR-TOF-MSPar not found" << endl;
    return;
  }
  
//   TModParameter* ElecMod = dynamic_cast<TModParameter*>(an->GetParameter("ModPar"));
   
  cout << endl << "setup script started" << endl;
 
  // setup FRS parameter
///168Re fragment centered with degrader S2, 
  // 20.Nov.2019
  // For the momemnt, we put 1 m for radius,
  // because we get brho from control system.
  frs->rho0[0]   = 1.;
  frs->rho0[1]   = 1.;
  frs->rho0[2]   = 1.; //S4-S8
  frs->dispersion[0] = -6.474266; // RUN81-TA2B-220CM 27.05.2016
  frs->dispersion[1] =  7.7064; // RUN81-TA2B-220CM 27.05.2016
  frs->magnification[1] = 1.1903;   // RUN81-TA2B-220CM 27.05.2016
 
  frs->dispersion[2]    = 12.397;   //S2-S8 (gicosy sign definition)
  frs->magnification[2] =  1.829;   //S2-S8
   ///-----distances (2019/Nov-Dec) -----
      ///S2
  frs->dist_focS2   = 2012.5; // [mm] at wedge position S411
  frs->dist_MW21    =  604.0; // 
  frs->dist_MW22    = 1782.5; // 
  frs->dist_SC21    = 1554.5; // 
  frs->dist_SC22    =-999;//
  frs->dist_TPC21 =  604.0;
  frs->dist_TPC22 = 1782.5;
  frs->dist_TPC23 =          -999;
  frs->dist_TPC24 =           999;
  frs->dist_S2target = 2460.5; //for some experiments
  
  ///S4
  frs->dist_focS4   = 2349.0; // at SC411  
  
  frs->dist_SC41    = 2245.0;
  frs->dist_SC42    = 2620.0;
  frs->dist_SC43    = 4706.0;
  frs->dist_MUSIC41 = 735.0;
  frs->dist_MUSIC42 = 1215.0;
  frs->dist_MUSIC43 = 5013.0;
  frs->dist_TPC41   =  415.0;
  frs->dist_TPC42   = 1535.0;
  frs->dist_S4target= 4000.0; //for some experiments
  
  ///S8
  frs->dist_focS8 = 0;
  frs->dist_MW81 = 0;
  frs->dist_MW82 = 0;
  frs->dist_SC81 = 0;
  
  // 2019 nov  20
  frs->primary_z = 92.;
  //frs->offset_z  =  0.;
  id->min_aoq_plot = 2.1;
  id->max_aoq_plot = 2.7;
  id->min_z_plot   = 50.0;
  id->max_z_plot   = 100.0;
  
  frs->bfield[0] = 10.1715; // 2019-Dec12  
  frs->bfield[1] = 10.1715;    
  frs->bfield[2] = 7.7955; // Brho 2019-Dec12  
  frs->bfield[3] = 7.7955; // D4 (to S4) not used
  frs->bfield[4] = 99.999; // D5 (to ESR) not used
  frs->bfield[5] = 8.7817; // D6 (to S8)
      
   // TOF calibration SC21-SC81 (TAC)
   id->id_tofoff4  = 210000.;   // [ps]  //check 
   id->id_path4    = 120000.;   // path/c [ps]  //check
     
//      id->id_tofoff4  = 374609.;   //SC21-81 [ps]          // quickly done from run156 and 166 (2019/Nov, YT)
//      id->id_path4    = 284296.;   //SC21-81  path/c [ps]  // quickly done from run156 and 166 (2019/Nov, YT)
//   
   // TOF calibration SC21-SC81 (TAC)

  
  // TPC@S2->Z estimation, velocity correction (TAC)
    id->vel_a_s2tpc[0] =  7.48405*200.*(18.*18./(14.0*14.0));// TPC-A was not measured during tof calib.
    id->vel_a_s2tpc[1] = -13.7912*200.*(18.*18./(14.0*14.0));// now we estimate from ATIMA. and then
    id->vel_a_s2tpc[2] =  7.38286*200.*(18.*18./(14.0*14.0));// translate parameters to fit go4 parametes. (YT)
    id->vel_a_s2tpc[3] =  0.0;
    id->offset_z_s2tpc = 0.0;
    
    // SC81->Z estimation, velocity correction (TAC)
	  id->vel_a_sc81[0] =  1.;// SC81 dE was not propery measured.
	  id->vel_a_sc81[1] =  0.;// I skip to set these parameters
	  id->vel_a_sc81[2] =  0.;// this time ...
	  id->vel_a_sc81[3] =  0.0;
	  id->offset_z_sc81 = 0.0;
      
     // From here Multi-HitTDC analysis
	  id->mhtdc_length_s2s8 = 85.230; // (2019/Nov, YT)
	  id->mhtdc_s2pos_option=1; //(1: sc21x-timediff-mhtdc, 2:tpc);
	  id->pos_offset_sc81x  = 7.0;// (2019/Nov, YT)
	  // MHTDCAnalyais TPC@S2dE => Z estimation, velocity correction
	  id->mhtdc_vel_a_s2tpc[0] =  7.48405*200.*(18.*18./(14.0*14.0));// TPC-A was not measured during tof calib.
	  id->mhtdc_vel_a_s2tpc[1] = -13.7912*200.*(18.*18./(14.0*14.0));// now we estimate from ATIMA. and then
	  id->mhtdc_vel_a_s2tpc[2] =  7.38286*200.*(18.*18./(14.0*14.0));// translate parameters to fit go4 parametes. (YT)
	  id->mhtdc_vel_a_s2tpc[3] =  0.0;
	  id->mhtdc_offset_z_s2tpc = 0.0;
	
	  // MHTDCAnalyais, velocity correction SC81dE => Z estimation
	  id->mhtdc_vel_a_sc81[0] =  1.;// SC81 dE was not propery measured.
	  id->mhtdc_vel_a_sc81[1] =  0.;// I skip to set these parameters
	  id->mhtdc_vel_a_sc81[2] =  0.;// this time ...
	  id->mhtdc_vel_a_sc81[3] =  0.0;
	  id->mhtdc_offset_z_sc81 = 0.0;
  
      id->offset_z  = 3.0 ;
      id->offset_z2  = 0.0 ;
      id->offset_z3  = 0.0 ;
      id->a2AoQCorr = 0.00095;
      id->a4AoQCorr = 0.0012;//0.0015
///MUSIC velocity corrections
      id->vel_a[0] =   8232.58;
      id->vel_a[1] =  -6483.04; 
      id->vel_a[2] =   0.0; 
      id->vel_a[3] =   0.0;
      id->vel_a2[0] =  19602 ;  
      id->vel_a2[1] =  -34442;
      id->vel_a2[2] =  17273;
      id->vel_a2[3] =  0.0; 
      id->vel_a3[0] =  13951.37; //
      id->vel_a3[1] =  -38369.9; 
      id->vel_a3[2] =  28396.46;
      id->vel_a3[3] =  0.0;    
      
      id-> id_tofoff2 =  174541;    // Offset (ps)
      id-> id_path2   =   122389.;  // Path/c (ps) this number fit
  
      id->id_tofoff3  = 210000.;   // [ps] //check
      id->id_path3    = 120000.;   // path/c [ps] //check
      
      id->mhtdc_length_s2s4 = 0.0;
	  id->mhtdc_vel_a_music41[0]=1.0;
	  id->mhtdc_vel_a_music41[1]=0.0;
	  id->mhtdc_vel_a_music41[2]=0.0;
	  id->mhtdc_vel_a_music41[3]=0.0;
	  id->mhtdc_vel_a_music42[0]=1.0;
	  id->mhtdc_vel_a_music42[1]=0.0;
	  id->mhtdc_vel_a_music42[2]=0.0;
	  id->mhtdc_vel_a_music42[3]=0.0;
	  id->mhtdc_offset_z_music41=0.0;
	  id->mhtdc_offset_z_music42=0.0;

//   //**S323,410 exp.
//   frs->dist_MUSIC1  = 555.0;  // TUM1
//   frs->dist_MUSIC2  = 1210.0; // Travelling MUSIC 
//   frs->dist_MUSIC3  = 1210.0; // TUM2
//  
//   frs->dist_MUSICa1 = 52.5;  // do not change
//   frs->dist_MUSICa2 = 157.5; // do not change
//   frs->dist_MUSICa3 = 262.5; // do not change
//   frs->dist_MUSICa4 = 367.5; // do not change
  

  

   //======
  //  MW
  //======
  /*   Naming conventions:  index     detector                               */
  /*                         0         MW11                                 */
  /*                         1         MW21                                 */
  /*                         2         MW22                                  */
  /*                         3         MW31                                 */
  /*                         4         MW51                                  */
  /*                         5         MW71                                  */
  /*                         6         MW81                                  */
  /*                         7         MW82                                  */
  /////////////////////////////////////////////////////////////////////////////

  mw->x_factor[0] = 0.25; // MW11 [mm/ns] some old value
  mw->x_factor[1] = 0.25; // MW21
  mw->x_factor[2] = 0.25; // MW22
  mw->x_factor[3] = 0.25; // MW31
  mw->x_factor[4] = 0.25; // MW51 
  mw->x_factor[5] = 0.25; // MW71
  mw->x_factor[6] = 0.25; // MW81
  mw->x_factor[7] = 0.125; // MW82

  mw->x_offset[0] = 5.0; // MW11 Feb 2014
  mw->x_offset[1] = -2.0; // MW21 Feb 2014
  mw->x_offset[2] = -1.5; // MW22 Feb 2014
  mw->x_offset[3] = 5.0; // MW31 like MW11 15.11.19
  mw->x_offset[4] = -0.205; // MW51
  mw->x_offset[5] = 1.642; // MW71 //15/05/06
  mw->x_offset[6] = 1.;   // MW81 //11/05/06
  mw->x_offset[7] = -5.; // MW82 //27-MAY-2007

  mw->y_factor[0] = 0.25; // MW11 [mm/ns] 14.09.05 CN+AM 2ns/mm delay line 
  mw->y_factor[1] = 0.25; // MW21
  mw->y_factor[2] = 0.25; // MW22
  mw->y_factor[3] = 0.25; // MW31
  mw->y_factor[4] = 0.25; // MW51 
  mw->y_factor[5] = 0.25; // MW71
  mw->y_factor[6] = 0.25; // MW81
  mw->y_factor[7] = 0.125; // MW82  [mm/ns] 11.05.06  CN 4ns/mm delay line

  mw->y_offset[0] = -14.0;  // MW11 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
  mw->y_offset[1] = 21.0;   // Feb 2014
  mw->y_offset[2] = -1.0;   // MW22 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
  mw->y_offset[3] = -14.0;    // MW31 like in MW11 15.11.19
  mw->y_offset[4] = 0.0;     //MW51  ???????
  mw->y_offset[5] = -2.736;  // MW71 //15/05/06
  mw->y_offset[6] = 3.2;     // MW81 //11/05/06
  mw->y_offset[7] = 0.764;  // MW82 //11/05/06

  mw->gain_tdc[0][0] = 0.302929; //  MW11 Anode (#ch  0 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][0] = 0.303253; //  MW11 XL    (#ch 17 TDC V775a)
  mw->gain_tdc[2][0] = 0.303975; //  MW11 XR    (#ch 16 TDC V775a)
  mw->gain_tdc[3][0] = 0.308414; //  MW11 YU    (#ch 18 TDC V775a)
  mw->gain_tdc[4][0] = 0.309826; //  MW11 YD    (#ch 19 TDC V775a)

  mw->gain_tdc[0][1] = 0.306064; //  MW21 Anode (#ch  1 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][1] = 0.306958; //  MW21 XL    (#ch 21 TDC V775a)
  mw->gain_tdc[2][1] = 0.307799; //  MW21 XR    (#ch 20 TDC V775a)
  mw->gain_tdc[3][1] = 0.297774; //  MW21 YU    (#ch 22 TDC V775a)
  mw->gain_tdc[4][1] = 0.310235; //  MW21 YD    (#ch 23 TDC V775a)

  mw->gain_tdc[0][2] = 0.301179;  // MW22 Anode (#ch  2 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][2] = 0.311121; //  MW22 XL    (#ch 25 TDC V775a)
  mw->gain_tdc[2][2] = 0.303233; //  MW22 XR    (#ch 24 TDC V775a)
  mw->gain_tdc[3][2] = 0.300558; //  MW22 YU    (#ch 26 TDC V775a)
  mw->gain_tdc[4][2] = 0.301105; //  MW22 YD    (#ch 27 TDC V775a)

  mw->gain_tdc[0][3] = 0.304426; //  MW31 Anode (#ch  3 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][3] = 0.312163; //  MW31 XL    (#ch 29 TDC V775a)
  mw->gain_tdc[2][3] = 0.305609; //  MW31 XR    (#ch 28 TDC V775a)
  mw->gain_tdc[3][3] = 0.304716; //  MW31 YU    (#ch 30 TDC V775a)
  mw->gain_tdc[4][3] = 0.293695; //  MW31 YD    (#ch 31 TDC V775a)

  mw->gain_tdc[0][4] = 0.298871; //  MW41 Anode (#ch  4 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][4] = 0.284086; //  MW41 XL    (#ch 1 TDC V775b)
  mw->gain_tdc[2][4] = 0.288656; //  MW41 XR    (#ch 0 TDC V775b)
  mw->gain_tdc[3][4] = 0.286589; //  MW41 YU    (#ch 2 TDC V775b)
  mw->gain_tdc[4][4] = 0.29269;  //  MW41 YD    (#ch 3 TDC V775b)

  mw->gain_tdc[0][5] = 0.297881; //  MW42 Anode (#ch  5 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][5] = 0.287364; //  MW42 XL    (#ch 5 TDC V775b)
  mw->gain_tdc[2][5] = 0.289636; //  MW42 XR    (#ch 4 TDC V775b)
  mw->gain_tdc[3][5] = 0.291135; //  MW42 YU    (#ch 6 TDC V775b)
  mw->gain_tdc[4][5] = 0.289867; //  MW42 YD    (#ch 7 TDC V775b)

  mw->gain_tdc[0][6] = 0.307892; //  MW51 Anode (#ch  6 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][6] = 0.289894; //  MW51 XL    (#ch  9 TDC V775b)
  mw->gain_tdc[2][6] = 0.292366; //  MW51 XR    (#ch  8 TDC V775b)
  mw->gain_tdc[3][6] = 0.284708; //  MW51 YU    (#ch 10 TDC V775b)
  mw->gain_tdc[4][6] = 0.28186;  //  MW51 YD    (#ch 11 TDC V775b)

  mw->gain_tdc[0][7] = 0.298266; //  MW61 Anode (#ch  7 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][7] = 0.311; //  MW61 XL    (#ch ? TDC V775b)
  mw->gain_tdc[2][7] = 0.305; //  MW61 XR    (#ch ? TDC V775b)
  mw->gain_tdc[3][7] = 0.337; //  MW61 YU    (#ch ? TDC V775b)
  mw->gain_tdc[4][7] = 0.289; //  MW61 YD    (#ch ? TDC V775b)

  mw->gain_tdc[0][8] = 0.303602; //  MW71 Anode (#ch  8 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][8] = 0.300082; //  MW71 XL    (#ch 13 TDC V775b)
  mw->gain_tdc[2][8] = 0.286092; //  MW71 XR    (#ch 12 TDC V775b)
  mw->gain_tdc[3][8] = 0.294287; //  MW71 YU    (#ch 14 TDC V775b)
  mw->gain_tdc[4][8] = 0.291341; //  MW71 YD    (#ch 15 TDC V775b)

  mw->gain_tdc[0][9] = 0.306041; //  MW81 Anode (#ch  9 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][9] = 0.288468; //  MW81 XL    (#ch 17 TDC V775b)
  mw->gain_tdc[2][9] = 0.293831; //  MW81 XR    (#ch 16 TDC V775b)
  mw->gain_tdc[3][9] = 0.281296; //  MW81 YU    (#ch 18 TDC V775b)
  mw->gain_tdc[4][9] = 0.279099; //  MW81 YD    (#ch 19 TDC V775b)

  mw->gain_tdc[0][10] = 0.31314;  //  MW82 Anode (#ch 10 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][10] = 0.287279; //  MW82 XL    (#ch 21 TDC V775b)
  mw->gain_tdc[2][10] = 0.284028; //  MW82 XR    (#ch 20 TDC V775b)
  mw->gain_tdc[3][10] = 0.28051;  //  MW82 YU    (#ch 22 TDC V775b)
  mw->gain_tdc[4][10] = 0.28743;  //  MW82 YD    (#ch 23 TDC V775b)

  mw->gain_tdc[0][11] = 0.299973; //  MWB21 Anode (#ch 11 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][11] = 0.311; //  MWB21 XL    (#ch ? TDC V775b)
  mw->gain_tdc[2][11] = 0.305; //  MWB21 XR    (#ch ? TDC V775b)
  mw->gain_tdc[3][11] = 0.337; //  MWB21 YU    (#ch ? TDC V775b)
  mw->gain_tdc[4][11] = 0.289; //  MWB21 YD    (#ch ? TDC V775b)

  mw->gain_tdc[0][12] = 0.306923; //  MWB22 Anode (#ch 12 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][12] = 0.311; //  MWB22 XL    (#ch ? TDC V775b)
  mw->gain_tdc[2][12] = 0.305; //  MWB22 XR    (#ch ? TDC V775b)
  mw->gain_tdc[3][12] = 0.337; //  MWB22 YU    (#ch ? TDC V775b)
  mw->gain_tdc[4][12] = 0.289; //  MWB22 YD    (#ch ? TDC V775b)


  //=========
  // MUSICs
  //=========
// histogram setup
	  music->max_adc_music1 =    4096; //tum music
	  music->max_adc_music2 =  0x2000; //travel music //depends on setup in mdpp16
	  music->max_adc_music3 =    4096; //tum music
	  music->max_tdc_music1 =    4096; //tum music
	  music->max_tdc_music2 =  0x10000; //travel music
	  music->max_tdc_music3 =    4096; //tum music
	
	  music->dist_MUSICa1 = 52.5;  // do not change
	  music->dist_MUSICa2 = 157.5; // do not change
	  music->dist_MUSICa3 = 262.5; // do not change
	  music->dist_MUSICa4 = 367.5; // do not change
	  
  //MUSIC41
  music->e1_off[0]   = 0.; //MUSIC41 offsets
  music->e1_off[1]   = 0.; 
  music->e1_off[2]   = 0.;
  music->e1_off[3]   = 0.;
  music->e1_off[4]   = 0.;
  music->e1_off[5]   = 0.;
  music->e1_off[6]   = 0.;
  music->e1_off[7]   = 0.;

  music->e1_gain[0]   = 1.; // MUSIC41 gains
  music->e1_gain[1]   = 1.; 
  music->e1_gain[2]   = 1.;
  music->e1_gain[3]   = 1.;
  music->e1_gain[4]   = 1.;
  music->e1_gain[5]   = 1.;
  music->e1_gain[6]   = 1.;
  music->e1_gain[7]   = 1.;

  //MUSIC42
  music->e2_off[0]   = 0.; //MUSIC42 offsets
  music->e2_off[1]   = 0.; 
  music->e2_off[2]   = 0.;
  music->e2_off[3]   = 0.;
  music->e2_off[4]   = 0.;
  music->e2_off[5]   = 0.;
  music->e2_off[6]   = 0.;
  music->e2_off[7]   = 0.;

  music->e2_gain[0]   = 1.; //MUSIC42 gains
  music->e2_gain[1]   = 1.; 
  music->e2_gain[2]   = 1.;
  music->e2_gain[3]   = 1.;
  music->e2_gain[4]   = 1.;
  music->e2_gain[5]   = 1.;
  music->e2_gain[6]   = 1.;
  music->e2_gain[7]   = 1.;

  //MUSIC43
  music->e3_off[0]   = 0.; //MUSIC3 offsets
  music->e3_off[1]   = 0.; 
  music->e3_off[2]   = 0.;
  music->e3_off[3]   = 0.;
  music->e3_off[4]   = 0.;
  music->e3_off[5]   = 0.;
  music->e3_off[6]   = 0.;
  music->e3_off[7]   = 0.;
  
  music->e3_gain[0]   = 1.; // MUSIC3 gains
  music->e3_gain[1]   = 1.; 
  music->e3_gain[2]   = 1.;
  music->e3_gain[3]   = 1.;
  music->e3_gain[4]   = 1.;
  music->e3_gain[5]   = 1.;
  music->e3_gain[6]   = 1.;
  music->e3_gain[7]   = 1.;

  music->pos_a1[0]   = 1.0;   // C0...Cn position correction not used
  music->pos_a1[1]   = 0.0;
  music->pos_a1[2]   = 0.0;
  music->pos_a1[3]   = 0.0;
  music->pos_a1[4]   = 0.0;
  music->pos_a1[5]   = 0.0;
  music->pos_a1[6]   = 0.0;


  //=========
  //  TPCs
  //=========
  
  //TPC 1 at S2 (TPC 21) in vaccuum  
  tpc->x_factor[0][0] = 0.079646;
  tpc->x_factor[0][1] = 0.079243;
  tpc->y_factor[0][0] = 0.03207;
  tpc->y_factor[0][1] = 0.03135;
  tpc->y_factor[0][2] = 0.031126;
  tpc->y_factor[0][3] = 0.032056; 
     
  tpc->x_offset[0][0] = -26.576;
  tpc->x_offset[0][1] = -52.23;
  tpc->y_offset[0][0] = -55.435 -3.708;
  tpc->y_offset[0][1] = -52.347 -3.625;
  tpc->y_offset[0][2] = -50.448 -3.599;
  tpc->y_offset[0][3] = -57.084 -3.707;
  

  //TPC 2 at S2 (TPC 22) in vaccuum
  tpc->x_factor[1][0] = 0.065251;
  tpc->x_factor[1][1] = 0.063554;
  tpc->y_factor[1][0] = 0.031488;
  tpc->y_factor[1][1] = 0.031949;
  tpc->y_factor[1][2] = 0.031321;
  tpc->y_factor[1][3] = 0.03171;  

  tpc->x_offset[1][0] = -33.958;
  tpc->x_offset[1][1] = -36.597;
  tpc->y_offset[1][0] = -52.579 -3.622;
  tpc->y_offset[1][1] = -55.077 -3.675;
  tpc->y_offset[1][2] = -47.418 -3.602;
  tpc->y_offset[1][3] = -51.457 -3.647;
  

  //TPC 3 at S2 (TPC 23) in air 
  tpc->x_factor[2][0] = 0.070128;  //L-R time 0
  tpc->x_factor[2][1] = 0.071489;  //L-R time 1
  tpc->y_factor[2][0] = -0.036481; //drift time 0
  tpc->y_factor[2][1] = -0.036863; //drift time 1
  tpc->y_factor[2][2] = -0.037120; //drift time 2
  tpc->y_factor[2][3] = -0.037125; //drift time 3

    
  tpc->x_offset[2][0] = 0.81-4.9; //2016Jul9
  tpc->x_offset[2][1] = 0.03-4.9; //2016Jul9 
  tpc->y_offset[2][0] = 19.2+49.8;//2016Jul9  
  tpc->y_offset[2][1] = 19.7+49.8;//2016Jul9  
  tpc->y_offset[2][2] = 18.9+49.8;//2016Jul9  
  tpc->y_offset[2][3] = 19.2+49.8;//2016Jul9
  

  //TPC 4 at S2 (TPC 24) in air
  tpc->x_factor[3][0] = 0.068179;
  tpc->x_factor[3][1] = 0.066689;
  tpc->y_factor[3][0] = -0.0412;
  tpc->y_factor[3][1] = -0.0411;
  tpc->y_factor[3][2] = -0.0404;
  tpc->y_factor[3][3] = -0.0418;

 
  tpc->x_offset[3][0] = -0.37+6.0-1.3 -4.8;//2016Jul9
  tpc->x_offset[3][1] = 2.3+6.0-1.3-4.8;//2016Jul9
  tpc->y_offset[3][0] = 28.0+48.9;//2016Jul9
  tpc->y_offset[3][1] = 28.4+48.9;//2016Jul9
  tpc->y_offset[3][2] = 28.4+48.9;//2016Jul9
  tpc->y_offset[3][3] = 27.8+48.9; //2016Jul9
  

  //TPC 5  at S4 (TPC 41) in air
  tpc->x_factor[4][0] = (0.086757);
  tpc->x_factor[4][1] = (0.085185);
  tpc->y_factor[4][0] = (-0.042107);
  tpc->y_factor[4][1] = (-0.042767);
  tpc->y_factor[4][2] = (-0.041949);
  tpc->y_factor[4][3] = (-0.041911);

  tpc->x_offset[4][0] = (-2.2117);
  tpc->x_offset[4][1] = (1.827);
  tpc->y_offset[4][0] = (66.006) +3.842;
  tpc->y_offset[4][1] = (66.287) +3/897;
  tpc->y_offset[4][2] = (65.527) +3.822;
  tpc->y_offset[4][3] = (65.286) +3.819;

  
  //TPC 6 at S4 (TPC 42) in air
  tpc->x_factor[5][0] = (0.083599);
  tpc->x_factor[5][1] = (0.08588);
  tpc->y_factor[5][0] = (-0.041885);
  tpc->y_factor[5][1] = (-0.04219);
  tpc->y_factor[5][2] = (-0.04313);
  tpc->y_factor[5][3] = (-0.042084);

  tpc->x_offset[5][0] = (-3.6323);
  tpc->x_offset[5][1] = (-3.7713);
  tpc->y_offset[5][0] = (60.363) +3.350;
  tpc->y_offset[5][1] = (60.58) +3.375;
  tpc->y_offset[5][2] = (58.993) +3.449;
  tpc->y_offset[5][3] = (58.805) +3.366;
  
  
  //tpc->x_factor[5][0] = 0.071256;
  //tpc->x_factor[5][1] = 0.072858;
  //tpc->y_factor[5][0] =-0.04215;
  //tpc->y_factor[5][1] =-0.04161;
  //tpc->y_factor[5][2] =-0.04100;
  //tpc->y_factor[5][3] =-0.04025;

  //tpc->x_offset[5][0] = -0.4-0.3+0.35; //21.10.2014
  //tpc->x_offset[5][1] = 1.1-0.3+0.35; //21.10.2014
  //tpc->y_offset[5][0] = 22.6;
  //tpc->y_offset[5][1] = 21.9;
  //tpc->y_offset[5][2] = 20.7;
  //tpc->y_offset[5][3] = 20.4;
//   tpc->x_offset[6][0] = 12.423937;
//   tpc->x_offset[6][1] = 5.771517;
//   tpc->x_factor[6][0] = 0.083178;
//   tpc->x_factor[6][1] = 0.081852;
//   
//   tpc->y_offset[6][0] = -51.080220;
//   tpc->y_offset[6][1] = -67.488923;
//   tpc->y_offset[6][2] = -35.682118;
//   tpc->y_offset[6][3] = -63.732814;
//   tpc->y_factor[6][0] = 0.047685;
//   tpc->y_factor[6][1] = 0.048059;
//   tpc->y_factor[6][2] = 0.047611;
//   tpc->y_factor[6][3] = 0.047218; 

 	  //TPC at S3 (TPC 31)
	  tpc->x_factor[6][0] = 0.08;
	  tpc->x_factor[6][1] = 0.08;
	  tpc->y_factor[6][0] = 0.032;
	  tpc->y_factor[6][1] = 0.032;
	  tpc->y_factor[6][2] = 0.032;
	  tpc->y_factor[6][3] = 0.032;
	
	  //TPC21 ADC pedestal
	  tpc->a_offset[0][0] = 43.;
	  tpc->a_offset[0][1] = 72.;
	  tpc->a_offset[0][2] = 56.;
	  tpc->a_offset[0][3] = 48.;
	  //TPC22 ADC pedestal
	  tpc->a_offset[1][0] = 73.;
	  tpc->a_offset[1][1] = 56.;
	  tpc->a_offset[1][2] = 73.;
	  tpc->a_offset[1][3] = 74.;
	  //TPC23 ADC pedestal
	  tpc->a_offset[2][0] = 999.; //set large number to exclude (pedestal data) of this tpc
	  tpc->a_offset[2][1] = 999.;
	  tpc->a_offset[2][2] = 999.;
	  tpc->a_offset[2][3] = 999.;
	  //TPC24 ADC pedestal
	  tpc->a_offset[3][0] = 999.;
	  tpc->a_offset[3][1] = 999.;
	  tpc->a_offset[3][2] = 999.;
	  tpc->a_offset[3][3] = 999.;
	
	  tpc->x_offset[6][0] = 0.;
	  tpc->x_offset[6][1] = 0.;
	  tpc->y_offset[6][0] = -50.;
	  tpc->y_offset[6][1] = -50.;
	  tpc->y_offset[6][2] = -50.;
	  tpc->y_offset[6][3] = -50.;
  //===========
  // Plastics
  //===========

  //index 2 for Sc21  
  //sci->x_a[0][2] =  -2065.2-27+55;  //  SC21 calibration ch->mm 27.05.2016
  //sci->x_a[1][2] =  0.73; //  27.05.2016 
  sci->x_a[0][2] =  -1.0*(-2065.2-27.+55.-29.);  // YT 2016/Jun/14, See Logbook p212-214
  sci->x_a[1][2] =  -1.0*(0.73); //  YT 2016/Jun/14, See Logbook p212-214         
  sci->x_a[2][2] =  0.000000;  // 
  sci->x_a[3][2] =  0.000000;  //                            
  sci->x_a[4][2] =  0.000000;  //                             
  sci->x_a[5][2] =  0.000000;  //                             
  sci->x_a[6][2] =  0.000000;  //  
  
   // index 5 for Sc41
  sci->x_a[0][5] = -5.84328*330.;  //  SC41 calibration ch->mm 
  sci->x_a[1][5] = 0.00558294;  //
  sci->x_a[2][5] = 0.000000;   //
  sci->x_a[3][5] = 0.000000;   //                            
  sci->x_a[4][5] = 0.000000;   //                             
  sci->x_a[5][5] = 0.000000;   //                             
  sci->x_a[6][5] = 0.000000;   //    

  // index 6 for Sc42
  sci->x_a[0][6] = 0.; //   SC42 calibration ch->mm 
  sci->x_a[1][6] = 1.; // 
  sci->x_a[2][6] = 0.000000;  // 
  sci->x_a[3][6] = 0.000000;  //                            
  sci->x_a[4][6] = 0.000000;  //                             
  sci->x_a[5][6] = 0.000000;  //                             
  sci->x_a[6][6] = 0.000000;  //

   // index 7 for Sc43
  sci->x_a[0][7] = 0.; //   SC43 calibration ch->mm 
  sci->x_a[1][7] = 1.; // 
  sci->x_a[2][7] = 0.000000;  // 
  sci->x_a[3][7] = 0.000000;  //                            
  sci->x_a[4][7] = 0.000000;  //                             
  sci->x_a[5][7] = 0.000000;  //                             
  sci->x_a[6][7] = 0.000000;  //

   // index 10 for Sc81
  sci->x_a[0][10] = 0.; //   SC81 calibration ch->mm 
  sci->x_a[1][10] = 1.; // 
  sci->x_a[2][10] = 0.000000;  // 
  sci->x_a[3][10] = 0.000000;  //                            
  sci->x_a[4][10] = 0.000000;  //                             
  sci->x_a[5][10] = 0.000000;  //                             
  sci->x_a[6][10] = 0.000000;  // 


  // TOF
   // For TAC calibration, please only set "factor".
	  // To put some "magic number" offset is very confusing!!
	  // TOF calibration should be done via setting id->id_tofoff2(3)(4)
	  sci->tac_off[0] = 0.0;  //SC21L-R    // fix to 0
	  sci->tac_off[1] = 0.0;  //SC41L-R    // fix to 0
	  sci->tac_off[2] = 0.0;  //SC41L-SC21L   // fix to 0
	  sci->tac_off[3] = 0.0;  //SC41R-SC21R   // fix to 0
	  sci->tac_off[4] = 0.0;  //SC42L-R       // fix to 0
	  sci->tac_off[5] = 0.0;  //SC42L-SC21L   // fix to 0
	  sci->tac_off[6] = 0.0;  //SC42R-SC21R   // fix to 0
	  sci->tac_off[7] = 0.0;  //SC43L-R  // fix to 0
	  sci->tac_off[8] = 0.0;  //SC81L-R  // fix to 0
	  sci->tac_off[9] = 0.0;  //SC81L-SC21L  // fix to 0
	  sci->tac_off[10]= 0.0;  //SC81R-SC21R  // fix to 0

      sci->tac_factor[0]  = 15.097;   //SC21L-R [ps/ch] //TAC factor added on 27-03-2019 //not re-analyzed in 2019/Nov, but is absorbed anyway adjustment of time->pos parameters
	  sci->tac_factor[1]  = 10.678;   //SC41L-R [ps/ch] //TAC factor added on 27-03-2019 //not re-analyzed in 2019/Nov, but is absorbed anyway adjustment of time->pos parameters
	  sci->tac_factor[2]  = 11.11;    //SC41L-SC21L [ps/ch] // mod by Ekawa/tanaka 20-11-2019
	  sci->tac_factor[3]  = 10.94;    //SC41R-SC21R [ps/ch] // mod by Ekawa/Tanaka 20-11-2019
	  sci->tac_factor[9]  = 10.4767; //SC81L21L (2019/Nov)
	  sci->tac_factor[10] = 10.1781; //SC81R21R (2019/Nov)

  
  
  sci->tof_bll2  = 1.;    // not used online [ps/ch]
  sci->tof_brr2  = 1.;    // not used online
  sci->tof_bll3  = 1.;    // not used online 
  sci->tof_brr3  = 1.;    // not used online
  sci->tof_bll4  = 1.;    // not used online 
  sci->tof_brr4  = 1.;    // not used online

  sci->tof_a2 = 0.; // [ps] offset   Tof S41-S21
  sci->tof_a3 = 0.; // [ps] offset   Tof S42-S21
  sci->tof_a4 = 0.; // [ps] offset   Tof S81-S21


  // for multihitTDC
	  sci->mhtdc_factor_ch_to_ns =  0.025;// tp be set in parameter...
	  sci->mhtdc_offset_21l_21r  =  -39.6625+20.0;    
      sci->mhtdc_factor_21l_21r = 62.5341;  // pos = offset + factor*dt
	  sci->mhtdc_offset_41l_41r  =  584.927;          
      sci->mhtdc_factor_41l_41r = 69.4128; // pos = offset + factor*dt
	  sci->mhtdc_offset_42l_42r  =  0.0;              
      sci->mhtdc_factor_42l_42r = 60.0; // pos = offset + factor*dt
	  sci->mhtdc_offset_43l_43r  =  0.0;              
      sci->mhtdc_factor_43l_43r = 60.0; // pos = offset + factor*dt
	  sci->mhtdc_offset_31l_31r  =  0.0;              
      sci->mhtdc_factor_31l_31r = 60.0; // pos = offset + factor*dt
	  sci->mhtdc_offset_81l_81r  =  -410.411;         
      sci->mhtdc_factor_81l_81r = 43.691; // pos = offset + factor*dt
	  sci->mhtdc_offset_41_21  =  178.0; //ns
	  sci->mhtdc_offset_42_21  =  0.0; //ns
	  sci->mhtdc_offset_43_21  =  0.0; //ns
	  sci->mhtdc_offset_31_21  =  0.0; //ns
	  sci->mhtdc_offset_81_21  =  -400.0 + 165.214; //ns


        id->ID_Z_AoverQ_num[0]=5; 
        id->ID_Z_AoverQ_num[1]=5; 
        id->ID_Z_AoverQ_num[2]=5; 
        id->ID_Z_AoverQ_num[3]=5; 
        id->ID_Z_AoverQ_num[4]=5; 

        id->ID_Z_AoverQ[0][0][0]=2.208      ; id->ID_Z_AoverQ[0][0][1]=90;
        id->ID_Z_AoverQ[0][1][0]=2.208      ; id->ID_Z_AoverQ[0][1][1]=40;
        id->ID_Z_AoverQ[0][2][0]=2.220      ; id->ID_Z_AoverQ[0][2][1]=40;
        id->ID_Z_AoverQ[0][3][0]=2.220      ; id->ID_Z_AoverQ[0][3][1]=90;
        id->ID_Z_AoverQ[0][4][0]=2.208      ; id->ID_Z_AoverQ[0][4][1]=90;

        id->ID_Z_AoverQ[1][0][0]=2.208+0.012; id->ID_Z_AoverQ[1][0][1]=1180; 
        id->ID_Z_AoverQ[1][1][0]=2.208+0.012; id->ID_Z_AoverQ[1][1][1]=0; 
        id->ID_Z_AoverQ[1][2][0]=2.220+0.012; id->ID_Z_AoverQ[1][2][1]=0; 
        id->ID_Z_AoverQ[1][3][0]=2.220+0.012; id->ID_Z_AoverQ[1][3][1]=1180; 
        id->ID_Z_AoverQ[1][4][0]=2.208+0.012; id->ID_Z_AoverQ[1][4][1]=1180; 

        id->ID_Z_AoverQ[2][0][0]=2.208+0.024; id->ID_Z_AoverQ[2][0][1]=1180; 
        id->ID_Z_AoverQ[2][1][0]=2.208+0.024; id->ID_Z_AoverQ[2][1][1]=60; 
        id->ID_Z_AoverQ[2][2][0]=2.220+0.024; id->ID_Z_AoverQ[2][2][1]=60; 
        id->ID_Z_AoverQ[2][3][0]=2.220+0.024; id->ID_Z_AoverQ[2][3][1]=1180; 
        id->ID_Z_AoverQ[2][4][0]=2.208+0.024; id->ID_Z_AoverQ[2][4][1]=1180; 

        id->ID_Z_AoverQ[3][0][0]=2.208+0.036; id->ID_Z_AoverQ[3][0][1]=1180; 
        id->ID_Z_AoverQ[3][1][0]=2.208+0.036; id->ID_Z_AoverQ[3][1][1]=60; 
        id->ID_Z_AoverQ[3][2][0]=2.220+0.036; id->ID_Z_AoverQ[3][2][1]=60; 
        id->ID_Z_AoverQ[3][3][0]=2.220+0.036; id->ID_Z_AoverQ[3][3][1]=1180; 
        id->ID_Z_AoverQ[3][4][0]=2.208+0.036; id->ID_Z_AoverQ[3][4][1]=1180; 

        id->ID_Z_AoverQ[4][0][0]=2.208+0.048; id->ID_Z_AoverQ[4][0][1]=1180; 
        id->ID_Z_AoverQ[4][1][0]=2.208+0.048; id->ID_Z_AoverQ[4][1][1]=60; 
        id->ID_Z_AoverQ[4][2][0]=2.220+0.048; id->ID_Z_AoverQ[4][2][1]=60; 
        id->ID_Z_AoverQ[4][3][0]=2.220+0.048; id->ID_Z_AoverQ[4][3][1]=1180; 
        id->ID_Z_AoverQ[4][4][0]=2.208+0.048; id->ID_Z_AoverQ[4][4][1]=1180; 


        id->ID_x2AoverQ_num[0]=5; 
        id->ID_x2AoverQ_num[1]=5; 
        id->ID_x2AoverQ_num[2]=5; 
        id->ID_x2AoverQ_num[3]=5; 
        id->ID_x2AoverQ_num[4]=5; 
        id->ID_x2AoverQ_num[5]=5; 


 id->ID_x2AoverQ[0][0][0]=2.24433; id->ID_x2AoverQ[0][0][1]=42.5864;
 id->ID_x2AoverQ[0][1][0]=2.17429; id->ID_x2AoverQ[0][1][1]=-68.2431;
 id->ID_x2AoverQ[0][2][0]=2.18351; id->ID_x2AoverQ[0][2][1]=-70.9073;
 id->ID_x2AoverQ[0][3][0]=2.2573; id->ID_x2AoverQ[0][3][1]=40.9879;
 id->ID_x2AoverQ[0][4][0]=2.24433;id->ID_x2AoverQ[0][4][1]=42.5864;
 
  id->ID_x2AoverQ[1][0][0]=2.27782; id->ID_x2AoverQ[1][0][1]=58.1797; 
  id->ID_x2AoverQ[1][1][0]=2.18477; id->ID_x2AoverQ[1][1][1]=-66.2442; 
  id->ID_x2AoverQ[1][2][0]=2.19417; id->ID_x2AoverQ[1][2][1]=-69.7005; 
  id->ID_x2AoverQ[1][3][0]=2.29192; id->ID_x2AoverQ[1][3][1]=57.0277; 
  id->ID_x2AoverQ[1][4][0]=2.27782; id->ID_x2AoverQ[1][4][1]=58.1797; 

  id->ID_x2AoverQ[2][0][0]=2.28597; id->ID_x2AoverQ[2][0][1]=40.8986; 
  id->ID_x2AoverQ[2][1][0]=2.19548; id->ID_x2AoverQ[2][1][1]=-69.1244; 
  id->ID_x2AoverQ[2][2][0]=2.21129; id->ID_x2AoverQ[2][2][1]=-69.1244; 
  id->ID_x2AoverQ[2][3][0]=2.30014; id->ID_x2AoverQ[2][3][1]=40.3226; 
  id->ID_x2AoverQ[2][4][0]=2.28597; id->ID_x2AoverQ[2][4][1]=40.8986; 

  id->ID_x2AoverQ[3][0][0]=2.30468; id->ID_x2AoverQ[3][0][1]=41.0484; 
  id->ID_x2AoverQ[3][1][0]=2.20712; id->ID_x2AoverQ[3][1][1]=-73.4407; 
  id->ID_x2AoverQ[3][2][0]=2.22237; id->ID_x2AoverQ[3][2][1]=-73.1567; 
  id->ID_x2AoverQ[3][3][0]=2.32009; id->ID_x2AoverQ[3][3][1]=41.0484; 
  id->ID_x2AoverQ[3][4][0]=2.30468; id->ID_x2AoverQ[3][4][1]=41.0484; 
  
  id->ID_x2AoverQ[4][0][0]=2.32064; id->ID_x2AoverQ[4][0][1]=39.6964; 
  id->ID_x2AoverQ[4][1][0]=2.22332; id->ID_x2AoverQ[4][1][1]=-73.875; 
  id->ID_x2AoverQ[4][2][0]=2.23886; id->ID_x2AoverQ[4][2][1]=-73.517; 
  id->ID_x2AoverQ[4][3][0]=2.33663; id->ID_x2AoverQ[4][3][1]=39.6964; 
  id->ID_x2AoverQ[4][4][0]=2.32064; id->ID_x2AoverQ[4][4][1]=39.6964; 
  
  id->ID_x2AoverQ[5][0][0]=2.26732; id->ID_x2AoverQ[5][0][1]=84.9736; 
  id->ID_x2AoverQ[5][1][0]=2.35488; id->ID_x2AoverQ[5][1][1]=78.52  ; 
  id->ID_x2AoverQ[5][2][0]=2.34538; id->ID_x2AoverQ[5][2][1]=75.078 ; 
  id->ID_x2AoverQ[5][3][0]=2.24458; id->ID_x2AoverQ[5][3][1]=82.0336; 
  id->ID_x2AoverQ[5][4][0]=2.26732; id->ID_x2AoverQ[5][4][1]=84.9736; 
  
   //---- initial value for x4 vs AoQ PID -----//
  id->ID_x4AoverQ_num[0]=5;
  id->ID_x4AoverQ_num[1]=5;
  id->ID_x4AoverQ_num[2]=5;
  id->ID_x4AoverQ_num[3]=5;
  id->ID_x4AoverQ_num[4]=5;

  id->ID_x4AoverQ[0][0][0]=2.24433; id->ID_x4AoverQ[0][0][1]=42.5864;
  id->ID_x4AoverQ[0][1][0]=2.17429; id->ID_x4AoverQ[0][1][1]=-68.2431;
  id->ID_x4AoverQ[0][2][0]=2.18351; id->ID_x4AoverQ[0][2][1]=-70.9073;
  id->ID_x4AoverQ[0][3][0]=2.2573; id->ID_x4AoverQ[0][3][1]=40.9879;
  id->ID_x4AoverQ[0][4][0]=2.24433;id->ID_x4AoverQ[0][4][1]=42.5864;

  id->ID_x4AoverQ[1][0][0]=2.27782; id->ID_x4AoverQ[1][0][1]=58.1797;
  id->ID_x4AoverQ[1][1][0]=2.18477; id->ID_x4AoverQ[1][1][1]=-66.2442;
  id->ID_x4AoverQ[1][2][0]=2.19417; id->ID_x4AoverQ[1][2][1]=-69.7005;
  id->ID_x4AoverQ[1][3][0]=2.29192; id->ID_x4AoverQ[1][3][1]=57.0277;
  id->ID_x4AoverQ[1][4][0]=2.27782; id->ID_x4AoverQ[1][4][1]=58.1797;

  id->ID_x4AoverQ[2][0][0]=2.28597; id->ID_x4AoverQ[2][0][1]=40.8986;
  id->ID_x4AoverQ[2][1][0]=2.19548; id->ID_x4AoverQ[2][1][1]=-69.1244;
  id->ID_x4AoverQ[2][2][0]=2.21129; id->ID_x4AoverQ[2][2][1]=-69.1244;
  id->ID_x4AoverQ[2][3][0]=2.30014; id->ID_x4AoverQ[2][3][1]=40.3226;
  id->ID_x4AoverQ[2][4][0]=2.28597; id->ID_x4AoverQ[2][4][1]=40.8986;

  id->ID_x4AoverQ[3][0][0]=2.30468; id->ID_x4AoverQ[3][0][1]=41.0484;
  id->ID_x4AoverQ[3][1][0]=2.20712; id->ID_x4AoverQ[3][1][1]=-73.4407;
  id->ID_x4AoverQ[3][2][0]=2.22237; id->ID_x4AoverQ[3][2][1]=-73.1567;
  id->ID_x4AoverQ[3][3][0]=2.32009; id->ID_x4AoverQ[3][3][1]=41.0484;
  id->ID_x4AoverQ[3][4][0]=2.30468; id->ID_x4AoverQ[3][4][1]=41.0484;

  id->ID_x4AoverQ[4][0][0]=2.32064; id->ID_x4AoverQ[4][0][1]=39.6964;
  id->ID_x4AoverQ[4][1][0]=2.22332; id->ID_x4AoverQ[4][1][1]=-73.875;
  id->ID_x4AoverQ[4][2][0]=2.23886; id->ID_x4AoverQ[4][2][1]=-73.517;
  id->ID_x4AoverQ[4][3][0]=2.33663; id->ID_x4AoverQ[4][3][1]=39.6964;
  id->ID_x4AoverQ[4][4][0]=2.32064; id->ID_x4AoverQ[4][4][1]=39.6964;

   // gate on Z 
//   id->zgate_low = 85;
//   id->zgate_high = 90;

  //=======
  //  Si
  //======= 
   
  si->si_factor1=5.82775; //CH 03/06/2016
  si->si_offset1=-381.593; //CH 03/06/2016

  si->si_factor2=3.809; //CH 18.10.2014
  si->si_offset2=-529.01; //CH 18.10.2014

  si->si_factor3=3.2596; //CH 21.05.2016
  si->si_offset3=-550.59; //CH 21.05.2016|

  si->si_factor4=3.2596; //CH 21.05.2016
  si->si_offset4=-550.59; //CH 21.05.2016

  for(int i = 0; i<32; i++){
    si->dssd_factor_det1[i]=1.;
    si->dssd_factor_det2[i]=1.;
    si->dssd_factor_det3[i]=1.;
    si->dssd_factor_det4[i]=1.;
    si->dssd_factor_det5[i]=1.;
    si->dssd_factor_det6[i]=1.;

    si->dssd_offset_det1[i]=0.;
    si->dssd_offset_det2[i]=0.;
    si->dssd_offset_det3[i]=0.;
    si->dssd_offset_det4[i]=0.;
    si->dssd_offset_det5[i]=0.;
    si->dssd_offset_det6[i]=0.;
  }
    
  //=========
  //MR-TOF-MS
  //=========
  
  mrtof->MRTOFMS_a=0.069;
  mrtof->MRTOFMS_b=0.71;
  mrtof->MRTOFMS_t0=0;
  mrtof->MRTOFMS_tFRS=0;

  cout << "Focus distance S4: " << frs->dist_focS4 << endl;

  
  cout << "Setup done " << endl;


}
    
    
    
