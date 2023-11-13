#ifndef ALL_WAYS_RELEASE_H_
#define ALL_WAYS_RELEASE_H_

#include "one_way.h"

/*открывается в директории одного варианта переходит в папку "results", собирает результаты по всем путям*/

class AllWaysRelease {
  public:
    AllWaysRelease() {
      std::cout << "constructor all_ways_release\n";
    }

    void LoadAllData(); // opening in current dir --> open results --> read all files with LoadData

    friend std::ostream& operator<<(std::ostream& os, AllWaysRelease& all_ways) {
      for (const auto& one_way : all_ways.all_ways_)
        os << one_way << std::endl;

      return os;
    }

  private:
    std::vector<OneWayRelease> all_ways_;
};

#endif // ALL_WAYS_RELEASE_H_