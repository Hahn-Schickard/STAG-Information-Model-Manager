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
  void SetUp() { event_source = make_shared<ModelRegistry>(); }

  shared_ptr<ModelRegistry> event_source;
  shared_ptr<DataConsumerAdapterInterfaceMock> event_listener;
};

TEST_F(ModelEventSourceTests, thrrowsOnNullPtr) {
  EXPECT_THROW(event_listener = make_unique<DataConsumerAdapterInterfaceMock>(
                   shared_ptr<ModelRegistry>(), "DCAI_Mock"),
               Event_Model::EventSourceIsNotInstantiated);
}

TEST_F(ModelEventSourceTests, canAttachEventSource) {
  EXPECT_NO_THROW(event_listener =
                      make_unique<DataConsumerAdapterInterfaceMock>(
                          event_source, "DCAI_Mock"));
}

TEST_F(ModelEventSourceTests, canStart) {
  if (!event_listener)
    event_listener = make_unique<DataConsumerAdapterInterfaceMock>(event_source,
                                                                   "DCAI_Mock");
  EXPECT_CALL(*event_listener, start()).Times(1);

  EXPECT_NO_THROW(event_listener->start());
}

TEST_F(ModelEventSourceTests, canHandleEvent) {
  if (!event_listener)
    event_listener = make_unique<DataConsumerAdapterInterfaceMock>(event_source,
                                                                   "DCAI_Mock");

  EXPECT_CALL(*event_listener, handleEvent(::testing::_)).Times(1);

  EXPECT_TRUE(event_source->registerDevice(
      make_shared<MockDevice>("123", "mocked", "mocked device")));
}

TEST_F(ModelEventSourceTests, canStop) {
  if (!event_listener)
    event_listener = make_unique<DataConsumerAdapterInterfaceMock>(event_source,
                                                                   "DCAI_Mock");
  EXPECT_CALL(*event_listener, stop()).Times(1);

  EXPECT_NO_THROW(event_listener->stop());
}