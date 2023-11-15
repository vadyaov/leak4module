#ifndef ALL_VARIANTS_H_
#define ALL_VARIANTS_H_

#include "all_ways_release.h"

class AllVariants {

    public:
        AllVariants() {}

        // opened in all_var directory, need to scroll all directories and use allwayrelease
        void LoadVariants() {
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (entry.is_directory()) {
                    std::cout << entry << std::endl;
                    AllWaysRelease all;
                    all.LoadAllData(entry);
                    variants_.push_back(all);
                }
            }
        }

        int FindMaxVariant(OneWayRelease::Way, Isotope::Condition condition);

        friend std::ostream& operator<<(std::ostream& os, AllVariants& vars) {
            int i = 1;
            for (auto& var : vars.variants_) {
                std::cout << "Variant " << i++ << std::endl;
                std::cout << var << "\n\n\n\n\n\n\n";
            }

            return os;
        }

    private:
        std::vector<AllWaysRelease> variants_;
};

#endif // ALL_VARIANTS_H_