/**
******************************************************************************
 * @file cpl.cc
 * @brief CPL implementation source file
 * @author Janani Kannan
 * @author Leo Dong
 * @author Alex Johnson
******************************************************************************
*/

#include "cpl.h"

CPL::CPL() {
  // constructor
  linecount = 0;
  electionType = "CPL";
}

CPL::~CPL() {};

void CPL::processElectables() {
  std::string electablesInfo = this->getElectablesInfo();
  std::stringstream ss(electablesInfo);
  std::string line;

  int linecount = 4;
  while (getline(ss, line)) {
    linecount++;
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(line);
    std::string candidateName;
    std::string partyName;

    while (std::getline(tokenStream, token, ',')) {
      size_t start = token.find_first_not_of(' ');
      if (start != std::string::npos) {
        token = token.substr(start);
      }
      tokens.push_back(token);
    }

    if (static_cast<int>(tokens.size()) < 1) {
      std::cerr << "No party name on line " << linecount << std::endl;
      exit(1);
    }
    if (static_cast<int>(tokens.size()) < 2) {
      std::cerr << "No candidate name on line " << linecount << std::endl;
      exit(1);
    }
    partyName = tokens.at(0);
    Party* party = new Party(partyName);
    this->addElectable(party);
    this->partyCount += 1;

    for (int i = 1; i < static_cast<int>(tokens.size()); i++) {
      // remove trailing space;
      candidateName = tokens[i].erase(tokens[i].find_last_not_of(" \n\r\t")+1,
        (tokens[i].size()-tokens[i].find_last_not_of(" \n\r\t")));
      Candidate* newCandidate = new Candidate(candidateName);
      newCandidate->setParty(party);
      this->candidateCount += 1;
      party->addCandidate(newCandidate);
    }
  }
}

// vote counting
void CPL::countVotes() {
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
    // access Electables to update the appropriate party's votecount
    this->electables.at(pos)->incVotes();
    this->totalVotes += 1;
  }
}

void CPL::calculateResults() {
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
  std::sort(this->electables.begin(), this->electables.end(),
    [&](Electable* p1, Electable* p2) {
      return (p1->getVotes() > p2->getVotes());
    });

  // FIRST ALLOCATION
  int votes;
  int remainder;
  int firstAllocation;
  int seats = this->getSeatCount();

  // need vector type Party* to set seats, remainders, etc.
  std::vector<Party*> parties = this->getParties();
  for (Party* p : parties) {
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
  std::sort(parties.begin(), parties.end(),
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

std::vector<Party*> CPL::getParties() {
  std::vector<Party*> parties(this->electables.size(), NULL);
  if (parties.size() != 0) {
    std::transform(this->electables.begin(), this->electables.end(),
    parties.begin(), [](Electable* e) { return dynamic_cast<Party*>(e);});
  }
  return parties;
}

std::vector<Candidate*> CPL::getWinners() {
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

void CPL::display() {
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
    // Cpl, for some reason, doesn't want to know how each candidate did
    for (Candidate *cand : cands) {
      std::cout << "  " << cand->getName() << std::endl;
    }
  }
}


int CPL::parseFile() {
  int ret = 0;
  for (const std::string& f : this->filenames) {
    this->fname = f;
    ret = ret | _parseFile();
  }
  return ret;
}


int CPL::_parseFile() {
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