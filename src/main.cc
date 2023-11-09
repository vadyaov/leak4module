#include "one_way.h"

#include <iostream>

int main() {
  Dataset data;
  data.LoadData("BypassReleaseOut.txt");
  std::cout << data << std::endl;
  return 0;
}