# multi-path layer optimizations for general CNN models

EE599 FPGA-Final Project by Jinming Lu

I write this program by using CPP, and bazel is just a platform supported by google. I use it Just because my CPP course use this.
I am familiar with the template, so I just modify one of my homework template before to do this project.
This is just a simple CPP program, nothing special. 

If you want to run this program, just go into the directory of this program and type:
bazel run src/main:main

Since this semester I am too busy, so this program is not as intelligent  as I want originally. It is a little stupid.
I make great efforts on the accuracy, but for the flexibility, I don't have enough time to make it perfect

# 1.INPUTS
At first, I want to use reading files to input data. But I ran out of my time and I am not very familiar with IO files.
So you need to input by yourself:(
  float PathNum;    //how many path numbers
  float MaxPoolPath; //do this layer include max pooling?
  float LUTresource;  //how many LUT resources do we have?
  float PEusageLUT;   //how many LUTs does a basic CU of MAC need?
  float PEusgaeDSP;   //how many DSPs does a basic CU of MAC need?
  float PoolusageLUT; //how many LUTs does a basic Comparator need?
  float DSPresource;  //how many DSP resources do we have?
  float InputFeatureMapHeight; 
  float InputFeatureMapWidth;
  float InputFeatureMapDepth;
  int DSPorLUT; // 1 means DSP is the bottleneck;0 means LUT is the bottleneck
  Path path[5]; //it includes the detailed information of paths:

  struct Path {
	float PathUnits = 0; //in most cases, inception is up to paths, and each path has up tp 5 layers. So in this program, the max size is 5x5
	float type[5] = {0};   // o is convolution, 1 is max pooling 
	float ConvSize[5] = {0}; 
	float ConvDepth[5] = {0};
	float ResultHeight[5] = {0};  //after im2col, the result matrix size
	float ResultWidth[5] = {0};
	float PE = 0;	              //how many CUs of MAC are arranged to this path?
  float DSP = 0;                  //how many DSPs of MAC are arranged to this path?
	float Comparactor = 0;        //how many Comparators are arranged to this path?
  int maxpoolingTrue = 0;         //Is max pooling on this path, max pooling can only be assigned to path[5], even there is no path[4], just leave path[4] /////empty
};

# 2.Run the program
After you finish inputs, you can run the program. Since I use Brute force to find the best performance combinations. So the running time is a little long.
Be patient.

# 3.Imperfect points:
Now it is adjust to show the results of exmaple Inception V1 of 4 path only, it can be easily modified to other hierachies.

# 4.Outputs:
The first line will tell you which is the bottleneck, DSP or LUT.
results:
2064384   //estimated latency of this multi-path layer
path1 CU# 5                    //the CU numbers assigned to each path
path2 CU# 49
path3 CU# 7
path5 pooling CU# 1
path5 CU# 3
P1Percentage 0.934524          //the percentage of each path comparing to the slowest path (which is set to 1)
P2Percentage 1
P3Percentage 0.861111
P5Percentage 0.852679

# Thank you! Happy ending of EE599!