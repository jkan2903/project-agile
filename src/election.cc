/** 
 * @file election.cc
 * @brief Assembles, runs, and displays the election
 * @author Alex Johnson
 */

#include "election.h"

Election::Election(std::vector<std::string> filenames) {
  VotingSystemFactory *vsf = new VotingSystemFactory();
  this->vSystem = vsf->newVotingSystem(filenames);
  this->audit = new Audit(this->vSystem);
}

Election::Election(std::string filename) {
  std::vector<std::string> filenames;
  filenames.push_back(filename);
  VotingSystemFactory *vsf = new VotingSystemFactory();
  this->vSystem = vsf->newVotingSystem(filenames);
  this->audit = new Audit(this->vSystem);
}

Election::~Election() {
}

void Election::doElection() {
  this->vSystem->doElection();
}

void Election::doAudit() {
  this->audit->writeResults();
}

void Election::display() {
  this->vSystem->display();
}
