/**
******************************************************************************
 * @file mpo.cc
 * @brief MPO implementation source file
 * @author Janani Kannan
******************************************************************************
*/

#include "mpo.h"

MPO::MPO() {
  // constructor
  linecount = 0;
  electionType = "MPO";
}

MPO::~MPO() {}

void MPO::processElectables() {
  std::string electablesInfo = this->getElectablesInfo();
  std::stringstream ss(electablesInfo);
  std::string line;

  std::getline(ss, line);

  linecount = 3;
  int k = 0;
  int end_idx;
  int pos;

  while(k < this->electablesCount){
    // ***************************************************
    // find [candidate,party] pair
    end_idx = line.find("]");
    std::string pair = line.substr(1, end_idx-1);
    line.erase(0, end_idx+3);

    // remove leading space
    line.erase(0, line.find_first_not_of(" \t"));  
    
    // remove trailing space
    line.erase(line.find_last_not_of(" \n\r\t")+1,
    (line.size()-line.find_last_not_of(" \n\r\t")));

    // ***************************************************

    // find party and candidate names
    pos = pair.find(",");
    std::string candidateName = pair.substr(0, pos);
    pair.erase(0, pos+1);

    // remove leading space
    pair.erase(0, pair.find_first_not_of(" \t"));  
    
    // remove trailing space
    pair.erase(pair.find_last_not_of(" \n\r\t")+1,
    (pair.size()-pair.find_last_not_of(" \n\r\t")));

    std::string partyName = pair;

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
    std::cout << candidateName << std::endl;


    k++;
  }

  sort list of candidates by voteCount
  std::sort(this->electables.begin(), this->electables.end(),
    [&](Electable* c1, Electable* c2){
        return (c1->getVotes() >= c2->getVotes());
    }
  );

  this->partyCount = parties.size();
  linecount++;
    
}

void MPO::countVotes() {
  std::string votes = this->ballotInfo;
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
          return (c1->getVotes() >= c2->getVotes());
      }
    );
    p->setCandidates(candidates);
  }

}


void MPO::display() {
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

void MPO::calculateResults() {
  // electables (candidates) already sorted
  std::vector<Electable*> candidates = this->electables;

  // ties to be resolved
  std::map<int, std::vector<Electable*>> toResolveTies; 
  
  int voteCount;
  for(Electable* cand : candidates){
    voteCount = cand->getVotes();
    toResolveTies[voteCount].push_back(cand);

    // if(!(toResolveTies[voteCount] == NULL)){
    //   toResolveTies[voteCount].push_back(cand);
    // } else {
    //   std::vector<Electable*> e;
    //   e.push_back(cand);
    //   toResolveTies[voteCount] = e;
    // }
  }

  std::vector<Electable*> finalCandidates;
  int idx = 0;

  std::map<int, std::vector<Electable*>>::iterator it = toResolveTies.begin();
  while(it != toResolveTies.end()){
    if((it->second).size() > 1){
      Electable* e = this->resolveTie(it->second);
      finalCandidates[idx] = e;
      // toResolveTies[it->first] = e;
    } else {
      finalCandidates[idx] = toResolveTies[it->first][0];
    }
    ++it;
    ++idx;
  }

  std::vector<Electable*> winners;
  int seatsLeft = this->seatCount;
  idx = 0;

  while(seatsLeft > 0){
    winners.push_back(finalCandidates[idx]);
    idx += 1;
    seatsLeft -= 1;
  }
  this->winners = winners;

}

std::vector<Party*> MPO::getParties() {
  // write me
  return this->parties;
  // return *new std::vector<Party*>;
}

std::vector<Candidate*> MPO::getWinners() {
  // write me
  return this->winners;
}


int MPO::parseFile() {
  int ret = 0;
  for (const std::string f : this->filenames) {
    this->fname = f;
    ret = ret | _parseFile();
  }
  return ret;
}


int MPO::_parseFile() {
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

  if (file.is_open()) {
    // extract the election type header
    getline(file, line);
    this->electionType = line.substr(0, 3);

    // extract the number of seat count
    getline(file, line);
    this->seatCount = std::stoi(line);

    // extract the number of Candidates count
    getline(file, line);
    this->electablesCount = std::stoi(line);

    // candidate party pairs
    getline(file, line);
    // std::cout << line << std::endl;
    this->electablesInfo = line;
    // std::cout << this->electablesInfo << std::endl;

    // ballot count
    getline(file, line);
    this->ballotCount = std::stoi(line);

    // read and extract all ballot information given the ballot count
    lines.str("");
    for (int i = 0; i < this->ballotCount; i++) {
      getline(file, line);
      lines << line + "\n";
    }
    this->ballotInfo = lines.str();

    file.close();
    return 0;
  } else {
    throw std::runtime_error("Unable to open file: " + this->fname);
  }
}
