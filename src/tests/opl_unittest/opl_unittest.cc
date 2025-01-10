/**
******************************************************************************
 * @file opl_unittest.cc
 * @brief Unit test file for OPL class
 * @author Janani Kannan, Leo Dong
 * @bug the order of the winner list is based on the remaining votes 
 * during the calculation process, but it does not affect the correctness of
 * the programs
 * @bug processElectables() is needed before getParties is called on an 
 * OPL object
******************************************************************************
*/

#include "gtest/gtest.h"
#include "../../opl.h"
#include "../../votingsystem.h"

class OPLTest : public testing::Test {
  public:
    void SetUp() {
      exOPL = new OPL();
      exOPL->setFilenames(OPLFile);
    }
  protected:
    std::vector<std::string> OPLFile = {"../../../testing/opl_ballot.csv"};
    OPL* exOPL;
};

TEST_F(OPLTest, CreateOPLTest) {
  EXPECT_NO_THROW(OPL());
}

TEST_F(OPLTest, GetPartiesTest){
  EXPECT_NO_THROW(exOPL->getParties());

  std::vector<Party*> ActualParties = exOPL->getParties();
  int actualPartySize = ActualParties.size();
  int expectedPartySize = 0;
  EXPECT_EQ(expectedPartySize, actualPartySize);
  
	Party* expected1 = new Party("Democrat");
	Party* expected2 = new Party("Republican");
	Party* expected3 = new Party("Independent");

  std::vector<Party*> ExpectedParties;
	ExpectedParties.push_back(expected1);
	ExpectedParties.push_back(expected2);
	ExpectedParties.push_back(expected3);

  exOPL->parseFile();
  exOPL->processElectables();
  ActualParties = exOPL->getParties();
  EXPECT_EQ(ExpectedParties.size(), ActualParties.size());
  EXPECT_EQ(expected1->getName(), ActualParties[0]->getName());
  EXPECT_EQ(expected2->getName(), ActualParties[1]->getName());
  EXPECT_EQ(expected3->getName(), ActualParties[2]->getName());

}


TEST_F(OPLTest, ProcessElectablesTest){

  EXPECT_EQ(0, exOPL->getPartyCount());
  EXPECT_EQ(0, exOPL->getCandidateCount());
  EXPECT_EQ(0, (int) exOPL->getParties().size());

  exOPL->parseFile();
  exOPL->processElectables();

	Party* expectedP1 = new Party("Democrat");
	Party* expectedP2 = new Party("Republican");
	Party* expectedP3 = new Party("Independent");

  std::vector<Party*> ExpectedParties;
	ExpectedParties.push_back(expectedP1);
	ExpectedParties.push_back(expectedP2);
	ExpectedParties.push_back(expectedP3);

  std::vector<Party*> ActualParties = exOPL->getParties();

	int idx = 0;
	for(Party* p : ExpectedParties){
		EXPECT_EQ(p->getName(), ActualParties[idx]->getName());
		idx += 1;
	}

  std::vector<Electable*> ActualElectables = exOPL->getElectables();

  std::vector<Candidate*> ActualCandidates(ActualElectables.size(), NULL);
  std::transform(ActualElectables.begin(), ActualElectables.end(), 
                  ActualCandidates.begin(), [](Electable* e) { return dynamic_cast<Candidate*>(e);});

  EXPECT_EQ("Pike - Democrat", ActualCandidates[0]->toString());
  EXPECT_EQ("Lucy - Democrat", ActualCandidates[1]->toString());
  EXPECT_EQ("Beiye - Democrat", ActualCandidates[2]->toString());
  EXPECT_EQ("Etta - Republican", ActualCandidates[3]->toString());
  EXPECT_EQ("Alawa - Republican", ActualCandidates[4]->toString());
  EXPECT_EQ("Sasha - Independent", ActualCandidates[5]->toString());

	EXPECT_EQ(3, exOPL->getPartyCount());
  EXPECT_EQ(6, exOPL->getCandidateCount());
}

// Democrat, Pike: 2
// Democrat, Lucy: 1
// Democrat, Beiye: 0
// Republican, Etta: 2
// Republican, Alawa: 2
// Independent1, Sasha: 2

TEST_F(OPLTest, CountVotesTest){

  int actual_votes = exOPL->totalVotes;
  EXPECT_EQ(0, actual_votes);
  EXPECT_NO_THROW(exOPL->countVotes());
  actual_votes = exOPL->totalVotes;
  EXPECT_EQ(0, actual_votes);

  exOPL->parseFile();
  EXPECT_NO_THROW(exOPL->processElectables());
  EXPECT_NO_THROW(exOPL->countVotes());

  std::vector<Electable*> ActualElectables = exOPL->getElectables();

  std::vector<Candidate*> ActualCandidates(ActualElectables.size(), NULL);
  std::transform(ActualElectables.begin(), ActualElectables.end(), 
                  ActualCandidates.begin(), [](Electable* e) { return dynamic_cast<Candidate*>(e);});

  std::map<std::string, int> ActualVotes;
  ActualVotes["Pike"] = 1;
  ActualVotes["Lucy"] = 2;
  ActualVotes["Beiye"] = 0;
  ActualVotes["Etta"] = 1;
  ActualVotes["Alawa"] = 3;
  ActualVotes["Sasha"] = 2;

  for(Candidate* c : ActualCandidates){
      EXPECT_EQ(ActualVotes[c->getName()], c->getVotes());
  }

}

TEST_F(OPLTest, CountVotesSortTest){
  exOPL->parseFile();
  EXPECT_NO_THROW(exOPL->processElectables());
  std::vector<Party*> ActualParties = exOPL->getParties();

  testing::internal::CaptureStdout();
  for(Party* p : ActualParties){
    std::cout << p->toString() << std::endl;
  }
  std::string output1 = testing::internal::GetCapturedStdout();

  std::string expected_output1 = 
    "Democrat - [Pike, Lucy, Beiye]\n"
    "Republican - [Etta, Alawa]\n"
    "Independent - [Sasha]\n";
  EXPECT_EQ(expected_output1, output1);

  EXPECT_NO_THROW(exOPL->countVotes());

  ActualParties = exOPL->getParties();
  EXPECT_EQ(3, ActualParties[0]->getVotes());
  EXPECT_EQ(4, ActualParties[1]->getVotes());
  EXPECT_EQ(2, ActualParties[2]->getVotes());

  testing::internal::CaptureStdout();
  for(Party* p : ActualParties){
    std::cout << p->toString() << std::endl;
  }
  output1 = testing::internal::GetCapturedStdout();

  expected_output1 = 
    "Democrat - [Lucy, Pike, Beiye]\n"
    "Republican - [Alawa, Etta]\n"
    "Independent - [Sasha]\n";
  EXPECT_EQ(expected_output1, output1);
}



TEST_F(OPLTest, CalculateResultsFirstAllocationTest){
  exOPL->parseFile();
  EXPECT_NO_THROW(exOPL->processElectables());
  EXPECT_NO_THROW(exOPL->countVotes());
  std::vector<Party*> ActualParties = exOPL->getParties();
  testing::internal::CaptureStdout();
  for(Party* p : ActualParties){
    std::cout << p->toString() + " - " + std::to_string(p->getRemainder()) << std::endl;
  }
  std::string output = testing::internal::GetCapturedStdout();
  std::string expected_output = 
    "Democrat - [Lucy, Pike, Beiye] - 0\n"
    "Republican - [Alawa, Etta] - 0\n"
    "Independent - [Sasha] - 0\n";
  EXPECT_EQ(expected_output, output);

  EXPECT_NO_THROW(exOPL->calculateResults());

  ActualParties = exOPL->getParties();
  EXPECT_EQ(0, ActualParties[0]->getFirstAllocation());
  EXPECT_EQ(0, ActualParties[1]->getFirstAllocation());
  EXPECT_EQ(1, ActualParties[2]->getFirstAllocation());

  testing::internal::CaptureStdout();
  for(Party* p : ActualParties){
    std::cout << p->toString() + " - " + std::to_string(p->getRemainder()) << std::endl;
  }
  output = testing::internal::GetCapturedStdout();

  expected_output = 
    "Democrat - [Lucy, Pike, Beiye] - 3\n"
    "Independent - [Sasha] - 2\n"
    "Republican - [Alawa, Etta] - 0\n";
  EXPECT_EQ(expected_output, output);
}

TEST_F(OPLTest, CalculateResultsSecondAllocationTest){
  exOPL->parseFile();
  EXPECT_NO_THROW(exOPL->processElectables());
  EXPECT_NO_THROW(exOPL->countVotes());
  std::vector<Party*> ActualParties = exOPL->getParties();
  EXPECT_EQ(0, ActualParties[0]->getSecondAllocation());
  EXPECT_EQ(0, ActualParties[1]->getSecondAllocation());
  EXPECT_EQ(0, ActualParties[2]->getSecondAllocation());
  EXPECT_NO_THROW(exOPL->calculateResults());

  ActualParties = exOPL->getParties();
  EXPECT_EQ(1, ActualParties[0]->getSecondAllocation());
  EXPECT_EQ(0, ActualParties[1]->getSecondAllocation());
  EXPECT_EQ(0, ActualParties[2]->getSecondAllocation());
}


TEST_F(OPLTest, CalculateResultsTotalSeatsTest){
  exOPL->parseFile();
  EXPECT_NO_THROW(exOPL->processElectables());
  EXPECT_NO_THROW(exOPL->countVotes());
  std::vector<Party*> ActualParties = exOPL->getParties();
  testing::internal::CaptureStdout();
  for(Party* p : ActualParties){
    std::cout << p->toString() + " - " + std::to_string(p->getSeats()) << std::endl;
  }
  std::string output = testing::internal::GetCapturedStdout();
  std::string expected_output = 
    "Democrat - [Lucy, Pike, Beiye] - 0\n"
    "Republican - [Alawa, Etta] - 0\n"
    "Independent - [Sasha] - 0\n";
  EXPECT_EQ(expected_output, output);

  EXPECT_NO_THROW(exOPL->calculateResults());

  ActualParties = exOPL->getParties();
  testing::internal::CaptureStdout();
  for(Party* p : ActualParties){
    std::cout << p->toString() + " - " + std::to_string(p->getSeats()) << std::endl;
  }
  output = testing::internal::GetCapturedStdout();
  expected_output = 
    "Democrat - [Lucy, Pike, Beiye] - 1\n"
    "Independent - [Sasha] - 0\n"
    "Republican - [Alawa, Etta] - 1\n";
  EXPECT_EQ(expected_output, output);
}

TEST_F(OPLTest, GetWinnersTest){
  exOPL->parseFile();
  EXPECT_NO_THROW(exOPL->processElectables());
  EXPECT_NO_THROW(exOPL->countVotes());
  EXPECT_NO_THROW(exOPL->calculateResults());
  EXPECT_NO_THROW(exOPL->getWinners());
  std::vector<Candidate*> ActualWinners = exOPL->getWinners();
  EXPECT_EQ(2, (int) ActualWinners.size());

  std::vector<Candidate*> ExpectedWinners;
  Candidate* expectedC1 = new Candidate("Lucy");
  Party* expectedP1 = new Party("Democrat");
  expectedC1->setParty(expectedP1);
  Candidate* expectedC2 = new Candidate("Alawa");
  Party* expectedP2 = new Party("Republican");
  expectedC2->setParty(expectedP2);

  ExpectedWinners.push_back(expectedC1);
  ExpectedWinners.push_back(expectedC2);

  int idx = 0;
	for(Candidate* e : ExpectedWinners){
		EXPECT_EQ(e->toString(), ActualWinners[idx]->toString());
		idx += 1;
	}
}