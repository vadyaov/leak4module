#ifndef ISOTOPE_H_
#define ISOTOPE_H

#include <string>

class Isotope {

  enum type {I_MOL, I_ORG, IRG, AEROSOL};
  
  private:
    std::string name_;
    type t_;
};

#endif // ISOTOPE_H