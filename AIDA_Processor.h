// #ifndef AIDA_PROCESSOR_H
// #define AIDA_PROCESSOR_H
// 
// #define GPP_FLAG ((__GNUC__ == 4 && __GNUC_MINOR__ >= 9) || __GNUC__ > 4)
// 
// #if(GPP_FLAG)
//     #include <thread>
// #endif
// 
// #include <iostream>
// #include <fstream>
// 
// #include "TX_Matrix.h"
// #include "XY_Matrix.h"
// #include "Raw_Event.h"
// #include "AIDA_Data_Streamer.h"
// #include "AIDA_Decay_Event_Store.h"
// 
// 
// typedef unsigned long long ULong64_t;
// 
// class AIDA_Processor{
// private:
// 
//     const bool TX_CALC = true;
//     const bool XY_CALC = false;
// 
//     bool USE_THREADS;
//     
//     int max_len_Streamer,max_len_T_Matrix_Row;
//     int max_len_TX_Matrix,max_len_XY_Matrix;
// 
//     bool* empty_bunch;
// 
//     int amount_z_strips,amount_thr,am_sub_threads;
//     int am_threads;
// 
//     AIDA_Data_Streamer* Stream;
// 
//     TX_Matrix** TX;
//     XY_Matrix** XY;
// 
//     #if(GPP_FLAG)
//         std::thread threading(bool,int);
//     #endif
// 
//     inline void non_threading(bool,int);
// 
//     void check_Thread_Use();
//     void RETURN_THREAD();
// 
// public:
//     AIDA_Processor(int,int*);
//     ~AIDA_Processor();
//     
//     void PROCESSING(AIDA_Decay_Event_Store*);
//     void Store_and_Purge(bool*,int*,ULong64_t*,double*,int*,int);
//     void get_DATA(Raw_Event*);
// };
// 
// #endif
