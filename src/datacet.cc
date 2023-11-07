#include "dataset.h"
#include "filereader.h"

void Dataset::LoadData(const std::string& filename) {
  FileReader reader(filename);
  times_ = reader.GetTimeArray();
  releases_ = reader.GetData();
}