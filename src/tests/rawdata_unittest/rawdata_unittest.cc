/**
 * @file rawdata_unittest.cc
 * @brief RawData_unittest source file
 * @author Leo Dong
 */

#include <fstream>
#include "gtest/gtest.h"
#include "../../rawdata.h"


class RawDataTest : public::testing::Test {
 public:
  void SetUp() {
    exampleCPL = RawData(CPL);
    exampleOPL = RawData(OPL);
    exampleMV = RawData(mv);
    exampleMPO = RawData(mpo);
    rawData1 = RawData(txtFile);
    errorRawData = RawData(errorFile);
  }
 protected:
  std::string txtFile = "../../../testing/textTestfile.txt";
  std::string CPL = "../../../testing/cpl_ballot.csv";
  std::string OPL = "../../../testing/opl_ballot.csv";
  std::string mpo = "../../../testing/mpo_ballot.csv";
  std::string mv = "../../../testing/mv_ballot.csv";
  std::string errorFile = "../../../testing/notExist.csv";
  
  RawData rawData1;
  RawData defaultRawData;
  RawData exampleCPL;
  RawData exampleOPL;
  RawData exampleMV;
  RawData exampleMPO;
  RawData errorRawData;
};


TEST_F(RawDataTest, constructorTest) {
  EXPECT_NO_THROW(RawData());
  EXPECT_NO_THROW(RawData(CPL));
}

TEST_F(RawDataTest, writeTest) {
  EXPECT_THROW(defaultRawData.write("test"),  std::runtime_error);
  EXPECT_THROW(rawData1.write("test"),  std::runtime_error);
  EXPECT_THROW(exampleCPL.write("test"),  std::runtime_error);
  EXPECT_THROW(exampleOPL.write("test"),  std::runtime_error);
}

TEST_F(RawDataTest, getElectionTest) {
  EXPECT_NO_THROW(defaultRawData.getElectionType());
  EXPECT_EQ("", defaultRawData.getElectionType());
  EXPECT_NO_THROW(exampleCPL.getElectionType());
  EXPECT_EQ("", exampleCPL.getElectionType());
}
TEST_F(RawDataTest, getElectablesTest) {
  EXPECT_NO_THROW(defaultRawData.getElectablesCount());
  EXPECT_EQ(-1, defaultRawData.getElectablesCount());
  EXPECT_NO_THROW(exampleCPL.getElectablesCount());
  EXPECT_EQ(-1, exampleCPL.getElectablesCount());
}
TEST_F(RawDataTest, getBallotTest) {
  EXPECT_NO_THROW(defaultRawData.getBallotCount());
  EXPECT_EQ(-1, defaultRawData.getBallotCount());
  EXPECT_NO_THROW(exampleCPL.getBallotCount());
  EXPECT_EQ(-1, exampleCPL.getBallotCount());
}
TEST_F(RawDataTest, getSeatTest) {
  EXPECT_NO_THROW(defaultRawData.getSeatCount());
  EXPECT_EQ(-1, defaultRawData.getSeatCount());
  EXPECT_NO_THROW(exampleCPL.getSeatCount());
  EXPECT_EQ(-1, exampleCPL.getSeatCount());
}
TEST_F(RawDataTest, getElectablesInfoTest) {
  EXPECT_NO_THROW(defaultRawData.getElectablesInfo());
  EXPECT_EQ("", defaultRawData.getElectablesInfo());
  EXPECT_NO_THROW(exampleCPL.getElectablesInfo());
  EXPECT_EQ("", exampleCPL.getElectablesInfo());
}
TEST_F(RawDataTest, getBallotInfoTest) {
  EXPECT_NO_THROW(defaultRawData.getBallotInfo());
  EXPECT_EQ("", defaultRawData.getBallotInfo());
  EXPECT_NO_THROW(exampleCPL.getBallotInfo());
  EXPECT_EQ("", exampleCPL.getBallotInfo());
}

TEST_F(RawDataTest, getFilenameTest) {
  std::string output_1 = exampleCPL.getFilename();
  std::string expected_out_1 = "cpl_ballot.csv";

  std::string output_2 = exampleOPL.getFilename();
  std::string expected_out_2 = "opl_ballot.csv";

  std::string output_3 = defaultRawData.getFilename();
  std::string expected_out_3 = "Unknown";

  EXPECT_EQ(output_1, expected_out_1);
  EXPECT_EQ(output_2, expected_out_2);
  EXPECT_EQ(output_3, expected_out_3);
}


TEST_F(RawDataTest, readElectionTypeTest) {
  std::ifstream file;
  
  file.open(OPL);
  EXPECT_NO_THROW(exampleOPL.readElectionType(&file));
  std::string electionType = exampleOPL.getElectionType();
  std::string expected_et = "OPL";
  EXPECT_EQ(electionType, expected_et);
  file.close();

  file.open(CPL);
  EXPECT_NO_THROW(exampleCPL.readElectionType(&file));
  electionType = exampleCPL.getElectionType();
  expected_et = "CPL";
  EXPECT_EQ(electionType, expected_et);
  file.close();

  file.open(mpo);
  EXPECT_NO_THROW(exampleMPO.readElectionType(&file));
  electionType = exampleMPO.getElectionType();
  expected_et = "MPO";
  EXPECT_EQ(electionType, expected_et);
  file.close();

  file.open(mv);
  EXPECT_NO_THROW(exampleMV.readElectionType(&file));
  electionType = exampleMV.getElectionType();
  expected_et = "MV";
  EXPECT_EQ(electionType, expected_et);
  file.close();
  
  std::stringstream buffer;
  std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());
  file.open(errorFile);
  EXPECT_EXIT(errorRawData.readElectionType(&file), testing::ExitedWithCode(1), buffer.str());
  std::cerr.rdbuf(old);
  file.close();
}


TEST_F(RawDataTest, readSeatCountTest) {
  std::ifstream file;
  
  file.open(OPL);
  EXPECT_NO_THROW(exampleOPL.readElectionType(&file));
  EXPECT_NO_THROW(exampleOPL.readSeatCount(&file));
  int seatCount = exampleOPL.getSeatCount();
  int expected_et = 2;
  EXPECT_EQ(seatCount, expected_et);
  file.close();

  file.open(CPL);
  EXPECT_NO_THROW(exampleCPL.readElectionType(&file));
  EXPECT_NO_THROW(exampleCPL.readSeatCount(&file));
  seatCount = exampleCPL.getSeatCount();
  expected_et = 3;
  EXPECT_EQ(seatCount, expected_et);
  file.close();

  file.open(mpo);
  EXPECT_NO_THROW(exampleMPO.readElectionType(&file));
  EXPECT_NO_THROW(exampleMPO.readSeatCount(&file));
  seatCount = exampleMPO.getSeatCount();
  expected_et = 2;
  EXPECT_EQ(seatCount, expected_et);
  file.close();

  file.open(mv);
  EXPECT_NO_THROW(exampleMV.readElectionType(&file));
  EXPECT_NO_THROW(exampleMV.readSeatCount(&file));
  seatCount = exampleMV.getSeatCount();
  expected_et = 3;
  EXPECT_EQ(seatCount, expected_et);
  file.close();
  
  std::stringstream buffer;
  std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());
  file.open(errorFile);
  EXPECT_EXIT(errorRawData.readSeatCount(&file), testing::ExitedWithCode(1), buffer.str());
  std::cerr.rdbuf(old);
  file.close();
}

TEST_F(RawDataTest, parseFileTest) {
  EXPECT_NO_THROW(exampleCPL.parseFile());
  int exitCode = exampleCPL.parseFile();
  int expected_exitCode = 0;
  EXPECT_EQ(exitCode, expected_exitCode);

  exitCode = defaultRawData.parseFile();
  EXPECT_EQ(exitCode, 0);
  // EXPECT_EXIT(defaultRawData.parseFile(), testing::ExitedWithCode(1), "Exiting with error");
  // EXPECT_EQ(defaultRawData.parseFile()., std::runtime_error);
  // try {
  //   defaultRawData.parseFile();
  //   std::cout << "testing" << std::endl;
  //   EXPECT_EQ(std::string("basic_ios::clear: iostream error"), std::runtime_error);
  //   // FAIL();
  // } catch (const std::runtime_error& e) {
  //   EXPECT_EQ(e.what(), std::string("Incorrect file name format"));
  // } catch (const std::ios_base::failure &e){
  //   EXPECT_EQ(e.what(), std::string("ios failure"));
  // }

  // try {
  //   rawData1.parseFile();
  //   FAIL();
  // } catch (const std::runtime_error& e) {
  //   EXPECT_EQ(e.what(), std::string("Only .csv file is allowed"));
  // }
}

TEST_F(RawDataTest, CPLFileTest) {
  EXPECT_NO_THROW(exampleCPL.parseFile());
  std::string exampleCPL_electionType = exampleCPL.getElectionType();
  std::string expected_et = "CPL";
  int exampleCPL_electablesCount = exampleCPL.getElectablesCount();
  int expected_ec = 6;
  int exampleCPL_ballotCount = exampleCPL.getBallotCount();
  int expected_bc = 9;
  int exampleCPL_seatCount = exampleCPL.getSeatCount();
  int expected_sc = 3;
  std::string exampleCPL_electables = exampleCPL.getElectablesInfo();
  std::string expected_electables = 
    "Democratic, Joe, Sally, Ahmed\n"
    "Republican, Allen, Nikki, Taihui\n"
    "New Wave, Sarah\n"
    "Reform, Xinyue, Nikita\n"
    "Green, Bethany\n"
    "Independent, Mike\n";
  std::string exampleCPL_ballotInfo = exampleCPL.getBallotInfo();
  std::string expected_ballotInfo = 
    "1,,,,,\n"
    "1,,,,,\n"
    ",1,,,,\n"
    ",,,,1,\n"
    ",,,,,1\n"
    ",,,1,,\n"
    ",,,1,,\n"
    "1,,,,,\n"
    ",1,,,,\n";
  EXPECT_EQ(exampleCPL_electionType, expected_et);
  EXPECT_EQ(exampleCPL_electablesCount, expected_ec);
  EXPECT_EQ(exampleCPL_ballotCount, expected_bc);
  EXPECT_EQ(exampleCPL_seatCount, expected_sc);
  EXPECT_EQ(exampleCPL_electables, expected_electables);
  EXPECT_EQ(exampleCPL_ballotInfo, expected_ballotInfo);
}

TEST_F(RawDataTest, OPLFileTest) {
  EXPECT_NO_THROW(exampleOPL.parseFile());
  std::string exampleOPL_electionType = exampleOPL.getElectionType();
  std::string expected_et = "OPL";
  int exampleOPL_electablesCount = exampleOPL.getElectablesCount();
  int expected_ec = 6;
  int exampleOPL_ballotCount = exampleOPL.getBallotCount();
  int expected_bc = 9;
  int exampleOPL_seatCount = exampleOPL.getSeatCount();
  int expected_sc = 2;
  std::string exampleOPL_electables = exampleOPL.getElectablesInfo();
  std::string expected_electables = 
    "Democrat, Pike\n"
    "Democrat, Lucy\n"
    "Democrat, Beiye\n"
    "Republican, Etta\n"
    "Republican, Alawa\n"
    "Independent, Sasha\n";
  std::string exampleOPL_ballotInfo = exampleOPL.getBallotInfo();
  std::string expected_ballotInfo = 
    "1,,,,,\n"
    ",1,,,,\n"
    ",1,,,,\n"
    ",,,,1,\n"
    ",,,,,1\n"
    ",,,1,,\n"
    ",,,,1,\n"
    ",,,,1,\n"
    ",,,,,1\n";


  EXPECT_EQ(exampleOPL_electionType, expected_et);
  EXPECT_EQ(exampleOPL_electablesCount, expected_ec);
  EXPECT_EQ(exampleOPL_ballotCount, expected_bc);
  EXPECT_EQ(exampleOPL_seatCount, expected_sc);
  EXPECT_EQ(exampleOPL_electables, expected_electables);
  EXPECT_EQ(exampleOPL_ballotInfo, expected_ballotInfo);

  // EXPECT_THROW(errorRawData.parseFile(),  std::runtime_error);
}


