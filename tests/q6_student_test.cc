#include "src/lib/cpplib.h"

#include <map>
#include <vector>

#include "gtest/gtest.h"

// Add your own tests in this file
TEST(Q6_Student, Flatten2DVector) {
  EXPECT_EQ({}, Flatten2DVector({});
  EXPECT_EQ({1}, Flatten2DVector({1});
  EXPECT_EQ({1,2,3,4,5}, Flatten2DVector({{1,2,3},{4,5}});
  EXPECT_EQ({1,2,3,4,5,6,7,8}, Flatten2DVector{{1,2,3},{4,5},{6,7,8});
}