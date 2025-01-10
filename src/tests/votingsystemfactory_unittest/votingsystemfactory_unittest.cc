/**
******************************************************************************
 * @file votingsystemfactory_unittest.cc
 * @brief Unit test file for Voting System Factory class
 * @author Janani Kannan
******************************************************************************
*/

#include "gtest/gtest.h"
#include "../../votingsystem.h"
#include "../../votingsystemfactory.h"

class VotingSystemFactoryTest : public testing::Test {
    public:
        void SetUp() {
            votingSystemFactory = new VotingSystemFactory();
        }
		void TearDown() {
      
    	}
    protected:
        std::string OPLFile = "../../../testing/opl_ballot.csv";
        std::string CPLFile = "../../../testing/cpl_ballot.csv";
        VotingSystemFactory* votingSystemFactory;
};

TEST_F(VotingSystemFactoryTest, ConstructorTest){
    EXPECT_NO_THROW(VotingSystemFactory());
}

TEST_F(VotingSystemFactoryTest, NewVotingSystemTest){
    EXPECT_NO_THROW(votingSystemFactory->newVotingSystem(OPLFile));
    VotingSystem* exOPL = votingSystemFactory->newVotingSystem(OPLFile);
    EXPECT_EQ("OPL", exOPL->getElectionType());

    EXPECT_NO_THROW(votingSystemFactory->newVotingSystem(CPLFile));
    VotingSystem* exCPL = votingSystemFactory->newVotingSystem(CPLFile);
    EXPECT_EQ("CPL", exCPL->getElectionType());
}