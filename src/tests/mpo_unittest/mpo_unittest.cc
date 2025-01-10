/**
******************************************************************************
 * @file MPO_unittest.cc
 * @brief Unit test file for MPO class
 * @author Janani Kannan, Leo Dong
 * @bug the order of the winner list is based on the remaining votes 
 * during the calculation process, but it does not affect the correctness of
 * the programs
 * @bug processElectables() is needed before getParties is called on an 
 * MPO object
******************************************************************************
*/

#include "gtest/gtest.h"
#include "../../mpo.h"
#include "../../votingsystem.h"

class MPOTest : public testing::Test {
  public:
    void SetUp() {
      // exMPOData = RawData(MPOFile);
      // exMPOData.parseFile();

      exMPO = new MPO();
      exMPO->setFilenames(MPOFile);
      // exMPO->setBallotData(exMPOData);
    }
  protected:
    std::vector<std::string> MPOFile = {"../../../testing/mpo_ballot.csv"};
    MPO* exMPO;
    // RawData exMPOData;
};

TEST_F(MPOTest, CreateMPOTest) {
  EXPECT_NO_THROW(MPO());
}

TEST_F(MPOTest, GetPartiesTest){
  EXPECT_NO_THROW(exMPO->getParties());

  // exMPO->processElectables();
  std::vector<Party*> ActualParties = exMPO->getParties();
  int actualPartySize = ActualParties.size();
  int expectedPartySize = 0;
  EXPECT_EQ(expectedPartySize, actualPartySize);
  
	Party* expected1 = new Party("D");
	Party* expected2 = new Party("R");
	Party* expected3 = new Party("I");

  std::vector<Party*> ExpectedParties;
	ExpectedParties.push_back(expected1);
	ExpectedParties.push_back(expected2);
	ExpectedParties.push_back(expected3);

  exMPO->parseFile();
  exMPO->processElectables();
  ActualParties = exMPO->getParties();
  // EXPECT_EQ(exMPO->getElectablesInfo(), "a");
  EXPECT_EQ(ExpectedParties.size(), ActualParties.size());
  // EXPECT_EQ(expected1->getName(), ActualParties[0]->getName());
  // EXPECT_EQ(expected2->getName(), ActualParties[1]->getName());
  // EXPECT_EQ(expected3->getName(), ActualParties[2]->getName());
}


// // TEST_F(MPOTest, ProcessElectablesTest){

// //   EXPECT_EQ(0, exMPO->getPartyCount());
// //   EXPECT_EQ(0, exMPO->getCandidateCount());
// //   EXPECT_EQ(0, (int) exMPO->getParties().size());

//   // exMPO->parseFile();
//   // exMPO->processElectables();

// // 	Party* expectedP1 = new Party("Democrat");
// // 	Party* expectedP2 = new Party("Republican");
// // 	Party* expectedP3 = new Party("Independent");

// //   std::vector<Party*> ExpectedParties;
// // 	ExpectedParties.push_back(expectedP1);
// // 	ExpectedParties.push_back(expectedP2);
// // 	ExpectedParties.push_back(expectedP3);

// //   std::vector<Party*> ActualParties = exMPO->getParties();

// // 	int idx = 0;
// // 	for(Party* p : ExpectedParties){
// // 		EXPECT_EQ(p->getName(), ActualParties[idx]->getName());
// // 		idx += 1;
// // 	}

// //   std::vector<Electable*> ActualElectables = exMPO->getElectables();

// //   std::vector<Candidate*> ActualCandidates(ActualElectables.size(), NULL);
// //   std::transform(ActualElectables.begin(), ActualElectables.end(), 
// //                   ActualCandidates.begin(), [](Electable* e) { return dynamic_cast<Candidate*>(e);});

// //   EXPECT_EQ("Pike - Democrat", ActualCandidates[0]->toString());
// //   EXPECT_EQ("Lucy - Democrat", ActualCandidates[1]->toString());
// //   EXPECT_EQ("Beiye - Democrat", ActualCandidates[2]->toString());
// //   EXPECT_EQ("Etta - Republican", ActualCandidates[3]->toString());
// //   EXPECT_EQ("Alawa - Republican", ActualCandidates[4]->toString());
// //   EXPECT_EQ("Sasha - Independent", ActualCandidates[5]->toString());

// // 	EXPECT_EQ(3, exMPO->getPartyCount());
// //   EXPECT_EQ(6, exMPO->getCandidateCount());
// // }

// // // Democrat, Pike: 2
// // // Democrat, Lucy: 1
// // // Democrat, Beiye: 0
// // // Republican, Etta: 2
// // // Republican, Alawa: 2
// // // Independent1, Sasha: 2

// // TEST_F(MPOTest, CountVotesTest){

// //   int actual_votes = exMPO->totalVotes;
// //   EXPECT_EQ(0, actual_votes);
// //   EXPECT_NO_THROW(exMPO->countVotes());
// //   actual_votes = exMPO->totalVotes;
// //   EXPECT_EQ(0, actual_votes);

//   exMPO->parseFile();
//   EXPECT_NO_THROW(exMPO->processElectables());
//   EXPECT_NO_THROW(exMPO->countVotes());

// //   std::vector<Electable*> ActualElectables = exMPO->getElectables();

// //   std::vector<Candidate*> ActualCandidates(ActualElectables.size(), NULL);
// //   std::transform(ActualElectables.begin(), ActualElectables.end(), 
// //                   ActualCandidates.begin(), [](Electable* e) { return dynamic_cast<Candidate*>(e);});

// //   std::map<std::string, int> ActualVotes;
// //   ActualVotes["Pike"] = 1;
// //   ActualVotes["Lucy"] = 2;
// //   ActualVotes["Beiye"] = 0;
// //   ActualVotes["Etta"] = 1;
// //   ActualVotes["Alawa"] = 3;
// //   ActualVotes["Sasha"] = 2;

// //   for(Candidate* c : ActualCandidates){
// //       EXPECT_EQ(ActualVotes[c->getName()], c->getVotes());
// //   }

// // }

// TEST_F(MPOTest, CountVotesSortTest){
//   exMPO->parseFile();
//   EXPECT_NO_THROW(exMPO->processElectables());
//   std::vector<Party*> ActualParties = exMPO->getParties();

// //   testing::internal::CaptureStdout();
// //   for(Party* p : ActualParties){
// //     std::cout << p->toString() << std::endl;
// //   }
// //   std::string output1 = testing::internal::GetCapturedStdout();

// //   std::string expected_output1 = 
// //     "Democrat - [Pike, Lucy, Beiye]\n"
// //     "Republican - [Etta, Alawa]\n"
// //     "Independent - [Sasha]\n";
// //   EXPECT_EQ(expected_output1, output1);

// //   EXPECT_NO_THROW(exMPO->countVotes());

// //   ActualParties = exMPO->getParties();
// //   EXPECT_EQ(3, ActualParties[0]->getVotes());
// //   EXPECT_EQ(4, ActualParties[1]->getVotes());
// //   EXPECT_EQ(2, ActualParties[2]->getVotes());

// //   testing::internal::CaptureStdout();
// //   for(Party* p : ActualParties){
// //     std::cout << p->toString() << std::endl;
// //   }
// //   output1 = testing::internal::GetCapturedStdout();

// //   expected_output1 = 
// //     "Democrat - [Lucy, Pike, Beiye]\n"
// //     "Republican - [Alawa, Etta]\n"
// //     "Independent - [Sasha]\n";
// //   EXPECT_EQ(expected_output1, output1);
// // }



// TEST_F(MPOTest, CalculateResultsFirstAllocationTest){
//   exMPO->parseFile();
//   EXPECT_NO_THROW(exMPO->processElectables());
//   EXPECT_NO_THROW(exMPO->countVotes());
//   std::vector<Party*> ActualParties = exMPO->getParties();
//   testing::internal::CaptureStdout();
//   for(Party* p : ActualParties){
//     std::cout << p->toString() + " - " + std::to_string(p->getRemainder()) << std::endl;
//   }
//   std::string output = testing::internal::GetCapturedStdout();
//   std::string expected_output = 
//     "Democrat - [Lucy, Pike, Beiye] - 0\n"
//     "Republican - [Alawa, Etta] - 0\n"
//     "Independent - [Sasha] - 0\n";
//   EXPECT_EQ(expected_output, output);

// //   EXPECT_NO_THROW(exMPO->calculateResults());

// //   ActualParties = exMPO->getParties();
// //   EXPECT_EQ(0, ActualParties[0]->getFirstAllocation());
// //   EXPECT_EQ(0, ActualParties[1]->getFirstAllocation());
// //   EXPECT_EQ(1, ActualParties[2]->getFirstAllocation());

// //   testing::internal::CaptureStdout();
// //   for(Party* p : ActualParties){
// //     std::cout << p->toString() + " - " + std::to_string(p->getRemainder()) << std::endl;
// //   }
// //   output = testing::internal::GetCapturedStdout();

// //   expected_output = 
// //     "Democrat - [Lucy, Pike, Beiye] - 3\n"
// //     "Independent - [Sasha] - 2\n"
// //     "Republican - [Alawa, Etta] - 0\n";
// //   EXPECT_EQ(expected_output, output);
// // }

// TEST_F(MPOTest, CalculateResultsSecondAllocationTest){
//   exMPO->parseFile();
//   EXPECT_NO_THROW(exMPO->processElectables());
//   EXPECT_NO_THROW(exMPO->countVotes());
//   std::vector<Party*> ActualParties = exMPO->getParties();
//   EXPECT_EQ(0, ActualParties[0]->getSecondAllocation());
//   EXPECT_EQ(0, ActualParties[1]->getSecondAllocation());
//   EXPECT_EQ(0, ActualParties[2]->getSecondAllocation());
//   EXPECT_NO_THROW(exMPO->calculateResults());

// //   ActualParties = exMPO->getParties();
// //   EXPECT_EQ(1, ActualParties[0]->getSecondAllocation());
// //   EXPECT_EQ(0, ActualParties[1]->getSecondAllocation());
// //   EXPECT_EQ(0, ActualParties[2]->getSecondAllocation());
// // }


// TEST_F(MPOTest, CalculateResultsTotalSeatsTest){
//   exMPO->parseFile();
//   EXPECT_NO_THROW(exMPO->processElectables());
//   EXPECT_NO_THROW(exMPO->countVotes());
//   std::vector<Party*> ActualParties = exMPO->getParties();
//   testing::internal::CaptureStdout();
//   for(Party* p : ActualParties){
//     std::cout << p->toString() + " - " + std::to_string(p->getSeats()) << std::endl;
//   }
//   std::string output = testing::internal::GetCapturedStdout();
//   std::string expected_output = 
//     "Democrat - [Lucy, Pike, Beiye] - 0\n"
//     "Republican - [Alawa, Etta] - 0\n"
//     "Independent - [Sasha] - 0\n";
//   EXPECT_EQ(expected_output, output);

// //   EXPECT_NO_THROW(exMPO->calculateResults());

// //   ActualParties = exMPO->getParties();
// //   testing::internal::CaptureStdout();
// //   for(Party* p : ActualParties){
// //     std::cout << p->toString() + " - " + std::to_string(p->getSeats()) << std::endl;
// //   }
// //   output = testing::internal::GetCapturedStdout();
// //   expected_output = 
// //     "Democrat - [Lucy, Pike, Beiye] - 1\n"
// //     "Independent - [Sasha] - 0\n"
// //     "Republican - [Alawa, Etta] - 1\n";
// //   EXPECT_EQ(expected_output, output);
// // }

// TEST_F(MPOTest, GetWinnersTest){
//   exMPO->parseFile();
//   EXPECT_NO_THROW(exMPO->processElectables());
//   EXPECT_NO_THROW(exMPO->countVotes());
//   EXPECT_NO_THROW(exMPO->calculateResults());
//   EXPECT_NO_THROW(exMPO->getWinners());
//   std::vector<Candidate*> ActualWinners = exMPO->getWinners();
//   EXPECT_EQ(2, (int) ActualWinners.size());

// //   std::vector<Candidate*> ExpectedWinners;
// //   Candidate* expectedC1 = new Candidate("Lucy");
// //   Party* expectedP1 = new Party("Democrat");
// //   expectedC1->setParty(expectedP1);
// //   Candidate* expectedC2 = new Candidate("Alawa");
// //   Party* expectedP2 = new Party("Republican");
// //   expectedC2->setParty(expectedP2);

// //   ExpectedWinners.push_back(expectedC1);
// //   ExpectedWinners.push_back(expectedC2);

// //   int idx = 0;
// // 	for(Candidate* e : ExpectedWinners){
// // 		EXPECT_EQ(e->toString(), ActualWinners[idx]->toString());
// // 		idx += 1;
// // 	}
// // }