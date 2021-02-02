// E. Sahin 2021 Jan.
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int testPID (){
int lineN = 0;
ifstream file("PIDtest.C");
string data = "";

int vN=0;
string values[12];
while(getline(file, data,','))
{
  if(lineN>1 && lineN%2==0 && lineN<13){
      values[vN]=data;
      vN++;
  }else if(lineN>2 && lineN%2==1 && lineN<14){
      string data2 = data.substr(0, 7);
      values[vN]=data2;
      vN++;
  }
  lineN++;
}

file.close();

ofstream gateInfo;
gateInfo.open ("ZAoQ.txt", fstream::out | fstream::app);
gateInfo << "#Header \n";

for (int i = 0; i < 11;i = i + 2){
 gateInfo << values[i] << "   " << values[i+1] << endl;
}

gateInfo.close();
return 0;
}
