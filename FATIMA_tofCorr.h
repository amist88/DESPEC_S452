#ifndef FATIMA_TOFCORR_H
#define FATIMA_TOFCORR_H

#define FATIMA_TOFCORR_MAX_DET 36
#define FATIMA_TOFCORR_MAX_DSSD 9

class FATIMA_tofCorr {
private:
  // All distances measured in mm, all times in ns
  double c_air; //speed of light in air in mm/ns
  // SET FROM PARAMETER FILE by load_ToF_ParameterFile, init to 0
  bool   doToFCorr;
  bool   useAIDA_eventbyevent;
  double offset_posXYZ[3];
  double aida_offset[FATIMA_TOFCORR_MAX_DSSD][3]; //AIDA z-offset by DSSD id (max 9 detectors!)
  void   load_ToF_ParameterFile();
  // SET FROM FILE by load_FATIMA_pos()
  double det_posX[FATIMA_TOFCORR_MAX_DET];
  double det_posY[FATIMA_TOFCORR_MAX_DET];
  double det_posZ[FATIMA_TOFCORR_MAX_DET];
  double distance[FATIMA_TOFCORR_MAX_DET];
  void   load_FATIMA_pos();

  // Dynamically set event-by-event
  double aida_posXYZ[3];
  double pvec[3];
  double len_vec;
  double dt;
  double length(double cx, double cy, double cz);
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
