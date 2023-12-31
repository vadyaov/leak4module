#ifndef ALL_WAYS_RELEASE_H_
#define ALL_WAYS_RELEASE_H_

#include "one_way.h"
#include <filesystem>

namespace fs = std::filesystem;

class AllWaysRelease {
  public:
    AllWaysRelease() {}

    void LoadAllData(const fs::path&);

    OneWayRelease GetRelease(OneWayRelease::Way w) const {
      OneWayRelease release;
      for (const auto& one_way : all_ways_)
        if (one_way.GetWay() == w) release = one_way;

      return release;
    }

    friend std::ostream& operator<<(std::ostream& os, AllWaysRelease& all_ways) {
      for (const auto& one_way : all_ways.all_ways_)
        os << one_way << std::endl;

      return os;
    }

  private:
    std::vector<OneWayRelease> all_ways_;
};

#endif // ALL_WAYS_RELEASE_H_