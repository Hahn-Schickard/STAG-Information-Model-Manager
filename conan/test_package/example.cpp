#include "LoggerRepository.hpp"
#include "ModelManager.hpp"

#include <stdexcept>

using namespace HaSLL;
using namespace std;
using namespace Information_Model_Manager;

int main() {
  try {
    auto config = Configuration(
        "./log", "logfile.log", "[%Y-%m-%d-%H:%M:%S:%F %z][%n]%^[%l]: %v%$",
        SeverityLevel::TRACE, false, 8192, 2, 25, 100, 1);
    LoggerRepository::initialise(config);

    auto technology_manager = ModelManager();
    if (!technology_manager.getModelEventSource())
      throw runtime_error("Event source can not be null ptr");
  } catch (const exception &ex) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}