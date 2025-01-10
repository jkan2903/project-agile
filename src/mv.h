/**
******************************************************************************
 * @file mv.h
 * @brief MV header source file
 * @author Janani Kannan
 * @bug rewrite me, I am just mv right now
******************************************************************************
*/

#ifndef MV_H
#define MV_H

#include "votingsystem.h"

/// @brief Calculates an Open Party Listing election
class MV : public VotingSystem {
 public:
  /// @brief constructor
  MV();
  MV(std::string filename);
  MV(std::vector<std::string> filenames);

  /// @brief destructor
  ~MV();
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
  // int parseFile() override;
  // uncomment for manually testing protected variables
  #ifdef VTEST
  using VotingSystem::totalVotes;
  // uncomment for manually testing protected variables
  using VotingSystem::electables;
  #endif

 protected:
  /// @brief The parties involved in the election.
  ///  OPL is candidate based, though candidates are still associated
  ///  with a party
  std::vector<Party*> parties;
  
};

#endif
