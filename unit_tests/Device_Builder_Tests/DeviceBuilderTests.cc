#include "DeviceImplementationBuilder.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace std;
using namespace Information_Model;
using namespace Information_Model_Manager;

TEST(DeviceBuilder, canBuildSimpplestDevice) {
  auto builder_ =
      make_unique<DeviceImplementationBuilder>("1234", "name", "desc");
  auto device = builder_->getResult();

  EXPECT_EQ("1234", device->getElementId());
  EXPECT_EQ("name", device->getElementName());
  EXPECT_EQ("desc", device->getElementDescription());
}
