#include "src/lib/cpplib.h"

#include <map>
#include <vector>

#include "gtest/gtest.h"

// Add your own tests in this file
TEST(Q5_Student, ReturnIntro) {
  CPPLib CPPLib;
  std::string actual = cpplib..PrintIntro();
  std::string expected = "****SelfIntroduction****\n"
           "name: Jinming Lu\n"
           "email: jinmingl@usc.edu\n"
           "hobby: soccer, cooking\n"
           "github username: Jimmy-Lu-iK";
  EXPECT_EQ(actual, expected);
}