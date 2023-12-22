#include "variants.h"

int main() {

  Variants accident("variants/", Release::CVent | Release::Bypass);

  accident.print();

  return 0;
}