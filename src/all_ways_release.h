#ifndef ALL_WAYS_RELEASE_H_
#define ALL_WAYS_RELEASE_H_

#include "one_way.h"

#include <filesystem>

/*открывается в директории одного варианта переходит в папку "results", собирает результаты по всем путям*/

class AllWaysRelease {
  public:
    // AllWaysRelease()

  private:
    std::vector<OneWayRelease> all_ways_;
};

#endif // ALL_WAYS_RELEASE_H_