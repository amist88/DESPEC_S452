#include "AIDA_Detector_System.h"
#include "AIDA_Data_Types.h"
#include "AIDA_Event.h"
#include "TGo4MbsFile.h"
#include "TGo4MbsEvent.h"
#include <fstream>
#include "TGo4MbsSubEvent.h"
#include "TGo4Analysis.h"
#include "TROOT.h"
#include <cstdlib>
#include "TH1.h"
#include "TTree.h"
#include <time.h>
#include "Timestamp.h"
#include "TAidaConfiguration.h"
#include "TGo4Log.h"
#include <vector>
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"

using namespace std;

static const int FeeToStrip[64] = {
  62, 63, 59, 60, 61, 56, 57, 58, 52, 53, 54, 55, 49, 50, 51, 45,
  46, 47, 48, 42, 43, 44, 38, 39, 40, 41, 35, 36, 37, 31, 32, 33,
  34, 28, 29, 30, 24, 25, 26, 27, 21, 22, 23, 17, 18, 19, 20, 14,
  15, 16, 10, 11, 12,  7,  3,  0,  8,  4,  1,  9,  5,  2, 13,  6
};
//---------------------------------------------------------------


    
AIDA_Detector_System::AIDA_Detector_System()
{
  TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();

     
  adcOffsets.resize(conf->FEEs());
  adcTimeOffsets.resize(conf->FEEs());
  discriminatorTimes.resize(conf->FEEs());
  oldtime_d.resize(conf->FEEs());
  upperTime48_d.resize(conf->FEEs());
  upperTime63_d.resize(conf->FEEs());
  stats_d.resize(conf->FEEs());
  pauseTimes.resize(conf->FEEs());
  scaler.resize(conf->FEEs());


  Energy = new double[AIDA_MAX_HITS];
  FEE_ID =  new int[AIDA_MAX_HITS];
  Ch_ID = new int[AIDA_MAX_HITS];
  Time = new ULong64_t [AIDA_MAX_HITS];
  FastTime = new ULong64_t [AIDA_MAX_HITS];
  HighE_veto = new bool[AIDA_MAX_HITS];
  Side = new int[AIDA_MAX_HITS];
  Strip = new int[AIDA_MAX_HITS];
  EvtID = new int[AIDA_MAX_HITS];
  AdcData = new int[AIDA_MAX_HITS];

  Hits = 0;
  for (int i = 0; i < AIDA_MAX_HITS; i++)
  {
    Energy[i] = 0;
    FEE_ID[i] = 0;
    Ch_ID[i] = 0;
    Time[i] = 0;
    FastTime[i] = 0;
    HighE_veto[i] = 0;
    Side[i] = 0;
    Strip[i] = 0;
    EvtID[i] = 0;
    AdcData[i] = 0;
  }

  pausedCounter = 0;
  totalPauseTime = 0;
  for (int i = 0; i < conf->FEEs(); ++i)
  {
    oldtime_d[i] = 0;
    upperTime48_d[i] = 0;
    upperTime63_d[i] = 0;
    for (int j = 0; j < 64; ++j)
    {
      adcOffsets[i][j] = 0;
      discriminatorTimes[i][j] = 0;
    }
    pauseTimes[i] = 0;
    scaler[i] = 0;
    memset(&stats_d[i], 0, sizeof(UnpackProcStats));
  }

  upperTime48 = 0;
  upperTime63 = 0;
  //timewarpAmount = 0;
  memset(&stats, 0, sizeof(UnpackProcStats));



}

//---------------------------------------------------------------

AIDA_Detector_System::~AIDA_Detector_System(){


  delete[] Energy;
  delete[] FEE_ID;
  delete[] Ch_ID;
  delete[] Time;
  delete[] FastTime;
  delete[] HighE_veto;
  delete[] Side;
  delete[] Strip;
  delete[] EvtID;
  delete[] AdcData;

}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void AIDA_Detector_System::get_Event_data(Raw_Event* RAW){
  //
  if (Hits > AIDA_MAX_HITS)
  {
    std::cout << "WARNING: Too many AIDA hits: " << Hits << "/" << AIDA_MAX_HITS << std::endl;
    std::cout << " Extra Hits will be ignored" << std::endl;
    Hits = AIDA_MAX_HITS;
  }
  RAW->set_DATA_AIDA(Energy, FEE_ID, Ch_ID, Time, Hits, HighE_veto, Side, Strip, EvtID, FastTime, AdcData, ScalerData);
}
//---------------------------------------------------------------

void AIDA_Detector_System::Process_MBS(TGo4MbsSubEvent* psubevt)
{
  pdata = psubevt->GetDataField();
  Int_t lwords = psubevt->GetIntLen();
  pdata_start = pdata;

  sub_evt_length  = ((psubevt->GetDlen() - 2) / 2);

  stats.MBSEvents++;
  TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
 
  
// Loading in AIDA offsets and times  
if(get_newfile()==1 || stats.MBSEvents==1){
    
//   cout<< "get_newfile() " << get_newfile() <<endl;
 // cout<< "AIDA get_filename " << get_filename() << endl;
    
  std::ifstream fs("Configuration_Files/AIDA/AIDA_offsets.txt");
  fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  while (fs)
  {
    if (fs.peek() == '#')
    {
      fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    int fee, channel;
    double offset;
    fs >> fee >> channel >> offset;
    if (!fs) break;
    adcOffsets[fee-1][channel-1] = offset;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  TGo4Log::Info("AIDA: Loaded ADC Offsets");
  fs.close();
  
    
  //*************************************************************  
  // Deciding which file to open depending on the run number
  char ch[100] = "Configuration_Files/AIDA/AIDA_times_S452f"; 
  char ch2[10] = ".txt";
  string data = "";
  data = std::string(get_filename());
  size_t pos1, pos2, pos3;
  string filenum;

  pos1 = data.find("S452");
  if(pos1!=string::npos){
     pos2 = data.find("f",pos1+1);
     pos3 = data.find("_",pos2+1);
     filenum = data.substr(pos2+1,(pos3-pos2)-1);
  }

  cout << "The filenumber is: " << filenum << endl;
  strcat(ch,filenum.c_str());
  strcat(ch,ch2);
  cout << "Will load file " << ch << endl;  
  //*************************************************************
  
  fs.open(ch);
  if(fs){  
    cout << "Found AIDA ADC clock correction file " << ch << endl;  
  }
  else {
    cout << "Could not find AIDA ADC clock correction file. Using default AIDA_times.txt. " << endl;
    fs.open("Configuration_Files/AIDA/AIDA_times.txt");   
  }
      
  while (fs)
  {
    if (fs.peek() == '#')
    {
      fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    int fee, offset;
    fs >> fee >> offset;
    if (!fs) break;
    adcTimeOffsets[fee] = offset;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  TGo4Log::Info("AIDA: Loaded ADC Clock Correction");
  fs.close();  
    
  

}
///Better to load them here?Or in BuildAIDAADCEvent 
//Load_offset_times();

  //if (*pdata++ == 0x200) assume procID has verified the ID
  pdata++;
  {

    uint64_t wr = 0;
    uint64_t bits = *pdata++ & 0xFFFF;
    wr |= bits;
    bits = *pdata++ & 0xFFFF;
    wr |= (bits << 16);
    bits = *pdata++ & 0xFFFF;
    wr |= (bits << 32);
    bits = *pdata++ & 0xFFFF;
    wr |= (bits << 48);

    if (conf->ucesb() && conf->ucesbShift())
    {
      wr += conf->ucesbShift();
    }

    upperTime63 = std::max(upperTime63, wr >> 48);
    upperTime48 = std::max(upperTime48, (wr >> 28) & 0x000FFFFF);

    if(!stats.Start) stats.Start = wr;

    if ((lwords - 5 ) & 0x1)
    {
      std::cout << "AIDA data size is incorrect, ignoring data" << std::endl;
    }
    Hits = 0;
    ScalerData.clear();
    while ((pdata - pdata_start) < (sub_evt_length)) // subevent loop
    {

      Int_t word1 = *pdata++;
      Int_t word2 = *pdata++;

      //           printf( "word1 %d (0x%x)\n" , word1);
      //           printf( "word2 %d (0x%x)\n" , word2);

      BuildAIDAEvent(psubevt, word1, word2);
    }//end  while

  }
}

bool AIDA_Detector_System::BuildAIDAEvent(TGo4MbsSubEvent* psubevt, Int_t word1, Int_t word2)
{
  int type = (word1 >> 30) & 0x3;
  int lowTS = (word2 & 0x0FFFFFFF);
  stats.Stop = GetTime(lowTS);

  stats.AIDAEvents++;

  if (type == 3)
  {
    stats.Type.ADC++;
    return BuildAIDAADCEvent(psubevt, word1, word2);
  }
  else if (type == 2)
  {
    stats.Type.Info++;
    return BuildAIDAInfoEvent(psubevt, word1, word2);
  }
  else
  {
    std::cout << "Unknown event type " << type << std::endl;
    return false;
  }
}

bool AIDA_Detector_System::BuildAIDAADCEvent(TGo4MbsSubEvent* psubevt, Int_t word1, Int_t word2)
{
  AidaEvent evt;

  // evt.ID = 3;
  EvtID[Hits] = 3;

  int channelID = (word1 >> 16) & 0xFFF;
  int feeID = (channelID >> 6) & 0x3F;
  channelID &= 0x3F;
  int lowTS = (word2 & 0x0FFFFFFF);
  int data = (word1 & 0xFFFF);
  int veto = (word1 >> 28) & 0x1;

  stats_d[feeID].AIDAEvents++;
  stats_d[feeID].Type.ADC++;
  uint64_t newtime = GetTime_d(feeID, lowTS);
  if (newtime < oldtime_d[feeID])
  {
    stats.TimeWarps++;
    stats_d[feeID].TimeWarps++;
  }
  oldtime_d[feeID] = newtime;
  oldtime = newtime;

  evt.Data = data;

  ///For RAW event (to unpack procedure stage)
  FEE_ID[Hits] = feeID;
  Ch_ID[Hits] = channelID;
  Time[Hits] = newtime - adcTimeOffsets[feeID];
  HighE_veto[Hits] = (veto == 1);
  if (veto == 1)
  {
    stats.ADCType.Implant++;
    stats_d[feeID].ADCType.Implant++;
    FastTime[Hits] = Time[Hits];
  }
  else
  {
    stats.ADCType.Decay++;
    stats_d[feeID].ADCType.Decay++;
    FastTime[Hits] = discriminatorTimes[feeID][channelID];
    discriminatorTimes[feeID][channelID] = 0;
  }

  AdcData[Hits] = data;

  //cout <<" Ch_ID[hi] " <<Ch_ID[Hits]<< " Time[hi] " << Time[Hits] << " hits " <<Hits<< endl;
  // }
  /* Real DSSD Mapping */

  TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
  evt.DSSD = conf->FEE(feeID).DSSD;

  //Side, Front or back determines the polarity
  if (evt.DSSD > 0)
  {
    evt.Side = conf->FEE(feeID).Side;

    Side[Hits] = conf->FEE(feeID).Side;

    if (conf->FEE(feeID).High)
    {
      evt.Strip = 127 - FeeToStrip[channelID];
      Strip[Hits] = 127 - FeeToStrip[channelID];
    }
    else
    {
      evt.Strip = FeeToStrip[channelID];
      Strip[Hits] = FeeToStrip[channelID];
    }

    evt.Intensity = (evt.Data - 32768) * evt.Side;
    // if (evt.HighEnergy)
    // test->Fill(evt.Strip + (evt.Side == -1 ? 0 : 1) * 128);

    if (veto == 1)
    {
      evt.Energy = (evt.Intensity - adcOffsets[feeID][channelID]) * 0.7; // Energy in MeV
      Energy[Hits] = (evt.Intensity - adcOffsets[feeID][channelID]) * 0.7; // Energy in MeV
    }
    else
    {
      evt.Energy = (evt.Intensity- adcOffsets[feeID][channelID]) * 0.7; // Energy in keV
      Energy[Hits] = (evt.Intensity- adcOffsets[feeID][channelID]) * 0.7; // Energy in keV
    }
    // delete data without an offset (bad channels)		    }
    if (!adcOffsets[feeID][channelID])
    {
      //Side[Hits] = -10;
      //Energy[Hits] = 0;
    }
  }

  Hits++;
  return true;
}


//Don't need to output this
bool AIDA_Detector_System::BuildAIDAInfoEvent(TGo4MbsSubEvent* psubevt, Int_t word1, Int_t word2)
{
  int moduleNumber = (word1 >> 24) & 0x3F;
  int infoCode = (word1 >> 20) & 0x000F;
  int infoField = (word1 & 0x000FFFFF);
  int lowTS = (word2 & 0x0FFFFFFF);

  uint64_t newtime = GetTime_d(moduleNumber, lowTS);
  oldtime_d[moduleNumber] = newtime;

  stats_d[moduleNumber].AIDAEvents++;
  stats_d[moduleNumber].Type.Info++;

  // PAUSE: Start of deadtime, resync middle timestamp bits
  if (infoCode == 2) {
    stats.InfoType.Pause++;
    stats_d[moduleNumber].InfoType.Pause++;
    if (pauseTimes[moduleNumber] == 0)
    {
      pauseTimes[moduleNumber] = newtime;
      if(pausedCounter == 0)
        totalPauseTime = newtime;
      pausedCounter++;
    }
    upperTime48 = infoField;
    upperTime48_d[moduleNumber] = infoField;
  }
  // RESUME: End of deadtime, resync middle timestamp bits
  else if (infoCode == 3) {
    stats.InfoType.Resume++;
    stats_d[moduleNumber].InfoType.Resume++;
    if (pauseTimes[moduleNumber])
    {
      int64_t deadtime = newtime - pauseTimes[moduleNumber];
      stats_d[moduleNumber].TotalDeadTime += deadtime;
      pauseTimes[moduleNumber] = 0;
      pausedCounter--;
    }
    if (pausedCounter == 0 && totalPauseTime)
    {
      int64_t deadtime = newtime - totalPauseTime;
      stats.TotalDeadTime += deadtime;
      totalPauseTime = 0;
    }
    upperTime48 = infoField;
    upperTime48_d[moduleNumber] = infoField;
  }
  // SYNC: Resync bits 48:28 of the timestamp
  else if (infoCode == 4)
  {
    stats.InfoType.Sync48++;
    stats_d[moduleNumber].InfoType.Sync48++;
    upperTime48 = infoField;
    upperTime48_d[moduleNumber] = infoField;
    if (infoCode == 4 && stats.Start == 0) stats.Start = newtime;
  }
  // WR-SYNC for bits 63-48 of the timestamp
  else if (infoCode == 5)
  {
    stats.InfoType.Sync63++;
    stats_d[moduleNumber].InfoType.Sync63++;
    upperTime63 = infoField;
    upperTime63_d[moduleNumber] = infoField;
  }
  // DISCRIMINATOR hit pattern (fast time for LEC)
  else if (infoCode == 6)
  {
    stats.InfoType.Discriminator++;
    stats_d[moduleNumber].InfoType.Discriminator++;
    int adc = ((infoField >> 16) & 0xF) - 1;
    int hits = infoField & 0xFFFF;
    int64_t time = newtime;
    for (int i = 0; i < 16; ++i)
    {
      if (hits & (1 << i))
      {
        discriminatorTimes[moduleNumber][adc*16 + i] = time;
      }
    }
  }
  // SCALER
  else if (infoCode == 8)
  {
    stats.InfoType.Scaler++;
    stats_d[moduleNumber].InfoType.Scaler++;
    int index = ((infoField >> 16) & 0xF);
    int64_t value = infoField & 0xFFFF;
    if (index == 0)
    {
      scaler[moduleNumber] = value;
    }
    else if (index == 1)
    {
      scaler[moduleNumber] |= (value << 16);
    }
    else if (index == 2)
    {
      scaler[moduleNumber] |= (value << 32);
      ScalerData.emplace_back(moduleNumber, value, newtime);
    }
  }
  else
  {
    stats.InfoType.Unknown++;
    stats_d[moduleNumber].InfoType.Unknown++;
  }

  return false;
}

uint64_t AIDA_Detector_System::GetTime(uint64_t lowTS)
{
  return (upperTime63 << 48) | (upperTime48 << 28) | lowTS;
}

uint64_t AIDA_Detector_System::GetTime_d(int fee, uint64_t lowTS)
{
  return GetTime(lowTS);
  return (upperTime63_d[fee] << 48) | (upperTime48_d[fee] << 28) | lowTS;
}

void AIDA_Detector_System::PrintStatistics()
{
  TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
  if (!conf->ShowStats()) return;

  // Accumulate still-dead FEEs
  if (totalPauseTime) 
  {
    stats.TotalDeadTime += (oldtime - totalPauseTime);
    totalPauseTime = 0;
  }
  for (int i = 0; i < conf->FEEs(); i++)
  {
    if (pauseTimes[i])
    {
      stats_d[i].TotalDeadTime += (oldtime_d[i] - pauseTimes[i]);
      pauseTimes[i] = 0;
    }
  }


  int w = std::log10(stats.AIDAEvents) + 1;
  std::cout << "======================================" << std::endl;
  std::cout << "AIDA Unpacker Analysis" << std::endl;
  std::cout << "--------------------------------------" << std::endl;
  std::cout << "First event: " << wr_to_string(stats.Start);
  std::cout << "Last event : " << wr_to_string(stats.Stop);
  double duration = wr_to_duration(stats.Start, stats.Stop);
  std::cout << "Duration   : " << duration << " seconds" << std::endl;
  std::cout << "--------------------------------------" << std::endl;
  std::cout << "MBS Events   (M): " << std::setw(w) << stats.MBSEvents << " (" << frequency(stats.MBSEvents, duration) << ")" <<  std::endl;
  std::cout << "AIDA Words   (W): " << std::setw(w) << stats.AIDAEvents << " (" << frequency(stats.AIDAEvents, duration) << ")" <<  std::endl;
  std::cout << "ADC Words    (A): " << std::setw(w) << stats.Type.ADC << " (" << frequency(stats.Type.ADC, duration) << ")" <<  std::endl;
  std::cout << "-- Decays    (D): " << std::setw(w) << stats.ADCType.Decay << " (" << frequency(stats.ADCType.Decay, duration) << ")" <<  std::endl;
  std::cout << "-- Implants  (I): " << std::setw(w) << stats.ADCType.Implant << " (" << frequency(stats.ADCType.Implant, duration) << ")" <<  std::endl;
  std::cout << "Info Words   (F): " << std::setw(w) << stats.Type.Info << " (" << frequency(stats.Type.Info, duration) << ")" <<  std::endl;
  std::cout << "-- SYNC48    (S): " << std::setw(w) << stats.InfoType.Sync48 << " (" << frequency(stats.InfoType.Sync48, duration) << ")" <<  std::endl;
  std::cout << "-- SYNC63    (s): " << std::setw(w) << stats.InfoType.Sync63 << " (" << frequency(stats.InfoType.Sync63, duration) << ")" <<  std::endl;
  std::cout << "-- PAUSE     (P): " << std::setw(w) << stats.InfoType.Pause << " (" << frequency(stats.InfoType.Pause, duration) << ")" <<  std::endl;
  std::cout << "-- RESUME    (R): " << std::setw(w) << stats.InfoType.Resume << " (" << frequency(stats.InfoType.Resume, duration) << ")" <<  std::endl;
  std::cout << "-- Discrim   (D): " << std::setw(w) << stats.InfoType.Discriminator << " (" << frequency(stats.InfoType.Discriminator, duration) << ")" <<  std::endl;
  std::cout << "-- Scaler    (C): " << std::setw(w) << stats.InfoType.Scaler << " (" << frequency(stats.InfoType.Scaler / 3, duration) << ")" <<  std::endl;
  std::cout << "-- Unknown   (U): " << std::setw(w) << stats.InfoType.Unknown << " (" << frequency(stats.InfoType.Unknown, duration) << ")" <<  std::endl;
  std::cout << "Timewarps    (T): " << std::setw(w) << stats.TimeWarps << " (" << frequency(stats.TimeWarps, duration) << ")" <<  std::endl;
  std::cout << "Dead Time    (X): " << std::setprecision(w-4) << ((double)stats.TotalDeadTime / 1e9) << " s ("  << (100. * stats.TotalDeadTime / (stats.Stop - stats.Start)) << "%)" <<  std::endl;
  std::cout << "======================================" << std::endl;

  std::cout << "======================================" << std::endl;
  std::cout << "Individual FEE Overview" << std::endl;
  std::cout << "======================================" << std::endl;
  std::cout << std::setw(4) << "FEE" << " | " << std::setw(4)
    << std::setw(w) << "W" <<  " "
    << std::setw(w) << "A" <<  " "
    << std::setw(w) << "D" <<  " "
    << std::setw(w) << "I" <<  " "
    << std::setw(w) << "F" <<  " "
    << std::setw(w) << "S" <<  " "
    << std::setw(w) << "s" <<  " "
    << std::setw(w/2) << "P" <<  " "
    << std::setw(w/2) << "R" <<  " "
    << std::setw(w) << "D" <<  " "
    << std::setw(w/2) << "C" <<  " "
    << std::setw(w/2) << "U" <<  " "
    << std::setw(w/2) << "T" <<  " "
    << "X"
    << std::endl;
  for (int i = 0; i < conf->FEEs(); i++)
  {
    std::cout << std::setw(4) << (i+1) << " | " << std::setw(4)
      << std::setw(w) << stats_d[i].AIDAEvents << " "
      << std::setw(w) << stats_d[i].Type.ADC << " "
      << std::setw(w) << stats_d[i].ADCType.Decay << " "
      << std::setw(w) << stats_d[i].ADCType.Implant << " "
      << std::setw(w) << stats_d[i].Type.Info << " "
      << std::setw(w) << stats_d[i].InfoType.Sync48 << " "
      << std::setw(w) << stats_d[i].InfoType.Sync63 << " "
      << std::setw(w/2) << stats_d[i].InfoType.Pause << " "
      << std::setw(w/2) << stats_d[i].InfoType.Resume << " "
      << std::setw(w) << stats_d[i].InfoType.Discriminator << " "
      << std::setw(w/2) << stats_d[i].InfoType.Scaler << " "
      << std::setw(w/2) << stats_d[i].InfoType.Unknown << " "
      << std::setw(w/2) << stats_d[i].TimeWarps << " "
      << std::setprecision(w - 4) << ((double)stats_d[i].TotalDeadTime / 1e9)
      << std::endl;
  }
}
//gets the filename
const char* AIDA_Detector_System::get_filename(){
    const char* filename;
    filename = TGo4Analysis::Instance()->GetInputFileName();
    return filename;
}
bool AIDA_Detector_System::get_newfile(){
    bool newfile;
    newfile= TGo4Analysis::Instance()->IsNewInputFile();
    return newfile;
}

int* AIDA_Detector_System::get_pdata(){return pdata;}

///End of Nic Unpack here
//---------------------------------------------------------------
