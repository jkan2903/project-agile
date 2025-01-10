/** 
 * @file electable.cc
 * @brief Electable source file
 * @author Ashwin Wariar
 */

#include "electable.h"


int Electable::getVotes() {
  return this->votes;
}

void Electable::incVotes() {
  this->votes += 1;
}

void Electable::addVotes(int votes) {
  this->votes += votes;
}

int Electable::getFirstAllocation() {
  return this->firstAllocation;
}

void Electable::setFirstAllocation(int first_allocation) {
  this->firstAllocation = first_allocation;
}

int Electable::getSecondAllocation() {
  return this->secondAllocation;
}

void Electable::setSecondAllocation(int second_allocation) {
  this->secondAllocation = second_allocation;
}

void Electable::incSecondAllocation() {
  this->secondAllocation += 1;
}

std::string Electable::getName() {
  return this->name;
}
