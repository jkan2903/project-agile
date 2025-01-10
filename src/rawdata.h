/**
 * @file rawdata.h
 * @brief RawData header file
 * @author Alex Johnson, Janani Kannan, Leo Dong
 */

#ifndef RAWDATA_H
#define RAWDATA_H

//#include <string>
#include <sstream>
#include "fileops.h"

/**
 * @class RawData
 * @brief A more specific class inheriting the Fileops class.
 *  It extracts information from a .csv ballot file and stores all the
 *  necessary fields for an election, such as the election type,
 *  number of seats, number of ballots, number of candidates,
 *  or number of parties, etc.  
 */
class RawData : public Fileops {
 public:
  #ifdef VTEST
  friend class RawDataTest;
  #endif

  /// @brief default constructor
  RawData();
  /** 
   * @brief Creates a RawData object with given file paths
   * @param[in] filenames Vector string indicating the file locations
   */
  RawData(std::vector<std::string> filenames);
  /** 
   * @brief Creates a RawData object with given file path
   * @param[in] filename string indicating the file location
   */
  RawData(std::string filename);
  /**
   * @brief Gets the election type
   * @return A string, which represents the election type.
   *  Either be "OPL", "CPL", or ""
  */
  std::string getElectionType();

  /**
   * @brief Gets the number of parties or the number candidates in an election
   * @return A integer represents the number of parties or
   *  the number candidates
  */
  int getElectablesCount();

  /**
   * @brief Gets the number of ballot count
   * @return A integer represents the number of ballots in the ballot file
  */
  int getBallotCount();

  /**
   * @brief Gets the number of seats being voted in an election
   * @return A integer represents the number of seats
  */
  int getSeatCount();

  /**
   * @brief Gets the raw data information of all the parties and candidates. 
   * @return A string that contains all the information.
  */
  std::string getElectablesInfo();

  /**
   * @brief Gets the raw data information of all ballots
   * @return A string taht contains all the information.
  */
  std::string getBallotInfo();

  /**
   * @brief The overridden parsefile function.
   *  It is deactivated by throwing an error to prevent the ballot file
   *  from being overwritten.
   * @return A integer indicating the success of read process
  */
  int write(std::string writeable) override;

  /** 
   * @brief The overridden parsefile function to parse all necessary
   *  information from a ballot file
   * @return A integer indicating the success of file parse process
   */
  int parseFile() override;

  /// @brief helper to parseFile
  int _parseFile();
  void readElectionType(std::ifstream *file);  /// @bug document and test me
  void readSeatCount(std::ifstream *file);  /// @bug document and test me
  void readBallotCount(std::ifstream *file);  /// @bug document and test me
  void readElectableCount(std::ifstream *file);  /// @bug document and test me
  void readElectables(std::ifstream *file);  /// @bug document and test me
  void readBallots(std::ifstream *file);  /// @bug document and test me

 protected:
  /// @brief String that represents the election type
  std::string electionType = "";
  /// @brief Integer that represents the number of seat in the election
  int seatCount = -1;
  /// @brief Integer that represents the number of ballots
  int ballotCount = -1;
  /// @brief Integer that represents the number of parties or
  ///  number of candidates
  int electablesCount = -1;

  /**
   * @brief String the represents the parties and candidates.
   *  The parties and their candidates are in the 
   * ranked order of preference by the party, and each line represents a party
  */
  std::string electables = "";
  /**
   * @brief String that represents the all ballots
  */
  std::string ballotInfo = "";
 private:
  int linecount;

};

#endif
