#include "nuclide.h"

#include <iostream>

Nuclide::Nuclide(const std::string& name, int t) : name_{name}, t_{Tp(t)} {
  /* std::cout << "Creating Nuclide with name " << name << " and type " << t << "\n"; */
}

std::string Nuclide::Name() const noexcept { return name_; }
Nuclide::Tp Nuclide::Type() const noexcept {return t_; } 

bool operator<(const Nuclide& lhs, const Nuclide& rhs) {
  return lhs.Name() < rhs.Name();
}
