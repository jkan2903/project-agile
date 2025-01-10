/** 
 * @file fileops.cc
 * @brief
 * @author Leo Dong
 */

#include "fileops.h"

Fileops::Fileops() {}

Fileops::Fileops(std::vector<std::string> filenames) {
  this->fileidx = 0;
  this->filenames = filenames;
  this->fname = this->filenames.at(this->fileidx);
}

Fileops::Fileops(std::string filename) {
  std::vector<std::string> filesnames;
  filenames.push_back(filename);
  this->fileidx = 0;
  this->filenames = filenames;
  this->fname = this->filenames.at(this->fileidx);
}

Fileops::~Fileops() { }

std::string Fileops::getFilename() {
  std::string f;
  std::size_t slashPos = this->fname.find_last_of('/');
  if (slashPos != std::string::npos) {
    f = this->fname.substr(slashPos + 1);
  } else {
    f = this->fname;
  }
  return f;
}

int Fileops::checkCSVFormat() {
  // locate the position of the last '.' char to extract the
  //  file extension from filename
  std::size_t dotPos = this->fname.find_last_of('.');
  std::string fileExtention;
  if (dotPos != std::string::npos) {
    fileExtention = this->fname.substr(dotPos + 1);
    if (fileExtention != "csv") {
      throw std::runtime_error("Only .csv file is allowed");
    }
  } else {
    throw std::runtime_error("Incorrect file name format");
  }
  return 0;
}

int Fileops::write(std::string writeable) {
  // First writes should clear out a file
  if (!this->hasWritten) {
    std::ofstream file(this->fname, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
      file.close();
    }
    this->hasWritten = true;
  }
  std::ofstream file(this->fname, std::ios::out | std::ios::app);
  std::string line;

  if (file.is_open()) {
    file << writeable + "\n";
    file.close();
    return 0;
  } else {
    std::cerr << "Unable to open file: " << this->fname << std::endl;
    exit(1);
  }
}

void Fileops::nextFile() {
  this->fileidx++;
  if (this->fileidx < static_cast<int>(this->filenames.size())) {
    this->fname = this->filenames.at(this->fileidx);
  } else {
    this->fname = nullptr;
  }
  this->hasWritten = false;
}

int Fileops::parseFile() {
  std::ifstream file(this->fname);
  std::string line;

  // generically read lines and print on screen
  if (file.is_open()) {
    while (getline(file, line)) {
      std::cout << line << std::endl;
    }
    file.close();
    return 0;
  } else {
    std::cerr << "Unable to open file: " << this->fname << std::endl;
  }
  return -1;
}
