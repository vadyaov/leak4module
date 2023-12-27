#ifndef NUCLIDE_H_
#define NUCLIDE_H_

#include <string>

class Nuclide {
  public:
    enum Tp {IOD_MOL = 0, IOD_ORG, IOD_AER, IRG, AER};

    Nuclide(const std::string& name, int t);

    std::string Name() const noexcept;
    Tp Type() const noexcept;

  private:
    std::string name_;
    Tp t_;
};

bool operator<(const Nuclide& lhs, const Nuclide& rhs);

#endif // NUCLIDE_H_