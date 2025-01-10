/**
 * @file guiwindow.cc
 * @brief Opens a file selector gui
 * @author Alex Johnson
 */

#include "guiwindow.h"

guiWindow::guiWindow() {
  Gtk::FileChooserDialog dialog("Please select one or more files",
    Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);
  dialog.set_select_multiple(true);

  // Add response buttons the the dialog:
  dialog.add_button("_Open", Gtk::RESPONSE_OK);

  // Add filters, so that only certain file types can be selected:
  auto filter_cpp = Gtk::FileFilter::create();
  filter_cpp->set_name("Ballot files");
  filter_cpp->add_mime_type("text/x-csv");
  dialog.add_filter(filter_cpp);

  // Show the dialog and wait for a user response:
  int result = dialog.run();

  // Handle the response:
  switch (result) {
    case (Gtk::RESPONSE_OK):
      // Save filename
      this->filenames = dialog.get_filenames();
      break;
    default:
      break;
  }
}

guiWindow::~guiWindow() {
}

std::vector<std::string> guiWindow::getFilenames() {
  return this->filenames;
}
