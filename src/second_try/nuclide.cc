#include "nuclide.h"


Nuclide::Nuclide(const std::string& name, int t) : name_{name}, t_{Tp(t)} {}

std::string Nuclide::Name() const noexcept { return name_; }
Nuclide::Tp Nuclide::Type() const noexcept {return t_; } 

bool operator<(const Nuclide& lhs, const Nuclide& rhs) {
  return lhs.Name() < rhs.Name();
}