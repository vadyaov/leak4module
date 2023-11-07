#ifndef ISOTOPE_H_
#define ISOTOPE_H

#include <string>
#include <iostream>

class Isotope {

public:
  enum Condition {I_MOL, I_ORG, I_AER, IRG, AER};

  Isotope() = delete; // ?

  Isotope(const std::string& name, Condition c) : name_{name}, condition_{c} {
    std::cout << "Created " << name;

    switch (c)
    {
    case I_MOL:
      std::cout << "  Molecular iodine\n";
      break;
    case I_ORG:
      std::cout << "  Organic iodine\n";
      break;
    case I_AER:
      std::cout << "  Aerosol iodine\n";
      break;
    case IRG:
      std::cout << "  IRG\n";
      break;
    case AER:
      std::cout << "  Aerosol\n";
      break;
    default:
      std::cout << "  UNKNOWN\n";
      break;
    }

  }

  std::string GetName() const noexcept {
    return name_;
  }

  Condition GetCondition() const noexcept {
    return condition_;
  }
  
  private:
    std::string name_;
    Condition condition_;
};

#endif // ISOTOPE_H