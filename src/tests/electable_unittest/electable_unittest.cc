#include "gtest/gtest.h"
#include "../../candidate.h"
#include "../../party.h"
#include "../../electable.h"

class ElectableTest : public::testing::Test {
    public:
      void SetUp() {}
      void TearDown() {}     
};

TEST_F(ElectableTest, getVotesTest) {
    Candidate c1("Ashwin");
    EXPECT_EQ(c1.getVotes(), 0);
    Party p1("Green");
    EXPECT_EQ(p1.getVotes(), 0);
    c1.addVotes(1000);
    p1.addVotes(2342);
    EXPECT_EQ(c1.getVotes(), 1000);
    EXPECT_EQ(p1.getVotes(), 2342);
}

TEST_F(ElectableTest, incVotesTest) {
    Candidate c1("Ashwin");
    Party p1("Green");
    c1.incVotes();
    EXPECT_EQ(c1.getVotes(), 1);
    c1.incVotes();
    c1.incVotes();
    c1.incVotes();
    EXPECT_EQ(c1.getVotes(), 4);
    p1.incVotes();
    p1.incVotes();
    EXPECT_EQ(p1.getVotes(), 2);
}

TEST_F(ElectableTest, addVotesTest) {
    Candidate c1("Ashwin"); 
    Party p1("Green");
    c1.addVotes(555);
    p1.addVotes(555);
    EXPECT_EQ(c1.getVotes(), 555);
    EXPECT_EQ(p1.getVotes(), 555);
}

TEST_F(ElectableTest, getFirstAllocationTest) {
    Party p1("Green");
    EXPECT_EQ(p1.getFirstAllocation(), 0);
    p1.setFirstAllocation(12);
    EXPECT_EQ(p1.getFirstAllocation(), 12);
}

TEST_F(ElectableTest, setFirstAllocationTest) {
    Party p1("Green");
    p1.setFirstAllocation(6);
    EXPECT_EQ(p1.getFirstAllocation(), 6);
}

TEST_F(ElectableTest, getSecondAllocationTest) {
    Party p1("Green");
    EXPECT_EQ(p1.getSecondAllocation(), 0);
    p1.setSecondAllocation(2);
    EXPECT_EQ(p1.getSecondAllocation(), 2);
}

TEST_F(ElectableTest, setSecondAllocationTest) {
    Party p1("Green");
    p1.setSecondAllocation(3);
    EXPECT_EQ(p1.getSecondAllocation(), 3);
}

TEST_F(ElectableTest, incSecondAllocationTest) {
    Party p1("Green");
    p1.incSecondAllocation();
    p1.incSecondAllocation();
    p1.incSecondAllocation();
    EXPECT_EQ(p1.getSecondAllocation(), 3);
}

TEST_F(ElectableTest, setNameTest) {
    Party p1("Green");
    p1.setName("Democratic");
    EXPECT_EQ(p1.getName(), "Democratic");
    Candidate c1("Ashwin");
    c1.setName("Rob");
    EXPECT_EQ(c1.getName(), "Rob");
}

TEST_F(ElectableTest, getNameTest) {
    Party p1("Green");
    Candidate c1("Ashwin");
    EXPECT_EQ(p1.getName(), "Green");
    EXPECT_EQ(c1.getName(), "Ashwin");
}

TEST_F(ElectableTest, toStringTest) {
    Candidate c1("Ashwin");
    Party green("Green");
    c1.setParty(&green);
    green.addCandidate(&c1);
    EXPECT_EQ(c1.toString(), "Ashwin - Green");
    EXPECT_EQ(green.toString(), "Green - [Ashwin]");
}
