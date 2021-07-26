DESPEC_NAME        = DESPECOnline
MODULE_NAME            = $(DESPEC_NAME)

## normally should be like this for every module, but can be specific

ifdef GO4PACKAGE
DESPEC_DIR         = $(GO4SYS)/$(DESPEC_NAME)
else
DESPEC_DIR         = .
endif

DESPEC_LINKDEF     = $(DESPEC_DIR)/Go4UserAnalysisLinkDef.$(HedSuf)
DESPEC_LIBNAME     = libGo4UserAnalysis
DESPEC_EXENAME     = MainUserAnalysis
DESPEC_ONLYMAP     = $(DESPEC_DIR)/.localmap
DESPEC_MAP         = $(DESPEC_DIR)/$(ROOTMAPNAME)

DESPEC_NOTLIBF     = 

## must be similar for every module

DESPEC_EXEO        = $(DESPEC_DIR)/$(DESPEC_EXENAME).$(ObjSuf)
#DESPEC_EXEH        = $(DESPEC_DIR)/$(DESPEC_EXENAME).$(HedSuf)
DESPEC_EXES        = $(DESPEC_DIR)/$(DESPEC_EXENAME).$(SrcSuf)
DESPEC_EXE         = $(DESPEC_DIR)/$(DESPEC_EXENAME)$(ExeSuf)

DESPEC_DICT        = $(DESPEC_DIR)/$(DICT_PREFIX)$(DESPEC_NAME)
DESPEC_DH          = $(DESPEC_DICT).$(HedSuf)
DESPEC_DS          = $(DESPEC_DICT).$(SrcSuf)
DESPEC_DO          = $(DESPEC_DICT).$(ObjSuf)

DESPEC_H           = $(filter-out $(DESPEC_EXEH) $(DESPEC_NOTLIBF) $(DESPEC_DH) $(DESPEC_LINKDEF), $(wildcard $(DESPEC_DIR)/*.$(HedSuf)))
DESPEC_S           = $(filter-out $(DESPEC_EXES) $(DESPEC_NOTLIBF) $(DESPEC_DS), $(wildcard $(DESPEC_DIR)/*.$(SrcSuf)))
DESPEC_O           = $(DESPEC_S:.$(SrcSuf)=.$(ObjSuf))

DESPEC_DEP         =  $(DESPEC_O:.$(ObjSuf)=.$(DepSuf))
DESPEC_DDEP        =  $(DESPEC_DO:.$(ObjSuf)=.$(DepSuf))
DESPEC_EDEP        =  $(DESPEC_EXEO:.$(ObjSuf)=.$(DepSuf))

DESPEC_SLIB        =  $(DESPEC_DIR)/$(DESPEC_LIBNAME).$(DllSuf)
DESPEC_LIB         =  $(DESPEC_DIR)/$(DESPEC_LIBNAME).$(DllSuf).$(VERSSUF)

# used in the main Makefile

EXAMPDEPENDENCS    += $(DESPEC_DEP) $(DESPEC_DDEP) $(DESPEC_EDEP)

ifdef DOPACKAGE
DISTRFILES         += $(DESPEC_S) $(DESPEC_H) $(DESPEC_LINKDEF) $(DESPEC_EXEH) $(DESPEC_EXES)
DISTRFILES         += $(DESPEC_DIR)/Readme.txt
DISTRFILES         += $(DESPEC_DIR)/AnalysisStart.sh $(DESPEC_DIR)/rename.sh 
DISTRFILES         += $(DESPEC_DIR)/*.C 
endif

##### local rules #####

$(DESPEC_EXE):      $(BUILDGO4LIBS) $(DESPEC_EXEO) $(DESPEC_LIB)
	$(LD) $(LDFLAGS) $(DESPEC_EXEO) $(LIBS_FULLSET) $(DESPEC_LIB) $(OutPutOpt) $(DESPEC_EXE)
	@echo "$@  done"

$(DESPEC_LIB):   $(DESPEC_O) $(DESPEC_DO)
	@$(MakeLib) $(DESPEC_LIBNAME) "$(DESPEC_O) $(DESPEC_DO)" $(DESPEC_DIR)

$(DESPEC_DS): $(DESPEC_H)  $(DESPEC_LINKDEF)
	@$(ROOTCINTGO4) $(DESPEC_H) $(DESPEC_LINKDEF)

$(DESPEC_ONLYMAP): $(DESPEC_LINKDEF) $(DESPEC_LIB)
	@rm -f $(DESPEC_ONLYMAP)
	@$(MakeMap) $(DESPEC_ONLYMAP) $(DESPEC_SLIB) $(DESPEC_LINKDEF) "$(ANAL_LIB_DEP)"

all-$(DESPEC_NAME):     $(DESPEC_LIB) $(DESPEC_EXE) map-$(DESPEC_NAME)

clean-obj-$(DESPEC_NAME):
	@rm -f $(DESPEC_O) $(DESPEC_DO)
	@$(CleanLib) $(DESPEC_LIBNAME) $(DESPEC_DIR)
	@rm -f $(DESPEC_EXEO) $(DESPEC_EXE)

clean-$(DESPEC_NAME): clean-obj-$(DESPEC_NAME)
	@rm -f $(DESPEC_DEP) $(DESPEC_DDEP) $(DESPEC_DS) $(DESPEC_DH)
	@rm -f $(DESPEC_EDEP)
	@rm -f $(DESPEC_ONLYMAP) $(DESPEC_MAP)

ifdef DOMAP
map-$(DESPEC_NAME): $(GO4MAP) $(DESPEC_ONLYMAP)
	@rm -f $(DESPEC_MAP)
	@cat $(GO4MAP) $(DESPEC_ONLYMAP) > $(DESPEC_MAP)
else
map-$(DESPEC_NAME):

endif
