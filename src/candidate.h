/**
 * @file candidate.h
 * @brief Candidate header file
 * @author Alex Johnson
 * @author Ashwin Wariar
 */

#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "electable.h"
#include "party.h"

// #include <vector>
// #include <string>

/**
 * @class Candidate
 * @brief Represents a Candidate in the Voting system.
 *  Candidates can be added to parties,
 *  and can view what party they are in.
 */
class Candidate : public Electable {
 public:
    /// @brief Constructor that takes in the name to denote the name
    ///  of the candidate
    Candidate(std::string name);
    /// @brief Destructor for instantiations of Candidates that deletes
    ///  dynamically allocated memory.
    ~Candidate();
    /**  
     * @brief Sets the candidate to the specified party
     * @param party Party* to add as a participant
    */
    void setParty(Party* party);
    /**  
     * @brief Gets the party that the candidate is currently in
     * @param Party* party
     * @return Returns the Party object if there is a party,
     *  returns NULL if the party has not been set yet
    */
    Party* getParty();
    /**  
     * @brief Prints the candidate name followed by the party name
     * @return A string that has the candidate name followed by party name
    */
    std::string toString();
    /**
     * @brief Gets the name of a candidate
     * @return name std::string which is the name of a candidate
     */
    std::string getName();
    /**
     * @brief Sets the name of a candidate
     * @param new_name std::string the name of the candidate
     */
    void setName(std::string new_name);


 protected:
    /// @brief Party pointer that is used to set the party
    Party* party = NULL;
    /// @brief String that represents candidate name
    std::string name = "";
};

#endif
