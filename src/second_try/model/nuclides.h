#ifndef NUCLIDES_H_
#define NUCLIDES_H_

#include <vector>
#include <map>
#include <fstream>

#include "nuclide.h"

#include <iostream>
/*
  Класс Nuclides.
  После работы конструктора по path = "variants/var_num/" класс содержит
  мапу из всех нуклидов всех нужных форм (включая три формы йода) как ключи,
  значениями являются вектора активности(пока что пустые).

  Класс ничего не знает о пути выброса. Все, за что он отвечает - набор нуклидов
  и их активности. dvector в на более высоком уровне будет нужного размера - размера
  временного вектора (количество точек вывода)
*/

class Nuclides {
  public:
    typedef std::vector<double> dvector;

    Nuclides(const std::string& source_file);

    void Print() const noexcept;

    // суммарный выброс по всем р/н в последнюю временную точку
    double TotalRelease() const noexcept;

    // суммарный выброс по одной группе р/н в последней точке
    double TotalOneFormRelease(Nuclide::Tp form) const noexcept;

    dvector& GetNuclideActivity(const Nuclide& nuclide);

  private:
    std::multimap<Nuclide, dvector> coolant_data_;
};

#endif // NUCLIDES_H_