#ifndef FEBEX_H
#define FEBEX_H


#include <iostream>
#include <string>
#include <sstream>
using namespace std;

typedef unsigned long long ULong64_t;


// ############################################## //
// ######## White Rabbit Data Structure ######### //
// ############################################## //

/*

struct WR_Header
{  

	unsigned int check_wr	: 32;

};

struct WR_Data
{  

	unsigned int nothing	: 16;
	unsigned int timestamp	: 16;

};

*/

// ############################################## //


// ############################################## //
// ################ Sum Channel ################# //
// ############################################## //

struct FEBEX_Add
{  

	unsigned int rest		: 20;
	unsigned int add		: 12;

};


struct FEBEX_Header
{  

	unsigned int three_four		: 8;
	unsigned int trig_type		: 4;
	unsigned int sfp_id		: 4;
	unsigned int chan_head		: 8;
	unsigned int ff			: 8;

};

struct FEBEX_Chan_Size
{  
	
	unsigned int ignore		: 2;
	unsigned int chan_size		: 30;

};

struct FEBEX_Half_Time
{  

	ULong64_t ext_time		: 16;
	unsigned int blank		: 16;

};

struct FEBEX_Evt_Time
{

	ULong64_t evt_time		: 32;

};

struct FEBEX_Flag_Hits
{

	unsigned int hit_pattern	: 16;
	unsigned int pile_flags		: 16;

};

struct DEADBEEF
{

	unsigned long deadbeef 		: 32;

};

// ############################################## //


// ############################################## //
// ############### Channels Data ################ //
// ############################################## //



struct FEBEX_Chan_Header
{
	
	ULong64_t ext_chan_ts		: 16;
	unsigned int Ch_ID		: 8;	
	unsigned int oxfo		: 8;

};


struct FEBEX_TS
{

	ULong64_t chan_ts		: 32;
  
};

struct FEBEX_En
{

	unsigned int chan_en		 :24;
    unsigned int cf              :6;
    unsigned int pileup          :1;
    unsigned int overflow        :1;
    
  
};

struct FEBEX_Future
{

	unsigned int future		: 32;
  
};

#endif


// ############################################## //
