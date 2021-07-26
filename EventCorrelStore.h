// $Id: TSCNAnlEvent.h 755 2011-05-20 08:04:11Z linev $
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

#ifndef TSCNANLEVENT_H
#define TSCNANLEVENT_H

#include "TGo4EventElement.h"
//#include "TSCNUnpackEvent.h"
#include "EventAnlStore.h"

class EventCorrelStore : public TGo4EventElement {
   public:
      EventCorrelStore() : TGo4EventElement() {}
      EventCorrelStore(const char* name) : TGo4EventElement(name) {}
      virtual ~EventCorrelStore() {}

      virtual void  Clear(Option_t *t="");
      
      Bool_t AIDA_implantation_gate_DSSD1;
      Bool_t AIDA_implantation_gate_DSSD2;
      Bool_t AIDA_implantation_gate_DSSD3;
      
      Int_t AIDA_implantation_gate_DSSD1_StripX[512];
      Int_t AIDA_implantation_gate_DSSD1_StripY[512];
      
       ///FRS Outputs
      
      Float_t cFRS_AoQ;
      Float_t cFRS_ID_x2;
      Float_t cFRS_ID_x4;
      Float_t cFRS_z;
      Float_t cFRS_z2;
      
      Long64_t cdT_AIDA_FRS;
      Long64_t cAIDA_dT_imp_decay[100];
      Long64_t cAIDA_dT_imp_decay_FRS_gated[100];
      
      Int_t cAIDA_dT_imp_decay_hits;
     
      Int_t cImplantIterator;
      Int_t cDecayIterator;
      Int_t cEvent_number;
      
      Double_t cAIDAImplantE[200];
      Double_t cAIDADecayE[1000];
      
      double cFatimaVME_TimeMachine_dT[10];
      Long64_t cGermanium_TimeMachine_dT;
      Long64_t cFatimaTAMEX_TimeMachine_dT[10];
      Long64_t cbPlast_TimeMachine_dT[10];
      Double_t cAIDA_TimeMachine_dT;
      int64_t cAIDA_TM_WR;
      
      Double_t cGalE;
      Double_t cFatE[50];
      Double_t cbPlastE[48];
      
      
      
      Long64_t cAIDA_WR;
      Long64_t cbPlast_WR;
      Long64_t cFAT_WR;
      Long64_t cGe_WR;
      Long64_t cFRS_WR;
      
      
   ClassDef(EventCorrelStore,1)
};
#endif //TSCNANLEVENT_H



