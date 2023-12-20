#ifndef ONE_WAY_H_
#define ONE_WAY_H_

#include "release.h"

class OneWayRelease {
  public:
    enum Way {AnnulusAirAct, AnnulusSurfAct, AnnulusVentRel, BypassRel,
              ContAirAct, ContSurfAct, ContVentRel, SourceAct, SprinklerAct};

    OneWayRelease() {}
    OneWayRelease(Way w) : way{w} {}

    void LoadData(const std::string& filename); // loads releases and times from concrete file

    Way GetWay() const noexcept { return way; }

    double LatestSumInCondition(Isotope::Condition condition) const {
      double sum {0};
      for (const auto& release : releases_) {
        if (release.GetIsotoper().GetCondition() == condition) {
          sum += release.Back();
        }
      }
      return sum;
    }

    friend std::ostream& operator<<(std::ostream& os, const OneWayRelease& data) {
      os << "WAY = " << data.way << std::endl;
      os << std::setw(12);
      for (double moment : data.times_) {
        os << moment;
        os << std::setw(10);
      }
      os << std::setw(0);
      os << std::endl;

      bool flag = false; // rework this later
      for (const Release& rel : data.releases_){
        if (flag == false && rel.GetIsotoper().GetCondition() == Isotope::Condition::I_MOL) {
          os << "\nMOLECULAR IODINE" << std::endl;
          flag = true;
        }
        if (flag == true && rel.GetIsotoper().GetCondition() == Isotope::Condition::IRG) {
          os << "\nIRG" << std::endl;
          flag = false;
        }
        if (flag == false && rel.GetIsotoper().GetCondition() == Isotope::Condition::AER) {
          os << "\nAEROSOL" << std::endl;
          flag = true;
        }
        if (flag == true && rel.GetIsotoper().GetCondition() == Isotope::Condition::I_ORG) {
          os << "\nORGANIC IODINE" << std::endl;
          flag = false;
        }
        if (flag == false && rel.GetIsotoper().GetCondition() == Isotope::Condition::I_AER) {
          os << "\nAEROSOL IODINE" << std::endl;
          flag = true;
        }
        os << rel;
      }

      return os;
    }

  private:
    std::vector<Release> releases_;
    std::vector<double> times_;
    Way way;
};

#endif // ONE_WAY_H_