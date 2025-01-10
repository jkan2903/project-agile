/**
 ******************************************************************************
 * @file cpl.h
 * @brief CPL implementation header file
 * @author Janani Kannan
 ******************************************************************************
*/

#ifndef CPL_H
#define CPL_H

#include "votingsystem.h"
  
/// @brief Calculates a Closed Party Listing election
class CPL : public VotingSystem {
 public:
  /// @brief constructor
  CPL();
  /**
   * @brief Creates a fileops object with a given file path
   * @param[in] filename A string indicating the file location
  */
  CPL(std::string filename);
  CPL(std::vector<std::string> filenames);
  
  /// @brief destructor
  ~CPL();
  /// @brief Called first, reads in ballots
  void processElectables() override;
  /// @brief Called second, assigns votes to electables
  void countVotes() override;
  /// @brief Called third, implements the CPL calculation equation
  void calculateResults() override;
  /// @brief displays results
  void display() override;
  /// @brief Returns the parties involved
  /// @return std::vector of Party pointers
  std::vector<Party*> getParties() override;
  /// @brief Returns the candidates involved
  /// @return std::vector of Candidate pointers
  std::vector<Candidate*> getWinners() override;
  /// @brief Overriden. Parsefile function to parse all necessary information from a CSV ballot file
  /// @return An integer indicating success/failure of the file parse process
  int parseFile() override;

  int _parseFile() override;
  // void readElectionType(std::ifstream *file);  /// @bug document and test me
  // void readSeatCount(std::ifstream *file);  /// @bug document and test me
  // void readBallotCount(std::ifstream *file);  /// @bug document and test me
  // void readElectableCount(std::ifstream *file);  /// @bug document and test me
  // void readElectables(std::ifstream *file);  /// @bug document and test me
  // void readBallots(std::ifstream *file);  /// @bug document and test me

  // uncomment for manually testing protected variables
  #ifdef VTEST
  using VotingSystem::totalVotes;
  // uncomment for manually testing protected variables
  using VotingSystem::electables;
  #endif
};

#endif
