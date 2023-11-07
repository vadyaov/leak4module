#ifndef RELEASE_H_
#define RELEASE_H_

#include "isotope.h"

#include <vector>
#include <iomanip>

class Release {

  public:
  // mb use move semantic for activity
  Release(Isotope is, const std::vector<double>& act) : isotope_{is}, activity_{act} {
  }

  friend std::ostream& operator<<(std::ostream& os, const Release& rel) {
    os << rel.isotope_.GetName();

    for (double act : rel.activity_) {
      os << std::setw(10);
      os << act;
    }
    os << std::endl;

    return os;
  }

  private:
    Isotope isotope_;
    std::vector<double> activity_;
};

#endif // RELEASE_H_