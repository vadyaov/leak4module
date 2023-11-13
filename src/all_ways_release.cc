#include "all_ways_release.h"

#include <filesystem>

namespace fs = std::filesystem;

void AllWaysRelease::LoadAllData() { // opening in current dir --> open results --> read all files with LoadData
// 1. open "results"
// 2. out all filenames first
    // std::cout << "Current dir name is: " << fs::current_path() << '\n';

    fs::path current = fs::current_path().root_path();
    current /= "Work";
    current /= "Leak4";
    current /= "true";
    // fs::path current = fs::current_path();

    fs::path results_dir = current /= "results";

    int i = 0;
    for (const auto& entry : fs::directory_iterator(results_dir)) {
        OneWayRelease one_way(OneWayRelease::Way(i++));
        one_way.LoadData(entry.path().string());
        all_ways_.push_back(one_way);
    }
}