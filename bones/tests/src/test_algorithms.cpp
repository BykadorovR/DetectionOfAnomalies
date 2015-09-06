#include <gtest/gtest.h>
#include "Algorithms.h"

class AlgorithmsTest : public ::testing::Test {
 protected:

};

TEST_F(AlgorithmsTest, getMedianForArea) {
  static const int array[] = {16,2,77,2,41,12,55,13,12,2,5,98,4,1,0};
  vector<int> vec (array, array + sizeof(array) / sizeof(array[0]) );
  Algorithms oAlg(vec);
  EXPECT_EQ(41, oAlg.median(5,3));
  EXPECT_EQ(13, oAlg.median(5,5));
  EXPECT_EQ(16, oAlg.median(1,5));
  EXPECT_EQ(16, oAlg.median(0,3));
  EXPECT_EQ(4, oAlg.median(vec.size()-1,5));
}

TEST_F(AlgorithmsTest, getMedianForAreaOutOfArray) {
  static const int array[] = {16,2,77};
  vector<int> vec (array, array + sizeof(array) / sizeof(array[0]) );
  Algorithms oAlg(vec);
  EXPECT_EQ(-1, (oAlg.median(5,3)));
}

TEST_F(AlgorithmsTest, getMedianForAreaSizeOfArrayLessThanFilter) {
  static const int array[] = {16,2,77};
  vector<int> vec (array, array + sizeof(array) / sizeof(array[0]) );
  Algorithms oAlg(vec);
  EXPECT_EQ(-1, (oAlg.median(1,5)));
}