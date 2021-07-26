#ifndef TDC_HEADER_H
#define TDC_HEADER_H


#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct TDC_Check
{  

	unsigned int useful		: 5;
	unsigned int no			: 22;
	unsigned int type		: 5;
	

};
struct TDC_Glob_Header
{  

	unsigned int geo		: 5;
	unsigned int count		: 22;
	unsigned int empty		: 5;
	

};

struct TDC_Header
{

	unsigned int bunch		: 12;
	unsigned int id			: 12;
	unsigned int tdc		: 2;
	unsigned int blank		: 1;
	unsigned int empty 		: 5;

};

struct TDC_Measurement
{

	unsigned int measurement : 21;
	unsigned int channel	 : 5;
	unsigned int trail_lead  : 1;
	unsigned int empty_2	 : 5;

};

struct TDC_Trailer
{

	unsigned int count		: 12;
	unsigned int id			: 12;
	unsigned int tdc		: 2;
  	unsigned int blank_3	: 1;
	unsigned int empty_3 	: 5;
	
};

struct TDC_Error
{

	unsigned int error		: 15;
	unsigned int blank		: 9;
	unsigned int tdc		: 2;
  	unsigned int blank_4	: 1;
	unsigned int empty_4	: 5;
	
};

#endif
