#include "HaSLL/LoggerManager.hpp"
#include "HaSLL/SPD_LoggerRepository.hpp"
#include "Information_Model_Manager/ModelManager.hpp"

#include <iostream>
#include <stdexcept>

using namespace HaSLL;
using namespace std;
using namespace Information_Model_Manager;

int main() {
  try {
    auto repo = std::make_shared<SPD_LoggerRepository>();
    LoggerManager::initialise(repo);
    auto logger = LoggerManager::registerLogger("main");
    try {
      auto technology_manager = ModelManager();
      if (!technology_manager.getModelEventSource()) {
        throw runtime_error("Event source can not be null ptr");
      }
      logger->info("Integration test succeeded.");
      exit(EXIT_SUCCESS);
    } catch (const exception& ex) {
      logger->error("Integration test failed due to exception: {}", ex.what());
      exit(EXIT_FAILURE);
    }
  } catch (const exception& ex) {
    cerr << "Integration test failed due to exception: " << ex.what() << endl;
    exit(EXIT_FAILURE);
  }
}
