#include "all_vars.h"

int main() {
  AllVariants variants;
  variants.LoadVariants();
  // std::cout << variants << std::endl;
  std::cout << variants.FindMaxVariant(OneWayRelease::Way::ContAirAct, Isotope::Condition::I_MOL);
  return 0;
}