#include "gtest/gtest.h"
#include "../../election.h"

class ElectionTest : public testing::Test {
  public:
    void SetUp() {
      this->opl = "../../../testing/AuditOPLTest.csv";
      this->cpl = "../../../testing/AuditCPLTest.csv";
    }
    void TearDown() {
      
    }
  protected:
    std::string opl;
    std::string cpl;
};

TEST_F(ElectionTest, ElectionOPLCreateTest) {
  EXPECT_NO_THROW(Election a(this->opl));
}

TEST_F(ElectionTest, ElectionOPLDoElectionTest) {
  Election a(this->opl);
  EXPECT_NO_THROW(a.doElection());
}

TEST_F(ElectionTest, ElectionOPLDoAuditTest) {
  Election a(this->opl);
  a.doElection();
  EXPECT_NO_THROW(a.doAudit());
}

TEST_F(ElectionTest, ElectionOPLDisplayTest) {
  Election a(this->opl);
  a.doElection();
  testing::internal::CaptureStdout();
  EXPECT_NO_THROW(a.display());
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Winners:\n Bob - Party B\n Dave - Party D\n Alice Lastname - Party A\n\nElection type: OPL\nSeat count: 3\nBallots cast: 13\n\nAll candidates: \n Party B: 3 votes or 23.0769%\n  Bob: 2 votes or 15.3846%\n  Betty CoolerlastName: 1 votes or 7.69231%\n Party D: 3 votes or 23.0769%\n  Dave: 3 votes or 23.0769%\n Party A: 6 votes or 46.1538%\n  Alice Lastname: 4 votes or 30.7692%\n  Anna: 1 votes or 7.69231%\n  Alex: 1 votes or 7.69231%\n Party C: 1 votes or 7.69231%\n  Chris: 1 votes or 7.69231%\n  Candy: 0 votes or 0%\n");
}

TEST_F(ElectionTest, ElectionCPLCreateTest) {
  EXPECT_NO_THROW(Election a(this->cpl));
}

TEST_F(ElectionTest, ElectionCPLDoElectionTest) {
  Election a(this->cpl);
  EXPECT_NO_THROW(a.doElection());
}

TEST_F(ElectionTest, ElectionCPLDoAuditTest) {
  Election a(this->cpl);
  a.doElection();
  EXPECT_NO_THROW(a.doAudit());
}

TEST_F(ElectionTest, ElectionCPLDisplayTest) {
  Election a(this->cpl);
  a.doElection();
  testing::internal::CaptureStdout();
  EXPECT_NO_THROW(a.display());
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Winners:\n Alice Lastname - Party A\n Anna - Party A\n Bob - Party B\n\nElection type: CPL\nSeat count: 3\nBallots cast: 13\n\nAll candidates: \n Party A: 7 votes or 53.8462%\n  Alice Lastname\n  Anna\n  Alex\n Party B: 4 votes or 30.7692%\n  Bob\n  Betty\n Party C: 2 votes or 15.3846%\n  Chris\n  Candy Middlename Coollastname\n Party D: 0 votes or 0%\n  Dave\n");
}
