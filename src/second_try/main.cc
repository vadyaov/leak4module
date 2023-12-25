#include "variants.h"

int main() {

  Variants accident("variants/", Release::CVent | Release::Bypass);

  // accident.print(Release::Bypass);

  accident.FindMaxForAll(Release::Bypass).Print(Release::Bypass);
  accident.FindMaxForAll(Release::CVent).Print(Release::CVent);

  accident.FindMaxForNuclide(Release::Bypass, Nuclide::IOD_MOL);

  return 0;
}