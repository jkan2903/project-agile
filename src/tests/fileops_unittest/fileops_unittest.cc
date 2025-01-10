#include "gtest/gtest.h"
#include "../../fileops.h"
#include <filesystem>
#include <sstream>

class FileopsTest : public::testing::Test {
 public:
  void SetUp() { 
    Fileops1 = Fileops(txtFile);
    Fileops2 = Fileops(binFile);
    Fileops3 = Fileops(ballotFile);
    Fileops4 = Fileops(errorFile);
    nonExistFileops = Fileops(nonExistFile);
    Fileops_write = Fileops(fileToWrite);

    exampleCPL = Fileops(CPL);
    exampleOPL = Fileops(OPL);
    std::filesystem::remove(fileToWrite);
  }
  void TearDown() {
    std::filesystem::remove(fileToWrite);
  }
 protected:
  std::string txtFile = "../../../testing/textTestfile.txt";
  std::string binFile = "../../../testing/binTestFile.bin";
  std::string ballotFile = "../../../testing/Ballot.csv";
  std::string errorFile = "../../../testing/errorFile";
  std::string nonExistFile = "lasjdfwr";
  std::string fileToWrite = "fileToWrite";

  Fileops defaultFileops;
  Fileops Fileops1;
  Fileops Fileops2;
  Fileops Fileops3;
  Fileops Fileops4;
  Fileops nonExistFileops;
  Fileops Fileops_write;

  std::string CPL = "../../../testing/cpl_ballot.csv";
  std::string OPL = "../../../testing/opl_ballot.csv";

  Fileops exampleCPL;
  Fileops exampleOPL;
};


TEST_F(FileopsTest, constructorTest) {
  EXPECT_NO_THROW(Fileops());
  EXPECT_NO_THROW(Fileops("test.csv"));
  EXPECT_NO_THROW(Fileops(CPL));
}


TEST_F(FileopsTest, getFilenameTest) {
  std::string output = defaultFileops.getFilename();
  std::string expected_out = "Unknown";
  EXPECT_EQ(output, expected_out);

  std::string output_1 = Fileops1.getFilename();
  std::string expected_out_1 = "textTestfile.txt";

  std::string output_2 = Fileops2.getFilename();
  std::string expected_out_2 = "binTestFile.bin";

  std::string output_3 = Fileops3.getFilename();
  std::string expected_out_3 = "Ballot.csv";

  std::string output_4 = Fileops4.getFilename();
  std::string expected_out_4 = "errorFile";

  EXPECT_EQ(output_1, expected_out_1);
  EXPECT_EQ(output_2, expected_out_2);
  EXPECT_EQ(output_3, expected_out_3);
  EXPECT_EQ(output_4, expected_out_4);
}


TEST_F(FileopsTest, checkCSVFormatTest) {
  try {
    Fileops1.checkCSVFormat();
    FAIL();
  } catch (const std::runtime_error& e) {
    EXPECT_EQ(e.what(), std::string("Only .csv file is allowed"));
  }

  try {
    Fileops2.checkCSVFormat();
    FAIL();
  } catch (const std::runtime_error& e) {
    EXPECT_EQ(e.what(), std::string("Only .csv file is allowed"));
  }

  try {
    Fileops4.checkCSVFormat();
    FAIL();
  } catch (const std::runtime_error& e) {
    EXPECT_EQ(e.what(), std::string("Incorrect file name format"));
  }

  EXPECT_NO_THROW(Fileops3.checkCSVFormat());
  int exitCode3 = Fileops3.checkCSVFormat();
  int expected_out3 = 0;
  EXPECT_EQ(exitCode3, expected_out3);

  EXPECT_NO_THROW(exampleCPL.checkCSVFormat());
  int exitCodeCPL = exampleCPL.checkCSVFormat();
  int expected_CPL = 0;
  EXPECT_EQ(exitCodeCPL, expected_CPL);

  EXPECT_NO_THROW(exampleOPL.checkCSVFormat());
  int exitCodeOPL = exampleOPL.checkCSVFormat();
  int expected_OPL = 0;
  EXPECT_EQ(exitCodeOPL, expected_OPL);
}


TEST_F(FileopsTest, writeTest) {
  std::string content = "Hello World";
  int exitCode = Fileops_write.write(content);
  int expected_code = 0;
  EXPECT_EQ(exitCode, expected_code);

  std::ifstream file(fileToWrite);
  std::string line;
  std::stringstream lines;
  if (file.is_open()) {
    getline(file, line);
    EXPECT_EQ(line, content);
  } else {
    FAIL() << "Fail to open for reading.";
  }
  file.close();

  exitCode = Fileops_write.write(content);
  EXPECT_EQ(exitCode, expected_code);

  std::ifstream file2(fileToWrite);
  if (file2.is_open()) {
    while (std::getline(file2, line)){
      if (!lines.str().empty()) {
        lines << "\n";
      }
      lines << line;
    }
    EXPECT_EQ(lines.str(), content + "\n" + content);
  } else {
    FAIL() << "Fail to open for reading.";
  }
  file2.close();

  EXPECT_THROW(Fileops("ads/asdfavab/ew32/d").write("test"),  std::runtime_error);
}

TEST_F(FileopsTest, parseFileTest) {
  EXPECT_NO_THROW(Fileops1.parseFile());
  testing::internal::CaptureStdout();
  int returnOutput1 = Fileops1.parseFile();
  std::string output1 = testing::internal::GetCapturedStdout();

  int expected_returnOut_1 = 0;
  std::string expected_out_1 = "test\ntest2\ntest3\n";
  EXPECT_EQ(returnOutput1, expected_returnOut_1);
  EXPECT_EQ(output1, expected_out_1);

  EXPECT_NO_THROW(Fileops3.parseFile());
  testing::internal::CaptureStdout();
  int returnOutput3 = Fileops3.parseFile();
  std::string output3 = testing::internal::GetCapturedStdout();

  int expected_returnOut_3 = 0;
  std::string expected_out_3 = "Ballot\n";
  EXPECT_EQ(returnOutput3, expected_returnOut_3);
  EXPECT_EQ(output3, expected_out_3);

  EXPECT_THROW(Fileops("ads/asdfavab/ew32/d").parseFile(), std::runtime_error);
}


