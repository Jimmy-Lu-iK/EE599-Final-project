#include "src/lib/cpplib.h"

#include <map>
#include <vector>
#include <iostream>
#include "gtest/gtest.h"
using namespace std;
// Add your own tests in this file
TEST(Q6_Student, Flatten2DVector) {
  CPPLib cpplib;
  std::vector<int> in;
  std::vector<int> expected;
  std::vector<int> out;

// Check empty
// in ={};
  out = cpplib.Flatten2DVector({});
  expected = {};
  EXPECT_EQ(expected, out);

// array of 1 element
// in ={1};
  out = cpplib.Flatten2DVector({{1}});
  expected = {1};
  EXPECT_EQ(expected, out);

// array of 1 vector
// in ={1,2,3};
  out = cpplib.Flatten2DVector({{1,2,3}});
  expected = {1,2,3};
  EXPECT_EQ(expected, out);

// array of 2 vectors
// in ={{1,2,3},{4,5}};
  out = cpplib.Flatten2DVector({{1,2,3},{4,5}});
  expected = {1,2,3,4,5};
  EXPECT_EQ(expected, out);

// array of 3 vectors
//in ={{1,2,3},{4,5},{6,7,8}};
  out = cpplib.Flatten2DVector({{1,2,3},{4,5},{6,7,8}});
  expected = {1,2,3,4,5,6,7,8};
  EXPECT_EQ(expected, out);

// array of 3 vectors and one empty vector
//in ={{1,2,3},{4,5},{},{6,7,8}};
  out = cpplib.Flatten2DVector({{1,2,3},{4,5},{},{6,7,8}});
  expected = {1,2,3,4,5,6,7,8};
  EXPECT_EQ(expected, out);

// Check Repetitive elements in different vectors
//in ={{1,2,3,4},{4,5,6},{6,7,8}};
  out = cpplib.Flatten2DVector({{1,2,3,4},{4,5,6},{6,7,8}});
  expected = {1,2,3,4,4,5,6,6,7,8};
  EXPECT_EQ(expected, out);

// wrong tries  
  /*CPPLib cpplib;
  EXPECT_EQ({}, cpplib.Flatten2DVector({{}});
  EXPECT_EQ({1}, cpplib.Flatten2DVector({{1}});
  EXPECT_EQ({1,2,3,4,5}, cpplib.Flatten2DVector({{{1,2,3},{4,5}});
  EXPECT_EQ({1,2,3,4,5,6,7,8}, cpplib.Flatten2DVector({{{1,2,3},{4,5},{6,7,8}});*/

   // Check empty
  /*const std::vector<std::vector<int>> in = {{1,2,3},{4,5}};
  out = cpplib.Flatten2DVector(in);
  expected = {1,2,3,4,5};
  EXPECT_EQ(expected, out);
*/
}