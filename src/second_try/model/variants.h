#ifndef VARIANTS_H_
#define VARIANTS_H_

#include "release.h"

#include <iostream>

class Variants {
  public:
    Variants() {}

    void LoadData(const std::string& path);

    const std::vector<std::string>& GetNames() const noexcept;

    void print(int w) const;

    int TotalNuclidesNumber() const;

    const std::vector<double>& GetTimeArray() const;

    int IodNum() const;
    int IrgNum() const;
    int AerNum() const;

    std::vector<std::pair<std::string, Nuclides::dvector>> GetNuclideData(int variant_num, Release::Way way, Nuclide::Tp type);

    bool Empty() const noexcept;

    template<class T, class Compare = std::greater<T>>
    std::string FindVariant(Release::Way w, const std::vector<int>& forms, Compare comp) {
      std::string var_name = dir_names_[0];
      double sum = releases_[0].SumOfNuclidesActivity(w, forms);
      for (size_t i = 1; i != releases_.size(); ++i) {
        double sum_i = releases_[i].SumOfNuclidesActivity(w, forms);
        if (comp(sum_i, sum)) {
          sum = sum_i;
          var_name = dir_names_[i];
        }
      }

      return var_name;
    }

    std::vector<std::string> GetNuclideNames(Nuclide::Tp form) const {
      if (releases_.empty()) throw std::runtime_error("Empty release");

      return releases_.front().GetNuclideNames(form);
    }

    std::vector<std::pair<std::string, Nuclides::dvector>> NuclideActivityFor(const std::string& name, Release::Way w, Nuclide::Tp tp) {
      std::vector<std::pair<std::string, Nuclides::dvector>> data;
      data.reserve(releases_.size());
      for (std::size_t i = 0; i != releases_.size(); ++i) {
        data.push_back(std::make_pair(dir_names_[i], releases_[i].NuclideActivityFor(name, w, tp)));
      }

      return data;
    }

  private:
    std::vector<Release> releases_;
    std::vector<std::string> dir_names_;

};

#endif // VARIANTS_H_