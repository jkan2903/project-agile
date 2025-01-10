/**
 * @file votingsystem.h
 * @brief VotingSystem header file
 * @author Alex Johnson
 * @author Janani Kannan
 */

#ifndef VOTINGSYSTEM_H
#define VOTINGSYSTEM_H

// uncomment the following line for manually testing protected variables purpose
#ifdef VTEST
#include "gtest/gtest.h"
#endif
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include "party.h"

/**
 * @details Creates a virtual voting system realized by OPL or CPL. <br>
 * File information is stored in RawData
 */
class VotingSystem {
 public:
  /// @brief destructor
  virtual ~VotingSystem();

  /// @brief How many votes were cast
  /// @return Integer vote count
  int getBallotCount();

  /// @brief How many seats are available in an election
  /// @return Integer seat count
  int getSeatCount();

  /// @brief How many parties are participating
  /// @return Integer party count
  int getPartyCount();

  /// @brief How many candidates are participating
  /// @return Integer candidate count
  int getCandidateCount();

  /// @brief The internal representation of ballot file info
  /// @return A string capturing all ballot infor
  std::string getBallotInfo();

  /// @brief How a voting system acquires ballots
  /// @param[in] data RawData object to read election information from
  // void setBallotData(RawData data);

  void setFilenames(std::vector<std::string> filenames);

  /// @brief Flips a coin to break ties between participants
  /// @param[in] electables Vector of Electables to break a tie between
  /// @return Electable tie winner
  Electable* resolveTie(std::vector<Electable*> electables);

  /// @brief Adds participants to an election
  /// @param[in] toAdd Electable object to make a participant
  /// @return Integer status
  int addElectable(Electable* toAdd);
  
  /// @brief Get all participants in an election
  /// @return Vector of Electable participants in the election
  std::vector<Electable*> getElectables() {return this->electables;}

  /// @brief Get all participants in string format in an election
  /// @return A string capturing all Electable participants in the election
  std::string getElectablesInfo() {return this->electablesInfo;}

  virtual int parseFile() = 0;
  virtual int _parseFile() = 0;
  void readElectionType(std::ifstream *file);  /// @bug document and test me
  void readSeatCount(std::ifstream *file);  /// @bug document and test me
  void readBallotCount(std::ifstream *file);  /// @bug document and test me
  void readElectableCount(std::ifstream *file);  /// @bug document and test me
  void readElectables(std::ifstream *file);  /// @bug document and test me
  void readBallots(std::ifstream *file);  /// @bug document and test me

  /// @brief Overriden. Parsefile function to parse all necessary information from a CSV ballot file
  /// @return An integer indicating success/failure of the file parse process
  // virtual int parseFile() = 0;
  /// @brief Overriden. Parsefile function to parse all necessary information from a CSV ballot file
  /// @return An integer indicating success/failure of the file parse process
  // virtual int _parseFile() = 0;
  // virtual void readElectionType(std::ifstream *file);  /// @bug document and test me
  // virtual void readSeatCount(std::ifstream *file);  /// @bug document and test me
  // virtual void readBallotCount(std::ifstream *file);  /// @bug document and test me
  // virtual void readElectableCount(std::ifstream *file);  /// @bug document and test me
  // virtual void readElectables(std::ifstream *file);  /// @bug document and test me
  // virtual void readBallots(std::ifstream *file);  /// @bug document and test me

  /**
   * @brief moves to process the next file in the vector
  */
  void nextFile();

  /**
   * @brief A helper founction to check file extension is .csv
   * @return a int indicating whether it is true or false
  */
  int checkCSVFormat();


  /// @brief Overridden. Returns participating parties
  /// @return Vector of participating Party objects
  virtual std::vector<Party*> getParties() = 0;

  /// @brief Overridden. Get winning Candidates
  /// @return Vector of Candidate winners
  virtual std::vector<Candidate*> getWinners() = 0;

  /// @brief calls the methods associated with an election
  void doElection() {
    parseFile();
    processElectables();
    countVotes();
    calculateResults();
  }
  /// @brief Overridden. Called first to process the ballot file
  virtual void processElectables() = 0;
  /// @brief Overridden. Called second to assign votes to participants
  virtual void countVotes() = 0;
  /// @brief Overridden. Called third to calculate the election results
  virtual void calculateResults() = 0;
  /// @brief Overridden. Display election results
  virtual void display() = 0;

  /// @brief Get which type of election this object represents
  /// @return String election type. OPL or CPL
  std::string getElectionType();
  void setFname(std::string filename);

 protected:
  /// @brief Number of participating parties
  int partyCount = 0;
  /// @brief Number of participating candidates
  int candidateCount = 0;
  /// @brief Number of votes cast in election
  int totalVotes = 0;

  /// Refactoring all fileops and rawdata code into votingsystem for a better design

  /// @brief String that represents the file path
  std::string fname = "Unknown";
  /// @brief Vector string that represents the file names
  std::vector<std::string> filenames;
  /// @brief which file we're on
  int fileidx = 0;

  /// @brief String representing parties and candidates.;
  std::string electablesInfo;

  /// @brief std::vector<Electable*> electables;
  std::vector<Electable*> electables;

  /// @brief String that represents the election type
  std::string electionType = "";
  /// @brief Integer that represents the number of seat in the election
  int seatCount = -1;
  /// @brief Integer that represents the number of ballots
  int ballotCount = -1;
  /// @brief Integer that represents the number of parties or
  ///  number of candidates
  int electablesCount = -1;
  /// @brief String that represents all the ballots
  std::string ballotInfo;
  
  int linecount;
  
  // uncomment the following line for manually testing protected variables purpose
  #ifdef VTEST
  friend class ::testing::Test;
  #endif

};

#endif
