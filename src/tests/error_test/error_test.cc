#include "gtest/gtest.h"
#include "../../election.h"

/*
  Tests bad ballot files:

    Same for any type:
      File does not exist
      Election type is bad
      seat count is 0
      seat count is negative
      seat count is too big
      seat count is not a number
      ballot count is 0
      ballot count is negative
      ballot count is too big
      ballot count is not a number
      electable count is 0
      electable count is negative
      electable count is too big
      electable count is not a number

    Differs by type:
      OPL Candidate name is missing
      OPL Party name is missing
      CPL Candidate name is missing
      CPL Party name is missing
      MV / MPO Candidate name is missing
      MV / MPO Party name is missing
      OPL / CPL / MPO vote is bad
      MV vote is bad

    Multifile same for any type:
      multifile seat count differs
      multifile electable count differs
      multifile type differs
      multifile party differs
      multifile candidate differs
*/


class ErrorTest : public testing::Test {
  public:
    void SetUp() {
      
    }
    void TearDown() {
      
    }
};

TEST_F(ErrorTest, FileDoesNotExist) {
  std::string f = "../../../testing/ThisFileDoesNotExist.csv";
  std::vector<std::string> vf;
  vf.push_back(f);
  EXPECT_DEATH(Election election(vf), "ios failure\nIt is likely that the file does not exist\nbasic_ios::clear: iostream error\niostream:1");
}

TEST_F(ErrorTest, BadType) {
  std::string f = "../../../testing/BADType.csv";
  std::vector<std::string> vf;
  vf.push_back(f);
  EXPECT_DEATH(Election election(vf), "Bad election type: BAD");
}

TEST_F(ErrorTest, BadSeatCount) {
  std::string f = "../../../testing/BADSeatCount0.csv";
  std::vector<std::string> vf;
  vf.push_back(f);
  EXPECT_DEATH(Election election(vf), "On line 2\nseatCount is less than 1");

  std::string f2 = "../../../testing/BADSeatCountNeg.csv";
  std::vector<std::string> vf2;
  vf2.push_back(f2);
  EXPECT_DEATH(Election election2(vf2), "On line 2\nseatCount is less than 1");

  std::string f3 = "../../../testing/BADSeatCountBig.csv";
  std::vector<std::string> vf3;
  vf3.push_back(f3);
  EXPECT_DEATH(Election election3(vf3), "On line 2\n`3333333333333333333333333333333333333` out of range\nstoi");

  std::string f4 = "../../../testing/BADSeatCountNaN.csv";
  std::vector<std::string> vf4;
  vf4.push_back(f4);
  EXPECT_DEATH(Election election4(vf4), "On line 2\nCould not convert `three` to integer\nstoi");
}

TEST_F(ErrorTest, BadBallotCount) {
  std::string f = "../../../testing/BADBallotCount0.csv";
  std::vector<std::string> vf;
  vf.push_back(f);
  EXPECT_DEATH(Election election(vf), "On line 3\nballotCount is less than 1");

  std::string f2 = "../../../testing/BADBallotCountNeg.csv";
  std::vector<std::string> vf2;
  vf2.push_back(f2);
  EXPECT_DEATH(Election election2(vf2), "On line 3\nballotCount is less than 1");

  std::string f3 = "../../../testing/BADBallotCountBig.csv";
  std::vector<std::string> vf3;
  vf3.push_back(f3);
  EXPECT_DEATH(Election election3(vf3), "On line 3\n`13131313131313131313131313131313` out of range\nstoi");

  std::string f4 = "../../../testing/BADBallotCountNaN.csv";
  std::vector<std::string> vf4;
  vf4.push_back(f4);
  EXPECT_DEATH(Election election4(vf4), "On line 3\nCould not convert `thirteen` to integer\nstoi");
}

TEST_F(ErrorTest, BadElectCount) {
  std::string f = "../../../testing/BADElectCount0.csv";
  std::vector<std::string> vf;
  vf.push_back(f);
  EXPECT_DEATH(Election election(vf), "On line 4\nelectablesCount is less than 1");

  std::string f2 = "../../../testing/BADElectCountNeg.csv";
  std::vector<std::string> vf2;
  vf2.push_back(f2);
  EXPECT_DEATH(Election election2(vf2), "On line 4\nelectablesCount is less than 1");

  std::string f3 = "../../../testing/BADElectCountBig.csv";
  std::vector<std::string> vf3;
  vf3.push_back(f3);
  EXPECT_DEATH(Election election3(vf3), "On line 4\n`44444444444444444444444444444444444` out of range\nstoi");

  std::string f4 = "../../../testing/BADElectCountNaN.csv";
  std::vector<std::string> vf4;
  vf4.push_back(f4);
  EXPECT_DEATH(Election election4(vf4), "On line 4\nCould not convert `four` to integer\nstoi");
}

TEST_F(ErrorTest, BadPartyName) {
  std::string f = "../../../testing/BADPartyNameCPL.csv";
  std::vector<std::string> vf;
  vf.push_back(f);
  Election election(vf);
  EXPECT_DEATH(election.doElection(), "No party name on line 5");

  std::string f2 = "../../../testing/BADPartyNameMXX.csv";
  std::vector<std::string> vf2;
  vf2.push_back(f2);
  Election election2(vf2);
  EXPECT_DEATH(election2.doElection(), "No party name in line 6");

  std::string f3 = "../../../testing/BADPartyNameOPL.csv";
  std::vector<std::string> vf3;
  vf3.push_back(f3);
  Election election3(vf3);
  EXPECT_DEATH(election3.doElection(), "Could not find comma on line 5");
}

TEST_F(ErrorTest, BadCandidateName) {
  std::string f = "../../../testing/BADCandidateNameCPL.csv";
  std::vector<std::string> vf;
  vf.push_back(f);
  Election election(vf);
  EXPECT_DEATH(election.doElection(), "No candidate name on line 5");

  std::string f2 = "../../../testing/BADCandidateNameMXX.csv";
  std::vector<std::string> vf2;
  vf2.push_back(f2);
  Election election2(vf2);
  EXPECT_DEATH(election2.doElection(), "No candidate name in line 6");

  std::string f3 = "../../../testing/BADCandidateNameOPL.csv";
  std::vector<std::string> vf3;
  vf3.push_back(f3);
  Election election3(vf3);
  EXPECT_DEATH(election3.doElection(), "Could not find comma on line 5");
}

TEST_F(ErrorTest, BadVote) {
  std::string f = "../../../testing/BADVoteMVa.csv";
  std::vector<std::string> vf;
  vf.push_back(f);
  Election election(vf);
  EXPECT_DEATH(election.doElection(), "Invalid vote on line 6");

  std::string f2 = "../../../testing/BADVoteMVb.csv";
  std::vector<std::string> vf2;
  vf2.push_back(f2);
  Election election2(vf2);
  EXPECT_DEATH(election2.doElection(), "Invalid vote on line 6");

  std::string f4 = "../../../testing/BADVoteXPXa.csv";
  std::vector<std::string> vf4;
  vf4.push_back(f4);
  Election election4(vf4);
  EXPECT_DEATH(election4.doElection(), "Invalid vote on line 9");

  std::string f5 = "../../../testing/BADVoteXPXb.csv";
  std::vector<std::string> vf5;
  vf5.push_back(f5);
  Election election5(vf5);
  EXPECT_DEATH(election5.doElection(), "Invalid vote on line 9");
}

TEST_F(ErrorTest, BadMultifile) {
  std::string f1 = "../../../testing/OPL1.csv";
  std::string f2 = "../../../testing/OPL2.csv";
  std::string f3 = "../../../testing/OPL3.csv";

  std::string fa = "../../../testing/OPL2BADType.csv";
  std::string fb = "../../../testing/OPL2BADSeat.csv";
  std::string fc = "../../../testing/OPL2BADElect.csv";
  std::string fd = "../../../testing/OPL2BADCandidate.csv";
  std::string fe = "../../../testing/OPL2BADParty.csv";

  std::vector<std::string> vf;
  vf.push_back(f1);
  vf.push_back(f2);
  vf.push_back(f3);

  vf.push_back(fa);
  EXPECT_DEATH(Election election(vf), "On line 1\nFound different election type: CPL");

  vf.pop_back();
  vf.push_back(fb);
  EXPECT_DEATH(Election election(vf), "On line 2\nFound different seat count: 4");

  vf.pop_back();
  vf.push_back(fc);
  EXPECT_DEATH(Election election(vf), "On line 4\nFound different electablesCount: 7");

  vf.pop_back();
  vf.push_back(fd);
  EXPECT_DEATH(Election election(vf), "On lines 5 to 12\nExpected electables to match");

  vf.pop_back();
  vf.push_back(fe);
  EXPECT_DEATH(Election election(vf), "On lines 5 to 12\nExpected electables to match");
}
