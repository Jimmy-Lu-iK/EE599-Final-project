#include <iostream>
#include "src/lib/cpplib.h"


using namespace std;

int main() {
  // Print Hello world!
  CPPLib s;
  cout << "Q5 Answer:" << endl;

  std::cout << s.PrintIntro() << std::endl;

  cout << "Q6 Answer:" << endl;

  std::vector<int> res;
  res = s.Flatten2DVector({{1,2,3},{4,5},{7,8}});
  cout << "{";
  for (int i=0;i<res.size();i++){
    cout << res[i];
    if ( i!= res.size()-1)
    {
      cout << ", ";
    }
  }
  cout << "}" << endl;
  

  cout << "Q7 Answer:" << endl;
  
  cout << "5! = "; 
  
  std::cout << s.CalFactorial(5) << std::endl;

  //std::cout << s.Flatten2DVector({{1,2,3},{4,5},{7,8}}) << std::endl;

  return 0;
}