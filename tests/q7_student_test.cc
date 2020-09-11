#include "src/lib/cpplib.h"

#include <map>
#include <vector>

#include "gtest/gtest.h"

// Add your own tests in this file
TEST(Q7_Student, CalFactorial) {
CPPLib cpplib;

// Negtive Check:
  EXPECT_EQ(-1, cpplib.CalFactorial(-5));

// Zero Check:
  EXPECT_EQ(1, cpplib.CalFactorial(0));

// 1! = 1:
  EXPECT_EQ(1, cpplib.CalFactorial(1));

// 5! = 120:
  EXPECT_EQ(120, cpplib.CalFactorial(5));

// 10! = 3628800:
  EXPECT_EQ(3628800, cpplib.CalFactorial(10));


/*int in = 5;
  int out;
  int expected;
  out = cpplib.CalFactorial(in);
  expected  = 120; // 5!
  EXPECT_EQ(expected, out);*/
}