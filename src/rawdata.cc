/**
* @file	rawdata.cc
* @brief RawData source file
* @author Janani Kannan, Leo Dong, Alex Johnson
*/

#include "rawdata.h"
#include <algorithm>

RawData::RawData() : Fileops() { this->linecount = 0; }

RawData::RawData(std::vector<std::string> filenames) : Fileops(filenames) { this->linecount = 0; }
RawData::RawData(std::string filename) : Fileops(filename) { this->linecount = 0; }

std::string RawData::getElectionType() {
  return this->electionType;
}

int RawData::getElectablesCount() {
  return this->electablesCount;
}

int RawData::getBallotCount() {
  return this->ballotCount;
}

int RawData::getSeatCount() {
  return this->seatCount;
}

std::string RawData::getElectablesInfo() {
  return this->electables;
}

std::string RawData::getBallotInfo() {
  return this->ballotInfo;
}

int RawData::write(std::string writeable) {
  // Overwrite the Fileops::write() method to ensure the integrity
  //  of the ballot files.
  throw std::runtime_error("The input file can not be modified.");
}

void RawData::readElectionType(std::ifstream *file) {
  std::string line;
  linecount++;
  if (file->good() && file->peek() != EOF) {
    try {
      getline(*file, line);
      line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
    } catch (std::ifstream::failure &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Could not read line from file" << std::endl;
      std::cerr << e.what() << std::endl;
      std::cerr << e.code() << std::endl;
      exit(1);
    }
      // remove leading whitespace
    line.erase(0, line.find_first_not_of(" \t"));
    // Remove trailing whitespace
    line.erase(line.find_last_not_of(" \n\r\t")+1,
      (line.size()-line.find_last_not_of(" \n\r\t")));
    if (this->electionType.compare("") == 0) {
      this->electionType = line;
    } else if (this->electionType.compare(line) != 0) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Found different election type: " << line << std::endl;
      exit(1);
    }
  } else {
    std::cerr << "On line " << linecount << std::endl;
    std::cerr << "Found end of file" << std::endl;
    std::cerr << "File name: " << this->getFilename() << std::endl;
    std::cerr << "Expected election type" << std::endl;
    exit(1);
  }
}

void RawData::readSeatCount(std::ifstream *file) {
  std::string line;
  linecount++;
  if (file->good() && file->peek() != EOF) {
    try {
      getline(*file, line);
      line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
    } catch (std::ifstream::failure &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Could not read line from file" << std::endl;
      std::cerr << e.what() << std::endl;
      std::cerr << e.code() << std::endl;
      exit(1);
    }
    try {
      if (this->seatCount == -1) {
        this->seatCount = std::stoi(line);
      } else if (this->seatCount != std::stoi(line)) {
        std::cerr << "On line " << linecount << std::endl;
        std::cerr << "Found different seat count: " << line << std::endl;
        exit(1);
      }
      if (this->seatCount < 1) {
        std::cerr << "On line " << linecount << std::endl;
        std::cerr << "seatCount is less than 1" << std::endl;
        exit(1);
      }
    } catch (std::invalid_argument &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Could not convert `" << line << "` to integer" << std::endl;
      std::cerr << e.what() << std::endl;
      exit(1);
    } catch (std::out_of_range &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "`" << line << "` out of range" << std::endl;
      std::cerr << e.what() << std::endl;
      exit(1);
    }
  } else {
    std::cerr << "On line " << linecount << std::endl;
    std::cerr << "Found end of file" << std::endl;
    std::cerr << "Expected seat count" << std::endl;
    exit(1);
  }
}

void RawData::readBallotCount(std::ifstream *file) {
  std::string line;
  linecount++;
  if (file->good() && file->peek() != EOF) {
    try {
      getline(*file, line);
      line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
    } catch (std::ifstream::failure &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Could not read line from file" << std::endl;
      std::cerr << e.what() << std::endl;
      std::cerr << e.code() << std::endl;
      exit(1);
    }
    try {
      this->ballotCount = std::stoi(line);  /// @bug Multiple files have different ballot counts, right?
      if (this->ballotCount < 1) {
        std::cerr << "On line " << linecount << std::endl;
        std::cerr << "ballotCount is less than 1" << std::endl;
        exit(1);
      }
    } catch (std::invalid_argument &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Could not convert `" << line << "` to integer" << std::endl;
      std::cerr << e.what() << std::endl;
      exit(1);
    } catch (std::out_of_range &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "`" << line << "` out of range" << std::endl;
      std::cerr << e.what() << std::endl;
      exit(1);
    }
  } else {
    std::cerr << "On line " << linecount << std::endl;
    std::cerr << "Found end of file" << std::endl;
    std::cerr << "Expected ballot count" << std::endl;
    exit(1);
  }
}

void RawData::readElectableCount(std::ifstream *file) {
  std::string line;
  linecount++;
  if (file->good() && file->peek() != EOF) {
    try {
      getline(*file, line);
      line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
    } catch (std::ifstream::failure &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Could not read line from file" << std::endl;
      std::cerr << e.what() << std::endl;
      std::cerr << e.code() << std::endl;
      exit(1);
    }
    try {
      if (this->electablesCount == -1) {
        this->electablesCount = std::stoi(line);
      } else if (this->electablesCount != std::stoi(line)) {
        std::cerr << "On line " << linecount << std::endl;
        std::cerr << "Found different electablesCount: " << line << std::endl;
        exit(1);
      }
      if (this->electablesCount < 1) {
        std::cerr << "On line " << linecount << std::endl;
        std::cerr << "electablesCount is less than 1" << std::endl;
        exit(1);
      }
    } catch (std::invalid_argument &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Could not convert `" << line << "` to integer" << std::endl;
      std::cerr << e.what() << std::endl;
      exit(1);
    } catch (std::out_of_range &e) {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "`" << line << "` out of range" << std::endl;
      std::cerr << e.what() << std::endl;
      exit(1);
    }
  } else {
    std::cerr << "On line " << linecount << std::endl;
    std::cerr << "Found end of file" << std::endl;
    std::cerr << "Expected electableSCount" << std::endl;
    exit(1);
  }
}

void RawData::readElectables(std::ifstream *file) {
  std::string line;
  std::stringstream lines;
  int lstart = linecount+1;
  for (int i = 0; i < this->electablesCount; i++) {
    linecount++;
    if (file->good() && file->peek() != EOF) {
      try {
        getline(*file, line);
        //line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
      } catch (std::ifstream::failure &e) {
        std::cerr << "On line " << linecount << std::endl;
        std::cerr << "Could not read line from file" << std::endl;
        std::cerr << e.what() << std::endl;
        std::cerr << e.code() << std::endl;
        exit(1);
      }
    } else {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Found end of file" << std::endl;
      std::cerr << "Expected electables" << std::endl;
      exit(1);
    }
    lines << line + "\n";
  }
  if (this->electables.compare("") == 0) {
    this->electables = lines.str();
  } else if (this->electables.compare(lines.str()) != 0) {
    std::cerr << "On lines " << lstart << " to " << linecount << std::endl;
    std::cerr << "Expected electables to match" << std::endl;
    exit(1);
  }
}

void RawData::readBallots(std::ifstream *file) {
  std::string line;
  std::stringstream lines;
  for (int i = 0; i < this->ballotCount; i++) {  /// @bug could change this to while not EOF. Then Ballot count is just a hint (good for reading in more files)
    linecount++;
    if (file->good() && file->peek() != EOF) {
      try {
        getline(*file, line);
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
      } catch (std::ifstream::failure &e) {
        std::cerr << "On line " << linecount << std::endl;
        std::cerr << "Could not read line from file" << std::endl;
        std::cerr << e.what() << std::endl;
        std::cerr << e.code() << std::endl;
        exit(1);
      }
    } else {
      std::cerr << "On line " << linecount << std::endl;
      std::cerr << "Found end of file" << std::endl;
      std::cerr << "Expected ballot string" << std::endl;
      exit(1);
    }
    lines << line + "\n";
  }
  this->ballotInfo += lines.str();
}

int RawData::parseFile() {
  int ret = 0;
  for (const std::string f : this->filenames) {
    this->fname = f;
    ret = ret | _parseFile();
  }
  return ret;
}

int RawData::_parseFile() {
  try {
    checkCSVFormat();
  } catch (const std::exception &e) {
    std::cerr << "File should be of type .csv" << std::endl;
    std::cerr << e.what() << std::endl;
    exit(1);
  }

  std::ifstream file(this->fname);
  try {
    file.exceptions(std::ifstream::failbit|std::ifstream::badbit);
  } catch (std::ios_base::failure &e) {
    std::cerr << "ios failure" << std::endl;
    std::cerr << "It is likely that the file does not exist" << std::endl;
    std::cerr << e.what() << std::endl;
    std::cerr << e.code() << std::endl;
    exit(1);
  }
  std::string line;
  std::stringstream lines;

  this->linecount = 0;

  if (file.good() && file.is_open()) {
    // Line 1 (all)
    // extract the election type header
    readElectionType(&file);

    // Line 2 (all)
    // extract the number of seat count
    readSeatCount(&file);

    // Line 3 (opl, cpl)
    // extract the number of ballots if OPL or CPL
    if (this->getElectionType().compare("OPL") == 0 || this->getElectionType().compare("CPL") == 0) {
      readBallotCount(&file);
    }

    // Line 4 (opl, cpl) / 3 (mv, mpo)
    // extract the number of electables(Party or Candidate) count
    readElectableCount(&file);

    // Line 5 (opl, cpl) / 4 (mv, mpo)
    // read lines and extract all electables(Party or Candidate) information
    readElectables(&file);

    // Line 6 (opl, cpl) / 5 (mv, mpo)
    // extract the number of ballots if MPO or MV
    if (this->getElectionType().compare("MPO") == 0 || this->getElectionType().compare("MV") == 0) {
      readBallotCount(&file);
    }

    // Line 6 (all)
    // read and extract all ballot information given the ballot count
    readBallots(&file);

    file.close();
    return 0;
  } else {
    std::cerr << "Unable to open file: " << this->fname << std::endl;
    exit(1);
  }
  return -1;
}
