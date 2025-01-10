/**
******************************************************************************
 * @file mpo.h
 * @brief MPO implementation header file
 * @author Janani Kannan
******************************************************************************
*/

#ifndef MPO_H
#define MPO_H

#include "votingsystem.h"
#include <map>

/// @brief Calculates an MPO election
class MPO : public VotingSystem{
 public:
  /// @brief constructor
  MPO();
  MPO(std::string filename);
  MPO(std::vector<std::string> filenames);

  /// @brief destructor
  ~MPO();
  /// @brief Called first, reads in ballots
  void processElectables() override;
  /// @brief Called second, assigns votes to electables
  void countVotes() override;
  /// @brief Called third, implements the MPO calculation equation
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

  #ifdef VTEST
  using VotingSystem::totalVotes;
  using VotingSystem::electables;
  #endif

 protected:
  std::vector<Party*> parties;
  std::vector<Electable*> winners;
  
};

#endif
