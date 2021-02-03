// E. Sahin and H.M. Albers 2021 Jan.
// Run code using .L PID_mac2txt.cpp; PID("inputcutfile.C","outputfilename.txt");
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <cstring>
using namespace std;

int PID (const char *filename, const char *outfilename){
int NumPoints = 0;
ifstream file(filename);
string data = "";
char newline[500];
size_t pos1;
size_t pos2;
size_t pos3;
size_t found;
string values1[100];
string values2[100];


if (!file.is_open()){
   cout << "Cut file not found! Exit." << endl;   
   exit (0);
}
else{
    while(getline(file, data)){    
        
       found = data.find("SetPoint");
       if(found!=string::npos){

          pos1 = data.find(",");
          pos2 = data.find(",",pos1+1);
          pos3 = data.find(")",pos2+1);

          if(NumPoints<100){
             values1[NumPoints] = data.substr(pos1+1,(pos2-pos1)-1);
             values2[NumPoints] = data.substr(pos2+1,(pos3-pos2)-1);
  
          }
          else{
             cout << "Too many points in the file (max=100). Exit. " << endl;
             exit (0);
          }
          NumPoints++;

           
       }

   }

      
   
}


file.close();

ofstream gateInfo;
gateInfo.open (outfilename, fstream::out | fstream::app);
gateInfo << "#Header \n";

for (int i = 0; i < NumPoints;i++){
 gateInfo << values1[i] << "   " << values2[i] << endl;
}

gateInfo.close();

return 0;
}
