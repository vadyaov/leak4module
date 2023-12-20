#include "one_way.h"
#include "filereader.h"

void OneWayRelease::LoadData(const std::string& filename) {
  FileReader reader(filename);
  times_ = reader.GetTimeArray();
  releases_ = reader.GetData();
}