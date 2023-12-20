#pragma once

#include <string>

class Nuclide {
  public:
    enum Tp {IOD_MOL, IOD_ORG, IOD_AER, IRG, AER};
    Nuclide(const std::string& name, int t) : name_{name}, t_{Tp(t)} {}

    std::string Name() const noexcept { return name_; }
    Tp Type() const noexcept {return t_; } 

    // bool operator==(const Nuclide& lhs) {
    //   return lhs.name_ == name_ && lhs.t_ == t_;
    // }

  private:
    std::string name_;
    Tp t_;
};

bool operator<(const Nuclide& lhs, const Nuclide& rhs) {
  return lhs.Name() < rhs.Name();
}