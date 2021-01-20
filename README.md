<<<<<<< HEAD
# DEspec-Analysis-Framework
C++ analysis framwork for the DESPEC campaign @ GSI/FAIR
# DESPEC On/Nearline code for S452
=======================================================================

All used detector systems:
  - FRS
  - AIDA
  - beta-Plastic
  - FATIMA
  - GALILEO

=======================================================================


Raw Data unpacked in EventUnpackProc (links to individual detector system classes and passes through Raw_Event)
Individual systems filled in EventAnlProc
Correlations between subsystems in EventCorrelProc
Stores contain the tree branches

The histogram list can be found in the attached .pdf document, a branches list will follow shortly.

Gain matching files can be found in the subsequent detector folders in Configuration_Files/

# In Configuration_Files/DESPEC_General_Setup
Detector systems can be swtiched on/off in the code in Used_Systems.txt
Correlations Gates can be changed in Correlations_config.dat
Mapping and array sizes can be adjusted in DESPEC_Setup_File.h

# In 2D_Gates
2D polygon PID gates can be set


