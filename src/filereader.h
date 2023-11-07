#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "release.h"

class FileReader {
  public:
    FileReader(const std::string& filename) : istrm_{filename} {
      if (!istrm_.is_open())
        throw std::invalid_argument("Cant't open file");

    }

    std::vector<double> GetTimeArray() {
      std::string line;
      std::vector<double> times;
      bool timeline = false;
      while (std::getline(istrm_, line)) {
        if (timeline == true) {
          std::istringstream iss(line);
          while (!iss.eof()) {
            double value;
            iss >> value;
            times.push_back(value);
          }
          break;
        }

        if (line.find("Time of release") != line.npos) {
          timeline = true;
          std::getline(istrm_, line); // skip empty line
        }
      }
      return times;
    }

    std::vector<Release> GetData() {
      std::string line;
      std::vector<Release> releases;

      Isotope::Condition cond = Isotope::Condition::I_MOL;
      while (std::getline(istrm_, line)) {
        if (!line.empty()) {
          if (line.find("IRG") != line.npos) {
            cond = Isotope::Condition::IRG;
          } else if (line.find("Aerosol Iodine") != line.npos) {
            cond = Isotope::Condition::I_AER;
          } else if (line.find("Organic Iodine") != line.npos) {
            cond = Isotope::Condition::I_ORG;
          } else if (line.find("Aerosol") != line.npos) {
            cond = Isotope::Condition::AER;
          } else if (line.find("Molecular Iodine") != line.npos) {
            cond = Isotope::Condition::I_MOL;
          } else {
            std::istringstream iss(line);
            std::string name;
            iss >> name;

            std::vector<double> current_release;
            double value;
            while (!iss.eof()) {
              iss >> value;
              current_release.push_back(value);
            }
            releases.push_back(Release(Isotope(name, cond), current_release));
          }
        }
      }

      return releases;
    }

  private:
    std::ifstream istrm_;
};

#endif // FILEREADER_H_