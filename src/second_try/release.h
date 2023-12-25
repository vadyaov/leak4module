#ifndef RELEASE_H_
#define RELEASE_H_

#include "nuclides.h"

#include <sstream>

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

    void Print(Way w) const noexcept;

    double TotalRelease(Way w) const noexcept;
    double TotalOneFormRelease(Way w, Nuclide::Tp form) const noexcept;

  private:
    Nuclides nuc;
    std::vector<std::pair<Nuclides, Way>> release_;
    std::vector<double> time_;     // output time points

  private:
    void GetReleaseActivity(const std::string& path_to_dir, int way); // way from 0 to 9 here (as log2 of Way)
};

#endif // RELEASE_H_