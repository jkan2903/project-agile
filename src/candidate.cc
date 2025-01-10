/** 
 * @file candidate.cc
 * @brief Candidate source file
 * @author Ashwin Wariar
 */

#include "candidate.h"


Candidate::Candidate(std::string name) {
  this->name = name;
}

Candidate::~Candidate() {
}

void Candidate::setParty(Party* party) {
  this->party = party;
}

Party* Candidate::getParty() {
  return this->party;
}

std::string Candidate::toString() {
  std::string party_result = "";
  if (this->party == NULL) {
    // If party hasn't been set, give the candidate "No party"
    party_result = "No party";
    } else {
    party_result = this->party->getName(); // Otherwise, give the party
  }
  std::string result = this->name + " - " + party_result;
  return result;
}

std::string Candidate::getName() {
  return this->name;
}

void Candidate::setName(std::string new_name) {
  this->name = new_name;
}
