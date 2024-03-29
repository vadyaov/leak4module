#ifndef NUCLIDES_H_
#define NUCLIDES_H_

#include <vector>
#include <map>
#include <fstream>

#include "nuclide.h"

#include <iostream>
/*
  Класс Nuclides.
  Kласс содержит мапу из всех нуклидов всех нужных форм (включая три формы йода) как ключи,
  значениями являются вектора активности(пока что пустые).

  Класс ничего не знает о пути выброса. Все, за что он отвечает - набор нуклидов
  и их активности. dvector в на более высоком уровне будет нужного размера - размера
  временного вектора (количество точек вывода)
*/

// может лучше сделать std::vector<Nuclide> nuclides и std::vector<std::vector>> activity ? вместо multimap...

class Nuclides {
  public:
    typedef std::vector<double> dvector;

    Nuclides(const std::string& source_file, int time_points_num);

    void Print() const noexcept;

    double SumOf(const std::vector<int>& forms);

    dvector& GetNuclideActivity(const std::string& name, Nuclide::Tp type);
    std::vector<std::pair<std::string, dvector>> GetNuclideArray(Nuclide::Tp tp) const;

    int Size() const noexcept { return coolant_data_.size(); }

    int IodineNumber() const noexcept { return iodine_count; }
    int IrgNumber() const noexcept { return irg_count; }
    int AerNumber() const noexcept { return aer_count; }

    std::vector<std::string> GetNuclidesNames(Nuclide::Tp form) const {
      std::vector<std::string> result;
      for (const auto& p : coolant_data_) {
        if (p.first.Type() == form)
          result.push_back(p.first.Name());
      }
      return result;
    }

  private:
    std::multimap<Nuclide, dvector> coolant_data_;
    int iodine_count, irg_count, aer_count;
};

#endif // NUCLIDES_H_
