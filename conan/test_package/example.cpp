#include "LoggerRepository.hpp"
#include "TechnologyManager.hpp"

using namespace HaSLL;
using namespace std;
using namespace Information_Access_Manager;

int main() {
  try {
    auto config = Configuration(
        "./log", "logfile.log", "[%Y-%m-%d-%H:%M:%S:%F %z][%n]%^[%l]: %v%$",
        SeverityLevel::TRACE, false, 8192, 2, 25, 100, 1);
    LoggerRepository::initialise(config);

    auto technology_manager = TechnologyManager();
  } catch (const exception &ex) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}