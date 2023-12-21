#include "release.h"

// #include "dir_handler.h"

int main() {

  Release data1("variants/1/", Release::Bypass | Release::CVent);
  Release data2("variants/2/", Release::Bypass | Release::CVent);

  data1.Print();
  data2.Print();

  // DirectoryHandler h("variants");

  return 0;
}