/**
 * @file audit.h
 * @brief Audit header file
 * @author Alex Johnson
 */

#ifndef AUDIT_H
#define AUDIT_H

#include "votingsystemfactory.h"
#include "fileops.h"

/**
 * @brief Writes election information to an audit file
 * @details Structure as follows: <br>
 * 1. OPL or CPL <br>
 * 2. Party count <br>
 * 3. Ballot count <br>
 * 4. Seat count <br>
 * 5. Candidates' names and party affiliation (group by parties) <br>
 * 6. Equation for calculation of remainders followed by table <br>
 * <table>
 *  <tr>
 *   <th>Parties</th>
 *   <th>Votes</th>
 *   <th>First Allocation of Seats</th>
 *   <th>Remaining Votes</th><th>Second Allocation of Seats</th>
 *   <th>Final Seat Total</th>
 *   <th>% of Vote to % of Seats</th>
 *  </tr>
 *  <tr>
 *   <td>Republican</td>
 *   <td>38,000</td>
 *   <td>3</td>
 *   <td>8,000</td>
 *   <td>1</td>
 *   <td>4</td>
 *   <td>38% / 40%</td>
 *  </tr>
 *  <tr>
 *   <td>Democratic</td>
 *   <td>23,000</td>
 *   <td>2</td>
 *   <td>3,000</td>
 *   <td>0</td>
 *   <td>2</td>
 *   <td>23% / 20%</td>
 *  </tr>
 *  <tr>
 *   <td>Reform</td>
 *   <td>21,000</td>
 *   <td>2</td>
 *   <td>1,000</td>
 *   <td>0</td>
 *   <td>2</td>
 *   <td>21% / 20%</td>
 *  </tr>
 *  <tr>
 *   <td>Green</td>
 *   <td>12,000</td>
 *   <td>1</td>
 *   <td>2,000</td>
 *   <td>0</td>
 *   <td>1</td>
 *   <td>12% / 10%</td>
 *  </tr>
 *  <tr>
 *   <td>Moll</td>
 *   <td>6,000</td>
 *   <td>0</td>
 *   <td>6,000</td>
 *   <td>1</td>
 *   <td>1</td>
 *   <td>6% / 10%</td>
 *  </tr>
 * </table>
 * 7. List of seat winners and party affiliations. OPL also lists votes per candidate
 */
class Audit : public Fileops {
 public:
    /** 
     * @brief wrapper class on VotingSystem to write information to set audit file
     * @param[in] vSystem VotingSystem which contains all election data
     */
    Audit(VotingSystem* vSystem);
    /// @brief Destructor
    ~Audit();
    /**
     * @brief Writes election results to audit file
     * @return integer Status
     */
    int writeResults();

 public:
    /**
     * @brief Helper class to write OPL or CPL election type
     * @return string produced
     */
    std::string writeElectionType();
    /**
     * @brief Helper class to write number of parties
     * @return string produced
     */
    std::string writePartyCount();
    /**
     * @brief Helper class to write number of ballots
     * @return string produced
     */
    std::string writeBallotCount();
    /**
     * @brief Helper class to write number of seats
     * @return string produced
     */
    std::string writeSeatCount();
    /**
     * @brief Helper class to write Parties, calls writeParty()
     * @return string produced
     */
    std::string writeAllParties();
    /**
     * @brief Writes a Party object to the audit file
     * @param[in] party Party object to write to file
     * @return string produced
     */
    std::string writeParty(Party *party);
    /**
     * @brief Helper class to write the remainder calculation
     * @return string produced
     */
    std::string writeEquation();
    /**
     * @brief Helper class to write the table
     * @return string produced
     */
    std::string writeTable();
    /**
     * @brief Helper class to write winners, party affiliations, and votes per candidate if OPL
     * @return string produced
     */
    std::string writeWinners();

 private:
    /// @brief The voting system used
    VotingSystem *vSystem;
    /// @brief Fileops for writing to files
    Fileops *fileops;
    /// @brief the string to write
    std::string out;
    /// @brief the filename to write to
    std::string filename = "audit.html";
};

#endif
