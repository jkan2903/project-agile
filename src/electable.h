/**
 * @file electable.h
 * @brief Electable header file
 * @author Alex Johnson
 * @author Ashwin Wariar
 */

#ifndef ELECTABLE_H
#define ELECTABLE_H

#include <vector>
#include <string>
#include <random>
#include <functional>


class Party;
class Candidate;

/**
 * @class Electable
 * @brief Virtual class that amasses votes after an election and
 *  calculates seat totals and allocations based on the election type      
 */
class Electable {
 public:
  /**
   * @brief Gets the votes for either a candidate or party
   * @return int votes, the votes for either a candidate or party
   */
  int getVotes();
  /**
   * @brief Increments the votes by 1 for either a party or candidate
   */
  void incVotes();
  /**
   * @brief Adds a specific number of votes to either a candidate or party
   * @param votes Integer number of votes to add
   */
  void addVotes(int votes);
  /**
   * @brief Gets the first allocation of seats from the quota in the election
   * @param int firstAllocation, which is the number of seats given
   *  in the first allocation
   */
  int getFirstAllocation();
  /**
   * @brief Sets the first allocation of seats from the quota in the election
   * @param first_allocation Integer number of seats given
   *  in the first allocation
   */
  void setFirstAllocation(int first_allocation);
  /**
   * @brief Gets the second allocation of seats from the quota in the election
   * @return int secondAllocation, which is the number of seats given
   *  in the second allocation
   */
  int getSecondAllocation();
  /**
   * @brief Sets the second allocation of seats from the quota in the election
   * @param second_allocation Integer number of seats given
   *  in the second allocation
   */
  void setSecondAllocation(int second_allocation);
  /// @brief Increments the second allocation of seats by 1
  void incSecondAllocation();
  /**
   * @brief Gets the name of either a party or candidate
   * @return std::string name, which is the name of either a party or candidate
   */
  virtual std::string getName() = 0;
  /**
   * @brief Sets the name to either the name of a party or name of a candidate
   * @param new_name std::string, the human name of the party or candidate
   */
  virtual void setName(std::string new_name) = 0;
  /// @brief A virtual function that either prints the party with its
  ///  candidates or the candidate with its affiliated party
  virtual std::string toString() = 0;

 protected:
  /// @brief Denotes every vote cast for either a party or candidate
  ///  based on election type
  int votes = 0;
  /// @brief A string that represents the name of either a party or candidate
  ///  based on the election type
  std::string name = "";
  /// @brief Denotes the number of seats allocated for the first allocation
  int firstAllocation = 0;
  /// @brief Denotes the number of seats allocated for the second allocation
  int secondAllocation = 0;
};

#endif
