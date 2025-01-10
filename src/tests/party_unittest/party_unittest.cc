#include "gtest/gtest.h"
#include "../../candidate.h"
#include "../../party.h"
#include "../../electable.h"

class PartyTest : public::testing::Test {
    public:
      void SetUp() {}
      void TearDown() {}     
};

TEST_F(PartyTest, ConstructorTest) {
	EXPECT_NO_THROW(Party green("Green"));
	Party green("Green");
	EXPECT_EQ(green.getName(), "Green");
}

TEST_F(PartyTest, addCandidateTest) {
	Party green("Green");
	Candidate ashwin("Ashwin");
	EXPECT_EQ(green.addCandidate(&ashwin), 0);
	Candidate rob("Rob");
	EXPECT_EQ(green.addCandidate(&rob), 1);
}

TEST_F(PartyTest, getCandidatesTest) {
	Party green("Green");
	Candidate ashwin("Ashwin");
	Candidate ashwin2("Ashwin2");
	Candidate ashwin3("Ashwin3");
	Candidate ashwin4("Ashwin4");
	Candidate ashwin5("Ashwin5");
	std::vector<Candidate*> test{&ashwin, &ashwin2, &ashwin3, &ashwin4, &ashwin5};
	green.addCandidate(&ashwin);
	green.addCandidate(&ashwin2);
	green.addCandidate(&ashwin3);
	green.addCandidate(&ashwin4);
	green.addCandidate(&ashwin5);
	EXPECT_EQ(green.getCandidates(), test);
}

TEST_F(PartyTest, setCandidatesTest) {
	Party green("Green");
	Candidate ashwin("Ashwin");
	Candidate ashwin2("Ashwin2");
	Candidate ashwin3("Ashwin3");
	Candidate ashwin4("Ashwin4");
	Candidate ashwin5("Ashwin5");
	std::vector<Candidate*> test{&ashwin, &ashwin2, &ashwin3, &ashwin4, &ashwin5};
	green.addCandidate(&ashwin);
	green.addCandidate(&ashwin2);
	green.addCandidate(&ashwin3);
	green.addCandidate(&ashwin4);
	green.addCandidate(&ashwin5);
	EXPECT_EQ(green.getCandidates(), test);
	EXPECT_EQ((int) green.getCandidates().size(), 5);

	Candidate leo("Leo");
	Candidate leo1("Leo1");
	Candidate leo2("Leo2");
	std::vector<Candidate*> test2{&leo, &leo1, &leo2};
	EXPECT_NO_THROW(green.setCandidates(test2));
	EXPECT_EQ(green.getCandidates(), test2);
	EXPECT_EQ((int) green.getCandidates().size(), 3);
}

TEST_F(PartyTest, getCandidateTest) {
	Party green("Green");
	Candidate ashwin("Ashwin");
	Candidate ashwin2("Ashwin2");
	Candidate ashwin3("Ashwin3");
	Candidate ashwin4("Ashwin4");
	Candidate ashwin5("Ashwin5");
	green.addCandidate(&ashwin);
	green.addCandidate(&ashwin2);
	green.addCandidate(&ashwin3);
	green.addCandidate(&ashwin4);
	green.addCandidate(&ashwin5);
	EXPECT_EQ(green.getCandidate(0), &ashwin);
	EXPECT_EQ(green.getCandidate(1), &ashwin2);
	EXPECT_EQ(green.getCandidate(2), &ashwin3);
	EXPECT_EQ(green.getCandidate(3), &ashwin4);
	EXPECT_EQ(green.getCandidate(4), &ashwin5);
}

TEST_F(PartyTest, getCandidateCountTest) {
	Party green("Green");
	Candidate ashwin("Ashwin");
	Candidate ashwin2("Ashwin2");
	Candidate ashwin3("Ashwin3");
	Candidate ashwin4("Ashwin4");
	Candidate ashwin5("Ashwin5");
	green.addCandidate(&ashwin);
	green.addCandidate(&ashwin2);
	green.addCandidate(&ashwin3);
	green.addCandidate(&ashwin4);
	green.addCandidate(&ashwin5);
	EXPECT_EQ(green.getCandidateCount(), 5);
}

TEST_F(PartyTest, toStringTest) {
	Party green("Green");
	Party green2("Green 2");
	Candidate ashwin("Ashwin");
	Candidate ashwin2("Ashwin2");
	Candidate ashwin3("Ashwin3");
	Candidate ashwin4("Ashwin4");
	Candidate ashwin5("Ashwin5");
	green.addCandidate(&ashwin);
	green.addCandidate(&ashwin2);
	green.addCandidate(&ashwin3);
	green.addCandidate(&ashwin4);
	green.addCandidate(&ashwin5);
	EXPECT_EQ(green.toString(), "Green - [Ashwin, Ashwin2, Ashwin3, Ashwin4, Ashwin5]");
	EXPECT_EQ(green2.toString(), "Green 2 - []");
}

TEST_F(PartyTest, getSeatsTest) {
	Party green("Green");
	EXPECT_EQ(green.getSeats(), 0);
	green.setSeats(15);
	EXPECT_EQ(green.getSeats(), 15);
}

TEST_F(PartyTest, setSeatsTest) {
	Party green("Green");
	green.setSeats(2000);
	EXPECT_EQ(green.getSeats(), 2000);
	green.setSeats(0);
	EXPECT_EQ(green.getSeats(), 0);
}

TEST_F(PartyTest, incSeatsTest) {
	Party green("Green");
	green.setSeats(5);
	green.incSeats();
	EXPECT_EQ(green.getSeats(), 6);
	green.incSeats();
	green.incSeats();
	green.incSeats();
	green.incSeats();
	EXPECT_EQ(green.getSeats(), 10);
}

TEST_F(PartyTest, getRemainderTest) {
	Party green("Green");
	EXPECT_EQ(green.getRemainder(), 0);
	green.setRemainder(4);
	EXPECT_EQ(green.getRemainder(), 4);
}

TEST_F(PartyTest, setRemainderTest) {
	Party green("Green");
	green.setRemainder(6);
	EXPECT_EQ(green.getRemainder(), 6);
	green.setRemainder(0);
	EXPECT_EQ(green.getRemainder(), 0);
}

TEST_F(PartyTest, getNameTest) {
	Party green("Green");
	Party republican("Republican");
	Party democratic("Democratic");
	EXPECT_EQ(green.getName(), "Green");
	EXPECT_EQ(republican.getName(), "Republican");
	EXPECT_EQ(democratic.getName(), "Democratic");
}

TEST_F(PartyTest, setNameTest) {
	Party democratic("Green");
	democratic.setName("Democratic");
	EXPECT_EQ(democratic.getName(), "Democratic");
}