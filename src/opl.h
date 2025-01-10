/**
******************************************************************************
 * @file opl.h
 * @brief OPL implementation header file
 * @author Janani Kannan
******************************************************************************
*/

#ifndef OPL_H
#define OPL_H

#include "votingsystem.h"

/// @brief Calculates an Open Party Listing election
class OPL : public VotingSystem{
 public:
  /// @brief constructor
  OPL();
  /**
   * @brief Creates a fileops object with a given file path
   * @param[in] filename A string indicating the file location
  */
  OPL(std::string filename);
  OPL(std::vector<std::string> filenames);

  /// @brief destructor
  ~OPL();
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

  #ifdef VTEST
  using VotingSystem::totalVotes;
  using VotingSystem::electables;
  #endif

  int _parseFile() override;
  // void readElectionType(std::ifstream *file);  /// @bug document and test me
  // void readSeatCount(std::ifstream *file);  /// @bug document and test me
  // void readBallotCount(std::ifstream *file);  /// @bug document and test me
  // void readElectableCount(std::ifstream *file);  /// @bug document and test me
  // void readElectables(std::ifstream *file);  /// @bug document and test me
  // void readBallots(std::ifstream *file);  /// @bug document and test me


 protected:
  /// @brief The parties involved in the election.
  ///  OPL is candidate based, though candidates are still associated
  ///  with a party
  std::vector<Party*> parties;
};

#endif
