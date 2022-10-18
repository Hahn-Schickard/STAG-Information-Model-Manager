#include "HaSLL/LoggerManager.hpp"
#include "HaSLL/SPD_LoggerRepository.hpp"

#include "gtest/gtest.h"

using namespace HaSLL;
using namespace std;

int main(int argc, char** argv) {
  auto repo = std::make_shared<SPD_LoggerRepository>();
  LoggerManager::initialise(repo);

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
