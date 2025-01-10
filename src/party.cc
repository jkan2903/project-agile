/** 
 * @file party.cc
 * @brief Party source file
 * @author Ashwin Wariar
 */

#include "party.h"
#include "candidate.h"

Party::Party(std::string name) {
  this->name = name;
}

Party::~Party() {
}

int Party::addCandidate(Candidate* candidate) {
  int index = -1;
  candidates.push_back(candidate);
  for (int i = 0; i < static_cast<int>(candidates.size()); i++) {
    // Checks that candidate being added is the same as the
    //  candidate in the vector
    if (candidates.at(i) == candidate) {
      index = i;
    }
  }
  return index;
}

std::vector<Candidate*> Party::getCandidates() {
  return this->candidates;
}

void Party::setCandidates(const std::vector<Candidate*>& candidates) {
  this->candidates = candidates;
}

Candidate* Party::getCandidate(int candidate) {
  return candidates.at(candidate);
}

int Party::getCandidateCount() {
  return candidates.size();
}

std::string Party::toString() {
  // Party name first followed by "- ["
  std::string result = this->name + " - [";
  for (int i = 0; i < static_cast<int>(candidates.size()); i++) {
    result += (candidates.at(i))->getName();  // Adds candidate name
    // If there are multiple candidates, add commas
    if (i < (static_cast<int>(candidates.size()) - 1)) {
      result += ", ";
    }
  }
  result += "]";  // End with "]"
  return result;
}

int Party::getSeats() {
  return this->seats;
}

void Party::setSeats(int seats) {
  this->seats = seats;
}

void Party::incSeats() {
  this->seats += 1;
}

int Party::getRemainder() {
  return this->remainder;
}

void Party::setRemainder(int remainder) {
  this->remainder = remainder;
}

std::string Party::getName() {
  return this->name;
}

void Party::setName(std::string new_name) {
  this->name = new_name;
}
