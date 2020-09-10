#include <iostream>
#include "src/lib/cpplib.h"


using namespace std;

int main() {
  // Print Hello world!
  CPPLib s;
  std::cout << s.PrintIntro() << std::endl;
  
  std::cout << s.PrintHelloWorld() << std::endl;

  std::cout << s.CalFactorial(5) << std::endl;

  std::vector<int> res;
  res = s.Flatten2DVector({{1,2,3},{4,5},{7,8}});
  for (int i=0;i<res.size();i++){
    cout << res[i];
    cout << endl;
  }

  //std::cout << s.Flatten2DVector({{1,2,3},{4,5},{7,8}}) << std::endl;

  return 0;
}