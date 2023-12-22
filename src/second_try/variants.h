#pragma once

#include <filesystem>
#include "release.h"

#include <iostream>

class Variants {
  public:
    Variants(const std::string& path, int w) {
      for (const auto& dir_entry : std::filesystem::directory_iterator{path}) {
        if (dir_entry.is_directory()) {
          std::cout << "Getting release from " << dir_entry.path().string() << "\n";
          releases_.push_back({dir_entry.path().string() + '/', w});
        }
      }
    }

    void print() const {
      for (const Release& rel : releases_)
        rel.Print();
    }

  private:
    std::vector<Release> releases_; // releases[i] - release throw needed way for variant No. i + 1
};