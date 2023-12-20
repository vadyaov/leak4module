#ifndef ISOTOPE_H_
#define ISOTOPE_H_

#include <string>
#include <iostream>

class Isotope {

public:
  enum Condition {I_MOL, I_ORG, I_AER, IRG, AER};

  Isotope(const std::string& name, Condition c) : name_{name}, condition_{c} {}

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

#endif // ISOTOPE_H_