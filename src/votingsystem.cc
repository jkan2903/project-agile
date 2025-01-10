#include "votingsystem.h"
/**
 * @file votingsystem.cc
 * @brief VotingSystem Interface source file
 * @author Janani Kannan
 */

VotingSystem::~VotingSystem() {
}

int VotingSystem::getBallotCount() {
  return this->ballotCount;
}

int VotingSystem::getSeatCount() {
  return this->seatCount;
}

int VotingSystem::getPartyCount() {
  return this->partyCount;
}

int VotingSystem::getCandidateCount() {
  return this->candidateCount;
}

std::string VotingSystem::getBallotInfo() {
  return this->ballotInfo;
}

// void VotingSystem::setBallotData(RawData newData) {
//   this->ballots = newData;
// }

int VotingSystem::addElectable(Electable* toAdd) {
  this->electables.push_back(toAdd);
  return 0;
}

std::string VotingSystem::getElectionType() {
  return this->electionType;
}

Electable* VotingSystem::resolveTie(std::vector<Electable*> electables) {
  int idx = rand() % electables.size();
  return electables.at(idx);
}

void VotingSystem::setFilenames(std::vector<std::string> filenames) {
  this->filenames = filenames;
}

void VotingSystem::setFname(std::string filename) {
  this->fname = filename;
}

// int VotingSystem::parseFile() {
//   int ret = 0;
//   for (const std::string f : this->filenames) {
//     this->fname = f;
//     ret = ret | _parseFile();
//   }
//   return ret;
// }

int VotingSystem::checkCSVFormat() {
  // locate the position of the last '.' char to extract the
  //  file extension from filename
  std::size_t dotPos = this->fname.find_last_of('.');
  std::string fileExtention;
  if (dotPos != std::string::npos) {
    fileExtention = this->fname.substr(dotPos + 1);
    if (fileExtention != "csv") {
      throw std::runtime_error("Only .csv file is allowed");
    }
  } else {
    throw std::runtime_error("Incorrect file name format");
  }
  return 0;
}


void VotingSystem::readElectionType(std::ifstream *file) {
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
    std::cerr << "File name: " << this->fname << std::endl;
    std::cerr << "Expected election type" << std::endl;
    exit(1);
  }
}

void VotingSystem::readSeatCount(std::ifstream *file) {
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
      std::cerr << "Could not convert `" << line << "` to integer (Seat count)" << std::endl;
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

void VotingSystem::readBallotCount(std::ifstream *file) {
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
      std::cerr << "Could not convert `" << line << "` to integer (Ballot count)" << std::endl;
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

void VotingSystem::readElectableCount(std::ifstream *file) {
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
      std::cerr << "Could not convert `" << line << "` to integer (Electable count)" << std::endl;
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

void VotingSystem::readElectables(std::ifstream *file) {
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
  if (this->electablesInfo.compare("") == 0) {
    this->electablesInfo = lines.str();
  } else if (this->electablesInfo.compare(lines.str()) != 0) {
    std::cerr << "On lines " << lstart << " to " << linecount << std::endl;
    std::cerr << "Expected electables to match" << std::endl;
    exit(1);
  }
}

void VotingSystem::readBallots(std::ifstream *file) {
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


// int VotingSystem::_parseFile() {
//   try {
//     checkCSVFormat();
//   } catch (const std::exception &e) {
//     std::cerr << "File should be of type .csv" << std::endl;
//     std::cerr << e.what() << std::endl;
//     exit(1);
//   }

//   std::ifstream file(this->fname);
//   try {
//     file.exceptions(std::ifstream::failbit|std::ifstream::badbit);
//   } catch (std::ios_base::failure &e) {
//     std::cerr << "ios failure" << std::endl;
//     std::cerr << "It is likely that the file does not exist" << std::endl;
//     std::cerr << e.what() << std::endl;
//     std::cerr << e.code() << std::endl;
//     exit(1);
//   }
//   std::string line;
//   std::stringstream lines;

//   this->linecount = 0;

//   if (file.good() && file.is_open()) {
//     // Line 1 (all)
//     // extract the election type header
//     readElectionType(&file);

//     // Line 2 (all)
//     // extract the number of seat count
//     readSeatCount(&file);

//     // Line 3 (opl, cpl)
//     // extract the number of ballots if OPL or CPL
//     if (this->getElectionType().compare("OPL") == 0 || this->getElectionType().compare("CPL") == 0) {
//       readBallotCount(&file);
//     }

//     // Line 4 (opl, cpl) / 3 (mv, mpo)
//     // extract the number of electables(Party or Candidate) count
//     readElectableCount(&file);

//     // Line 5 (opl, cpl) / 4 (mv, mpo)
//     // read lines and extract all electables(Party or Candidate) information
//     readElectables(&file);

//     // Line 6 (opl, cpl) / 5 (mv, mpo)
//     // extract the number of ballots if MPO or MV
//     if (this->getElectionType().compare("MPO") == 0 || this->getElectionType().compare("MV") == 0) {
//       readBallotCount(&file);
//     }

//     // Line 6 (all)
//     // read and extract all ballot information given the ballot count
//     readBallots(&file);

//     file.close();
//     return 0;
//   } else {
//     std::cerr << "Unable to open file: " << this->fname << std::endl;
//     exit(1);
//   }
//   return -1;
// }

