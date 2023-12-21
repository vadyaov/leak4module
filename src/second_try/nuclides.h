#ifndef NUCLIDES_H_
#define NUCLIDES_H_

#include <vector>
#include <map>
#include <fstream>

#include "nuclide.h"

#include <iostream>

class Nuclides {

  public:
    typedef std::vector<double> dvector;

    Nuclides(const std::string& source_file) {
      std::ifstream ifstrm(source_file + "Initial_Coolant_Data.txt");
      if (!ifstrm.is_open())
        throw std::invalid_argument("Can't open " + source_file);

      std::string line;
      while (std::getline(ifstrm, line)) {
        std::string name = GetName(line);
        int type = GetType(line) + 1;

        if (name[0] == 'I') {
          coolant_data_.insert(std::make_pair(Nuclide(name, Nuclide::IOD_MOL), dvector()));
          coolant_data_.insert(std::make_pair(Nuclide(name, Nuclide::IOD_ORG), dvector()));
          coolant_data_.insert(std::make_pair(Nuclide(name, Nuclide::IOD_AER), dvector()));
        } else {
          coolant_data_.insert(std::make_pair(Nuclide(name, type), dvector()));
        }
      }

    }

    void Print() const noexcept {
      for (const auto& [key, value] : coolant_data_) {
        std::cout << key.Type() << " [" << key.Name() << "] = "; 
        for (double act : value)
          std::cout << act << " ";
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }

    dvector& GetNuclideActivity(const Nuclide& nuclide) {
      for (auto it = coolant_data_.begin(); it != coolant_data_.end(); ++it) {
        if (it->first.Name() == nuclide.Name() && it->first.Type() == nuclide.Type())
          return it->second;
      }
      throw std::runtime_error("No NUCLIDE found");
    }

    private:

    int GetType(const std::string& line) {
      return (line[line.size() - 1] - '0');
    }

    std::string GetName(const std::string& s) {
      std::string name;
      for (const auto& c : s) {
        if (c == ',' || c == ' ') break;
        name.push_back(c);
      }

      return name;
    }

  private:
    std::multimap<Nuclide, dvector> coolant_data_;

};

#endif // NUCLIDES_H_