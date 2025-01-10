/**
******************************************************************************
* @file	votingsystemfactory.cc
* @brief Voting System Factory class source file
* @author Janani Kannan
******************************************************************************
*/

#include "votingsystemfactory.h"

VotingSystemFactory::VotingSystemFactory() {
}

VotingSystemFactory::~VotingSystemFactory() {
}

VotingSystem* VotingSystemFactory::newVotingSystem(std::vector<std::string> filenames) {
  std::vector<VotingSystem*> vss; 
  std::string filename = filenames[0];
  std::string electionType;
  std::ifstream file;
  file.open(filename);
  std::string line;
  if (file.good() && file.peek() != EOF) {
    try {
      getline(file, line);
      line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
    } catch (std::ifstream::failure &e) {
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
    electionType = line;
  }else {
    std::cerr << "Found end of file" << std::endl;
    std::cerr << "File name: " << filename << std::endl;
    std::cerr << "Expected election type" << std::endl;
    exit(1);
  }

  if (electionType.compare("OPL") == 0) {
    OPL* oplObj = new OPL();
    oplObj->setFilenames(filenames);
    return oplObj;
  }

  if (electionType.compare("CPL") == 0) {
    CPL* cplObj = new CPL();
    cplObj->setFilenames(filenames);
    return cplObj;
  }

  if (electionType.compare("MPO") == 0) {
    MPO* mpoObj = new MPO();
    mpoObj->setFilenames(filenames);
    return mpoObj;
  }

  if (electionType.compare("MV") == 0) {
    MV* mvObj = new MV();
    mvObj->setFilenames(filenames);
    return mvObj;
  }
  
  // throw std::runtime_error("Bad election type: " + electionType);
  std::cerr << "Bad election type: " << electionType << std::endl;
  exit(1);
  return nullptr;  // NULL returned if unexpected election type found
}

VotingSystem *VotingSystemFactory::newVotingSystem(std::string filename) {
  std::vector<std::string> filenames;
  filenames.push_back(filename);
  return newVotingSystem(filenames);
}
