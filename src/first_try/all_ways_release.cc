#include "all_ways_release.h"

void AllWaysRelease::LoadAllData(const fs::path& var_path) { // inside one var

    fs::path results_dir = var_path;
    results_dir /= "results";

    int i = 0;
    for (const auto& entry : fs::directory_iterator(results_dir)) {
        OneWayRelease one_way(OneWayRelease::Way(i++));
        one_way.LoadData(entry.path().string());
        all_ways_.push_back(one_way);
    }
}