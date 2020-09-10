#include "cpplib.h"
#include "limits"
#include <iostream>
#include <vector>

using namespace std;
std::string CPPLib::PrintHelloWorld() { return "**** Hello World ****"; }

// Question 5 Print your self-introduction
std::string CPPLib::PrintIntro() {
    // Please fill up this function.
    
    return "****SelfIntroduction****\n"
           "name: Jinming Lu\n"
           "email: jinmingl@usc.edu\n"
           "hobby: soccer, cooking\n"
           "github username: Jimmy-Lu-iK"; 
}


// Question 6  Flatten a 2D vector
std::vector<int> CPPLib::Flatten2DVector(const std::vector<std::vector<int>> &inputs) {
   int a;
   vector<int> b={};
   std::vector<int> res = {};
   //const std::vector<std::vector<int>> inputs={{1,2},{3,4,5}};
   a = inputs.size();
   if(a==0){
	   cout << "You put an empty vector!" << endl;
	   return b;
    }
  else{
       for(int i=0; i<inputs.size(); i++){
	       for(int j=0;j<inputs[i].size();j++){
               res.push_back(inputs[i][j]);
	        }
        }
   //for(int k=0; k<res.size(); ++k){
   //std::cout << res[k] << ' ';}
   return res;
    }
 } 




// Question 7 Calculate the factorial number
long int CPPLib::CalFactorial(int N) {
    // Please fill up this function.

  long int count = 1;
  if (N < 0){
	   cout << "Please input a positive number." << endl;
	   return -1;
    }
  else if ( N == 0||N == 1){
	 return 1;
    }
  else{
	 for(int i=1; i<=N; i++){
		 count = count*i;
        }
	 return count;
    }
}