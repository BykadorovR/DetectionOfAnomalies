#include <gtest/gtest.h>
#include "Utils.h"

class UtilsTest : public ::testing::Test {
 protected:
};

TEST_F(UtilsTest, getMinMaxIndex) {
  //TODO: Clear path to .dcm files 
  int size = 3;
  int* buffer = new int[size];
  buffer[0] = 5;
  buffer[1] = -2;
  buffer[2] = 15;
  EXPECT_EQ(1, getMinIndex(buffer, size));
  EXPECT_EQ(2, getMaxIndex(buffer, size));
}

