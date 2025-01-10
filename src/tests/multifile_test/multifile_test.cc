#include "gtest/gtest.h"
#include "../../election.h"


class ErrorTest : public testing::Test {
  public:
    void SetUp() {
      
    }
    void TearDown() {
      
    }
};


TEST_F(ErrorTest, MultifileOPL) {
  std::string f1 = "../../../testing/OPL1.csv";
  std::string f2 = "../../../testing/OPL2.csv";
  std::string f3 = "../../../testing/OPL3.csv";

  std::vector<std::string> vf;
  vf.push_back(f1);
  vf.push_back(f2);
  vf.push_back(f3);

  EXPECT_NO_THROW(Election election(vf));
  Election election(vf);
  election.doElection();
  testing::internal::CaptureStdout();
  election.display();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "write me");
}

TEST_F(ErrorTest, MultifileCPL) {
  std::string f1 = "../../../testing/CPL1.csv";
  std::string f2 = "../../../testing/CPL2.csv";
  std::string f3 = "../../../testing/CPL3.csv";

  std::vector<std::string> vf;
  vf.push_back(f1);
  vf.push_back(f2);
  vf.push_back(f3);

  EXPECT_NO_THROW(Election election(vf));
  Election election(vf);
  election.doElection();
  testing::internal::CaptureStdout();
  election.display();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "write me");
}

TEST_F(ErrorTest, MultifileMPO) {
  std::string f1 = "../../../testing/MPO1.csv";
  std::string f2 = "../../../testing/MPO2.csv";
  std::string f3 = "../../../testing/MPO3.csv";

  std::vector<std::string> vf;
  vf.push_back(f1);
  vf.push_back(f2);
  vf.push_back(f3);

  EXPECT_NO_THROW(Election election(vf));
  Election election(vf);
  election.doElection();
  testing::internal::CaptureStdout();
  election.display();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "write me");
}

TEST_F(ErrorTest, MultifileMV) {
  std::string f1 = "../../../testing/MV1.csv";
  std::string f2 = "../../../testing/MV2.csv";
  std::string f3 = "../../../testing/MV3.csv";

  std::vector<std::string> vf;
  vf.push_back(f1);
  vf.push_back(f2);
  vf.push_back(f3);

  EXPECT_NO_THROW(Election election(vf));
  Election election(vf);
  election.doElection();
  testing::internal::CaptureStdout();
  election.display();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "write me");
}
