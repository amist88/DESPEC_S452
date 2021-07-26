#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Header
{
  unsigned int empty : 8;
  unsigned int channels:6;
  unsigned int check1:2;
  unsigned int crate:8;
  unsigned int check2:3;
  unsigned int geo:5;
};

struct Data
{
  unsigned int value:12;
  unsigned int OF:1;
  unsigned int UF:1;
  unsigned int empty:2;  
  unsigned int channel:5;
  unsigned int check:6;
  unsigned int geo:5;
};

struct End
{
  unsigned int evCounter:24;
  unsigned int check:3;
  unsigned int geo:5;
};
