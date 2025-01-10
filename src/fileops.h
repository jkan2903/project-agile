/**
 * @file fileops.h
 * @brief Fileops header file
 * @author Leo Dong
 */

#ifndef FILEOPS_H
#define FILEOPS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @class Fileops
 * @brief An utility class for all general file operation functions
 */
class Fileops {
 public:
  /// @brief Creates a fileops object with default file path value
  Fileops();

  /**
   * @brief Creates a fileops object with a given file path
   * @param[in] filenames A vector string indicating the file locations
  */
  Fileops(std::vector<std::string> filenames);
  /**
   * @brief Creates a fileops object with a given file path
   * @param[in] filename A string indicating the file location
  */
  Fileops(std::string filename);
  /// @brief destructor
  virtual ~Fileops();

  /**
   * @brief Gets the filename that has been extracted from provided file path
   * @return a string indicating the filename
  */
  std::string getFilename();
  /**
   * @brief moves to process the next file in the vector
  */
  void nextFile();

  /**
   * @brief A helper founction to check file extension is .csv
   * @return a int indicating whether it is true or false
  */
  int checkCSVFormat();

  /**
   * @brief Writes a given string to the file at the file path
   * @param[in] writeable A intended string being written to the file  
   * @return a int indicating whether the process is success or not 
  */
  virtual int write(std::string writeable);

  /**
   * @brief Parse or read the file at the file path
   * @return a int indicating whether the process is success or not 
  */
  virtual int parseFile();

 protected:
  /// @brief String that represents the file path
  std::string fname = "Unknown";
  /// @brief Vector string that represents the file names
  std::vector<std::string> filenames;
  /// @brief which file we're on
  int fileidx = 0;

 private:
  /// @brief Have we written to the out file yet
  bool hasWritten = false;
};

#endif
