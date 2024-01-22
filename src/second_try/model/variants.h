#pragma once

#include "release.h"

#include <iostream>

class Variants {
  public:
    Variants() {}

    void LoadData(const std::string& path) {
      releases_.clear();
      dir_names_.clear();

      std::string dir_path;
      for (const auto& dir_entry : std::filesystem::directory_iterator{path}) {
        if (dir_entry.is_directory()) {
          // std::cout << "Getting release from " << dir_entry.path().string() << "\n";
          dir_path = dir_entry.path().string();
          releases_.push_back(dir_path + '/');
          dir_names_.push_back(dir_path.substr(dir_path.find_last_of('\\') + 1));
        }
      }
    }

    Release FindMaxForAll(Release::Way way) const noexcept {
      std::vector<double> total_releases(releases_.size());
      for (std::size_t i = 0; i != releases_.size(); ++i) {
        total_releases[i] = releases_[i].TotalRelease(way);
      }
      int index = std::distance(total_releases.begin(), std::max_element(total_releases.begin(), total_releases.end()));
      for (double m : total_releases)
        std::cout << m << " ";

      std::cout << "\nMax variant is " << dir_names_[index] << "\n";
      return releases_[index];
    }

    Release FindMaxForNuclide(Release::Way way, Nuclide::Tp form) {
      std::vector<double> total_releases(releases_.size());
      for (std::size_t i = 0; i != releases_.size(); ++i) {
        total_releases[i] = releases_[i].TotalOneFormRelease(way, form);
      }
      int index = std::distance(total_releases.begin(), std::max_element(total_releases.begin(), total_releases.end()));
      for (double m : total_releases)
        std::cout << m << " ";

      std::cout << "\nMax variant is " << dir_names_[index] << "\n";
      return releases_[index];
    }

    const std::vector<std::string>& GetNames() const noexcept {
      return dir_names_;
    }

    void print(int w) const {
      for (std::size_t i = 0; i != releases_.size(); ++i) {
        std::cout << "DIR: " << dir_names_[i] << "\n";
        releases_[i].Print(w);
      }
    }

    int TotalNuclidesNumber() const { 
      if (releases_.empty()) throw std::runtime_error("No releases loaded");
      
      return releases_.back().TotalNuclidesNumber();
    }

    const std::vector<double>& GetTimeArray() const { 
      if (releases_.empty()) throw std::runtime_error("No releases loaded");

      return releases_.back().GetTimeVector();
    }

    int IodNum() const {
      if (releases_.empty()) throw std::runtime_error("No releases loaded");

      return releases_.back().IodineNumber();
    }

    int IrgNum() const {
      if (releases_.empty()) throw std::runtime_error("No releases loaded");

      return releases_.back().IrgNumber();
    }

    int AerNum() const {
      if (releases_.empty()) throw std::runtime_error("No releases loaded");

      return releases_.back().AerNumber();
    }

    std::vector<std::pair<std::string, Nuclides::dvector>> GetNuclideData(int variant_num, Release::Way way, Nuclide::Tp type) {
      return releases_[variant_num].GetNucData(way, type);
    }

  private:
    std::vector<Release> releases_; // releases[i] - release throw needed way for variant No. i + 1
    std::vector<std::string> dir_names_;

};
