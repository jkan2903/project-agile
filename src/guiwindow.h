/**
 * @file guiwindow.h
 * @brief guiWindow header file
 * @author Alex Johnson
 */

#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include <gtkmm.h>

/**
 * @brief Class to open a file selector gui
 * @details Opens a file selector gui. <br>
 * Only allows .csv files to be selected
 */
class guiWindow : public Gtk::Window {
 public:
  /// @brief Constructor, creates and displays the window
  guiWindow();
  /// @brief Destructor, nothing needed
  virtual ~guiWindow();
  /**
   * @brief Get filenames selected by user
   * @return vector string filename
   */
  std::vector<std::string> getFilenames();

 protected:
  /// @brief filenames Vector of strings specified by user
  std::vector<std::string> filenames;
};

#endif
