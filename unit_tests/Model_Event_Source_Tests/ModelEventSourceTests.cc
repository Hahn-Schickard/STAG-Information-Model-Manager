#include "Data_Consumer_Adapter_Interface/mocks/DataConsumerAdapterInterface_MOCK.hpp"
#include "Information_Model/mocks/Device_MOCK.hpp"
#include "ModelRegistry.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace std;
using namespace DCAI;
using namespace DCAI::testing;
using namespace Information_Model::testing;
using namespace Information_Model_Manager;

class ModelEventSourceTests : public ::testing::Test {
public:
  void SetUp() {
    event_source = make_shared<ModelRegistry>();
    event_listener = make_unique<DataConsumerAdapterInterfaceMock>(
        event_source, "DCAI_Mock");
  }

  shared_ptr<ModelRegistry> event_source;
  shared_ptr<DataConsumerAdapterInterfaceMock> event_listener;
};

// NOLINTNEXTLINE
TEST(ModelEventSourceThrowTest, thrrowsOnNullPtr) {
  auto event_source = make_shared<ModelRegistry>();
  EXPECT_THROW(
      auto event_listener = make_unique<DataConsumerAdapterInterfaceMock>(
          shared_ptr<ModelRegistry>(), "DCAI_Mock"),
      Event_Model::EventSourceIsNotInstantiated);
}

// NOLINTNEXTLINE
TEST(ModelEventSourceThrowTest, canAttachEventSource) {
  auto event_source = make_shared<ModelRegistry>();
  EXPECT_NO_THROW(
      auto event_listener = make_unique<DataConsumerAdapterInterfaceMock>(
          event_source, "DCAI_Mock"));
}

// NOLINTNEXTLINE
TEST_F(ModelEventSourceTests, canStart) {
  EXPECT_CALL(*event_listener, start()).Times(1);

  EXPECT_NO_THROW(event_listener->start());
}

// NOLINTNEXTLINE
TEST_F(ModelEventSourceTests, canHandleEvent) {
  EXPECT_CALL(*event_listener, handleEvent(::testing::_)).Times(1);

  EXPECT_TRUE(event_source->registerDevice(
      make_shared<MockDevice>("123", "mocked", "mocked device")));

  this_thread::sleep_for(50ms); // block premature destruction
}

// NOLINTNEXTLINE
TEST_F(ModelEventSourceTests, canStop) {
  EXPECT_CALL(*event_listener, stop()).Times(1);

  EXPECT_NO_THROW(event_listener->stop());
}
