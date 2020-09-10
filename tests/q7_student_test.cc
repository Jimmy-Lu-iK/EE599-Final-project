#include "src/lib/cpplib.h"

#include <map>
#include <vector>

#include "gtest/gtest.h"

// Add your own tests in this file
TEST(Q7_Student, CalFactorial) {
  EXPECT_EQ(-1, CalFactorial(-5));
  EXPECT_EQ(1, CalFactorial(0));
  EXPECT_EQ(1, CalFactorial(1));
  EXPECT_EQ(120, CalFactorial(5));
  EXPECT_EQ(3628800, CalFactorial(10));
}