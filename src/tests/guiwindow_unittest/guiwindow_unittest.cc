#include "gtest/gtest.h"
#include "../../guiwindow.h"

class guiWindowTest : public::testing::Test {
  public:
    void SetUp() {
      
    }
    void TearDown() {
      
    }
};

TEST_F(guiWindowTest, createWindowTest) {
  std::cout << "Close the window or select a file" << std::endl;
  EXPECT_NO_THROW(auto app = Gtk::Application::create());
  auto app = Gtk::Application::create();
  EXPECT_NO_THROW(guiWindow winTest);
}

TEST_F(guiWindowTest, getFNameFromWindowTest) {
  std::cout << "You must select a .csv file" << std::endl;
  std::string fname = "";
  while (fname == "") {
    auto app = Gtk::Application::create();
    guiWindow gui;
    EXPECT_NO_THROW(fname = gui.getFilename());
    fname = gui.getFilename();
  }
  ASSERT_FALSE(fname.compare("") == 0);
  ASSERT_EQ(".csv", fname.substr(fname.size() - 4));
}
