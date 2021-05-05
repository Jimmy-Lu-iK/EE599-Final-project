#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/lib/cpplib.h"
#define MAXLINE 81

using namespace std;

struct Path {
	float PathUnits;
	float type[5];
	float ConvSize[5];
	float ConvDepth[5];
	float ResultHeight[5]; 
	float ResultWidth[5];
	float PE;	
	float Comparactor;
};

int main() {
  // Print Hello world!
  //CPPLib s;
  float PathNum;
  float MaxPoolPath;
  float LUTresource;
  float PEusageLUT;
  float PoolusageLUT;
  float InputFeatureMapHeight;
  float InputFeatureMapWidth;
  float InputFeatureMapDepth;
  Path path[5];
  //start inputing the information of multi path layer:

  PathNum = 4;
  MaxPoolPath = 4;
  LUTresource = 400000;
  PEusageLUT = 2200;
  PoolusageLUT = 500;
  InputFeatureMapHeight = 28;
  InputFeatureMapWidth = 28;
  InputFeatureMapDepth = 192;

  //path1:
  path[1].PathUnits = 1;
  path[1].type[1] = 0;
  path[1].ConvSize[1] = 1;
  path[1].ConvDepth[1] = 64;
	path[1].ResultHeight[1] = 64; 
	path[1].ResultWidth[1] = 28*28;
	//path[1].PE;	
	//path[1].Comparactor;
  cout << path[1].ResultWidth[1] << endl;

  //path2:
  path[2].PathUnits = 2;
  path[2].type[1] = 0;
  path[2].ConvSize[1] = 1;
  path[2].ConvDepth[1] = 96;
	path[2].ResultHeight[1] = 96; 
	path[2].ResultWidth[1] = 28*28;
  path[2].type[2] = 0;
  path[2].ConvSize[2] = 3*3;
  path[2].ConvDepth[2] = 128;
	path[2].ResultHeight[2] = 128; 
	path[2].ResultWidth[2] = 28*28;

  //path3:
  path[3].PathUnits = 2;
  path[3].type[1] = 0;
  path[3].ConvSize[1] = 1;
  path[3].ConvDepth[1] = 16;
	path[3].ResultHeight[1] = 16; 
	path[3].ResultWidth[1] = 28*28;
  path[3].type[2] = 0;
  path[3].ConvSize[2] = 5*5;
  path[3].ConvDepth[2] = 32;
	path[3].ResultHeight[2] = 32; 
	path[3].ResultWidth[2] = 28*28;

  //path4:
  path[4].PathUnits = 2;
  path[4].type[1] = 1;
  path[4].ConvSize[1] = 3*3;
  path[4].ConvDepth[1] = 192;
	path[4].ResultHeight[1] = 192; 
	path[4].ResultWidth[1] = 28*28;
  path[4].type[2] = 0;
  path[4].ConvSize[2] = 1;
  path[4].ConvDepth[2] = 32;
	path[4].ResultHeight[2] = 32; 
	path[4].ResultWidth[2] = 28*28;

  float ratio[5];

  ratio[1] = 1;
  ratio[2] = (path[2].ResultHeight[1]*path[2].ResultWidth[1]*path[2].ConvSize[1]*InputFeatureMapDepth + path[2].ResultHeight[2]*path[2].ResultWidth[2]*path[2].ConvSize[2]*path[2].ConvDepth[1])/(path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth);
  ratio[3] = (path[3].ResultHeight[1]*path[3].ResultWidth[1]*path[3].ConvSize[1]*InputFeatureMapDepth + path[3].ResultHeight[2]*path[3].ResultWidth[2]*path[3].ConvSize[2]*path[3].ConvDepth[1])/(path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth);
  cout<<ratio[2]<<endl;
  cout<<ratio[3]<<endl;
  float TotalRatio = ratio[2]+ratio[3]+1;
  float minilatency = 10000000;
  float rightx;
  float righty;
  float rightz;

  for(int x=1; x<((LUTresource-PEusageLUT-PoolusageLUT)/TotalRatio); x++){
      for(int y=1; y<((LUTresource-(TotalRatio*x+1)*PEusageLUT)/PoolusageLUT); y++){
        for(int z=1; z<((LUTresource-(TotalRatio*x*PEusageLUT)-y*PoolusageLUT)/PEusageLUT); z++){
            //float latency = abs((path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth)/x - path[4].ResultWidth[1]*path[4].ResultHeight[1]/y - path[4].ResultHeight[2]*path[4].ResultWidth[2]*path[4].ConvSize[2]*path[4].ConvDepth[1]/z);
            //cout<<"test:"<<endl;
            //cout <<"path1:"<<path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth<<" "<<x<<" "<<(path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth)/x <<endl;
            //cout <<"path4pq:"<<path[4].ResultWidth[1]*path[4].ResultHeight[1]<<" "<<y<<" "<<path[4].ResultWidth[1]*path[4].ResultHeight[1]/y <<endl;
            //cout <<"path4p2:"<<path[4].ResultHeight[2]*path[4].ResultWidth[2]*path[4].ConvSize[2]*path[4].ConvDepth[1]<<" "<<z<<" "<<path[4].ResultHeight[2]*path[4].ResultWidth[2]*path[4].ConvSize[2]*path[4].ConvDepth[1]/z <<endl;
            float latency1 = path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth/x;
            float latency2 = path[4].ResultWidth[1]*path[4].ResultHeight[1]*2/y + path[4].ResultHeight[2]*path[4].ResultWidth[2]*path[4].ConvSize[2]*path[4].ConvDepth[1]/z;
            float miner;
            if(latency1 <= latency2)
              miner = latency2;
            else 
              miner = latency1;

            if(minilatency>=miner) {
              minilatency = miner;
              rightx = x;
              righty = y;
              rightz = z;
            }
        }
      }
  }
  cout<<"results:"<<endl;
  cout<<minilatency<<endl;
  cout<<rightx<<endl;
  cout<<righty<<endl;
  cout<<rightz<<endl;
  return 0;








   /*
  std::string menu =
      "**************************************************************\n"
      "* Welcome to multi path optimizations for general CNN models. \n"
      "* 1. Start inputing information about multi path layer        \n"
      "* 2. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char number = input[0];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Start inputing information about multi path layer        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;

    menu = "Please input total path num (no more than 5):";
    std::cout << menu;
    getline(std::cin, input);
    if(!input.size())
      man:std::cout<<"Please select 2 - 5\n"<<std::endl;
    getline(std::cin, input);
    if(input != "2" && input != "3" && input != "4" && input != "5"){
      goto man;
    } 
    PathNum = atoi(input.c_str());
    cout << "PathNum:" << PathNum << endl;

    menu = "Is the multi path contains maxpooling? (1-yes, 0-no):";
    std::cout << menu;
    getline(std::cin, input);
    if(!input.size())
      man2:std::cout<<"Please select 0 or 1\n"<<std::endl;
    getline(std::cin, input);
    if(input != "0" && input != "1"){
      goto man2;
    } 
    MaxPoolTure = atoi(input.c_str());
    cout << "MaxPoolTure:" << MaxPoolTure << endl;

    menu = "Please input total LUT resource:";
    std::cout << menu;
    getline(std::cin, input);
    LUTresource = atoi(input.c_str());
    cout << "LUTresource:" << LUTresource << endl;
    break;
  }
  }*/
}