#include "HaSLL/LoggerManager.hpp"
#include "Information_Model_Manager/ModelManager.hpp"

#include <iostream>
#include <stdexcept>

using namespace HaSLL;
using namespace std;
using namespace Information_Model_Manager;

int main() {
  auto status = EXIT_SUCCESS;
  try {
    LoggerManager::initialise(makeDefaultRepository());
    try {
      auto technology_manager = ModelManager();
      if (!technology_manager.getModelDataConnector()) {
        throw runtime_error("Model Data Connector can not be null ptr");
      }
      cout << "Integration test succeeded." << endl;

    } catch (const exception& ex) {
      cerr << "Integration test failed due to exception: " << ex.what() << endl;
      status = EXIT_FAILURE;
    }

    LoggerManager::terminate();
  } catch (...) {
    cerr << "Integration test failed due to an unknown exception" << endl;
    status = EXIT_FAILURE;
  }
  exit(status);
}
