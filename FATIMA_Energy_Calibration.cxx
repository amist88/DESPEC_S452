#include "FATIMA_Energy_Calibration.h"
#include "Configuration_Files/DESPEC_General_Setup/DESPEC_Setup_File.h"


#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <unistd.h>

using namespace std;

//----------------------------------------------------------

FATIMA_Energy_Calibration::FATIMA_Energy_Calibration(){
    load_Calibration_File();
    do_gm = 1;
    have_gm_list = 0;
    last_ts_in_list = 0;
    current_gmlist_pos = 0;
    next_ts_for_update = 0;
    ResetGainMatching();
    load_GainMatching_List();
}

//----------------------------------------------------------

FATIMA_Energy_Calibration::~FATIMA_Energy_Calibration(){
    gm_list.clear();
}

//----------------------------------------------------------

void FATIMA_Energy_Calibration::load_Calibration_File(){

    const char* format = "%d %lf %lf %lf %lf %lf";


    ifstream calib_file("Configuration_Files/FATIMA/FATIMA_Energy_Calibration.txt");

    if(calib_file.fail()){
        cerr << "Could not find Fatima Energy Calibration file" << endl;
        exit(0);
    }
    string line;

    double tmp_coeffs[5] = {0,0,0,0,0};

    int det_id = 0;

    while(calib_file.good()){
        getline(calib_file,line,'\n');
        if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&det_id,&tmp_coeffs[0]
                                  ,&tmp_coeffs[1],&tmp_coeffs[2]
                                  ,&tmp_coeffs[3],&tmp_coeffs[4]);

        for(int i = 0;i < 5;++i){
            calib_coeffs[det_id][i] = tmp_coeffs[i];
             original_calib_coeffs[det_id][i] = tmp_coeffs[i];
        }
    }
}

//----------------------------------------------------------

double FATIMA_Energy_Calibration::Calibrate(double E,int det_id){
    //calibrate using Horner's method (https://en.wikipedia.org/wiki/Horner%27s_method)
    double Energy_c = calib_coeffs[det_id][0];
    for(int i = 1;i < 5;++i) Energy_c = Energy_c*E + calib_coeffs[det_id][i];

    Energy_c += (static_cast<double>(rand())/static_cast<double>(RAND_MAX+0.5));
    return Energy_c;
}

//----------------------------------------------------------
void FATIMA_Energy_Calibration::ResetGainMatching()
{
   for(int i=0; i<100; i++) {
     gm_coeffs[i][0] = 0;
     gm_coeffs[i][1] = 1;
   }
}

void FATIMA_Energy_Calibration::UpdateGainMatching(int ts_minutes)
{
     //For cases where all future attempts to get a gm factor will fail (no list at all,
     //or current ts is larger than largest ts in the list) set the next update point
     //to a time farfar in the future (80000 minutes is approx 56 days). Might cause
     //problems for long consecutive data sets...
     if (!have_gm_list){
       printf("INFO: FATIMA gainmatching - No gain matching list found. Will not attempt to load again.\n");
       next_ts_for_update = (ts_minutes + 80000)*1e9*60;
       return;
     }

   if(ts_minutes > last_ts_in_list){
       printf("INFO: FATIMA gainmatching - TS larger than largest gm-file. Will not attempt to load again.\n");
    next_ts_for_update = (ts_minutes + 80000)*1e9*60;
     return;
   }

   int tshigh = std::get<1>(gm_list[current_gmlist_pos]);
   int tslow = std::get<0>(gm_list[current_gmlist_pos]);
   //printf("tl: %d, th: %d in %s\n", tslow, tshigh, std::get<2>(gm_list[current_gmlist_pos]).c_str());
   do_gm=1;
   if (tslow <= ts_minutes && tshigh >= ts_minutes) {
     load_GainMatching_File(gm_list[current_gmlist_pos]);
     current_gmlist_pos++;

   } else {
     //Find the correct entry in the list, if none exists, use the previous gm values.
     int countgme = 0;
     bool foundit = 0;
     for (auto gme : gm_list) {
       int tshigh_tmp = std::get<1>(gme);
       int tslow_tmp = std::get<0>(gme);
       //printf("Trying ts %d,,,tl: %d, th: %d in %s\n", ts_minutes, tslow_tmp, tshigh_tmp, std::get<2>(gme).c_str());
       countgme++;
       if (tslow_tmp <= ts_minutes && tshigh_tmp >= ts_minutes) {
         current_gmlist_pos = countgme;
         load_GainMatching_File(gme);
         foundit = 1;
         break;
       }
       if(tslow_tmp > ts_minutes){
         current_gmlist_pos = countgme;
         next_ts_for_update = tslow_tmp*1E9*60;
         //printf("Thinks there is none\n");
         break;
       }
     }
     if(!foundit) {
       printf("WARNING: FATIMA, no matching gainmatching parameter file found. Not updating parameters! (This TS = %20d -- newxtTS = %lu\n", ts_minutes, next_ts_for_update);
       do_gm=0;

     }
   }

   if (do_gm) {
     printf("Updating Gain Matching for FATIMA:\n");
     for(int i=0; i<36; i++) {
        double A = gm_coeffs[i][1];
        double B = gm_coeffs[i][0]*10;
        double a0 = original_calib_coeffs[i][4];
        double a1 = original_calib_coeffs[i][3];
        double a2 = original_calib_coeffs[i][2];
        double a3 = original_calib_coeffs[i][1];
        double a4 = original_calib_coeffs[i][0];
        //printf("original --det%02d  %lf  %lf  %lf\n", i, a0, a1, a2);
        //printf("A%lf  B%lf\n", A, B);
        calib_coeffs[i][4] = a4*pow(B,4) + a3*pow(B,3) + a2*pow(B,2) + a1*B + a0;
        calib_coeffs[i][3] = A*(4*a4*pow(B,3) + 3*a3*pow(B,2) + 2*a2*B + a1);
        calib_coeffs[i][2] = pow(A,2)*(6*a4*pow(B,2) + 3*a3*B + a2);
        calib_coeffs[i][1] = pow(A,3)*(4*a4*B + a3);
        calib_coeffs[i][0] = pow(A,4)*a4;
    //printf("corrected--det%02d  %lf  %lf  %lf\n", i, calib_coeffs[i][4],
       //                                              calib_coeffs[i][3],
        //                                             calib_coeffs[i][2]);
     }
   }
}

void FATIMA_Energy_Calibration::load_GainMatching_List()
{
  //std::system("rm -f Configuration_Files/FATIMA/gmfiles.list");
  //std::system("ls Configuration_Files/FATIMA/gainmatching/* > Configuration_Files/FATIMA/gmfiles.list");
  ifstream gm_filelist("Configuration_Files/FATIMA/gmfiles.list");
  if(gm_filelist.fail()){
    cerr << "Could not read from FATIMA gainmatching directory Configuration_Files/FATIMA/gainmatching!\n" << endl;
    have_gm_list= 0;
    return;
  } else {
    have_gm_list = 1;
  }
  string line;
  char name[100];
  int firstts = 0;
  int lastts = 0;
  gmentry tmpentry;
  int offset=FatGM_Offset;
  printf("Reading Gain matching file list:\n");
  while(gm_filelist.good()){
    getline(gm_filelist,line);
    if(line[0] == '#') continue;
    /*
    if(access(line.c_str(),F_OK)==-1){
     continue;
     cout << "gm file not found!" << line << endl;
     }
     */
    if(sscanf(line.c_str(),
        "Configuration_Files/FATIMA/gainmatching/%[^_]_%d_%d.gm",
        name, &firstts, &lastts) == 3) {
      //printf("%s\n", line.c_str());
      //printf("%d, %d, %s\n", firstts+offset, lastts+offset, name);
      tmpentry = std::make_tuple(firstts+offset, lastts+offset, line);
      gm_list.push_back(tmpentry);
    }
  }
  gm_filelist.close();
  if(gm_list.size() > 0){
    sort(gm_list.begin(), gm_list.end());
    last_ts_in_list = std::get<1>(gm_list.back());
  }else{
    printf("WARNING - FATIMA: Haven't read any entries from gmfiles.list. Check path?\n");
    exit(0);
  }
  /*
  for (auto le : gm_list) {
      cout << std::get<0>(le) << endl;
      cout << std::get<1>(le) << endl;
      cout << std::get<2>(le) << endl;
  }*/
}
void FATIMA_Energy_Calibration::load_GainMatching_File(gmentry gm)
{
  string filename = std::get<2>(gm);
  ifstream gmfile (filename);
  if(gmfile.fail()){
    cerr << "Could not read FATIMA gainmatching file:"<< filename << endl;
    do_gm = 0;
    return;
  }
  ResetGainMatching();
  printf("Reading gain matching parameters from %s:\n", filename.c_str());
  string line;
  int deti = -1;
  double a = 1;
  double b = 0;
  next_ts_for_update = ((unsigned long) std::get<1>(gm))*1E9*60;
  while(gmfile.good()){
    getline(gmfile,line);
    if(line[0] == '#') continue;

    if(sscanf(line.c_str(),
        "%d\t%lf\t%lf",
        &deti, &b, &a) == 3) {
      gm_coeffs[deti][0] = b;
      gm_coeffs[deti][1] = a;
      //cout << "det " << deti << " b " << b << " a " << a << endl;
    }
  }
  gmfile.close();
}
