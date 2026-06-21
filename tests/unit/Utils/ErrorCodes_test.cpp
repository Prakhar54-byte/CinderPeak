#include "StorageEngine/ErrorCodes.hpp"
#include <gtest/gtest.h>
#include <sstream>

using namespace CinderPeak;

TEST(PeakStatusTest, EqualityOperators) {
  PeakStatus ok1 = PeakStatus::OK();
  PeakStatus ok2 = PeakStatus::OK();
  PeakStatus notFound1 = PeakStatus::NotFound("Not Found 1");
  PeakStatus notFound2 = PeakStatus::NotFound("Not Found 2");
  PeakStatus edgeNotFound = PeakStatus::EdgeNotFound();

  EXPECT_EQ(ok1, ok2);
  EXPECT_EQ(notFound1, notFound2);
  EXPECT_NE(ok1, notFound1);
  EXPECT_NE(notFound1, edgeNotFound);
}

TEST(PeakStatusTest, StreamOperator) {
  PeakStatus status = PeakStatus::VertexNotFound("Test Error Message");
  std::stringstream ss;
  ss << status;
  EXPECT_TRUE(ss.str().find("Test Error Message") != std::string::npos);
}
