#ifndef FATIMA_TOFCORR_H
#define FATIMA_TOFCORR_H

class FATIMA_tofCorr {
private:
  // All distances measured in mm, all times in ns
  double c_air; //speed of light in air in mm/ns
  // SET FROM PARAMETER FILE by load_ToF_ParameterFile, init to 0
  bool   doToFCorr;
  bool   useAIDA_eventbyevent;
  double offset_posXYZ[3];
  double aida_offset[9][3]; //AIDA z-offset by DSSD id (max 9 detectors!)
  void   load_ToF_ParameterFile();
  // SET FROM FILE by load_FATIMA_pos()
  double det_posX[35];
  double det_posY[35];
  double det_posZ[35];
  double distance[35];
  void   load_FATIMA_pos();

  // Dynamically set event-by-event
  double aida_posXYZ[3];
  double pvec[3];
  double len_vec;
  double dt;
  double Calc_dToF (double time_ns, int detid);

public:
  // inits private arrays to zero and loads from files
  FATIMA_tofCorr();
  ~FATIMA_tofCorr();

  // All distances measured in mm, all times in ns
  void   set_AIDA_pos(int dssd_id, double posx, double posy);
  double get_t_tofCorr (int detid, double time_ns);
  double get_dt_tofCorr (int detSTOP_id, double time_ns_detSTOP,
                         int detSTART_id, double time_ns_detSTART);
};


#endif
