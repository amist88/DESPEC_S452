// mrudigiere 11.2021. Added this Class for position dependent
// time of flight correction for FATIMA gamma timing.

#include "FATIMA_tofCorr.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <math.h>

FATIMA_tofCorr::FATIMA_tofCorr(){
  useAIDA_eventbyevent = 0;
  memset(offset_posXYZ, 0, sizeof(double)*3);
  memset(aida_offset, 0, sizeof(double)*3*FATIMA_TOFCORR_MAX_DSSD);
  memset(det_posX, 0, sizeof(double)*FATIMA_TOFCORR_MAX_DET);
  memset(det_posY, 0, sizeof(double)*FATIMA_TOFCORR_MAX_DET);
  memset(det_posZ, 0, sizeof(double)*FATIMA_TOFCORR_MAX_DET);
  doToFCorr = 1;
  load_FATIMA_pos();
  load_ToF_ParameterFile();
  c_air = 299.702547 ; //speed of light in air in mm/ns
}

FATIMA_tofCorr::~FATIMA_tofCorr(){

}

void FATIMA_tofCorr::set_AIDA_pos(int dssd_id, double posx, double posy) {
  if (useAIDA_eventbyevent) {
    aida_posXYZ[0] = aida_offset[dssd_id][0] + posx;
    aida_posXYZ[1] = aida_offset[dssd_id][1] + posy;
    aida_posXYZ[2] = aida_offset[dssd_id][2];
  }
}
double FATIMA_tofCorr::length(double cx, double cy, double cz) {
  return sqrt(pow(cx,2) + pow(cy,2) + pow(cz,2));
}

double FATIMA_tofCorr::get_t_tofCorr (int detid, double time_ns) {
  if (doToFCorr && detid < FATIMA_TOFCORR_MAX_DET && detid > -1) {
    memset(this->pvec, 0, sizeof(double)*3);
    pvec[0] = +offset_posXYZ[0];
    pvec[1] = +offset_posXYZ[1];
    pvec[2] = +offset_posXYZ[2];
    if(useAIDA_eventbyevent) {
      pvec[0] += aida_posXYZ[0];
      pvec[1] += aida_posXYZ[1];
      pvec[2] += aida_posXYZ[2];
    }
    len_vec = this->length(pvec[0] - det_posX[detid],
                           pvec[1] - det_posY[detid],
                           pvec[2] - det_posZ[detid]);
    printf("calculated l(%02d): %lf\n", detid, len_vec);
    printf("tabulated  l(%02d): %lf\n", detid, distance[detid]);
    dt = (distance[detid] - len_vec)/c_air;
    return time_ns + dt;
  }else{
    return time_ns;
  }
  printf("WARNING in FATIMA_tofCorr::get_t_tofCorr -- should never get here!\n");
  return 0;
}

double FATIMA_tofCorr::get_dt_tofCorr (int detSTOP_id, double time_ns_detSTOP,
                                       int detSTART_id, double time_ns_detSTART) {
  return get_t_tofCorr(detSTOP_id, time_ns_detSTOP)
         - get_t_tofCorr(detSTART_id, time_ns_detSTART);
}

void FATIMA_tofCorr::load_FATIMA_pos() {
  const char* format = "%d %lf %lf %lf";
  printf("Loading FATIMA detector positions.\n");
  std::ifstream pos_file("Configuration_Files/FATIMA/FATIMA_pos.txt");

  if(pos_file.fail()){
      std::cout << "  Could not find Fatima detector position file" << std::endl;
      exit(0);
  }
  std::string line;
  double tmppos[3];
  int tmpid = 0;

  while(pos_file.good()){
      getline(pos_file,line,'\n');
      if(line[0] == '#') continue;
      sscanf(line.c_str(),format,&tmpid,&tmppos[0]
                                ,&tmppos[1],&tmppos[2]);
      det_posX[tmpid] = tmppos[0];
      det_posY[tmpid] = tmppos[1];
      det_posZ[tmpid] = tmppos[2];
      distance[tmpid] = sqrt(pow(tmppos[0],2)
                                    + pow(tmppos[1],2)
                                    + pow(tmppos[2],2));
  }
}

void FATIMA_tofCorr::load_ToF_ParameterFile(){
  printf("Loading FATIMA ToF Correction Parameter File.\n");
  printf("=============================================\n");
  std::ifstream param_file("Configuration_Files/FATIMA/FATIMA_ToF_Parameters.txt");
  if(param_file.fail()){
      std::cout << "  WARNING FATIMA: Could not find Fatima ToF parameter file." << std::endl;
      std::cout << "                  The code will still run, but no ToF corrections will be applied!" << std::endl;
      doToFCorr = 0;
  }
  std::string line;
  double tmp;
  double tmppos[3];
  bool readaline = 0;
  while(param_file.good()){
    if (!readaline) {
      getline(param_file,line,'\n');
    } else {
      readaline = 0;
    }
    if(line[0] == '#' || line[0] == '\0') continue;
    if(line.compare("USE_TOF") == 0) {
      printf("  USE_TOF\n");
      while(param_file.good()) {
        getline(param_file,line,'\n');
        if(line[0] == '#' || line[0] == '\0') continue;
        if(sscanf(line.c_str(),"%lf",&tmp) == 1){
          printf("    %lf\n", tmp);
          doToFCorr = tmp;
          break;
        }else{
          printf("  USE_TOF not set. Setting to 0\n");
          doToFCorr = 0;
          readaline = 1;
          break;
        }
      }
    }
    else if(line.compare("USE_AIDA_POS") == 0) {
      printf("  USE_AIDA_POS\n");
      while(param_file.good()) {
        getline(param_file,line,'\n');
        if(line[0] == '#' || line[0] == '\0') continue;
        if(sscanf(line.c_str(),"%lf",&tmp) == 1){
          printf("    %lf\n", tmp);
          useAIDA_eventbyevent = tmp;
          break;
        }else{
          printf("  USE_AIDA_POS not set. Setting to 0\n");
          useAIDA_eventbyevent = 0;
          readaline = 1;
          break;
        }
      }
    }
    else if (line.compare("CONST_OFFSET") == 0) {
      printf("  CONST_OFFSET\n");
      int max = 0;
      while(param_file.good() && max < 3) {
        getline(param_file,line,'\n');
        if(line[0] == '#' || line[0] == '\0') continue;
        if(sscanf(line.c_str(),"%lf",&tmp) == 1){
          printf("    %lf\n", tmp);
          offset_posXYZ[max] = tmp;
          max++;
        }else{
          //offset_posXYZ is initialised to 0.
          readaline = 1;
          break;
        }
      }
      if (max < 3) {
        printf("    Less than three arguments given for CONST_OFFSET. Setting rest to 0\n");
      }
    }
    else if (line.compare("AIDA_OFFSET") == 0) {
      printf("  AIDA_OFFSET\n");
      int max = 0;
      int det = 0;
      while(param_file.good() && max < FATIMA_TOFCORR_MAX_DSSD) {
        getline(param_file,line,'\n');
        if(line[0] == '#' || line[0] == '\0') continue;
        if(sscanf(line.c_str(),"%d %lf %lf %lf",
                               &det, &tmppos[0], &tmppos[1], &tmppos[2]) == 4){
          printf("    %d %lf %lf %lf\n", det, tmppos[0], tmppos[1], tmppos[2]);
          if (det < 9) {
            aida_offset[det][0] = tmppos[0];
            aida_offset[det][1] = tmppos[1];
            aida_offset[det][2] = tmppos[2];
          }
          max++;
        }else{
          // aida_offset is initialised to 0.
          readaline = 1;
          break;
        }
      }
      if (max < 9) {
        printf("    Found %d/%d AIDA_OFFSET parameters. Setting rest to 0\n", max, FATIMA_TOFCORR_MAX_DSSD);
      }
    }
  }
}
