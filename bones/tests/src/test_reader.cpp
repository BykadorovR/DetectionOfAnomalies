#include <gtest/gtest.h>
#include "Reader.h"

class ReaderTest : public ::testing::Test {
 protected:
   Reader* reader;
};

TEST_F(ReaderTest, readFromUINT16) {
  //TODO: Clear path to .dcm files
  reader = new Reader("../tests/dcm/IM000000.dcm");
  char* buffer = reader->readFile();    
  reader->initializeHUValuesFromUInt16(buffer);    
  EXPECT_EQ(20, reader->getHU(229, 315));
  EXPECT_EQ(-178, reader->getHU(337, 300));
  EXPECT_EQ(-24, reader->getHU(327, 284));
  EXPECT_EQ(-13, reader->getHU(260, 5));
  EXPECT_EQ(-296, reader->getHU(412, 353));
}

TEST_F(ReaderTest, readWindowWidthAndCenter) {
  //TODO: Clear path to .dcm files
  reader = new Reader("../tests/dcm/IM000000.dcm");
  char* buffer = reader->readFile();    
  reader->initializeHUValuesFromUInt16(buffer);    
  EXPECT_EQ(1500, reader->getWindowWidth());
  EXPECT_EQ(50, reader->getWindowCenter());
}