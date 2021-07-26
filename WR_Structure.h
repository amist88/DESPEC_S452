#ifndef WR_HEADER_H
#define WR_HEADER_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// ############################################## //
// ######## White Rabbit Data Structure ######### //
// ############################################## //

static const int WR_TS_ID_L = 0x03e1;
static const int WR_TS_ID_M = 0x04e1;
static const int WR_TS_ID_H = 0x05e1;
static const int WR_TS_ID_X = 0x06e1;

struct WR_Data
{

    unsigned int timestamp  : 16;
    unsigned int id    : 16;

};

// ############################################## //

#endif
