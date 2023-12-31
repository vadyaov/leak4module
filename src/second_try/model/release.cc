#include "release.h"

#include <cmath>

static std::vector<double> GetTimeArray(const std::string& path) {
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

Release::Release(const std::string& path, int w) : nuc{path} {
  time_ = GetTimeArray(path + "/Initial_Systems_Data.txt");
  for (int i = 0; i < 9; ++i) // 9 ways
    if (w & (1 << i)) {
      release_.resize(release_.size() + 1, std::make_pair(nuc, Release::Way(1 << i))); // dont like such logic here, mb do it one time before
      GetReleaseActivity(path, static_cast<int>(std::log2(1 << i)));
    }
}

// можно сделать этот метод статик, чтобы он просто был в области видимости класса, но принимал указатель на сам класс, так как методу по сути
// не нужны приватные поля.
// Его работа - заполнять векторы активности из класса Nuclides
// в общем, надо тут логику улучшить немного
void Release::GetReleaseActivity(const std::string& path_to_dir, int way) {
  static const std::vector<std::string> file_names {"AnnulusAirActOut", "AnnulusSurfActOut", "AnnulusVentReleaseOut", "BypassReleaseOut", "ContAirActOut", "ContSurfActOut", "ContVentReleaseOut", "SourceActOut", "SprinklerActOut"};
  std::string current_way{path_to_dir + "results/" + file_names[way] + ".txt"};

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

      Nuclides::dvector& act_vec = release_.back().first.GetNuclideActivity({name, forms[f]});
      act_vec.resize(time_.size()); // это можно сделать раньше, но есть ли смысл?
      for (std::size_t i = 0; i != time_.size(); ++i) {
        ss >> act_vec[i];
      }
      std::getline(ifstrm, line);
    }

    for (int i = 0; i < 4; ++i)
      std::getline(ifstrm, line);
  }
  
}

void Release::Print(Way w) const noexcept {
  for (const auto& one_way_release : release_) {
    if (one_way_release.second == w) {
      std::cout << "WAY #" << one_way_release.second << std::endl;
      one_way_release.first.Print();
    }
  }
}

double Release::TotalOneFormRelease(Way w, Nuclide::Tp form) const noexcept {
  double total_rel_for_one_form {0};
  for (const auto& rel : release_) {
    if (rel.second == w) {
      total_rel_for_one_form += rel.first.TotalOneFormRelease(form);
    }
  }
  return total_rel_for_one_form;
}

double Release::TotalRelease(Way w) const noexcept {
  double total_rel_for_all_nuc {0};
  for (const auto& rel : release_) {
    if (rel.second == w) {
      total_rel_for_all_nuc += rel.first.TotalRelease();
    }
  }
  return total_rel_for_all_nuc;
}