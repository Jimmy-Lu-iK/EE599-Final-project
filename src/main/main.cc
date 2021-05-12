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
	float PathUnits = 0;
	float type[5] = {0};
	float ConvSize[5] = {0};
	float ConvDepth[5] = {0};
	float ResultHeight[5] = {0}; 
	float ResultWidth[5] = {0};
	float PE = 0;	
  float DSP = 0;
	float Comparactor = 0;
  int maxpoolingTrue = 0;
};

int main() {
  // Print Hello world!
  //CPPLib s;
  float PathNum;
  float MaxPoolPath;
  float LUTresource;
  float PEusageLUT;
  float PEusgaeDSP;
  float PoolusageLUT;
  float DSPresource;
  float InputFeatureMapHeight;
  float InputFeatureMapWidth;
  float InputFeatureMapDepth;
  int DSPorLUT; // 1 means DSP is the bottleneck;0 means LUT is the bottleneck
  Path path[5];
  //start inputing the information of multi path layer:

  PathNum = 4;
  MaxPoolPath = 4;
  LUTresource = 20000;
  PEusageLUT = 300;
  PEusgaeDSP = 4;
  PoolusageLUT = 100;
  DSPresource = 50000;
  InputFeatureMapHeight = 28;
  InputFeatureMapWidth = 28;
  InputFeatureMapDepth = 192;

  //determine the bottleneck, DSP or LUT?
  if(LUTresource>PEusageLUT*DSPresource/PEusgaeDSP){
    cout<<"DSP is the bottleneck of this multi-path"<<endl;
    DSPorLUT = 1;
  }
  else {
    cout <<"LUT is the bottleneck of this multi-path"<<endl;
    DSPorLUT = 0;
  }

  //path1:
  path[1].PathUnits = 1;
  path[1].type[1] = 0;
  path[1].ConvSize[1] = 1;
  path[1].ConvDepth[1] = 64;
	path[1].ResultHeight[1] = 64; 
	path[1].ResultWidth[1] = 28*28;
  path[1].maxpoolingTrue = 0;
	//path[1].PE;	
	//path[1].Comparactor;
  //cout << path[1].ResultWidth[1] << endl;

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
  path[2].maxpoolingTrue = 0;

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
  path[3].maxpoolingTrue = 0;

  //path5: maxpooling should only be put in path[5]
  path[5].PathUnits = 2;
  path[5].type[1] = 1;
  path[5].ConvSize[1] = 3*3;
  path[5].ConvDepth[1] = 192;
	path[5].ResultHeight[1] = 192; 
	path[5].ResultWidth[1] = 28*28;
  path[5].type[2] = 0;
  path[5].ConvSize[2] = 1;
  path[5].ConvDepth[2] = 32;
	path[5].ResultHeight[2] = 32; 
	path[5].ResultWidth[2] = 28*28;
  path[5].maxpoolingTrue = 1;

  float ratio[5] = {0};
  //for (int i=0;i<5;i++)
   // cout << ratio[i]<<endl;

  ratio[1] = 1;
  if(path[2].PathUnits!=0) 
    ratio[2] = (path[2].ResultHeight[1]*path[2].ResultWidth[1]*path[2].ConvSize[1]*InputFeatureMapDepth + path[2].ResultHeight[2]*path[2].ResultWidth[2]*path[2].ConvSize[2]*path[2].ConvDepth[1])/(path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth);
  if(path[3].PathUnits!=0)
    ratio[3] = (path[3].ResultHeight[1]*path[3].ResultWidth[1]*path[3].ConvSize[1]*InputFeatureMapDepth + path[3].ResultHeight[2]*path[3].ResultWidth[2]*path[3].ConvSize[2]*path[3].ConvDepth[1])/(path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth);
  if(path[4].PathUnits!=0)
    ratio[4] = (path[4].ResultHeight[1]*path[4].ResultWidth[1]*path[4].ConvSize[1]*InputFeatureMapDepth + path[4].ResultHeight[2]*path[4].ResultWidth[2]*path[4].ConvSize[2]*path[4].ConvDepth[1])/(path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth);
  if((path[5].maxpoolingTrue == 0)&(path[5].PathUnits !=0))
    ratio[5] = (path[5].ResultHeight[1]*path[5].ResultWidth[1]*path[5].ConvSize[1]*InputFeatureMapDepth + path[5].ResultHeight[2]*path[5].ResultWidth[2]*path[5].ConvSize[2]*path[5].ConvDepth[1])/(path[1].ResultHeight[1]*path[1].ResultWidth[1]*path[1].ConvSize[1]*InputFeatureMapDepth);
  
  //BLOCKSIZE optimization:
  float minilatency = 10000000;
  float righta;
  float rightb;
  float rightc;
  //float rightd;
  float righte;
  float rightf;

  if(DSPorLUT) {//DSP bottleneck model:
    cout <<"Brute Force:"<<endl;
    righte = floor((LUTresource - DSPresource/PEusgaeDSP*PEusageLUT)/PoolusageLUT);
    for(int a=1; a<(DSPresource/PEusgaeDSP - (PathNum-1)); a++){
        for(int b=1; b<(DSPresource/PEusgaeDSP - a - (PathNum-2)); b++){
            for(int c=1; c<(DSPresource/PEusgaeDSP - a - b - (PathNum-3)); c++){
                for(int f=1; f<(DSPresource/PEusgaeDSP - a - b - c- (PathNum-4));f++){
                  int latencyP1 = path[1].ResultHeight[1]*ceil(path[1].ResultWidth[1]/a)*path[1].ConvSize[1]*InputFeatureMapDepth;
                  int latencyP2 = path[2].ResultHeight[1]*ceil(path[2].ResultWidth[1]/b)*path[2].ConvSize[1]*InputFeatureMapDepth+path[2].ResultHeight[2]*ceil(path[2].ResultWidth[2]/b)*path[2].ConvSize[2]*path[2].ConvDepth[1];
                  int latencyP3 = path[3].ResultHeight[1]*ceil(path[3].ResultWidth[1]/c)*path[3].ConvSize[1]*InputFeatureMapDepth+path[3].ResultHeight[2]*ceil(path[3].ResultWidth[2]/c)*path[3].ConvSize[2]*path[3].ConvDepth[1];
                  int latencyP4 = 0;
                  int latencyP5 = path[5].ResultHeight[1]*path[5].ResultWidth[1]/righte+path[5].ResultHeight[2]*ceil(path[5].ResultWidth[2]/f)*path[5].ConvSize[2]*path[5].ConvDepth[1];
              
                  int TempMaxLatency = latencyP1;
                  if(latencyP2>TempMaxLatency) TempMaxLatency = latencyP2;
                  if(latencyP3>TempMaxLatency) TempMaxLatency = latencyP3;
                  if(latencyP4>TempMaxLatency) TempMaxLatency = latencyP4;
                  if(latencyP5>TempMaxLatency) TempMaxLatency = latencyP5;
                  //cout << TempMaxLatency <<endl;
                  if(minilatency>TempMaxLatency) {
                    minilatency = TempMaxLatency;
                    righta = a;
                    rightb = b;
                    rightc = c;
                    //rightd = d;
                    //righte = e;
                    rightf = f;
                  }

                }
            } 
        }
    }
  }
  else {
    for(int a=1; a<(LUTresource - (PathNum-1)*PEusageLUT - PoolusageLUT)/PEusageLUT; a++){
      for(int b=1; b<(LUTresource - a*PEusageLUT - (PathNum-2)*PEusageLUT - PoolusageLUT)/PEusageLUT; b++){
        for(int c=1; c<(LUTresource - (a+b)*PEusageLUT - (PathNum-3)*PEusageLUT - PoolusageLUT)/PEusageLUT; c++){
          for(int f=1; f<(LUTresource - (a+b+c)*PEusageLUT - (PathNum-34)*PEusageLUT - PoolusageLUT)/PEusageLUT; f++){
            for(int e=1;e<(LUTresource - (a+b+c+f)*PEusageLUT)/PoolusageLUT; e++){
              int latencyP1 = path[1].ResultHeight[1]*ceil(path[1].ResultWidth[1]/a)*path[1].ConvSize[1]*InputFeatureMapDepth;
              int latencyP2 = path[2].ResultHeight[1]*ceil(path[2].ResultWidth[1]/b)*path[2].ConvSize[1]*InputFeatureMapDepth+path[2].ResultHeight[2]*ceil(path[2].ResultWidth[2]/b)*path[2].ConvSize[2]*path[2].ConvDepth[1];
              int latencyP3 = path[3].ResultHeight[1]*ceil(path[3].ResultWidth[1]/c)*path[3].ConvSize[1]*InputFeatureMapDepth+path[3].ResultHeight[2]*ceil(path[3].ResultWidth[2]/c)*path[3].ConvSize[2]*path[3].ConvDepth[1];
              int latencyP4 = 0;
              int latencyP5 = path[5].ResultHeight[1]*path[5].ResultWidth[1]/e+path[5].ResultHeight[2]*ceil(path[5].ResultWidth[2]/f)*path[5].ConvSize[2]*path[5].ConvDepth[1];
              int TempMaxLatency = latencyP1;
              //cout<<"a "<<a<<endl;
              //cout<<"b "<<b<<endl;
              //cout<<"c "<<c<<endl;
              //cout<<"e "<<e<<endl;
              //cout<<"f "<<f<<endl;

              //cout<<"latencyP1 "<<latencyP1<<endl;
              //cout<<"latencyP2 "<<latencyP2<<endl;
              //cout<<"latencyP3 "<<latencyP3<<endl;
              //cout<<"latencyP5 "<<latencyP5<<endl;

              if(latencyP2>TempMaxLatency) TempMaxLatency = latencyP2;
              if(latencyP3>TempMaxLatency) TempMaxLatency = latencyP3;
              if(latencyP4>TempMaxLatency) TempMaxLatency = latencyP4;
              if(latencyP5>TempMaxLatency) TempMaxLatency = latencyP5;

              if(minilatency>TempMaxLatency) {
                minilatency = TempMaxLatency;
                righta = a;
                rightb = b;
                rightc = c;
                //rightd = d;
                righte = e;
                rightf = f;
              }
            }
          }
        }

      }
    }
  }

  float latencyP1 = path[1].ResultHeight[1]*ceil(path[1].ResultWidth[1]/righta)*path[1].ConvSize[1]*InputFeatureMapDepth;
  float latencyP2 = path[2].ResultHeight[1]*ceil(path[2].ResultWidth[1]/rightb)*path[2].ConvSize[1]*InputFeatureMapDepth+path[2].ResultHeight[2]*ceil(path[2].ResultWidth[2]/rightb)*path[2].ConvSize[2]*path[2].ConvDepth[1];
  float latencyP3 = path[3].ResultHeight[1]*ceil(path[3].ResultWidth[1]/rightc)*path[3].ConvSize[1]*InputFeatureMapDepth+path[3].ResultHeight[2]*ceil(path[3].ResultWidth[2]/rightc)*path[3].ConvSize[2]*path[3].ConvDepth[1];
  float latencyP4 = 0;
  float latencyP5 = path[5].ResultHeight[1]*path[5].ResultWidth[1]/righte+path[5].ResultHeight[2]*ceil(path[5].ResultWidth[2]/rightf)*path[5].ConvSize[2]*path[5].ConvDepth[1];
              
  float P1Percentage = latencyP1/minilatency;
  float P2Percentage = latencyP2/minilatency;
  float P3Percentage = latencyP3/minilatency;
  float P5Percentage = latencyP5/minilatency;

  cout<<"results:"<<endl;
  cout<<int(minilatency)<<endl;
  cout<<"path1 CU# "<<righta<<endl;
  cout<<"path2 CU# "<<rightb<<endl;
  cout<<"path3 CU# "<<rightc<<endl;
  //cout<<rightd<<endl;
  cout<<"path5 pooling CU# "<<righte<<endl;
  cout<<"path5 CU# "<<rightf<<endl;
  cout<<"P1Percentage "<<P1Percentage<<endl;
  cout<<"P2Percentage "<<P2Percentage<<endl;
  cout<<"P3Percentage "<<P3Percentage<<endl;
  cout<<"P5Percentage "<<P5Percentage<<endl;
  return 0;

}
/*
  float TotalRatio = ratio[1]+ratio[2]+ratio[3]+ratio[4]+ratio[5];
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
  */