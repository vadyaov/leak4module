#ifndef RELEASE_H_
#define RELEASE_H_

#include "nuclides.h"

#include <sstream>

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

    Release(const std::string& path, int w);

    void Print(int w) const noexcept;

    // суммарный выброс по всем нуклидам для пути Way
    double TotalRelease(Way w) const noexcept;

    // суммарный выброс по нуклидов в форме form для пути Way
    double TotalOneFormRelease(Way w, Nuclide::Tp form) const noexcept;

    int TotalNuclidesNumber() const noexcept { return nuc.Size(); }
    const std::vector<double>& GetTimeVector() const noexcept { return time_; }

    int IodineNumber() const noexcept { return nuc.IodineNumber(); }
    int IrgNumber() const noexcept { return nuc.IrgNumber(); }
    int AerNumber() const noexcept { return nuc.AerNumber(); }

  private:
     // плохо сделано. логика в том чтобы один раз инициализировать nuclides для всех путей
     // но наверняка можно сделать как то по другому, может, на более высоком уровне (variants)
     // хотя можно оставить и так, не сильно критично. Я не могу быть точно уверен что во всех вариантах
     // будут одни и те же изотопы (хотя скорее всего это так)
    Nuclides nuc;

    std::vector<std::pair<Nuclides, Way>> release_;
    std::vector<double> time_;     // output time points

  private:
    void GetReleaseActivity(const std::string& path_to_dir, int way); // way from 0 to 9 here (as log2 of Way)
};

#endif // RELEASE_H_