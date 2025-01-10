/**
 * @file main.cc
 * @brief Gets filename via cmd or gui, Runs the rest of the election
 * @author Alex Johnson
 */

#include "guiwindow.h"
#include "election.h"

/**
 * @details Gets filename from command line or opens Window <br>
 * Creates an Election, runs it, audits it, and displays the results.
 * @param[in] argc Integer number of arguments
 * @param[in] argv String array of arguments
 * @return Integer status
 */
int main(int argc, char *argv[]) {
  std::vector<std::string>filenames;

  // Get filename
  if (argc < 2) {
    // Prompt user with GUI until a file is selected
    while (static_cast<int>(filenames.size()) < 1) {
      try {
        // Apparently this line is needed to keep gtk happy
        auto app = Gtk::Application::create(argc, argv);
        guiWindow gui;
        filenames = gui.getFilenames();
      } catch (...) {
        // If gtk doesn't work
        std::cout << "Cannot display window. Please enter filenames" << std::endl;
        std::string f;
        std::cin >> f;
        std::stringstream ff(f);
        while (getline(ff, f, ' ')) {
          filenames.push_back(f);
        }
      }
    }
  } else {
    for (int i = 1; i < argc; i++) {
      filenames.push_back(argv[i]);
    }
  }

  // Do everything else
  Election election(filenames);
  election.doElection();
  election.doAudit();
  election.display();

  return 0;
}
