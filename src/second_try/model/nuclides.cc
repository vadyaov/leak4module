#include "nuclides.h"

namespace {

int GetType(const std::string& line) {
  size_t lastDigitIndex = line.find_last_of("0123456789");
  if (lastDigitIndex != std::string::npos) {
    return std::stoi(line.substr(lastDigitIndex));
  }

  throw std::runtime_error("GetType function error.");
}

std::string GetName(const std::string& s) {
  std::string name;
  for (const auto& c : s) {
    if (c == ',' || c == ' ') break;
    name.push_back(c);
  }
  return name;
}

} // namespace

Nuclides::Nuclides(const std::string& source_file, int time_points_num) : iodine_count{0}, irg_count{0}, aer_count{0} {
  std::ifstream ifstrm(source_file + "Initial_Coolant_Data.txt");
  if (!ifstrm.is_open())
    throw std::invalid_argument("Can't open " + source_file);

  std::string line;
  while (std::getline(ifstrm, line)) {
    std::string name = GetName(line);
    if (name[0] == 'I') {
      coolant_data_.insert(std::make_pair(Nuclide(name, Nuclide::IOD_MOL), dvector(time_points_num)));
      coolant_data_.insert(std::make_pair(Nuclide(name, Nuclide::IOD_ORG), dvector(time_points_num)));
      coolant_data_.insert(std::make_pair(Nuclide(name, Nuclide::IOD_AER), dvector(time_points_num)));

      iodine_count++;
    } else {
      int type = GetType(line) + 1;
      coolant_data_.insert(std::make_pair(Nuclide(name, type), dvector(time_points_num)));

      if (type == Nuclide::IRG)
        irg_count++;
      else if (type == Nuclide::AER)
        aer_count++;
    }
  }
}

Nuclides::dvector& Nuclides::GetNuclideActivity(const std::string& name, Nuclide::Tp type) {
  for (auto& it : coolant_data_) {
    if (it.first.Name() == name && it.first.Type() == type)
      return it.second;
  }
  throw std::runtime_error("No NUCLIDE" + name + " found");
}

std::vector<std::pair<std::string, Nuclides::dvector>> Nuclides::GetNuclideArray(Nuclide::Tp tp) const {
  std::vector<std::pair<std::string, dvector>> result;
  for (const auto& nucl : coolant_data_) {
    if (nucl.first.Type() == tp) {
      result.push_back(std::make_pair(nucl.first.Name(), nucl.second));
    }
  }
  return result;
}

void Nuclides::Print() const noexcept {
  for (const auto& [key, value] : coolant_data_) {
    std::cout << key.Type() << " [" << key.Name() << "] = "; 
    for (double act : value)
      std::cout << std::scientific << act << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

double Nuclides::SumOf(const std::vector<int>& forms) {
  double sum {0};
  for (const auto& nucl : coolant_data_) {
    for (int f : forms) {
      if (nucl.first.Type() == Nuclide::Tp(f)) {
        sum += nucl.second.back();
      }
    }
  }
  return sum;
}