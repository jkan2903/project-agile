/**
 * @file audit.cc
 * @brief Writes election information to an audit file
 * @author Alex Johnson
 */

#include "audit.h"

Audit::Audit(VotingSystem* vSystem) {
  this->vSystem = vSystem;
  std::vector<std::string> filenames;
  filenames.push_back(this->filename);
  this->fileops = new Fileops(filenames);
  this->out = "";
}

Audit::~Audit() {
}

// Call helpers to write everything to audit file
int Audit::writeResults() {
  this->out += "<!DOCTYPE html>\n";
  this->out += "<html dir=\"ltr\" lang=\"en\">\n";
  this->out += "<body>\n";
  this->out += writeElectionType();
  this->out += writePartyCount();
  this->out += writeBallotCount();
  this->out += writeSeatCount();
  this->out += writeAllParties();
  this->out += writeEquation();
  this->out += writeTable();
  this->out += writeWinners();
  this->out += "</body>\n";
  this->out += "</html>\n";
  return this->fileops->write(this->out);
}

std::string Audit::writeElectionType() {
  std::string o = "<p>";
  o += "Election type: ";
  o += this->vSystem->getElectionType();
  o += "</p>\n";
  return o;
}

std::string Audit::writePartyCount() {
  std::string o = "<p>";
  o += "Party count: ";
  o += std::to_string(this->vSystem->getPartyCount());
  o += "</p>\n";
  return o;
}

std::string Audit::writeBallotCount() {
  std::string o = "<p>";
  o += "Ballot count: ";
  o += std::to_string(this->vSystem->getBallotCount());
  o += "</p>\n";
  return o;
}

std::string Audit::writeSeatCount() {
  std::string o = "<p>";
  o += "Seat count: ";
  o += std::to_string(this->vSystem->getSeatCount());
  o += "</p>\n";
  return o;
}

// Loop over the parties, calling helper
std::string Audit::writeAllParties() {
  std::string o = "";
  std::vector<Party*> parties = this->vSystem->getParties();
  for (Party *party : parties) {
    o += writeParty(party);
  }
  return o;
}

std::string Audit::writeParty(Party *party) {
  std::string o = "<p>";
  o += party->toString();
  o += "</p>\n";
  return o;
}

std::string Audit::writeEquation() {
  std::string o = "<p><math display=\"inline\"><mfrac><mn>";
  o += std::to_string(this->vSystem->getBallotCount());
  o += "</mn><mn>";
  o += std::to_string(this->vSystem->getSeatCount());
  o += "</mn></mfrac><mo>=</mo><mn>";
  if (this->vSystem->getSeatCount() < 1) {
    std::cerr << "seatCount is less than 1" << std::endl;
    exit(1);
  }
  o += std::to_string(this->vSystem->getBallotCount() /
    this->vSystem->getSeatCount());
  o += "</mn></math></p>\n";
  return o;
}

// Do a pretty little html table
std::string Audit::writeTable() {
  std::vector<Party*> parties = this->vSystem->getParties();
  std::string o = "<style>";
  o += ".tb { border-collapse: collapse; width:100%; }";
  o += ".tb th, .tb td { padding: 5px; border: solid 1px #777; }";
  o += ".tb th { background-color: lightblue; }";
  o += "</style>";
  o += "<table class=\"tb\"><tr><th>Parties</th>";
  o += "<th>Votes</th>";
  o += "<th>First Allocation of Seats</th>";
  o += "<th>Remaining Votes</th>";
  o += "<th>Second Allocation of Seats</th>";
  o += "<th>Final Seat Total</th>";
  o += "<th>% of Vote to % of Seats</th></tr>";
  // Each party gets a new row
  if (this->vSystem->getSeatCount() < 1) {
    std::cerr << "seatCount is less than 1" << std::endl;
    exit(1);
  }
  if (this->vSystem->getBallotCount() < 1) {
    std::cerr << "ballotCount is less than 1" << std::endl;
    exit(1);
  }
  for (Party *party : parties) {
    o += "<tr><td>";
    o += party->getName();
    o += "</td><td>";
    o += std::to_string(party->getVotes());
    o += "</td><td>";
    o += std::to_string(party->getFirstAllocation());
    o += "</td><td>";
    o += std::to_string(party->getVotes() - (party->getFirstAllocation()*
      (this->vSystem->getBallotCount() / this->vSystem->getSeatCount())));
    o += "</td><td>";
    o += std::to_string(party->getSecondAllocation());
    o += "</td><td>";
    o += std::to_string(party->getSeats());
    o += "</td><td>";
    o += std::to_string(100*(static_cast<double>(party->getVotes()) /
      static_cast<double>(this->vSystem->getBallotCount()))).substr(0, 5);
    o += "% to ";
    o += std::to_string(100*(static_cast<double>(party->getSeats()) /
      static_cast<double>(this->vSystem->getSeatCount()))).substr(0, 5);
    o += "%</td></tr>";
  }
  o +="</table>\n";
  return o;
}

std::string Audit::writeWinners() {
  std::vector<Candidate*> winners = this->vSystem->getWinners();
  std::string o = "<p>Winners:</p>";
  for (Candidate *cand : winners) {
    o += "<p>";
    o += cand->toString();
    // OPL also gives candidates' votes
    if (this->vSystem->getElectionType().compare("OPL") == 0) {
      o += " got ";
      o += std::to_string(cand->getVotes());
      o += " votes";
    }
    o +="</p>";
  }
  return o;
}
