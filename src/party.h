/**
 * @file party.h
 * @brief Party header file
 * @author Alex Johnson
 * @author Ashwin Wariar
 */

#ifndef PARTY_H
#define PARTY_H

#include "electable.h"
#include "candidate.h"

// #include <vector>
// #include <string>

/**
 * @class Party
 * @brief Represents a Party in the Voting system.
 *  Parties have a vector list of Candidates and can add Candidates.
 */
class Party : public Electable {
 public:
  /// @brief Constructor that takes in a name to denote the name of the party
  Party(std::string name);
  /// @brief Destructor for instantiations of Parties that deletes
  ///  dynamically allocated memory
  ~Party();
  /**  
   * @brief Adds a Candidate to the vector of candidates in the party
   * @param[in] candidate Candidate* to add to election
   * @return Returns an int that represents its index in the vector of
   *  candidates, returns -1 if fail
  */
  int addCandidate(Candidate *candidate);
  /**  
   * @brief Gets the vector of candidates
   * @return std::vector<candidate*> candidates
  */
  std::vector<Candidate*> getCandidates();
  /**
   * @brief Sets the vector of candidates associated with a party
   * @param[in] candidates std::vector<Candidate*>&,
   *  which is a reference of a candidate vector
  */
  void setCandidates(const std::vector<Candidate*>& candidates);
  /**  
   * @brief Gets a Candidate from the vector of candidates based on their
   *  index in the vector of candidates
   * @param[in] candidate Integer which represents their index in the vector
   *  list of candidates
   * @return Candidate object of the candidate
  */
  Candidate* getCandidate(int candidate);
  /**  
   * @brief Gets the number of candidates in a party
   * @return int that represents the number of candidates in the party
  */
  int getCandidateCount();
  /**  
   * @brief Prints the party name along with each of the candidates
   * @return A string that has the party name followed by the names
   *  of each candidate
  */
  std::string toString();
  /**
   * @brief Gets the number of seats allocated to a party
   * @return int seats, the number of seats given to a party
  */
  int getSeats();
  /**
   * @brief Sets the number of seats allocated to a party
   * @param[in] seats Integer which is the number of seats set to be
   *  allocated to a party
  */
  void setSeats(int seats);
  /// @brief Increments the number of seats allotted to a party by 1
  void incSeats();
  /**
   * @brief Gets the remainder of seats
   * @return int remainder, which represents the remainder of seats
  */
  int getRemainder();
  /**
   * @brief Sets the remainder of seats
   * @param[in] remainder Integer remainder of seats given to the function
  */
  void setRemainder(int remainder);
  /**
   * @brief Gets the name of a party
   * @return std::string name, which is the name of a party
   */
  std::string getName();
  /**
   * @brief Sets the name of a party
   * @param[in] new_name std::string, the name of the party
   */
  void setName(std::string new_name);

 protected:
  /// @brief Vector of type Candidate pointers that stores all the
  ///  candidates in a party
  std::vector<Candidate*> candidates;
  /// @brief String that represents the name of the party
  std::string name = "";
  /// @brief Remainder after first round of seat allocation
  int remainder = 0;
  /// @brief The number of seats that a party gets throughout an election
  int seats = 0;
};

#endif
