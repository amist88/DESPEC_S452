// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__SCN
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "./AIDA_Headers.h"
#include "./DESPECAnalysis.h"
#include "./FRS_Detector_System.h"
#include "./EventAnlStore.h"
#include "./FATIMA_Time_Calibration.h"
#include "./AIDA_Decay_Event_Store.h"
#include "./FINGER_Calibrator.h"
#include "./Timestamp.h"
#include "./QDC_751.h"
#include "./TDC_1290.h"
#include "./Germanium_Energy_Calibration.h"
#include "./QDC.h"
#include "./CorrelParameter.h"
#include "./EventUnpackFact.h"
#include "./EventCorrelProc.h"
#include "./White_Rabbit.h"
#include "./FATIMA_TAMEX_Detector_System.h"
#include "./TAidaConfiguration.h"
#include "./Germanium_Time_Calibration.h"
#include "./Raw_Event.h"
#include "./AIDA_Data_Types.h"
#include "./FEBEX.h"
#include "./TAMEX.h"
#include "./AIDA_Processor.h"
#include "./FATIMA_Energy_Calibration.h"
#include "./TFRSParameter.h"
#include "./WR_Structure.h"
#include "./Germanium_Detector_System.h"
#include "./FATIMA_Detector_System.h"
#include "./EventAnlProc.h"
#include "./EventUnpackStore.h"
#include "./AIDA_Detector_System.h"
#include "./EventUnpackProc.h"
#include "./AIDA_Event.h"
#include "./PLASTIC_TAMEX_Detector_System.h"
#include "./EventCorrelStore.h"
#include "./FINGER_Detector_System.h"
#include "./FATIMA_TAMEX_Calibrator.h"
#include "./PLASTIC_TAMEX_Calibrator.h"
#include "./CalibParameter.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_AidaEvent(void *p = 0);
   static void *newArray_AidaEvent(Long_t size, void *p);
   static void delete_AidaEvent(void *p);
   static void deleteArray_AidaEvent(void *p);
   static void destruct_AidaEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AidaEvent*)
   {
      ::AidaEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AidaEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AidaEvent", ::AidaEvent::Class_Version(), "AIDA_Decay_Event_Store.h", 10,
                  typeid(::AidaEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AidaEvent::Dictionary, isa_proxy, 4,
                  sizeof(::AidaEvent) );
      instance.SetNew(&new_AidaEvent);
      instance.SetNewArray(&newArray_AidaEvent);
      instance.SetDelete(&delete_AidaEvent);
      instance.SetDeleteArray(&deleteArray_AidaEvent);
      instance.SetDestructor(&destruct_AidaEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AidaEvent*)
   {
      return GenerateInitInstanceLocal((::AidaEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AidaEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AidaHit(void *p = 0);
   static void *newArray_AidaHit(Long_t size, void *p);
   static void delete_AidaHit(void *p);
   static void deleteArray_AidaHit(void *p);
   static void destruct_AidaHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AidaHit*)
   {
      ::AidaHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AidaHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AidaHit", ::AidaHit::Class_Version(), "AIDA_Decay_Event_Store.h", 75,
                  typeid(::AidaHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AidaHit::Dictionary, isa_proxy, 4,
                  sizeof(::AidaHit) );
      instance.SetNew(&new_AidaHit);
      instance.SetNewArray(&newArray_AidaHit);
      instance.SetDelete(&delete_AidaHit);
      instance.SetDeleteArray(&deleteArray_AidaHit);
      instance.SetDestructor(&destruct_AidaHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AidaHit*)
   {
      return GenerateInitInstanceLocal((::AidaHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AidaHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AidaScaler(void *p = 0);
   static void *newArray_AidaScaler(Long_t size, void *p);
   static void delete_AidaScaler(void *p);
   static void deleteArray_AidaScaler(void *p);
   static void destruct_AidaScaler(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AidaScaler*)
   {
      ::AidaScaler *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AidaScaler >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AidaScaler", ::AidaScaler::Class_Version(), "AIDA_Decay_Event_Store.h", 116,
                  typeid(::AidaScaler), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AidaScaler::Dictionary, isa_proxy, 4,
                  sizeof(::AidaScaler) );
      instance.SetNew(&new_AidaScaler);
      instance.SetNewArray(&newArray_AidaScaler);
      instance.SetDelete(&delete_AidaScaler);
      instance.SetDeleteArray(&deleteArray_AidaScaler);
      instance.SetDestructor(&destruct_AidaScaler);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AidaScaler*)
   {
      return GenerateInitInstanceLocal((::AidaScaler*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AidaScaler*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AIDA_Event(void *p = 0);
   static void *newArray_AIDA_Event(Long_t size, void *p);
   static void delete_AIDA_Event(void *p);
   static void deleteArray_AIDA_Event(void *p);
   static void destruct_AIDA_Event(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AIDA_Event*)
   {
      ::AIDA_Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AIDA_Event >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AIDA_Event", ::AIDA_Event::Class_Version(), "AIDA_Event.h", 11,
                  typeid(::AIDA_Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AIDA_Event::Dictionary, isa_proxy, 4,
                  sizeof(::AIDA_Event) );
      instance.SetNew(&new_AIDA_Event);
      instance.SetNewArray(&newArray_AIDA_Event);
      instance.SetDelete(&delete_AIDA_Event);
      instance.SetDeleteArray(&deleteArray_AIDA_Event);
      instance.SetDestructor(&destruct_AIDA_Event);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AIDA_Event*)
   {
      return GenerateInitInstanceLocal((::AIDA_Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AIDA_Event*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *AidaUnpackData_Dictionary();
   static void AidaUnpackData_TClassManip(TClass*);
   static void *new_AidaUnpackData(void *p = 0);
   static void *newArray_AidaUnpackData(Long_t size, void *p);
   static void delete_AidaUnpackData(void *p);
   static void deleteArray_AidaUnpackData(void *p);
   static void destruct_AidaUnpackData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AidaUnpackData*)
   {
      ::AidaUnpackData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::AidaUnpackData));
      static ::ROOT::TGenericClassInfo 
         instance("AidaUnpackData", "EventUnpackStore.h", 25,
                  typeid(::AidaUnpackData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &AidaUnpackData_Dictionary, isa_proxy, 4,
                  sizeof(::AidaUnpackData) );
      instance.SetNew(&new_AidaUnpackData);
      instance.SetNewArray(&newArray_AidaUnpackData);
      instance.SetDelete(&delete_AidaUnpackData);
      instance.SetDeleteArray(&deleteArray_AidaUnpackData);
      instance.SetDestructor(&destruct_AidaUnpackData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AidaUnpackData*)
   {
      return GenerateInitInstanceLocal((::AidaUnpackData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AidaUnpackData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *AidaUnpackData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::AidaUnpackData*)0x0)->GetClass();
      AidaUnpackData_TClassManip(theClass);
   return theClass;
   }

   static void AidaUnpackData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_EventUnpackStore(void *p = 0);
   static void *newArray_EventUnpackStore(Long_t size, void *p);
   static void delete_EventUnpackStore(void *p);
   static void deleteArray_EventUnpackStore(void *p);
   static void destruct_EventUnpackStore(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventUnpackStore*)
   {
      ::EventUnpackStore *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventUnpackStore >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EventUnpackStore", ::EventUnpackStore::Class_Version(), "EventUnpackStore.h", 36,
                  typeid(::EventUnpackStore), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventUnpackStore::Dictionary, isa_proxy, 4,
                  sizeof(::EventUnpackStore) );
      instance.SetNew(&new_EventUnpackStore);
      instance.SetNewArray(&newArray_EventUnpackStore);
      instance.SetDelete(&delete_EventUnpackStore);
      instance.SetDeleteArray(&deleteArray_EventUnpackStore);
      instance.SetDestructor(&destruct_EventUnpackStore);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventUnpackStore*)
   {
      return GenerateInitInstanceLocal((::EventUnpackStore*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EventUnpackStore*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CalibParameter(void *p = 0);
   static void *newArray_CalibParameter(Long_t size, void *p);
   static void delete_CalibParameter(void *p);
   static void deleteArray_CalibParameter(void *p);
   static void destruct_CalibParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CalibParameter*)
   {
      ::CalibParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CalibParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CalibParameter", ::CalibParameter::Class_Version(), "CalibParameter.h", 7,
                  typeid(::CalibParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CalibParameter::Dictionary, isa_proxy, 4,
                  sizeof(::CalibParameter) );
      instance.SetNew(&new_CalibParameter);
      instance.SetNewArray(&newArray_CalibParameter);
      instance.SetDelete(&delete_CalibParameter);
      instance.SetDeleteArray(&deleteArray_CalibParameter);
      instance.SetDestructor(&destruct_CalibParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CalibParameter*)
   {
      return GenerateInitInstanceLocal((::CalibParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::CalibParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CorrelParameter(void *p = 0);
   static void *newArray_CorrelParameter(Long_t size, void *p);
   static void delete_CorrelParameter(void *p);
   static void deleteArray_CorrelParameter(void *p);
   static void destruct_CorrelParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CorrelParameter*)
   {
      ::CorrelParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CorrelParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CorrelParameter", ::CorrelParameter::Class_Version(), "CorrelParameter.h", 9,
                  typeid(::CorrelParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CorrelParameter::Dictionary, isa_proxy, 4,
                  sizeof(::CorrelParameter) );
      instance.SetNew(&new_CorrelParameter);
      instance.SetNewArray(&newArray_CorrelParameter);
      instance.SetDelete(&delete_CorrelParameter);
      instance.SetDeleteArray(&deleteArray_CorrelParameter);
      instance.SetDestructor(&destruct_CorrelParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CorrelParameter*)
   {
      return GenerateInitInstanceLocal((::CorrelParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::CorrelParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TFRSParameter(void *p = 0);
   static void *newArray_TFRSParameter(Long_t size, void *p);
   static void delete_TFRSParameter(void *p);
   static void deleteArray_TFRSParameter(void *p);
   static void destruct_TFRSParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TFRSParameter*)
   {
      ::TFRSParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TFRSParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TFRSParameter", ::TFRSParameter::Class_Version(), "TFRSParameter.h", 8,
                  typeid(::TFRSParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TFRSParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TFRSParameter) );
      instance.SetNew(&new_TFRSParameter);
      instance.SetNewArray(&newArray_TFRSParameter);
      instance.SetDelete(&delete_TFRSParameter);
      instance.SetDeleteArray(&deleteArray_TFRSParameter);
      instance.SetDestructor(&destruct_TFRSParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TFRSParameter*)
   {
      return GenerateInitInstanceLocal((::TFRSParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TFRSParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Map1(void *p = 0);
   static void *newArray_Map1(Long_t size, void *p);
   static void delete_Map1(void *p);
   static void deleteArray_Map1(void *p);
   static void destruct_Map1(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Map1*)
   {
      ::Map1 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Map1 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Map1", ::Map1::Class_Version(), "TFRSParameter.h", 68,
                  typeid(::Map1), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Map1::Dictionary, isa_proxy, 4,
                  sizeof(::Map1) );
      instance.SetNew(&new_Map1);
      instance.SetNewArray(&newArray_Map1);
      instance.SetDelete(&delete_Map1);
      instance.SetDeleteArray(&deleteArray_Map1);
      instance.SetDestructor(&destruct_Map1);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Map1*)
   {
      return GenerateInitInstanceLocal((::Map1*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Map1*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMWParameter(void *p = 0);
   static void *newArray_TMWParameter(Long_t size, void *p);
   static void delete_TMWParameter(void *p);
   static void deleteArray_TMWParameter(void *p);
   static void destruct_TMWParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMWParameter*)
   {
      ::TMWParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMWParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMWParameter", ::TMWParameter::Class_Version(), "TFRSParameter.h", 80,
                  typeid(::TMWParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TMWParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TMWParameter) );
      instance.SetNew(&new_TMWParameter);
      instance.SetNewArray(&newArray_TMWParameter);
      instance.SetDelete(&delete_TMWParameter);
      instance.SetDeleteArray(&deleteArray_TMWParameter);
      instance.SetDestructor(&destruct_TMWParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMWParameter*)
   {
      return GenerateInitInstanceLocal((::TMWParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TMWParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTPCParameter(void *p = 0);
   static void *newArray_TTPCParameter(Long_t size, void *p);
   static void delete_TTPCParameter(void *p);
   static void deleteArray_TTPCParameter(void *p);
   static void destruct_TTPCParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTPCParameter*)
   {
      ::TTPCParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTPCParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTPCParameter", ::TTPCParameter::Class_Version(), "TFRSParameter.h", 99,
                  typeid(::TTPCParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTPCParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TTPCParameter) );
      instance.SetNew(&new_TTPCParameter);
      instance.SetNewArray(&newArray_TTPCParameter);
      instance.SetDelete(&delete_TTPCParameter);
      instance.SetDeleteArray(&deleteArray_TTPCParameter);
      instance.SetDestructor(&destruct_TTPCParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTPCParameter*)
   {
      return GenerateInitInstanceLocal((::TTPCParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TTPCParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMUSICParameter(void *p = 0);
   static void *newArray_TMUSICParameter(Long_t size, void *p);
   static void delete_TMUSICParameter(void *p);
   static void deleteArray_TMUSICParameter(void *p);
   static void destruct_TMUSICParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMUSICParameter*)
   {
      ::TMUSICParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMUSICParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMUSICParameter", ::TMUSICParameter::Class_Version(), "TFRSParameter.h", 132,
                  typeid(::TMUSICParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TMUSICParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TMUSICParameter) );
      instance.SetNew(&new_TMUSICParameter);
      instance.SetNewArray(&newArray_TMUSICParameter);
      instance.SetDelete(&delete_TMUSICParameter);
      instance.SetDeleteArray(&deleteArray_TMUSICParameter);
      instance.SetDestructor(&destruct_TMUSICParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMUSICParameter*)
   {
      return GenerateInitInstanceLocal((::TMUSICParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TSCIParameter(void *p = 0);
   static void *newArray_TSCIParameter(Long_t size, void *p);
   static void delete_TSCIParameter(void *p);
   static void deleteArray_TSCIParameter(void *p);
   static void destruct_TSCIParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TSCIParameter*)
   {
      ::TSCIParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TSCIParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TSCIParameter", ::TSCIParameter::Class_Version(), "TFRSParameter.h", 169,
                  typeid(::TSCIParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TSCIParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TSCIParameter) );
      instance.SetNew(&new_TSCIParameter);
      instance.SetNewArray(&newArray_TSCIParameter);
      instance.SetDelete(&delete_TSCIParameter);
      instance.SetDeleteArray(&deleteArray_TSCIParameter);
      instance.SetDestructor(&destruct_TSCIParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TSCIParameter*)
   {
      return GenerateInitInstanceLocal((::TSCIParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TSCIParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TIDParameter(void *p = 0);
   static void *newArray_TIDParameter(Long_t size, void *p);
   static void delete_TIDParameter(void *p);
   static void deleteArray_TIDParameter(void *p);
   static void destruct_TIDParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TIDParameter*)
   {
      ::TIDParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TIDParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TIDParameter", ::TIDParameter::Class_Version(), "TFRSParameter.h", 226,
                  typeid(::TIDParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TIDParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TIDParameter) );
      instance.SetNew(&new_TIDParameter);
      instance.SetNewArray(&newArray_TIDParameter);
      instance.SetDelete(&delete_TIDParameter);
      instance.SetDeleteArray(&deleteArray_TIDParameter);
      instance.SetDestructor(&destruct_TIDParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TIDParameter*)
   {
      return GenerateInitInstanceLocal((::TIDParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TIDParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TSIParameter(void *p = 0);
   static void *newArray_TSIParameter(Long_t size, void *p);
   static void delete_TSIParameter(void *p);
   static void deleteArray_TSIParameter(void *p);
   static void destruct_TSIParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TSIParameter*)
   {
      ::TSIParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TSIParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TSIParameter", ::TSIParameter::Class_Version(), "TFRSParameter.h", 305,
                  typeid(::TSIParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TSIParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TSIParameter) );
      instance.SetNew(&new_TSIParameter);
      instance.SetNewArray(&newArray_TSIParameter);
      instance.SetDelete(&delete_TSIParameter);
      instance.SetDeleteArray(&deleteArray_TSIParameter);
      instance.SetDestructor(&destruct_TSIParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TSIParameter*)
   {
      return GenerateInitInstanceLocal((::TSIParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TSIParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TMRTOFMSParameter(void *p = 0);
   static void *newArray_TMRTOFMSParameter(Long_t size, void *p);
   static void delete_TMRTOFMSParameter(void *p);
   static void deleteArray_TMRTOFMSParameter(void *p);
   static void destruct_TMRTOFMSParameter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMRTOFMSParameter*)
   {
      ::TMRTOFMSParameter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMRTOFMSParameter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMRTOFMSParameter", ::TMRTOFMSParameter::Class_Version(), "TFRSParameter.h", 352,
                  typeid(::TMRTOFMSParameter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TMRTOFMSParameter::Dictionary, isa_proxy, 4,
                  sizeof(::TMRTOFMSParameter) );
      instance.SetNew(&new_TMRTOFMSParameter);
      instance.SetNewArray(&newArray_TMRTOFMSParameter);
      instance.SetDelete(&delete_TMRTOFMSParameter);
      instance.SetDeleteArray(&deleteArray_TMRTOFMSParameter);
      instance.SetDestructor(&destruct_TMRTOFMSParameter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMRTOFMSParameter*)
   {
      return GenerateInitInstanceLocal((::TMRTOFMSParameter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *FRS_Detector_System_Dictionary();
   static void FRS_Detector_System_TClassManip(TClass*);
   static void *new_FRS_Detector_System(void *p = 0);
   static void *newArray_FRS_Detector_System(Long_t size, void *p);
   static void delete_FRS_Detector_System(void *p);
   static void deleteArray_FRS_Detector_System(void *p);
   static void destruct_FRS_Detector_System(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FRS_Detector_System*)
   {
      ::FRS_Detector_System *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FRS_Detector_System));
      static ::ROOT::TGenericClassInfo 
         instance("FRS_Detector_System", "FRS_Detector_System.h", 64,
                  typeid(::FRS_Detector_System), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FRS_Detector_System_Dictionary, isa_proxy, 4,
                  sizeof(::FRS_Detector_System) );
      instance.SetNew(&new_FRS_Detector_System);
      instance.SetNewArray(&newArray_FRS_Detector_System);
      instance.SetDelete(&delete_FRS_Detector_System);
      instance.SetDeleteArray(&deleteArray_FRS_Detector_System);
      instance.SetDestructor(&destruct_FRS_Detector_System);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FRS_Detector_System*)
   {
      return GenerateInitInstanceLocal((::FRS_Detector_System*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FRS_Detector_System*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FRS_Detector_System_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FRS_Detector_System*)0x0)->GetClass();
      FRS_Detector_System_TClassManip(theClass);
   return theClass;
   }

   static void FRS_Detector_System_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_EventUnpackProc(void *p = 0);
   static void *newArray_EventUnpackProc(Long_t size, void *p);
   static void delete_EventUnpackProc(void *p);
   static void deleteArray_EventUnpackProc(void *p);
   static void destruct_EventUnpackProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventUnpackProc*)
   {
      ::EventUnpackProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventUnpackProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EventUnpackProc", ::EventUnpackProc::Class_Version(), "EventUnpackProc.h", 71,
                  typeid(::EventUnpackProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventUnpackProc::Dictionary, isa_proxy, 4,
                  sizeof(::EventUnpackProc) );
      instance.SetNew(&new_EventUnpackProc);
      instance.SetNewArray(&newArray_EventUnpackProc);
      instance.SetDelete(&delete_EventUnpackProc);
      instance.SetDeleteArray(&deleteArray_EventUnpackProc);
      instance.SetDestructor(&destruct_EventUnpackProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventUnpackProc*)
   {
      return GenerateInitInstanceLocal((::EventUnpackProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EventUnpackProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EventUnpackFact(void *p = 0);
   static void *newArray_EventUnpackFact(Long_t size, void *p);
   static void delete_EventUnpackFact(void *p);
   static void deleteArray_EventUnpackFact(void *p);
   static void destruct_EventUnpackFact(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventUnpackFact*)
   {
      ::EventUnpackFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventUnpackFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EventUnpackFact", ::EventUnpackFact::Class_Version(), "EventUnpackFact.h", 15,
                  typeid(::EventUnpackFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventUnpackFact::Dictionary, isa_proxy, 4,
                  sizeof(::EventUnpackFact) );
      instance.SetNew(&new_EventUnpackFact);
      instance.SetNewArray(&newArray_EventUnpackFact);
      instance.SetDelete(&delete_EventUnpackFact);
      instance.SetDeleteArray(&deleteArray_EventUnpackFact);
      instance.SetDestructor(&destruct_EventUnpackFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventUnpackFact*)
   {
      return GenerateInitInstanceLocal((::EventUnpackFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EventUnpackFact*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_DESPECAnalysis(void *p = 0);
   static void *newArray_DESPECAnalysis(Long_t size, void *p);
   static void delete_DESPECAnalysis(void *p);
   static void deleteArray_DESPECAnalysis(void *p);
   static void destruct_DESPECAnalysis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DESPECAnalysis*)
   {
      ::DESPECAnalysis *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::DESPECAnalysis >(0);
      static ::ROOT::TGenericClassInfo 
         instance("DESPECAnalysis", ::DESPECAnalysis::Class_Version(), "DESPECAnalysis.h", 30,
                  typeid(::DESPECAnalysis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::DESPECAnalysis::Dictionary, isa_proxy, 4,
                  sizeof(::DESPECAnalysis) );
      instance.SetNew(&new_DESPECAnalysis);
      instance.SetNewArray(&newArray_DESPECAnalysis);
      instance.SetDelete(&delete_DESPECAnalysis);
      instance.SetDeleteArray(&deleteArray_DESPECAnalysis);
      instance.SetDestructor(&destruct_DESPECAnalysis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DESPECAnalysis*)
   {
      return GenerateInitInstanceLocal((::DESPECAnalysis*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::DESPECAnalysis*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *AidaAnlData_Dictionary();
   static void AidaAnlData_TClassManip(TClass*);
   static void *new_AidaAnlData(void *p = 0);
   static void *newArray_AidaAnlData(Long_t size, void *p);
   static void delete_AidaAnlData(void *p);
   static void deleteArray_AidaAnlData(void *p);
   static void destruct_AidaAnlData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AidaAnlData*)
   {
      ::AidaAnlData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::AidaAnlData));
      static ::ROOT::TGenericClassInfo 
         instance("AidaAnlData", "EventAnlStore.h", 24,
                  typeid(::AidaAnlData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &AidaAnlData_Dictionary, isa_proxy, 4,
                  sizeof(::AidaAnlData) );
      instance.SetNew(&new_AidaAnlData);
      instance.SetNewArray(&newArray_AidaAnlData);
      instance.SetDelete(&delete_AidaAnlData);
      instance.SetDeleteArray(&deleteArray_AidaAnlData);
      instance.SetDestructor(&destruct_AidaAnlData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AidaAnlData*)
   {
      return GenerateInitInstanceLocal((::AidaAnlData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AidaAnlData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *AidaAnlData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::AidaAnlData*)0x0)->GetClass();
      AidaAnlData_TClassManip(theClass);
   return theClass;
   }

   static void AidaAnlData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_EventAnlStore(void *p = 0);
   static void *newArray_EventAnlStore(Long_t size, void *p);
   static void delete_EventAnlStore(void *p);
   static void deleteArray_EventAnlStore(void *p);
   static void destruct_EventAnlStore(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventAnlStore*)
   {
      ::EventAnlStore *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventAnlStore >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EventAnlStore", ::EventAnlStore::Class_Version(), "EventAnlStore.h", 28,
                  typeid(::EventAnlStore), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventAnlStore::Dictionary, isa_proxy, 4,
                  sizeof(::EventAnlStore) );
      instance.SetNew(&new_EventAnlStore);
      instance.SetNewArray(&newArray_EventAnlStore);
      instance.SetDelete(&delete_EventAnlStore);
      instance.SetDeleteArray(&deleteArray_EventAnlStore);
      instance.SetDestructor(&destruct_EventAnlStore);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventAnlStore*)
   {
      return GenerateInitInstanceLocal((::EventAnlStore*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EventAnlStore*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AidaHitPID(void *p = 0);
   static void *newArray_AidaHitPID(Long_t size, void *p);
   static void delete_AidaHitPID(void *p);
   static void deleteArray_AidaHitPID(void *p);
   static void destruct_AidaHitPID(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AidaHitPID*)
   {
      ::AidaHitPID *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AidaHitPID >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AidaHitPID", ::AidaHitPID::Class_Version(), "EventCorrelProc.h", 43,
                  typeid(::AidaHitPID), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AidaHitPID::Dictionary, isa_proxy, 4,
                  sizeof(::AidaHitPID) );
      instance.SetNew(&new_AidaHitPID);
      instance.SetNewArray(&newArray_AidaHitPID);
      instance.SetDelete(&delete_AidaHitPID);
      instance.SetDeleteArray(&deleteArray_AidaHitPID);
      instance.SetDestructor(&destruct_AidaHitPID);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AidaHitPID*)
   {
      return GenerateInitInstanceLocal((::AidaHitPID*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AidaHitPID*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EventCorrelProc(void *p = 0);
   static void *newArray_EventCorrelProc(Long_t size, void *p);
   static void delete_EventCorrelProc(void *p);
   static void deleteArray_EventCorrelProc(void *p);
   static void destruct_EventCorrelProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventCorrelProc*)
   {
      ::EventCorrelProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventCorrelProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EventCorrelProc", ::EventCorrelProc::Class_Version(), "EventCorrelProc.h", 92,
                  typeid(::EventCorrelProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventCorrelProc::Dictionary, isa_proxy, 4,
                  sizeof(::EventCorrelProc) );
      instance.SetNew(&new_EventCorrelProc);
      instance.SetNewArray(&newArray_EventCorrelProc);
      instance.SetDelete(&delete_EventCorrelProc);
      instance.SetDeleteArray(&deleteArray_EventCorrelProc);
      instance.SetDestructor(&destruct_EventCorrelProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventCorrelProc*)
   {
      return GenerateInitInstanceLocal((::EventCorrelProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EventCorrelProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EventAnlProc(void *p = 0);
   static void *newArray_EventAnlProc(Long_t size, void *p);
   static void delete_EventAnlProc(void *p);
   static void deleteArray_EventAnlProc(void *p);
   static void destruct_EventAnlProc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventAnlProc*)
   {
      ::EventAnlProc *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventAnlProc >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EventAnlProc", ::EventAnlProc::Class_Version(), "EventAnlProc.h", 47,
                  typeid(::EventAnlProc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventAnlProc::Dictionary, isa_proxy, 4,
                  sizeof(::EventAnlProc) );
      instance.SetNew(&new_EventAnlProc);
      instance.SetNewArray(&newArray_EventAnlProc);
      instance.SetDelete(&delete_EventAnlProc);
      instance.SetDeleteArray(&deleteArray_EventAnlProc);
      instance.SetDestructor(&destruct_EventAnlProc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventAnlProc*)
   {
      return GenerateInitInstanceLocal((::EventAnlProc*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EventAnlProc*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EventCorrelStore(void *p = 0);
   static void *newArray_EventCorrelStore(Long_t size, void *p);
   static void delete_EventCorrelStore(void *p);
   static void deleteArray_EventCorrelStore(void *p);
   static void destruct_EventCorrelStore(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventCorrelStore*)
   {
      ::EventCorrelStore *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventCorrelStore >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EventCorrelStore", ::EventCorrelStore::Class_Version(), "EventCorrelStore.h", 21,
                  typeid(::EventCorrelStore), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventCorrelStore::Dictionary, isa_proxy, 4,
                  sizeof(::EventCorrelStore) );
      instance.SetNew(&new_EventCorrelStore);
      instance.SetNewArray(&newArray_EventCorrelStore);
      instance.SetDelete(&delete_EventCorrelStore);
      instance.SetDeleteArray(&deleteArray_EventCorrelStore);
      instance.SetDestructor(&destruct_EventCorrelStore);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventCorrelStore*)
   {
      return GenerateInitInstanceLocal((::EventCorrelStore*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EventCorrelStore*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr AidaEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AidaEvent::Class_Name()
{
   return "AidaEvent";
}

//______________________________________________________________________________
const char *AidaEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AidaEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AidaEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AidaEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AidaEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AidaEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AidaEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AidaEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AidaHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AidaHit::Class_Name()
{
   return "AidaHit";
}

//______________________________________________________________________________
const char *AidaHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AidaHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AidaHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AidaHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AidaHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AidaHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AidaHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AidaHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AidaScaler::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AidaScaler::Class_Name()
{
   return "AidaScaler";
}

//______________________________________________________________________________
const char *AidaScaler::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AidaScaler*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AidaScaler::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AidaScaler*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AidaScaler::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AidaScaler*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AidaScaler::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AidaScaler*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AIDA_Event::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AIDA_Event::Class_Name()
{
   return "AIDA_Event";
}

//______________________________________________________________________________
const char *AIDA_Event::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AIDA_Event*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AIDA_Event::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AIDA_Event*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AIDA_Event::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AIDA_Event*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AIDA_Event::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AIDA_Event*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventUnpackStore::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EventUnpackStore::Class_Name()
{
   return "EventUnpackStore";
}

//______________________________________________________________________________
const char *EventUnpackStore::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackStore*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EventUnpackStore::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackStore*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventUnpackStore::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackStore*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventUnpackStore::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackStore*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr CalibParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CalibParameter::Class_Name()
{
   return "CalibParameter";
}

//______________________________________________________________________________
const char *CalibParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CalibParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CalibParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CalibParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CalibParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CalibParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CalibParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CalibParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr CorrelParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CorrelParameter::Class_Name()
{
   return "CorrelParameter";
}

//______________________________________________________________________________
const char *CorrelParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CorrelParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CorrelParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CorrelParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CorrelParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CorrelParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CorrelParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CorrelParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TFRSParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TFRSParameter::Class_Name()
{
   return "TFRSParameter";
}

//______________________________________________________________________________
const char *TFRSParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TFRSParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TFRSParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TFRSParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TFRSParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TFRSParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Map1::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Map1::Class_Name()
{
   return "Map1";
}

//______________________________________________________________________________
const char *Map1::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Map1*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Map1::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Map1*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Map1::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Map1*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Map1::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Map1*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TMWParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TMWParameter::Class_Name()
{
   return "TMWParameter";
}

//______________________________________________________________________________
const char *TMWParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMWParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMWParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMWParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TMWParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMWParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TMWParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMWParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TTPCParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TTPCParameter::Class_Name()
{
   return "TTPCParameter";
}

//______________________________________________________________________________
const char *TTPCParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTPCParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TTPCParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTPCParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TTPCParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTPCParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TTPCParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTPCParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TMUSICParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TMUSICParameter::Class_Name()
{
   return "TMUSICParameter";
}

//______________________________________________________________________________
const char *TMUSICParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMUSICParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TMUSICParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TMUSICParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMUSICParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TSCIParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TSCIParameter::Class_Name()
{
   return "TSCIParameter";
}

//______________________________________________________________________________
const char *TSCIParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSCIParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TSCIParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSCIParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TSCIParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSCIParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TSCIParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSCIParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TIDParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TIDParameter::Class_Name()
{
   return "TIDParameter";
}

//______________________________________________________________________________
const char *TIDParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TIDParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TIDParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TIDParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TIDParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TIDParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TIDParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TIDParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TSIParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TSIParameter::Class_Name()
{
   return "TSIParameter";
}

//______________________________________________________________________________
const char *TSIParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSIParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TSIParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TSIParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TSIParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSIParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TSIParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TSIParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TMRTOFMSParameter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TMRTOFMSParameter::Class_Name()
{
   return "TMRTOFMSParameter";
}

//______________________________________________________________________________
const char *TMRTOFMSParameter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMRTOFMSParameter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TMRTOFMSParameter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TMRTOFMSParameter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMRTOFMSParameter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventUnpackProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EventUnpackProc::Class_Name()
{
   return "EventUnpackProc";
}

//______________________________________________________________________________
const char *EventUnpackProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EventUnpackProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventUnpackProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventUnpackProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventUnpackFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EventUnpackFact::Class_Name()
{
   return "EventUnpackFact";
}

//______________________________________________________________________________
const char *EventUnpackFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EventUnpackFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventUnpackFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventUnpackFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventUnpackFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr DESPECAnalysis::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *DESPECAnalysis::Class_Name()
{
   return "DESPECAnalysis";
}

//______________________________________________________________________________
const char *DESPECAnalysis::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DESPECAnalysis*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int DESPECAnalysis::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DESPECAnalysis*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DESPECAnalysis::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DESPECAnalysis*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DESPECAnalysis::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DESPECAnalysis*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventAnlStore::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EventAnlStore::Class_Name()
{
   return "EventAnlStore";
}

//______________________________________________________________________________
const char *EventAnlStore::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventAnlStore*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EventAnlStore::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventAnlStore*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventAnlStore::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventAnlStore*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventAnlStore::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventAnlStore*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AidaHitPID::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AidaHitPID::Class_Name()
{
   return "AidaHitPID";
}

//______________________________________________________________________________
const char *AidaHitPID::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AidaHitPID*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AidaHitPID::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AidaHitPID*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AidaHitPID::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AidaHitPID*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AidaHitPID::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AidaHitPID*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventCorrelProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EventCorrelProc::Class_Name()
{
   return "EventCorrelProc";
}

//______________________________________________________________________________
const char *EventCorrelProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventCorrelProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EventCorrelProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventCorrelProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventCorrelProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventCorrelProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventCorrelProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventCorrelProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventAnlProc::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EventAnlProc::Class_Name()
{
   return "EventAnlProc";
}

//______________________________________________________________________________
const char *EventAnlProc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventAnlProc*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EventAnlProc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventAnlProc*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventAnlProc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventAnlProc*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventAnlProc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventAnlProc*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventCorrelStore::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EventCorrelStore::Class_Name()
{
   return "EventCorrelStore";
}

//______________________________________________________________________________
const char *EventCorrelStore::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventCorrelStore*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EventCorrelStore::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventCorrelStore*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventCorrelStore::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventCorrelStore*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventCorrelStore::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventCorrelStore*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void AidaEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class AidaEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AidaEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(AidaEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AidaEvent(void *p) {
      return  p ? new(p) ::AidaEvent : new ::AidaEvent;
   }
   static void *newArray_AidaEvent(Long_t nElements, void *p) {
      return p ? new(p) ::AidaEvent[nElements] : new ::AidaEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_AidaEvent(void *p) {
      delete ((::AidaEvent*)p);
   }
   static void deleteArray_AidaEvent(void *p) {
      delete [] ((::AidaEvent*)p);
   }
   static void destruct_AidaEvent(void *p) {
      typedef ::AidaEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AidaEvent

//______________________________________________________________________________
void AidaHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class AidaHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AidaHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(AidaHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AidaHit(void *p) {
      return  p ? new(p) ::AidaHit : new ::AidaHit;
   }
   static void *newArray_AidaHit(Long_t nElements, void *p) {
      return p ? new(p) ::AidaHit[nElements] : new ::AidaHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_AidaHit(void *p) {
      delete ((::AidaHit*)p);
   }
   static void deleteArray_AidaHit(void *p) {
      delete [] ((::AidaHit*)p);
   }
   static void destruct_AidaHit(void *p) {
      typedef ::AidaHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AidaHit

//______________________________________________________________________________
void AidaScaler::Streamer(TBuffer &R__b)
{
   // Stream an object of class AidaScaler.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AidaScaler::Class(),this);
   } else {
      R__b.WriteClassBuffer(AidaScaler::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AidaScaler(void *p) {
      return  p ? new(p) ::AidaScaler : new ::AidaScaler;
   }
   static void *newArray_AidaScaler(Long_t nElements, void *p) {
      return p ? new(p) ::AidaScaler[nElements] : new ::AidaScaler[nElements];
   }
   // Wrapper around operator delete
   static void delete_AidaScaler(void *p) {
      delete ((::AidaScaler*)p);
   }
   static void deleteArray_AidaScaler(void *p) {
      delete [] ((::AidaScaler*)p);
   }
   static void destruct_AidaScaler(void *p) {
      typedef ::AidaScaler current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AidaScaler

//______________________________________________________________________________
void AIDA_Event::Streamer(TBuffer &R__b)
{
   // Stream an object of class AIDA_Event.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AIDA_Event::Class(),this);
   } else {
      R__b.WriteClassBuffer(AIDA_Event::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AIDA_Event(void *p) {
      return  p ? new(p) ::AIDA_Event : new ::AIDA_Event;
   }
   static void *newArray_AIDA_Event(Long_t nElements, void *p) {
      return p ? new(p) ::AIDA_Event[nElements] : new ::AIDA_Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_AIDA_Event(void *p) {
      delete ((::AIDA_Event*)p);
   }
   static void deleteArray_AIDA_Event(void *p) {
      delete [] ((::AIDA_Event*)p);
   }
   static void destruct_AIDA_Event(void *p) {
      typedef ::AIDA_Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AIDA_Event

namespace ROOT {
   // Wrappers around operator new
   static void *new_AidaUnpackData(void *p) {
      return  p ? new(p) ::AidaUnpackData : new ::AidaUnpackData;
   }
   static void *newArray_AidaUnpackData(Long_t nElements, void *p) {
      return p ? new(p) ::AidaUnpackData[nElements] : new ::AidaUnpackData[nElements];
   }
   // Wrapper around operator delete
   static void delete_AidaUnpackData(void *p) {
      delete ((::AidaUnpackData*)p);
   }
   static void deleteArray_AidaUnpackData(void *p) {
      delete [] ((::AidaUnpackData*)p);
   }
   static void destruct_AidaUnpackData(void *p) {
      typedef ::AidaUnpackData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AidaUnpackData

//______________________________________________________________________________
void EventUnpackStore::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventUnpackStore.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventUnpackStore::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventUnpackStore::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventUnpackStore(void *p) {
      return  p ? new(p) ::EventUnpackStore : new ::EventUnpackStore;
   }
   static void *newArray_EventUnpackStore(Long_t nElements, void *p) {
      return p ? new(p) ::EventUnpackStore[nElements] : new ::EventUnpackStore[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventUnpackStore(void *p) {
      delete ((::EventUnpackStore*)p);
   }
   static void deleteArray_EventUnpackStore(void *p) {
      delete [] ((::EventUnpackStore*)p);
   }
   static void destruct_EventUnpackStore(void *p) {
      typedef ::EventUnpackStore current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventUnpackStore

//______________________________________________________________________________
void CalibParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class CalibParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CalibParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(CalibParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CalibParameter(void *p) {
      return  p ? new(p) ::CalibParameter : new ::CalibParameter;
   }
   static void *newArray_CalibParameter(Long_t nElements, void *p) {
      return p ? new(p) ::CalibParameter[nElements] : new ::CalibParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_CalibParameter(void *p) {
      delete ((::CalibParameter*)p);
   }
   static void deleteArray_CalibParameter(void *p) {
      delete [] ((::CalibParameter*)p);
   }
   static void destruct_CalibParameter(void *p) {
      typedef ::CalibParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CalibParameter

//______________________________________________________________________________
void CorrelParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class CorrelParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CorrelParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(CorrelParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CorrelParameter(void *p) {
      return  p ? new(p) ::CorrelParameter : new ::CorrelParameter;
   }
   static void *newArray_CorrelParameter(Long_t nElements, void *p) {
      return p ? new(p) ::CorrelParameter[nElements] : new ::CorrelParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_CorrelParameter(void *p) {
      delete ((::CorrelParameter*)p);
   }
   static void deleteArray_CorrelParameter(void *p) {
      delete [] ((::CorrelParameter*)p);
   }
   static void destruct_CorrelParameter(void *p) {
      typedef ::CorrelParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CorrelParameter

//______________________________________________________________________________
void TFRSParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TFRSParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TFRSParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TFRSParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TFRSParameter(void *p) {
      return  p ? new(p) ::TFRSParameter : new ::TFRSParameter;
   }
   static void *newArray_TFRSParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TFRSParameter[nElements] : new ::TFRSParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TFRSParameter(void *p) {
      delete ((::TFRSParameter*)p);
   }
   static void deleteArray_TFRSParameter(void *p) {
      delete [] ((::TFRSParameter*)p);
   }
   static void destruct_TFRSParameter(void *p) {
      typedef ::TFRSParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TFRSParameter

//______________________________________________________________________________
void Map1::Streamer(TBuffer &R__b)
{
   // Stream an object of class Map1.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Map1::Class(),this);
   } else {
      R__b.WriteClassBuffer(Map1::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Map1(void *p) {
      return  p ? new(p) ::Map1 : new ::Map1;
   }
   static void *newArray_Map1(Long_t nElements, void *p) {
      return p ? new(p) ::Map1[nElements] : new ::Map1[nElements];
   }
   // Wrapper around operator delete
   static void delete_Map1(void *p) {
      delete ((::Map1*)p);
   }
   static void deleteArray_Map1(void *p) {
      delete [] ((::Map1*)p);
   }
   static void destruct_Map1(void *p) {
      typedef ::Map1 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Map1

//______________________________________________________________________________
void TMWParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMWParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMWParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMWParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMWParameter(void *p) {
      return  p ? new(p) ::TMWParameter : new ::TMWParameter;
   }
   static void *newArray_TMWParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TMWParameter[nElements] : new ::TMWParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMWParameter(void *p) {
      delete ((::TMWParameter*)p);
   }
   static void deleteArray_TMWParameter(void *p) {
      delete [] ((::TMWParameter*)p);
   }
   static void destruct_TMWParameter(void *p) {
      typedef ::TMWParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMWParameter

//______________________________________________________________________________
void TTPCParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTPCParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTPCParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTPCParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TTPCParameter(void *p) {
      return  p ? new(p) ::TTPCParameter : new ::TTPCParameter;
   }
   static void *newArray_TTPCParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TTPCParameter[nElements] : new ::TTPCParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTPCParameter(void *p) {
      delete ((::TTPCParameter*)p);
   }
   static void deleteArray_TTPCParameter(void *p) {
      delete [] ((::TTPCParameter*)p);
   }
   static void destruct_TTPCParameter(void *p) {
      typedef ::TTPCParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTPCParameter

//______________________________________________________________________________
void TMUSICParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMUSICParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMUSICParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMUSICParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMUSICParameter(void *p) {
      return  p ? new(p) ::TMUSICParameter : new ::TMUSICParameter;
   }
   static void *newArray_TMUSICParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TMUSICParameter[nElements] : new ::TMUSICParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMUSICParameter(void *p) {
      delete ((::TMUSICParameter*)p);
   }
   static void deleteArray_TMUSICParameter(void *p) {
      delete [] ((::TMUSICParameter*)p);
   }
   static void destruct_TMUSICParameter(void *p) {
      typedef ::TMUSICParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMUSICParameter

//______________________________________________________________________________
void TSCIParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TSCIParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TSCIParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TSCIParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TSCIParameter(void *p) {
      return  p ? new(p) ::TSCIParameter : new ::TSCIParameter;
   }
   static void *newArray_TSCIParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TSCIParameter[nElements] : new ::TSCIParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TSCIParameter(void *p) {
      delete ((::TSCIParameter*)p);
   }
   static void deleteArray_TSCIParameter(void *p) {
      delete [] ((::TSCIParameter*)p);
   }
   static void destruct_TSCIParameter(void *p) {
      typedef ::TSCIParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TSCIParameter

//______________________________________________________________________________
void TIDParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TIDParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TIDParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TIDParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TIDParameter(void *p) {
      return  p ? new(p) ::TIDParameter : new ::TIDParameter;
   }
   static void *newArray_TIDParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TIDParameter[nElements] : new ::TIDParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TIDParameter(void *p) {
      delete ((::TIDParameter*)p);
   }
   static void deleteArray_TIDParameter(void *p) {
      delete [] ((::TIDParameter*)p);
   }
   static void destruct_TIDParameter(void *p) {
      typedef ::TIDParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TIDParameter

//______________________________________________________________________________
void TSIParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TSIParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TSIParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TSIParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TSIParameter(void *p) {
      return  p ? new(p) ::TSIParameter : new ::TSIParameter;
   }
   static void *newArray_TSIParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TSIParameter[nElements] : new ::TSIParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TSIParameter(void *p) {
      delete ((::TSIParameter*)p);
   }
   static void deleteArray_TSIParameter(void *p) {
      delete [] ((::TSIParameter*)p);
   }
   static void destruct_TSIParameter(void *p) {
      typedef ::TSIParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TSIParameter

//______________________________________________________________________________
void TMRTOFMSParameter::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMRTOFMSParameter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TMRTOFMSParameter::Class(),this);
   } else {
      R__b.WriteClassBuffer(TMRTOFMSParameter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMRTOFMSParameter(void *p) {
      return  p ? new(p) ::TMRTOFMSParameter : new ::TMRTOFMSParameter;
   }
   static void *newArray_TMRTOFMSParameter(Long_t nElements, void *p) {
      return p ? new(p) ::TMRTOFMSParameter[nElements] : new ::TMRTOFMSParameter[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMRTOFMSParameter(void *p) {
      delete ((::TMRTOFMSParameter*)p);
   }
   static void deleteArray_TMRTOFMSParameter(void *p) {
      delete [] ((::TMRTOFMSParameter*)p);
   }
   static void destruct_TMRTOFMSParameter(void *p) {
      typedef ::TMRTOFMSParameter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TMRTOFMSParameter

namespace ROOT {
   // Wrappers around operator new
   static void *new_FRS_Detector_System(void *p) {
      return  p ? new(p) ::FRS_Detector_System : new ::FRS_Detector_System;
   }
   static void *newArray_FRS_Detector_System(Long_t nElements, void *p) {
      return p ? new(p) ::FRS_Detector_System[nElements] : new ::FRS_Detector_System[nElements];
   }
   // Wrapper around operator delete
   static void delete_FRS_Detector_System(void *p) {
      delete ((::FRS_Detector_System*)p);
   }
   static void deleteArray_FRS_Detector_System(void *p) {
      delete [] ((::FRS_Detector_System*)p);
   }
   static void destruct_FRS_Detector_System(void *p) {
      typedef ::FRS_Detector_System current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FRS_Detector_System

//______________________________________________________________________________
void EventUnpackProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventUnpackProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventUnpackProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventUnpackProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventUnpackProc(void *p) {
      return  p ? new(p) ::EventUnpackProc : new ::EventUnpackProc;
   }
   static void *newArray_EventUnpackProc(Long_t nElements, void *p) {
      return p ? new(p) ::EventUnpackProc[nElements] : new ::EventUnpackProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventUnpackProc(void *p) {
      delete ((::EventUnpackProc*)p);
   }
   static void deleteArray_EventUnpackProc(void *p) {
      delete [] ((::EventUnpackProc*)p);
   }
   static void destruct_EventUnpackProc(void *p) {
      typedef ::EventUnpackProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventUnpackProc

//______________________________________________________________________________
void EventUnpackFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventUnpackFact.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventUnpackFact::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventUnpackFact::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventUnpackFact(void *p) {
      return  p ? new(p) ::EventUnpackFact : new ::EventUnpackFact;
   }
   static void *newArray_EventUnpackFact(Long_t nElements, void *p) {
      return p ? new(p) ::EventUnpackFact[nElements] : new ::EventUnpackFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventUnpackFact(void *p) {
      delete ((::EventUnpackFact*)p);
   }
   static void deleteArray_EventUnpackFact(void *p) {
      delete [] ((::EventUnpackFact*)p);
   }
   static void destruct_EventUnpackFact(void *p) {
      typedef ::EventUnpackFact current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventUnpackFact

//______________________________________________________________________________
void DESPECAnalysis::Streamer(TBuffer &R__b)
{
   // Stream an object of class DESPECAnalysis.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(DESPECAnalysis::Class(),this);
   } else {
      R__b.WriteClassBuffer(DESPECAnalysis::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_DESPECAnalysis(void *p) {
      return  p ? new(p) ::DESPECAnalysis : new ::DESPECAnalysis;
   }
   static void *newArray_DESPECAnalysis(Long_t nElements, void *p) {
      return p ? new(p) ::DESPECAnalysis[nElements] : new ::DESPECAnalysis[nElements];
   }
   // Wrapper around operator delete
   static void delete_DESPECAnalysis(void *p) {
      delete ((::DESPECAnalysis*)p);
   }
   static void deleteArray_DESPECAnalysis(void *p) {
      delete [] ((::DESPECAnalysis*)p);
   }
   static void destruct_DESPECAnalysis(void *p) {
      typedef ::DESPECAnalysis current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DESPECAnalysis

namespace ROOT {
   // Wrappers around operator new
   static void *new_AidaAnlData(void *p) {
      return  p ? new(p) ::AidaAnlData : new ::AidaAnlData;
   }
   static void *newArray_AidaAnlData(Long_t nElements, void *p) {
      return p ? new(p) ::AidaAnlData[nElements] : new ::AidaAnlData[nElements];
   }
   // Wrapper around operator delete
   static void delete_AidaAnlData(void *p) {
      delete ((::AidaAnlData*)p);
   }
   static void deleteArray_AidaAnlData(void *p) {
      delete [] ((::AidaAnlData*)p);
   }
   static void destruct_AidaAnlData(void *p) {
      typedef ::AidaAnlData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AidaAnlData

//______________________________________________________________________________
void EventAnlStore::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventAnlStore.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventAnlStore::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventAnlStore::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventAnlStore(void *p) {
      return  p ? new(p) ::EventAnlStore : new ::EventAnlStore;
   }
   static void *newArray_EventAnlStore(Long_t nElements, void *p) {
      return p ? new(p) ::EventAnlStore[nElements] : new ::EventAnlStore[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventAnlStore(void *p) {
      delete ((::EventAnlStore*)p);
   }
   static void deleteArray_EventAnlStore(void *p) {
      delete [] ((::EventAnlStore*)p);
   }
   static void destruct_EventAnlStore(void *p) {
      typedef ::EventAnlStore current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventAnlStore

//______________________________________________________________________________
void AidaHitPID::Streamer(TBuffer &R__b)
{
   // Stream an object of class AidaHitPID.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AidaHitPID::Class(),this);
   } else {
      R__b.WriteClassBuffer(AidaHitPID::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AidaHitPID(void *p) {
      return  p ? new(p) ::AidaHitPID : new ::AidaHitPID;
   }
   static void *newArray_AidaHitPID(Long_t nElements, void *p) {
      return p ? new(p) ::AidaHitPID[nElements] : new ::AidaHitPID[nElements];
   }
   // Wrapper around operator delete
   static void delete_AidaHitPID(void *p) {
      delete ((::AidaHitPID*)p);
   }
   static void deleteArray_AidaHitPID(void *p) {
      delete [] ((::AidaHitPID*)p);
   }
   static void destruct_AidaHitPID(void *p) {
      typedef ::AidaHitPID current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AidaHitPID

//______________________________________________________________________________
void EventCorrelProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventCorrelProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventCorrelProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventCorrelProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventCorrelProc(void *p) {
      return  p ? new(p) ::EventCorrelProc : new ::EventCorrelProc;
   }
   static void *newArray_EventCorrelProc(Long_t nElements, void *p) {
      return p ? new(p) ::EventCorrelProc[nElements] : new ::EventCorrelProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventCorrelProc(void *p) {
      delete ((::EventCorrelProc*)p);
   }
   static void deleteArray_EventCorrelProc(void *p) {
      delete [] ((::EventCorrelProc*)p);
   }
   static void destruct_EventCorrelProc(void *p) {
      typedef ::EventCorrelProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventCorrelProc

//______________________________________________________________________________
void EventAnlProc::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventAnlProc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventAnlProc::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventAnlProc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventAnlProc(void *p) {
      return  p ? new(p) ::EventAnlProc : new ::EventAnlProc;
   }
   static void *newArray_EventAnlProc(Long_t nElements, void *p) {
      return p ? new(p) ::EventAnlProc[nElements] : new ::EventAnlProc[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventAnlProc(void *p) {
      delete ((::EventAnlProc*)p);
   }
   static void deleteArray_EventAnlProc(void *p) {
      delete [] ((::EventAnlProc*)p);
   }
   static void destruct_EventAnlProc(void *p) {
      typedef ::EventAnlProc current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventAnlProc

//______________________________________________________________________________
void EventCorrelStore::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventCorrelStore.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventCorrelStore::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventCorrelStore::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventCorrelStore(void *p) {
      return  p ? new(p) ::EventCorrelStore : new ::EventCorrelStore;
   }
   static void *newArray_EventCorrelStore(Long_t nElements, void *p) {
      return p ? new(p) ::EventCorrelStore[nElements] : new ::EventCorrelStore[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventCorrelStore(void *p) {
      delete ((::EventCorrelStore*)p);
   }
   static void deleteArray_EventCorrelStore(void *p) {
      delete [] ((::EventCorrelStore*)p);
   }
   static void destruct_EventCorrelStore(void *p) {
      typedef ::EventCorrelStore current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventCorrelStore

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 214,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 214,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEarraylEunsignedsPlongcO4gRsPgR_Dictionary();
   static void vectorlEarraylEunsignedsPlongcO4gRsPgR_TClassManip(TClass*);
   static void *new_vectorlEarraylEunsignedsPlongcO4gRsPgR(void *p = 0);
   static void *newArray_vectorlEarraylEunsignedsPlongcO4gRsPgR(Long_t size, void *p);
   static void delete_vectorlEarraylEunsignedsPlongcO4gRsPgR(void *p);
   static void deleteArray_vectorlEarraylEunsignedsPlongcO4gRsPgR(void *p);
   static void destruct_vectorlEarraylEunsignedsPlongcO4gRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<array<unsigned long,4> >*)
   {
      vector<array<unsigned long,4> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<array<unsigned long,4> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<array<unsigned long,4> >", -2, "vector", 214,
                  typeid(vector<array<unsigned long,4> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEarraylEunsignedsPlongcO4gRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<array<unsigned long,4> >) );
      instance.SetNew(&new_vectorlEarraylEunsignedsPlongcO4gRsPgR);
      instance.SetNewArray(&newArray_vectorlEarraylEunsignedsPlongcO4gRsPgR);
      instance.SetDelete(&delete_vectorlEarraylEunsignedsPlongcO4gRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEarraylEunsignedsPlongcO4gRsPgR);
      instance.SetDestructor(&destruct_vectorlEarraylEunsignedsPlongcO4gRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<array<unsigned long,4> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<array<unsigned long,4> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEarraylEunsignedsPlongcO4gRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<array<unsigned long,4> >*)0x0)->GetClass();
      vectorlEarraylEunsignedsPlongcO4gRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEarraylEunsignedsPlongcO4gRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEarraylEunsignedsPlongcO4gRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<unsigned long,4> > : new vector<array<unsigned long,4> >;
   }
   static void *newArray_vectorlEarraylEunsignedsPlongcO4gRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<unsigned long,4> >[nElements] : new vector<array<unsigned long,4> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEarraylEunsignedsPlongcO4gRsPgR(void *p) {
      delete ((vector<array<unsigned long,4> >*)p);
   }
   static void deleteArray_vectorlEarraylEunsignedsPlongcO4gRsPgR(void *p) {
      delete [] ((vector<array<unsigned long,4> >*)p);
   }
   static void destruct_vectorlEarraylEunsignedsPlongcO4gRsPgR(void *p) {
      typedef vector<array<unsigned long,4> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<array<unsigned long,4> >

namespace ROOT {
   static TClass *vectorlEarraylEintcO4gRsPgR_Dictionary();
   static void vectorlEarraylEintcO4gRsPgR_TClassManip(TClass*);
   static void *new_vectorlEarraylEintcO4gRsPgR(void *p = 0);
   static void *newArray_vectorlEarraylEintcO4gRsPgR(Long_t size, void *p);
   static void delete_vectorlEarraylEintcO4gRsPgR(void *p);
   static void deleteArray_vectorlEarraylEintcO4gRsPgR(void *p);
   static void destruct_vectorlEarraylEintcO4gRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<array<int,4> >*)
   {
      vector<array<int,4> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<array<int,4> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<array<int,4> >", -2, "vector", 214,
                  typeid(vector<array<int,4> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEarraylEintcO4gRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<array<int,4> >) );
      instance.SetNew(&new_vectorlEarraylEintcO4gRsPgR);
      instance.SetNewArray(&newArray_vectorlEarraylEintcO4gRsPgR);
      instance.SetDelete(&delete_vectorlEarraylEintcO4gRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEarraylEintcO4gRsPgR);
      instance.SetDestructor(&destruct_vectorlEarraylEintcO4gRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<array<int,4> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<array<int,4> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEarraylEintcO4gRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<array<int,4> >*)0x0)->GetClass();
      vectorlEarraylEintcO4gRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEarraylEintcO4gRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEarraylEintcO4gRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<int,4> > : new vector<array<int,4> >;
   }
   static void *newArray_vectorlEarraylEintcO4gRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<int,4> >[nElements] : new vector<array<int,4> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEarraylEintcO4gRsPgR(void *p) {
      delete ((vector<array<int,4> >*)p);
   }
   static void deleteArray_vectorlEarraylEintcO4gRsPgR(void *p) {
      delete [] ((vector<array<int,4> >*)p);
   }
   static void destruct_vectorlEarraylEintcO4gRsPgR(void *p) {
      typedef vector<array<int,4> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<array<int,4> >

namespace ROOT {
   static TClass *vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR_Dictionary();
   static void vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR_TClassManip(TClass*);
   static void *new_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(void *p = 0);
   static void *newArray_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(Long_t size, void *p);
   static void delete_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(void *p);
   static void deleteArray_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(void *p);
   static void destruct_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<array<array<TH1*,2>,64> >*)
   {
      vector<array<array<TH1*,2>,64> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<array<array<TH1*,2>,64> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<array<array<TH1*,2>,64> >", -2, "vector", 214,
                  typeid(vector<array<array<TH1*,2>,64> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<array<array<TH1*,2>,64> >) );
      instance.SetNew(&new_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR);
      instance.SetNewArray(&newArray_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR);
      instance.SetDelete(&delete_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR);
      instance.SetDestructor(&destruct_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<array<array<TH1*,2>,64> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<array<array<TH1*,2>,64> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<array<array<TH1*,2>,64> >*)0x0)->GetClass();
      vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<array<TH1*,2>,64> > : new vector<array<array<TH1*,2>,64> >;
   }
   static void *newArray_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<array<TH1*,2>,64> >[nElements] : new vector<array<array<TH1*,2>,64> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(void *p) {
      delete ((vector<array<array<TH1*,2>,64> >*)p);
   }
   static void deleteArray_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(void *p) {
      delete [] ((vector<array<array<TH1*,2>,64> >*)p);
   }
   static void destruct_vectorlEarraylEarraylETH1mUcO2gRcO64gRsPgR(void *p) {
      typedef vector<array<array<TH1*,2>,64> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<array<array<TH1*,2>,64> >

namespace ROOT {
   static TClass *vectorlETH2mUgR_Dictionary();
   static void vectorlETH2mUgR_TClassManip(TClass*);
   static void *new_vectorlETH2mUgR(void *p = 0);
   static void *newArray_vectorlETH2mUgR(Long_t size, void *p);
   static void delete_vectorlETH2mUgR(void *p);
   static void deleteArray_vectorlETH2mUgR(void *p);
   static void destruct_vectorlETH2mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TH2*>*)
   {
      vector<TH2*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TH2*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TH2*>", -2, "vector", 214,
                  typeid(vector<TH2*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETH2mUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TH2*>) );
      instance.SetNew(&new_vectorlETH2mUgR);
      instance.SetNewArray(&newArray_vectorlETH2mUgR);
      instance.SetDelete(&delete_vectorlETH2mUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETH2mUgR);
      instance.SetDestructor(&destruct_vectorlETH2mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TH2*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TH2*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETH2mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TH2*>*)0x0)->GetClass();
      vectorlETH2mUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETH2mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETH2mUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TH2*> : new vector<TH2*>;
   }
   static void *newArray_vectorlETH2mUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TH2*>[nElements] : new vector<TH2*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETH2mUgR(void *p) {
      delete ((vector<TH2*>*)p);
   }
   static void deleteArray_vectorlETH2mUgR(void *p) {
      delete [] ((vector<TH2*>*)p);
   }
   static void destruct_vectorlETH2mUgR(void *p) {
      typedef vector<TH2*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TH2*>

namespace ROOT {
   static TClass *vectorlETH1mUgR_Dictionary();
   static void vectorlETH1mUgR_TClassManip(TClass*);
   static void *new_vectorlETH1mUgR(void *p = 0);
   static void *newArray_vectorlETH1mUgR(Long_t size, void *p);
   static void delete_vectorlETH1mUgR(void *p);
   static void deleteArray_vectorlETH1mUgR(void *p);
   static void destruct_vectorlETH1mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TH1*>*)
   {
      vector<TH1*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TH1*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TH1*>", -2, "vector", 214,
                  typeid(vector<TH1*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETH1mUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TH1*>) );
      instance.SetNew(&new_vectorlETH1mUgR);
      instance.SetNewArray(&newArray_vectorlETH1mUgR);
      instance.SetDelete(&delete_vectorlETH1mUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETH1mUgR);
      instance.SetDestructor(&destruct_vectorlETH1mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TH1*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TH1*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETH1mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TH1*>*)0x0)->GetClass();
      vectorlETH1mUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETH1mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETH1mUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TH1*> : new vector<TH1*>;
   }
   static void *newArray_vectorlETH1mUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TH1*>[nElements] : new vector<TH1*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETH1mUgR(void *p) {
      delete ((vector<TH1*>*)p);
   }
   static void deleteArray_vectorlETH1mUgR(void *p) {
      delete [] ((vector<TH1*>*)p);
   }
   static void destruct_vectorlETH1mUgR(void *p) {
      typedef vector<TH1*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TH1*>

namespace ROOT {
   static TClass *vectorlELong64_tgR_Dictionary();
   static void vectorlELong64_tgR_TClassManip(TClass*);
   static void *new_vectorlELong64_tgR(void *p = 0);
   static void *newArray_vectorlELong64_tgR(Long_t size, void *p);
   static void delete_vectorlELong64_tgR(void *p);
   static void deleteArray_vectorlELong64_tgR(void *p);
   static void destruct_vectorlELong64_tgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Long64_t>*)
   {
      vector<Long64_t> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Long64_t>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Long64_t>", -2, "vector", 214,
                  typeid(vector<Long64_t>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlELong64_tgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Long64_t>) );
      instance.SetNew(&new_vectorlELong64_tgR);
      instance.SetNewArray(&newArray_vectorlELong64_tgR);
      instance.SetDelete(&delete_vectorlELong64_tgR);
      instance.SetDeleteArray(&deleteArray_vectorlELong64_tgR);
      instance.SetDestructor(&destruct_vectorlELong64_tgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Long64_t> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<Long64_t>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELong64_tgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Long64_t>*)0x0)->GetClass();
      vectorlELong64_tgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELong64_tgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELong64_tgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Long64_t> : new vector<Long64_t>;
   }
   static void *newArray_vectorlELong64_tgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Long64_t>[nElements] : new vector<Long64_t>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELong64_tgR(void *p) {
      delete ((vector<Long64_t>*)p);
   }
   static void deleteArray_vectorlELong64_tgR(void *p) {
      delete [] ((vector<Long64_t>*)p);
   }
   static void destruct_vectorlELong64_tgR(void *p) {
      typedef vector<Long64_t> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Long64_t>

namespace ROOT {
   static TClass *vectorlEAidaUnpackDatagR_Dictionary();
   static void vectorlEAidaUnpackDatagR_TClassManip(TClass*);
   static void *new_vectorlEAidaUnpackDatagR(void *p = 0);
   static void *newArray_vectorlEAidaUnpackDatagR(Long_t size, void *p);
   static void delete_vectorlEAidaUnpackDatagR(void *p);
   static void deleteArray_vectorlEAidaUnpackDatagR(void *p);
   static void destruct_vectorlEAidaUnpackDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<AidaUnpackData>*)
   {
      vector<AidaUnpackData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<AidaUnpackData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<AidaUnpackData>", -2, "vector", 214,
                  typeid(vector<AidaUnpackData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAidaUnpackDatagR_Dictionary, isa_proxy, 0,
                  sizeof(vector<AidaUnpackData>) );
      instance.SetNew(&new_vectorlEAidaUnpackDatagR);
      instance.SetNewArray(&newArray_vectorlEAidaUnpackDatagR);
      instance.SetDelete(&delete_vectorlEAidaUnpackDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlEAidaUnpackDatagR);
      instance.SetDestructor(&destruct_vectorlEAidaUnpackDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<AidaUnpackData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<AidaUnpackData>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAidaUnpackDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<AidaUnpackData>*)0x0)->GetClass();
      vectorlEAidaUnpackDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAidaUnpackDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAidaUnpackDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaUnpackData> : new vector<AidaUnpackData>;
   }
   static void *newArray_vectorlEAidaUnpackDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaUnpackData>[nElements] : new vector<AidaUnpackData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAidaUnpackDatagR(void *p) {
      delete ((vector<AidaUnpackData>*)p);
   }
   static void deleteArray_vectorlEAidaUnpackDatagR(void *p) {
      delete [] ((vector<AidaUnpackData>*)p);
   }
   static void destruct_vectorlEAidaUnpackDatagR(void *p) {
      typedef vector<AidaUnpackData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<AidaUnpackData>

namespace ROOT {
   static TClass *vectorlEAidaScalergR_Dictionary();
   static void vectorlEAidaScalergR_TClassManip(TClass*);
   static void *new_vectorlEAidaScalergR(void *p = 0);
   static void *newArray_vectorlEAidaScalergR(Long_t size, void *p);
   static void delete_vectorlEAidaScalergR(void *p);
   static void deleteArray_vectorlEAidaScalergR(void *p);
   static void destruct_vectorlEAidaScalergR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<AidaScaler>*)
   {
      vector<AidaScaler> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<AidaScaler>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<AidaScaler>", -2, "vector", 214,
                  typeid(vector<AidaScaler>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAidaScalergR_Dictionary, isa_proxy, 4,
                  sizeof(vector<AidaScaler>) );
      instance.SetNew(&new_vectorlEAidaScalergR);
      instance.SetNewArray(&newArray_vectorlEAidaScalergR);
      instance.SetDelete(&delete_vectorlEAidaScalergR);
      instance.SetDeleteArray(&deleteArray_vectorlEAidaScalergR);
      instance.SetDestructor(&destruct_vectorlEAidaScalergR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<AidaScaler> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<AidaScaler>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAidaScalergR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<AidaScaler>*)0x0)->GetClass();
      vectorlEAidaScalergR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAidaScalergR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAidaScalergR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaScaler> : new vector<AidaScaler>;
   }
   static void *newArray_vectorlEAidaScalergR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaScaler>[nElements] : new vector<AidaScaler>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAidaScalergR(void *p) {
      delete ((vector<AidaScaler>*)p);
   }
   static void deleteArray_vectorlEAidaScalergR(void *p) {
      delete [] ((vector<AidaScaler>*)p);
   }
   static void destruct_vectorlEAidaScalergR(void *p) {
      typedef vector<AidaScaler> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<AidaScaler>

namespace ROOT {
   static TClass *vectorlEAidaHitgR_Dictionary();
   static void vectorlEAidaHitgR_TClassManip(TClass*);
   static void *new_vectorlEAidaHitgR(void *p = 0);
   static void *newArray_vectorlEAidaHitgR(Long_t size, void *p);
   static void delete_vectorlEAidaHitgR(void *p);
   static void deleteArray_vectorlEAidaHitgR(void *p);
   static void destruct_vectorlEAidaHitgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<AidaHit>*)
   {
      vector<AidaHit> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<AidaHit>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<AidaHit>", -2, "vector", 214,
                  typeid(vector<AidaHit>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAidaHitgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<AidaHit>) );
      instance.SetNew(&new_vectorlEAidaHitgR);
      instance.SetNewArray(&newArray_vectorlEAidaHitgR);
      instance.SetDelete(&delete_vectorlEAidaHitgR);
      instance.SetDeleteArray(&deleteArray_vectorlEAidaHitgR);
      instance.SetDestructor(&destruct_vectorlEAidaHitgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<AidaHit> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<AidaHit>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAidaHitgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<AidaHit>*)0x0)->GetClass();
      vectorlEAidaHitgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAidaHitgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAidaHitgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaHit> : new vector<AidaHit>;
   }
   static void *newArray_vectorlEAidaHitgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaHit>[nElements] : new vector<AidaHit>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAidaHitgR(void *p) {
      delete ((vector<AidaHit>*)p);
   }
   static void deleteArray_vectorlEAidaHitgR(void *p) {
      delete [] ((vector<AidaHit>*)p);
   }
   static void destruct_vectorlEAidaHitgR(void *p) {
      typedef vector<AidaHit> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<AidaHit>

namespace ROOT {
   static TClass *vectorlEAidaEventgR_Dictionary();
   static void vectorlEAidaEventgR_TClassManip(TClass*);
   static void *new_vectorlEAidaEventgR(void *p = 0);
   static void *newArray_vectorlEAidaEventgR(Long_t size, void *p);
   static void delete_vectorlEAidaEventgR(void *p);
   static void deleteArray_vectorlEAidaEventgR(void *p);
   static void destruct_vectorlEAidaEventgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<AidaEvent>*)
   {
      vector<AidaEvent> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<AidaEvent>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<AidaEvent>", -2, "vector", 214,
                  typeid(vector<AidaEvent>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAidaEventgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<AidaEvent>) );
      instance.SetNew(&new_vectorlEAidaEventgR);
      instance.SetNewArray(&newArray_vectorlEAidaEventgR);
      instance.SetDelete(&delete_vectorlEAidaEventgR);
      instance.SetDeleteArray(&deleteArray_vectorlEAidaEventgR);
      instance.SetDestructor(&destruct_vectorlEAidaEventgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<AidaEvent> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<AidaEvent>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAidaEventgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<AidaEvent>*)0x0)->GetClass();
      vectorlEAidaEventgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAidaEventgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAidaEventgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaEvent> : new vector<AidaEvent>;
   }
   static void *newArray_vectorlEAidaEventgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaEvent>[nElements] : new vector<AidaEvent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAidaEventgR(void *p) {
      delete ((vector<AidaEvent>*)p);
   }
   static void deleteArray_vectorlEAidaEventgR(void *p) {
      delete [] ((vector<AidaEvent>*)p);
   }
   static void destruct_vectorlEAidaEventgR(void *p) {
      typedef vector<AidaEvent> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<AidaEvent>

namespace ROOT {
   static TClass *vectorlEAidaAnlDatagR_Dictionary();
   static void vectorlEAidaAnlDatagR_TClassManip(TClass*);
   static void *new_vectorlEAidaAnlDatagR(void *p = 0);
   static void *newArray_vectorlEAidaAnlDatagR(Long_t size, void *p);
   static void delete_vectorlEAidaAnlDatagR(void *p);
   static void deleteArray_vectorlEAidaAnlDatagR(void *p);
   static void destruct_vectorlEAidaAnlDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<AidaAnlData>*)
   {
      vector<AidaAnlData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<AidaAnlData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<AidaAnlData>", -2, "vector", 214,
                  typeid(vector<AidaAnlData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAidaAnlDatagR_Dictionary, isa_proxy, 4,
                  sizeof(vector<AidaAnlData>) );
      instance.SetNew(&new_vectorlEAidaAnlDatagR);
      instance.SetNewArray(&newArray_vectorlEAidaAnlDatagR);
      instance.SetDelete(&delete_vectorlEAidaAnlDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlEAidaAnlDatagR);
      instance.SetDestructor(&destruct_vectorlEAidaAnlDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<AidaAnlData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<AidaAnlData>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAidaAnlDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<AidaAnlData>*)0x0)->GetClass();
      vectorlEAidaAnlDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAidaAnlDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAidaAnlDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaAnlData> : new vector<AidaAnlData>;
   }
   static void *newArray_vectorlEAidaAnlDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AidaAnlData>[nElements] : new vector<AidaAnlData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAidaAnlDatagR(void *p) {
      delete ((vector<AidaAnlData>*)p);
   }
   static void deleteArray_vectorlEAidaAnlDatagR(void *p) {
      delete [] ((vector<AidaAnlData>*)p);
   }
   static void destruct_vectorlEAidaAnlDatagR(void *p) {
      typedef vector<AidaAnlData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<AidaAnlData>

namespace ROOT {
   static TClass *multimaplElongcOAidaHitPIDgR_Dictionary();
   static void multimaplElongcOAidaHitPIDgR_TClassManip(TClass*);
   static void *new_multimaplElongcOAidaHitPIDgR(void *p = 0);
   static void *newArray_multimaplElongcOAidaHitPIDgR(Long_t size, void *p);
   static void delete_multimaplElongcOAidaHitPIDgR(void *p);
   static void deleteArray_multimaplElongcOAidaHitPIDgR(void *p);
   static void destruct_multimaplElongcOAidaHitPIDgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const multimap<long,AidaHitPID>*)
   {
      multimap<long,AidaHitPID> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(multimap<long,AidaHitPID>));
      static ::ROOT::TGenericClassInfo 
         instance("multimap<long,AidaHitPID>", -2, "map", 95,
                  typeid(multimap<long,AidaHitPID>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &multimaplElongcOAidaHitPIDgR_Dictionary, isa_proxy, 0,
                  sizeof(multimap<long,AidaHitPID>) );
      instance.SetNew(&new_multimaplElongcOAidaHitPIDgR);
      instance.SetNewArray(&newArray_multimaplElongcOAidaHitPIDgR);
      instance.SetDelete(&delete_multimaplElongcOAidaHitPIDgR);
      instance.SetDeleteArray(&deleteArray_multimaplElongcOAidaHitPIDgR);
      instance.SetDestructor(&destruct_multimaplElongcOAidaHitPIDgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< multimap<long,AidaHitPID> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const multimap<long,AidaHitPID>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *multimaplElongcOAidaHitPIDgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const multimap<long,AidaHitPID>*)0x0)->GetClass();
      multimaplElongcOAidaHitPIDgR_TClassManip(theClass);
   return theClass;
   }

   static void multimaplElongcOAidaHitPIDgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_multimaplElongcOAidaHitPIDgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) multimap<long,AidaHitPID> : new multimap<long,AidaHitPID>;
   }
   static void *newArray_multimaplElongcOAidaHitPIDgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) multimap<long,AidaHitPID>[nElements] : new multimap<long,AidaHitPID>[nElements];
   }
   // Wrapper around operator delete
   static void delete_multimaplElongcOAidaHitPIDgR(void *p) {
      delete ((multimap<long,AidaHitPID>*)p);
   }
   static void deleteArray_multimaplElongcOAidaHitPIDgR(void *p) {
      delete [] ((multimap<long,AidaHitPID>*)p);
   }
   static void destruct_multimaplElongcOAidaHitPIDgR(void *p) {
      typedef multimap<long,AidaHitPID> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class multimap<long,AidaHitPID>

namespace ROOT {
   static TClass *maplEintcOintgR_Dictionary();
   static void maplEintcOintgR_TClassManip(TClass*);
   static void *new_maplEintcOintgR(void *p = 0);
   static void *newArray_maplEintcOintgR(Long_t size, void *p);
   static void delete_maplEintcOintgR(void *p);
   static void deleteArray_maplEintcOintgR(void *p);
   static void destruct_maplEintcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,int>*)
   {
      map<int,int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,int>", -2, "map", 96,
                  typeid(map<int,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,int>) );
      instance.SetNew(&new_maplEintcOintgR);
      instance.SetNewArray(&newArray_maplEintcOintgR);
      instance.SetDelete(&delete_maplEintcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOintgR);
      instance.SetDestructor(&destruct_maplEintcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,int>*)0x0)->GetClass();
      maplEintcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int> : new map<int,int>;
   }
   static void *newArray_maplEintcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int>[nElements] : new map<int,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOintgR(void *p) {
      delete ((map<int,int>*)p);
   }
   static void deleteArray_maplEintcOintgR(void *p) {
      delete [] ((map<int,int>*)p);
   }
   static void destruct_maplEintcOintgR(void *p) {
      typedef map<int,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,int>

namespace ROOT {
   static TClass *maplEintcOdequelEintgRsPgR_Dictionary();
   static void maplEintcOdequelEintgRsPgR_TClassManip(TClass*);
   static void *new_maplEintcOdequelEintgRsPgR(void *p = 0);
   static void *newArray_maplEintcOdequelEintgRsPgR(Long_t size, void *p);
   static void delete_maplEintcOdequelEintgRsPgR(void *p);
   static void deleteArray_maplEintcOdequelEintgRsPgR(void *p);
   static void destruct_maplEintcOdequelEintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,deque<int> >*)
   {
      map<int,deque<int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,deque<int> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,deque<int> >", -2, "map", 96,
                  typeid(map<int,deque<int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOdequelEintgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,deque<int> >) );
      instance.SetNew(&new_maplEintcOdequelEintgRsPgR);
      instance.SetNewArray(&newArray_maplEintcOdequelEintgRsPgR);
      instance.SetDelete(&delete_maplEintcOdequelEintgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOdequelEintgRsPgR);
      instance.SetDestructor(&destruct_maplEintcOdequelEintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,deque<int> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,deque<int> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOdequelEintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,deque<int> >*)0x0)->GetClass();
      maplEintcOdequelEintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOdequelEintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOdequelEintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,deque<int> > : new map<int,deque<int> >;
   }
   static void *newArray_maplEintcOdequelEintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,deque<int> >[nElements] : new map<int,deque<int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOdequelEintgRsPgR(void *p) {
      delete ((map<int,deque<int> >*)p);
   }
   static void deleteArray_maplEintcOdequelEintgRsPgR(void *p) {
      delete [] ((map<int,deque<int> >*)p);
   }
   static void destruct_maplEintcOdequelEintgRsPgR(void *p) {
      typedef map<int,deque<int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,deque<int> >

namespace ROOT {
   static TClass *maplEintcOTH1mUgR_Dictionary();
   static void maplEintcOTH1mUgR_TClassManip(TClass*);
   static void *new_maplEintcOTH1mUgR(void *p = 0);
   static void *newArray_maplEintcOTH1mUgR(Long_t size, void *p);
   static void delete_maplEintcOTH1mUgR(void *p);
   static void deleteArray_maplEintcOTH1mUgR(void *p);
   static void destruct_maplEintcOTH1mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,TH1*>*)
   {
      map<int,TH1*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,TH1*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,TH1*>", -2, "map", 96,
                  typeid(map<int,TH1*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOTH1mUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,TH1*>) );
      instance.SetNew(&new_maplEintcOTH1mUgR);
      instance.SetNewArray(&newArray_maplEintcOTH1mUgR);
      instance.SetDelete(&delete_maplEintcOTH1mUgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOTH1mUgR);
      instance.SetDestructor(&destruct_maplEintcOTH1mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,TH1*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,TH1*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOTH1mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,TH1*>*)0x0)->GetClass();
      maplEintcOTH1mUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOTH1mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOTH1mUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,TH1*> : new map<int,TH1*>;
   }
   static void *newArray_maplEintcOTH1mUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,TH1*>[nElements] : new map<int,TH1*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOTH1mUgR(void *p) {
      delete ((map<int,TH1*>*)p);
   }
   static void deleteArray_maplEintcOTH1mUgR(void *p) {
      delete [] ((map<int,TH1*>*)p);
   }
   static void destruct_maplEintcOTH1mUgR(void *p) {
      typedef map<int,TH1*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,TH1*>

namespace ROOT {
   static TClass *dequelEintgR_Dictionary();
   static void dequelEintgR_TClassManip(TClass*);
   static void *new_dequelEintgR(void *p = 0);
   static void *newArray_dequelEintgR(Long_t size, void *p);
   static void delete_dequelEintgR(void *p);
   static void deleteArray_dequelEintgR(void *p);
   static void destruct_dequelEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const deque<int>*)
   {
      deque<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(deque<int>));
      static ::ROOT::TGenericClassInfo 
         instance("deque<int>", -2, "deque", 735,
                  typeid(deque<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &dequelEintgR_Dictionary, isa_proxy, 0,
                  sizeof(deque<int>) );
      instance.SetNew(&new_dequelEintgR);
      instance.SetNewArray(&newArray_dequelEintgR);
      instance.SetDelete(&delete_dequelEintgR);
      instance.SetDeleteArray(&deleteArray_dequelEintgR);
      instance.SetDestructor(&destruct_dequelEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< deque<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const deque<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *dequelEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const deque<int>*)0x0)->GetClass();
      dequelEintgR_TClassManip(theClass);
   return theClass;
   }

   static void dequelEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_dequelEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) deque<int> : new deque<int>;
   }
   static void *newArray_dequelEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) deque<int>[nElements] : new deque<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_dequelEintgR(void *p) {
      delete ((deque<int>*)p);
   }
   static void deleteArray_dequelEintgR(void *p) {
      delete [] ((deque<int>*)p);
   }
   static void destruct_dequelEintgR(void *p) {
      typedef deque<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class deque<int>

namespace {
  void TriggerDictionaryInitialization_libGo4UserAnalysis_Impl() {
    static const char* headers[] = {
"./AIDA_Headers.h",
"./DESPECAnalysis.h",
"./FRS_Detector_System.h",
"./EventAnlStore.h",
"./FATIMA_Time_Calibration.h",
"./AIDA_Decay_Event_Store.h",
"./FINGER_Calibrator.h",
"./Timestamp.h",
"./QDC_751.h",
"./TDC_1290.h",
"./Germanium_Energy_Calibration.h",
"./QDC.h",
"./CorrelParameter.h",
"./EventUnpackFact.h",
"./EventCorrelProc.h",
"./White_Rabbit.h",
"./FATIMA_TAMEX_Detector_System.h",
"./TAidaConfiguration.h",
"./Germanium_Time_Calibration.h",
"./Raw_Event.h",
"./AIDA_Data_Types.h",
"./FEBEX.h",
"./TAMEX.h",
"./AIDA_Processor.h",
"./FATIMA_Energy_Calibration.h",
"./TFRSParameter.h",
"./WR_Structure.h",
"./Germanium_Detector_System.h",
"./FATIMA_Detector_System.h",
"./EventAnlProc.h",
"./EventUnpackStore.h",
"./AIDA_Detector_System.h",
"./EventUnpackProc.h",
"./AIDA_Event.h",
"./PLASTIC_TAMEX_Detector_System.h",
"./EventCorrelStore.h",
"./FINGER_Detector_System.h",
"./FATIMA_TAMEX_Calibrator.h",
"./PLASTIC_TAMEX_Calibrator.h",
"./CalibParameter.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/csee.gsi.de/go4/600-00/include",
"/cvmfs/csee.gsi.de/go4/600-00",
"/cvmfs/csee.gsi.de/hdf5/1.10.5//include",
"/cvmfs/csee.gsi.de/root/618-04/include",
"/u/amistry/DESPEC_S452/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libGo4UserAnalysis dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$AIDA_Decay_Event_Store.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  AidaScaler;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
struct __attribute__((annotate("$clingAutoload$./EventAnlStore.h")))  AidaAnlData;
class __attribute__((annotate("$clingAutoload$AIDA_Decay_Event_Store.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  AidaEvent;
class __attribute__((annotate("$clingAutoload$AIDA_Decay_Event_Store.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  AidaHit;
class __attribute__((annotate("$clingAutoload$AIDA_Event.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  AIDA_Event;
struct __attribute__((annotate("$clingAutoload$EventUnpackStore.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  AidaUnpackData;
class __attribute__((annotate("$clingAutoload$EventUnpackStore.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  EventUnpackStore;
class __attribute__((annotate("$clingAutoload$CalibParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  CalibParameter;
class __attribute__((annotate("$clingAutoload$CorrelParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  CorrelParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  TFRSParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  Map1;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  TMWParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  TTPCParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  TMUSICParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  TSCIParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  TIDParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  TSIParameter;
class __attribute__((annotate("$clingAutoload$TFRSParameter.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  TMRTOFMSParameter;
class __attribute__((annotate("$clingAutoload$FRS_Detector_System.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  FRS_Detector_System;
class __attribute__((annotate("$clingAutoload$EventUnpackProc.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  EventUnpackProc;
class __attribute__((annotate("$clingAutoload$EventUnpackFact.h")))  __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  EventUnpackFact;
class __attribute__((annotate("$clingAutoload$./DESPECAnalysis.h")))  DESPECAnalysis;
class __attribute__((annotate("$clingAutoload$./EventAnlStore.h")))  EventAnlStore;
class __attribute__((annotate("$clingAutoload$./EventCorrelProc.h")))  AidaHitPID;
class __attribute__((annotate("$clingAutoload$./EventCorrelProc.h")))  EventCorrelProc;
class __attribute__((annotate("$clingAutoload$./EventAnlProc.h")))  EventAnlProc;
class __attribute__((annotate("$clingAutoload$./EventCorrelStore.h")))  EventCorrelStore;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libGo4UserAnalysis dictionary payload"

#ifndef Linux
  #define Linux 1
#endif
#ifndef __GO4HDF5__
  #define __GO4HDF5__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "./AIDA_Headers.h"
#include "./DESPECAnalysis.h"
#include "./FRS_Detector_System.h"
#include "./EventAnlStore.h"
#include "./FATIMA_Time_Calibration.h"
#include "./AIDA_Decay_Event_Store.h"
#include "./FINGER_Calibrator.h"
#include "./Timestamp.h"
#include "./QDC_751.h"
#include "./TDC_1290.h"
#include "./Germanium_Energy_Calibration.h"
#include "./QDC.h"
#include "./CorrelParameter.h"
#include "./EventUnpackFact.h"
#include "./EventCorrelProc.h"
#include "./White_Rabbit.h"
#include "./FATIMA_TAMEX_Detector_System.h"
#include "./TAidaConfiguration.h"
#include "./Germanium_Time_Calibration.h"
#include "./Raw_Event.h"
#include "./AIDA_Data_Types.h"
#include "./FEBEX.h"
#include "./TAMEX.h"
#include "./AIDA_Processor.h"
#include "./FATIMA_Energy_Calibration.h"
#include "./TFRSParameter.h"
#include "./WR_Structure.h"
#include "./Germanium_Detector_System.h"
#include "./FATIMA_Detector_System.h"
#include "./EventAnlProc.h"
#include "./EventUnpackStore.h"
#include "./AIDA_Detector_System.h"
#include "./EventUnpackProc.h"
#include "./AIDA_Event.h"
#include "./PLASTIC_TAMEX_Detector_System.h"
#include "./EventCorrelStore.h"
#include "./FINGER_Detector_System.h"
#include "./FATIMA_TAMEX_Calibrator.h"
#include "./PLASTIC_TAMEX_Calibrator.h"
#include "./CalibParameter.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"AIDA_Event", payloadCode, "@",
"AidaAnlData", payloadCode, "@",
"AidaEvent", payloadCode, "@",
"AidaHit", payloadCode, "@",
"AidaHitPID", payloadCode, "@",
"AidaScaler", payloadCode, "@",
"AidaUnpackData", payloadCode, "@",
"CalibParameter", payloadCode, "@",
"CorrelParameter", payloadCode, "@",
"DESPECAnalysis", payloadCode, "@",
"EventAnlProc", payloadCode, "@",
"EventAnlStore", payloadCode, "@",
"EventCorrelProc", payloadCode, "@",
"EventCorrelStore", payloadCode, "@",
"EventUnpackFact", payloadCode, "@",
"EventUnpackProc", payloadCode, "@",
"EventUnpackStore", payloadCode, "@",
"FRS_Detector_System", payloadCode, "@",
"Map1", payloadCode, "@",
"TFRSParameter", payloadCode, "@",
"TIDParameter", payloadCode, "@",
"TMRTOFMSParameter", payloadCode, "@",
"TMUSICParameter", payloadCode, "@",
"TMWParameter", payloadCode, "@",
"TSCIParameter", payloadCode, "@",
"TSIParameter", payloadCode, "@",
"TTPCParameter", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libGo4UserAnalysis",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libGo4UserAnalysis_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libGo4UserAnalysis_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libGo4UserAnalysis() {
  TriggerDictionaryInitialization_libGo4UserAnalysis_Impl();
}
