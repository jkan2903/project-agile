/**
******************************************************************************
 * @file cpl_unittest.cc
 * @brief Unit test file for CPL class
 * @author Leo Dong
 * @bug electables are not populated in countVotes() method, 
 *  processElectables()is needed.
 * @note CPL unit test is not an automated test. To compile the 
 * cpl_unittest.cc source file, please manually uncomment lines 35 and 37 in 
 * cpl.h and lines 12 and 89 in votingsystem.h for the purpose of  testing 
 * protected class variables.
******************************************************************************
*/

#include "gtest/gtest.h"
#include "../../cpl.h"
#include "../../votingsystem.h"

class CPLTest : public testing::Test {
  public:
    void SetUp() {
      exCPL = new CPL();
      exCPL->setFilenames(CPLFile);
    }
  void TearDown() { }
  protected:
    std::vector<std::string> CPLFile = {"../../../testing/cpl_ballot.csv"};
    CPL* exCPL;
};


TEST_F(CPLTest, CreateCPLTest) {
  EXPECT_NO_THROW(CPL());
}


TEST_F(CPLTest, getPartiesTest) {
  EXPECT_NO_THROW(exCPL->getParties());

  std::vector<Party*> ActualParties = exCPL->getParties();
  int actualPartySize = ActualParties.size();
  int expectedPartySize = 0;
  EXPECT_EQ(expectedPartySize, actualPartySize);

	Party* expectedP1 = new Party("Democratic");
	Party* expectedP2 = new Party("Republican");

  exCPL->addElectable(expectedP1);
  exCPL->addElectable(expectedP2);
  ActualParties = exCPL->getParties();
  actualPartySize = ActualParties.size();
  expectedPartySize = 2;
  EXPECT_EQ(expectedPartySize, actualPartySize);
  EXPECT_EQ(expectedP1->getName(), ActualParties[0]->getName());
  EXPECT_EQ(expectedP2->getName(), ActualParties[1]->getName());

  Party* expectedP3 = new Party("Democratic2");
  Party* expectedP4 = new Party("Republican2");
  exCPL->addElectable(expectedP3);
  exCPL->addElectable(expectedP4);

  ActualParties = exCPL->getParties();
  actualPartySize = ActualParties.size();
  expectedPartySize = 4;
  EXPECT_EQ(expectedPartySize, actualPartySize);
  EXPECT_EQ(expectedP1->getName(), ActualParties[0]->getName());
}


TEST_F(CPLTest, ProcessElectablesTest){
  EXPECT_EQ(0, exCPL->getPartyCount());
  EXPECT_EQ(0, exCPL->getCandidateCount());
  EXPECT_EQ(0, (int) exCPL->getParties().size());

  exCPL->parseFile();
  EXPECT_NO_THROW(exCPL->processElectables());
	Party* expectedP1 = new Party("Democratic");
	Party* expectedP2 = new Party("Republican");
	Party* expectedP3 = new Party("New Wave");
	Party* expectedP4 = new Party("Reform");
	Party* expectedP5 = new Party("Green");
	Party* expectedP6 = new Party("Independent");

  std::vector<Party*> ExpectedParties;
	ExpectedParties.push_back(expectedP1);
	ExpectedParties.push_back(expectedP2);
	ExpectedParties.push_back(expectedP3);
	ExpectedParties.push_back(expectedP4);
	ExpectedParties.push_back(expectedP5);
	ExpectedParties.push_back(expectedP6);

  std::vector<Party*> ActualParties = exCPL->getParties();

	int idx = 0;
	for(Party* p : ExpectedParties){
		EXPECT_EQ(p->getName(), ActualParties[idx]->getName());
		idx += 1;
	}

  std::vector<Candidate*> ActualCandidates = ActualParties[0]->getCandidates();
	EXPECT_EQ(3, (int) ActualCandidates.size());
	EXPECT_EQ("Joe - Democratic", ActualCandidates[0]->toString());
	EXPECT_EQ("Sally - Democratic", ActualCandidates[1]->toString());
	EXPECT_EQ("Ahmed - Democratic", ActualCandidates[2]->toString());

  ActualCandidates = ActualParties[2]->getCandidates();
	EXPECT_EQ(1, (int) ActualCandidates.size());
	EXPECT_EQ("Sarah - New Wave", ActualCandidates[0]->toString());

  ActualCandidates = ActualParties[3]->getCandidates();
	EXPECT_EQ(2, (int) ActualCandidates.size());
	EXPECT_EQ("Xinyue - Reform", ActualCandidates[0]->toString());
	EXPECT_EQ("Nikita - Reform", ActualCandidates[1]->toString());

	EXPECT_EQ(6, exCPL->getPartyCount());
  EXPECT_EQ(11, exCPL->getCandidateCount());
}


TEST_F(CPLTest, countVotesTest) {
  int actual_votes = exCPL->totalVotes;
  EXPECT_EQ(0, actual_votes);
  EXPECT_NO_THROW(exCPL->countVotes());
  actual_votes = exCPL->totalVotes;
  EXPECT_EQ(0, actual_votes);

  exCPL->parseFile();
  exCPL->processElectables();
  EXPECT_NO_THROW(exCPL->countVotes());
  actual_votes = exCPL->totalVotes;
  EXPECT_EQ(9, actual_votes);

  std::vector<Electable*> ActualElectables = exCPL->getElectables();
  std::vector<Party*> ActualParties(ActualElectables.size(), NULL);
  std::transform(ActualElectables.begin(), ActualElectables.end(), 
                  ActualParties.begin(), [](Electable* e) { return dynamic_cast<Party*>(e);});
  std::map<std::string, int> ActualVotes;
  ActualVotes["Democratic"] = 3;
  ActualVotes["Republican"] = 2;
  ActualVotes["New Wave"] = 0;
  ActualVotes["Reform"] = 2;
  ActualVotes["Green"] = 1;
  ActualVotes["Independent"] = 1;

  for(Party* p : ActualParties){
    EXPECT_EQ(ActualVotes[p->getName()], p->getVotes());
  }
}

TEST_F(CPLTest, CalculateResultsSortTest){
  exCPL->parseFile();
  EXPECT_NO_THROW(exCPL->processElectables());
  EXPECT_NO_THROW(exCPL->countVotes());
  std::vector<Electable*> ActualElectables = exCPL->getElectables();

  testing::internal::CaptureStdout();
  for(Electable* e : ActualElectables){
    std::cout << e->toString() << std::endl;
  }
  std::string output1 = testing::internal::GetCapturedStdout();

  std::string expected_output1 = 
    "Democratic - [Joe, Sally, Ahmed]\n"
    "Republican - [Allen, Nikki, Taihui]\n"
    "New Wave - [Sarah]\n"
    "Reform - [Xinyue, Nikita]\n"
    "Green - [Bethany]\n"
    "Independent - [Mike]\n";
  EXPECT_EQ(expected_output1, output1);

  EXPECT_NO_THROW(exCPL->calculateResults());

  ActualElectables = exCPL->getElectables();

  testing::internal::CaptureStdout();
  for(Electable* e : ActualElectables){
    std::cout << e->toString() << std::endl;
  }
  output1 = testing::internal::GetCapturedStdout();

  expected_output1 = 
    "Democratic - [Joe, Sally, Ahmed]\n"
    "Republican - [Allen, Nikki, Taihui]\n"
    "Reform - [Xinyue, Nikita]\n"
    "Green - [Bethany]\n"
    "Independent - [Mike]\n"
    "New Wave - [Sarah]\n";
  EXPECT_EQ(expected_output1, output1);
}


TEST_F(CPLTest, CalculateResultsFirstAllocationTest){
  exCPL->parseFile();
  EXPECT_NO_THROW(exCPL->processElectables());
  EXPECT_NO_THROW(exCPL->countVotes());
  std::vector<Electable*> ActualElectables = exCPL->getElectables();
  testing::internal::CaptureStdout();
  for(Electable* e : ActualElectables){
    std::cout << e->toString() + " - " + std::to_string(e->getFirstAllocation()) << std::endl;
  }
  std::string output = testing::internal::GetCapturedStdout();
  std::string expected_output = 
    "Democratic - [Joe, Sally, Ahmed] - 0\n"
    "Republican - [Allen, Nikki, Taihui] - 0\n"
    "New Wave - [Sarah] - 0\n"
    "Reform - [Xinyue, Nikita] - 0\n"
    "Green - [Bethany] - 0\n"
    "Independent - [Mike] - 0\n";
  EXPECT_EQ(expected_output, output);

  EXPECT_NO_THROW(exCPL->calculateResults());

  ActualElectables = exCPL->getElectables();
  testing::internal::CaptureStdout();
  for(Electable* e : ActualElectables){
    std::cout << e->toString() + " - " + std::to_string(e->getFirstAllocation()) << std::endl;
  }
  output = testing::internal::GetCapturedStdout();

  expected_output = 
    "Democratic - [Joe, Sally, Ahmed] - 1\n"
    "Republican - [Allen, Nikki, Taihui] - 0\n"
    "Reform - [Xinyue, Nikita] - 0\n"
    "Green - [Bethany] - 0\n"
    "Independent - [Mike] - 0\n"
    "New Wave - [Sarah] - 0\n";
  EXPECT_EQ(expected_output, output);
}


TEST_F(CPLTest, CalculateResultsSecondAllocationTest){
  exCPL->parseFile();
  EXPECT_NO_THROW(exCPL->processElectables());
  EXPECT_NO_THROW(exCPL->countVotes());
  std::vector<Electable*> ActualElectables = exCPL->getElectables();
  testing::internal::CaptureStdout();
  for(Electable* e : ActualElectables){
    std::cout << e->toString() + " - " + std::to_string(e->getSecondAllocation()) << std::endl;
  }
  std::string output = testing::internal::GetCapturedStdout();
  std::string expected_output = 
    "Democratic - [Joe, Sally, Ahmed] - 0\n"
    "Republican - [Allen, Nikki, Taihui] - 0\n"
    "New Wave - [Sarah] - 0\n"
    "Reform - [Xinyue, Nikita] - 0\n"
    "Green - [Bethany] - 0\n"
    "Independent - [Mike] - 0\n";
  EXPECT_EQ(expected_output, output);

  EXPECT_NO_THROW(exCPL->calculateResults());

  ActualElectables = exCPL->getElectables();
  testing::internal::CaptureStdout();
  for(Electable* e : ActualElectables){
    std::cout << e->toString() + " - " + std::to_string(e->getSecondAllocation()) << std::endl;
  }
  output = testing::internal::GetCapturedStdout();

  expected_output = 
    "Democratic - [Joe, Sally, Ahmed] - 0\n"
    "Republican - [Allen, Nikki, Taihui] - 1\n"
    "Reform - [Xinyue, Nikita] - 1\n"
    "Green - [Bethany] - 0\n"
    "Independent - [Mike] - 0\n"
    "New Wave - [Sarah] - 0\n";
  EXPECT_EQ(expected_output, output);
}


TEST_F(CPLTest, CalculateResultsTotalSeatsTest){
  exCPL->parseFile();
  EXPECT_NO_THROW(exCPL->processElectables());
  EXPECT_NO_THROW(exCPL->countVotes());
  std::vector<Party*> ActualParties = exCPL->getParties();
  testing::internal::CaptureStdout();
  for(Party* p : ActualParties){
    std::cout << p->getName() + " - " + std::to_string(p->getSeats()) << std::endl;
  }
  std::string output = testing::internal::GetCapturedStdout();
  std::string expected_output = 
    "Democratic - 0\n"
    "Republican - 0\n"
    "New Wave - 0\n"
    "Reform - 0\n"
    "Green - 0\n"
    "Independent - 0\n";
  EXPECT_EQ(expected_output, output);

  EXPECT_NO_THROW(exCPL->calculateResults());

  ActualParties = exCPL->getParties();
  testing::internal::CaptureStdout();
  for(Party* p : ActualParties){
    std::cout << p->getName() + " - " + std::to_string(p->getSeats()) << std::endl;
  }
  output = testing::internal::GetCapturedStdout();
  expected_output = 
    "Democratic - 1\n"
    "Republican - 1\n"
    "Reform - 1\n"
    "Green - 0\n"
    "Independent - 0\n"
    "New Wave - 0\n";
  EXPECT_EQ(expected_output, output);
}

TEST_F(CPLTest, GetWinnersTest){
  exCPL->parseFile();
  EXPECT_NO_THROW(exCPL->processElectables());
  EXPECT_NO_THROW(exCPL->countVotes());
  EXPECT_NO_THROW(exCPL->calculateResults());
  EXPECT_NO_THROW(exCPL->getWinners());
  std::vector<Candidate*> ActualWinners = exCPL->getWinners();
  EXPECT_EQ(3, (int) ActualWinners.size());

  std::vector<Candidate*> ExpectedWinners;
  Candidate* expectedC1 = new Candidate("Joe");
  Party* expectedP1 = new Party("Democratic");
  expectedC1->setParty(expectedP1);
  Candidate* expectedC2 = new Candidate("Allen");
  Party* expectedP2 = new Party("Republican");
  expectedC2->setParty(expectedP2);
  Candidate* expectedC3 = new Candidate("Xinyue");
  Party* expectedP3 = new Party("Reform");
  expectedC3->setParty(expectedP3);

  ExpectedWinners.push_back(expectedC1);
  ExpectedWinners.push_back(expectedC2);
  ExpectedWinners.push_back(expectedC3);

  int idx = 0;
	for(Candidate* e : ExpectedWinners){
		EXPECT_EQ(e->toString(), ActualWinners[idx]->toString());
		idx += 1;
	}
}