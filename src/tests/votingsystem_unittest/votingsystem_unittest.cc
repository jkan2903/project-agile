/**
******************************************************************************
* @file votingsystem_unittest.cc
* @brief Unit test file for Voting System interface
* @author Janani Kannan
******************************************************************************
*/

#include "gtest/gtest.h"
#include <fstream>
#include "../../votingsystem.h"
#include "../../opl.h"
#include "../../cpl.h"
#include "../../mpo.h"
#include "../../mv.h"

class VotingSystemTest : public testing::Test {
  public:
    void SetUp() {
      exOPL = new OPL();
      exCPL = new CPL();
      exMPO = new MPO();
      exMV = new MV();
      exError = new OPL();
    }
    void TearDown() {
    }
  protected:
    std::string OPLFile = "../../../testing/opl_ballot.csv";
    std::string CPLFile = "../../../testing/cpl_ballot.csv";
    std::string MPOFile = "../../../testing/mpo_ballot.csv";
    std::string MVFile = "../../../testing/mv_ballot.csv";
    std::string errorFile = "../../../testing/notExist.csv";
    OPL* exOPL;
    CPL* exCPL;
    MPO* exMPO;
    MV* exMV;
    OPL* exError;
};


TEST_F(VotingSystemTest, defaultValueAndGetterTest){
  EXPECT_EQ("OPL", exOPL->getElectionType());
  EXPECT_EQ(-1, exOPL->getSeatCount());
  EXPECT_EQ(-1, exOPL->getBallotCount());
  EXPECT_EQ("", exOPL->getElectablesInfo());
  EXPECT_EQ("", exOPL->getBallotInfo());
  EXPECT_EQ(0, exOPL->getPartyCount());
  EXPECT_EQ(0, exOPL->getCandidateCount());
  EXPECT_TRUE(exOPL->getElectables().empty());

  EXPECT_EQ("CPL", exCPL->getElectionType());
  EXPECT_EQ(-1, exCPL->getSeatCount());
  EXPECT_EQ(-1, exCPL->getBallotCount());
  EXPECT_EQ("", exCPL->getElectablesInfo());
  EXPECT_EQ("", exCPL->getBallotInfo());
  EXPECT_EQ(0, exCPL->getPartyCount());
  EXPECT_EQ(0, exCPL->getCandidateCount());
  EXPECT_TRUE(exCPL->getElectables().empty());

  EXPECT_EQ("MPO", exMPO->getElectionType());
  EXPECT_EQ(-1, exMPO->getSeatCount());
  EXPECT_EQ(-1, exMPO->getBallotCount());
  EXPECT_EQ("", exMPO->getElectablesInfo());
  EXPECT_EQ("", exMPO->getBallotInfo());
  EXPECT_EQ(0, exMPO->getPartyCount());
  EXPECT_EQ(0, exMPO->getCandidateCount());
  EXPECT_TRUE(exMPO->getElectables().empty());

  EXPECT_EQ("MV", exMV->getElectionType());
  EXPECT_EQ(-1, exMV->getSeatCount());
  EXPECT_EQ(-1, exMV->getBallotCount());
  EXPECT_EQ("", exMV->getElectablesInfo());
  EXPECT_EQ("", exMV->getBallotInfo());
  EXPECT_EQ(0, exMV->getPartyCount());
  EXPECT_EQ(0, exMV->getCandidateCount());
  EXPECT_TRUE(exMV->getElectables().empty());
}


TEST_F(VotingSystemTest, addElectableTest){
  Candidate* C1 = new Candidate("Janani");
  exOPL->addElectable(C1);
  exCPL->addElectable(C1);
  exMPO->addElectable(C1);
  exMV->addElectable(C1);
  long unsigned int s = 1;
  EXPECT_EQ(s, exOPL->getElectables().size());
  EXPECT_EQ(s, exCPL->getElectables().size());
  EXPECT_EQ(s, exMPO->getElectables().size());
  EXPECT_EQ(s, exMV->getElectables().size());

  EXPECT_EQ(C1, exOPL->getElectables()[0]);
  EXPECT_EQ(C1, exCPL->getElectables()[0]);
  EXPECT_EQ(C1, exMPO->getElectables()[0]);
  EXPECT_EQ(C1, exMV->getElectables()[0]);

  Candidate* C2 = new Candidate("Alex");
  
  exOPL->addElectable(C2);
  exCPL->addElectable(C2);
  exMPO->addElectable(C2);
  exMV->addElectable(C2);
  s = 2;
  EXPECT_EQ(s, exOPL->getElectables().size());
  EXPECT_EQ(s, exCPL->getElectables().size());
  EXPECT_EQ(s, exMPO->getElectables().size());
  EXPECT_EQ(s, exMV->getElectables().size());

  EXPECT_EQ(C2, exOPL->getElectables()[1]);
  EXPECT_EQ(C2, exCPL->getElectables()[1]);
  EXPECT_EQ(C2, exMPO->getElectables()[1]);
  EXPECT_EQ(C2, exMV->getElectables()[1]);
}


TEST_F(VotingSystemTest, readElectionTypeTest) {
  std::ifstream file;
  
  file.open(OPLFile);
  EXPECT_NO_THROW(exOPL->readElectionType(&file));
  std::string electionType = exOPL->getElectionType();
  std::string expected_et = "OPL";
  EXPECT_EQ(electionType, expected_et);
  file.close();

  file.open(CPLFile);
  EXPECT_NO_THROW(exCPL->readElectionType(&file));
  electionType = exCPL->getElectionType();
  expected_et = "CPL";
  EXPECT_EQ(electionType, expected_et);
  file.close();

  file.open(MPOFile);
  EXPECT_NO_THROW(exMPO->readElectionType(&file));
  electionType = exMPO->getElectionType();
  expected_et = "MPO";
  EXPECT_EQ(electionType, expected_et);
  file.close();

  file.open(MVFile);
  EXPECT_NO_THROW(exMV->readElectionType(&file));
  electionType = exMV->getElectionType();
  expected_et = "MV";
  EXPECT_EQ(electionType, expected_et);
  file.close();
  
  std::stringstream buffer;
  std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());
  file.open(errorFile);
  EXPECT_EXIT(exError->readElectionType(&file), testing::ExitedWithCode(1), buffer.str());
  std::cerr.rdbuf(old);
  file.close();
}


TEST_F(VotingSystemTest, readSeatCountTest) {
  std::ifstream file;
  
  file.open(OPLFile);
  EXPECT_NO_THROW(exOPL->readElectionType(&file));
  EXPECT_NO_THROW(exOPL->readSeatCount(&file));
  int seatCount = exOPL->getSeatCount();
  int expected_et = 2;
  EXPECT_EQ(seatCount, expected_et);
  file.close();

  file.open(CPLFile);
  EXPECT_NO_THROW(exCPL->readElectionType(&file));
  EXPECT_NO_THROW(exCPL->readSeatCount(&file));
  seatCount = exCPL->getSeatCount();
  expected_et = 3;
  EXPECT_EQ(seatCount, expected_et);
  file.close();

  file.open(MPOFile);
  EXPECT_NO_THROW(exMPO->readElectionType(&file));
  EXPECT_NO_THROW(exMPO->readSeatCount(&file));
  seatCount = exMPO->getSeatCount();
  expected_et = 2;
  EXPECT_EQ(seatCount, expected_et);
  file.close();

  file.open(MVFile);
  EXPECT_NO_THROW(exMV->readElectionType(&file));
  EXPECT_NO_THROW(exMV->readSeatCount(&file));
  seatCount = exMV->getSeatCount();
  expected_et = 3;
  EXPECT_EQ(seatCount, expected_et);
  file.close();
  
  std::stringstream buffer;
  std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());
  file.open(errorFile);
  EXPECT_EXIT(exError->readSeatCount(&file), testing::ExitedWithCode(1), buffer.str());
  std::cerr.rdbuf(old);
  file.close();
}



TEST_F(VotingSystemTest, checkCSVFormatTest) {
  try {
    exOPL->checkCSVFormat();
    FAIL();
  } catch (const std::runtime_error& e) {
    EXPECT_EQ(e.what(), std::string("Incorrect file name format"));
  }

  try {
    exCPL->checkCSVFormat();
    FAIL();
  } catch (const std::runtime_error& e) {
    EXPECT_EQ(e.what(), std::string("Incorrect file name format"));
  }

  try {
    exMPO->checkCSVFormat();
    FAIL();
  } catch (const std::runtime_error& e) {
    EXPECT_EQ(e.what(), std::string("Incorrect file name format"));
  }

  EXPECT_NO_THROW(exOPL->setFname(OPLFile));
  int exitCode = exOPL->checkCSVFormat();
  int expected_out = 0;
  EXPECT_EQ(exitCode, expected_out);

  EXPECT_NO_THROW(exCPL->setFname(CPLFile));
  exitCode = exCPL->checkCSVFormat();
  expected_out = 0;
  EXPECT_EQ(exitCode, expected_out);

  EXPECT_NO_THROW(exMPO->setFname(MPOFile));
  exitCode = exMPO->checkCSVFormat();
  expected_out = 0;
  EXPECT_EQ(exitCode, expected_out);
}


TEST_F(VotingSystemTest, ResolveTieTest){
  // OPL Resolve Tie
  Candidate* C1 = new Candidate("Janani");
  Candidate* C2 = new Candidate("Rose");
  Candidate* C3 = new Candidate("Amelia");
  C1->addVotes(9);
  C2->addVotes(9);
  C3->addVotes(9);

  std::vector<Electable*> twoElectables;
  twoElectables.push_back(C1);
  twoElectables.push_back(C2);

  Electable* retCand = exOPL->resolveTie(twoElectables);
  bool resolved = false;
  for(Electable* c : twoElectables){
      if(c->getName() == retCand->getName()){
          resolved = true;
      }
  }
  EXPECT_TRUE(resolved);

  std::vector<Electable*> threeElectables;
  threeElectables.push_back(C1);
  threeElectables.push_back(C2);
  threeElectables.push_back(C3);

  retCand = exOPL->resolveTie(threeElectables);
  resolved = false;
  for(Electable* c : threeElectables){
    if(c->getName() == retCand->getName()){
        resolved = true;
    }
  }
  EXPECT_TRUE(resolved);

  // CPL Resolve Tie
  Party* P1 = new Party("Democrat");
  Party* P2 = new Party("Republican");
  Party* P3 = new Party("Independent1");
  P1->addVotes(9);
  P2->addVotes(9);
  P3->addVotes(9);

  twoElectables.clear();
  twoElectables.push_back(P1);
  twoElectables.push_back(P2);

  Electable* retParty = exCPL->resolveTie(twoElectables);
  resolved = false;
  for(Electable* p : twoElectables){
    if(p->getName() == retParty->getName()){
        resolved = true;
    }
  }
  EXPECT_TRUE(resolved);


  threeElectables.clear();
  threeElectables.push_back(P1);
  threeElectables.push_back(P2);
  threeElectables.push_back(P3);

  retParty = exCPL->resolveTie(threeElectables);
  resolved = false;
  for(Electable* p : threeElectables){
    if(p->getName() == retParty->getName()){
        resolved = true;
    }
  }
  EXPECT_TRUE(resolved);
}

TEST_F(VotingSystemTest, AddElectable2Test){
  
  // CPL
  size_t size = 0;
  EXPECT_EQ(size, exCPL->getElectables().size());
  
  Party* partyToAdd = new Party("Democrat");
  size += 1;
  int retval = exCPL->addElectable(partyToAdd);
  std::vector<Electable*> electables = exCPL->getElectables();

  EXPECT_EQ(0, retval);
  EXPECT_EQ(partyToAdd->getName(), electables[0]->getName());
  EXPECT_EQ(electables.size(), size);

  // OPL
  size = 0;
  EXPECT_EQ(size, exOPL->getElectables().size());
  
  Candidate* candidateToAdd = new Candidate("Janani");
  size += 1;
  retval = exOPL->addElectable(candidateToAdd);
  electables = exOPL->getElectables();

  EXPECT_EQ(0, retval);
  EXPECT_EQ(candidateToAdd->getName(), electables[0]->getName());
  EXPECT_EQ(electables.size(), size);

  // MPO
  size = 0;
  EXPECT_EQ(size, exMPO->getElectables().size());
  
  candidateToAdd = new Candidate("Janani");
  size += 1;
  retval = exMPO->addElectable(candidateToAdd);
  electables = exMPO->getElectables();

  EXPECT_EQ(0, retval);
  EXPECT_EQ(candidateToAdd->getName(), electables[0]->getName());
  EXPECT_EQ(electables.size(), size);


  // MV
  size = 0;
  EXPECT_EQ(size, exMV->getElectables().size());
  
  candidateToAdd = new Candidate("Janani");
  size += 1;
  retval = exMV->addElectable(candidateToAdd);
  electables = exMV->getElectables();

  EXPECT_EQ(0, retval);
  EXPECT_EQ(candidateToAdd->getName(), electables[0]->getName());
  EXPECT_EQ(electables.size(), size);

}

TEST_F(VotingSystemTest, GetElectablesTest){

  // CPL
  Party* p1 = new Party("Democrat");
  Party* p2 = new Party("Republican");
  Party* p3 = new Party("Independent1");

  EXPECT_NO_THROW(exCPL->addElectable(p1));
  EXPECT_NO_THROW(exCPL->addElectable(p2));
  EXPECT_NO_THROW(exCPL->addElectable(p3));
  std::vector<Electable*> electables = exCPL->getElectables();
  bool corrupt = false;
  for(Electable* p : electables){
    if(p->getName() != "Democrat" && p->getName() != "Republican" && p->getName() != "Independent1"){
        corrupt = true;
    }
  }
  EXPECT_FALSE(corrupt);

  // OPL
  Candidate* c1 = new Candidate("Janani");
  Candidate* c2 = new Candidate("Rose");
  Candidate* c3 = new Candidate("Amelia");

  EXPECT_NO_THROW(exOPL->addElectable(c1));
  EXPECT_NO_THROW(exOPL->addElectable(c2));
  EXPECT_NO_THROW(exOPL->addElectable(c3));
  electables = exOPL->getElectables();
  corrupt = false;
  for(Electable* c : electables){
    if(c->getName() != "Janani" && c->getName() != "Rose" && c->getName() != "Amelia"){
        corrupt = true;
    }
  }
  EXPECT_FALSE(corrupt);
}
