/**
******************************************************************************
 * @file opl.cc
 * @brief OPL implementation source file
 * @author Janani Kannan
 * @author Alex Johnson
******************************************************************************
*/

#include "opl.h"

OPL::OPL() {
  // constructor
  linecount = 0;
  electionType = "OPL";
}

OPL::~OPL() {};

void OPL::processElectables() {
  std::string electablesInfo = this->getElectablesInfo();
  std::stringstream ss(electablesInfo);
  std::string line;

  int linecount = 4;
  while (std::getline(ss, line)) {
    linecount++;
    std::string partyName;

    int pos = line.find(",");
    if (pos < 0) {
      std::cerr << "Could not find comma on line " << linecount << std::endl;
      exit(1);
    }
    partyName = line.substr(0, pos);
    line.erase(0, pos+1);  // 1 is the length of the delimiter, ","
    line.erase(0, line.find_first_not_of(" \t"));  // remove leading space
    // remove trailing space
    line.erase(line.find_last_not_of(" \n\r\t")+1,
    (line.size()-line.find_last_not_of(" \n\r\t")));

    std::string candidateName = line;

    Candidate* newCandidate = new Candidate(candidateName);
    Party* party;

    bool partySet = false;
    // check if this party already exists
    for (Party* p : this->parties) {
      if (p->getName() == partyName) {
        party = p;
        partySet = true;
        break;
      }
    }

    if (!(partySet)) {
      party = new Party(partyName);
      this->parties.push_back(party);
    }

    party->addCandidate(newCandidate);
    newCandidate->setParty(party);
    this->candidateCount += 1;

    this->addElectable(dynamic_cast<Electable*> (newCandidate));
  }
  this->partyCount = parties.size();
}

// vote counting
void OPL::countVotes() {
  std::string votes = this->getBallotInfo();
  // given a string with multiple lines
  // each line ends with \n
  std::stringstream ss(votes);
  std::string line;
  int linecount = 8;
  while (std::getline(ss, line)) {
    linecount++;
    // look at one line, find the index of the 1
    int pos = line.find("1");

    // for fault tolerance
    if (this->electables.size() == 0) {
      break;
    }
    if (pos < 0 || pos >= static_cast<int>(this->electables.size())) {
      std::cerr << "Invalid vote on line " << linecount << std::endl;
      exit(1);
    }
    Candidate* cand = dynamic_cast<Candidate*>(this->electables[pos]);

    // access Electables to update the appropriate candidate's votecount
    cand->incVotes();
    // the party votecount is also incremented
    cand->getParty()->incVotes();
    this->totalVotes += 1;
  }

    // sort each party's candidates list so they are ranked 
    // in order of most to least votes received
    // simultaneously increment partyCount
    // resolve any ties as necessary
    std::vector<Candidate*> candidates;
    std::vector<Electable*> toResolveTies;
    std::vector<Candidate*> finalCandidates;
    for(Party* p : this->parties){
      candidates = p->getCandidates();
      std::sort(candidates.begin(), candidates.end(),
        [&](Candidate* c1, Candidate* c2){
            return (c1->getVotes() > c2->getVotes());
        }
      );
      p->setCandidates(candidates);
    }
}

void OPL::calculateResults() {
  // integer division rounds down
  if (this->getSeatCount() < 1) {
    std::cerr << "seatCount is less than 1" << std::endl;
    exit(1);
  }
  int quota = this->totalVotes / this->getSeatCount();
  if (quota < 1) {
    std::cerr << "quota is less than 1" << std::endl;
    exit(1);
  }

  // sort parties list in order of most to least number of votes
  std::sort(this->parties.begin(), this->parties.end(),
    [&](Party* p1, Party* p2) {
      return (p1->getVotes() > p2->getVotes());
    });

  int votes;
  int remainder;
  int firstAllocation;
  int seats = this->getSeatCount();

  for (Party* p : this->parties) {
    if (seats > 0) {
      votes = p->getVotes();
      firstAllocation = votes / quota;
      // Don't allocate more seats than candidates
      if (firstAllocation > p->getCandidateCount()) {
        firstAllocation = p->getCandidateCount();
      }
      p->setFirstAllocation(firstAllocation);
      p->setSeats(firstAllocation);

      seats -= firstAllocation;

      remainder = votes - (firstAllocation*quota);
      p->setRemainder(remainder);
    } else {
      break;
    }
  }

  // arrange parties in order of largest to smallest remainder
  std::sort(this->parties.begin(), this->parties.end(),
    [&](Party* p1, Party* p2) {
      return (p1->getRemainder() > p2->getRemainder());
    });

  // SECOND ALLOCATION
  // keep allocating seats in this order
  // inc by 1 each time
  int iter = 0;
  int skipped = 0;
  while (seats > 0 && skipped < static_cast<int>(parties.size())) {
    if (iter == this->partyCount) {
      iter = 0;
    }

    Party* currParty = parties[iter];
    if (currParty->getSeats() < currParty->getCandidateCount()) {
      currParty->incSeats();
      currParty->incSecondAllocation();
      seats -= 1;
      skipped = 0;
    } else {
      skipped++;  // Just in case there are more seats than candidates
    }
    iter += 1;
  }
}

std::vector<Party*> OPL::getParties() {
  return this->parties;
}

std::vector<Candidate*> OPL::getWinners() {
  std::vector<Party*> _parties = this->getParties();
  // sort parties by seats
  std::sort(_parties.begin(), _parties.end(),
    [&](Party* p1, Party* p2) {
      return (p1->getSeats() > p2->getSeats());
    });

  std::vector<Candidate*> winners;
  std::vector<Candidate*> candidates;
  int seatsCount;

  for (Party* p : _parties) {
    seatsCount = p->getSeats();
    if (seatsCount != 0) {
      candidates = p->getCandidates();
      for (int i = 0; i < seatsCount; i++) {
        winners.push_back(candidates.at(i));
      }
    }
  }
  return winners;
}

// void OPL::readElectionType(std::ifstream *file) {
//   std::string line;
//   linecount++;
//   if (file->good() && file->peek() != EOF) {
//     try {
//       getline(*file, line);
//       line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
//     } catch (std::ifstream::failure &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Could not read line from file" << std::endl;
//       std::cerr << e.what() << std::endl;
//       std::cerr << e.code() << std::endl;
//       exit(1);
//     }
//       // remove leading whitespace
//     line.erase(0, line.find_first_not_of(" \t"));
//     // Remove trailing whitespace
//     line.erase(line.find_last_not_of(" \n\r\t")+1,
//       (line.size()-line.find_last_not_of(" \n\r\t")));
//     if (this->electionType.compare("") == 0) {
//       this->electionType = line;
//     } else if (this->electionType.compare(line) != 0) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Found different election type: " << line << std::endl;
//       exit(1);
//     }
//   } else {
//     std::cerr << "On line " << linecount << std::endl;
//     std::cerr << "Found end of file" << std::endl;
//     std::cerr << "File name: " << this->fname << std::endl;
//     std::cerr << "Expected election type" << std::endl;
//     exit(1);
//   }
// }

// void OPL::readSeatCount(std::ifstream *file) {
//   std::string line;
//   linecount++;
//   if (file->good() && file->peek() != EOF) {
//     try {
//       getline(*file, line);
//       line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
//     } catch (std::ifstream::failure &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Could not read line from file" << std::endl;
//       std::cerr << e.what() << std::endl;
//       std::cerr << e.code() << std::endl;
//       exit(1);
//     }
//     try {
//       if (this->seatCount == -1) {
//         this->seatCount = std::stoi(line);
//       } else if (this->seatCount != std::stoi(line)) {
//         std::cerr << "On line " << linecount << std::endl;
//         std::cerr << "Found different seat count: " << line << std::endl;
//         exit(1);
//       }
//       if (this->seatCount < 1) {
//         std::cerr << "On line " << linecount << std::endl;
//         std::cerr << "seatCount is less than 1" << std::endl;
//         exit(1);
//       }
//     } catch (std::invalid_argument &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Could not convert `" << line << "` to integer" << std::endl;
//       std::cerr << e.what() << std::endl;
//       exit(1);
//     } catch (std::out_of_range &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "`" << line << "` out of range" << std::endl;
//       std::cerr << e.what() << std::endl;
//       exit(1);
//     }
//   } else {
//     std::cerr << "On line " << linecount << std::endl;
//     std::cerr << "Found end of file" << std::endl;
//     std::cerr << "Expected seat count" << std::endl;
//     exit(1);
//   }
// }

// void OPL::readBallotCount(std::ifstream *file) {
//   std::string line;
//   linecount++;
//   if (file->good() && file->peek() != EOF) {
//     try {
//       getline(*file, line);
//       line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
//     } catch (std::ifstream::failure &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Could not read line from file" << std::endl;
//       std::cerr << e.what() << std::endl;
//       std::cerr << e.code() << std::endl;
//       exit(1);
//     }
//     try {
//       this->ballotCount = std::stoi(line);  /// @bug Multiple files have different ballot counts, right?
//       if (this->ballotCount < 1) {
//         std::cerr << "On line " << linecount << std::endl;
//         std::cerr << "ballotCount is less than 1" << std::endl;
//         exit(1);
//       }
//     } catch (std::invalid_argument &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Could not convert `" << line << "` to integer" << std::endl;
//       std::cerr << e.what() << std::endl;
//       exit(1);
//     } catch (std::out_of_range &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "`" << line << "` out of range" << std::endl;
//       std::cerr << e.what() << std::endl;
//       exit(1);
//     }
//   } else {
//     std::cerr << "On line " << linecount << std::endl;
//     std::cerr << "Found end of file" << std::endl;
//     std::cerr << "Expected ballot count" << std::endl;
//     exit(1);
//   }
// }

// void OPL::readElectableCount(std::ifstream *file) {
//   std::string line;
//   linecount++;
//   if (file->good() && file->peek() != EOF) {
//     try {
//       getline(*file, line);
//       line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
//     } catch (std::ifstream::failure &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Could not read line from file" << std::endl;
//       std::cerr << e.what() << std::endl;
//       std::cerr << e.code() << std::endl;
//       exit(1);
//     }
//     try {
//       if (this->electablesCount == -1) {
//         this->electablesCount = std::stoi(line);
//       } else if (this->electablesCount != std::stoi(line)) {
//         std::cerr << "On line " << linecount << std::endl;
//         std::cerr << "Found different electablesCount: " << line << std::endl;
//         exit(1);
//       }
//       if (this->electablesCount < 1) {
//         std::cerr << "On line " << linecount << std::endl;
//         std::cerr << "electablesCount is less than 1" << std::endl;
//         exit(1);
//       }
//     } catch (std::invalid_argument &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Could not convert `" << line << "` to integer" << std::endl;
//       std::cerr << e.what() << std::endl;
//       exit(1);
//     } catch (std::out_of_range &e) {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "`" << line << "` out of range" << std::endl;
//       std::cerr << e.what() << std::endl;
//       exit(1);
//     }
//   } else {
//     std::cerr << "On line " << linecount << std::endl;
//     std::cerr << "Found end of file" << std::endl;
//     std::cerr << "Expected electableSCount" << std::endl;
//     exit(1);
//   }
// }

// void OPL::readElectables(std::ifstream *file) {
//   std::string line;
//   std::stringstream lines;
//   int lstart = linecount+1;
//   for (int i = 0; i < this->electablesCount; i++) {
//     linecount++;
//     if (file->good() && file->peek() != EOF) {
//       try {
//         getline(*file, line);
//         //line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
//       } catch (std::ifstream::failure &e) {
//         std::cerr << "On line " << linecount << std::endl;
//         std::cerr << "Could not read line from file" << std::endl;
//         std::cerr << e.what() << std::endl;
//         std::cerr << e.code() << std::endl;
//         exit(1);
//       }
//     } else {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Found end of file" << std::endl;
//       std::cerr << "Expected electables" << std::endl;
//       exit(1);
//     }
//     lines << line + "\n";
//   }
//   if (this->electablesInfo.compare("") == 0) {
//     this->electablesInfo = lines.str();
//   } else if (this->electablesInfo.compare(lines.str()) != 0) {
//     std::cerr << "On lines " << lstart << " to " << linecount << std::endl;
//     std::cerr << "Expected electables to match" << std::endl;
//     exit(1);
//   }
// }

// void OPL::readBallots(std::ifstream *file) {
//   std::string line;
//   std::stringstream lines;
//   for (int i = 0; i < this->ballotCount; i++) {  /// @bug could change this to while not EOF. Then Ballot count is just a hint (good for reading in more files)
//     linecount++;
//     if (file->good() && file->peek() != EOF) {
//       try {
//         getline(*file, line);
//         line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
//       } catch (std::ifstream::failure &e) {
//         std::cerr << "On line " << linecount << std::endl;
//         std::cerr << "Could not read line from file" << std::endl;
//         std::cerr << e.what() << std::endl;
//         std::cerr << e.code() << std::endl;
//         exit(1);
//       }
//     } else {
//       std::cerr << "On line " << linecount << std::endl;
//       std::cerr << "Found end of file" << std::endl;
//       std::cerr << "Expected ballot string" << std::endl;
//       exit(1);
//     }
//     lines << line + "\n";
//   }
//   this->ballotInfo += lines.str();
// }

int OPL::parseFile() {
  int ret = 0;
  for (const std::string& f : this->filenames) {
    this->fname = f;
    ret = ret | _parseFile();
  }
  return ret;
}

int OPL::_parseFile() {
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

void OPL::display() {
  std::cout << "Winners:" << std::endl;
  std::vector<Candidate*> winners = getWinners();
  for (Candidate *cand : winners) {
    std::cout << " " << cand->toString() << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Election type: " << getElectionType()
    << std::endl;
  std::cout << "Seat count: " << getSeatCount()
    << std::endl;
  std::cout << "Ballots cast: " << getBallotCount()
    << std::endl;
  std::cout << std::endl;
  std::cout << "All candidates: " << std::endl;
  std::vector<Party*> parties = getParties();
  if (getBallotCount() < 1) {
    std::cerr << "ballotCount is less than 1" << std::endl;
    exit(1);
  }
  for (Party *party : parties) {
    std::vector<Candidate*> cands = party->getCandidates();
    std::cout << " " << party->getName() << ": " << party->getVotes()
      << " votes or " << (static_cast<double>(party->getVotes()) /
      static_cast<double>(getBallotCount())) * 100
      << "%" << std::endl;
    for (Candidate *cand : cands) {
      std::cout << "  " << cand->getName();
      std:: cout << ": " << cand->getVotes() << " votes or "
        << (static_cast<double>(cand->getVotes()) /
        static_cast<double>(getBallotCount())) * 100 << "%"
        << std::endl;
    }
  }
}
