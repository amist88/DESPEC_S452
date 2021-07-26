// $Id: TSCNAnlEvent.cxx 755 2011-05-20 08:04:11Z linev $
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

#include "EventCorrelStore.h"
#include "TAidaConfiguration.h"
#define ZERO_ARRAY(x) memset(x, 0, sizeof(x))
void EventCorrelStore::Clear(Option_t *t)
{
       cFRS_AoQ = 0;
       cFRS_ID_x2 = 0;
       cFRS_ID_x4 = 0;
       cFRS_z = 0;
       cFRS_z2 = 0; 
       
    TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();
   
         cdT_AIDA_FRS = 0;
         AIDA_implantation_gate_DSSD1 = false;
         AIDA_implantation_gate_DSSD2 = false;
         AIDA_implantation_gate_DSSD3 = false;
         cImplantIterator = -1;
         cDecayIterator = -1;
         
           ZERO_ARRAY(AIDA_implantation_gate_DSSD1_StripX);
           ZERO_ARRAY(AIDA_implantation_gate_DSSD1_StripY);
         
         cAIDA_dT_imp_decay_hits=0;
         
            cGalE =-1;
            ZERO_ARRAY(cFatE);
            ZERO_ARRAY(cbPlastE);
            cAIDA_WR = -1;
            cbPlast_WR= -1;
            cFAT_WR= -1;
            cGe_WR= -1;
            cFRS_WR= -1;
       
          ZERO_ARRAY(cAIDA_dT_imp_decay);
          ZERO_ARRAY(cAIDA_dT_imp_decay_FRS_gated);        
          ZERO_ARRAY(cAIDAImplantE);
          ZERO_ARRAY(cAIDADecayE);            
      
      ZERO_ARRAY(cFatimaVME_TimeMachine_dT);
      ZERO_ARRAY(cbPlast_TimeMachine_dT);
      ZERO_ARRAY(cFatimaTAMEX_TimeMachine_dT);
      
      cGermanium_TimeMachine_dT=0;
      cAIDA_TimeMachine_dT=0;
      cAIDA_TM_WR=0;
      
                
                 
                 
                 
         //cAIDA_dT_imp_decay = 0;
       //  for(int i =0; i<128; i++){
//            AIDA_implantation_gate_DSSD1_StripX[i] = 0;
//            AIDA_implantation_gate_DSSD1_StripY[i] = 0;
        // }
}
