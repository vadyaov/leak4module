#ifndef DATASET_H_
#define DATASET_H_

#include "release.h"

#include <iomanip>

class Dataset {
  public:
    Dataset() {}

    void LoadData(const std::string& filename); // loads releases and times from concrete file

    friend std::ostream& operator<<(std::ostream& os, const Dataset& data) {
      os << "DATASET:\n";
      os << std::setw(12);
      for (double moment : data.times_) {
        os << moment;
        os << std::setw(10);
      }
      os << std::setw(0);
      os << std::endl;

      for (const Release& rel : data.releases_){
        os << rel;
      }

      return os;
    }

  private:
    std::vector<Release> releases_;
    std::vector<double> times_;
};

#endif // DATASET_H_