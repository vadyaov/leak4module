#ifndef RELEASE_H_
#define RELEASE_H_

#include "nuclides.h"

#include <sstream>
#include <filesystem>

/*
  Класс Release.
  Класс более высокого уровня над классом Nuclides.
  Класс Release содержит в качетсве основного поля с данными вектор release_,
  размер которого равен количеству путей, через которые нужно посмотреть выброс.
  Если нужен байпас и вентиляция, release_ будет содержать 2 пары <Nuclides, Way> 
  - байпас и вентсистема соответсвенно.

  ВАЖНО понимать:
    Единственный объект Release хранит данные для одного конкретного расчета, например,
    для варианта 1.
    Для варианта 2 будет другой объект Release.
*/
class Release {
  public:
    enum Way {AAir      = 1 << 0,
              ASurf     = 1 << 1,
              AVent     = 1 << 2,
              Bypass    = 1 << 3,
              CAir      = 1 << 4,
              CSurf     = 1 << 5,
              CVent     = 1 << 6,
              SourceAct = 1 << 7,
              SprinkAct = 1 << 8
            };

    Release(const std::string& path);

    void Print(int w) const noexcept;

    int TotalNuclidesNumber() const noexcept { return release_.back().first.Size(); }
    const std::vector<double>& GetTimeVector() const noexcept { return time_; }

    int IodineNumber() const noexcept { return release_.back().first.IodineNumber(); }
    int IrgNumber() const noexcept { return release_.back().first.IrgNumber(); }
    int AerNumber() const noexcept { return release_.back().first.AerNumber(); }

    double SumOfNuclidesActivity(Way w, const std::vector<int>& forms) {
      double res_sum {0};
      for (size_t i = 0; i != release_.size(); ++i) {
        if (release_[i].second == w) {
          res_sum += release_[i].first.SumOf(forms);
        }
      }
      return res_sum;
    }

    std::vector<std::pair<std::string, Nuclides::dvector>> GetNucData(Way way, Nuclide::Tp type) {
      std::vector<std::pair<std::string, Nuclides::dvector>> res;
      for (const auto& rel : release_) {
        if (rel.second == way) {
          return rel.first.GetNuclideArray(type);
        }
      }
      throw std::runtime_error("Runtime error. No nuclide found");
    }

    std::vector<std::string> GetNuclideNames(Nuclide::Tp form) const {
      return release_.front().first.GetNuclidesNames(form);
    }

  private:
    std::vector<std::pair<Nuclides, Way>> release_;
    std::vector<double> time_;     // output time points

  private:
    Nuclides LoadNuclidesData(const std::string& path_to_dir, int way); // way from 0 to 9 here (as log2 of Way)
};

#endif // RELEASE_H_
