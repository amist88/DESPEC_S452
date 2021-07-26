#ifndef QDC_HEADERS_H
#define QDC_HEADERS_H


#include <iostream>
#include <string>
#include <sstream>
using namespace std;
typedef unsigned long long ULong64_t;


struct QDC_Header
{  

	unsigned int length		: 28;
	unsigned int check_a	: 4;

};

struct QDC_Header_2
{

	unsigned int channels	: 8;
	unsigned int pattern	: 15;
	unsigned int empty		: 3;
	unsigned int fail		: 1;
	unsigned int geo 		: 5;

};

struct QDC_Format_Size
{

	unsigned long size		: 22;
	unsigned int empty		: 6;
	unsigned int format		: 4;

};

struct QDC_Time
{

	ULong64_t trigger_tag : 32;

};

struct QDC_Traces
{

	unsigned int third_trace	: 10;
	unsigned int second_trace	: 10;	
	unsigned int first_trace	: 10;
	unsigned int trgcod			: 2;

};

struct QDC_Extras
{

	ULong64_t fine_time	: 10;
	unsigned int flags	: 6;	
	ULong64_t ext_trig	: 16;
	
};


struct QDC_Data
{

	unsigned int QS		:15;
	unsigned int empty	:1;
	unsigned int QL		:16;
  
};

struct QDC_End
{
  unsigned int evCounter:24;
  unsigned int check:3;
  unsigned int geo:5;
};
#endif
