// $Originally by754 2011-05-18 11:04:52Z adamczew $
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

#include "DESPECAnalysis.h"

#include <stdlib.h>
#include "Riostream.h"

#include "TH1.h"
#include "TFile.h"
#include "TSystem.h"

#include "TGo4Fitter.h"
#include "TGo4FitterEnvelope.h"
#include "TGo4AnalysisStep.h"
#include "TGo4StepFactory.h"

#include "TFRSParameter.h"
#include "EventUnpackStore.h"
#include "EventAnlStore.h"
#include "EventCorrelStore.h"
#include "TGo4Version.h"

#include "TAidaConfiguration.h"
#include "AIDA_Event.h"
//#include "Go4CommandsAnalysis/Go4CommandsAnalysis.h"

#include "Go4EventServer.h"

//***********************************************************
DESPECAnalysis::DESPECAnalysis() :
   TGo4Analysis(),
   fMbsEvent(0),
   fRawEvent(0),
 //  fOutput(0),
   fAnlEvent(0),
   fCorrelEvent(0)
   //fEvents(0),
   //fLastEvent(0)
{
  cout << "Wrong constructor DESPECAnalysis()!" << endl;
}

//***********************************************************
// this constructor is called by go4analysis executable
DESPECAnalysis::DESPECAnalysis(int argc, char** argv) :
   TGo4Analysis(argc, argv),
   fMbsEvent(0),
   fRawEvent(0),
  // fOutput(0),
   fAnlEvent(0),
   fCorrelEvent(0),
   fEvents(0),
   fLastEvent(0)
{
   if (!TGo4Version::CheckVersion(__GO4BUILDVERSION__)) {
      cout << "****  Go4 version mismatch" << endl;
      exit(-1);
   }

   cout << "**** DESPECAnalysis: Create " << argv[0] << endl;
  
   TString kind, input, out1, out2;

// Create step 1 Unpack.
  // TGo4StepFactory* factory1 = new TGo4StepFactory("UnpackFactory");
   TGo4StepFactory* factory1 = new TGo4StepFactory("Unpack-factory");
   factory1->DefEventProcessor("EventUnpackProc", "EventUnpackProc");// object name, class name
   factory1->DefOutputEvent("UnpackStore", "EventUnpackStore"); // object name, class name
   TGo4AnalysisStep* step1 = new TGo4AnalysisStep("Unpack",factory1,0,0,0);
   step1->SetSourceEnabled(kTRUE);
   step1->SetStoreEnabled(kTRUE);  // enable output
   step1->SetProcessEnabled(kTRUE);
   step1->SetErrorStopEnabled(kTRUE);
   AddAnalysisStep(step1);

// Create step 2 Calibration and Main Monitoring histograms
   TGo4StepFactory* factory2 = new TGo4StepFactory("Analysis-factory");
   factory2->DefInputEvent("UnpackStore", "EventUnpackStore"); // object name, class name
   factory2->DefEventProcessor("AnlProc", "EventAnlProc"); // object name, class name
   factory2->DefOutputEvent("AnlEvent", "EventAnlStore"); // object name, class name
   TGo4AnalysisStep* step2    = new TGo4AnalysisStep("Analysis",factory2,0,0,0);
   step2->SetSourceEnabled(kTRUE);
   step2->SetErrorStopEnabled(kTRUE);
   AddAnalysisStep(step2);
cout<<"MHTDC_OR_TAC " <<MHTDC_OR_TAC << endl;
// Create step 3 Correlations.
   TGo4StepFactory* factory3 = new TGo4StepFactory("CorrelationsFactory");
   factory3->DefInputEvent("AnlEvent", "EventAnlStore"); // object name, class name
   factory3->DefEventProcessor("CorrelProc", "EventCorrelProc"); // object name, class name
   factory3->DefOutputEvent("CorrelEvent", "EventCorrelStore"); // object name, class name
   TGo4AnalysisStep* step3    = new TGo4AnalysisStep("Correlations",factory3,0,0,0);
   step3->SetErrorStopEnabled(kTRUE);
  // step3->SetStoreEnabled(kTRUE);  // enable output
   AddAnalysisStep(step3);
/////////////// Parameters //////////////////////////
  // At this point, autosave file has not yet been read!
  // Therefore parameter values set here will be overwritten
  // if an autosave file is there.
  
  fCal = new CalibParameter("CalibPar");
  AddParameter(fCal);
 //if (fCal) fCal->PrintParameter(0,0);
  
  fCorrel = new CorrelParameter("CorrelPar");
  AddParameter(fCorrel);

  fFRSPar = new TFRSParameter("FRSPar");
  AddParameter(fFRSPar);

  fMWPar = new TMWParameter("MWPar");
  AddParameter(fMWPar);

  fMUSICPar = new TMUSICParameter("MUSICPar");
  AddParameter(fMUSICPar);

  fTPCPar = new TTPCParameter("TPCPar");
  AddParameter(fTPCPar);

  fSCIPar = new TSCIParameter("SCIPar");
  AddParameter(fSCIPar);

  fIDPar = new TIDParameter("IDPar");
  AddParameter(fIDPar);

  fSIPar = new TSIParameter("SIPar");
  AddParameter(fSIPar);

//   ModPar = new TModParameter("ModPar");
//   AddParameter(ModPar);
  
  MRtofPar = new TMRTOFMSParameter("MRTOFMSPar");
  AddParameter(MRtofPar);
}
Bool_t DESPECAnalysis::InitEventClasses() 
{
    Bool_t res = TGo4Analysis::InitEventClasses();
  std::string nameExperiment;
  std::ifstream ifs ( "Configuration_Files/FRS/FRS_Setups/frsconfig.txt" );
  if(ifs.is_open())
    {
       
      const std::string CommentSymbol("#");
      const std::string ExpNameSymbol("NameExperiment");
        
      std::string temp_line;
      while(std::getline(ifs,temp_line))
    {
      std::stringstream stream(temp_line);
      std::string testComment(stream.str());
      std::size_t it_comment = testComment.find(CommentSymbol);
      if(it_comment!=std::string::npos)
        {
          //std::cout<<"!> Skip comment"<<temp_line<<std::endl;
          continue;
        }
      std::string key, value;
      stream >> key >> value ;
      if(key==ExpNameSymbol)
        nameExperiment=value;
    }
    }
    
  std::string nameSetupFile ("Configuration_Files/FRS/FRS_Setups/setup_");
  nameSetupFile+=nameExperiment;
  nameSetupFile+=".C";

  std::cout << "DESPECAnalysis_FRS::Call "<< nameSetupFile<<" script" << std::endl;
  
  std::ifstream testingFileExist(nameSetupFile.c_str());
  if(testingFileExist.good()==false)
    {
      std::cout<<" E> !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! "<<std::endl;
      std::cout<<" E> FRS Setup file "<<nameSetupFile<<" not found ! Please look to directory Configuration_Files/FRS_Setups/ if it exits or set proper name of experiment in config.txt"<<std::endl;
      std::cout<<" E> !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! "<<std::endl;

      std::exit(-1);
    }
  
  std::string processL(".x ");
  processL += nameSetupFile;
  gROOT->ProcessLine(processL.c_str());

  return res;
}

//***********************************************************
DESPECAnalysis::~DESPECAnalysis()
{
  cout << "**** DESPECAnalysis: Delete" << endl;
}
//***********************************************************
//-----------------------------------------------------------
Int_t DESPECAnalysis::UserPreLoop()
{
  
  
//   cout << "**** DESPECAnalysis: PreLoop" << endl;
//   Print(); // printout the step settings
//   cout << "**************************************" << endl;
//    // we update the pointers to the current event structures here:
//    fMbsEvent = dynamic_cast<TGo4MbsEvent*>    (GetInputEvent("Unpack"));   // of step "Unpack"
//    //Aida_inp= dynamic_cast<AIDA_Event*>    (GetInputEvent("AIDA_Event"));   // of step "Unpack"
//    fRawEvent = dynamic_cast<EventUnpackStore*> (GetOutputEvent("Unpack"));
//    //fOutput = dynamic_cast<EventUnpackStore*> (GetOutputEvent("Unpack"));
//    fAnlEvent = dynamic_cast<EventAnlStore*>    (GetOutputEvent("Analysis"));
//    fCorrelEvent = dynamic_cast<EventCorrelStore*>    (GetOutputEvent("Correlation"));
//    
//   
//      
//    fEvents=0;
//    fLastEvent=0;
   // create histogram for UserEventFunc
   // At this point, the histogram has been restored
   // from auto-save file if any.
   
      return 0;
}

//-----------------------------------------------------------
Int_t DESPECAnalysis::UserPostLoop()
{
  cout << "**** DESPECAnalysis: PostLoop" << endl;
  cout << "Last event: " << fLastEvent << " Total events: " << fEvents << endl;
  if(fMbsEvent)
    {
      // we can check some properties of last event here:
      //fMbsEvent->PrintEvent(); // header and data content

      // fileheader structure:
      s_filhe* fileheader=fMbsEvent->GetMbsSourceHeader();
//       if(fileheader) {
//            cout <<"\nInput file was: "<<fileheader->filhe_file << endl;
//            cout <<"Tapelabel:\t" << fileheader->filhe_label<<endl;
//            cout <<"UserName:\t" << fileheader->filhe_user<<endl;
//            cout <<"RunID:\t" << fileheader->filhe_run<<endl;
//            cout <<"\tExplanation: "<<fileheader->filhe_exp <<endl;
//            cout <<"\tComments: "<<endl;
//            Int_t numlines=fileheader->filhe_lines;
//            for(Int_t i=0; i<numlines;++i)
//                cout<<"\t\t"<<fileheader->s_strings[i].string << endl;
//             }

         }

   fMbsEvent = 0; // reset to avoid invalid pointer if analysis is changed in between
   fRawEvent = 0;
  // fOutput = 0;
   fAnlEvent = 0;
   fEvents=0;
   return 0;
}

//-----------------------------------------------------------
Int_t DESPECAnalysis::UserEventFunc()
{
//// This function is called once for each event.
   // unused // Int_t value = 0;
   Int_t count = 0;
   if(fMbsEvent) // unused // value = fMbsEvent->GetDlen()/2+2; // total longwords
   fEvents++;
   if(fEvents == 1 || IsNewInputFile()) {
      if(fMbsEvent) {
         count=fMbsEvent->GetCount();
         cout << "\nFirst event #: " << count  << endl;
         }
      }
      SetNewInputFile(kFALSE); // we have to reset the newfile flag
   
   fLastEvent = count;
   return 0;
}

