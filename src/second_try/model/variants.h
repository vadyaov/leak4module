#pragma once

#include <filesystem>
#include "release.h"

#include <iostream>

class Variants {
  public:
    Variants() {}

    void LoadData(const std::string& path, int w) {
      for (const auto& dir_entry : std::filesystem::directory_iterator{path}) {
        if (dir_entry.is_directory()) {
          // std::cout << "Getting release from " << dir_entry.path().string() << "\n";
          releases_.push_back({dir_entry.path().string() + '/', w});
          dir_names_.push_back(dir_entry.path().string());
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

    void print(Release::Way w) const {
      for (const Release& rel : releases_)
        rel.Print(w);
    }

  private:
    std::vector<Release> releases_; // releases[i] - release throw needed way for variant No. i + 1
    std::vector<std::string> dir_names_;

};