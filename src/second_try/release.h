#pragma once

#include "nuclides.h"

#include <sstream>

class Release {
  public:
    enum Way {AAir, ASurf, AVent, Bypass, CAir, CSurf, CVent, SourceAct, SprinkAct};
    Release(const std::string& path, Way w) : release_{path}, w_{w} {
      time_ = GetTimeArray(path + "/Initial_Systems_Data.txt");
      GetReleaseActivity(path, w);
      std::cout << "TIME : ";
      for (double t : time_)
        std::cout << t << " ";
      std::cout << "\n";
      release_.Print();
    }

  private:
    Nuclides release_;
    std::vector<double> time_;     // output time points
    Way w_;

    std::vector<double> GetTimeArray(const std::string& path) {
      std::vector<double> t;

      std::ifstream ifstrm(path);
      if (!ifstrm.is_open())
        throw std::invalid_argument("Can't open file " + path);

      std::string line;
      // because time line is #8
      for (int i = 0; i != 9; ++i) {
        std::getline(ifstrm, line);
        if (i == 7) {
          size_t last_index = line.find_first_of("0123456789");
          std::string num = line.substr(last_index);
          t.resize(std::stoi(num));
        } else if (i == 8) {
          size_t last_index = line.find_first_of("0123456789");
          std::string num = line.substr(last_index);

          std::stringstream ss(num);
           for (std::size_t i = 0; i != t.size(); ++i)
            ss >> t[i];
        }
      }

      return t;
    }

    void GetReleaseActivity(const std::string& path_to_dir, Way w) {
      const std::vector<std::string> file_names {"AnnulusAirActOut", "AnnulusSurfActOut", "AnnulusVentRelease", "BypassReleaseOut", "ContAirActOut", "ContSurfActOut", "ContVentReleaseOut", "SourceActOut", "SprinklerActOut"};
      std::string current_way{path_to_dir + "results/" + file_names[static_cast<int>(w)] + ".txt"};

      std::cout << "Current file: " << current_way << "\n";

      std::ifstream ifstrm(current_way);
      if (!ifstrm.is_open())
        throw std::invalid_argument("Can't open file " + current_way);

      std::string line;
      // 11 lines before Iodime molecular
      for (int i = 0; i < 12; ++i)
        std::getline(ifstrm, line);

      const std::vector<Nuclide::Tp> forms = {Nuclide::IOD_MOL, Nuclide::IRG, Nuclide::AER, Nuclide::IOD_ORG, Nuclide::IOD_AER};

      for (std::size_t f = 0; f != forms.size(); ++f) {
        while (!line.empty()) {
          std::stringstream ss(line);
          std::string name;
          ss >> name;

          Nuclides::dvector& act_vec = release_.GetNuclideActivity({name, forms[f]});
          act_vec.resize(time_.size()); // это можно сделать раньше, но есть ли смысл?
          for (std::size_t i = 0; i != time_.size(); ++i) {
            std::cout << "HERE for " << name << " " << forms[f] << "\n";
            double i_act;
            ss >> i_act;
            std::cout << i_act << " ";
            act_vec[i] = i_act;
          }
          std::getline(ifstrm, line);
        }

        for (int i = 0; i < 4; ++i)
          std::getline(ifstrm, line);
      }
      

//      now staying at first mol iodine nuclide
      // while (!line.empty()) {
      //   std::stringstream ss(line);
      //   std::string name;
      //   ss >> name;
      //   std::cout << "Nuclide name: " << name << "\n";
      //   Nuclides::dvector& act_vec = release_.GetNuclideActivity({name, Nuclide::IOD_MOL});
      //   act_vec.resize(time_.size());
      //   for (std::size_t i = 0; i != time_.size(); ++i) {
      //     ss >> act_vec[i];
      //   }
      //   std::getline(ifstrm, line);
      // }

      // for (int i = 0; i < 4; ++i)
      //   std::getline(ifstrm, line);

      // // now staying at first IRG
      // while (!line.empty()) {
      //   std::stringstream ss(line);
      //   std::string name;
      //   ss >> name;
      //   std::cout << "Nuclide name: " << name << "\n";
      //   Nuclides::dvector& act_vec = release_.GetNuclideActivity({name, Nuclide::IRG});
      //   act_vec.resize(time_.size());
      //   for (std::size_t i = 0; i != time_.size(); ++i) {
      //     ss >> act_vec[i];
      //   }
      //   std::getline(ifstrm, line);
      // }

      // for (int i = 0; i < 4; ++i)
      //   std::getline(ifstrm, line);

      // // now staying at first AER
      // while (!line.empty()) {
      //   std::stringstream ss(line);
      //   std::string name;
      //   ss >> name;
      //   std::cout << "Nuclide name: " << name << "\n";
      //   Nuclides::dvector& act_vec = release_.GetNuclideActivity({name, Nuclide::AER});
      //   act_vec.resize(time_.size());
      //   for (std::size_t i = 0; i != time_.size(); ++i) {
      //     ss >> act_vec[i];
      //   }
      //   std::getline(ifstrm, line);
      // }

      // for (int i = 0; i < 4; ++i)
      //   std::getline(ifstrm, line);

      // // // now staying at first org ioddine
      // std::cout << line << "\n";
      // while (!line.empty()) {
      //   std::stringstream ss(line);
      //   std::string name;
      //   ss >> name;
      //   std::cout << "Nuclide name: " << name << "\n";
      //   Nuclides::dvector& act_vec = release_.GetNuclideActivity({name, Nuclide::IOD_ORG});
      //   std::cout << "size = " << act_vec.size() << "\n";
      //   act_vec.resize(time_.size(), 0);
      //   for (std::size_t i = 0; i != time_.size(); ++i) {
      //     ss >> act_vec[i];
      //   }
      //   std::getline(ifstrm, line);
      // }

      // for (int i = 0; i < 4; ++i)
      //   std::getline(ifstrm, line);

      // // now staying at first aer ioddine
      // while (!line.empty()) {
      //   std::stringstream ss(line);
      //   std::string name;
      //   ss >> name;
      //   std::cout << "Nuclide name: " << name << "\n";
      //   Nuclides::dvector& act_vec = release_.GetNuclideActivity({name, Nuclide::IOD_AER});
      //   act_vec.resize(time_.size());
      //   for (std::size_t i = 0; i != time_.size(); ++i) {
      //     ss >> act_vec[i];
      //   }
      //   std::getline(ifstrm, line);
      // }

      // for (int i = 0; i < 4; ++i)
      //   std::getline(ifstrm, line);
    }
};