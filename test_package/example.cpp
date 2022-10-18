#include "HaSLL/LoggerManager.hpp"
#include "HaSLL/SPD_LoggerRepository.hpp"
#include "Information_Model_Manager/ModelManager.hpp"

#include <stdexcept>

using namespace HaSLL;
using namespace std;
using namespace Information_Model_Manager;

int main() {
  try {
    auto repo = std::make_shared<SPD_LoggerRepository>();
    LoggerManager::initialise(repo);

    auto technology_manager = ModelManager();
    if (!technology_manager.getModelEventSource())
      throw runtime_error("Event source can not be null ptr");
  } catch (const exception& ex) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
