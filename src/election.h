/**
 * @file election.h
 * @brief Election header file
 * @author Alex Johnson
 */

#ifndef ELECTION_H
#define ELECTION_H

#include "audit.h"

/**
 * @brief Collects election attributes and runs the election
 */
class Election {
 public:
  /**
   * @brief Creates an election
   * @param[in] filenames vector String name of ballot files
   */
  Election(std::vector<std::string> filenames);
  /**
   * @brief Creates an election
   * @param[in] filename String name of ballot file
   */
  Election(std::string filename);
  /// @brief destructor
  ~Election();
  /// @brief Run the election
  void doElection();
  /// @brief Run the audit of the election
  void doAudit();
  /// @brief Display election results
  void display();

 protected:
  /// @brief The voting system to be used, OPL or CPL
  VotingSystem* vSystem;
  /// @brief The Audit wrapper on VotingSystem
  Audit* audit;
};

#endif
