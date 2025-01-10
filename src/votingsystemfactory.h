/**
******************************************************************************
* @file votingsystemfactory.h
* @brief Voting System Factory Class; creates Voting System objects
* @author Janani Kannan
******************************************************************************
*/

#ifndef VOTINGSYSTEMFACTORY_H
#define VOTINGSYSTEMFACTORY_H

#include "votingsystem.h"
#include "opl.h"
#include "cpl.h"
#include "mpo.h"
#include "mv.h"

/// @brief Determines election type and returns an OPL or CPL object
class VotingSystemFactory {
  public:
    /// @brief Constructor
    VotingSystemFactory();
    /// @brief Deconstructor
    ~VotingSystemFactory();
    /// @brief Reads election type to return the correct object
    /// @param[in] filenames Vector string name of ballot files to read
    /// @return Pointer of type VotingSystem - either on OPL or CPL object
    VotingSystem* newVotingSystem(std::vector<std::string> filenames);
    /// @brief Reads election type to return the correct object
    /// @param[in] filename string name of ballot file to read
    /// @return Pointer of type VotingSystem - either on OPL or CPL object
    VotingSystem* newVotingSystem(std::string filename);

  // protected:
      // @brief Internal ballot file parser and representation
      // RawData* ballots;
};

#endif
