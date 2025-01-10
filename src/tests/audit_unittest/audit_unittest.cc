#include "gtest/gtest.h"
#include "../../audit.h"

class AuditTest : public testing::Test {
  public:
    void SetUp() {
      VotingSystemFactory *vsf = new VotingSystemFactory();
      this->opl = vsf->newVotingSystem("../../../testing/AuditOPLTest.csv");
      this->opl->doElection();
      this->cpl = vsf->newVotingSystem("../../../testing/AuditCPLTest.csv");
      this->opl->doElection();
      this->Bopl = vsf->newVotingSystem("../../../testing/BigOPL.csv");
      this->opl->doElection();
      this->Bcpl = vsf->newVotingSystem("../../../testing/BigCPL.csv");
      this->opl->doElection();
    }
    void TearDown() {
      
    }
  protected:
    VotingSystem *opl;
    VotingSystem *cpl;
    VotingSystem *Bopl;
    VotingSystem *Bcpl;
};

TEST_F(AuditTest, AuditOPLCreateTest) {
  EXPECT_NO_THROW(Audit a(this->opl));
}

TEST_F(AuditTest, AuditOPLWriteElectionTypeTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeElectionType(), "<p>Election type: OPL</p>\n"));
}

TEST_F(AuditTest, AuditOPLWritePartyCountTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writePartyCount(), "<p>Party count: 4</p>\n"));
}

TEST_F(AuditTest, AuditOPLWriteBallotCountTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeBallotCount(), "<p>Ballot count: 13</p>\n"));
}

TEST_F(AuditTest, AuditOPLWriteSeatCountTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeSeatCount(), "<p>Seat count: 3</p>\n"));
}

TEST_F(AuditTest, AuditOPLWritePartyTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeParty(new Party("Green")), "<p>Green - []</p>\n"));
}

TEST_F(AuditTest, AuditOPLWriteAllPartiesTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeAllParties(), "<p>Party B - [Bob, Betty CoolerlastName]</p>\n<p>Party D - [Dave]</p>\n<p>Party A - [Alice Lastname, Anna, Alex]</p>\n<p>Party C - [Chris, Candy]</p>\n"));
}

TEST_F(AuditTest, AuditOPLWriteEquationTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeEquation(), "<p><math display=\"inline\"><mfrac><mn>13</mn><mn>3</mn></mfrac><mo>=</mo><mn>4</mn></math></p>\n"));
}

TEST_F(AuditTest, AuditOPLWriteTableTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeTable(), "<style>.tb { border-collapse: collapse; width:100%; }.tb th, .tb td { padding: 5px; border: solid 1px #777; }.tb th { background-color: lightblue; }</style><table class=\"tb\"><tr><th>Parties</th><th>Votes</th><th>First Allocation of Seats</th><th>Remaining Votes</th><th>Second Allocation of Seats</th><th>Final Seat Total</th><th>% of Vote to % of Seats</th></tr><tr><td>Party B</td><td>3</td><td>0</td><td>3</td><td>1</td><td>1</td><td>23.07% to 33.33%</td></tr><tr><td>Party D</td><td>3</td><td>0</td><td>3</td><td>1</td><td>1</td><td>23.07% to 33.33%</td></tr><tr><td>Party A</td><td>6</td><td>1</td><td>2</td><td>0</td><td>1</td><td>46.15% to 33.33%</td></tr><tr><td>Party C</td><td>1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>7.692% to 0.000%</td></tr></table>\n"));
}

TEST_F(AuditTest, AuditOPLWriteWinnersTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeWinners(), "<p>Winners:</p><p>Bob - Party B got 2 votes</p><p>Dave - Party D got 3 votes</p><p>Alice Lastname - Party A got 4 votes</p>"));
}

TEST_F(AuditTest, AuditOPLWriteResultsTest) {
  Audit a(this->opl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeResults(), 0));
  std::ifstream co("correctoplaudit.html");
  std::stringstream cob;
  cob << co.rdbuf();
  std::ifstream o("audit.html");
  std::stringstream ob;
  ob << o.rdbuf();
  EXPECT_EQ(cob.str(), ob.str());
  Audit ba(this->Bopl);
  EXPECT_NO_THROW(EXPECT_EQ(ba.writeResults(), 0));
  std::ifstream bco("correctboplaudit.html");
  std::stringstream bcob;
  bcob << bco.rdbuf();
  std::ifstream bo("audit.html");
  std::stringstream bob;
  bob << bo.rdbuf();
  EXPECT_EQ(bcob.str(), bob.str());
}

TEST_F(AuditTest, AuditCPLCreateTest) {
  EXPECT_NO_THROW(Audit a(this->cpl));
}

TEST_F(AuditTest, AuditCPLWriteElectionTypeTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeElectionType(), "<p>Election type: CPL</p>\n"));
}

TEST_F(AuditTest, AuditCPLWritePartyCountTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writePartyCount(), "<p>Party count: 4</p>\n"));
}

TEST_F(AuditTest, AuditCPLWriteBallotCountTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeBallotCount(), "<p>Ballot count: 13</p>\n"));
}

TEST_F(AuditTest, AuditCPLWriteSeatCountTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeSeatCount(), "<p>Seat count: 3</p>\n"));
}

TEST_F(AuditTest, AuditCPLWritePartyTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeParty(new Party("Green")), "<p>Green - []</p>\n"));
}

TEST_F(AuditTest, AuditCPLWriteAllPartiesTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeAllParties(), "<p>Party A - [Alice Lastname, Anna, Alex]</p>\n<p>Party B - [Bob, Betty]</p>\n<p>Party C - [Chris, Candy Middlename Coollastname]</p>\n<p>Party D - [Dave]</p>\n"));
}

TEST_F(AuditTest, AuditCPLWriteEquationTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeEquation(), "<p><math display=\"inline\"><mfrac><mn>13</mn><mn>3</mn></mfrac><mo>=</mo><mn>4</mn></math></p>\n"));
}

TEST_F(AuditTest, AuditCPLWriteTableTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeTable(), "<style>.tb { border-collapse: collapse; width:100%; }.tb th, .tb td { padding: 5px; border: solid 1px #777; }.tb th { background-color: lightblue; }</style><table class=\"tb\"><tr><th>Parties</th><th>Votes</th><th>First Allocation of Seats</th><th>Remaining Votes</th><th>Second Allocation of Seats</th><th>Final Seat Total</th><th>% of Vote to % of Seats</th></tr><tr><td>Party A</td><td>7</td><td>1</td><td>3</td><td>1</td><td>2</td><td>53.84% to 66.66%</td></tr><tr><td>Party B</td><td>4</td><td>1</td><td>0</td><td>0</td><td>1</td><td>30.76% to 33.33%</td></tr><tr><td>Party C</td><td>2</td><td>0</td><td>2</td><td>0</td><td>0</td><td>15.38% to 0.000%</td></tr><tr><td>Party D</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0.000% to 0.000%</td></tr></table>\n"));
}

TEST_F(AuditTest, AuditCPLWriteWinnersTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeWinners(), "<p>Winners:</p><p>Alice Lastname - Party A</p><p>Anna - Party A</p><p>Bob - Party B</p>"));
}

TEST_F(AuditTest, AuditCPLWriteResultsTest) {
  Audit a(this->cpl);
  EXPECT_NO_THROW(EXPECT_EQ(a.writeResults(), 0));
  std::ifstream co("correctcplaudit.html");
  std::stringstream cob;
  cob << co.rdbuf();
  std::ifstream o("audit.html");
  std::stringstream ob;
  ob << o.rdbuf();
  EXPECT_EQ(cob.str(), ob.str());
  Audit ba(this->Bcpl);
  EXPECT_NO_THROW(EXPECT_EQ(ba.writeResults(), 0));
  std::ifstream bco("correctbcplaudit.html");
  std::stringstream bcob;
  bcob << bco.rdbuf();
  std::ifstream bo("audit.html");
  std::stringstream bob;
  bob << bo.rdbuf();
  EXPECT_EQ(bcob.str(), bob.str());
}
