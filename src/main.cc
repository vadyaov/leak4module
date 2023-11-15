#include "dir_runner.h"

int main() {
  AllVariants variants;
  variants.LoadVariants();
  std::cout << variants << std::endl;
  return 0;
}