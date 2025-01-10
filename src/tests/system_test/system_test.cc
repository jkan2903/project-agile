#include "gtest/gtest.h"
#include "../../election.h"

class SystemTest : public testing::Test {
  public:
    void SetUp() {
      
    }
    void TearDown() {
      
    }
};

TEST_F(SystemTest, OPL) {
  testing::internal::CaptureStdout();
  std::string filename = "../../../testing/BigOPL.csv";
  EXPECT_NO_THROW(Election election(filename));
  Election election(filename);
  EXPECT_NO_THROW(election.doElection());
  EXPECT_NO_THROW(election.doAudit());
  EXPECT_NO_THROW(election.display());


  std::ifstream co("correctboplaudit.html");
  std::stringstream cob;
  cob << co.rdbuf();
  std::ifstream o("audit.html");
  std::stringstream ob;
  ob << o.rdbuf();
  EXPECT_EQ(cob.str(), ob.str());
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Winners:\n Alice Lastname - Party A\n Anna - Party A\n Alex - Party A\n Candy - Party C\n Bob - Party B\n Dave - Party D\n\nElection type: OPL\nSeat count: 6\nBallots cast: 61440\n\nAll candidates: \n Party A: 55296 votes or 90%\n  Alice Lastname: 52224 votes or 85%\n  Anna: 2048 votes or 3.33333%\n  Alex: 1024 votes or 1.66667%\n Party C: 4096 votes or 6.66667%\n  Candy: 3072 votes or 5%\n  Chris: 1024 votes or 1.66667%\n Party B: 2048 votes or 3.33333%\n  Bob: 1024 votes or 1.66667%\n  Betty CoolerlastName: 1024 votes or 1.66667%\n Party D: 0 votes or 0%\n  Dave: 0 votes or 0%\n");
}

TEST_F(SystemTest, CPL) {
  testing::internal::CaptureStdout();
  std::string filename = "../../../testing/BigCPL.csv";
  EXPECT_NO_THROW(Election election(filename));
  Election election(filename);
  EXPECT_NO_THROW(election.doElection());
  EXPECT_NO_THROW(election.doAudit());
  EXPECT_NO_THROW(election.display());

  std::ifstream co("correctbcplaudit.html");
  std::stringstream cob;
  cob << co.rdbuf();
  std::ifstream o("audit.html");
  std::stringstream ob;
  ob << o.rdbuf();
  EXPECT_EQ(cob.str(), ob.str());
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Winners:\n Alice Lastname - Party A\n Anna - Party A\n Alex - Party A\n Bob - Party B\n Chris - Party C\n Dave - Party D\n\nElection type: CPL\nSeat count: 6\nBallots cast: 26104\n\nAll candidates: \n Party A: 18936 votes or 72.5406%\n  Alice Lastname\n  Anna\n  Alex\n Party B: 4096 votes or 15.6911%\n  Bob\n  Betty\n Party C: 2048 votes or 7.84554%\n  Chris\n  Candy Middlename Coollastname\n Party D: 1024 votes or 3.92277%\n  Dave\n");
}
