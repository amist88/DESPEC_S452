#include "TFRSParameter.h"
#include "Riostream.h"
#include "TObjString.h"


TFRSParameter::TFRSParameter() : TGo4Parameter("FRSParameter")
{
  fill_raw_histos = kTRUE;

  //S2
  dist_focS2 = 0;
  dist_MW21 = 0; 
  dist_MW22 = 0;
  dist_SC21 = 0;
  dist_SC22 = 0;
  dist_TPC21 = 0;
  dist_TPC22 = 0;
  dist_TPC23 = 0;
  dist_TPC24 = 0;
  dist_S2target = 0;
  
  //S4
  dist_focS4 = 0;
  dist_SC41 = 0;
  dist_SC42 = 0;
  dist_SC43 = 0;
  dist_MUSIC41 = 0;
  dist_MUSIC42 = 0;
  dist_MUSIC43 = 0;
  dist_TPC41 = 0;
  dist_TPC42 = 0;
  dist_S4target = 0;
  //S8
  dist_focS8 = 0;
  dist_MW81 = 0;
  dist_MW82 = 0;
  dist_SC81 = 0;
  
  //filed
  for(int i=0;i<7;i++) {
    dispersion[i] = 0.;  
    rho0[i] = 0.;  
    bfield[i] = 0.;
    magnification[i] = 0.;
  }
  
  primary_z = 0.;
 
  
}

TFRSParameter::TFRSParameter(const char* name) : TGo4Parameter(name) { 
  
  fill_raw_histos = kTRUE;
    
  // FRS part
  
  dist_focS2		= 2280.0;        // !* Abstand TS3QT33 - Focus S2    !
  dist_MW21		=  604.0;        // !  Abstand TS3QT33 - MW21        !
  dist_MW22		= 1697.0;        // !  Abstand TS3QT33 - MW22        !
  dist_SC21		= 1469.0;        // !  Abstand TS3QT33 - SC21        !
  
  //    !  LAND "finger" scint 
  dist_SC22		= 3740.0;        // !  Abstand TS3QT33 - SC22        !
    
  dist_focS4		= 4290.0;        // !* MW_ZXS4 => ~ 3m 22.09.2003     !
  dist_SC41		= 2769.9;        // !  Abstand HFSQT13 - SC41        !
  dist_SC42		= 3378.0;
  dist_SC43		= 4132.0;		

  dist_MUSIC41	    = 1251.2;        // !  HFSQT13 - MUSIC1              !
  dist_MUSIC42	    = 3030.0;        // !  HFSQT13 - MUSIC2              !
  dist_MUSIC43	    = 3030.0;        // !  HFSQT13 - MUSIC3              !
    
  dist_focS8		= 3789.0;		 // !* Abstand TH4QD12 - Focus S8    !
  dist_MW81		= 1021.0;		 // !  Abstand TH4QD12 - MW81        !
  dist_MW82		= 4500.0;		 // !  Abstand TH4QD12 - MW82        !
  dist_SC81		= 4000.0;		 // !  Abstand TH4QD12 - SC81        !
 
  for(int i=0;i<7;i++) {
    dispersion[i] = 0.;  
    rho0[i] = 0.;  
    bfield[i] = 0.;
    magnification[i] = 0.;
  }
    
  dispersion[0] = -6.474;    // !  FRS Dispersion TA-S2 (Run114)  !
  dispersion[1] =  7.239;    // !  FRS Dispersion S2-S4 (Run114)  !
  magnification[0] = 0.730;  // !  FRS Vergroesserung  TA-S2      !
  magnification[1] = 1.12;   // !  FRS Vergroesserung  S2-S4      !
   
  bfield[0] = 0.59655;      // !  FRS D1 Feld [Tesla]  !
  bfield[1] = 0.59594;      // !  FRS D2 Feld [Tesla]  !
  bfield[2] = 0.6167;       // !  FRS D3 Feld [Tesla]  !
  bfield[3] = 0.6180;       // !  FRS D4 Feld [Tesla]  !
                            // !--------------------------------!
                            // ! effective   Rho1..Rho4	       !
                            // !--------------------------------!
  rho0[0] = 11.26840;       // ! FRS TA/S2 Sollbahnradius [m]   !
  rho0[1] = 11.2794;        // ! FRS S2/S4 Sollbahnradius [m]   !
   
  primary_z = 92.0;

}

TFRSParameter::~TFRSParameter() { 
}

void TFRSParameter::Print(Option_t*) const {	
  std::cout << "Parameter " << GetName()<<":" << std::endl;	
  
  std::cout << "fill_raw_histos = " << fill_raw_histos << std::endl;

  std::cout << "Dist_FocS2="<< dist_focS2<< std::endl;				
  std::cout << "Dist_MW21=" << dist_MW21 << std::endl; 				       
  std::cout << "Dist_MW22=" << dist_MW22 << std::endl; 					
  std::cout << "Dist_SC21=" << dist_SC21 << std::endl; 	
  std::cout << "Dist_SC22=" << dist_SC22 << std::endl; 			
  
  std::cout << "Dist_FocS4="<< dist_focS4<< std::endl;						
  std::cout << "Dist_SC41=" << dist_SC41 << std::endl;					
  std::cout << "Dist_SC42=" << dist_SC42 << std::endl;					
  std::cout << "Dist_SC43=" << dist_SC43 << std::endl;				 
	
  std::cout << "Dist_MUSIC41="  << dist_MUSIC41  << std::endl;  			
  std::cout << "Dist_MUSIC42="  << dist_MUSIC42  << std::endl; 				
  std::cout << "Dist_MUSIC43="  << dist_MUSIC43  << std::endl; 	

  std::cout << "Dist_FocS8="<< dist_focS8<< std::endl; 				
  std::cout << "Dist_MW81=" << dist_MW81 << std::endl; 				
  std::cout << "Dist_MW82=" << dist_MW82 << std::endl; 			
  std::cout << "Dist_SC81=" << dist_SC81 << std::endl;  					
  
  std::cout << "primary_z = " << primary_z << std::endl;

  return ; 
}



Bool_t TFRSParameter::UpdateFrom(TGo4Parameter *pp) { 
  TFRSParameter *from = dynamic_cast<TFRSParameter*> (pp);
  if (from==0) {
    std::cout << "Wrong parameter object: " << pp->ClassName() << std::endl; 
    return kFALSE;   
  }

  dist_focS2=from->dist_focS2;				
  dist_MW21 =from->dist_MW21;					       
  dist_MW22 =from->dist_MW22;					
  dist_SC21 =from->dist_SC21;
  dist_SC22 =from->dist_SC22;					
                                                                    
  dist_focS4=from->dist_focS4;									
  dist_SC41 =from->dist_SC41;					
  dist_SC42 =from->dist_SC42;					
  dist_SC43 =from->dist_SC43;
			
  dist_MUSIC41=from->dist_MUSIC41;			
  dist_MUSIC42=from->dist_MUSIC42;
  dist_MUSIC43=from->dist_MUSIC43;				
                                                            
  dist_focS8=from->dist_focS8;				
  dist_MW81 =from->dist_MW81;					
  dist_MW82 =from->dist_MW82;					
  dist_SC81 =from->dist_SC81;		
             

  for(int i=0;i<7;i++) {
    dispersion[i] = from->dispersion[i];  
    magnification[i] = from->magnification[i];
    rho0[i] = from->rho0[i];  
    bfield[i] = from->bfield[i];
  }
    
  primary_z = from->primary_z;

  std::cout << "Updated Parameter: " << GetName() << std::endl;    
    
  return kTRUE; 
}

ClassImp(TFRSParameter)


// ----------------------------------------------------------
/*
TModParameter::TModParameter() : TGo4Parameter("TModParameter")
{
  Nb_Modules = 0;
  Nb_QDC = 0;
  Nb_ADC = 0;
  Nb_TDC = 0;
  Nb_Scaler = 0;
  Nb_TimeStamp = 0;
  Scaler32bit = 0;
  
  EventFlags.clear();
  Nb_Channels.clear();
  MapCrates.clear();
  ModType.clear();
}

TModParameter::TModParameter(const char* name) : TGo4Parameter(name)
{
  Nb_Modules = 0;
  Nb_QDC = 0;
  Nb_ADC = 0;
  Nb_TDC = 0;
  Nb_Scaler = 0;
  Nb_TimeStamp = 0;
  Scaler32bit = 0;
  
  EventFlags.clear();
  Nb_Channels.clear();
  MapCrates.clear();
  ModType.clear();
} 

TModParameter::~TModParameter()
{ }

void TModParameter::Print(Option_t*) const
{
  std::cout << "Parameter " << GetName() << std::endl;	    
  std::cout<< " Number of Electronic modules :"<<Nb_Modules<<std::endl;

  std::cout<<" N_Mod "<<Nb_Modules<<" qdc:"<<Nb_QDC<<" adc:"<<Nb_ADC<<" tdc:"<<Nb_TDC<<" Sc:"<<Nb_Scaler<<" TS:"<<Nb_TimeStamp<<std::endl;
  std::cout<<" Channels mapping :"<<Nb_Channels.size()<<std::endl;
  for(const auto& it_ch : Nb_Channels)
    std::cout<<" IdMod:"<<it_ch.first<<" Ch:"<<it_ch.second<<std::endl;

  std::cout<<" Crate mapping :"<<std::endl;
  for(const auto& it_crate : MapCrates )
    {
      std::cout<<" ProcID :"<<it_crate.first<<" ";
      for(const auto& it_mod : it_crate.second)
	std::cout<<"{"<<it_mod.first<<", "<<it_mod.second<<"} ";
    }
  std::cout<<" module naming :"<<std::endl;
  for(unsigned int i=0; i<ModType.size();++i)
    std::cout<<"IdMod:"<<i<<" "<<ModType[i]<<std::endl;
  
}

Bool_t TModParameter::UpdateFrom(TGo4Parameter* par)
{
  TModParameter *from = dynamic_cast<TModParameter*>(par);
  if (from==nullptr)
    {
      std::cout << "Wrong parameter object: " << par->ClassName() << std::endl; 
      return kFALSE;   
    }
  Nb_Modules = from->Nb_Modules;
  Nb_QDC = from->Nb_QDC;
  Nb_ADC = from->Nb_ADC;
  Nb_TDC = from->Nb_TDC;
  Nb_Scaler = from->Nb_Scaler;
  Nb_TimeStamp = from->Nb_TimeStamp;
  Scaler32bit = from->Scaler32bit;
  
  EventFlags = from->EventFlags;
  
  Nb_Channels = from->Nb_Channels;
  MapCrates = from->MapCrates;
  ModType = from->ModType;
  
  return kTRUE;
}
void TModParameter::setMap()
{
  std::cout<<" setMap :"<<Maptemp.GetEntries()<<std::endl;
  TIterator* it = Maptemp.MakeIterator();
  while(TObject* key = it->Next())
    {
      Map1* temp = dynamic_cast<Map1*>(Maptemp.GetValue(key));
      TObjString* nametemp = dynamic_cast<TObjString*>(key);
      //std::cout<<nametemp->GetString()<<"\n";
      // for(const auto& it_map : temp->map)
      // 	{
      // 	  std::cout<<"{ "<<it_map.first<<", "<<it_map.second<<"} \n";
      // 	}
      int key_real = nametemp->GetString().Atoi();
      MapCrates.insert(std::pair<int,std::map<int,int> >(key_real,temp->map));

    }
}


ClassImp(TModParameter)
*/

// ----------------------------------------------------------

TMWParameter::TMWParameter() : TGo4Parameter("TMWParameter") {
  for (int i=0;i<13;i++) {
    x_factor[i] = 0.1;
    x_offset[i] = 0.;
    y_factor[i] = 0.1;
    y_offset[i] = 0.;
  }
  for(int i=0;i<5;i++)
    for(int j=0;j<13;j++)
      gain_tdc[i][j] = 0.;
}

TMWParameter::TMWParameter(const char* name) : TGo4Parameter(name) {
  x_factor[0]  = 0.0696;    //! (~2ns/mm) ! meas. 238U 06-JUL-03 
  x_factor[1]  = 0.0732;    //! (2ns/mm)
  x_factor[2]  = 0.0732;    //! (2ns/mm)
  x_factor[3]  = 0.0732;    //! (2ns/mm)
  x_factor[4]  = 0.0751;    //! 
  x_factor[5]  = 0.07829;   //! 
  x_factor[6]  = 0.0732;    //!  
  x_factor[7]  = 0.0732;    //! 
  x_factor[8]  = 0.0732;    //! 
  x_factor[9]  = 0.0732;    //! (2ns/mm)
  x_factor[10] = 0.0366;    //! (4ns/mm) 
  x_factor[11] = 0.0732;    //! (2ns/mm)
  x_factor[12] = 0.0732;    //! (2ns/mm)

  x_offset[0]  =  0.0;      //
  x_offset[1]  =  0.0;      //
  x_offset[2]  =  0.0;      //
  x_offset[3]  =  0.0;      //
  x_offset[4]  =  0.0;      //
  x_offset[5]  =  0.0;      //
  x_offset[6]  =  0.0;      //
  x_offset[7]  =  0.0;      //
  x_offset[8]  =  0.0;      // 
  x_offset[9]  =  0.0;      // 
  x_offset[10] =  0.0;      // 
  x_offset[11] =  0.0;      // 
  x_offset[12] =  0.0;      // 

  y_factor[0]  = 0.0696;    //! (2ns/mm) ! =x 238U 06-JUL-03 
  y_factor[1]  = 0.0732;
  y_factor[2]  = 0.0732;
  y_factor[3]  = 0.0732;
  y_factor[4]  = 0.0732; 
  y_factor[5]  = 0.0751; 
  y_factor[6]  = 0.07829;  
  y_factor[7]  = 0.0732; 
  y_factor[8]  = 0.0732;
  y_factor[9]  = 0.0732;
  y_factor[10] = 0.0366;     //! (4ns/mm)
  y_factor[11] = 0.0732; 
  y_factor[12] = 0.0732;

  y_offset[0]  = 0.0;
  y_offset[1]  = 0.0;
  y_offset[2]  = 0.0;
  y_offset[3]  = 0.0;
  y_offset[4]  = 0.0;
  y_offset[5]  = 0.0;
  y_offset[6]  = 0.0;
  y_offset[7]  = 0.0;
  y_offset[8]  = 0.0;
  y_offset[9]  = 0.0;
  y_offset[10] = 0.0;
  y_offset[11] = 0.0;
  y_offset[12] = 0.0;

  for(int i=0;i<5;i++)
    for(int j=0;j<13;j++)
      gain_tdc[i][j] = 0.;
} 

TMWParameter::~TMWParameter() {
}

void TMWParameter::Print(Option_t*) const {
  std::cout << "Parameter " << GetName() << std::endl;	    
   
  for(int i=0;i<13;i++) 
    std::cout << "x_factor[" << i << "]= " << x_factor[i] 
	      << "  x_offset[" << i << "]= " << x_offset[i] << std::endl;
  for(int i=0;i<13;i++) 
    std::cout << "y_factor[" << i << "]= " << y_factor[i]
	      << "  y_offset[" << i << "]= " << y_offset[i] << std::endl;

  return ;
}

Bool_t TMWParameter::UpdateFrom(TGo4Parameter* par) {
  TMWParameter *from = dynamic_cast<TMWParameter*> (par);
  if (from==0) {
    std::cout << "Wrong parameter object: " << par->ClassName() << std::endl; 
    return kFALSE;   
  }
   
  for(int i=0;i<13;i++) {
    x_factor[i] = from->x_factor[i];
    x_offset[i] = from->x_offset[i];
    y_factor[i] = from->y_factor[i];
    y_offset[i] = from->y_offset[i];
  }

  for(int i=0;i<5;i++)
    for(int j=0;j<13;j++)
      gain_tdc[i][j] = from->gain_tdc[i][j];
   
  return kTRUE;
}

ClassImp(TMWParameter)


// ----------------------------------------------------------
// TPC Parameters
  
TTPCParameter::TTPCParameter() : TGo4Parameter("TTPCParameter") {
//     for(int i=0;i<8;i++){
//     for(int j=0;j<2;j++){
//         lim_timeref[i][j] = from->lim_timeref[i][j];
//     }
//   }
  //TPC 1 at S2 (TPC 21) in vaccuum
  x_factor[0][0] = 0.070623;
  x_factor[0][1] = 0.07248;
  y_factor[0][0] =-0.036;
  y_factor[0][1] =-0.035;
  y_factor[0][2] =-0.035;
  y_factor[0][3] =-0.036; 
	 
  x_offset[0][0] =-0.5;
  x_offset[0][1] =-1.058;
  y_offset[0][0] = 39.3;
  y_offset[0][1] = 38.6;
  y_offset[0][2] = 39.6;
  y_offset[0][3] = 40.0;

  //TPC 2 at S2 (TPC 22) in vaccuum
  x_factor[1][0] = 0.0716;
  x_factor[1][1] = 0.070329;
  y_factor[1][0] = -0.035;
  y_factor[1][1] = -0.035;
  y_factor[1][2] = -0.034;
  y_factor[1][3] = -0.034;  

  x_offset[1][0] = -0.81;
  x_offset[1][1] =  1.9;
  y_offset[1][0] =  37.4;
  y_offset[1][1] =  37.1;
  y_offset[1][2] =  36.1;
  y_offset[1][3] =  35.7;

  //TPC 3 at S2 (TPC 23) in air //TPC3   //23/04/08 VALUE SET ACCORDING TO CALIBRATION
  x_factor[2][0] = 0.070155;  //L-R time 0
  x_factor[2][1] = 0.069089;  //L-R time 1
  y_factor[2][0] = -0.0373246; //drift time 0
  y_factor[2][1] = -0.0379154; //drift time 1
  y_factor[2][2] = -0.0382496; //drift time 2
  y_factor[2][3] = -0.0378421; //drift time 3
	 
  x_offset[2][0] = -3.3;
  x_offset[2][1] = -1.15;
  y_offset[2][0] = 46.9423;
  y_offset[2][1] = 46.8563;
  y_offset[2][2] = 47.118;
  y_offset[2][3] = 46.9655;

  //TPC 4 at S2 (TPC 24) in air
  x_factor[3][0] = 0.070797;
  x_factor[3][1] = 0.069579;
  y_factor[3][0] = -0.0379319;
  y_factor[3][1] = -0.0388858;
  y_factor[3][2] = -0.0377925;
  y_factor[3][3] = -0.0383422; 
	
  x_offset[3][0] = -0.9;
  x_offset[3][1] = 2.88;
  y_offset[3][0] = 55.5394;
  y_offset[3][1] = 55.781;
  y_offset[3][2] = 55.5143;
  y_offset[3][3] = 55.5203;
  

  //TPC 5 at S4 (TPC 41) in air  
  x_factor[4][0] = 0.073641;
  x_factor[4][1] = 0.075485;
  y_factor[4][0] =-0.041;
  y_factor[4][1] =-0.040;
  y_factor[4][2] =-0.0396;
  y_factor[4][3] =-0.0387; 
  
  x_offset[4][0] = 2.79;
  x_offset[4][1] =-0.83;
  y_offset[4][0] = 44.2;
  y_offset[4][1] = 43.2;
  y_offset[4][2] = 41.4;
  y_offset[4][3] = 40.6;
  

  //TPC 6 at S4 (TPC 42) in air 
  x_factor[5][0] = 0.07755;
  x_factor[5][1] = 0.07683;
  y_factor[5][0] =0.040;
  y_factor[5][1] =0.039;
  y_factor[5][2] =0.039;
  y_factor[5][3] =0.039;

  x_offset[5][0] = -0.15221;
  x_offset[5][1] = 1.5;
  y_offset[5][0] = -41-6;
  y_offset[5][1] =-39.2-6;
  y_offset[5][2] =-39.5-6;
  y_offset[5][3] =-40.8-6;


  //TPC at S3 (TPC 31)
  x_factor[6][0] = 0.07755;
  x_factor[6][1] = 0.07683;
  y_factor[6][0] =0.040;
  y_factor[6][1] =0.039;
  y_factor[6][2] =0.039;
  y_factor[6][3] =0.039;

  x_offset[6][0] = -0.15221;
  x_offset[6][1] = 1.5;
  y_offset[6][0] = -41-6;
  y_offset[6][1] =-39.2-6;
  y_offset[6][2] =-39.5-6;
  y_offset[6][3] =-40.8-6;
 
  
  for(int i=0;i<32;i++){
    tdc1_factor[i]=1;
    tdc2_factor[i]=1;
  }

  for(int i=0;i<7;i++){
    //    tdc_reference[i]=0;
  }
  
}


TTPCParameter::TTPCParameter(const Text_t * name) : TGo4Parameter(name) {



  //TPC 1 at S2 (TPC 21) in vaccuum
  x_factor[0][0] = 0.070623;
  x_factor[0][1] = 0.07248;
  y_factor[0][0] =-0.036;
  y_factor[0][1] =-0.035;
  y_factor[0][2] =-0.035;
  y_factor[0][3] =-0.036; 
	 
  x_offset[0][0] =-0.5;
  x_offset[0][1] =-1.058;
  y_offset[0][0] = 39.3;
  y_offset[0][1] = 38.6;
  y_offset[0][2] = 39.6;
  y_offset[0][3] = 40.0;

  //TPC 2 at S2 (TPC 22) in vaccuum
  x_factor[1][0] = 0.0716;
  x_factor[1][1] = 0.070329;
  y_factor[1][0] = -0.035;
  y_factor[1][1] = -0.035;
  y_factor[1][2] = -0.034;
  y_factor[1][3] = -0.034;  

  x_offset[1][0] = -0.81;
  x_offset[1][1] =  1.9;
  y_offset[1][0] =  37.4;
  y_offset[1][1] =  37.1;
  y_offset[1][2] =  36.1;
  y_offset[1][3] =  35.7;

  //TPC 3 at S2 (TPC 23) in air //TPC3   //23/04/08 VALUE SET ACCORDING TO CALIBRATION
  x_factor[2][0] = 0.070155;  //L-R time 0
  x_factor[2][1] = 0.069089;  //L-R time 1
  y_factor[2][0] = -0.0373246; //drift time 0
  y_factor[2][1] = -0.0379154; //drift time 1
  y_factor[2][2] = -0.0382496; //drift time 2
  y_factor[2][3] = -0.0378421; //drift time 3
	 
  x_offset[2][0] = -3.3;
  x_offset[2][1] = -1.15;
  y_offset[2][0] = 46.9423;
  y_offset[2][1] = 46.8563;
  y_offset[2][2] = 47.118;
  y_offset[2][3] = 46.9655;

  //TPC 4 at S2 (TPC 24) in air
  x_factor[3][0] = 0.070797;
  x_factor[3][1] = 0.069579;
  y_factor[3][0] = -0.0379319;
  y_factor[3][1] = -0.0388858;
  y_factor[3][2] = -0.0377925;
  y_factor[3][3] = -0.0383422; 
	
  x_offset[3][0] = -0.9;
  x_offset[3][1] = 2.88;
  y_offset[3][0] = 55.5394;
  y_offset[3][1] = 55.781;
  y_offset[3][2] = 55.5143;
  y_offset[3][3] = 55.5203;
  

  //TPC 5 at S4 (TPC 41) in air  
  x_factor[4][0] = 0.073641;
  x_factor[4][1] = 0.075485;
  y_factor[4][0] =-0.041;
  y_factor[4][1] =-0.040;
  y_factor[4][2] =-0.0396;
  y_factor[4][3] =-0.0387; 
  
  x_offset[4][0] = 2.79;
  x_offset[4][1] =-0.83;
  y_offset[4][0] = 44.2;
  y_offset[4][1] = 43.2;
  y_offset[4][2] = 41.4;
  y_offset[4][3] = 40.6;
  

  //TPC 6 at S4 (TPC 42) in air 
  x_factor[5][0] = 0.07755;
  x_factor[5][1] = 0.07683;
  y_factor[5][0] =0.040;
  y_factor[5][1] =0.039;
  y_factor[5][2] =0.039;
  y_factor[5][3] =0.039;

  x_offset[5][0] = -0.15221;
  x_offset[5][1] = 1.5;
  y_offset[5][0] = -41-6;
  y_offset[5][1] =-39.2-6;
  y_offset[5][2] =-39.5-6;
  y_offset[5][3] =-40.8-6;


  //TPC at S3 (TPC 31)
  x_factor[6][0] = 0.07755;
  x_factor[6][1] = 0.07683;
  y_factor[6][0] =0.040;
  y_factor[6][1] =0.039;
  y_factor[6][2] =0.039;
  y_factor[6][3] =0.039;

  x_offset[6][0] = -0.15221;
  x_offset[6][1] = 1.5;
  y_offset[6][0] = -41-6;
  y_offset[6][1] =-39.2-6;
  y_offset[6][2] =-39.5-6;
  y_offset[6][3] =-40.8-6;


  for(int i=0;i<32;i++){
    tdc1_factor[i]=1;
    tdc2_factor[i]=1;
  }

   for(int i=0;i<7;i++){
     //tdc_reference[i]=0;
  }
  
} 

TTPCParameter::~TTPCParameter() {
}

void TTPCParameter::Print(Option_t*) const {
  std::cout << "Parameter " << GetName() << std::endl;       
  
  for(int i=0;i<7;i++) 
    for(int j=0;j<2;j++){ 
      std::cout << "x_factor[" << i << "][" << j <<"]= " << x_factor[i][j] 
		<< "  x_offset[" << i << "][" << j <<"]= " << x_offset[i][j] << std::endl;
    }
  return ;
}

Bool_t TTPCParameter::UpdateFrom(TGo4Parameter* par) {
  TTPCParameter *from = dynamic_cast<TTPCParameter*> (par);
  if (from==0) {
    std::cout << "Wrong parameter object: " << par->ClassName() << std::endl; 
    return kFALSE;   
  }
  
  for(int i=0;i<7;i++) {
    for(int j=0;j<2;j++){ 
      x_factor[i][j] = from->x_factor[i][j];
      x_offset[i][j] = from->x_offset[i][j];
    } 
    for(int j=0;j<4;j++){ 
      y_factor[i][j] = from->y_factor[i][j];
      y_offset[i][j] = from->y_offset[i][j];
    }
  }

  for(int i=0;i<32;i++){
    tdc1_factor[i]=from->tdc1_factor[i];
    tdc2_factor[i]=from->tdc2_factor[i];
  }

  for (int i=0;i<7;i++){
    //tdc_reference[i]=from->tdc_reference[i];
  }

  return kTRUE;
}


// ----------------------------------------------------------

TMUSICParameter::TMUSICParameter() : TGo4Parameter("TMUSICParameter") {
  for (int i=0;i<8;i++){
    e1_off[i] = 0;
    e1_gain[i] = 1.;
    e2_off[i] = 0;
    e2_gain[i] = 1.;
    e3_off[i] = 0;
    e3_gain[i] = 1.;
    exclude_de1_adc_channel[i] = kFALSE;//true means exlude. 
    exclude_de2_adc_channel[i] = kFALSE;
    exclude_de3_adc_channel[i] = kFALSE;
  }

  b_selfcorr1 = kFALSE;  
    
  for(int i=0;i<7;i++)
    pos_a1[i] = 0.;
}

TMUSICParameter::TMUSICParameter(const char* name) : TGo4Parameter(name) {
  //   e1_off[0]  = 133;  //          ! ADC offset MUSIC1 A1       !
  //   e1_off[1]  =  95;  //          ! ADC offset MUSIC1 A2       !
  //   e1_off[2]  = 123;  //          ! ADC offset MUSIC1 A3       !
  //   e1_off[3]  = 150;  //          ! ADC offset MUSIC1 A4       !
  //   e1_off[4]  = 117;  //          ! ADC offset MUSIC1 A5       !
  //   e1_off[5]  = 130;  //          ! ADC offset MUSIC1 A6       !
  //   e1_off[6]  = 136;  //          ! ADC offset MUSIC1 A7       !
  //   e1_off[7]  =  86;  //          ! ADC offset MUSIC1 A8       !
   
  e1_off[0]  = 0;  //          ! ADC offset MUSIC1 A1       !
  e1_off[1]  = 0;  //          ! ADC offset MUSIC1 A2       !
  e1_off[2]  = 0;  //          ! ADC offset MUSIC1 A3       !
  e1_off[3]  = 0;  //          ! ADC offset MUSIC1 A4       !
  e1_off[4]  = 0;  //          ! ADC offset MUSIC1 A5       !
  e1_off[5]  = 0;  //          ! ADC offset MUSIC1 A6       !
  e1_off[6]  = 0;  //          ! ADC offset MUSIC1 A7       !
  e1_off[7]  = 0;  //          ! ADC offset MUSIC1 A8       !

  e1_gain[0]  = 1.0368;  //      ! ADC gain MUSIC1 A1       !
  e1_gain[1]  = 1.0378;  //      ! ADC gain MUSIC1 A2       !
  e1_gain[2]  = 1.0181;  //      ! ADC gain MUSIC1 A3       !
  e1_gain[3]  = 1.0000;  //      ! ADC gain MUSIC1 A4       !
  e1_gain[4]  = 1.0152;  //      ! ADC gain MUSIC1 A5       !
  e1_gain[5]  = 1.0200;  //      ! ADC gain MUSIC1 A6       !
  e1_gain[6]  = 1.0220;  //      ! ADC gain MUSIC1 A7       !
  e1_gain[7]  = 1.0249;  //      ! ADC gain MUSIC1 A8       !

  e3_off[0]  = 0;  //          ! ADC offset MUSIC2 A1       !
  e3_off[1]  = 0;  //          ! ADC offset MUSIC2 A2       !
  e3_off[2]  = 0;  //          ! ADC offset MUSIC2 A3       !
  e3_off[3]  = 0;  //          ! ADC offset MUSIC2 A4       !
  e3_off[4]  = 0;  //          ! ADC offset MUSIC2 A5       !
  e3_off[5]  = 0;  //          ! ADC offset MUSIC2 A6       !
  e3_off[6]  = 0;  //          ! ADC offset MUSIC2 A7       !
  e3_off[7]  = 0;  //          ! ADC offset MUSIC2 A8       !

  e3_gain[0]  = 1.0135;  //      ! ADC gain MUSIC2 A1       !
  e3_gain[1]  = 1.5205;  //      ! ADC gain MUSIC2 A2       !
  e3_gain[2]  = 1.1795;  //      ! ADC gain MUSIC2 A3       !
  e3_gain[3]  = 1.1040;  //      ! ADC gain MUSIC2 A4       !
  e3_gain[4]  = 1.0000;  //      ! ADC gain MUSIC2 A5       !
  e3_gain[5]  = 1.0243;  //      ! ADC gain MUSIC2 A6       !
  e3_gain[6]  = 1.0529;  //      ! ADC gain MUSIC2 A7       !
  e3_gain[7]  = 1.2172;  //      ! ADC gain MUSIC2 A8       !


  e2_off[0]  = 0;  //          ! ADC offset MUSIC3 A1       !
  e2_off[1]  = 0;  //          ! ADC offset MUSIC3 A2       !
  e2_off[2]  = 0;  //          ! ADC offset MUSIC3 A3       !
  e2_off[3]  = 0;  //          ! ADC offset MUSIC3 A4       ! 
  e2_off[4]  = 0;  //          ! ADC offset MUSIC3 A5       !
  e2_off[5]  = 0;  //          ! ADC offset MUSIC3 A6       !
  e2_off[6]  = 0;  //          ! ADC offset MUSIC3 A7       !
  e2_off[7]  = 0;  //          ! ADC offset MUSIC3 A8       !
  

  e2_gain[0]  = 1.;  //          ! ADC gain MUSIC3 A1       !
  e2_gain[1]  = 1.;  //          ! ADC gain MUSIC3 A2       !
  e2_gain[2]  = 1.;  //          ! ADC gain MUSIC3 A3       !
  e2_gain[3]  = 1.;  //          ! ADC gain MUSIC3 A4       !
  e2_gain[4]  = 1.;  //          ! ADC gain MUSIC3 A5       !
  e2_gain[5]  = 1.;  //          ! ADC gain MUSIC3 A6       !
  e2_gain[6]  = 1.;  //          ! ADC gain MUSIC3 A7       !
  e2_gain[7]  = 1.;  //          ! ADC gain MUSIC3 A8       !

  b_selfcorr1 = kFALSE;

   
  //   pos_a1[0] = 2027.98;      //   ! 22 sep03 calib
  pos_a1[0] = 1.0;          //   !
  pos_a1[1] = 0.0;          //   ! 
  pos_a1[2] = 0.0;          //	  ! 
  pos_a1[3] = 0.0;          //   !
  pos_a1[4] = 0.0;          //   !
  pos_a1[5] = 0.0;          //   !
  pos_a1[6] = 0.0;          //   !
  std::cout << "set MUSIC parameters" << std::endl;

} 


TMUSICParameter::~TMUSICParameter() {
}

void TMUSICParameter::Print(Option_t*) const {
  std::cout << "Parameter " << GetName() << std::endl;
   
  for (int i=0;i<8;i++){
    std::cout << "e1_off[" << i << "] = " << e1_off[i] << std::endl;
    std::cout << "e1_gain[" << i << "] = " << e1_gain[i] << std::endl;
  }
  std::cout << "b_selfcorr1 = " << b_selfcorr1 << std::endl;
    
  for (int i=0;i<7;i++)
    std::cout << "pos_a1[" << i << "] = " << pos_a1[i] << std::endl; 
        
  return ;
}

Bool_t TMUSICParameter::UpdateFrom(TGo4Parameter* par) {
  TMUSICParameter *from = dynamic_cast<TMUSICParameter*> (par);
  if (from==0) {
    std::cout << "Wrong parameter object: " << par->ClassName() << std::endl; 
    return kFALSE;   
  }
   
  for (int i=0;i<8;i++){
    e1_off[i] = from->e1_off[i];
    e1_gain[i] = from->e1_gain[i];
    e2_off[i] = from->e2_off[i];
    e2_gain[i] = from->e2_gain[i];
    e3_off[i] = from->e3_off[i];
    e3_gain[i] = from->e3_gain[i];
  }
  b_selfcorr1 = from->b_selfcorr1;
    
  for (int i=0;i<7;i++)
    pos_a1[i] = from->pos_a1[i];
   
  return kTRUE;
}

ClassImp(TMUSICParameter)




// ----------------------------------------------------------

TSCIParameter::TSCIParameter() : TGo4Parameter("TSCIParameter") {
  for(int i=0;i<12;i++) {
    le_a[0][i] = 0.;
    le_a[1][i] = 1.;
    re_a[0][i] = 0.;
    re_a[1][i] = 1.;
  }

  for(int i=0;i<3;i++) {
    le_veto_a[0][i] = 0.;
    le_veto_a[1][i] = 1.;
    re_veto_a[0][i] = 0.;
    re_veto_a[1][i] = 1.;
  }
 
  for(int i=0;i<16;i++){
    tac_factor[i] =1.0;
    tac_off[i] = 0.;
  }
   
  for(int i=0;i<7;i++)
    for(int j=0;j<12;j++)
      x_a[i][j] = 0.;
        
  for(int i=0;i<7;i++)
    y5_a[i] = 0.;
      
  tof_bll2 = 1.0;        /* [ps/channel]             */
  tof_brr2 = 1.0;        /* [ps/channel]             */
  tof_a2   = 0.0;        /* shift [ps]               */
  tof_bll3 = 1.0;        /* [ps/channel]             */
  tof_brr3 = 1.0;        /* [ps/channel]             */
  tof_a3   = 0.0;        /* shift [ps]               */
  tof_bll4 = 1.0;        /* [ps/channel]             */
  tof_brr4 = 1.0;        /* [ps/channel]             */
  tof_a4   = 0.0;        /* shift [ps]               */
  tof_bll5 = 1.0;        /* [ps/channel]             */
  tof_brr5 = 1.0;        /* [ps/channel]             */
  tof_a5   = 0.0;        /* shift [ps]               */
  tof_bll6 = 1.0;        /* [ps/channel]             */
  tof_brr6 = 1.0;        /* [ps/channel]             */
  tof_a6   = 0.0;        /* shift [ps]               */
}

TSCIParameter::TSCIParameter(const char* name) : TGo4Parameter(name) {
  for(int i=0;i<12;i++) {
    le_a[0][i] = 0.;
    le_a[1][i] = 1.;
    re_a[0][i] = 0.;
    re_a[1][i] = 1.;
  }

  for(int i=0;i<3;i++) {
    le_veto_a[0][i] = 0.;
    le_veto_a[1][i] = 1.;
    re_veto_a[0][i] = 0.;
    re_veto_a[1][i] = 1.;
  }


  tac_off[0] = 0.;  //SC21L-R
  tac_off[1] = 0.;  //SC41L-R
  tac_off[2] = 0.;  //SC41L-SC21L
  tac_off[3] = 0.;  //SC41R-SC21R
  tac_off[4] = 0.;  //SC42L-R
  tac_off[5] = 0.;  //SC42L-SC21L
  tac_off[6] = 0.;  //SC42R-SC21R
  tac_off[7] = 0.;  //SC43L-R
  tac_off[8] = 0.;  //SC81L-R
  tac_off[9] = 0.;  //SC81L-SC21L
  tac_off[10] = 0.; //SC81R-SC21R
  tac_off[11] = 0.;  //SC22L-22R
  tac_off[12] = 0.; //SC41L-SC22L
  tac_off[13] = 0.; //SC41R-SC22R
  tac_off[14] = 0.; //SC81L-SC22L
  tac_off[15] = 0.; //SC81R-SC22R
  

  tac_factor[0] = 5.571;    //SC21L-R [ps/ch]
  tac_factor[1] = 5.604;    //SC41L-R
  tac_factor[2] = 16.809;  //SC41L-SC21L
  tac_factor[3] = 17.149;  //SC41R-SC21R
  tac_factor[4] = 1.;    //SC42L-R
  tac_factor[5] = 1.;    //SC42L-SC21L
  tac_factor[6] = 1.;    //SC42R-SC21R
  tac_factor[7] = 1.;      //SC43L-R
  tac_factor[8] = 1.;      //SC81L-R
  tac_factor[9] = 1.;      //SC81L-SC21L
  tac_factor[10] = 1.;     //SC81R-SC21R
  tac_factor[11] = 1.;     //SC22L-R
  tac_factor[12] = 1.;     //SC41L-SC22L
  tac_factor[13] = 1.;     //SC41R-SC22R
  tac_factor[14] = 1.;     //SC81L-SC22L
  tac_factor[15] = 1.;     //SC81R-SC22R


  for(int i=0;i<7;i++)
    for(int j=0;j<12;j++)
      x_a[i][j] = 0.;
   
  x_a[0][2] =  672.101;   // ! SC21 calibration ch->mm    !
  x_a[1][2] =  -0.371043; // ! 22sep03                    !
  x_a[2][2] =  -2.68163e-7;//! slope from eyeballing width!
  x_a[3][2] =  0.000000; // !                            !
  x_a[4][2] =  0.000000; // !                            !
  x_a[5][2] =  0.000000; // !                            !
  x_a[6][2] =  0.000000; // !                            !

  x_a[0][3] =   781.;    // ! SC21 calibration ch->mm    !
  x_a[1][3] =  -0.4483;  // ! offset 23-Jul-03           !
  x_a[2][3] =  0.000000; // ! slope from eyeballing width!
  x_a[3][3] =  0.000000; // !                            !
  x_a[4][3] =  0.000000; // !                            !
  x_a[5][3] =  0.000000; // !                            !
  x_a[6][3] =  0.000000; // !                            !

  x_a[0][5] =  282.097;  // ! SC41 calibration ch->mm    !
  x_a[1][5] = -5.09955e-4;  // ! offset 23-Jul-03        !
  x_a[2][5] = -7.15792e-5; // ! coeffs guessed!          !
  x_a[3][5] = 0.000000;  // !                            !
  x_a[4][5] = 0.000000;  // !                            !
  x_a[5][5] = 0.000000;  // !                            !
  x_a[6][5] = 0.000000;  // !                            !

  x_a[0][6] =    752;   // ! SC42 calibration ch->mm   !
  x_a[1][6] =   -0.4;   // !                           !
  x_a[2][6] = 0.000000; // !                           !
  x_a[3][6] = 0.000000; // !                           !
  x_a[4][6] = 0.000000; // !                           !
  x_a[5][6] = 0.000000; // !                           !
  x_a[6][6] = 0.000000; // !                           !

  x_a[0][7] =    752;   // ! SC43 calibration ch->mm   !
  x_a[1][7] =   -0.4;   // !                           !
  x_a[2][7] = 0.000000; // !                           !
  x_a[3][7] = 0.000000; // !                           !
  x_a[4][7] = 0.000000; // !                           !
  x_a[5][7] = 0.000000; // !                           !
  x_a[6][7] = 0.000000; // !                           !

  x_a[0][10] =    752;   // ! SC81 calibration ch->mm   !
  x_a[1][10] =   -0.4;   // !                           !
  x_a[2][10] = 0.000000; // !                           !
  x_a[3][10] = 0.000000; // !                           !
  x_a[4][10] = 0.000000; // !                           !
  x_a[5][10] = 0.000000; // !                           !
  x_a[6][10] = 0.000000; // !                           !
     
  y5_a[0] = 164.9;        // ! SC41 calibration ch->mm    !
  y5_a[1] = -0.0985331;        // ! offset 23-Jul-03           ! 
  y5_a[2] = 0.000000;    // ! coeffs guessed!            !
  y5_a[3] = 0.000000;    // !                            !
  y5_a[4] = 0.000000;    // !                            !
  y5_a[5] = 0.000000;    // !                            !
  y5_a[6] = 0.000000;    // !                            !
   
  tof_bll2 = 1.;        //        
  tof_brr2 = 1.;        //         
  tof_a2   = 0.0;       // 
  tof_bll3 = 1.;        //        
  tof_brr3 = 1.;        //
  tof_a3   = 0.0;       //
  tof_bll4 = 1.;        //        
  tof_brr4 = 1.;        //
  tof_a4   = 0.0;       //
  tof_bll5 = 1.;        //
  tof_brr5 = 1.;        //
  tof_a5 = 0.0;         //
  tof_bll6 = 1.;        //
  tof_brr6 = 1.;        //
  tof_a6 = 0.0;          //
} 

TSCIParameter::~TSCIParameter() {
}

void TSCIParameter::Print(Option_t*) const {
  std::cout << "Parameter " << GetName() << std::endl;	    
   
  for(int i=0;i<12;i++) 
    std::cout << "le_a[0]["<<i<<"] = " << le_a[0][i] << 
      "    le_a[1]["<<i<<"] = " << le_a[1][i] << std::endl;
              
  for(int i=0;i<12;i++) 
    std::cout << "re_a[0]["<<i<<"] = " << re_a[0][i] << 
      "  re_a[1]["<<i<<"] = " << re_a[1][i] << std::endl;

  for(int i=0;i<3;i++) 
    std::cout << "le_veto_a[0]["<<i<<"] = " << le_veto_a[0][i] << 
      "    le_veto_a[1]["<<i<<"] = " << le_veto_a[1][i] << std::endl;
              
  for(int i=0;i<3;i++) 
    std::cout << "re_veto_a[0]["<<i<<"] = " << re_veto_a[0][i] << 
      "  re_veto_a[1]["<<i<<"] = " << re_veto_a[1][i] << std::endl;
   
  for(int i=0;i<16;i++) 
    std::cout << "tac_factor["<<i<<"] = " << tac_factor[i] << std::endl;

  for(int i=0;i<16;i++) 
    std::cout << "tac_off["<<i<<"] = " << tac_off[i] << std::endl;
           
  for(int i=0;i<7;i++)
    for(int j=0;j<12;j++)
      std::cout << "x_a["<<i<<"]["<<j<<"] = "  << x_a[i][j] << std::endl;
   
  for(int i=0;i<7;i++)
    std::cout << "y5_a[" << i << "] = " << y5_a[i] << std::endl;
     
  std::cout << "tof_bll2 = " << tof_bll2 << std::endl;
  std::cout << "tof_brr2 = " << tof_brr2 << std::endl;
  std::cout << "tof_a2   = " << tof_a2   << std::endl;
  std::cout << "tof_bll3 = " << tof_bll3 << std::endl;
  std::cout << "tof_brr3 = " << tof_brr3 << std::endl;
  std::cout << "tof_a3   = " << tof_a3   << std::endl;
  std::cout << "tof_bll4 = " << tof_bll4 << std::endl;
  std::cout << "tof_brr4 = " << tof_brr4 << std::endl;
  std::cout << "tof_a4   = " << tof_a4   << std::endl;
  std::cout << "tof_bll5 = " << tof_bll5 << std::endl;
  std::cout << "tof_brr5 = " << tof_brr5 << std::endl;
  std::cout << "tof_a5   = " << tof_a5   << std::endl;
  std::cout << "tof_bll6 = " << tof_bll6 << std::endl;
  std::cout << "tof_brr6 = " << tof_brr6 << std::endl;
  std::cout << "tof_a6   = " << tof_a6   << std::endl;
              
  return ;
}

Bool_t TSCIParameter::UpdateFrom(TGo4Parameter* par) {
  TSCIParameter *from = dynamic_cast<TSCIParameter*> (par);
  if (from==0) {
    std::cout << "Wrong parameter object: " << par->ClassName() << std::endl; 
    return kFALSE;   
  }
   
  for(int i=0;i<12;i++) {
    le_a[0][i] = from->le_a[0][i];
    le_a[1][i] = from->le_a[1][i];
    re_a[0][i] = from->re_a[0][i];
    re_a[1][i] = from->re_a[1][i];
  }

  for(int i=0;i<3;i++) {
    le_veto_a[0][i] = from->le_veto_a[0][i];
    le_veto_a[1][i] = from->le_veto_a[1][i];
    re_veto_a[0][i] = from->re_veto_a[0][i];
    re_veto_a[1][i] = from->re_veto_a[0][i];
  }


  for(int i=0;i<16;i++){
    tac_factor[i] = from->tac_factor[i];
    tac_off[i] = from->tac_off[i];
  }

  for(int i=0;i<7;i++)
    for(int j=0;j<12;j++)
      x_a[i][j] = from->x_a[i][j];
        
  for(int i=0;i<7;i++)
    y5_a[i] = from->y5_a[i];
      
  tof_bll2 = from->tof_bll2;
  tof_brr2 = from->tof_brr2;
  tof_a2 = from->tof_a2;
  tof_bll3 = from->tof_bll3;
  tof_brr3 = from->tof_brr3;
  tof_a3 = from->tof_a3;
  tof_bll4 = from->tof_bll4;
  tof_brr4 = from->tof_brr4;
  tof_a4 = from->tof_a4;
  tof_bll5 = from->tof_bll5;
  tof_brr5 = from->tof_brr5;
  tof_a5 = from->tof_a5;
  tof_bll6 = from->tof_bll6;
  tof_brr6 = from->tof_brr6;
  tof_a6 = from->tof_a6;
   
  return kTRUE;
}

ClassImp(TSCIParameter)


// ----------------------------------------------------------

TIDParameter::TIDParameter() : TGo4Parameter("TIDParameter") {

  id_tofoff2 = 0.;   
  id_tofoff3 = 0.;
  id_tofoff4 = 0.;
  id_tofoff5 = 0.;
  id_tofoff6 = 0.;
  id_tofcorr2 = 0.;   
  id_tofcorr3 = 0.;
  id_tofcorr4 = 0.;
  id_tofcorr5 = 0.;
  id_tofcorr6 = 0.;
  id_path2 = 0.;
  id_path3 = 0.;
  id_path4 = 0.;
  id_path5 = 0.;
  id_path6 = 0.;
  
  offset_z = 0.;
  offset_z2 = 0.;
  offset_z3 = 0.;
  a2AoQCorr =0.;
  a4AoQCorr =0.;
  
  for (int i=0;i<4;i++){
    vel_a[i] = 0.;
    vel_a2[i] = 0.;
    vel_a3[i] = 0.;
  }


  for(int i=0;i<5;++i)
    {
      ID_Z_AoverQ_num[i] = 0;

      for(int j=0;j<5;++j)
	for(int k=0;k<2;++k)
	  ID_Z_AoverQ[i][j][k] = 0;
    }
  for(int i=0;i<6;++i)
    {
      ID_x2AoverQ_num[i] = 0;

      for(int j=0;j<5;++j)
	for(int k=0;k<2;++k)
	  ID_x2AoverQ[i][j][k] = 0;
    }

}

TIDParameter::TIDParameter(const char* name) : TGo4Parameter(name) {

  id_tofoff2 = 267690.0;    // Offset (ps), 22sep03
  id_path2 =   123000.0;    // Path/c (ps)
  id_tofcorr2 = 0.0;        // Correction for x4, 23sep03

  id_tofoff3 = 267690.0;    // Offset (ps)
  id_path3 =   271850.0;    // Path/c (ps)
  id_tofcorr3 = 0.0;        // Correction for x4, 03.07.2018

  id_tofoff4 = 267690.0;    // Offset (ps)
  id_path4 =   271850.0;    // Path/c (ps)
  id_tofcorr4 = 0.0;        // Correction for x8, 03.07.2018

  id_tofoff5 = 267690.0;    // Offset (ps)
  id_path5 =   271850.0;    // Path/c (ps)
  id_tofcorr5 = 0.0;        // Correction for x4, 03.07.2018

  id_tofoff6 = 267690.0;    // Offset (ps)
  id_path6 =   271850.0;    // Path/c (ps)
  id_tofcorr6 = 0.0;        // Correction for x8, 03.07.2018

  
   
  vel_a[0] =  0.;   // 160310 calib
  vel_a[1] =  1.;   // 
  vel_a[2] =  0.;   //
  vel_a[3] =  0.;   // Used in ID part 

  vel_a2[0] =  0.;   // 160310 calib
  vel_a2[1] =  1.;   // 
  vel_a2[2] =  0.;   // 
  vel_a2[3] =  0.;   // Used in ID part 

  vel_a3[0] =  0.;   // 160310 calib
  vel_a3[1] =  1.;   // 
  vel_a3[2] =  0.;   // 
  vel_a3[3] =  0.;   // Used in ID part 
        
  
  for(int i=0;i<5;++i)
    {
      ID_Z_AoverQ_num[i] = 0;

      for(int j=0;j<5;++j)
	for(int k=0;k<2;++k)
	  ID_Z_AoverQ[i][j][k] = 0;
    }
  for(int i=0;i<6;++i)
    {
      ID_x2AoverQ_num[i] = 0;

      for(int j=0;j<5;++j)
	for(int k=0;k<2;++k)
	  ID_x2AoverQ[i][j][k] = 0;
    }


} 

TIDParameter::~TIDParameter() {
}

void TIDParameter::Print(Option_t*) const {
  std::cout << "Parameter " << GetName() << std::endl;
  std::cout << "id_tofoff2 = " << id_tofoff2 << std::endl;
  std::cout << "id_tofoff3 = " << id_tofoff3 << std::endl;
  std::cout << "id_tofoff4 = " << id_tofoff4 << std::endl;
  std::cout << "id_tofoff5 = " << id_tofoff5 << std::endl;
  std::cout << "id_tofoff6 = " << id_tofoff6 << std::endl;
  std::cout << "id_tofcorr2 = " << id_tofcorr2 << std::endl;
  std::cout << "id_tofcorr3 = " << id_tofcorr3 << std::endl;
  std::cout << "id_tofcorr4 = " << id_tofcorr4 << std::endl;
  std::cout << "id_tofcorr5 = " << id_tofcorr5 << std::endl;
  std::cout << "id_tofcorr6 = " << id_tofcorr6 << std::endl;
  std::cout << "id_path2 = " << id_path2 << std::endl;
  std::cout << "id_path3 = " << id_path3 << std::endl;
  std::cout << "id_path4 = " << id_path4 << std::endl;
  std::cout << "id_path5 = " << id_path5 << std::endl;
  std::cout << "id_path6 = " << id_path6 << std::endl;

  for (int i=0;i<4;i++){
    std::cout << "vel_a["<<i<<"] = " << vel_a[i] << std::endl;
    std::cout << "vel_a2["<<i<<"] = " << vel_a2[i] << std::endl;
    std::cout << "vel_a3["<<i<<"] = " << vel_a3[i] << std::endl;
  }

  for(int i=0;i<5;++i)
    {
      std::cout<<"ID condition "<<i<<" "<<ID_Z_AoverQ_num[i]<<std::endl;
      for(int j=0;j<ID_Z_AoverQ_num[i];++j)
	std::cout<<"--> x["<<j<<"] ="<<ID_Z_AoverQ[i][j][0]<<" y["<<j<<"] ="<<ID_Z_AoverQ[i][j][1]<<std::endl;
    }
  
  return ;
}

Bool_t TIDParameter::UpdateFrom(TGo4Parameter* par) {
  TIDParameter *from = dynamic_cast<TIDParameter*> (par);
  if (from==0) {
    std::cout << "Wrong parameter object: " << par->ClassName() << std::endl; 
    return kFALSE;   
  }
   
   id_tofoff2 = from->id_tofoff2;
  id_tofoff3 = from->id_tofoff3;
  id_tofoff4 = from->id_tofoff4;
  id_tofoff5 = from->id_tofoff5;
  id_tofoff6 = from->id_tofoff6;
  id_tofcorr2 = from->id_tofcorr2;
  id_tofcorr3 = from->id_tofcorr3;
  id_tofcorr4 = from->id_tofcorr4;
  id_tofcorr5 = from->id_tofcorr5;
  id_tofcorr6 = from->id_tofcorr6;
  id_path2 = from->id_path2; 
  id_path3 = from->id_path3;
  id_path4 = from->id_path4;
  id_path5 = from->id_path5;
  id_path6 = from->id_path6;

  for (int i=0;i<4;i++){
    vel_a[i] = from->vel_a[i];
    vel_a2[i] = from->vel_a2[i];
    vel_a3[i] = from->vel_a3[i];
  }   


  for(int i=0;i<5;++i)
    {
      ID_Z_AoverQ_num[i] = from->ID_Z_AoverQ_num[i];

      for(int j=0;j<ID_Z_AoverQ_num[i];++j)
	for(int k=0;k<2;++k)
	  ID_Z_AoverQ[i][j][k] = from->ID_Z_AoverQ[i][j][k];
    }

  for(int i=0;i<6;++i)
    {
      ID_x2AoverQ_num[i] = from->ID_x2AoverQ_num[i];

      for(int j=0;j<ID_x2AoverQ_num[i];++j)
	for(int k=0;k<2;++k)
	  ID_x2AoverQ[i][j][k] = from->ID_x2AoverQ[i][j][k];
    }

  
  return kTRUE;
}

ClassImp(TIDParameter)


// ----------------------------------------------------------

TSIParameter::TSIParameter() : TGo4Parameter("TSIParameter")
{
  si_factor1 = 1.;
  si_factor2 = 1.;
  si_factor3 = 1.;
  si_factor4 = 1.;
  si_factor5 = 1.;

  si_offset1 = 0.;
  si_offset2 = 0.;
  si_offset3 = 0.;
  si_offset4 = 0.;
  si_offset5 = 0.;

  for(int i=0;i<32;i++){
    //dssd_factor[i] = 1.;
    //dssd_offset[i] = 0.;

      dssd_factor_det1[i] = 1.;
      dssd_offset_det1[i] = 0.;

      dssd_factor_det2[i] = 1.;
      dssd_offset_det2[i] = 0.;

      dssd_factor_det3[i] = 1.;
      dssd_offset_det3[i] = 0.;

      dssd_factor_det4[i] = 1.;
      dssd_offset_det4[i] = 0.;

      dssd_factor_det5[i] = 1.;
      dssd_offset_det5[i] = 0.;

      dssd_factor_det6[i] = 1.;
      dssd_offset_det6[i] = 0.;

      
  }

}

TSIParameter::TSIParameter(const char* name) : TGo4Parameter(name)
{
  si_factor1 = 1.;
  si_factor2 = 1.;
  si_factor3 = 1.;
  si_factor4 = 1.;
  si_factor5 = 1.;

  si_offset1 = 0.;
  si_offset2 = 0.;
  si_offset3 = 0.;
  si_offset4 = 0.;
  si_offset5 = 0.;

  for(int i=0;i<32;i++){
    //dssd_factor[i] = 1.;
    //dssd_offset[i] = 0.;

      dssd_factor_det1[i] = 1.;
      dssd_offset_det1[i] = 0.;

      dssd_factor_det2[i] = 1.;
      dssd_offset_det2[i] = 0.;

      dssd_factor_det3[i] = 1.;
      dssd_offset_det3[i] = 0.;

      dssd_factor_det4[i] = 1.;
      dssd_offset_det4[i] = 0.;

      dssd_factor_det5[i] = 1.;
      dssd_offset_det5[i] = 0.;

      dssd_factor_det6[i] = 1.;
      dssd_offset_det6[i] = 0.;
  }

} 

  
TSIParameter::~TSIParameter()
{ }

void TSIParameter::Print(Option_t*) const {
  std::cout << "Parameter " << GetName() << std::endl;
  return ;
}

Bool_t TSIParameter::UpdateFrom(TGo4Parameter* par) {
  TSIParameter *from = dynamic_cast<TSIParameter*> (par);
  if (from==0) {
    std::cout << "Wrong parameter object: " << par->ClassName() << std::endl; 
    return kFALSE;   
  }
  si_factor1 = from->si_factor1;
  si_factor2 = from->si_factor2;
  si_factor3 = from->si_factor3;
  si_factor4 = from->si_factor4;
  si_factor5 = from->si_factor5;

  si_offset1 = from->si_offset1;
  si_offset2 = from->si_offset2;
  si_offset3 = from->si_offset3;
  si_offset4 = from->si_offset4;
  si_offset5 = from->si_offset5;

  for(int i=0;i<32;i++){
    //dssd_factor[i] = from->dssd_factor[i];
    //dssd_offset[i] = from->dssd_offset[i];

      dssd_factor_det1[i] = from->dssd_factor_det1[i];;
      dssd_offset_det1[i] = from->dssd_offset_det1[i];

      dssd_factor_det2[i] = from->dssd_factor_det2[i];;
      dssd_offset_det2[i] = from->dssd_offset_det2[i];

      dssd_factor_det3[i] = from->dssd_factor_det3[i];;
      dssd_offset_det3[i] = from->dssd_offset_det3[i];

      dssd_factor_det4[i] = from->dssd_factor_det4[i];;
      dssd_offset_det4[i] = from->dssd_offset_det4[i];

      dssd_factor_det5[i] = from->dssd_factor_det5[i];;
      dssd_offset_det5[i] = from->dssd_offset_det5[i];

      dssd_factor_det6[i] = from->dssd_factor_det6[i];;
      dssd_offset_det6[i] = from->dssd_offset_det6[i];
  }


  return kTRUE;		
}

ClassImp(TSIParameter)


TMRTOFMSParameter::TMRTOFMSParameter() : TGo4Parameter("TMRTOFMSParameter")
{
  MRTOFMS_a = 1.;
  MRTOFMS_b = 0.;
  MRTOFMS_t0 = 0.;
  MRTOFMS_tFRS = 0.;

}

TMRTOFMSParameter::TMRTOFMSParameter(const char* name) : TGo4Parameter(name)
{
  MRTOFMS_a = 1.;
  MRTOFMS_b = 0.;
  MRTOFMS_t0 = 0.;
  MRTOFMS_tFRS = 0.;

} 


TMRTOFMSParameter::~TMRTOFMSParameter() {

}

void TMRTOFMSParameter::Print(Option_t*) const {
  std::cout << "Parameter " << GetName() << std::endl;
  return ;
}

Bool_t TMRTOFMSParameter::UpdateFrom(TGo4Parameter* par) {
  TMRTOFMSParameter *from = dynamic_cast<TMRTOFMSParameter*> (par);
  if (from==0) {
    std::cout << "Wrong parameter object: " << par->ClassName() << std::endl; 
    return kFALSE;   
  }		
  MRTOFMS_a = from->MRTOFMS_a;
  MRTOFMS_b = from->MRTOFMS_b;
  MRTOFMS_t0 = from->MRTOFMS_t0;
  MRTOFMS_tFRS = from->MRTOFMS_tFRS;


  return kTRUE;		
}

ClassImp(TMRTOFMSParameter)
