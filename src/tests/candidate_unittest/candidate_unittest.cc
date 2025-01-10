#include "gtest/gtest.h"
#include "../../candidate.h"
#include "../../party.h"
#include "../../electable.h"

class CandidateTest : public::testing::Test {
    public:
      void SetUp() {}
      void TearDown() {}     
};

TEST_F(CandidateTest, ConstructorTest) {
    Candidate c1("Ashwin");
    EXPECT_NO_THROW(Candidate c1("Ashwin"));
    EXPECT_EQ(c1.getName(), "Ashwin");
}

TEST_F(CandidateTest, setPartyTest) {
    Candidate c1("Ashwin");
    Candidate c2("Ashwin Two");
    Candidate c3("Ashwin Three");
    Party green("Green");
    Party republican("Republican");
    Party democrat("Democrat");
    c1.setParty(&green);
    EXPECT_EQ(c1.getParty(), &green);
    c2.setParty(&republican);
    c3.setParty(&democrat);
    EXPECT_EQ(c2.getParty(), &republican);
    EXPECT_EQ(c3.getParty(), &democrat);
}

TEST_F(CandidateTest, getPartyTest) {
    Candidate c1("Ashwin");
    Party green("Green");
    c1.setParty(&green);
    EXPECT_EQ(c1.getParty(), &green);
}

TEST_F(CandidateTest, toStringTest) {
    Candidate c1("Ashwin");
    Party green("Green");
    c1.setParty(&green);
    Candidate c2("Ashwin Two");
    EXPECT_EQ(c1.toString(), "Ashwin - Green");
    EXPECT_EQ(c2.toString(), "Ashwin Two - No party");
}

TEST_F(CandidateTest, getNameTest) {
    Candidate c2("Ashwin Two");
    EXPECT_EQ(c2.getName(), "Ashwin Two");
}

TEST_F(CandidateTest, setNameTest) {
	Candidate c1("Ashwin");
	c1.setName("Rob");
	EXPECT_EQ(c1.getName(), "Rob");
}
