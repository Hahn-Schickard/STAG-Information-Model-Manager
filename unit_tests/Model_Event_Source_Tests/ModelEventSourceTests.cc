#include "Data_Consumer_Adapter_Interface/mocks/DataConsumerAdapterInterface_MOCK.hpp"
#include "Information_Model/mocks/Device_MOCK.hpp"
#include "ModelRepository.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace std;
using namespace Data_Consumer_Adapter;
using namespace Data_Consumer_Adapter::testing;
using namespace Information_Model;
using namespace Information_Model::testing;
using namespace Information_Model_Manager;

class ModelEventSourceTests : public ::testing::Test {
public:
  void SetUp() override {
    event_source = make_shared<ModelRepository>();
    event_listener =
        make_unique<DataConsumerAdapterMock>(event_source, "DCAI_Mock");
  }

  shared_ptr<ModelRepository> event_source;
  shared_ptr<DataConsumerAdapterMock> event_listener;
};

// NOLINTNEXTLINE
TEST(ModelEventSourceThrowTest, thrrowsOnNullPtr) {
  auto event_source = make_shared<ModelRepository>();
  EXPECT_THROW(auto event_listener = make_unique<DataConsumerAdapterMock>(
                   shared_ptr<ModelRepository>(), "DCAI_Mock"),
      Event_Model::EventSourceIsNotInstantiated);
}

// NOLINTNEXTLINE
TEST(ModelEventSourceThrowTest, canAttachEventSource) {
  auto event_source = make_shared<ModelRepository>();
  EXPECT_NO_THROW(auto event_listener = make_unique<DataConsumerAdapterMock>(
                      event_source, "DCAI_Mock"));
}

// NOLINTNEXTLINE
TEST_F(ModelEventSourceTests, canStart) {
  EXPECT_CALL(*event_listener, start(::testing::_)).Times(1);

  EXPECT_NO_THROW(event_listener->start({}));
}

// NOLINTNEXTLINE
TEST_F(ModelEventSourceTests, canHandleEvent) {
  NonemptyDevicePtr device =
      NonemptyDevicePtr(make_shared<::testing::NiceMock<MockDevice>>(
          "123", "mocked", "mocked device"));
  EXPECT_CALL(*event_listener, registrate(::testing::_)).Times(1);

  EXPECT_TRUE(event_source->add(device));

  this_thread::sleep_for(50ms); // block premature destruction
}

// NOLINTNEXTLINE
TEST_F(ModelEventSourceTests, canStop) {
  EXPECT_CALL(*event_listener, stop()).Times(1);

  EXPECT_NO_THROW(event_listener->stop());
}
