#include "variants.h"

void Variants::LoadData(const std::string& path) {
  releases_.clear();
  dir_names_.clear();

  std::string dir_path;
  for (const auto& dir_entry : std::filesystem::directory_iterator{path}) {
    if (dir_entry.is_directory()) {
      // std::cout << "Getting release from " << dir_entry.path().string() << "\n";
      dir_path = dir_entry.path().string();
      releases_.push_back(dir_path + '/');
      dir_names_.push_back(dir_path.substr(dir_path.find_last_not_of("0123456789") + 1));
    }
  }
}

const std::vector<std::string>& Variants::GetNames() const noexcept {
  return dir_names_;
}

void Variants::print(int w) const {
  for (std::size_t i = 0; i != releases_.size(); ++i) {
    std::cout << "DIR: " << dir_names_[i] << "\n";
    releases_[i].Print(w);
  }
}

int Variants::TotalNuclidesNumber() const { 
  if (releases_.empty()) throw std::runtime_error("No releases loaded");
  
  return releases_.back().TotalNuclidesNumber();
}

const std::vector<double>& Variants::GetTimeArray() const { 
  if (releases_.empty()) throw std::runtime_error("No releases loaded");

  return releases_.back().GetTimeVector();
}

int Variants::IodNum() const {
  if (releases_.empty()) throw std::runtime_error("No releases loaded");

  return releases_.back().IodineNumber();
}

int Variants::IrgNum() const {
  if (releases_.empty()) throw std::runtime_error("No releases loaded");

  return releases_.back().IrgNumber();
}

int Variants::AerNum() const {
  if (releases_.empty()) throw std::runtime_error("No releases loaded");

  return releases_.back().AerNumber();
}

std::vector<std::pair<std::string, Nuclides::dvector>> Variants::GetNuclideData(int variant_num, Release::Way way, Nuclide::Tp type) {
  return releases_[variant_num].GetNucData(way, type);
}

bool Variants::Empty() const noexcept { return releases_.empty(); }